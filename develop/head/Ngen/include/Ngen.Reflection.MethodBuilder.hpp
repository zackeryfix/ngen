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
#ifndef __NGEN_REFLECTION_METHODBUILDER_HPP
#define __NGEN_REFLECTION_METHODBUILDER_HPP

#include "Ngen.Reflection.ETypeTrait.hpp"
#include "Ngen.Reflection.EReflectedPiece.hpp"
#include "Ngen.Deconstructor.hpp"
#include "Ngen.Constructor.hpp"

namespace Ngen {
	namespace Reflection {
		class NamespaceInfo;
		class TypeInfo;
		class MethodInfo;

		/** @brief Map<mirror, NamespaceInfo> */
		typedef Map<mirror, NamespaceInfo> 	MirrorNamespaceMap;

		/** @brief Map<mirror, TypeInfo> */
		typedef Map<mirror, TypeInfo> 		MirrorTypeInfoMap;

		/** @brief Map<mirror, MethodInfo> */
		typedef Map<mirror, MethodInfo> 		MirrorMethodInfoMap;

		/** @brief Map<mirror, NamespaceInfo*> */
		typedef Map<mirror, NamespaceInfo*> MirrorNamespacePointerMap;

		/** @brief Map<mirror, TypeInfo*> */
		typedef Map<mirror, TypeInfo*> 		MirrorTypeInfoPointerMap;

		/** @brief Map<mirror, MethodInfo*> */
		typedef Map<mirror, MethodInfo*> 	MirrorMethodInfoPointerMap;

		/** @brief */
		class ngen_api MethodBuilder {
		public:
			MethodBuilder(MethodInfo* method);

		protected:
			MethodInfo* mInfo;

			friend class Assembly;
		};

		typedef StaticDelegate<MethodBuilder>::TFunction MethodInfoInitializer;
	}
}

#endif
