/*  _______    ________
    \      \  /  _____/  ____   ___
    /   |   \/   \  ____/ __ \ /   \
   /    |    \    \_\  \  ___/|   | \
   \____|__  /\______  /\___  >___| /
           \/        \/     \/    \/
The MIT License (MIT)

COPYRIGHT (C) 2014 NGENWARE

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

#include "Ngen.Assembly.hpp"

namespace Ngen {
	/** @brief Modifier flags are used to mark reflected items with having specific
	 * properties that will influence that items behaviour, or visibility to other reflected items.
	 */
	enum class ETypeTrait : uword {
		/** @brief Visible to all reflected code spaces.
		 */
		Public = 0,

		/** @brief Visible to inherited code spaces.
		 */
		Protected,

		/** @brief Visible only to its origin code space.
		 */
		Private,

		/** @brief Accessed using an static instance of an assembly; rather than
		 * the object instance of a type.
		 */
		Static,

		/** @brief A virtual layer that maintains a generic code base that can be overridden through an
		 * inherited implementation.
		 */
		Virtual,

		/** @brief An abstract layer that strictly maintains the declaration guidelines required by
		 * the API of an inherited code space.
		 */
		Abstract,

		/** @brief Completely hidden from all other codes spaces.  Typically used for internal static
		 * code spaces.
		 */
		Hidden,

		/** @brief Can be cropped into place with another code space to improve performance and reduce redundant
		 * code implementations.
		 */
		Inline,

		/** @brief A generic implementation that can encapsulate various types that share a common component,
		 * trait, or base reflection.
		 */
		Template,

		/** @brief The final implementation in a chain of inherited types.
		 */
		Final,

		/** @brief The default implementation for a prerequisite required by the RTI.
		 */
		Default,

		/** @brief Can be copied, referenced, and modified, but cannot be reassigned or exchanged.
		 */
		Readonly,

		/** @brief Can be copied and referenced, but cannot be modified, reassigned, or exchanged.
		 */
		Const,

		/** @brief Allows for zero or more arguments of the same type under a single parameter.
		 */
		Variadic,

		/** @brief Allows for zero or more arguments of the same type under a single parameter.
		 */
		LinqExpression,

		_COUNT,
	};


	class enum ESecurityTrait : uword {
		IsPublic = 0,
		IsProtected,
		IsPrivate,
		IsInternal,
		IsObsolete,
		IsFinal,
		IsDefault,
		IsAbstract,
		IsVirtual,
		IsStatic,
		IsTemplate,
		IsLocal,
		IsLinq,
		IsReadonly,
		IsDynamic,
		IsUndocumented,
		IsUntested,
		IsUnsafe,

		_COUNT
	}; typedef BitFlags<ESecurityTrait> SecurityTraitFlags;

	class enum ETypeTrait : uword {
		IsBase,
		IsPrimitive,
		IsAligned,
		IsContainer,
		IsCopyable,
		IsMoveable,
		IsDestructable,
		IsComparable,
		IsNullable,
		IsAttribute,
		IsNamespace,

		_COUNT,
	}; typedef BitFlags<ETypeTrait> TypeTraitFlags;

	typedef BitFlags<EMethodTrait> MethodTraitFlags;


	class enum EParameterTrait : uword {
		IsByReference = 0,
		IsPointer,
		IsObject,
		IsDynamic,
		IsConst;
		_COUNT
	}; typedef BitFlags<EParameterTrait> ParameterTraitFlags;

	class enum EAttributeTrait {
		TypeBound,
		NamespaceBound,
		AssmeblyBound,
		MethodBound,
		EventBound,
		ApplicationBound,
		RuntimeBound,
		FieldBound,
		PropertyBound,
		DelegateBound,
		ParameterBound,

		_COUNT
	};	typedef BitFlags<EAttributeTrait> AttributeTraitFlags;
}

#endif // __NGEN_REFLECTION_ETYPETRAIT_HPP
