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
#ifndef __NGEN_RTI_ASSEMBLYINFO_HPP
#define __NGEN_RTI_ASSEMBLYINFO_HPP

#include "Ngen.Reflection.AssemblyBuilder.hpp"

namespace Ngen {
	namespace Reflection {

		class ngen_api AssemblyInfo : public Assembly {
		public:
		   /** @brief
          */
			AssemblyInfo();

		   /** @brief
          */
			static AssemblyInfo* New(const mirror& library, const mirror& assemblyName,  typename VoidStaticDelegate<AssemblyBuilder>::TFunction initialize);

			/** @brief Get an array of all the namespaces currently available through the assembly.
			 * @return An array that contains each namespace available through the assembly.
			 */
			Array<Type*> GetNamespaces() const;

			/** @brief Get an array of all the types currently available through the assembly.
			 * @return An array that contains each type available through the assembly.
			 */
			Array<Type*> GetTypes() const;

			/** @brief Get an array of attributes that were bound to the assembly.
			 * @return An array that contains each attribute applied to the assembly.
			 */
			Array<Attribute*> GetAttributes() const;

			/** @brief Gets the reflected information for a namespace that belongs to the assembly.
			 * @param name A mirror that can be used to identify the namespace being retrieved.
			 * @return The reflected information representing the non-constructible type of the static namespace.
			 */
			Type* GetNamespace(const mirror& name) const;

			/** @brief Gets a type from the assembly.
			 * @param name A mirror that can be used to identify the type being retrieved.
			 * @return The reflected information of the constructible or static/non-constructible type.
			 */
			Type* GetType(const mirror& name) const;

			Library* GetNativeLibrary() const;

		protected:
			void pMute() { mIsMuted = true; }
			void pUnmute() { mIsMuted = false; }

		   bool mIsMuted;                               // logic flag
			Library* mLibrary;                           // the library that owns the assembly
			mirror mAssemblyName;                        // the actual name of the assembly (constant)
			Map<Mirror, NamespaceInfo> mRootNamespaceMap;    // all the root namespaces in the assmebly
			Map<Mirror, NamespaceInfo*> mNamespaceInfoMap;
			Map<Mirror, TypeInfo*> mTypeInfoMap;
         Array<Attribute> mCustomAttributes;          // all the custom attributes found inside the assembly

         friend class TypeInfo;
         friend class NamespaceInfo;
			friend class AssemblyBuilder;
		};


	}
}

#endif // __NGEN_RTI_ASSEMBLYINFO_HPP
