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
#ifndef __NGEN_ALGORITHM_HPP
#define __NGEN_ALGORITHM_HPP

#include "Ngen.Memory.hpp"

namespace Ngen {
   /** @brief An enumeration used by sorting algorithms to determine the order of sorted items. */
   enum class EOrderBy {
      HIGHEST = 0,
      LOWEST = 1,
   };

   /** @brief A static functor used in specializing swap operations for specific types. */
   template<typename T> struct t_swap {
      t_swap(T& lhs, T& rhs) {
         T tmp = lhs;
         lhs = rhs;
         rhs = tmp;
      }
   };

   /** @brief A static instance that exposes various algorithms for analyzing or manipulating memory
    * constructs.
    */
   class Algorithm final {
   public:
      /** @brief A generic algorithm used to compare pointer arrays.
       * @param lhs The left-hand sided pointer array being compared.
       * @param lhs The left-hand sided pointer array being compared.
       * @param lhsbegin The starting locating withing the left-hand sided pointer array to begin comparing.
       * @param rhsbegin The starting locating withing the right-hand sided pointer array to begin comparing.
       * @param length The number of items in each array being compared.
       */
      template<typename TLhs, typename TRhs>
      static inline bool Compare(TLhs* lhs, TRhs* rhs, uword length) {
         if(isnull(lhs) || isnull(rhs) || length == 0) {
            throw InvalidParameterException(E"The parameters 'lhs' and 'rhs' cannot be null, and 'length' cannot be zero.");
         }

         for(uword i = 0; i < length; ++i) {
            if(*(lhs + i) != *(rhs + i)) {
               return false;
            }
         }

         return true;
      }

      /** @brief A generic algorithm used to compare pointer arrays.
       * @param lhs The left-hand sided pointer array being compared.
       * @param lhs The left-hand sided pointer array being compared.
       * @param length The number of items in each array being compared.
       */
      template<typename T>
      static inline bool Compare(T* lhs, T* rhs, uword length) {
         switch(sizeof(T)) {
         case 1:
         case 2: {
               uword* lhsp = (uword*)lhs;
               uword* rhsp = (uword*)rhs;
               uword len = length/sizeof(uword);
               uword pad = length%sizeof(uword);

               for(uword i = 0; i < len; ++i) {
                 if(*lhsp++ != *rhsp++) {
                   return false;
                 } else if(i+1 == len && pad != 0) {
                   for(i = len*sizeof(uword); i < length; ++i) {
                     if(*(lhs+i) != *(rhs+i)) {
                        return false;
                     }
                   }
                 }
               }

               return true;
            }
         default:
            return Compare<T, T>(lhs, rhs, length);
         }
      }

      /** @brief A generic algorithm that performs a bubble sort on the given pointer array ordering
       * it's contents from high to low.
       * @param at The pointer where to begin the bubble sort.
       * @param length The number of items
       */
      template<typename T, EOrderBy TOrderBy = EOrderBy::HIGHEST>
      static inline void BubbleSort(T*& at, uword length) {
         if(isnull(at) || length == 0) {
            return;
         }

         bool hit = true;
         while(hit) {
            hit = false;

            for(uword i = 0; i < length - 1; ++i) {
               T* lhs = (at + i) + 1;
               T* rhs = (at + i);

               switch(TOrderBy) {
                  case EOrderBy::HIGHEST: {
                     if(*lhs > *rhs) {
                        t_swap<T>(*lhs, *rhs);
                        hit = true;
                     }
                     break;
                  }
                  case EOrderBy::LOWEST: {
                     if(*lhs < *rhs) {
                        t_swap<T>(*lhs, *rhs);
                        hit = true;
                     }
                     break;
                  }
                  default: break;
               }
            }
         }
      }

      /** @brief Sorts the contents of a pointer array in reverse order.
       * @param at A reference to the pointer where to begin sorting.
       * @param length The number of items to sort.
       */
      template<typename T> static inline void ReverseSort(T*& at, uword length) {
         uword pad = length - 1;
         for(uword i = 0; i < length / 2; i++) {
            T* lhs = at + i;
            T* rhs = (at + pad) - i;
            t_swap<T>(*lhs, *rhs);
         }
      }

      /** @brief
       */
      template<typename T> static inline uword Find(T* at, const T& item, uword length) {
          for(int i = 0; i < length; ++i) {
            if(*at == item) {
               return i;
            }
          }

          return length;
      }

       /** @brief
       */
      template<typename T> static inline void Populate(T*& at, const T& item, uword length) {
          for(int i = 0; i < length; ++i) {
            *at = item;
          }
      }
   };
}

#endif // __NGEN_ALGORITHM_HPP
