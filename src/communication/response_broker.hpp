/*
 * Copyright 2008 Search Solution Corporation
 * Copyright 2016 CUBRID Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */

#ifndef _RESPONSE_BROKER_HPP_
#define _RESPONSE_BROKER_HPP_

#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <limits>
#include <mutex>
#include <unordered_map>

namespace cubcomm
{
  using response_sequence_number = std::uint64_t;
  constexpr response_sequence_number NO_RESPONSE_SEQUENCE_NUMBER =
	  std::numeric_limits<response_sequence_number>::max ();

  class response_sequence_number_generator
  {
    public:
      response_sequence_number get_unique_number ()
      {
	return ++m_next_number;
      }

    private:
      std::atomic<response_sequence_number> m_next_number = 0;
  };

  template<typename T_PAYLOAD>
  class response_broker
  {
    public:
      response_broker () = delete;
      response_broker (size_t a_bucket_count);

      void register_response (response_sequence_number a_rsn, T_PAYLOAD &&a_payload);
      T_PAYLOAD get_response (response_sequence_number a_rsn);

    private:

      struct bucket
      {
	bucket () = default;
	bucket (bucket &&) = default;
	bucket (const bucket &);

	std::mutex m_mutex;
	std::condition_variable m_condvar;
	std::unordered_map<response_sequence_number, T_PAYLOAD> m_response_payloads;

	void register_response (response_sequence_number a_rsn, T_PAYLOAD &&a_payload);
	T_PAYLOAD get_response (response_sequence_number a_rsn);
      };

      bucket &get_bucket (response_sequence_number rsn);

      std::vector<bucket> m_buckets;
  };
}

//
// Template implementation
//

namespace cubcomm
{
  template <typename T_PAYLOAD>
  response_broker<T_PAYLOAD>::response_broker (size_t a_bucket_count)
  {
    assert (a_bucket_count > 0);
    m_buckets.resize (a_bucket_count);
  }

  template <typename T_PAYLOAD>
  typename response_broker<T_PAYLOAD>::bucket &
  response_broker<T_PAYLOAD>::get_bucket (response_sequence_number rsn)
  {
    return m_buckets[rsn % m_buckets.size ()];
  }

  template <typename T_PAYLOAD>
  void
  response_broker<T_PAYLOAD>::register_response (response_sequence_number a_rsn, T_PAYLOAD &&a_payload)
  {
    get_bucket (a_rsn).register_response (a_rsn, std::move (a_payload));
  }

  template <typename T_PAYLOAD>
  void
  response_broker<T_PAYLOAD>::bucket::register_response (response_sequence_number a_rsn, T_PAYLOAD &&a_payload)
  {
    {
      std::lock_guard<std::mutex> lk_guard (m_mutex);

      T_PAYLOAD &ent = m_response_payloads[a_rsn];
      ent = std::move (a_payload);
    }
    m_condvar.notify_all ();
  }

  template <typename T_PAYLOAD>
  T_PAYLOAD
  response_broker<T_PAYLOAD>::get_response (response_sequence_number a_rsn)
  {
    return get_bucket (a_rsn).get_response (a_rsn);
  }

  template <typename T_PAYLOAD>
  T_PAYLOAD
  response_broker<T_PAYLOAD>::bucket::get_response (response_sequence_number a_rsn)
  {
    std::unique_lock<std::mutex> ulock (m_mutex);
    T_PAYLOAD payload;

    auto condvar_pred = [this, &payload, a_rsn] ()
    {
      auto it = m_response_payloads.find (a_rsn);
      if (it == m_response_payloads.end ())
	{
	  return false;
	}
      payload = std::move ((*it).second);
      m_response_payloads.erase (it);
      return true;
    };
    m_condvar.wait (ulock, condvar_pred);

    return payload;
  }

  template <typename T_PAYLOAD>
  response_broker<T_PAYLOAD>::bucket::bucket (const bucket &o)
  {
    // Bucket copy constructor may be required only during the response_broker initialization.
    // The copied bucket is empty and no synchronization is required.
    assert (o.m_response_payloads.empty ());
  }
}

#endif // !_RESPONSE_BROKER_HPP_