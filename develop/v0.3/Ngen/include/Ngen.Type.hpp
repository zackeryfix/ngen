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
#ifndef __NGEN_TYPE_HPP
#define __NGEN_TYPE_HPP

#include "Ngen.Object.hpp"

namespace Ngen {
	/** @brief */
	class ngen_api Type {
	public:
		/** @brief */
		virtual ~Type() {}

		/** @brief operator==(Type* const) */
		virtual bool operator==(Type* const rhs) const pure;

		/** @brief operator!=(Type* const) */
		virtual bool operator!=(Type* const rhs) const pure;

		/** @brief Gets the size (in bytes) of the data structure represented by the Type.
		 */
		virtual uword Size() const pure;

		/** @brief Gets the full reflected name of the Type.
		 */
		virtual mirror FullName() const pure;

		/** @brief Gets the short name of the Type.
		 */
		virtual mirror Name() const pure;

		/** @brief Gets a method member of the Type that matches the given signature.
		 * @param signature The signature of the method nested within the scope of the type.
		 * @return A delegate representing the method that was found.
		 * @throw MissingReferenceException when the method signature could not be resolved to an actual function.
		 */
		virtual Delegate* GetMethod(const mirror& signature) const pure;

		/** @brief Gets an array of all the method members of this Type.
		 * @return An array containing all the method information bound to this type.
		 */
		virtual Array<Delegate*> GetMemberMethods() const pure;

      /** @brief Gets an array of all the method members of this Type.
		 * @return An array containing all the method information bound to this type.
		 */
		virtual Array<Delegate*> GetStaticMethods() const pure;

			/** @brief Gets a field member of the Type that matches the given signature.
		 * @param signature The signature of the field nested within the scope of this type.
		 * @return A field representing the field member that was found.
		 * @throw MissingReferenceException when the field signature could not be resolved to an actual member.
		 */
		virtual Field* GetField(const mirror& signature) const pure;

		/** @brief Gets an array of all the field members of this Type.
		 * @return An array containing all the field information bound to this type.
		 */
		virtual Array<Field*> GetStaticFields() const pure;


		/** @brief Gets an array of all the field members of this Type.
		 * @return An array containing all the field information bound to this type.
		 */
		virtual Array<Field*> GetMemberFields() const pure;

		/** @brief Gets a member method callback for the Type that matches the given signature.
		 * @param _this An unknown pointer that is represented as an instance of this type.
		 * @param signature The signature of the method nested within the scope of the type.
		 * @return A callback representing an invocation of the method that was found.
		 * @throw MissingReferenceException when the method signature could not be resolved to an actual function.
		 */
      Callback GetCallback(unknown _this, const mirror& signature) const {
         return Callback(_this, GetMethod(signature));
		}

		/** @brief Creates a default Object instance of the Type.
		 */
		virtual Object NewInstance() const pure;

		/** @brief Creates a new Object instance of the Type using unknown data.
		 * @param data A pointer representing a the data that will encapsulate the new Object.
		 * @param stackBound Determines if the object is stack bound, or heap bound.
		 */
		virtual Object NewInstance(unknown data, bool stackBound = true) const pure;

		/** @brief Creates a new Object instance of the Type from the copy of another same type Object.
		 */
		virtual Object CopyInstance(Object copy) const pure;

		/** @brief Destroys an Object instance of the Type.
		 */
		virtual void DestroyInstance(Object _this) const pure;

		/** @brief Determines if the Type is a base and does not inherit another type. */
		virtual bool IsBase() const pure;

		/** @brief Determines if the Type is considered a primitive data type. */
		virtual bool IsPrimitive() const pure;

		/** @brief Determines if the Type inherits the given Type.
		 * @param base A mirror that can be used to identify the type expected in the chain of inheritance.
		 * @return True when the type is a child of the type belonging to the given mirror.
		 */
		virtual bool IsDerivedOf(const mirror& base) const pure;

		/** @brief Determines if the Type is inherited by the given Type.
		 * @param derived A mirror that can be used to identify the type expected in the chain of inheritance.
		 * @return True when the type is a parent of the type belonging to the given mirror.
		 */
		virtual bool IsBaseOf(const mirror& derived) const pure;

		/** @brief Determines if the Type can be constructed as an object.
		 */
		virtual bool IsConstructible() const pure;

		/** @brief Determines if the Type is represented as pure namespace, which is always static and can never be constructed.
		 */
		virtual bool IsPureNamespace() const pure;

		/** @brief Determines if an instance of this Type can be copied.
		 */
		virtual bool IsCopyable() const pure;

		/** @brief Determines if this type has public visibility through out the reflection engine.
		 */
		virtual bool IsPublic() const pure;

		/** @brief Determines if the type has hidden visibility.
		 */
		virtual bool IsHidden() const pure;

		/** @brief Determines if the type is a template for new types.
		 */
		virtual bool IsTemplate() const pure;

		/** @brief Determines if this type is a base abstraction for new types.
		 */
		virtual bool IsAbstract() const pure;

		/** @brief Determines if the type is the final abstraction in a chain of inheritance.
		 */
		virtual bool IsFinal() const pure;

		/** @brief Determines if the type is nested inside another type scope.
		 */
		virtual bool IsNested() const pure;


		virtual bool IsParent() const pure;
		virtual bool IsChild() const pure;

		/** @brief Gets the assembly where the type is located.
		 */
		virtual Assembly* GetAssembly() const pure;

		/** @brief Gets all the types that inherit this type.
		 */
		virtual Array<Type*> GetChildren() const pure;

		/** @brief Gets all the types that are inherited by this type.
		 */
		virtual Array<Type*> GetParents() const pure;

		/** @brief Gets all the types nested within this type, including non-constructible static types.
		 */
		virtual Array<Type*> GetNestedNamespaces() const pure;

		/** @brief Gets all the types nested within this type, including non-constructible static types.
		 */
		virtual Array<Type*> GetNestedTypes() const pure;

		/** @brief Gets the type (or namespace) where the type is nested.
		 */
		virtual Type* GetDirectory() const pure;

		/** @brief Gets the type information for a type that has the given mirror.
		 */
		static Type* GetType(const mirror& typeName);  // Implementation: see [Ngen.Reflection]+Ngen.Reflection.AssemblyInfo.cpp
	};
}
#endif // __NGEN_TYPE_HPP
