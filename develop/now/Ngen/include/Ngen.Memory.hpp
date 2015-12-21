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
#ifndef __NGEN_MEMORY_HPP
#define __NGEN_MEMORY_HPP

#include "Ngen.Cast.hpp"

namespace Ngen {
   /** @addtogroup memorymanagement
    * @{
    */
   template<typename T>
   typename Trait<T>::Moved mref(typename Trait<T>::Reference e) {
      return (typename Trait<T>::Moved)e;
   }

   /** @brief A static instance with various routines used to manipulate heap bound memory. */
   class Memory final {
   public:

      /** @brief Allocates a new memory block based on the size of the given typename.
       * @param count The number of structures (typeof(T)) to allocate.
       */
      template<typename T = int8> static T* New(uword count = 1, bool initialize = false) {
         uword len = sizeof(T) * count;
         T* result = (T*)(operator new (len));

         if(initialize) {
				Clear(result, len);
         }

         return result;
      }

      /** @brief A template that deletes a previously allocated memory block.
       * @param at The memory address that points the memory block being freed.
       */
      template<typename T = int8> static void Delete(T* at) {
         operator delete (at);
      }

      /** @brief A template that invokes the destructor of the typename at the given address.
       * @param at The memory address that points the memory block being destructed.
       */
      template<typename T = int8> static void Destruct(T* at) {
         at->~T();
      }

      /** @brief Performs a memory placement operation at a given address.
       * @param at The memory address that points the memory block being replaced.
       */
      template<typename T = int8> static void Place(T* at, const T& copy) {
			new (at) T(copy);
      }

		/** @brief Performs a memory placement operation at a given address.
       * @param at The memory address that points the memory block being replaced.
       */
      template<typename T = int8> static void Move(T* at, const T& copy) {
			new (at) T((T&&)copy);
      }

      /** @brief Performs a memory copy operation at a given address.
       * @param at The memory address that points the memory block being replaced.
       */
      template<typename T = int8> static void Copy(const T* from, T*& at, uword length) {
         for(uword i = 0; i < length; ++i) {
            Place((at + i), *(from + i));
         }
      }

      /** @brief Clears all the memory starting at the given address pointer.
       * @param at The memory address where to begin clearing memory.
       * @param length The number of int8s that should be cleared.
       * @param with The value used to clear the memory.  Default: 0x0
       */
      template<typename T = int8> static void Clear(inref T* at, uword length, int8 with=0x0) {
         length = length * sizeof(T);
         uword wordlen = length / sizeof(uword);
         uword* l = (uword*)at;
         uword* r = (uword*)at + wordlen;
         for(uword i = 0; i < wordlen/2; i++) {
            *l++ = *r-- = with;
         }
         *l = with;

         uword difflen = length % sizeof(uword);
         l = (uword*)at + wordlen;
         for(uword i = 0; i < difflen; i++) {
            *l++ = with;
         }
      }

		/** @brief Performs a memory placement operation at a given unknown address.
       * @param at The memory address that points the memory block being replaced.
       */
      template<typename T> static void UnknownCopy(const unknown from, unknown& to) {
      	int8* ptr = (int8*)to;
			Copy((int8*)from, ptr, sizeof(T));
      }

		/** @brief Performs a memory copy operation at a given address.
       * @param at The memory address that points the memory block being replaced.
       */
		template<typename T> static void UnknownPlace(unknown& at, const unknown from) {
      	int8* ptr = (int8*)at;
			Copy((int8*)from, ptr, sizeof(T));
      }

		/** @brief Allocates a new memory block based on the size of the given typename.
       * @param count The number of structures (typeof(T)) to allocate.
       */
		template<typename T> static void UnknownNew(unknown& at, uword count = 1) {
      	at = (unknown)New<T>(count);
      }

		/** @brief A template that deletes a previously allocated memory block.
       * @param at The memory address that points the memory block being freed.
       */
      template<typename T = int8> static void UnknownDelete(unknown* at) {
         Delete<T>((T*)at);
      }
   };


	typedef Memory memory;
   /** @} */
}

#endif // __NGEN_MEMORY_HPP
