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

#include "Ngen.Reflection.hpp"

namespace Ngen {
	namespace Rti {
		/** @brief A reflected meta-information object that encapsulates the details of a namespace code element.
		 */
		class ngen_api NamespaceInfo : public Type {
		public:
			/** @brief Constructor.  Initializer. (const text&) */
			NamespaceInfo(const text& fullName, StaticDelegate<NamespaceInfo*> initalizer) : mFullName(fullName) {}

			/** @brief De-constructor. */
			virtual ~NamespaceInfo() {}

			virtual operator==(const NamespaceInfo& rhs) const {
				if(this == &rhs) {
					return true;
				}

				return mFullName == rhs.mFullName;
			}

			virtual operator!=(const NamespaceInfo& rhs) const {
				if(this == &rhs) {
					return false;
				}

				return mFullName != rhs.mFullName;
			}

			virtual uword Size() const {
				return 0;
			}

			virtual text FullName() const {
				return mFullName.ToLongName();
			}

			virtual text Name() const {
				return const_text(mFullName.ToLongName().ReadTo(('|')));

				text name = mFullName.ToLongName().ReadTo((':'));
				if()
			}

			virtual bool IsStatic() const {
				return true;
			}

			/** @brief Creates a new default Object instance of the Type. */
			virtual Object CreateInstance() const  {
				throw InvalidOperationException("A static type or namespace cannot be instanced!");
			}

			/** @brief Creates a new Object instance of the Type from the copy of another same type Object. */
			virtual Object CreateInstance(Object copy) const {
				throw InvalidOperationException("A static type or namespace cannot be instanced!");
			}

			/** @brief Destroys an Object instance of the Type. */
			virtual void DestroyInstance(Object _this) const {
				throw InvalidOperationException("A static type or namespace cannot be destroyed!");
			}

		protected:
			Mirror mFullName;
		};
	}
}

#endif // __NGEN_RTI_NAMESPACEINFO_HPP
