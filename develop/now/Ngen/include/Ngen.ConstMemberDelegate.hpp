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
#ifndef __NGEN_CONSTMEMBERDELEGATE_HPP
#define __NGEN_CONSTMEMBERDELEGATE_HPP

#include "Ngen.Delegate.hpp"
#include "Ngen.Cast.hpp"

namespace Ngen {
	/** @brief A const member function without a return argument.
	 */
	template<typename TOwner, typename... TParams>
	class VoidConstMemberDelegate : public VoidDelegate<TParams...> {
	public:
		/** @brief Native function signature. */
		typedef void(TOwner::*TFunction)(TParams...) const;

		/** @brief A type redefinition of the expanded delegate typename. */
		typedef VoidConstMemberDelegate<TOwner, TParams...> TSelf;

		/** @brief Constructor. Default. */
		VoidConstMemberDelegate() : mOwner(0), mFunction(0) {
		}

		/** @brief Constructor. (TFunction). */
		VoidConstMemberDelegate(TFunction func) : mOwner(0), mFunction(func) {
		}

		/** @brief Constructor. (TOwner, TFunction). */
		VoidConstMemberDelegate(TOwner* owner, TFunction func) : mOwner(owner), mFunction(func) {
		}

		/** @brief Constructor. Copy. */
		VoidConstMemberDelegate(const TSelf& copy) : mOwner(copy.mOwner), mFunction(copy.mFunction) {
		}

		/** @brief De-constructor. */
		~VoidConstMemberDelegate() {
		}

		/** @brief Determines if the Delegate is equal-to another delegate. */
		virtual bool EqualTo(Delegate* rhs) const {
			if(!rhs->IsMember() || rhs->IsNonVoid() || !rhs->IsConst()) {
				return false;
	    }

			return ((TSelf*)rhs)->mFunction == mFunction&& ((TSelf*)rhs)->mOwner == mOwner;
		}

		/** @brief operator!=(const Delegate* const). */
		bool operator!=(const Delegate* const rhs) {
			if(!rhs->IsMember() || rhs->IsNonVoid() || !rhs->IsConst()) {
				return true;
			}

			return ((TSelf*)rhs)->mFunction != mFunction || ((TSelf*)rhs)->mOwner != mOwner;
		}

		/** @brief operator=(const Delegate* const). */
		TSelf& operator=(const TSelf& rhs) {
			if(this == &rhs) {
				return *this;
			}

         mOwner = rhs.mOwner;
			mFunction = rhs.mFunction;
			return *this;
		}

		/** @brief operator()(unknown, unknown*). */
		unknown operator()(unknown _this, unknown* params) const {
			_Call(_this, params, typename make_index_pack_t<sizeof...(TParams)>::type());
			return null;
		}

		/** @brief Determines if the delegate references a constant-member function. */
		bool IsConst() const { return true; }

		/** @brief Determines if the delegate references a member function. */
		bool IsMember() const { return true; }

      bool IsValid() const { return !isnull(mOwner) && !isnull(mFunction); }

      void SetOwner(unknown owner) const { mOwner = Cast<TOwner*>::From(owner); }

		/** @brief Invokes the function being referenced by the delegate. */
		void Call(TOwner* _this, TParams... params) const {
         if((isnull(_this) && isnull(mFunction)) || !IsValid()) {
            THROW(NullReferenceException());
			} else if(isnull(_this)) {
            _this = mOwner;
			}

         _this->*mFunction(params...);
		}

	protected:
		template<uword... I> void _Call(unknown _this, unknown* params, index_pack_t<I...>) const {
			Call(Cast<TOwner*>::From(_this), (Cast<TParams>::From(params[I]))...);
		}

      TOwner*    mOwner;
		TFunction* mFunction;
	};

	template<typename TOwner, typename TReturn, typename... TParams>
	class ConstMemberDelegate : public NonVoidDelegate<TReturn, TParams...> {
	public:
		/** @brief Native function signature. */
		typedef TReturn(TOwner::*TFunction)(TParams...) const;

		typedef ConstMemberDelegate<TOwner, TReturn, TParams...> TSelf;

		ConstMemberDelegate() : mOwner(0), mFunction(0) {
		}

      /** @brief Constructor. (TFunction). */
		ConstMemberDelegate(TFunction func) : mOwner(0), mFunction(func) {
		}

		ConstMemberDelegate(TOwner* owner, TFunction func): mOwner(owner), mFunction(func) {
		}

		ConstMemberDelegate(const TSelf& copy) : mOwner(copy.mOwner), mFunction(copy.mFunction) {
		}

		~ConstMemberDelegate() {
		}

		/** @brief Determines if the Delegate is equal-to another delegate. */
		virtual bool EqualTo(Delegate* rhs) const {
			if(!rhs->IsMember() || !rhs->IsNonVoid() || !rhs->IsConst()) {
				return false;
			}

			return ((TSelf*)rhs)->mFunction == mFunction ((TSelf*)rhs)->mOwner == mOwner;
		}

		/** @brief operator=(const Delegate* const). */
		TSelf& operator=(const TSelf& rhs) {
			if(this == &rhs) {
				return *this;
			}

         mOwner = rhs.mOwner;
			mFunction = rhs.mOwner;
			return *this;
		}

		unknown operator()(unknown _this, unknown* params) const {
			return Cast<TReturn>::To(_Call(_this, params, typename make_index_pack_t<sizeof...(TParams)>::type()));
		}

		bool IsConst() const { return true; }

		bool IsMember() const { return true; }

      bool IsValid() const { return !isnull(mOwner) && !isnull(mFunction); }

      void SetOwner(unknown owner) const { mOwner = Cast<TOwner*>::From(owner); }

		/** @brief Invokes the function being referenced by the delegate. */
		TReturn Call(TOwner* _this, TParams... params) const {
         if((isnull(_this) && isnull(mFunction)) || !IsValid()) {
            THROW(NullReferenceException());
			} else if(isnull(_this)) {
            _this = mOwner;
			}

         return _this->*mFunction(params...);
		}
	protected:
		template<uword... I>
		TReturn _Call(unknown _this, unknown* params, index_pack_t<I...>) const {
			return Call(Cast<TOwner*>::From(_this), (Cast<TParams>::From(params[I]))...);
		}

      TOwner*    mOwner;
		TFunction* mFunction;
	};
}
#endif
