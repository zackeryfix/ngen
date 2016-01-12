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
#ifndef __NGEN_FIELD_HPP
#define __NGEN_FIELD_HPP

#include "Ngen.Cast.hpp"

namespace Ngen {
	/** @brief Represents a static or member field. */
	class ngen_api Field {
	public:
		virtual ~Field() {}

		/** @brief Gets the value of the field. */
		virtual unknown Get(unknown _this = 0) const pure;

		/** @brief Sets the value of the field. */
		virtual void Set(unknown _this, unknown value) const pure;

		/** @brief Gets the size of the field (in bytes).
		 */
		virtual uword Size() const pure;

		virtual bool IsConst() const pure;
		virtual bool IsMember() const pure;

		/** @brief Gets the type that identifies the data belonging to the field. */
		virtual Type* ReturnType() const pure;

		template<typename TOwner, typename TValue> TValue Get(TOwner* _this) {
			return (TValue)Get((unknown)_this);
		}

		template<typename TOwner, typename TValue> void Set(TOwner* _this, TValue value) {
			Set((unknown)_this, (unknown)&value);
		}
	};

	template<typename TOwner, typename TValue>
	class ngen_api MemberField : public Field {
	public:

		typedef TValue TOwner::*TField;
		typedef MemberField<TOwner, TValue> TSelf;

		MemberField(TField field) : mField(field) {
		}

		virtual bool IsConst() const {
			return false;
		}

		virtual bool IsMember() const {
			return true;
		}

		virtual uword Size() const {
         return sizeof(TValue);
		}

		virtual TValue Get(unknown _this) {
			return Cast<TOwner*>::From(_this)->mField;
		}

		virtual void Set(unknown _this, unknown value) {
		  Cast<TOwner*>::From(_this)->mField = Cast<TValue>::From(value);
		}

      virtual Type* ReturnType() const {
         return typeof<TValue>();
      }

	protected:
		TField mField;
	};

	template<typename TOwner, typename TValue>
	class ngen_api ConstMemberField : public Field {
	public:

		typedef const TValue TOwner::*TField;
		typedef ConstMemberField<TOwner, TValue> TSelf;

		ConstMemberField(TField field) : mField(field) {
		}

		virtual bool IsConst() const {
			return true;
		}

		virtual bool IsMember() const {
			return true;
		}

      virtual uword Size() const {
         return sizeof(TValue);
		}

		virtual TValue Get(unknown _this) {
			return Cast<TOwner*>::From(_this)->mField;
		}

		virtual void Set(unknown _this, unknown value) {
		  THROW(InvalidOperationException(E"Unable to modify a readonly/const data field."));
		}

      virtual Type* ReturnType() const {
         return typeof<TValue>();
      }
	protected:
		TField mField;
	};

	template<typename TValue>
	class ngen_api ConstStaticField : public Field {
	public:

		typedef const TValue* TField;
		typedef ConstStaticField<TValue> TSelf;

		ConstStaticField(TField field) : mField(field) {
		}

		virtual bool IsConst() const {
			return true;
		}

		virtual bool IsMember() const {
			return false;
		}

      virtual uword Size() const {
         return sizeof(TValue);
		}

		virtual TValue Get(unknown _this) {
			return *mField;
		}

		virtual void Set(unknown _this, unknown value) {
		  THROW(InvalidOperationException(E"Unable to modify a readonly/const data field."));
		}

      virtual Type* ReturnType() const {
         return typeof<TValue>();
      }
	protected:
		TField mField;
	};

	template<typename TValue>
	class ngen_api StaticField : public Field {
	public:

		typedef TValue* TField;
		typedef StaticField<TValue> TSelf;

		StaticField(TField field) : mField(field) {
		}

		virtual bool IsConst() const {
			return false;
		}

		virtual bool IsMember() const {
			return false;
		}

      virtual uword Size() const {
         return sizeof(TValue);
		}

		virtual unknown Get(unknown _this) {
			return (unknown)mField;
		}

		virtual void Set(unknown _this, unknown value) {
		  *mField = *(TValue*)value;
		}

      virtual Type* ReturnType() const {
         return typeof<TValue>();
      }
	protected:
		TField mField;
	};
}
#endif // __NGEN_FIELD_HPP
