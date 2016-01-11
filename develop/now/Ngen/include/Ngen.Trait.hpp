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
#ifndef __NGEN_TRAIT_HPP
#define __NGEN_TRAIT_HPP

#include "Ngen.Exception.hpp"

namespace Ngen {
#  define __inline_reusable_trait_logic \
      static constexpr bool IsPrimitive() { return Trait<T>::IsPrimitive(); }\
      static constexpr bool IsMovable() { return Trait<T>::IsMovable(); }\
      static constexpr bool IsNumerical() { return Trait<T>::IsNumercial(); }\
      static constexpr bool IsDecimal() { return Trait<T>::IsDecimal(); }\
      static constexpr bool IsIntegral() { return Trait<T>::IsIntegral(); }\
      static constexpr uword Size() { return Trait<T>::Size(); }\
      typedef typename Trait<T>::Typename Typename;\
      typedef typename Trait<T>::Typename& Reference;\
      typedef typename Trait<T>::Typename&& Moved;\
      typedef typename Trait<T>::Typename* Pointer;\
      typedef typename Trait<T>::Typename*& PointerRef;\
      typedef typename Trait<T>::Typename* const PointerConst;\
      typedef const typename Trait<T>::Typename Const;\
      typedef const typename Trait<T>::Typename& ConstReference;\
      typedef const typename Trait<T>::Typename* ConstPointer;\
      typedef const typename Trait<T>::Typename*& ConstPointerRef;\
      typedef const typename Trait<T>::Typename* const ConstPointerConst;

   /** @brief A constant expressions data-structure that identifies specific traits
    * of a typename.
    */
   template<typename T> struct Trait {
      static constexpr bool IsPointer() { return false; }
      static constexpr bool IsConst() { return false; }
      static constexpr bool IsReference() { return false; }
      static constexpr bool IsPointerConst() { return false; }
      static constexpr bool IsPrimitive() { return __is_primitive<T>::result(); }
      static constexpr bool IsMovable() { return __is_movable<T>::result(); }
      static constexpr bool IsNumerical() { return __is_integral<T>::result() || __is_decimal<T>::result(); }
      static constexpr bool IsDecimal() { return __is_decimal<T>::result(); }
      static constexpr bool IsIntegral() { return __is_integral<T>::result(); }
      template<typename TTo> static constexpr bool IsEqual() { return __is_equal<T, typename Trait<TTo>::Typename>::result(); }
      static constexpr uword Size() { return sizeof(T); }

      typedef T Typename;
      typedef T& Reference;
      typedef T&& Moved;
      typedef T* Pointer;
      typedef T*& PointerRef;
      typedef T* const PointerConst;
      typedef const T Const;
      typedef const T& ConstReference;
      typedef const T* ConstPointer;
      typedef const T*& ConstPointerRef;
      typedef const T* const ConstPointerConst;
   };

   /** @brief @see Trait */
   template<typename T> struct Trait<T*> {
      static constexpr bool IsPointer() { return true; }
      static constexpr bool IsConst() { return Trait<T>::IsConst(); }
      static constexpr bool IsReference() { return false; }
      static constexpr bool IsPointerConst() { return false; }

      __inline_reusable_trait_logic
   };

   /** @brief @see Trait */
   template<typename T> struct Trait<T*&> {
      static constexpr bool IsPointer() { return true; }
      static constexpr bool IsConst() { return Trait<T>::IsConst(); }
      static constexpr bool IsReference() { return true; }
      static constexpr bool IsPointerConst() { return false; }

      __inline_reusable_trait_logic
   };

   /** @brief @see Trait */
   template<typename T> struct Trait<T* const> {
      static constexpr bool IsPointer() { return true; }
      static constexpr bool IsConst() { return Trait<T>::IsConst(); }
      static constexpr bool IsReference() { return false; }
      static constexpr bool IsPointerConst() { return true; }

      __inline_reusable_trait_logic
   };

   /** @brief @see Trait */
   template<typename T> struct Trait<T&> {
      static constexpr bool IsPointer() { return Trait<T>::IsPointer(); }
      static constexpr bool IsConst() { return Trait<T>::IsConst(); }
      static constexpr bool IsReference() { return true; }
      static constexpr bool IsPointerConst() { return Trait<T>::IsPointerConst; }

      __inline_reusable_trait_logic
   };

   /** @brief @see Trait */
   template<typename T> struct Trait<const T> {
      static constexpr bool IsPointer() { return Trait<T>::IsPointer(); }
      static constexpr bool IsConst() { return true; }
      static constexpr bool IsReference() { return Trait<T>::IsReference(); }
      static constexpr bool IsPointerConst() { return Trait<T>::IsPointerConst; }

      __inline_reusable_trait_logic
   };

   template <typename T> typename Trait<T>::Moved mref(T&& arg) { return (typename Trait<T>::Moved)arg; }
}

#endif // __NGEN_TRAITS_HPP
