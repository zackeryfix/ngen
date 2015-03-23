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
#ifndef __NGEN_MEMORY_HPP
#define __NGEN_MEMORY_HPP

#include "Ngen.Typedefs.hpp"

namespace Ngen {
   /** @addtogroup memorymanagement
    * @{
    */

   /** @brief A static instance with various routines used to manipulate heap bound memory. */
   class Memory final {
   public:

      /** @brief Allocates a new memory block based on the size of the given typename.
       * @param count The number of structures (typeof(T)) to allocate.
       */
      template<typename T = byte> static T* New(uword count = 1, bool initialize = false) {
         uword len = sizeof(T) * count;
         T* result = (T*)(operator new (len));

         if(initialize) {
				byte* l = (byte*)result;
				byte* r = (byte*)result + len;
				for(uword i = 0; i < len/2; i++) {
					*l++ = *r-- = 0x0;
				}
				*l = 0;
         }

         return result;
      }

      /** @brief A template that deletes a previously allocated memory block.
       * @param at The memory address that points the memory block being freed.
       */
      template<typename T = byte> static void Delete(T* at) {
         operator delete (at);
      }

      /** @brief A template that invokes the destructor of the typename at the given address.
       * @param at The memory address that points the memory block being destructed.
       */
      template<typename T = byte> static void Destruct(T* at) {
         at->~T();
      }

      /** @brief Performs a memory placement operation at a given address.
       * @param at The memory address that points the memory block being replaced.
       */
      template<typename T = byte> static void Place(T* at, const T& copy) {
			new (at) T(copy);
      }

		/** @brief Performs a memory placement operation at a given address.
       * @param at The memory address that points the memory block being replaced.
       */
      template<typename T = byte> static void Move(T* at, const T& copy) {
			new (at) T((T&&)copy);
      }

      /** @brief Performs a memory copy operation at a given address.
       * @param at The memory address that points the memory block being replaced.
       */
      template<typename T = byte> static void Copy(const T* from, T*& at, uword length) {
         for(uword i = 0; i < length; ++i) {
            Place((at + i), *(from + i));
         }
      }

		/** @brief Performs a memory placement operation at a given unknown address.
       * @param at The memory address that points the memory block being replaced.
       */
      template<typename T> static void UnknownCopy(const unknown from, unknown& to) {
      	byte* ptr = (byte*)to;
			Copy((byte*)from, ptr, sizeof(T));
      }

		/** @brief Performs a memory copy operation at a given address.
       * @param at The memory address that points the memory block being replaced.
       */
		template<typename T> static void UnknownPlace(unknown& at, const unknown from) {
      	byte* ptr = (byte*)at;
			Copy((byte*)from, ptr, sizeof(T));
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
      template<typename T = byte> static void UnknownDelete(unknown* at) {
         Delete<T>((T*)at);
      }
   };


	typedef Memory memory;
   /** @} */
}

#endif // __NGEN_MEMORY_HPP
