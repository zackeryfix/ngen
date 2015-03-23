/*  _______    ________
    \      \  /  _____/  ____   ___
    /   |   \/   \  ____/ __ \ /   \
   /    |    \    \_\  \  ___/|   | \
   \____|__  /\______  /\___  >___| /
           \/        \/     \/    \/
The MIT License (MIT)

COPYRIGHT (C) 2014 NGENWARE STUDIOS

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

#ifndef __NGEN_REFLECTION_ATTRIBUTEINFO_HPP
#define __NGEN_REFLECTION_ATTRIBUTEINFO_HPP

#include "Ngen.Attribute.hpp"
#include "Ngen.Reflection.TypeInfo.hpp"

namespace Ngen {
	namespace Reflection {
	   class TypeInfo;
	   class MethodInfo;
	   class ParameterInfo;
	   class NamespaceInfo;
	   class AssemblyInfo;

      /** @brief An attribute is a custom property that can be assigned to any code element, such as
       * a type definition or method argument.
       */
      class ngen_api AttributeInfo : public virtual Attribute {
      public:
         /** @brief
          */
         template<typename TReflection>
         AttributeInfo(AttributeBindingFlags bindingFlags, TypeInfo* customType, TReflection* rtiTarget) : Attribute(bindingFlags, customType), mTarget((unknown)rti) {
            mData = customType->
         }

         /** @brief
          */
         AttributeInfo(const AttributeInfo& copy) : mType(copy.mType), mConstraints(copy.mConstraints), mData(copy.mData), mTarget(copy.mTarget) {}

         /** @brief
          */
         bool Attribute::Equals(Attribute* rhs) const {
            AttributeInfo* rhsp = (AttributeInfo*)rhs;
            return rhsp->mType == this->mType &&
                   rhsp->mTarget == this->mTarget &&
                   rhsp->mConstraints == this->mConstraints &&
                   rhsp->mData == this->mData;
         }

         /** @brief Gets the custom attributes type information.
          */
         Type* Attribute::CustomAttribute() const {
            return (Type*)this->mType;
         }

         /** @brief Gets the custom attributes type information.
          */
         TypeInfo* Attribute::CustomAttributeInfo() const {
            return mType;
         }


         /** @brief Gets the target reflected
          */
         unknown Attribute::Target() const {
            return mTarget;
         }

         /** @brief
          */
         Object& Attribute::CustomData() const {
            return mData;
         }


      protected:
         TypeInfo* mType;
         AttributeBindingFlags mConstraints;
         Object mData;
         unknown mTarget;
      };
	}
}

#endif // __NGEN_REFLECTION_ELABELPART_HPP
