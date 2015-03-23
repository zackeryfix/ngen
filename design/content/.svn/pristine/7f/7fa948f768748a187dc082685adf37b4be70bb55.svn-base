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
#ifndef __NGEN_ENCODING_HPP
#define __NGEN_ENCODING_HPP

#include "Ngen.Typedefs.hpp"
#include "Ngen.Memory.hpp"
#include "Ngen.String.hpp"

namespace Ngen {
   class AsciiEncoding;

   class ngen_api Encoding {
   protected:
      Encoding() {}
      virtual ~Encoding() {}

   public:
      /** @brief Compares bytes in this encoding to bytes of another encoding.
       * @param lhs An address pointing to the first byte in this encoding.
       * @param rhs An address pointing to the first byte in the other encoding.
       * @param rhsEncoding The encoding that is being compared against.
       */
      virtual bool Compare(const Encoding* rhsEncoding, const byte* lhs, const byte* rhs, uword length) pure;

      /** @brief Encodes bytes of this encoding to the bytes of another encoding.
       * @param encodeTo The encoding of the given bytes.
       * @param from An address pointing to the first byte being encoded.
       * @param to An address pointing to the location where to begin encoding.
       * @param length The number of bytes to encode.
       */
      virtual void Encode(const Encoding* encodeTo, const byte* from, byte*& to, uword length) pure;

      /** @brief Decodes bytes from another encoding to the bytes of this encoding.
       * @param decodeFrom The encoding of the given bytes.
       * @param from An address pointing to the first byte being decoded.
       * @param to An address pointing to the location where to begin decoding.
       * @param length The number of bytes to encode.
       */
      virtual void Decode(const Encoding* decodeFrom, const byte* from, byte*& to, uword length) pure;

      /** @brief Detects the encoding of the given array of bytes. */
      static Encoding* GetEncoding(byte* data, uword length);

      /** @brief Gets the text encoding used to encode and decode ASCII character streams. */
      static AsciiEncoding* Ascii() { return &sAscii; }

       /** @brief Gets the text encoding used to encode and decode 16-bit Unicode character streams. */
      //static UnicodeEncoding* Unicode() { return &sUnicode; }

   private:
      ngen_api static AsciiEncoding sAscii;
      //ngen_api static UnicodeEncoding sUnicode;
   };
}

#endif // __NGEN_ENCODING_HPP
