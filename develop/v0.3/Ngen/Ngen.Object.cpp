/*  _______    ________
    \      \  /  _____/  ____   ___
    /   |   \/   \  ____/ __ \ /   \
   /    |    \    \_\  \  ___/|   | \
   \____|__  /\______  /\___  >___| /
           \/        \/     \/    \/
The MIT License (MIT)

COPYRIGHT (C) 2014 NGENWARE

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
#include "Ngen.Object.hpp"
#include "Ngen.Type.hpp"

namespace Ngen {
	Object __nullObject = Object();

	const Object& Object::Null() {
		return __nullObject;
	}


   Object Object::New(unknown value, Type* type, bool readOnly) {
      return Object(value, type, readOnly);
   }

   Object Object::New(unknown value, bool readOnly) {
      return Object(value, readOnly);
   }

	void Object::pInitialize() {
		if(!mIsReadonly) {
			int8* tmp = (int8*)mThis;
			mThis = (unknown)memory::New<int8>(mType->Size());

			Memory::Copy<int8>((int8*)mThis, tmp, mType->Size());

			mReference = new Reference();
			mReference->Increment();
		}
	}

	void Object::pSet(unknown _this, Type* type, Reference* reference, bool readOnly) {
		mThis = _this;
		mType = type;
		mIsReadonly = readOnly;
		mReference = reference;

		this->pInitialize();
	}

	void Object::pThrowIfReadonly() const {
		if(IsReadonly()) {
			THROW(InvalidOperationException(E"Cannot modify a read-only object!"));
		}
	}

	void Object::pClear(bool ignoreReadonlyError) {
		if(!ignoreReadonlyError) {
			pThrowIfReadonly();
		}

		if(!mIsReadonly) {
			if(mReference->IsValid()) {
				mReference->Decrement();
				if(mReference->Current() <= 0) {
					delete mReference;
					mReference = null;

					if(pIsTypeInstace()) {
						mType->DestroyInstance(mThis);
					} else {
						memory::Delete<byte>((byte*)mThis);
					}

					mThis = null;
					mType = null;
					mIsReadonly = true;
				}
			}
		}
	}

	uword Object::Size() const {
		return mType->Size();
	}

	Type* typeof(Object& variable) { return (Type*)variable.GetType(); }
}
