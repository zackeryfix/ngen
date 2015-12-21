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
#ifndef __NGEN_STATICDELEGATE_HPP
#define __NGEN_STATICDELEGATE_HPP

#include "Ngen.Delegate.hpp"
#include "Ngen.Cast.hpp"

namespace Ngen {
	/** @brief A non-member static function without a return argument.
	 */
   template<typename... TParams>
   class StaticDelegate : public VoidDelegate<TParams...> {
   public:
      /** @brief Native function signature. */
      typedef void(TFunction)(TParams...);

		/** @brief A type redefinition of the expanded delegate typename. */
      typedef StaticDelegate<TParams...> TSelf;

		/** @brief Constructor. Default. */
		StaticDelegate() : mFunction(0) {}

		/** @brief Constructor. (TFunction). */
      StaticDelegate(TFunction func) {
         mFunction = func;
      }

		/** @brief Constructor. Copy. */
      StaticDelegate(const StaticDelegate<TParams...>& copy) : mFunction(copy.mFunction) {}

		/** @brief De-constructor. */
      ~StaticDelegate() {

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
      unknown operator()(unknown _this, unknown* params) {
			_Call(params, typename make_index_pack_t<sizeof...(TParams)>::type());
			return null;
      }

		/** @brief Determines if the delegate references a constant-member function. */
      bool IsConst() const { return false; }

		/** @brief Determines if the delegate references a member function. */
      bool IsMember() const { return false; }


		/** @brief Invokes the function being referenced by the delegate. */
      void Call(TParams... params) {
			mFunction(params...);
      }

   protected:
   	template<uword... I> void _Call(unknown* params, index_pack_t<I...>) {
			Call((Cast<TParams>::From(params[I]))...);
   	}

      TFunction* mFunction;
   };

   template<typename TReturn, typename... TParams>
   class NonVoidStaticDelegate : public NonVoidDelegate<TReturn, TParams...> {
   public:
      /** @brief Native function signature. */
      typedef TReturn(TFunction)(TParams...);

      typedef NonVoidStaticDelegate<TParams...> TSelf;

		NonVoidStaticDelegate() : mFunction(0) {}

      NonVoidStaticDelegate(TFunction func) {
         mFunction = func;
      }

      ~NonVoidStaticDelegate() {

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

		unknown operator()(unknown _this, unknown* params) {
			TReturn ret = _Call(params, typename make_index_pack_t<sizeof...(TParams)>::type());
			return Cast<TReturn>::To(ret);
      }

      bool IsConst() const { return false; }

      bool IsMember() const { return false; }

		bool IsLinq() const { return false; }

      TReturn Call(TParams... params) {
         return mFunction(params...);
      }

   protected:
   	template<uword... I>
   	TReturn _Call(unknown* params, index_pack_t<I...>) {
			return Call((Cast<TParams>::From(params[I]))...);
   	}

      TFunction* mFunction;
   };
}
#endif // __NGEN_STATICDELEGATE_HPP
