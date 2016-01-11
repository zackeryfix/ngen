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
#ifndef __NGEN_REFLECTION_PARAMETERINFO_HPP
#define __NGEN_REFLECTION_PARAMETERINFO_HPP

#include "Ngen.Reflection.EParameterTrait.hpp"

namespace Ngen {
   namespace Reflection {
      class ngen_api ParameterInfo {
      public:
         ParameterInfo() : mTraits(), mName(), mIndex(),  mOwner(null), mType(null), mTypeName() {}

         ParameterInfo(MethodInfo* owner, ParameterTraitFlags flags, const mirror& typeName, const mirror& paramName, uword paramIndex);

         ParameterInfo(const ParameterInfo& copy) : mTraits(copy.mTraits), mName(copy.mName), mIndex(copy.mIndex),  mOwner(copy.mOwner), mType(copy.mType), mTypeName(copy.mTypeName) {
         }

         mirror Name() const { return mName; }

         MethodInfo* Owner() const { return mOwner; }

         TypeInfo* Type() const { return mType; }

         bool IsObject() const { return mTraits[EParameterTrait::Object]; }
         bool IsConst() const { return mTraits[EParameterTrait::Const]; }
         bool IsValue() const { return mTraits[EParameterTrait::Value]; }
         bool IsReference() const { return mTraits[EParameterTrait::Reference]; }
         bool IsPointer() const { return mTraits[EParameterTrait::Pointer]; }
         bool IsDelegate() const { return mTraits[EParameterTrait::Delegate]; }
         bool IsArray() const { return mTraits[EParameterTrait::Array]; }

      protected:
         ParameterTraitFlags  mTraits;
         mirror               mName;
         uword                mIndex;
         MethodInfo*          mOwner;
         TypeInfo*            mType;
         mirror               mTypeName;

         friend class MethodBuilder;
         friend class MethodInfo;
      };
   }
}

#endif // __NGEN_REFLECTION_PARAMETERINFO_HPP
