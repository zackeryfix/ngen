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
#ifndef __NGEN_REFLECTION_TYPEBUILDER_HPP
#define __NGEN_REFLECTION_TYPEBUILDER_HPP

#include "Ngen.Reflection.NamespaceBuilder.hpp"

namespace Ngen {
	namespace Reflection {
		/** @brief A procedural programming structure used to build the description of a new type.
		 */
		class ngen_api TypeBuilder {
		public:
		   /** @brief
		    */
			TypeBuilder(TypeInfo* type);

			/** @brief Adds a new method information structure to the type.
			 * @param signature The signature used to identify the method as a part of the type.
			 * @param function The delegate constant that represents the method body.
			 */
			void AddMethod(const mirror& signature, Delegate* function);
			void AddConstructor(const mirror& signature, Delegate* function, EConstructorKind kind);
			void InitializeAs(EInitializerKind kind);
			void AddParent(const mirror& parentName);
			void AddTrait(ETrait trait);
			void RemoveTrait(ETrait trait);
			void SetTraits(TraitFlags traits);
			void SetDestructor(Delegate* function, MethodInfoInitializer initializer);

         /** @brief Validates the type information after it has been constructed. */
         bool Save() const;
		protected:
			TypeInfo* mInfo;

			friend class Assembly;
		};
	}
}

#endif // __NGEN_RTI_BUILDERS_HPP
