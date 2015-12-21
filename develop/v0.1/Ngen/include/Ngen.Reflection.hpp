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
#ifndef __NGEN_REFLECTION_HPP
#define __NGEN_REFLECTION_HPP

#include "Ngen.Delegate.hpp"

namespace Ngen {
	class Type;

	/** @brief The gateway into the frameworks reflected type information.
	 */
	class ngen_api Reflection final {

		class TypeLibrary {
			public:
		};

		Reflection();

	public:
		/** @brief A reflection of all reflected code elements. */
		static Reflection* All();

		Reflection(text scopeName);

		Type* GetType(text typeName) pure;
		Delegate* GetFunction(text signature);
		Reflection
	protected:
		static const Reflection mAll;

		Mirror mScopeName;
		friend class Type;
	};
}

#endif // __NGEN_REFLECTION_HPP
