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

#include "Ngen.BitFlags.hpp"
#include "Ngen.Mirror.hpp"
#include "Ngen.Array.hpp"

namespace Ngen {
   /** @brief
    */
   enum class EAttributeBinding : uword {
      /** @brief */
      TypeBound = 0,

      /** @brief */
      NamespaceBound,

      /** @brief */
      AssmeblyBound,

      /** @brief */
      MethodBound,

      /** @brief */
      EventBound,

      /** @brief */
      //RuntimeBound,

      /** @brief */
      FieldBound,

      /** @brief */
      PropertyBound,

      /** @brief */
      DelegateBound,

      /** @brief */
      ParameterBound,

      /** @brief */
      _COUNT
   };
   typedef BitFlags<EAttributeBinding> AttributeBindingFlags;


	/** @brief An attribute is a custom property that can be assigned to any code element, such as
	 * a type definition or method argument.
	 */
	class ngen_api Attribute {
	public:
	   /** @brief */
	   Attribute() {}

		/** @brief */
		bool operator==(const Attribute& rhs) const {
         return (this->Target() == rhs.Target() &&
                 this->Data() == rhs.Data() &&
                 this->BindingConstraints() == rhs.BindingConstraints());
		}

		/** @brief */
		bool operator!=(const Attribute& rhs) const {
         return (this->Target() != rhs.Target() ||
                 this->Data() != rhs.Data() ||
                 this->BindingConstraints() != rhs.BindingConstraints());
		}


      virtual bool Equals(Attribute* rhs) const pure;

		/** @brief */
		virtual Object& Data() const pure;

		/** @brief Gets the binding flags used to identify the RTI constraints.
		 */
      virtual AttributeBindingFlags BindingConstraints() const pure;

      /** @brief
       */
      virtual unknown Target() const pure;
	};
}
#endif // __NGEN_ATTRIBUTE_HPP
