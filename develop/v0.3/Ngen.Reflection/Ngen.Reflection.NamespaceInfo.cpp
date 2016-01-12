
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

#include "Ngen.Reflection.AssemblyInfo.hpp"
#include "Ngen.Reflection.TypeInfo.hpp"
#include "Ngen.Reflection.NamespaceInfo.hpp"

namespace Ngen {
   namespace Reflection {
         Array<Type*> NamespaceInfo::GetNestedTypes() const {
            return this->mNestedTypeMap.ToPointerMap().Values().AsType<Type*>();
			}

         NamespaceInfo* NamespaceInfo::Initialize(AssemblyInfo* assembly, NamespaceInfo* directory, const mirror& relativeName, VoidStaticDelegate<NamespaceBuilder>::TFunction initalizer) {
            this->pMute();
            this->mName = relativeName;
            this->mFullName = directory->FullName().ToLongName() + ':' + relativeName.ToLongName();
            this->mAssembly = assembly;
            this->mAssembly->mNamespaceInfoMap.Add(mFullName, this);
            this->mDirectory = directory;
				initalizer(NamespaceBuilder(this));
				this->pUnmute();
				return this;
			}

         NamespaceBuilder::NamespaceBuilder(NamespaceInfo* info) : mInfo(info) {
            if(!mInfo->pIsMuted()) {
               THROW(InvalidOperationException("The given RTI is not mutable and can not be modified."));
            }
         }

			MethodInfo* NamespaceBuilder::AddStaticMethod(const mirror& relativeSignature, Delegate* function, typename VoidStaticDelegate<MethodBuilder>::TFunction initializer) {
            if(this->mInfo->mStaticMethodMap.ContainsKey(relativeSignature)) {
               //THROW()
            }

            this->mInfo->mStaticMethodMap.Add(relativeSignature, MethodInfo());
            return this->mInfo->mStaticMethodMap[relativeSignature].Initialize(this->mInfo, relativeSignature, function, initializer);
			}

         FieldInfo* NamespaceBuilder::AddStaticField(const mirror& signature, Field* field, typename VoidStaticDelegate<FieldBuilder>::TFunction initializer) {
            if(this->mInfo->mStaticFieldMap.ContainsKey(signature)) {
               //THROW()
            }

            this->mInfo->mStaticFieldMap.Add(signature, FieldInfo());
            return this->mInfo->mStaticFieldMap[signature].Initialize(this->mInfo, field, signature, initializer);
			}

         TypeInfo* NamespaceBuilder::AddNestedType(const mirror& relativeTypeName, uword typeSize, typename VoidStaticDelegate<TypeBuilder>::TFunction initializer) {
            if(this->mInfo->mNestedTypeMap.ContainsKey(relativeTypeName)) {
               //THROW()
            }

            this->mInfo->mNestedTypeMap.Add(relativeTypeName, TypeInfo());
            return this->mInfo->mNestedTypeMap[relativeTypeName].Initialize(this->mInfo, relativeTypeName, typeSize, initializer);
			}

         NamespaceInfo* NamespaceBuilder::AddNestedNamespace(const mirror& relativeNamespaceName, typename VoidStaticDelegate<NamespaceBuilder>::TFunction initializer) {
            if(this->mInfo->mNestedNamespaceMap.ContainsKey(relativeNamespaceName)) {
               //THROW()
            }

            this->mInfo->mNestedNamespaceMap.Add(relativeNamespaceName, TypeInfo());
            return this->mInfo->mNestedNamespaceMap[relativeNamespaceName].Initialize(this->mInfo->mAssembly, this->mInfo, relativeNamespaceName, initializer);
			}
   }
}
