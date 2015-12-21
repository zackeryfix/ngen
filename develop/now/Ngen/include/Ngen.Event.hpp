/*  _______    ________
    \      \  /  _____/  ____   ___
    /   |   \/   \  ____/ __ \ /   \
   /    |    \    \_\  \  ___/|   | \
   \____|__  /\______  /\___  >___| /
           \/        \/     \/    \/
The MIT License (MIT)

COPYRIGHT (C) 2016 RAZORWARE, LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#ifndef __NGEN_EVENT_HPP
#define __NGEN_EVENT_HPP

#include "Ngen.Callback.hpp"
#include "Ngen.Array.hpp"

namespace Ngen {
	/** @brief An collection of delegate subscribers that are invoked together representing an event.
	*/
	class ngen_api Event {
	public:
		/** @brief Constructor. Default. */
		Event() : mEvent(1) {}

		/** @brief Constructor. (const Event&, bool) */
		Event(const Event& copy, bool readOnly = true) : mEvent(copy.mEvent, readOnly) {}

		/** @brief Constructor. Move. */
		Event(Event&& move) : mEvent((Array<Callback>&&)move.mEvent) {}

		/** @brief De-constructor. */
		virtual ~Event() {}

		/** @brief operator==(const Event&) */
		bool operator==(const Event& rhs) const {
			if(mEvent.Length() != rhs.mEvent.Length()) {
				return false;
			}

			Callback* lhsp = mEvent.Begin();
			Callback* rhsp = rhs.mEvent.Begin();

			while(lhsp != mEvent.End() && rhsp != rhs.mEvent.End()) {
				if(!lhsp->operator==(*rhsp)) {
					return false;
				}

				lhsp++;
				rhsp++;
			}

			return true;
		}

		/** @brief operator+=(const Callback&) */
		Event& operator+=(const Callback& rhs) {
			mEvent.Add(rhs);
			return *this;
		}

		/** @brief operator-=(const Callback&) */
		Event& operator-=(const Callback& rhs) {
			mEvent.Remove(rhs);
			return *this;
		}

		/** @brief operator()(unknown*) */
		void operator()(unknown* params) {
			Callback* lhsp = mEvent.Begin();

			while(lhsp != mEvent.End()) {
				if(lhsp->IsValid()) {
					lhsp->Call(params);
				}

				lhsp++;
			}
		}

		/** @brief Gets the number of callbacks subscribed to the event. */
		uword Length() const {
			return mEvent.Length();
		}

		/** @brief Determines if the event is null or empty. */
		bool IsNullOrEmpty() const {
			return mEvent.IsNullOrEmpty();
		}

		/** @brief A type-safe function that can be used to invoke the event.
		 * @param params Each parameter needed to properly invoke the event.
		 */
		template<typename... TParams>
		void Fire(TParams... params) {
			unknown args[sizeof...(TParams)] {
				(Cast<TParams>::To(params))...
			};

			this->operator()(args);
		}

	protected:
		Array<Callback> mEvent;
	};
}
#endif

