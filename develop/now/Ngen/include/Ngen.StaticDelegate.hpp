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
#ifndef __NGEN_STATICDELEGATE_HPP
#define __NGEN_STATICDELEGATE_HPP

#include "Ngen.Delegate.hpp"
#include "Ngen.Cast.hpp"

namespace Ngen {
	/** @brief A non-member static function without a return argument.
	 */
	template<typename... TParams>
	class ngen_api VoidStaticDelegate : public VoidDelegate<TParams...> {
	public:
		/** @brief Native function signature. */
		typedef void(TFunction)(TParams...);

		/** @brief A type redefinition of the expanded delegate typename. */
		typedef VoidStaticDelegate<TParams...> TSelf;

		/** @brief Constructor. Default. */
		VoidStaticDelegate() : mFunction(0) {}

		/** @brief Constructor. (TFunction). */
		VoidStaticDelegate(TFunction func) : mFunction(func) {
		}

		/** @brief Constructor. Copy. */
		VoidStaticDelegate(const TSelf& copy) : mFunction(copy.mFunction) {}

		/** @brief De-constructor. */
		~VoidStaticDelegate() {
		}

		/** @brief Determines if the Delegate is equal-to another delegate. */
		virtual bool EqualTo(Delegate* rhs) const {
			if(rhs->IsMember() || rhs->IsNonVoid()) {
				return false;
	    }

			return ((TSelf*)rhs)->mFunction == mFunction;
		}

		/** @brief operator!=(const Delegate* const). */
		bool operator!=(const Delegate* const rhs) {
			if(rhs->IsMember() || rhs->IsNonVoid()) {
				return true;
			}

			return ((TSelf*)rhs)->mFunction != mFunction;
		}

		/** @brief operator=(const Delegate* const). */
		TSelf& operator=(const TSelf& rhs) {
			if(this == &rhs) {
				return *this;
			}

			mFunction = rhs.mFunction;
			return *this;
		}

		/** @brief operator()(unknown, unknown*). */
		unknown operator()(unknown _this, unknown* params) const {
			_Call(params, typename make_index_pack_t<sizeof...(TParams)>::type());
			return null;
		}

		/** @brief Determines if the delegate references a constant-member function. */
		bool IsConst() const { return false; }

		/** @brief Determines if the delegate references a member function. */
		bool IsMember() const { return false; }

      bool IsValid() const { return !isnull(mFunction); }

      void SetOwner(unknown owner) { }

		/** @brief Invokes the function being referenced by the delegate. */
		void Call(TParams... params) const {
			mFunction(params...);
		}

	protected:
		template<uword... I> void _Call(unknown* params, index_pack_t<I...>) const {
			Call((Cast<TParams>::From(params[I]))...);
		}

		TFunction* mFunction;
	};

	template<typename TReturn, typename... TParams>
	class ngen_api StaticDelegate : public NonVoidDelegate<TReturn, TParams...> {
	public:
		/** @brief Native function signature. */
		typedef TReturn(TFunction)(TParams...);

		typedef StaticDelegate<TReturn, TParams...> TSelf;

		StaticDelegate() : mFunction(0) {
		}

		StaticDelegate(TFunction func) : mFunction(func) {
		}

      StaticDelegate(const TSelf& copy) : mFunction(copy.mFunction) {
      }

		~StaticDelegate() {

		}

		/** @brief Determines if the Delegate is equal-to another delegate. */
		virtual bool EqualTo(Delegate* rhs) const {
			if(rhs->IsMember() || !rhs->IsNonVoid()) {
				return false;
			}

			return ((TSelf*)rhs)->mFunction == mFunction;
		}

		/** @brief operator=(const Delegate* const). */
		TSelf& operator=(const TSelf& rhs) {
			if(this == &rhs) {
				return *this;
			}

			mFunction = rhs->mFunction;
			return *this;
		}

		unknown operator()(unknown _this, unknown* params) const {
			return Cast<TReturn>::To(_Call(params, typename make_index_pack_t<sizeof...(TParams)>::type()));
		}

		bool IsConst() const { return false; }

		bool IsMember() const { return false; }

      bool IsValid() const { return !isnull(mFunction); }

      void SetOwner(unknown owner) {
      }

		TReturn Call(TParams... params) const {
			return mFunction(params...);
		}

	protected:
		template<uword... I>
		TReturn _Call(unknown* params, index_pack_t<I...>) const {
			return Call((Cast<TParams>::From(params[I]))...);
		}

		TFunction* mFunction;
	};
}
#endif // __NGEN_STATICDELEGATE_HPP
