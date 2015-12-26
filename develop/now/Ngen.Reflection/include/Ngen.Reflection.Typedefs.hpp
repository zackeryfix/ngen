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
#ifndef __NGEN_REFLECTION_TYPEDEFS_HPP
#define __NGEN_REFLECTION_TYPEDEFS_HPP

#include "Build.Ngen.Reflection.Logic.hpp"

namespace Ngen {
   namespace Reflection {
      class FieldInfo;
      class FieldBuilder;
      class MethodInfo;
      class MethodBuilder;
      class ParameterInfo;
      class NamespaceInfo;
      class NamespaceBuilder;
      class TypeInfo;
      class TypeBuilder;
      class AssemblyInfo;
      class AssemblyBuilder;

#     define __inline_standard_containers(__TYPENAME__)\
      typedef Map<Mirror, __TYPENAME__>      Mirror##__TYPENAME__##Map;;\
      typedef Map<Mirror, __TYPENAME__*>     Mirror##__TYPENAME__##PtrMap;\
      typedef Array<__TYPENAME__>            __TYPENAME__##Array;\
      typedef Array<__TYPENAME__*>           __TYPENAME__##PtrArray;\
      typedef List<__TYPENAME__>            __TYPENAME__##List;\
      typedef List<__TYPENAME__*>           __TYPENAME__##PtrList

      __inline_standard_containers(FieldInfo);
      __inline_standard_containers(MethodInfo);
      __inline_standard_containers(ParameterInfo);
      __inline_standard_containers(NamespaceInfo);
      __inline_standard_containers(TypeInfo);
      __inline_standard_containers(AssemblyInfo);
   }
}


#endif // __NGEN_REFLECTION_TYPEDEFS_HPP
