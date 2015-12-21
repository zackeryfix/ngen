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
#ifndef __NGEN_RTI_ENUMS_HPP
#define __NGEN_RTI_ENUMS_HPP

#include "Ngen.Assembly.hpp"

namespace Ngen {
	namespace Rti {
		/** @brief Describes the different kinds of constructors of a Type. */
		enum class EConstructorKind {
			/** @brief  Default constructor. T() */
			Default = 1,
			/** @brief  Copy constructor. T(const T&) */
			Copy = 2,
			/** @brief  Move constructor. T(T&&) */
			Move = 3,
		};

		/** @brief Modifier flags are used to mark reflected items with having specific
		 * properties that will influence that items behaviour, or visibility to other reflected items.
		 */
		enum class EModifierFlags : uword {
			Public 		= 1,
			Protected 	= 1001,
			Private 		= 100001,

			Static 		= 2,
			Virtual 		= 4,
			Abstract 	= 8,
			Hidden	 	= 16,
			Inline   	= 32,
			Template    = 64,
			Final 		= 128,
			Default 		= 256,
			Const 		= 512,

			PublicStatic = EModifierFlags::Public | EModifierFlags::Static,
			AbstractHidden = EModifierFlags::Abstract | EModiferFlags::Hidden,

		};


		// a mirror = EModifierFlags%API
		enum class EMirrorPart : char8 {
			NamespaceSep		 	= '.', // 3%Namespace.Subspace
			TypeSep		 			= '$', // 1%Namespace.Subspace$TypeName
			MememberSep				= '@',
			Seperator   			= '%', // 515%Namespace.Subspace$TypeName@void%FieldName
			ParamBegin				= '(',
			ParamSep			 		= ',',
			ParamEnd					= ')', // 1009%Namespace.Subspace$TypeName@void%MethodName(int%x,int%y)
			DocumentationEnd		= '#', // @brief%Writes the product of two variables to the console output stream.\
													 @param%x%The left-handed side variable.\
													 @param%y%The right-handed side variable.\
													 #1009%Namespace.Subspace$TypeName@void%MethodName(int%x,int%y)
			BodyBegin 				= '{',
			BodyStatementSep		= ';',
			BodyEnd					= '}', // @brief%Writes the product of two variables to the console output stream.\
													 @param%x%The left-handed side variable.\
													 @param%y%The right-handed side variable.\
													 @return%A value that determines if the product is less than the sum of the two values.\
													 #1009%Namespace.Subspace$TypeName@bool%MethodName(int%x,int%y) {\
														Console@void%WriteLine((x * y)@text%ToText());\
														return x * y < x + y;\
													 }\
		};

		/** @brief */
		enum class ERtiMirrorPart : char8 {
			Namespace 	= '.',
			Type 		 	= '$',
			Memember  	= '@',
			Seperator	= '%',
			ParamBegin 	= '(',
			ParamEnd  	= ')',
		};
	}
}

#endif // __NGEN_RTI_ENUMS_HPP
