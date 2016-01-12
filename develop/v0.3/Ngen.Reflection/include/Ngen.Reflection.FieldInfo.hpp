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
#ifndef __NGEN_REFLECTION_FIELDINFO_HPP
#define __NGEN_REFLECTION_FIELDINFO_HPP

#include "Ngen.Reflection.FieldBuilder.hpp"

namespace Ngen {
   namespace Reflection {
      class ngen_api FieldInfo : Field {
      public:
         FieldInfo() : mIsMuted(false), mTraits(), mDirectory(null), mReturnType(null), mName(), mFullName(null), mField(null) {
         }

         virtual uword Size() const { return mField->Size(); }

         virtual unknown Get(unknown _this) const { return mField->Get(_this); }

         virtual void Set(unknown _this, unknown value) const {
            if(mField->IsConst() || IsReadonly()) {
               THROW(InvalidOperationException(E"Unable to modify a readonly/const data field."));
            }

            mField->Set(_this, value);
         }

         mirror Name() const { return mName; }

         mirror FullName() const { return mFullName; }

         Type* ReturnType() const { return (Type*)mReturnType; }

         TypeInfo* ReturnTypeInfo() const { return mReturnType; }

         NamespaceInfo* Directory() const { return mDirectory; }

         bool IsPublic() const { return mTraits[EFieldTrait::Public]; }
         bool IsProtected() const { return mTraits[EFieldTrait::Protected]; }
         bool IsPrivate() const { return mTraits[EFieldTrait::Private]; }
         bool IsStatic() const { return mTraits[EFieldTrait::Static]; }
         bool IsReadonly() const { return mTraits[EFieldTrait::Readonly]; }
         bool IsHidden() const { return mTraits[EFieldTrait::Hidden]; }
         virtual bool IsConst() const { return mField->IsConst(); }
         virtual bool IsMember() const { return mField->IsMember(); }

         FieldInfo* Initialize(NamespaceInfo* directory,  Field* field, const mirror& relativeName, typename VoidStaticDelegate<FieldBuilder>::TFunction initializer);
      protected:
         void pMute() { mIsMuted = true; }
         void pUnmute() { mIsMuted = false; }
         bool pIsMuted() { return mIsMuted; }

         bool              mIsMuted;
         FieldTraitFlags   mTraits;
         NamespaceInfo*    mDirectory;
         TypeInfo*         mReturnType;
         mirror            mName;
         mirror            mFullName;
         Field*            mField;
         Array<Attribute>  mCustomAttributes;          // all the custom attributes found inside the assembly

         friend class FieldBuilder;
      };
   }
}

#endif // __NGEN_ECONSTRUCTORKIND_HPP
