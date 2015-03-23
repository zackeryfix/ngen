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
#ifndef __NGEN_TYPEDEFS_HPP
#define __NGEN_TYPEDEFS_HPP

#include "Build.External.hpp"

namespace Ngen {
   /** @brief An 8-bit wide unsigned integer value. */
   typedef unsigned char uint8;

   /** @brief An 8-bit wide signed integer value. */
   typedef signed char int8;

   /** @brief A 16-bit wide unsigned integer value. */
   typedef unsigned short uint16;

   /** @brief A 16-bit wide signed integer value. */
   typedef signed short int16;

   /** @brief A 32-bit wide unsigned integer value. */
   typedef unsigned int uint32;

   /** @brief A 32-bit wide signed integer value. */
   typedef signed int int32;

   /** @brief A 64-bit wide unsigned integer value. */
   typedef unsigned long long int uint64;

   /** @brief An 64-bit wide signed integer value. */
   typedef signed long long int int64;

   /** @brief An 32-bit wide floating-point integer value. */
   typedef float float32;

   /** @brief An 64-bit wide floating-point integer value. */
   typedef double float64;

   /** @brief An 96-bit wide floating-point integer value. */
   typedef long double float96;

   /** @brief An 8-bit wide signed value. */
   typedef signed char byte;

   /** @brief An 8-bit wide unsigned value. */
   typedef unsigned char ubyte;

   /** @brief An 8-bit wide character value. */
   typedef char char8;

   /** @brief An 16-bit wide character value. */
   typedef char16_t char16;

   /** @brief An 32-bit wide character value. */
   typedef char32_t char32;

   /** @brief A wide character value. */
   typedef wchar_t wchar;

   /** @brief The floating-point value used by complex data structures used in geometric
    * calculations.
    */
#  if _tkn_UseDoublePrecision == _tknval_True
      typedef float64 real;
#  else
      typedef float32 real;
#  endif

   /** @brief A user-defined literal for converting floating point constants
    * to the frameworks 'real'.
    */
   static inline constexpr real operator"" _rl(long double value) {
      return (real)value;
   }

   /** @brief The unsigned integral data type used in indexing arithmetic. */
#  if _tkn_RegisterWidth == _tknval_RegisterWidth_32
      typedef uint32 uword;
#  elif _tkn_RegisterWidth == _tknval_RegisterWidth_64
      typedef uint64 uword;
#  endif

   /** @brief The signed integral data type used in indexing arithmetic. */
#  if _tkn_RegisterWidth == _tknval_RegisterWidth_32
      typedef int32 word;
#  elif _tkn_RegisterWidth == _tknval_RegisterWidth_64
      typedef int64 word;
#  endif

   /** @brief A pointer with all type information discarded. */
   typedef void* unknown;

	/** @brief A pointer value that represents an invalid data structure. */
#  define null 0x0

	/** @brief A constant expression used to check if a pointer is null. */
   template<typename T> static constexpr bool isnull(T* rhs) {
   	return rhs == null;
	}

	/** @brief A data-structure used to represent void. Needed for use with delegates, events, and callbacks. */
   struct void_t {
   	void_t() {}
   	void_t(const void_t& copy) {}
   	//void_t& operator=(const void_t& rhs) const { return rhs; }
   	bool operator==(const void_t& rhs) const { return true; }
   	bool operator!=(const void_t& rhs) const { return false; }
	};

	/** @brief Recursive structure used to represent the indices required for accessing a template parameter pack. */
	template<uword... Indices>
	struct index_pack_t {
		template<uword N> using append = index_pack_t<Indices..., N>;
	};

	/** @brief A meta-programming structure used to create an index_pack_t. */
	template<uword Size>
	struct make_index_pack_t	{
		typedef typename make_index_pack_t<Size-1>::type::template append<Size-1> type;
	};

	template<>
	struct make_index_pack_t<0u> {
		typedef index_pack_t<> type;
	};


	/** @brief A template expression used to create an index_pack_t for a set of template parameters. */
	template<typename... Types>
	using pack_indices_t = typename make_index_pack_t<sizeof...(Types)>::type;


	template<typename T> struct typename_t {
		const char8* result() { return "unknown"; }
	};

	#define _define_typename(T, typeName) template<> struct typename_t<T> {\
		static const char8* __m;\
		static const char8* result() {\
			return __m;\
		}\
	};\
	const char8* typename_t<T>::__m = typeName;

	#define typenameof(T) typename_t<T>::result()

   // XXXX: Primitive Data-Type Registration -----------------------------------
   __make_primitive(int8);
   __make_primitive(int16);
   __make_primitive(int32);
   __make_primitive(int64);
   __make_primitive(uint8);
   __make_primitive(uint16);
   __make_primitive(uint32);
   __make_primitive(uint64);
   __make_primitive(float32);
   __make_primitive(float64);
   __make_primitive(float96);
   __make_primitive(char8);
   __make_primitive(char16);
   __make_primitive(char32);
   __make_primitive(wchar);
}

#endif // __NGEN_TYPEDEFS_HPP
