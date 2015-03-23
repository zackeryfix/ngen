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
#ifndef __NGEN_OBJECT_HPP
#define __NGEN_OBJECT_HPP

#include "Ngen.Mirror.hpp"
#include "Ngen.Reference.hpp"

namespace Ngen {
	class Delegate;
	class Type;

	class ngen_api Object {
	public:

		Object() : mThis(null), mReference(null), mIsReadonly(true), mType(0) {}

		Object(unknown _this, bool readOnly = true) : mThis(_this), mReference(0), mIsReadonly(readOnly), mType(0) {
			pInitialize();
		}

		Object(unknown _this, Type* type, bool readOnly = true) : mThis(_this), mReference(0), mIsReadonly(readOnly), mType(type) {
			pInitialize();
		}

		Object(const Object& copy) : mThis(copy.mThis), mReference(copy.mReference), mIsReadonly(copy.mIsReadonly), mType(copy.mType) {
			pInitialize();
		}

		Object(const Object& copy, bool readOnly) : mThis(copy.mThis), mReference(copy.mReference), mIsReadonly(readOnly), mType(copy.mType) {
			pInitialize();
		}

		Object(Object&& move) : mThis(move.mThis), mReference(move.mReference), mIsReadonly(move.mIsReadonly), mType(move.mType) {
			if(!mIsReadonly) {
				move.mThis = null;
				move.mReference = null;
				move.mIsReadonly = true;
			}
		}

		~Object() {
			pClear(true);
		}

		bool operator==(const Object& rhs) const {
			if(this == &rhs || this->mThis == rhs.mThis) {
				return true;
			}

			return false;
		}

		Object& operator=(const Object& rhs) {
			if(this == &rhs) {
				return *this;
			}

			pClear(true);
			pSet(rhs.mThis, rhs.mType, rhs.mReference, rhs.mIsReadonly);

			return *this;
		}

		Object& operator=(Object&& rhs) {
			if(this == &rhs) {
				return *this;
			}

			pClear(true);

			mThis = rhs.mThis;
			mReference = rhs.mReference;
			mIsReadonly = rhs.mIsReadonly;

			if(!mIsReadonly) {
				rhs.mThis = null;
				rhs.mReference = null;
				rhs.mIsReadonly = true;
				mReference->Increment();
			}

			return *this;
		}

		bool IsNull() const {
			return isnull(mThis) || this == &Null() || this->operator==(Null());
		}

		Object As(Type* type) const {
			return Object(mThis, type);
		}

		template<typename T> T* Cast() const {
			return (T*)mThis;
		}

		unknown This() const {
			return mThis;
		}

		bool IsReadonly() const {
			return mIsReadonly;
		}

		const Reference* GetReference() const {
			return mReference;
		}

		Type* GetType() const {
			return mType;
		}

		template<typename T>
		static Object New(T* value, bool readOnly = false) {
			return Object((unknown)value, readOnly);
		}

		static const Object& Null();
		static Object New(unknown value, const text& type, bool readOnly = false);
		static Object New(unknown value, bool readOnly = false);

	protected:
		void pInitialize();
		void pSet(unknown _this, Type* type, Reference* reference, bool readOnly);
		void pThrowIfReadonly() const;
		void pClear(bool ignoreReadonlyError);
		bool pIsTypeInstace() const {
			return !isnull(mType);
		}

		unknown mThis;
		Reference* mReference;
		bool mIsReadonly;
		Type* mType;

		friend class Type;
	};

	typedef Object object;

#  define const_object(value) object::New(value, true)
#  define copy_object(value) object::New(value, false)

}

#endif // __NGEN_OBJECT_HPP
