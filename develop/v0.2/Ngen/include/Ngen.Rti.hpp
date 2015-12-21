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
#ifndef __NGEN_RTI_HPP
#define __NGEN_RTI_HPP

#include "Ngen.hpp"
#include "Ngen.Enums.hpp"
#include "Ngen.Builders.hpp"
#include "Ngen.Rti.AttributeInfo.hpp"
#include "Ngen.Rti.MethodInfo.hpp"
#include "Ngen.Rti.NamespaceInfo.hpp"
#include "Ngen.Rti.TypeInfo.hpp"
#include "Ngen.Rti.AssemblyInfo.hpp"

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

extern "C" {
	ngen_api TypeInfo* wNewTypeInfo(const TypeInfo& info);
	ngen_api MethodInfo* wNewMethodInfo(const MethodInfo& info);
	ngen_api Attribute* wNewAttribute(const Attribute& info);
	ngen_api NamespaceInfo* wNewMethodInfo(const NamespaceInfo& info);

	ngen_api TypeInfo* wGetType(const mirror& typeName);
	ngen_api MethodInfo* wGetMethod(const mirror& signature);
	ngen_api Attribute* wGetAttribute(const mirror& identity);
	ngen_api TypeInfo* wGetNamespace(const mirror& name);
	//ngen_api Enumeration* wGetEnumeration(const mirror& name);
}

#endif // __NGEN_RTI_HPP
