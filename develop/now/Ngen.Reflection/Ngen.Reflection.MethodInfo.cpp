
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
#include "Ngen.Reflection.MethodInfo.hpp"
#include "Ngen.Reflection.NamespaceInfo.hpp"
#include "Ngen.Reflection.TypeInfo.hpp"

namespace Ngen {
   namespace Reflection {
			MethodInfo* MethodInfo::Initialize(NamespaceInfo* directory, const mirror& signature, Delegate* function, VoidStaticDelegate<MethodBuilder>::TFunction initializer) {
            pMute();
            mDirectory = directory;
            mName = signature;
            mFullName = directory->FullName().ToLongName() + '$' + mName.ToLongName();
            mFunction = function;
            mReturn = 0;
				initializer(MethodBuilder(this));
				pUnmute();
				return this;
			}

         Assembly* MethodInfo::Assembly() const {
            return mDirectory->GetAssembly();
			}

         MethodBuilder::MethodBuilder(MethodInfo* method) : mInfo(method) {}

         ParameterInfo* MethodBuilder::AddParameter(ParameterTraitFlags traits, const mirror& typeName, const string& name, const string& description) {
            auto info = ParameterInfo(mInfo, traits, typeName, name, mParamCount);
            this->mInfo->mParams.Add(info);
            return &this->mInfo->mParams[this->mParamCount++];
         }

         void MethodBuilder::SetTrait(EMethodTrait trait, bool value) {
            this->mInfo->mTraits.Set(trait, value);
         }
         void MethodBuilder::SetTrait(MethodTraitFlags traits) {
            this->mInfo->mTraits = traits;
         }
   }
}
