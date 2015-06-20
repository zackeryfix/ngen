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
#ifndef __NGEN_RTI_BUILDERS_HPP
#define __NGEN_RTI_BUILDERS_HPP

#include "Ngen.Enums.hpp"

namespace Ngen {
	namespace Rti {
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

		/** @brief A procedural programming structure used to build the description of a new type.
		 */
		class ngen_api TypeBuilder {
		public:
			TypeBuilder(TypeInfo* type) : mInfo(type) {
				if(!mInfo->pIsMuted()) {
					THROW(InvalidOperationException("The given RTI is not mutable and can not be modified."));
				}
			}

			/** @brief Adds a new method information structure to the type.
			 * @param signature The signature used to identify the method as a part of the type.
			 * @param function The delegate constant that represents the method body.
			 */
			void AddMethod(const mirror& signature, Delegate* function);
			void AddConstructor(const mirror& signature, Delegate* function, EConstructorKind kind);
			void InitializeAs(EInitializerKind kind);
			void AddParent(const mirror& parentName) {
				TypeInfo* parent = ngen_get_type(parentName);
				parent->mChildren.Add(mInfo->FullName(), mInfo);
				mInfo->mParents.Add(parent->FullName(), parent);
			}

			void AddFlag(EModifierFlag flag) {
				mInfo->mModifierFlag |= flag;
			}

			void RemoveFlag(EModifierFlag flag) {
				mInfo->mModifierFlag &= ~flag;
			}

			void SetModifierFlags(uword flags) {
				mInfo->mModifierFlag = flags;
			}

			void SetDestructor(Delegate* function, MethodInfoInitializer initializer) {
				MethodInfo method = MethodInfo((NamespaceInfo*)mInfo, const_text(""), function, initializer);
				mInfo->mDtor = method;

			}
		protected:
			TypeInfo* mInfo;

			friend class Assembly;
		};
	}
}

#endif // __NGEN_RTI_BUILDERS_HPP