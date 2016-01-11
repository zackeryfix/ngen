
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
#include "Ngen.Reflection.TypeInfo.hpp"
#include "Ngen.Reflection.MethodInfo.hpp"
#include "Ngen.Reflection.FieldInfo.hpp"
#include "Ngen.Reflection.NamespaceBuilder.hpp"

namespace Ngen {
   typedef typename StaticDelegate<word>::TFunction assembly_count_function;
   typedef typename StaticDelegate<Reflection::AssemblyInfo*, const mirror& assemblyName>::TFunction assembly_load_function;

   // the actual assembly storage
   Map<Mirror, Reflection::AssemblyInfo>                    pAssemblyMap = Map<Mirror, Reflection::AssemblyInfo>();

   // referenced and loaded assemblies
   Map<Mirror, Reflection::AssemblyInfo*>                   pMirrorAssemblyInfoMap = Map<Mirror, Reflection::AssemblyInfo*>();
   Map<Reflection::AssemblyInfo*, Reference*>               pAssemblyReferenceMap = Map<Reflection::AssemblyInfo*, Reference*>();
   Map<Reflection::AssemblyInfo*, Library*>                 pAssemblyLibraryMap = Map<Reflection::AssemblyInfo*, Library*>();
   Map<Library*, uword> pLibraryAssemblyCount = Map<Library*, uword>();

   ////////////////////////
   // Ngen.Assembly implementation (requires Ngen::Reflection)
   ////////////////////////////////////////////////////////////
   word Assebly::Verify(const mirror& libraryFileName) {
      Library* lib = null;
      if(!Library::Load(libraryFileName, inref lib)) {
         //THROW();
      }

      auto assembly_count = (assembly_count_function)lib->Get(const_mirror(E"assembly_count"));
      word result = assembly_count();
      return result > 0;
   }

   Assembly* Assembly::Reference(const mirror& libraryFileName, const mirror& assemblyName) {
      AssemblyInfo* result = null;
      Library* lib = null;
      if(!pMirrorAssemblyInfoMap.TryGetValue(assemblyName, inref result)) {
         if(!Library::Load(libraryFileName, inref lib)) {
            //THROW();
         }

         auto load_assembly = (assembly_load_function)lib->Get(const_mirror(E"load_assembly"));
         result = load_assembly(assemblyName);
         pMirrorAssemblyInfoMap.Add(assemblyName, result);
         pAssemblyLibraryMap.Add(result, lib);
         pAssemblyReferenceMap.Add(result, new Ngen::Reference());
         pLibraryAssemblyCount.Add(lib, 0);
      }

      pAssemblyReferenceMap[result]->Increment();
      pLibraryAssemblyCount[lib]++;
      return (Assembly*)result;
   }

   bool Assembly::Dereference(const mirror& assemblyName) {
      AssemblyInfo* result = null;
      if(!pMirrorAssemblyInfoMap.TryGetValue(assemblyName, inref result)) {
         return true;
      }

      Library* lib = pAssemblyLibraryMap[result];
      Reference* counter = pAssemblyReferenceMap[assemblyName];
      if(counter->Decrement().Current() == 0) {
         delete counter;

         // remove all map bindings and references
         pAssemblyLibraryMap.Remove(result);
         pMirrorAssemblyInfoMap.Remove(assemblyName);
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

   namespace Reflection {
      AssemblyInfo::AssemblyInfo() : mIsMuted(true), mLibrary(null), mAssemblyName(), mNamespaceMap(), mCustomAttributes() {
      }

      AssemblyInfo* AssemblyInfo::New(Library* library, const mirror& assemblyName,  typename VoidStaticDelegate<AssemblyBuilder>::TFunction initialize) {
         pAssemblyMap.Add(assemblyName, AssemblyInfo());
         auto result = &pAssemblyMap[assemblyName];
         result->pMute();
         result->mLibrary(library);
         result->mAssemblyName(assemblyName);
         result->mNamespaceMap();
         result->mTypeInfoMap();
         result->mCustomAttributes();
         initialize(AssemblyBuilder(result));
         result->pUnmute();
      }

      Array<Type*> AssemblyInfo::GetNamespaces() const {
         return this->mNamespaceMap.Values().AsType<Type*>();
      }

      Array<Type*> AssemblyInfo::GetTypes() const {
         return this->mTypeInfoMap.Values().AsType<Type*>();
      }

      Array<Attribute*> AssemblyInfo::GetAssemblyAttributes() const {
         return this->mCustomAttributes().ToPointerArray();
      }

      Type* AssemblyInfo::GetNamespace(const mirror& name) const {
         if(!this->mNamespaceMap.ContainsKey(name)) {
            THROW();
         }

         return (Type*)this->mNamespaceMap[name];
      }

      Type* AssemblyInfo::GetType(const mirror& name) const {
         if(!this->mTypeInfoMap.ContainsKey(name)) {
            THROW();
         }

         return (Type*)this->mTypeInfoMap[name];
      }

      AssemblyBuilder::AssemblyBuilder(AssemblyInfo* info) : mInfo(info) {
         if(!mInfo->mIsMuted) {
            THROW(InvalidOperationException("The assembly being constructed is read-only and cannot be modified."));
         }
      }

      AssmeblyInfo* AssemblyBuilder::Finalize() {
         return mInfo;
      }

      NamespaceInfo* AssemblyBuilder::AddNamespace(const mirror& namespaceName, NamespaceInfo* directory, const VoidStaticDelegate<NamespaceBuilder>::TFunction initalizer) {
         mirror fullName = (isnull(directory) ? mInfo->FullName() + ':' + relativeName.ToLongName() :
                                                mInfo->FullName() + ':' + directory->FullName()) + ':' + relativeName.ToLongName());
         mInfo->mNamespaceMap(fullName, NamespaceInfo());
         return mInfo->mNamespaceMap[fullName].Initialize(this->mInfo, directory, namespaceName, fullName, initalizer);
      }
   }
}
