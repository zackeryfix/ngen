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
			/** @brief Constructor. Initializer. */
			TypeInfo(const text& fullName, typename StaticDelegate<TypeInfo*>::TFunction initializer) : NamspaceInfo(fullName) {
				initializer(this);
			}

			/** @brief Constructor. Copy. (const TypeInfo&)
			 */
			TypeInfo(const TypeInfo& copy) : NamespaceInfo(copy.mFullName) {}


			/** @brief operator=(const TypeInfo&) */
			TypeInfo& operator=(const TypeInfo& rhs) {
				if(this == &rhs || this->mFullName == rhs.mFullName) {
					return;
				}
			}

		protected:


			friend class Reflection;
		};
	}

#endif // __RTI_TYPEINFO_HPP
