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
#ifndef __NGEN_REFLECTION_EPARAMETERTRAIT_HPP
#define __NGEN_REFLECTION_EPARAMETERTRAIT_HPP

#include "Ngen.Reflection.Typedefs.hpp"

namespace Ngen {

	/** @brief The different traits associated with the parameters of a method call. */
	enum class EParameterTrait : uword {
       /** @brief The parameter is a reference to the value changes made to the parameter will persist when the function returns. */
		Reference = 0,
      /** @brief The parameter is a copy of the value and changes to the parameter will not persist when the function returns. */
		Value,
      /** @brief The parameter is a pointer to the value. */
		Pointer,
      /** @brief The parameter is a strongly dynamically typed object instance. */
		Object,
      /** @brief The parameter is constant and its value is guaranteed not to change when the function returns. */
		Const,
      /** @brief The parameter is a delegated function or lambda. */
		Delegate,
      /** @brief The parameter is a pointer to a set of values that have the same parameter traits. This is not the same as an Array construct and can be looked at more like a C++ pointer-to-pointer. */
      Array,

		_COUNT,
	};
	typedef BitFlags<EParameterTrait> ParameterTraitFlags;
}

#endif // __NGEN_REFLECTION_EPARAMETERTRAIT_HPP
