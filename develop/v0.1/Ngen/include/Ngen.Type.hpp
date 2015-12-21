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
#ifndef __NGEN_TYPE_HPP
#define __NGEN_TYPE_HPP

#include "Ngen.List.hpp"
#include "Ngen.Object.hpp"
#include "Ngen.StaticDelegate.hpp"

namespace Ngen {
	/** @brief */
	class ngen_api Type {
	public:
		virtual ~Type() {}

		/** @brief Gets the byte size of the data structure represented by the Type. */
		virtual uword Size() const pure;

		/** @brief Gets the full reflected name of the Type. */
		virtual text FullName() const pure;

		/** @brief Gets the short name of the Type. */
		virtual text Name() const pure;

		/** @brief Gets a human readable string representing a Object known to be of the same Type. */
		//virtual text ToText(const Object& _this) const pure;

		/** @brief Gets a method known to the Type using the given signature. */
		//virtual Delegate* GetMethod(const text& signature) const pure;

		/** @brief Invokes a method known to the Type using the given signature. */
		//virtual Object Invoke(const text& signature, Object _this, Object* params) const pure;

		/** @brief Creates a new default Object instance of the Type. */
		virtual Object CreateInstance() const pure;

		/** @brief Creates a new Object instance of the Type from the copy of another same type Object. */
		virtual Object CreateInstance(Object copy) const pure;

		/** @brief Destroys an Object instance of the Type. */
		virtual void DestroyInstance(Object _this) const pure;

		/** @brief Determines if the Type is a base and does not inherit another type. */
		//virtual bool IsBase() const pure;

		/** @brief Determines if the Type is a concrete implementation with pure abstractions. */
		//virtual bool IsAbstract() const pure;

		/** @brief Determines if the Type is a pure abstraction with no concrete implementation. */
		//virtual bool IsInterface() const pure;

		/** @brief Determines if the Type has been finalized and can not be inherited. */
		//virtual bool IsFinal() const pure;

		/** @brief Determines if the Type is considered a primitive structure. */
		//virtual bool IsPrimitive() const pure;

		/** @brief Determines if the Type inherits the given Type. */
		//virtual bool IsChild(const Type* oftype) const pure;

		/** @brief Determines if the Type has been inherited by the given Type. */
		//virtual bool IsParent(const Type* oftype) const pure;

		/** @brief Determines if the Type is a completely reflected or is minimally reflected. */
		//virtual bool IsComplete() const pure;

		/** @brief Determines if the Type should be treated as a namespace and should not be constructed. */
		//virtual bool IsStatic() const pure;

		/** @brief Determines if the Type can be copied or only referenced. */
		//virtual bool IsCopyable() const pure;

		/** @brief Gets an array of each Type the Type inherits. */
		//virtual List<Type*> Parents() const pure;

		/** @brief Gets an array of each Attribute assigned to the Type. */
		//virtual List<Attribute*> Attributes() const pure;

		/** @brief Gets an array of each Method available through the Type.
		 * @param inherited Determines if inherited methods should be included. Default = true.
		 */
		//virtual List<Delegate*> Methods(bool inherited = true) const pure;

		/** @brief Gets an array of each Field available through the Type.
		 * @param inherited Determines if inherited fields should be included. Default = true.
		 */
		//virtual List<Field*> Fields(bool inherited = true) const pure;

		/** @brief Gets an array of each nested Type available through the Type.
		 */
		//virtual List<Type*> Nested() const pure;

	};
}
#endif // __NGEN_TYPE_HPP
