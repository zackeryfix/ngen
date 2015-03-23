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
#ifndef __NGEN_ATTRIBUTE_HPP
#define __NGEN_ATTRIBUTE_HPP

#include "Ngen.Mirror.hpp"
#include "Ngen.Array.hpp"

namespace Ngen {
	class ngen_api Attribute {
	public:
		Attribute(const mirror& identity) : mIdentity(identity) {}
		Attribute(const mirror& identity, const Array<mirror>& parents) : mIdentity(identity), mParents(parents) {}
		Attribute(const Attribute& copy) : mIdentity(copy.mIdentity), mParents(copy.mParents) {}

		bool operator==(const Attribute& rhs) const {
			return rhs.mIdentity == this->mIdentity;
		}

		bool operator!=(const Attribute& rhs) const {
			return rhs.mIdentity != this->mIdentity;
		}

		/** @brief Determines if the attribute inherited another attribute. */
		bool IsTypeOf(const mirror& identity) const {
			for(uword i = 0; i < mParents.Length(); ++i) {
				if(mParents->Begin(i)->mIdentity == identity) {
					return true;
				} else if(mParents->Begin(i)->IsTypeOf(identity)) {
					return true;
				}
			}

			return false;
		}
	protected:
		mirror mIdentity;
		Array<Attribute*> mParents;
	};
}
#endif // __NGEN_ATTRIBUTE_HPP
