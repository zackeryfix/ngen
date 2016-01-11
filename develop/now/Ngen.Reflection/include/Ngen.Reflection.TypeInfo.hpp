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
			virtual TypeInfo() : NamspaceInfo(), mSize(0), mMemberFields(), mMemberMethods(), mConstructors(), mDeconstructor(), mChildren(), mParents() {
			}

			/** @brief Constructor. Copy. (const TypeInfo&)
			 */
			virtual TypeInfo(const TypeInfo& copy) : NamespaceInfo((const NamespaceInfo&)copy),
               mSize(copy.mSize), mMemberFields(copy.mMemberFields), mMemberMethods(copy.mMemberMethods),
               mConstructors(copy.mConstructors), mDeconstructor(copy.mDeconstructor),
               mChildren(copy.mChildren), mParents(copy.mParents) {
					this->pUnmute();
			}

			virtual TypeInfo(TypeInfo&& move) : NamespaceInfo((NamespaceInfo&&)move), mSize(move.mSize),
            mMemberFields(mref(move.mMemberFields)), mMemberMethods(mref(move.mMemberMethods)),
            mConstructors((mref(move.mConstructors)), mDeconstructor(mref(move.mDeconstructor)),
            mChildren(mref(move.mChildren)), mParents(mref(move.mParents)) {
         }

			/** @brief operator=(const TypeInfo&) */
			virtual TypeInfo& operator=(const TypeInfo& rhs) {
				if(this == &rhs || this->mFullName == rhs.mFullName) {
					return *this;
				}

				this->TypeInfo(rhs);
				return *this;
			}

			/** @brief operator=(const TypeInfo&) */
			virtual TypeInfo& operator=(TypeInfo&& rhs) {
				if(this == &rhs || this->mFullName == rhs.mFullName) {
					return *this;
				}

				this->TypeInfo(rhs);
				return *this;
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
				return mTraits[ETrait::Static];
			}

			/** @brief Determines if the namespace is constructable.
			 * @remarks A pure namespace will never be constructable. However, a pure type can be both
			 * static or constructable.
			 */
			virtual bool IsConstructable() const {
				return pHasDefaultCtor();
			}

			/** @brief Determines if the type is public. */
			virtual bool IsPublic() const {
				return mTraint[ETrait::Public];
			}

			/** @brief Determines if the type is protected. */
			virtual bool IsProtected() const {
				return mTraits[ETrait::Protected];
			}

			/** @brief Determines if the type is private. */
			virtual bool IsPrivate() const {
				return mTraits[ETrait::Private];
			}

			/** @brief Determines if the type is a template for new types. */
			virtual bool IsTemplate() const {
				return mTraits[ETrait::Template];
			}

			/** @brief Determines if the type is a base abstraction for new types. */
			virtual bool IsAbstract() const {
				return mTraits[ETrait::Abstract];
			}

			/** @brief Determines if the type is a virtual interface for new types. */
			virtual bool IsVirtual() const {
				return mTraits[ETrait::Virtual];
			}

			/** @brief Determines if the type is hidden from external processes. */
			virtual bool IsHidden() const {
				return mTraits[ETrait::Hidden];
			}

			/** @brief Determines if the type is the final abstraction in a chain of inheritance. */
			virtual bool IsFinal() const {
				return mTraits[ETrait::Final];
			}

			/** @brief Determines if the type is nested inside a namespace or another type. */
			virtual bool IsNested() const {
				return !isnull(this->mScope);
			}

			/** @brief Creates a new default Object instance of the Type.
			 * @return An object created in heap-bound memory.
			 */
			Object NewInstance() const  {
				Constructor* ctor = null;
				if(!pHasCtorKind(EConstructorKind::Default)) {
					THROW(InvalidOperationException("Unable to create an object from a non-constructable type."));
				}

				return Object(ctor->Ctor.Call(void_t, 1), this, false);
			}

			/** @brief Creates a new default Object instance of the Type.
			 * @param data An unknown pointer that represent the data for the instance.
			 * @param stackBound Determines if the object is stack bound, or heap bound.
			 * @return An constant object created from stack bound memory.
			 * @remarks A heap-bound instance will be referenced counted and destroyed when not used. Optionally,
			 * the object can be destroyed at any time.
			 */
			Object NewInstance(unknown data, bool stackBound = true) const  {
				return Object(ptr, this, stackBound);
			}

			/** @brief Creates a new Object instance of the Type from the copy of another same type Object. */
			Object CopyInstance(Object copy) const {
				return Object(copy, false);
			}

			/** @brief Destroys an Object instance of the Type.
			 * @remarks
			 */
			void DestroyInstance(Object _this) const {
				if(!_this.IsConst()) {
					mDeconstructor(_this.UnknownThis(), null);
				} else {
					THROW(InvalidOperationException("Unable to destroy a constant object instance."));
				}
			}

			/** @brief Determines if the Type is a base and does not inherit another type. */
			virtual bool IsBase() const {
				return IsParent() && !IsChild(); // child |= parent
			}

			/** @brief Determines if the Type is considered a primitive structure. */
			virtual bool IsPrimitive() const {
				return mTraits[ETrait:::Primitive];
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
				return mChildren.AsType<Type*>();
			}

			virtual Array<Type*> GetParents() const {
				return mParents.AsType<Type*>();
			}

         TypeInfo* Initialize(NamespaceInfo* directory, const mirror& typeName, uword size, typename StaticDelegate<TypeBuilder>::TFunction initializer) {
				this->pMute();
				this->mName(typeName);
            this->mFullName(directory->mFullName.ToLongName() + '@' + typeName.ToLongName());
            this->mAssembly(directory->mAssembly);
            this->mDirectory(directory);
            this->mSize = size;
				initializer(TypeBuilder(this));
				this->pUnmute();
				return this;
			}
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

			friend class Assembly;
			friend class AssmeblyInfo;
			friend class TypeBuilder;
		};
	}

#endif // __RTI_TYPEINFO_HPP
