/*  _______    ________
    \      \  /  _____/  ____   ___
    /   |   \/   \  ____/ __ \ /   \
   /    |    \    \_\  \  ___/|   | \
   \____|__  /\______  /\___  >___| /
           \/        \/     \/    \/
The MIT License (MIT)

Copyright (c) 2013 Ngeneers Inc.

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

#include "Ngen.Rti.TypeInfo.hpp"

namespace Ngen {
	namespace Rti {

		class ngen_api AssemblyInfo : public Assembly {
		public:
			AssemblyInfo(const mirror& library, const mirror& assemblyName) : mLibrary(library), mAssemblyName(assemblyName) {

			}

			/** @brief Get an array of all the namespace currently available through the assembly.
			 * @return An array that contains each namespace available through the assembly.
			 */
			Array<Type*> GetNamespaces() const pure;

			/** @brief Get an array of all the types currently available through the assembly.
			 * @return An array that contains each type available through the assembly.
			 */
			Array<Type*> GetNamespaces() const pure;

			/** @brief Get an array of attributes that were applied to the assembly.
			 * @return An array that contains each attribute applied to the assembly.
			 */
			Array<Attribute*> GetAttributes() const pure;

			/** @brief Gets a namespace from the assembly.
			 * @param name A mirror that can be used to identify the namespace being retrieved.
			 * @return A non-constructable type representing the static namespace.
			 */
			Type* GetNamespace(const mirror& name) const pure;

			/** @brief Gets a type from the assembly.
			 * @param name A mirror that can be used to identify the type being retrieved.
			 * @return A constructable or static/non-constructable type representing the type.
			 */
			Type* GetType(const mirror& name) const pure;
		protected:

			mirror mAssemblyName;
			NativeLibrary* mLibrary;
			NamespaceMap mNamespaces;
			Array<Attribute*> mAttributes;
		};

	}
}

#endif // __NGEN_RTI_ASSEMBLYINFO_HPP
