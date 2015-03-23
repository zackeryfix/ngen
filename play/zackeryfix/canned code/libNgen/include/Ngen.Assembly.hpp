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
#ifndef __NGEN_ASSEMBLY_HPP
#define __NGEN_ASSEMBLY_HPP

#include "Ngen.Type.hpp"

namespace Ngen {
	class Type;

	typedef Map<Assmebly*, Reference*> AssemblyReferenceMap;

	/** @brief A single unit of reflected type information that is load and unloaded
	 * in its entirety and typically will reside inside a shared object file or dynamic
	 * library.
	 */
	class ngen_api Assembly {
	public:

		static bool TryLoadFrom(const mirror& libraryFileName)
		/** @brief Loads a binary file from a physical storage location.
		 * @param library The mirror that can be used to identify the file path of the library.
		 * @param assemblyName The mirror used to identify the assemebly being referenced from the library.
		 * @return The number of assemblies found to exist in the library.
		 */
		static Assembly* Reference(const mirror& libraryFileName, const mirror& assmeblyName);

		/** @brief Dereferences an assembly previously referenced by the reflection engine.
		 * @param assemblyName The assembly being dereferenced.
		 * @return A value that determines if there were conflicts while attempting to dereference the assembly.
		 */
		static bool Dereference(Assembly* assembly);

		/** @brief Unloads a previously loaded library, and all assemblies it references.
		 * @param library A mirror used to identify the library being unloaded.
		 */
		static void Unload(const mirror& library);

		/** @brief Get an array of all the namespace currently available through the assembly.
		 * @return An array that contains each namespace available through the assembly.
		 */
		Array<Type*> GetNamespaces() const pure;

		/** @brief Get an array of all the types currently available through the assembly.
		 * @return An array that contains each type available through the assembly.
		 */
		Array<Type*> GetTypes() const pure;

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

		/** @brief Gets the library responsible for referencing the assembly. */
		Library* GetNativeLibrary() const pure;
	protected:
		Library* mLib;

		friend class Type;
	};

#	define typeof(T) Assembly::GetType(t_mirror<T>::result());
}

#endif // __NGEN_REFLECTION_HPP
