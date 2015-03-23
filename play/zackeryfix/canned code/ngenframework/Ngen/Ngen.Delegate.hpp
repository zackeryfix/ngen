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
#ifndef __NGEN_DELEGATE_HPP
#define __NGEN_DELEGATE_HPP

#include "Ngen.Typedefs.hpp"
#include "Ngen.Cast.hpp"

namespace Ngen {
	class Mirror;

	/** @brief A data structure that represents the reference to a function.
	*/
   class ngen_api Delegate {
   public:
		/** @brief De-constructor. */
      virtual ~Delegate() {}

		/** @brief Determines if the Delegate is equal-to another delegate. */
      virtual bool EqualTo(Delegate* rhs) const pure;

		/** @brief operator()(unknown, unknown*). */
      virtual unknown operator()(unknown _this, unknown* params) pure;

		/** @brief Determines if the delegate references a constant-member function. */
      virtual bool IsConst() const pure;

		/** @brief Determines if the delegate references a member function. */
      virtual bool IsMember() const pure;

		/** @brief Determines if the delegate references a non-void function. */
      virtual bool IsNonVoid() const pure;

		/** @brief Gets the number parameters that are needed for a valid invocation of the delegate. */
		virtual uword Length() const pure;

		/** @brief Invokes the function being referenced by the delegate. */
      template<typename TOwner, typename TReturn, typename... TParams>
      TReturn Call(TOwner* _this, TParams... params) {
      	unknown ret = 0;
			unknown args[sizeof...(TParams)] {
				(Cast<TParams>::To(params))...
			};

      	if(this->IsNonVoid()) {
				ret = this->operator()(Cast<TOwner*>::To(_this), args);
      	} else {
				this->operator()(Cast<TOwner*>::To(_this), args);
      	}

			return Cast<TReturn>::From(ret);
		}

		/** @brief Gets the mirror that identifies the return type of the function call. */
		virtual const char8* ReturnTypename() const pure;

		/** @brief Gets the size (in bytes) for the return type of the function call. */
		virtual uword ReturnSize() const pure;
   };

   template<typename TReturn, typename... TParams>
   class ngen_api NonVoidDelegate : public Delegate {
   public:
      virtual ~NonVoidDelegate() {}
      virtual TReturn Call(TParams... params) pure;
      bool IsNonVoid() const { return true; };

      const char8* ReturnTypename() const { return typenameof(TReturn); }
      uword ReturnSize() const { return sizeof(TReturn); }
   };

   template<typename... TParams>
   class ngen_api VoidDelegate : public Delegate {
   public:
      virtual ~VoidDelegate() {}
      virtual void Call(TParams... params) pure;
      bool IsNonVoid() const { return false; };

      const char8* ReturnTypename() const { return null; }
      uword ReturnSize() const { return 0; }
   };
}

#endif // __NGEN_DELEGATE_HPP
