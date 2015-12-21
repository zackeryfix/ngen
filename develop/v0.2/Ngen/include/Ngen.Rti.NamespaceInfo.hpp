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
#ifndef __RTI_NAMESPACEINFO_HPP
#define __RTI_NAMESPACEINFO_HPP

#include "Ngen.Rti.MethodInfo.hpp"

namespace Ngen {
	namespace Rti {
		/** @brief A reflected meta-information object that encapsulates the details of a namespace code element.
		 */
		class ngen_api NamespaceInfo : public Type {
		public:
			/** @brief Constructor.  Initializer. (const mirror&, (void)(NamespaceDescriptor)*) */
			NamespaceInfo(Assembly* lib, NamespaceInfo* scope, const mirror& name, StaticDelegate<NamespaceBuilder>::TFunction initalizer) :
				mModiferFlag(_tkn_Mute), mAssembly(lib), mScope(scope), mName(relativeName), mFullName(), mStaticMethods(1) {
				initalizer(&NamespaceBuilder(this));
				pUnmute();
				pParseMirror();
			}

			/** @brief De-constructor. */
			virtual ~NamespaceInfo() {}

			/** @brief operator==(const NamespaceInfo&) */
			virtual operator==(const NamespaceInfo& rhs) const {
				if(this == &rhs) {
					return true;
				}

				return mFullName == rhs.mFullName;
			}

			/** @brief operator!=(const NamespaceInfo&) */
			virtual operator!=(const NamespaceInfo& rhs) const {
				if(this == &rhs) {
					return false;
				}

				return mFullName != rhs.mFullName;
			}

			/** @brief Gets the size (in bytes) of the namespace. */
			virtual uword Size() const {
				return 0;
			}

			/** @brief  Gets the full mirrored name of the namespace. */
			virtual mirror FullName() const {
				return mFullName;
			}

			/** @brief Gets the short-hand name of the namespace. */
			virtual mirror Name() const {
				return mRelativeName;
			}

			/** @brief Determines if the namespace is a pure namespace.
			 * @remarks Remember, a pure type is also a namespace, but not a 'pure' namespace.
			 */
			virtual bool IsPureNamespace() const {
				return true;
			}

			/** @brief Determines if the namespace is static.
			 * @remarks A pure namespace will always be static, but will never be constructable. However, a pure class can be both
			 * static or constructable.
			 */
			virtual bool IsStatic() const {
				return true;
			}

			/** @brief Determines if the namespace is constructable.
			 * @remarks A pure namespace will never be constructable. However, a pure class can be both
			 * static or constructable.
			 */
			virtual bool IsConstructable() const {
				return false;
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
				return false;
			}

			/** @brief Determines if the type is a base abstraction for new types. */
			virtual bool IsAbstract() const {
				return false;
			}

			/** @brief Determines if the type is a virtual interface for new types. */
			virtual bool IsVirtual() const {
				return false;
			}

			/** @brief Determines if the type is hidden from external processes. */
			virtual bool IsHidden() const {
				return (this->mModifierFlag & EModifierFlags::Hidden);
			}

			/** @brief Determines if the type is the final abstraction in a chain of inheritance.
			 */
			virtual bool IsFinal() const {
				return true;
			}

			/** @brief Determines if the type is nested within the scope of another type or namespace.
			 */
			virtual bool IsNested() const {
				return !isnull(mDirectory);
			}

			virtual Object NewInstance() const  {
				THROW(InvalidOperationException("A static type or namespace cannot be instanced!"));
			}

			virtual Object NewInstance(Object copy) const {
				THROW(InvalidOperationException("A static type or namespace cannot be instanced!"));
			}

			virtual Object NewInstance(unknown data, bool stackBound = true) const {
				THROW(InvalidOperationException("A static type or namespace cannot be instanced!"));
			}

			virtual Object CopyInstance(Object copy) const {
				THROW(InvalidOperationException("A static type or namespace cannot be instanced!"));
			}


			virtual void DestroyInstance(Object _this) const {
				THROW(InvalidOperationException("A static type or namespace cannot be destroyed!"));
			}

			virtual bool IsChildOf(const mirror& parent) const {
				return false;
			}

			virtual bool IsParentOf(const mirror& child) const {
				return false;
			}

			Assembly* GetAssembly() const {
				return this->mAssembly;
			}

			virtual Array<Type*> GetChildren() const {
				return Array<Type*>();
			}

			virtual Array<Type*> GetParents() const {
				return Array<Type*>();
			}

			virtual Array<Type*> GetNested() const {
				return mNested.Recasted<Type*>();
			}

			virtual Type* GetDirectory() const {
				return (Type*)mDirectory;
			}
		protected:
			/** @brief Constructor.  Initializer. (const mirror&) */
			NamespaceInfo(Assembly* lib, NamespaceInfo* scope, const mirror& fullName) :
				mModifierFlag(true), mAssembly(lib), mDirectory(scope), mFullName(fullName), mStaticMethods(1) {
			}

			void pMute() {
				mModifierFlag |= _tkn_Mute;
			}

			void pUnmute() {
				mModifierFlag &= ~_tkn_Mute;
			}

			bool pIsMuted() const {
				return (mModifierFlag & _tkn_Mute);
			}

			void pParseMirror() const {
				if(IsNested()) {
					text sep = this->IsPureNamespace() ?
						const_text((char)EMirrorPart::NamespaceSeperator) :
						const_text((char)EMirrorPart::TypeSeperator);
					mFullName = text((text&&) mDirectory->FullName().ToLongName() + sep + Name().ToLongName());
				} else {
					mFullName = text((text&&)Name().ToLongName());
				}
			}

			uword mModifierFlag;
			Assembly* mAssembly;
			NamespaceInfo* mDirectory;
			mirror mName;
			mirror mFullName;
			MethodMap mStaticMethods;
			NamespacePtrMap mNested;

			friend class Assembly;
			friend class TypeBuilder;
			friend class NamespaceBuilder;
		};
	}
}

#endif // __NGEN_RTI_NAMESPACEINFO_HPP
