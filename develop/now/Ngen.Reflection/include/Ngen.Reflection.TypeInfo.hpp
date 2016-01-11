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
#ifndef __NGEN_REFLECTION_TYPEINFO_HPP
#define __NGEN_REFLECTION_TYPEINFO_HPP

#include "Ngen.Reflection.NamespaceInfo.hpp"
#include "Ngen.Reflection.TypeBuilder.hpp"

namespace Ngen {
	namespace Reflection {
		/** @brief Represents reflected information detailing an object type.
		 */
		class ngen_api TypeInfo : public NamespaceInfo {
		public:
         /** @brief Constructor. Initializer. */
         TypeInfo() : NamespaceInfo(), mSize(0), mMemberMethods(), mMemberFields(), mConstructors(), mDeconstructor(), mChildren(), mParents() {
			}

			/** @brief Constructor. Copy. (const TypeInfo&)
			 */
         TypeInfo(const TypeInfo& copy) : NamespaceInfo((const NamespaceInfo&)copy),
               mSize(copy.mSize), mMemberMethods(copy.mMemberMethods), mMemberFields(copy.mMemberFields),
               mConstructors(copy.mConstructors), mDeconstructor(copy.mDeconstructor),
               mChildren(copy.mChildren), mParents(copy.mParents) {
					this->pUnmute();
			}

         TypeInfo(TypeInfo&& move) : NamespaceInfo((NamespaceInfo&&)move), mSize(move.mSize),
            mMemberMethods(mref(move.mMemberMethods)), mMemberFields(mref(move.mMemberFields)),
            mConstructors(mref(move.mConstructors)), mDeconstructor(move.mDeconstructor),
            mChildren(mref(move.mChildren)), mParents(mref(move.mParents)) {
         }

			/** @brief operator=(const TypeInfo&) */
			virtual TypeInfo& operator=(const TypeInfo& rhs) {
				if(this == &rhs || this->mFullName == rhs.mFullName) {
					return *this;
				}

            *this = TypeInfo(rhs);
				return *this;
			}

			/** @brief operator=(const TypeInfo&) */
			virtual TypeInfo& operator=(TypeInfo&& rhs) {
				if(this == &rhs || this->mFullName == rhs.mFullName) {
					return *this;
				}

				*this = TypeInfo(rhs);
				return *this;
			}

         /** @brief operator==(Type* const) */
         virtual bool operator==(Type* const rhs) const {
            if((Type*)this == rhs) {
					return false;
				}

				return mFullName != rhs->FullName();
         }

         /** @brief operator!=(Type* const) */
         virtual bool operator!=(Type* const rhs) const {
            if((Type*)this == rhs) {
					return false;
				}

				return mFullName == rhs->FullName();
         }

			/** @brief Gets the size (in bytes) of the type. */
			virtual uword Size() const {
				return mSize;
			}

			/** @brief Determines if the type is a pure namespace.
			 * @remarks Remember, a pure type is also a namespace, but not be a 'pure' namespace.
			 */
			virtual bool IsPureNamespace() const {
				return false;
			}

			/** @brief Determines if the namespace is static.
			 * @remarks A pure namespace will always be static, but will never be constructable. However, a pure type can be both
			 * static or constructable.
			 */
			virtual bool IsStatic() const {
				return mTraits[ETypeTrait::Static];
			}

			/** @brief Determines if the namespace is constructable.
			 * @remarks A pure namespace will never be constructable. However, a pure type can be both
			 * static or constructable.
			 */
			virtual bool IsConstructable() const {
				return IsStatic() && mConstructors.Length() != 0;
			}

			/** @brief Determines if the type is public. */
			virtual bool IsPublic() const {
				return mTraits[ETypeTrait::Public];
			}

			/** @brief Determines if the type is a template for new types. */
			virtual bool IsTemplate() const {
				return mTraits[ETypeTrait::Template];
			}

			/** @brief Determines if the type is a base abstraction for new types. */
			virtual bool IsAbstract() const {
				return mTraits[ETypeTrait::Abstract];
			}

			/** @brief Determines if the type is hidden from external processes. */
			virtual bool IsHidden() const {
				return mTraits[ETypeTrait::Hidden];
			}

			/** @brief Determines if the type is the final abstraction in a chain of inheritance. */
			virtual bool IsFinal() const {
				return mTraits[ETypeTrait::Final];
			}

			/** @brief Determines if the type is nested inside a namespace or another type. */
			virtual bool IsNested() const {
				return !isnull(this->mDirectory);
			}

			/** @brief Creates a new default Object instance of the Type.
			 * @return An object created in heap-bound memory.
			 */
			Object NewInstance() const  {

				//TODO:
				return Object::Null();
			}

			/** @brief Creates a new default Object instance of the Type.
			 * @param data An unknown pointer that represent the data for the instance.
			 * @param stackBound Determines if the object is stack bound, or heap bound.
			 * @return An constant object created from stack bound memory.
			 * @remarks A heap-bound instance will be referenced counted and destroyed when not used. Optionally,
			 * the object can be destroyed at any time.
			 */
			Object NewInstance(unknown ptr, bool stackBound = true) const  {
				return Object(ptr, (Type*)this, stackBound); // const to non-const
			}

			/** @brief Creates a new Object instance of the Type from the copy of another same type Object. */
			Object CopyInstance(Object copy) const {
				return Object(copy, false);
			}

			/** @brief Destroys an Object instance of the Type.
			 * @remarks
			 */
			void DestroyInstance(Object _this) const {
				if(!_this.IsNull() && !_this.IsReadonly()) {
					mDeconstructor(_this.UnknownThis(), null);
				} else {
					THROW(InvalidOperationException("Unable to destroy a constant or null object instance."));
				}
			}

			/** @brief Determines if the Type is a base and does not inherit another type. */
			virtual bool IsBase() const {
				return IsParent() && !IsChild(); // child |= parent
			}

         /** @brief Determines if the type is a base abstraction for new types. */
			virtual bool IsParent() const {
				return mChildren.Length() != 0;
			}

			/** @brief Determines if the type is hidden from external processes. */
			virtual bool IsChild() const {
				return mParents.Length() != 0;
			}

			/** @brief Determines if the Type is considered a primitive structure. */
			virtual bool IsPrimitive() const {
				return mTraits[ETypeTrait::Primitive];
			}

			/** @brief Determines if the Type inherits the given Type. */
			virtual bool IsChildOf(const mirror& parent) const {
				return false;
			}

			/** @brief Determines if the Type has been inherited by the given Type. */
			virtual bool IsParentOf(const mirror& child) const {
				return false;
			}

			virtual Array<Type*> GetChildren() const {
				return mChildren.ToPointerMap().Values().AsType<Type*>();
			}

			virtual Array<Type*> GetParents() const {
				return mParents.ToPointerMap().Values().AsType<Type*>();
			}

			virtual Delegate* GetMethod(const mirror& signature) const {
            if(!this->mStaticMethodMap.ContainsKey(signature)) {
               if(!this->mMemberMethods.ContainsKey(signature)) {
                  return null;
               }

               return (Delegate*)&((TypeInfo*)this)->mMemberMethods[signature];
            }

            return (Delegate*)&this->mStaticMethodMap[signature];
			}

			virtual Array<Delegate*> GetStaticMethods() const {
            return this->mStaticMethodMap.ToPointerMap().Values().AsType<Delegate*>();
			}

			virtual Array<Delegate*> GetMemberMethods() const {
            return this->mMemberMethods.ToPointerMap().Values().AsType<Delegate*>();
			}

			virtual Field* GetField(const mirror& signature) const {
            if(!this->mStaticFieldMap.ContainsKey(signature)) {
               if(!this->mMemberFields.ContainsKey(signature)) {
                  return null;
               }

               return (Field*)&this->mMemberFields[signature];;
            }

            return (Field*)&this->mStaticFieldMap[signature];
			}

			virtual Array<Field*> GetStaticFields() const {
            return this->mStaticFieldMap.ToPointerMap().Values().AsType<Field*>();
			}

			virtual Array<Field*> GetMemberFields() const {
            return this->mMemberFields.ToPointerMap().Values().AsType<Field*>();
			}

         TypeInfo* Initialize(NamespaceInfo* directory, const mirror& typeName, uword size, typename VoidStaticDelegate<TypeBuilder>::TFunction initializer);
		protected:
         void pMute() { this->mIsMuted = true; }
         void pUnmute() { this->mIsMuted = false; }
         bool pIsMuted() { return this->mIsMuted; }

         TypeTraitFlags             mTraits;
			uword                      mSize;
			Map<Mirror, MethodInfo>    mMemberMethods;
         Map<Mirror, FieldInfo>     mMemberFields;
			Map<Mirror, MethodInfo>    mConstructors;
			MethodInfo                 mDeconstructor;
			Map<Mirror, TypeInfo*>     mChildren; // types inheriting this
			Map<Mirror, TypeInfo*>     mParents;  // types this inherits

			friend class TypeBuilder;
		};
	}
}
#endif // __RTI_TYPEINFO_HPP
