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
#ifndef __NGEN_REFLECTION_ETYPETRAIT_HPP
#define __NGEN_REFLECTION_ETYPETRAIT_HPP

#include "Ngen.Reflection.Typedefs.hpp"

namespace Ngen {
namespace Reflection {
	/** @brief The different traits associated with type information. */
	enum class ETypeTrait {
	   /** @brief The type is publicly available through-out the reflection engine. */
      Public,
	   /** @brief The type is static and cannot have an object instance created for it. */
      Static,
	   /** @brief The type is a template and requires dynamic binding to type information when an instance is created or its members are accessed. */
      Template,
	   /** @brief The type is hidden and can only be instanced or accessed from code within the same assembly. */
      Hidden,
	   /** @brief The type only represents an abstract implementation and requires an inherited implementation to be functionally created. */
      Abstract,
      /** @brief The type is the final implementation in a chain of inheritance. */
      Final,

      Primitive,
      _COUNT
	};
	typedef BitFlags<ETypeTrait> TypeTraitFlags;
}
}

#endif // __NGEN_REFLECTION_ETYPETRAIT_HPP
