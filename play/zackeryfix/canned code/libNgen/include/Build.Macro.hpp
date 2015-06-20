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
#ifndef __NGEN_MACRO_HPP
#define __NGEN_MACRO_HPP

#include "Build.Token.hpp"

namespace Ngen {
	struct error_incomplete {};

	template<typename T> struct __typename { const error_incomplete* result() { return (error_incomplete*)0; } };
	template<typename T> struct __aliasname { const error_incomplete* result() { return (error_incomplete*)0; } };

   /** @brief A logic structure used by the trait class for determining if a
    * typename represents a primitive data structure.
    */
   template<typename T> struct __is_primitive { static constexpr bool result() { return false; } };

   /** @brief A logic structure used by the trait class for determining if a
    * typename is movable.
    */
   template<typename T> struct __is_movable { static constexpr bool result() { return false; } };

   /** @brief A logic structure used by the trait class for determining if a two typenames are equal.
    */
	template<typename TLhs, typename TRhs> struct __is_equal { static constexpr bool result() { return false; } };
	template<typename TLhs> struct __is_equal<TLhs, TLhs> { static constexpr bool result() { return true; } };

   /** @brief A macro used to signify that a given typename represents a built-in primitive. */
   #define __make_primitive(typename) template<> struct __is_primitive<typename> { static constexpr bool result() { return true; } }

   /** @brief A macro used to signify that a given typename represents a movable type. */
   #define __make_movable(typename) template<> struct __is_movable<typename> { static constexpr bool result() { return true; } }

	/** @brief A macro used to generate a compile-time constant for the text conversion of a typename. */
	#define __set_typename(T, typeName) template<> struct __typename<T> {\
		static constexpr const char8* __m = typeName;\
		static constexpr const char8* result() {\
			return __m;\
		}\
	}

	/** @brief A macro used to generate a compile-time constant for the text conversion of a typedef'd typename. */
	#define __set_aliasname(T, typeName) template<> struct __aliasname<T> {\
		static constexpr const char8* __m = typeName;\
		static constexpr const char8* result() {\
			return __m;\
		}\
	}

	#define __define_generic_containers(_typename_)\
		typedef Array<_typename_> _typename_#Array;\
		typedef Array<_typename_#*> _typename_#PointerArray;\
		typedef List<_typename_> _typename_#List;\
		typedef List<_typename_#*> _typename_#PointerList;


}

#endif // __NGEN_MACRO_HPP