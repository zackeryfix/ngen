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
#ifndef __NGEN_RTI_TYPEINFO_HPP
#define __NGEN_RTI_TYPEINFO_HPP

#include "Ngen.NamespaceInfo.hpp"

namespace Ngen {
	namespace Rti {
		/** @brief Represents reflected information detailing an object type.
		 */
		class ngen_api TypeInfo : public NamespaceInfo {
		public:
			/** @brief A data structure used to bind meta-data to a constructor method of a Type. */
			virtual class ngen_api Constructor {
			public:
				Constructor(MethodInfo method, EConstructorKind kind) : Ctor(method), Kind(kind) {
				}

				MethodInfo Ctor;
				EConstructorKind Kind;
			};

			typedef Map<EConstructorKind, Constructor> CtorMap;


			/** @brief Constructor. Initializer. */
			virtual TypeInfo(NamespaceInfo* scope, const mirror& typeName, uword size, typename StaticDelegate<TypeBuilder>::TFunction initializer) :
					NamspaceInfo(scope->mAssembly, scope, typeName), mSize(size),
					mMemberMethods(), mStaticMethods(), mCtorMethods(), mDtor(), mParent(scope) {
				this->pMute();
				initializer(TypeBuilder(this));
				this->pUnmute();
			}

			/** @brief Constructor. Copy. (const TypeInfo&)
			 */
			virtual TypeInfo(const TypeInfo& copy) : NamespaceInfo(copy.Assembly(), copy.Scope(), copy.FullName()),
					mSize(copy.mSize), mMemberMethods(copy.mMemberMethods), mStaticMethods(copy.mStaticMethods),
					mCtorMethods(copy.mCtorMethods), mDtor(copy.mDtor) {
					this->pUnmute();
			}

			/** @brief operator=(const TypeInfo&) */
			virtual TypeInfo& operator=(const TypeInfo& rhs) {
				if(this == &rhs || this->mFullName == rhs.mFullName) {
					return;
				}
			}

			/** @brief Gets the size (in bytes) of the type. */
			virtual uword Size() const {
				return mSize;
			}

			/** @brief Gets the short-hand name of the type. */
			virtual text Name() const {

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
				return (this->mModifierFlag & EModifierFlags::Static);
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
				return (this->mModifierFlag & EModifierFlags::Public);
			}

			/** @brief Determines if the type is protected. */
			virtual bool IsProtected() const {
				return (this->mModifierFlag & EModifierFlags::Protected);
			}

			/** @brief Determines if the type is private. */
			virtual bool IsPrivate() const {
				return (this->mModifierFlag & EModifierFlags::Private);
			}

			/** @brief Determines if the type is a template for new types. */
			virtual bool IsTemplate() const {
				return (this->mModifierFlag & EModifierFlags::Template);
			}

			/** @brief Determines if the type is a base abstraction for new types. */
			virtual bool IsAbstract() const {
				return (this->mModifierFlag & EModifierFlags::Abstract);
			}

			/** @brief Determines if the type is a virtual interface for new types. */
			virtual bool IsVirtual() const {
				return (this->mModifierFlag & EModifierFlags::Virtual);
			}

			/** @brief Determines if the type is hidden from external processes. */
			virtual bool IsHidden() const {
				return (this->mModifierFlag & EModifierFlags::Hidden);
			}

			/** @brief Determines if the type is the final abstraction in a chain of inheritance. */
			virtual bool IsFinal() const {
				return (this->mModifierFlag & EModifierFlags::Final);
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
w
			}

			/** @brief Destroys an Object instance of the Type.
			 * @remarks
			 */
			void DestroyInstance(Object _this) const {
				if(!_this.IsConst()) {
					mDeconstructor.Call(_this.This());
					pInvalidate(_this);
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
				return (this->mModifierFlag & EModifierFlags::Primitive);
			}

			/** @brief Determines if the Type inherits the given Type. */
			virtual bool IsChildOf(const mirror& parent) const {
				for(uword i = 0; i < mParents; ++i) {
					if(mParents.Begin(i)->FullName() == parent) {
						return true;
					}
				}
			}

			/** @brief Determines if the Type has been inherited by the given Type. */
			virtual bool IsParentOf(const mirror& child) const {
				for(uword i = 0; i < mChildren; ++i) {
					if(mChildren.Begin(i)->mFullName == child) {
						return true;
					}
				}

				return false;
			}

			virtual Array<Type*> GetChildren() const {
				return mChildren.OfType<Type*>();
			}

			virtual Array<Type*> GetParents() const {
				return mParents.OfType<Type*>();
			}

		protected:
			bool pHasDefaultCtor() const {
				return pHasCtorKind(EConstructorKind::Default);
			}

			bool pHasCopyCtor() const {
				return pHasCtorKind(EConstructorKind::Copy);
			}

			bool pHasMoveCtor() const {
				return pHasCtorKind(EConstructorKind::Move);
			}

			bool pHasCtorKind(EConstructorKind kind) const {
				Constructor* ctor;
				return pHasCtorKind(kind, inref ctor);
			}

			bool pHasCtorKind(EConstructorKind kind, Constructor*& ctor) const {
				if(mCtorMethods.Length() == 0) {
					return false;
				}

				typename CtorMap::Node* begin = mCtorMethods.Begin();
				while(!isnull(begin)) {
					Constructor* value = begin->Data()->Value;
					if(value->Kind == kind) {
						return true;
					}

					begin = begin->Next();
				}

				return false;
			}

			void pMute() const {
				this->mIsMutable = true;
			}

			void pUnmute() const {
				this->mIsMutable = false;
			}

			bool mIsPrimitive;
			uword mSize;
			MethodMap mMemberMethods;
			CtorMap mConstructors;
			MethodInfo mDeconstructor;
			TypePtrMap mChildren;
			TypePtrMap mParents;

			friend class Assembly;
			friend class TypeBuilder;
		};
	}

#endif // __RTI_TYPEINFO_HPP
