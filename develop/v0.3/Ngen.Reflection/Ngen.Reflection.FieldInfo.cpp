
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
#include "Ngen.Reflection.FieldInfo.hpp"
#include "Ngen.Reflection.NamespaceInfo.hpp"
#include "Ngen.Reflection.TypeInfo.hpp"

namespace Ngen {
   namespace Reflection {
      FieldBuilder::FieldBuilder(FieldInfo* field) : mInfo(field) {}

      void FieldBuilder::SetTrait(EFieldTrait trait, bool value) {
         this->mInfo->mTraits.Set(trait, value);
      }

      void FieldBuilder::SetTrait(FieldTraitFlags traits) {
         this->mInfo->mTraits = traits;
      }

      FieldInfo* FieldInfo::Initialize(NamespaceInfo* directory,  Field* field, const mirror& relativeName, typename VoidStaticDelegate<FieldBuilder>::TFunction initializer) {
         pMute();
         mDirectory = directory;
         mReturnType = null; //TODO: find return type information || pass into Initialize as param
         mName = relativeName;
         mFullName = directory->FullName().ToLongName() + '#' + mName.ToLongName();
         mField = field;
         initializer(FieldBuilder(this));
         pUnmute();
         return this;
      }
   }
}
