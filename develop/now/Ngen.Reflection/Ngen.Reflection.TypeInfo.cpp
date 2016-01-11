
/*  _______    ________
    \      \  /  _____/  ____   ___
    /   |   \/   \  ____/ __ \ /   \
   /    |    \    \_\  \  ___/|   | \
   \____|__  /\______  /\___  >___| /
           \/        \/     \/    \/
The MIT License (MIT)

COPYRIGHT (C) 2016 NGENWARE STUDIOS, LLC

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
#ifndef NGEN_REFLECTION_TYPEINFO_CPP_INCLUDED
#define NGEN_REFLECTION_TYPEINFO_CPP_INCLUDED

#include "Ngen.Reflection.TypeInfo.hpp"
#include "Ngen.Reflection.MethodInfo.hpp"
#include "Ngen.Reflection.FieldInfo.hpp"
#include "Ngen.Reflection.NamespaceBuilder.hpp"

namespace Ngen {
   namespace Reflection {

         TypeBuilder::TypeBuilder(TypeInfo* type) : mInfo(type) {
            if(!mInfo->pIsMuted()) {
               THROW(InvalidOperationException("The given RTI is not mutable and can not be modified."));
            }
         }

			MethodInfo* TypeBuilder::AddStaticMethod(const mirror& relativeSignature, Delegate* function, typename StaticDelegate<MethodBuilder>::TFunction initializer) {
            NamespaceBuilder builder = NamespaceBuilder((NamespaceInfo*)this->mInfo);
            return builder.AddStaticMethod(relativeSignature, function, initializer);
			}

         FieldInfo* TypeBuilder::AddStaticField(const mirror& signature, Field* field, typename StaticDelegate<FieldBuilder>::TFunction initializer) {
            NamespaceBuilder builder = NamespaceBuilder((NamespaceInfo*)this->mInfo);
            return builder.AddStaticField(signature, field, initializer);
         }
         MethodInfo* TypeBuilder::AddMemberMethod(const mirror& relativeSignature, Delegate* function, typename StaticDelegate<MethodBuilder>::TFunction initializer) {
            if(this->mInfo->mMemberMethods.ContainsKey(relativeSignature)) {
               //THROW()
            }

            this->mInfo->mMemberMethods.Add(relativeSignature, MethodInfo());
            return this->mInfo->mMemberMethods[relativeSignature].Initialize((NamespaceInfo*)this->mInfo, relativeSignature, function, initializer);
         }
			FieldInfo* TypeBuilder::AddMemberField(const mirror& signature, Field* field, typename StaticDelegate<FieldBuilder>::TFunction initializer) {
			 if(this->mInfo->mMemberFields.ContainsKey(relativeSignature)) {
               //THROW()
            }

            this->mInfo->mMemberFields.Add(relativeSignature, FieldInfo());
            return this->mInfo->mMemberFields[relaitveSignature].Initialize((NamespaceInfo*)this->mInfo, signature, field, initializer);
			}
			MethodInfo* TypeBuilder::AddConstructor(const mirror& relativeSignature, Delegate* function, typename StaticDelegate<MethodBuilder>::TFunction initializer) {
            if(this->mInfo->mConstructors.ContainsKey(relativeSignature)) {
               //THROW()
            }

            this->mInfo->mConstructors.Add(relativeSignature, MethodInfo());
            return this->mInfo->mConstructors[relativeSignature].Initialize((NamespaceInfo*)this->mInfo, relativeSignature, function, initializer);
         }
			void TypeBuilder::AddParent(const mirror& parentName) {
            auto info = this->mInfo->mAssembly->GetType(parentName);
            info->mChildren.Add(this->mInfo->FullName(), this->mInfo);
            mInfo->mParents.Add(parentName, info);
			}
			void TypeBuilder::SetTrait(ETypeTrait trait, bool value) {
            this->mInfo->mTraits[trait] = value;
			}
			void TypeBuilder::SetTrait(TypeTraitFlags traits) {
            this->mInfo->mTraits = traits;
			}
			void TypeBuilder::SetDestructor(Delegate* function, typename StaticDelegate<MethodBuilder>::TFunction initializer) {
            mInfo->mDtor = MethodInfo((NamespaceInfo*)mInfo, const_text(""), function, initializer);
			}
         TypeInfo* TypeBuilder::AddNestedType(const mirror& relativeTypeName, typename StaticDelegate<TypeBuilder>::TFunction initializer) {
            if(this->mInfo->mNestedTypeMap.ContainsKey(relativeTypeName)) {
               //THROW()
            }

            auto copy = TypeInfo((NamespaceInfo*)this->mInfo, relativeTypeName, function, initializer);
            this->mInfo->mNestedTypeMap.Add(relativeTypeName, copy);
            return &this->mInfo->mNestedTypeMap[relativeTypeName];
         }

         /** @brief Validates the type information after it has been constructed. */
         bool Save() const { return true; }
   }
}

#endif // NGEN_REFLECTION_TYPEINFO_CPP_INCLUDED
