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
#ifndef __NGEN_RTI_METHODINFO_HPP
#define __NGEN_RTI_METHODINFO_HPP

#include "Ngen.Reflection.MethodBuilder.hpp"

namespace Ngen {
	namespace Reflection {
		/** @brief A meta-data object used to retain the reflected type information of a method or function. */
		class MethodInfo : public Delegate {
		public:
			/** @brief Constructor. Default. */
			MethodInfo() : mModifierFlag(0), mScope(0), mSignature(), mFunction(0) {}

			/** @brief Constructor. (NamespaceInfo*, const text&, Delegate*). */
			MethodInfo(NamespaceInfo* scope, const text& signature, Delegate* function, StaticDelegate<MethodBuilder>::TFunction initializer) :
				mIsMuted(true), mTraits(), mScope(scope), mFunction(function), mSignature(signature) {
				initializer(MethodBuilder(this));
				pUnmute();
			}

			/** @brief Constructor. Copy. */
			MethodInfo(const MethodInfo& copy) :
				mScope(copy.mScope), mSignature(copy.mSignature), mFullName(copy.mFullName) mFunction(copy.mFunction) {}

			/** @brief operator==(const MethodInfo&) */
			bool operator==(const MethodInfo& rhs) const {
				return mSignature == rhs.mSignature && mFunction->EqualTo(rhs.mFunction);
			}

			/** @brief operator!=(const MethodInfo&) */
			bool operator!=(const MethodInfo& rhs) const {
				return mSignature != rhs.mSignature || !mFunction->EqualTo(rhs.mFunction);
			}

			/** @brief operator()(unknown, unknown*) */
			unknown operator()(unknown _this, unknown* params) {
				return mFunction(_this, params);
			}

			/** @brief operator()(Object, Object*). */
			Object operator()(Object _this, Object* params) {
				return _Call(params, typename make_index_pack_t<sizeof...(TParams)>::type());
			}

			mirror FullName() const {
				return text::Empty(); // ODO: Calc full name

			}

			mirror Signature() const {
				return mSignature;
			}

			/** @brief Determines if the method represents a member function. */
			bool IsMember() const {
				return mFunction->IsMember();
			}

			/** @brief Determines if the method represents a static function. */
			bool IsStatic() const {
				return !mFunction->IsMember();
			}

			/** @brief Determines if the method represents a const-member function. */
			bool IsConst() const {
				return mFunction->IsConst();
			}

			/** @brief Determines if the method represents a function with a non-void return type. */
			bool IsNonVoid() const {
				return mFunction->IsNonVoid();
			}

			/** @brief Determines if the type is public. */
			bool IsPublic() const {
				return mTraits[ETrait::Public];
			}

			/** @brief Determines if the type is protected. */
			bool IsProtected() const {
				return mTraits[ETrait::Protected];
			}

			/** @brief Determines if the type is private. */
			bool IsPrivate() const {
				return mTraits[ETrait::Private];
			}

			/** @brief Determines if the type is a template for new types. */
			bool IsTemplate() const {
				return mTraits[ETrait::Template];
			}

			/** @brief Determines if the type is a base abstraction for new types. */
			bool IsAbstract() const {
				return mTraits[ETrait::Abstract];
			}

			/** @brief Determines if the type is a virtual interface for new types. */
			bool IsVirtual() const {
				return mTraits[ETrait::Virtual];
			}

			/** @brief Determines if the type is hidden from external processes. */
			bool IsHidden() const {
				return mTraits[ETrait::Hidden];
			}

			/** @brief Determines if the type is the final abstraction in a chain of inheritance. */
			bool IsFinal() const {
				return mTraits[ETrait::Final];
			}

			/** @brief Gets the number of parameters in the function. */
			uword Length() const {
				return mFunction->Length();
			}

			/** @brief Gets the reflected name of the underlying functions return type. */
			const char8* ReturnTypename() const {
				return mFunction->GetReturnType();
			}

			/** @brief Gets the reflected name of the underlying functions return type. */
			mirror ReturnTypeMirror() const {
				return const_mirror(mFunction->ReturnTypename());
			}

			/** @brief Gets the size (in bytes) of the underlying functions return type. */
			uword ReturnSize() const {
				return mFunction->GetReturnSize();
			}


		protected:
			template<uword... I> Object _Call(Object _this, Object* params, index_pack_t<I...>) {
				unknown[mFunction->Length()] p = {
					(params[I].GetPtr())...
				};

				Object ret = Object::Null();
				if(this->IsNonVoid()) {
					ret = Object::From(this->operator()(_this.GetPtr(), p), ReturnTypeMirror());
				} else {
					this->operator()(_this.GetPtr(), p);
				}

				return ret;
			}

			void pMute() {
				mIsMuted = true;
			}

			void pUnmute() {
				mIsMuted = false;
			}

			bool pIsMuted() const {
				return mIsMuted;
			}

			void pParseMirror() {
            //todo:
			}

			bool mIsMuted;
			TraitFlags mTraits;
			NamespaceInfo* mScope;
			mirror mSignature;		//TReturn%NAME(T1%T2)
			mirror mFunctionName;
			mirror mFullName;
			Delegate* mFunction;
			TypeInfo* mReturn;
			Array<TypeInfo*> mParams;
		};
	}
}

#endif // __RTI_METHODINFO_HPP
