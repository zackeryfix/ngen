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
#ifndef __NGEN_REFLECTION_NAMESPACEINFO_HPP
#define __NGEN_REFLECTION_NAMESPACEINFO_HPP

#include "Ngen.Reflection.MethodInfo.hpp"
#include "Ngen.Reflection.FieldInfo.hpp"
#include "Ngen.Reflection.NamespaceBuilder.hpp"
#include "Ngen.Reflection.ETrait.hpp"

namespace Ngen {
	namespace Reflection {
		/** @brief A reflected meta-information object that encapsulates the details of a namespace code element.
		 */
		class ngen_api NamespaceInfo : public Type {
		public:
		   /** @brief Constructor.  Initializer. (const mirror&, (void)(NamespaceDescriptor)*) */
			NamespaceInfo() : mIsMuted(false), mTraits(), mAssembly(null), mDirectory(null),
				mFullName(), mStaticFieldMap(), mStaticMethodMap(), mNestedNamespaceMap(), mNestedTypeMap() {
			}

			NamespaceInfo(const NamespaceInfo& copy) : mIsMuted(copy.mIsMuted), mTraits(copy.mTraits),
            mAssembly(copy.mAssembly), mDirectory(copy.mDirectory), mFullName(copy.mFullName), mName(copy.mName),
				mStaticFieldMap(copy.mStaticFieldMap), mStaticMethodMap(copy.mStaticMethodMap),
				mNestedNamespaceMap(copy.mNestedNamespaceMap), mNestedTypeMap(copy.mNestedTypeMap) {
			}

         NamespaceInfo(NamespaceInfo&& move) : mIsMuted(move.mIsMuted), mTraits(move.mTraits),
            mAssembly(move.mAssembly), mDirectory(move.mDirectory), mFullName(mref(move.mFullName)), mName(mref(move.mName)),
				mStaticFieldMap(mref(move.mStaticFieldMap)), mStaticMethodMap(mref(move.mStaticMethodMap)),
				mNestedNamespaceMap(mref(move.mNestedNamespaceMap)), mNestedTypeMap(mref(move.mNestedTypeMap)) {
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
				return mName;
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
			virtual bool IsConstructible() const {
				return false;
			}

			/** @brief Determines if the type is public. */
			virtual bool IsPublic() const {
				return true;
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
				return false;
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

			virtual bool IsDerivedOf(const mirror& base) const {
				return false;
			}

			virtual bool IsBaseOf(const mirror& inherited) const {
				return false;
			}

			Assembly* GetAssembly() const {
				return (Assembly*)this->mAssembly;
			}

			virtual Array<Type*> GetChildren() const {
				return Array<Type*>();
			}

			virtual Array<Type*> GetParents() const {
				return Array<Type*>();
			}

			virtual Array<Type*> GetNestedNamespaces() const {
            auto result = Array<Type*>(mNestedNamespaceMap.Length());
            auto kv = mNestedNamespaceMap.Begin();
            while(kv != mNestedNamespaceMap.End()) {
               result.Add((Type*)&kv->Value);
               kv++;
            }

            return result;
			}

			virtual Array<Type*> GetNestedTypes() const {
            auto result = Array<Type*>(mNestedTypeMap.Length());
            auto kv = mNestedTypeMap.Begin();
            while(kv != mNestedTypeMap.End()) {
               result.Add((Type*)&kv->Value);
               kv++;
            }

            return result;
			}

			virtual Type* GetDirectory() const {
				return (Type*)mDirectory;
			}

         /** @brief Constructor.  Initializer. (const mirror&, (void)(NamespaceDescriptor)*) */
         NamespaceInfo* Initialize(AssemblyInfo* assmebly, NamespaceInfo* directory, const mirror& relativeName, const mirror& fullName, VoidStaticDelegate<NamespaceBuilder>::TFunction initalizer) {
            pMute();
            mName(relativeName);
            mFullName(fullName);
            mAssembly(assembly);
            mDirectory(directory);
				initalizer(NamespaceBuilder(this));
				pUnmute();
				return this;
			}

			 /** @brief Constructor.  Initializer. (const mirror&, (void)(NamespaceDescriptor)*) */
         NamespaceInfo* Initialize(AssemblyInfo* assmebly, NamespaceInfo* directory, const mirror& relativeName, VoidStaticDelegate<NamespaceBuilder>::TFunction initalizer) {
            pMute();
            mName(relativeName);
            mFullName(directory->FullName().ToLongName() + ':' + relativeName.ToLongName());
            mAssembly(assembly);
            mDirectory(directory);
				initalizer(NamespaceBuilder(this));
				pUnmute();
				return this;
			}
		protected:
			void pMute() { mIsMuted = true; }
			void pUnmute() { mIsMuted = false; }
         bool pIsMuted() const { return mIsMuted; }

         bool                       mIsMuted;
			mirror                     mName;
			mirror                     mFullName; // created during construction
			string                     mDescription;
			AssemblyInfo*              mAssembly;
			NamespaceInfo*             mDirectory;
			Map<Mirror, FieldInfo>     mStaticFieldMap;
			Map<Mirror, MethodInfo>    mStaticMethodMap;
			Map<Mirror, NamespaceInfo> mNestedNamespaceMap;
         Map<Mirror, TypeInfo>      mNestedTypeMap;
         Array<Attribute>           mCustomAttributes;          // all the custom attributes found inside the assembly

         friend class Assembly;
			friend class AssemblyInfo;
			friend class TypeBuilder;
			friend class NamespaceBuilder;
		};
	}
}

#endif // __NGEN_RTI_NAMESPACEINFO_HPP
