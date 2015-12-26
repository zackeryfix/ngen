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
#ifndef __NGEN_REFLECTION_ASSEMBLYBUILDER_HPP
#define __NGEN_REFLECTION_ASSEMBLYBUILDER_HPP

#include "Ngen.Reflection.TypeBuilder.hpp"

namespace Ngen {
   namespace Reflection {
      /** @brief
       */
      class AssemblyBuilder {
         AssemblyBuilder(AssemblyInfo* info) : mInfo(info) {
            if(!info->mIsMuted) {
               THROW(InvalidOperationException("The assembly being constructed is read-only and cannot be modified."));
            }
         }

         AssemblyBuilder& AddNamespace(const mirror& namespaceName, NamespaceInfo* directory, const VoidStaticDelegate<NamespaceBuilder>::TFunction initalizer);
      private:
         AssemblyInfo* mInfo;

         friend class AssemblyInfo;
         friend class Assembly;
      };
   }
}

#endif // __NGEN_REFLECTION_ASSEMBLYBUILDER_HPP
