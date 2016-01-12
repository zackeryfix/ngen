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
#ifndef __NGEN_CALLBACK_HPP
#define __NGEN_CALLBACK_HPP

#include "Ngen.Delegate.hpp"

namespace Ngen {
	/** @brief A function-call provider primarily used to bind object instances to member delegates before invocation.
	 */
	class ngen_api Callback {
	public:
		/** @brief Constructor. Default. */
		Callback() : mThis(0), mFunc(0) {}

		/** @brief Constructor. (unknown, Delegate*). */
		Callback(unknown _this, Delegate* function) : mThis(_this), mFunc(function) {}

		/** @brief Constructor. (Delegate*). */
		Callback(Delegate* function) : mThis(0), mFunc(function) {}

		/** @brief Constructor. Copy. */
		Callback(const Callback& copy) : mThis(copy.mThis), mFunc(copy.mFunc) {}

		/** @brief De-constructor. */
		~Callback() {
			mThis = null;
			mFunc = null;
		}

		/** @brief Determines if the callback is properly configured for an invocation. */
		bool IsValid() const {
			if(!isnull(mFunc)) {
				if(mFunc->IsMember()) {
					return !isnull(mThis);
				}

				return true;
			}

			return false;
		}

		/** @brief operator==(const Callback&) */
		bool operator==(const Callback& rhs) const {
			if(!isnull(mThis) && mThis != rhs.mThis) {
				return false;
			}

			return rhs.mFunc->EqualTo(mFunc);
		}

		/** @brief operator!=(const Callback&) */
		bool operator!=(const Callback& rhs) const {
			if(!isnull(mThis) && mThis != rhs.mThis) {
				return true;
			}

			return !rhs.mFunc->EqualTo(mFunc);
		}

		/** @brief Invokes the callback using the given unknown parameter set. */
		unknown Call(unknown* params) {
			return mFunc->operator()(mThis, params);
		}

		void MakeValid(unknown tthis) {
			mThis = tthis;
		}

		Type* ReturnType() const {
			return mFunc->ReturnType();
		}

	protected:
		unknown mThis;
		Delegate* mFunc;
	};
}
#endif // __NGEN_CALLBACK_HPP
