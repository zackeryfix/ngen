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
#ifndef __NGEN_REFLECTION_EFIELDTRAIT_HPP
#define __NGEN_REFLECTION_EFIELDTRAIT_HPP

#include "Ngen.Reflection.Typedefs.hpp"

namespace Ngen {

	/** @brief The different traits associated with field information and property information. */
	enum class EFieldTrait : uword {
	   /** @brief The field is publicly available through-out the reflection engine. */
      Public = 0,
	   /** @brief The field is protected and is only available to inherited types, or friendly types. */
      Protected,
      /** @brief The field is private and is only available to the type that it belongs to. */
      Private,
	   /** @brief The field is static and does not require an object instance to be accessed. */
      Static,
	   /** @brief The field is hidden and can only be accessed by code existing within the same assembly. */
      Hidden,
	   /** @brief The field is a constant, cannot be changed, and its value is copied in places where its used. */
      Const,
	   /** @brief The field is read-only, can only be changed by code existing within the same scope where it is declared, and its value is referenced in places where its used. */
      Readonly,

      _COUNT
	};
	typedef BitFlags<EFieldTrait> FieldTraitFlags;
}

#endif // __NGEN_REFLECTION_EFIELDTRAIT_HPP
