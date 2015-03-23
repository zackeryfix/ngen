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
#ifndef __NGEN_REFLECTION_HPP
#define __NGEN_REFLECTION_HPP

#include "Ngen.hpp"
#include "Ngen.Reflection.EReflectedPart.hpp"
#include "Ngen.Reflection.ETypeTrait.hpp"
#include "Ngen.Reflection.MethodBuilder.hpp"
#include "Ngen.Reflection.TypeBuilder.hpp"
#include "Ngen.Reflection.NamespaceBuilder.hpp"
#include "Ngen.Reflection.AttributeInfo.hpp"
#include "Ngen.Reflection.MethodInfo.hpp"
#include "Ngen.Reflection.NamespaceInfo.hpp"
#include "Ngen.Reflection.TypeInfo.hpp"
#include "Ngen.Reflection.AssemblyInfo.hpp"

typedef template StaticDelegate<TypeBuilder>::TFunction TypeInitializerFunction;

/** @brief Creates a default type that has a default constructor, copy constructor, and de-constructor.
 * @remarks If the new type has the properties of a primitive construct, then consider using the CreatePrimitive
 * function instead.
 */
template<typename T> TypeInfo* new_typeinfo(Type* scope, uword modifierFlags, bool dtor, TypeInitializerFunction initializer) {
	mirror name = t_mirror<T>::result();

	TypeInfo result = TypeInfo(name, [] (TypeDescriptor builder) {
		// default constructor
		builder.AddConstructor(&StaticDelegate<unknown&, uword>([] (unknown& at, uword count) {
			at = memory::UnknownNew<T>(at, count);
		}));

		if(dtor) {
			// default de-constructor
			builder.SetDestructor(&StaticDelegate<unknown>([] (unknown del) {
				memory::UnknownDelete<T>(del);
			}));
		}

		initializer(builder);
	});

	return wNewTypeInfo(const TypeInfo& info);
}

#endif // __NGEN_RTI_HPP
