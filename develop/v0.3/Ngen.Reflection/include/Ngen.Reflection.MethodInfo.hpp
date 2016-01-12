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
#ifndef __NGEN_RTI_METHODINFO_HPP
#define __NGEN_RTI_METHODINFO_HPP

#include "Ngen.Reflection.MethodBuilder.hpp"

namespace Ngen {
	namespace Reflection {
		/** @brief A meta-data object used to retain the reflected type information of a method or function. */
		class ngen_api MethodInfo : public Delegate {
		public:

			/** @brief Constructor. Default. */
			MethodInfo() :	mIsMuted(false), mTraits(), mDirectory(0), mName(), mFullName(), mFunction(0), mReturn(0), mParams(0) {}

			/** @brief Constructor. Copy. */
			MethodInfo(const MethodInfo& copy) :
				mIsMuted(false), mTraits(copy.mTraits), mDirectory(copy.mDirectory),
				mName(copy.mName), mFullName(copy.mFullName), mFunction(copy.mFunction), mReturn(copy.mReturn), mParams(copy.mParams) {}

         ~MethodInfo() {

         }

			/** @brief operator==(const MethodInfo&) */
			bool operator==(const MethodInfo& rhs) const {
				return mFullName == rhs.mFullName && mFunction->EqualTo(rhs.mFunction);
			}

			/** @brief operator!=(const MethodInfo&) */
			bool operator!=(const MethodInfo& rhs) const {
				return mFullName != rhs.mFullName || !mFunction->EqualTo(rhs.mFunction);
			}

			/** @brief operator()(unknown, unknown*) */
			unknown operator()(unknown _this, unknown* params) const {
				return mFunction->operator()(_this, params);
			}

			/** @brief operator()(Object, Object*). */
			Object operator()(Object _this, Object* params) const {
				unknown set[mFunction->Length()];
            for(uword i = 0; i < mFunction->Length(); ++i) {
               set[i] = params[i].UnknownThis();
            }

            unknown result = mFunction->operator()(_this.UnknownThis(), set);
            return IsNonVoid() ?
               Object::New(result, ReturnType()) :
               Object::Null();
			}

         virtual bool EqualTo(Delegate* rhs) const {
            if((Delegate*)this == rhs || this->mFunction == rhs) {
               return true;
            }

            return mFunction->EqualTo(rhs);
         }

         void SetOwner(unknown _this) {
            mFunction->SetOwner(_this);
         }

         bool IsValid() const {
            return mFunction->IsValid();
         }

			mirror FullName() const {
            return mFullName;
			}

			mirror Signature() const {
            return mName;
			}

			Assembly* Assembly() const;

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
				return mTraits[EMethodTrait::Public];
			}

			/** @brief Determines if the type is protected. */
			bool IsProtected() const {
				return mTraits[EMethodTrait::Protected];
			}

			/** @brief Determines if the type is private. */
			bool IsPrivate() const {
				return mTraits[EMethodTrait::Private];
			}

			/** @brief Determines if the type is a template for new types. */
			bool IsTemplate() const {
				return mTraits[EMethodTrait::Template];
			}

			/** @brief Determines if the type is a base abstraction for new types. */
			bool IsAbstract() const {
				return mTraits[EMethodTrait::Abstract];
			}

			/** @brief Determines if the type is a virtual interface for new types. */
			bool IsVirtual() const {
				return mTraits[EMethodTrait::Virtual];
			}

			/** @brief Determines if the type is hidden from external processes. */
			bool IsHidden() const {
				return mTraits[EMethodTrait::Hidden];
			}

			/** @brief Determines if the type is the final abstraction in a chain of inheritance. */
			bool IsFinal() const {
				return mTraits[EMethodTrait::Final];
			}

			/** @brief Gets the number of parameters in the function. */
			uword Length() const {
				return mFunction->Length();
			}

			/** @brief Gets the reflected name of the underlying functions return type. */
			Type* ReturnType() const {
				return (Type*)mReturn;
			}

			/** @brief Gets the size (in bytes) of the underlying functions return type. */
			uword ReturnSize() const {
				return mFunction->ReturnSize();
			}

         template<typename TSelf, typename TReturn, typename... TParams>
         TReturn SafeCall(TSelf* self, TParams... params) {
            unknown tmp[sizeof...(TParams)] {
               (Cast<TParams>::To(params))...
            };

            return Cast<TReturn>::From(this->operator()(self, tmp));
         }

         /** @brief Constructor. (NamespaceInfo*, const string&, Delegate*). */
			MethodInfo* Initialize(NamespaceInfo* directory, const mirror& signature, Delegate* function, VoidStaticDelegate<MethodBuilder>::TFunction initializer);
		protected:
			void pMute() {
				mIsMuted = true;
			}

			void pUnmute() {
				mIsMuted = false;
			}

			bool pIsMuted() const {
				return mIsMuted;
			}

			bool                 mIsMuted;
			MethodTraitFlags     mTraits;
			NamespaceInfo*       mDirectory;
			mirror               mName;
			mirror               mFullName;
			string               mDescription;
			Delegate*            mFunction;
			TypeInfo*            mReturn;
			Array<ParameterInfo> mParams;

			friend class MethodBuilder;
			friend class NamespaceBuilder;
			friend class TypeBuilder;
		};
	}
}

#endif // __RTI_METHODINFO_HPP
