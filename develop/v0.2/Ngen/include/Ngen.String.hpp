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
#ifndef __NGEN_STRING_HPP
#define __NGEN_STRING_HPP

#include "Ngen.Typedefs.hpp"
#include "Ngen.Exception.hpp"

namespace Ngen {
   /** @brief A contiguous array of bytes used to represent binary data. */
   class String {
   public:
      /** @brief Constructor. */
      String() : mData(null), mLength(0) {
      }

      /** @brief Constructor. (const char*).
       * This is meant to provide compatibility with compile-time strings, but its suggested to use Ngen::Text when
       * representing human-readable data.
       */
      explicit String(const char* data) : mData(null), mLength(0) {
         if(isnull(data)) {
            throw InvalidParameterException("The parameter 'data' cannot be a null pointer!");
         }

         byte* ptr = (byte*)data;

         do {
            mLength++;
         } while(*ptr++);

         mData = Memory::New<byte>(mLength);
         for(uword i = 0; i < mLength; ++i) {
            *(mData + i) = *(data + i);
         }
      }

      /** @brief Constructor. (const byte*, uword). */
      String(const byte* data, uword length) :  mData(Memory::New<byte>(length)), mLength(length) {
         if(isnull(data)) {
            throw InvalidParameterException("The parameter 'data' cannot be a null pointer!");
         } else if(length == 0) {
            throw InvalidParameterException("The parameter 'length' cannot be zero!");
         }

         for(uword i = 0; i < length; ++i) {
            *(mData + i) = *(data + i);
         }
      }

      /** @brief Constructor. Copy. (const String&). */
      explicit String(const String& copy) : mData(null), mLength(copy.mLength) {
         if(copy.mLength == 0) {
            return;
         }

         mData = Memory::New<byte>(mLength);
         for(uword i = 0; i < mLength; ++i) {
            *(mData + i) = *(copy.mData + i);
         }
      }

      /** @brief Constructor. Move. (String&&). */
      String(String&& move) : mData(move.mData), mLength(move.mLength) {
         move.mData = null;
         move.mLength = 0;
      }

      /** De-constructor. */
      ~String() {
         if(!isnull(mData)) {
            Memory::Delete(mData);
         }
      }

      bool operator==(const String& rhs) const {
         if(rhs.mLength == mLength) {

            for(uword i = 0; i < mLength; ++i) {
               if(*(rhs.mData + i) != *(mData + i)) {
                  return false;
               }
            }

            return true;
         }

         return false;
      }

      bool operator!=(const String& rhs) const {
         if(rhs.mLength == mLength) {
            for(uword i = 0; i < mLength; ++i) {
               if(*(rhs.mData + i) != *(mData + i)) {
                  return true;
               }
            }

            return false;
         }

         return true;
      }

      String& operator=(const String& rhs) {
         if(this == &rhs) {
            return *this;
         }

         this->~String();

         if(rhs.mLength != 0) {
            mLength = rhs.mLength;
            mData = Memory::New<byte>(mLength);
            Memory::Copy<byte>(rhs.mData, inref mData, mLength);
         }
      }

      byte& operator[](uword index) {
         if(index >= mLength) {
            THROW(InvalidParameterException("The given parameter 'index' cannot be greater-than the length of the string!"));
         }

         return *(mData + index);
      }

      /** @brief Gets the length of the string. */
      uword Length() const { return mLength; }

      /** @brief Gets the byte-pointer address of strings data member. */
      byte* Data() const { return mData; }


   protected:
      byte* mData;
      uword mLength;
   };

   typedef String string;
}

#endif // __NGEN_STRING_HPP
