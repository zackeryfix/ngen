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
#ifndef __NGEN_LIBRARY_HPP
#define __NGEN_LIBRARY_HPP

#include "Ngen.Mirror.hpp"

namespace Ngen {

	class ngen_api Library final {
	public:
		Library() = default;
		Library(const mirror& path, unknown handle) : mPath(path), mHandle(handle) {}
		Library(const Library& copy) : mPath(copy.mPath), mHandle(copy.mHandle) {}

		/** @brief Attempts to load a shared library from a physical location.
		 * @param path A mirror created from the physical file path used to identify the library.
		 * @param lib A pointer where the loaded library will be referenced after the function exits.
		 * @return A value that indicates if the library was correctly loaded.
		 */
		static bool Load(const mirror& path, Library*& lib);

		/** @brief Unloads a library that was previously loaded by the system.
		 * @param path A mirror created from the physical file path used to identify the library.
		 * @return A value that indicates if the library was correctly unloaded.
		 */
		static bool Unload(const mirror& path);

		/** @brief Ensures a library has been registered to the global cache.
		 * @param path A mirror created from the physical file path used to identify the library.
		 * @return A value that indicates if the library was correctly cached.
		 */
		static bool Cache(const mirror& path);

		/** @brief Gets the mirror representing the physical path  of the shared object file.
		 */
		mirror Path() const {
			return mPath;
		}

		/** @brief Gets a symbol from the library cast to the given symbol signature.
		 * @param symbol The signature of the symbol being referenced from the library.
		 */
		unknown Get(const mirror& symbol) const {
			return mGet(symbol);
		}

		/** @brief Determines if the library has been loaded into memory.
		 */
		bool IsLoaded() const;

	protected:
		/** @brief Protected member */
		unknown mGet(const mirror& signature) const;

		mirror mPath;
		unknown mHandle;
	};
}
#endif // __NGEN_LIBRARY_HPP
