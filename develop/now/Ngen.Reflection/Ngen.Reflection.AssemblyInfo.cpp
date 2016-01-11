
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
#include "Ngen.Reflection.NamespaceInfo.hpp"
#include "Ngen.Reflection.TypeInfo.hpp"

namespace Ngen {
   typedef typename StaticDelegate<word>::TFunction* assembly_count_function;
   typedef typename StaticDelegate<Reflection::AssemblyInfo*, const mirror&>::TFunction* assembly_load_function;

   // the actual assembly storage
   Reflection::MirrorAssemblyInfoMap            pAssemblyMap = Reflection::MirrorAssemblyInfoMap();

   // referenced and loaded assemblies
   Reflection::MirrorAssemblyInfoPtrMap         pMirrorAssemblyPtrMap = Reflection::MirrorAssemblyInfoPtrMap();
   Map<Reflection::AssemblyInfo*, Reference*>   pAssemblyReferenceMap = Map<Reflection::AssemblyInfo*, Reference*>();
   Map<Reflection::AssemblyInfo*, Library*>     pAssemblyLibraryMap = Map<Reflection::AssemblyInfo*, Library*>();
   Map<Library*, uword>                         pLibraryAssemblyCount = Map<Library*, uword>();


   Type* Type::GetType(const mirror& typeName) {
      Type* result = null;
      Reflection::MirrorAssemblyInfoPtrMap::Node* begin = pMirrorAssemblyPtrMap.Begin();
      while(!isnull(begin)) {
         result = begin->Data().Value->GetType(typeName);
         if(!isnull(result)) {
            break;
         }

         begin = begin->Next();
      }

      return result;
   }
	Type* typeof(const mirror& typeName) {
	   return Type::GetType(typeName);
   }
   Object Object::New(unknown value, const mirror& typeName, bool readOnly) {
      return Object(value, typeof(typeName), readOnly);
   }

   word Assembly::Verify(const mirror& libraryFileName) {
      Library* lib = null;
      if(!Library::Load(libraryFileName, inref lib)) {
         //THROW();
      }

      auto assembly_count = (assembly_count_function)lib->Get(const_mirror(E"assembly_count"));
      word result = assembly_count();
      return result > 0;
   }

   Assembly* Assembly::Reference(const mirror& libraryFileName, const mirror& assemblyName) {
      Reflection::AssemblyInfo* result = null;
      Library* lib = null;
      if(!pMirrorAssemblyPtrMap.TryGetValue(assemblyName, inref result)) {
         if(!Library::Load(libraryFileName, inref lib)) {
            //THROW();
         }

         auto load_assembly = (assembly_load_function)lib->Get(const_mirror(E"assembly_load"));
         result = load_assembly(assemblyName);
         pMirrorAssemblyPtrMap.Add(assemblyName, result);
         pAssemblyLibraryMap.Add(result, lib);
         pAssemblyReferenceMap.Add(result, new Ngen::Reference());
         pLibraryAssemblyCount.Add(lib, 0);
      }

      pAssemblyReferenceMap[result]->Increment();
      pLibraryAssemblyCount[lib]++;
      return (Assembly*)result;
   }

   bool Assembly::Dereference(const mirror& assemblyName) {
      Reflection::AssemblyInfo* result = null;
      if(!pMirrorAssemblyPtrMap.TryGetValue(assemblyName, inref result)) {
         return true;
      }

      Library* lib = pAssemblyLibraryMap[result];
      auto refc = pAssemblyReferenceMap[result];
      if(refc->Decrement().Current() == 0) {
         delete refc;

         // remove all map bindings and references
         pAssemblyLibraryMap.Remove(result);
         pMirrorAssemblyPtrMap.Remove(assemblyName);
         pAssemblyReferenceMap.Remove(result);
         pAssemblyMap.Remove(assemblyName);

         // unload assembly library if no other assemblies are loaded
         pLibraryAssemblyCount[lib]--;
         if(pLibraryAssemblyCount[lib] == 0) {
            Library::Unload(lib->Path());
            pLibraryAssemblyCount.Remove(lib);
         }

         return true;
      }

      return false;
   }
}

namespace Ngen {
   namespace Reflection {
      AssemblyInfo::AssemblyInfo() : mIsMuted(true), mLibrary(null), mAssemblyName(), mRootNamespaceMap(), mNamespaceInfoMap(), mCustomAttributes() {
      }

      AssemblyInfo* AssemblyInfo::New(const mirror& library, const mirror& assemblyName,  typename VoidStaticDelegate<AssemblyBuilder>::TFunction initialize) {
         pAssemblyMap.Add(assemblyName, AssemblyInfo());
         auto result = &pAssemblyMap[assemblyName];
         result->pMute();
         Library::Load(library, inref result->mLibrary); // this may conflict during generation of RTI
         result->mAssemblyName = assemblyName;
         initialize(AssemblyBuilder(result));
         result->pUnmute();
         return result;
      }

      Array<Type*> AssemblyInfo::GetNamespaces() const {
         return this->mNamespaceInfoMap.Values().AsType<Type*>();
      }

      Array<Type*> AssemblyInfo::GetTypes() const {
         return this->mTypeInfoMap.Values().AsType<Type*>();
      }

      Array<Attribute*> AssemblyInfo::GetAttributes() const {
         return this->mCustomAttributes.ToPointerArray();
      }

      Type* AssemblyInfo::GetNamespace(const mirror& name) const {
         if(!this->mNamespaceInfoMap.ContainsKey(name)) {
            return null;
         }

         return (Type*)this->mNamespaceInfoMap[name];
      }

      Type* AssemblyInfo::GetType(const mirror& name) const {
         if(!this->mTypeInfoMap.ContainsKey(name)) {
            return null;
         }

         return (Type*)this->mTypeInfoMap[name];
      }

      Library* AssemblyInfo::GetNativeLibrary() const {
         return this->mLibrary;
      }

      AssemblyBuilder::AssemblyBuilder(AssemblyInfo* info) : mInfo(info) {
         if(!mInfo->mIsMuted) {
            THROW(InvalidOperationException("The assembly being constructed is read-only and cannot be modified."));
         }
      }

      AssemblyInfo* AssemblyBuilder::Finalize() {
         return mInfo;
      }

      AssemblyBuilder& AssemblyBuilder::AddNamespace(const mirror& namespaceName, NamespaceInfo* directory, const VoidStaticDelegate<NamespaceBuilder>::TFunction initalizer) {
         mirror fullName = (isnull(directory) ? namespaceName.ToLongName() :
                            directory->FullName().ToLongName() + ':' + namespaceName.ToLongName());
         mInfo->mRootNamespaceMap.Add(fullName, NamespaceInfo());
         mInfo->mRootNamespaceMap[fullName].Initialize(this->mInfo, directory, namespaceName, fullName, initalizer);
         return *this;
      }
   }
}
