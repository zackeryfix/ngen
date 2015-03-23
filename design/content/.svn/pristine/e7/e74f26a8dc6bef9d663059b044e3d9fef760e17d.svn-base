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
#ifndef __NGEN_SYSTEM_HPP
#define __NGEN_SYSTEM_HPP

#include "Ngen.Mirror.hpp"

namespace Ngen {
	class Library;

	class ngen_api System final {
	public:
		/** @brief Attempts to load a shared library from a physical location.
		 * @param path A mirror created from the physical file path used to identify the library.
		 * @param lib A pointer where the loaded library will be referenced after the function exits.
		 * @return A value that indicates if the library was correctly loaded.
		 */
		static bool Load(const mirror& path, Library*& lib);

		/** @brief Determines if a library has been registered to the global cache.
		 * @param path A mirror created from the physical file path used to identify the library.
		 * @return A value that indicates if the library was correctly unloaded.
		 */
		static bool Unload(const mirror& path);

		/** @brief Determines if a library has been registered to the global cache.
		 * @param path A mirror created from the physical file path used to identify the library.
		 * @return A value that indicates if the library was correctly cached.
		 */
		static bool Cache(const mirror& path);
	};

	/** @brief A structure representing a library file context.
	*/
	class ngen_api Library {
	public:
		Library() : mPath(), mIsLoaded(false) {}
		Library(const mirror& path) : mPath(path), mIsLoaded(false) {
		}
		Library(const Library& copy) : mPath(copy.mPath), mIsLoaded(copy.mIsLoaded) {
		}

		bool IsLoaded() const {
			return mIsLoaded;
		}

		mirror Path() const {
			return mPath;
		}

	protected:
		mirror mPath;
		bool mIsLoaded;

		friend class System;
	};

}
#endif // __NGEN_NATIVE_HPP
