/*  _______    ________
    \      \  /  _____/  ____   ___
    /   |   \/   \  ____/ __ \ /   \
   /    |    \    \_\  \  ___/|   | \
   \____|__  /\______  /\___  >___| /
           \/        \/     \/    \/
The MIT License (MIT)

Copyright (c) 2013 Ngeneers Inc.

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

#include "Ngen.Delegate.hpp"
#include "Ngen.Array.hpp"

namespace Ngen {
	/** @brief An collection of delegate subscribers that are invoked together representing an event.
	    @example
	*/
	template<typename TReturn, typename... TParams>
	class ngen_api Event {
	public:
		class ngen_api Subscriber {
		public:
			Subscriber() : mThis(0), mFunc(0) {}
			Subscriber(unknown _this, Delegate* function) : mThis(_this), mFunc(function) {}
			Subscriber(Delegate* function) : mThis(0), mFunc(function) {}
			Subscriber(const Subscriber& copy) : mThis(copy.mThis), mFunc(copy.mFunc) {}
			~Subscriber() {
				mThis = null;
				mFunc = null;
			}

			bool IsValid() const {
				if(!isnull(mFunc)) {
					if(mFunc->IsMember()) {
						return !isnull(mThis);
					}

					return true;
				}

				return false;
			}

			bool operator==(const Subscriber& rhs) const {
				if(!isnull(mThis) && mThis != rhs.mThis) {
					return false;
				}

				return rhs.mFunc->EqualTo(mFunc);
			}

			bool operator!=(const Subscriber& rhs) const {
				if(!isnull(mThis) && mThis != rhs.mThis) {
					return true;
				}

				return !rhs.mFunc->EqualTo(mFunc);
			}

			unknown Call(unknown* params) {
				return mFunc->operator()(mThis, params);
			}
		protected:
			unknown mThis;
			Delegate* mFunc;
		};

		Event() : mEvent(1) {}

		Event(const Event& copy, bool readOnly = true) : mEvent(copy.mEvent, readOnly) {}

		Event(Event&& move) : mEvent((Array<Subscriber>&&)move.mEvent) {}

		virtual ~Event() {
			//mEvent.~Array<Subscriber>();
		}

		bool operator==(const Event& rhs) const {
			if(mEvent.Length() != rhs.mEvent.Length()) {
				return false;
			}

			Subscriber* lhsp = mEvent.Begin();
			Subscriber* rhsp = rhs.mEvent.Begin();
			while(lhsp != mEvent.End() && rhsp != rhs.mEvent.End()) {
				if(!lhsp->operator==(*rhsp)) {
					return false;
				}

				lhsp++;
				rhsp++;
			}

			return true;
		}

		Event& operator+=(const Subscriber& rhs) {
			mEvent.Add(rhs);
			return *this;
		}

		Event& operator-=(const Subscriber& rhs) {
			mEvent.Remove(rhs);
			return *this;
		}

		unknown operator()(unknown* params) {
			unknown ret = 0;
			Subscriber* lhsp = mEvent.Begin();
			while(lhsp != mEvent.End()) {
				if(lhsp->IsValid()) {
					ret = lhsp->Call(params);
				}

				lhsp++;
			}

			return ret;
		}

		uword Length() const {
			return mEvent.Length();
		}

		virtual bool Contains(const Subscriber& rhs) const {
			Subscriber lhsp;
			return pContains(rhs, inref lhsp);
		}

		bool IsNullOrEmpty() const {
			return mEvent.IsNullOrEmpty();
		}

		TReturn Invoke(TParams... params) {
			unknown args[sizeof...(TParams)] {
				(Cast<TParams>::To(params))...
			};

			return Cast<TReturn>::From(this->operator()(args));
		}

	protected:
		bool pContains(const Subscriber& rhs, Subscriber& item) const {
			Subscriber* lhsp = mEvent.Begin();
			while(lhsp != mEvent.End()) {
				if(lhsp->operator==(rhs)) {
					item = *lhsp;
					return true;
				}

				lhsp++;
			}

			return false;
		}

		Array<Subscriber> mEvent;
	};
}
#endif // __NGEN_STATICDELEGATE_HPP

