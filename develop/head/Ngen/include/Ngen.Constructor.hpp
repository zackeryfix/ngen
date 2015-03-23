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
#ifndef __NGEN_ECONSTRUCTORKIND_HPP
#define __NGEN_ECONSTRUCTORKIND_HPP

#inlcude "Ngen.Map.hpp"

namespace Ngen {
	/** @brief Describes the different kinds of constructors of a Type.
	 */
	enum class EConstructorKind {
		/** @brief  Default constructor. T()
		 */
		Default = 1,

		/** @brief  Copy constructor. T(const T&)
		 */
		Copy = 2,

		/** @brief  Move constructor. T(T&&)
		 */
		Move = 3,

		/** @brief  Implicit-cast constructor. T(T2&)
		 */
		Cast = 4,
	};

	/** @brief A data structure used to bind meta-data to a constructor method of a Type. */
	class ngen_api Constructor {
	public:
		/** @brief */
		Constructor(MethodInfo method, EConstructorKind kind) : Ctor(method), Kind(kind) {
		}

		MethodInfo Ctor;
		EConstructorKind Kind;
	};

	typedef Array<Constructor> ConstructorArray;
	typedef Array<Constructor*> ConstructorPointerArray;
	typedef Map<EConstructorKind, ConstructorArray> ConstructorBook;
	typedef Map<EConstructorKind, ConstructorArray> ConstructorPointerBook;
}

#endif // __NGEN_ECONSTRUCTORKIND_HPP
