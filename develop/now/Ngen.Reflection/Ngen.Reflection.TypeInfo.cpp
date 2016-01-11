
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
#include "Ngen.Reflection.AssemblyInfo.hpp"

namespace Ngen {
   namespace Reflection {
         TypeInfo* TypeInfo::Initialize(NamespaceInfo* directory, const mirror& typeName, uword size, typename VoidStaticDelegate<TypeBuilder>::TFunction initializer) {
				this->pMute();
				this->mName = typeName;
            this->mFullName = (directory->FullName().ToLongName() + E'@' + typeName.ToLongName());
            this->mAssembly = directory->GetAssemblyInfo();
            this->mAssembly->mTypeInfoMap.Add(mFullName, this);
            this->mDirectory = directory;
            this->mSize = size;
				initializer(TypeBuilder(this));
				this->pUnmute();
				return this;
			}

         TypeBuilder::TypeBuilder(TypeInfo* type) : mInfo(type) {
            if(!mInfo->pIsMuted()) {
               THROW(InvalidOperationException("The given RTI is not mutable and can not be modified."));
            }
         }

			MethodInfo* TypeBuilder::AddStaticMethod(const mirror& relativeSignature, Delegate* function, typename VoidStaticDelegate<MethodBuilder>::TFunction initializer) {
            NamespaceBuilder builder = NamespaceBuilder((NamespaceInfo*)this->mInfo);
            return builder.AddStaticMethod(relativeSignature, function, initializer);
			}

         FieldInfo* TypeBuilder::AddStaticField(const mirror& signature, Field* field, typename VoidStaticDelegate<FieldBuilder>::TFunction initializer) {
            NamespaceBuilder builder = NamespaceBuilder((NamespaceInfo*)this->mInfo);
            return builder.AddStaticField(signature, field, initializer);
         }
         MethodInfo* TypeBuilder::AddMemberMethod(const mirror& relativeSignature, Delegate* function, typename VoidStaticDelegate<MethodBuilder>::TFunction initializer) {
            if(this->mInfo->mMemberMethods.ContainsKey(relativeSignature)) {
               //THROW()
            }

            this->mInfo->mMemberMethods.Add(relativeSignature, MethodInfo());
            return this->mInfo->mMemberMethods[relativeSignature].Initialize((NamespaceInfo*)this->mInfo, relativeSignature, function, initializer);
         }

			FieldInfo* TypeBuilder::AddMemberField(const mirror& relativeSignature, Field* field, typename VoidStaticDelegate<FieldBuilder>::TFunction initializer) {
			 if(this->mInfo->mMemberFields.ContainsKey(relativeSignature)) {
               //THROW()
            }

            this->mInfo->mMemberFields.Add(relativeSignature, FieldInfo());
            return this->mInfo->mMemberFields[relativeSignature].Initialize((NamespaceInfo*)this->mInfo, field, relativeSignature, initializer);
			}

			MethodInfo* TypeBuilder::AddConstructor(const mirror& relativeSignature, Delegate* function, typename VoidStaticDelegate<MethodBuilder>::TFunction initializer) {
            if(this->mInfo->mConstructors.ContainsKey(relativeSignature)) {
               //THROW()
            }

            this->mInfo->mConstructors.Add(relativeSignature, MethodInfo());
            return this->mInfo->mConstructors[relativeSignature].Initialize((NamespaceInfo*)this->mInfo, relativeSignature, function, initializer);
         }
			void TypeBuilder::AddParent(const mirror& parentName) {
            auto parent = (TypeInfo*)this->mInfo->mAssembly->GetType(parentName);
            parent->mChildren.Add(this->mInfo->FullName(), this->mInfo);
            mInfo->mParents.Add(parentName, parent);
			}
			void TypeBuilder::SetTrait(ETypeTrait trait, bool value) {
            this->mInfo->mTraits.Set(trait, value);
			}
			void TypeBuilder::SetTrait(TypeTraitFlags traits) {
            this->mInfo->mTraits = traits;
			}
			void TypeBuilder::SetDestructor(Delegate* function, typename VoidStaticDelegate<MethodBuilder>::TFunction initializer) {
            mInfo->mDeconstructor.Initialize((NamespaceInfo*)mInfo, const_mirror(E""), function, initializer);
			}

         TypeInfo* TypeBuilder::AddNestedType(const mirror& relativeTypeName, uword typeSize, typename VoidStaticDelegate<TypeBuilder>::TFunction initializer) {
            if(this->mInfo->mNestedTypeMap.ContainsKey(relativeTypeName)) {
               //THROW()
            }

            this->mInfo->mNestedTypeMap.Add(relativeTypeName, TypeInfo());
            return this->mInfo->mNestedTypeMap[relativeTypeName].Initialize((NamespaceInfo*)this->mInfo, relativeTypeName, typeSize, initializer);
         }
   }
}

#endif // NGEN_REFLECTION_TYPEINFO_CPP_INCLUDED
