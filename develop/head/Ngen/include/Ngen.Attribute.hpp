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
#ifndef __NGEN_ATTRIBUTE_HPP
#define __NGEN_ATTRIBUTE_HPP

#include "Ngen.Mirror.hpp"
#include "Ngen.Array.hpp"

namespace Ngen {
   /** @brief
    */
   enum class EAttributeBinding {
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
      RuntimeBound,

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
         return (this->CustomAttribute() == rhs.CustomAttribute() &&
                 this->CustomData() == rhs.CustomData() &&
                 this->BindingConstraints() == rhs.BindingConstraints();
		}

		/** @brief */
		bool operator!=(const Attribute& rhs) const {
         return (this->CustomAttribute() != rhs.CustomAttribute() ||
                 this->CustomData() != rhs.CustomData() ||
                 this->BindingConstraints() != rhs.BindingConstraints();
		}


      bool Equals(Attribute* rhs) const pure;

		/** @brief */
		Type* CustomAttribute() const pure;

		/** @brief Gets the data object that represents the custom properties of the attribute.
		 */
		Object& CustomData() const pure;

		/** @brief Gets the binding flags used to identify the RTI constraints.
		 */
      AttributeBindingFlags BindingConstraints() const pure;

      /** @brief
       */
      unknown Target() const pure;

      /** @brief */
      template<typename TReflection> bool Target(inref TReflection* pointer) const {
         if(this->BindingConstraints()[TReflection::AttributeBinding]) {
            pointer = (TReflection*)pointer;
            return true;
         }

         pointer = null;
         return false;
      }
	};
}
#endif // __NGEN_ATTRIBUTE_HPP
