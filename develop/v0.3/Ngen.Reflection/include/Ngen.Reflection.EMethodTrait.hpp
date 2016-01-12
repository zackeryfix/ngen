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
#ifndef __NGEN_REFLECTION_EMETHODTRAIT_HPP
#define __NGEN_REFLECTION_EMETHODTRAIT_HPP

#include "Ngen.Reflection.Typedefs.hpp"

namespace Ngen {
   /** @brief The different traits associated with a method. */
	enum class EMethodTrait : uword {
	   /** @brief The method is publicly available through-out the reflection engine. */
      Public = 0,
	   /** @brief The method is protected and is only available to inherited types, or friendly types. */
      Protected,
      /** @brief The method is private and is only available to the type that it belongs to. */
      Private,
	   /** @brief The method is static and does not require an object instance to be invoked. */
      Static,
	   /** @brief The method is a template and requires dynamic binding to type information when executed. */
      Template,
	   /** @brief The contents of the method can be in-lined directly where its invoked. */
      Inline,
	   /** @brief The method is hidden and can only be invoked by code existing within the same assembly. */
      Hidden,
	   /** @brief The method is virtual and can optionally be overridden by inherited types. */
      Virtual,
	   /** @brief The method is an abstract label and must be overridden by inherited types. */
      Abstract,
	   /** @brief The method requires an instance to be invoked and guarantees that the instance will not be modified when the method is invoked. */
      ConstMember,
      /** @brief The method cannot be overridden or reimplemented in derived types. */
      Final,
      _COUNT
	};
	typedef BitFlags<EMethodTrait> MethodTraitFlags;
}

#endif // __NGEN_REFLECTION_EMETHODTRAIT_HPP
