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
#ifndef __NGEN_ATTRIBUTE_HPP
#define __NGEN_ATTRIBUTE_HPP

#include "Ngen.Object.hpp"

namespace Ngen {
	/** @brief An attribute is a custom external property that can be assigned to any code element, such as
	 * a type definition or method argument.  These are not restricted to any kind of RTI element, and any
	 * Type can be an attribute.
	 */
	class ngen_api Attribute {
	public:
	   /** @brief */
	   Attribute(unknown rti, const Type* attributeType) : mRTI(rti), mData(Object::Null()) {}

		/** @brief */
		bool operator==(const Attribute& rhs) const {
         return (this->RTI() == rhs.RTI() &&
                 this->Data() == rhs.Data());
		}

		/** @brief */
		bool operator!=(const Attribute& rhs) const {
         return (this->RTI() != rhs.RTI() ||
                 this->Data() != rhs.Data());
		}

		/** @brief Gets the reflected type information element bound to this attribute. */
		unknown RTI() const { return mRTI; }

		/** @brief Gets the type information that the custom data for the attribute was created from. */
		const Type* Type() const { return mData.GetType(); }

		/** @brief Gets the custom object representing this attribute's data. */
		Object Data() const { return mData; }

   protected:
      unknown mRTI;
      Object mData;
	};
}
#endif // __NGEN_ATTRIBUTE_HPP
