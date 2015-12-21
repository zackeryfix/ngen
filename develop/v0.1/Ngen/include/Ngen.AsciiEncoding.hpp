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
#ifndef __NGEN_ASCIIENCODING_HPP
#define __NGEN_ASCIIENCODING_HPP

#include "Ngen.Encoding.hpp"

namespace Ngen {

   class ngen_api AsciiEncoding : public virtual Encoding {
      AsciiEncoding() {}

      friend class Encoding;
   public:
      /** @brief The definition representing the primitive character structure used for the encoding. */
      typedef char8 TChar;

      ngen_api virtual bool Compare(const Encoding* rhsEncoding, const byte* lhs, const byte* rhs, uword length);

      ngen_api virtual void Encode(const Encoding* encodeTo, const byte* from, byte*& to, uword length);

      ngen_api virtual void Decode(const Encoding* decodeFrom, const byte* from, byte*& to, uword length);

      /** @brief Counts the number of characters starting at the given address until the a termination character is discovered. */
      static uword Count(const TChar* at) {
         uword len = 0;
         if(!isnull(at)) {
            do {
               len++;
            } while(*(at++));
         }

         return len;
      }

		static TChar EndOfString() {
			return '\0';
		}

		/** @brief Sets the character at the given address to an encoded termination character.
       */
      static void EndOfString(TChar* at) {
         *at = EndOfString();
      }

		static TChar EndOfLine() {
			return '\n';
		}

      /** @brief Sets the character at the given address to an encoded end-of-line character.
       */
      static void EndOfLine(TChar* at) {
         *at = EndOfLine();
      }

      /** @brief Encodes a series of ASCII characters to another encoding.
       * @param from The characters being encoded.
       * @param at A place to store the encoded result.
       * @param length The number of characters to encode.
       */
      template<typename TEncoding>
      ngen_api static bool Compare(const TChar* lhs, const typename TEncoding::TChar* rhs, uword length) = delete;

      /** @brief Encodes a series of ASCII characters to another encoding.
       * @param from The characters being encoded.
       * @param at A place to store the encoded result.
       * @param length The number of characters to encode.
       */
      template<typename TEncoding>
      ngen_api static void Encode(const TChar* from, typename TEncoding::TChar*& at, uword length) = delete;

      /** @brief Decodes a series of ASCII characters from another encoding.
       * @param from The characters being decoded.
       * @param at A place to store the decoded result.
       * @param length The number of characters to decode.
       */
      template<typename TEncoding>
      ngen_api static void Decode(TChar*& at, const typename TEncoding::TChar* from, uword length) = delete;
   };

   template<> ngen_api bool AsciiEncoding::Compare<AsciiEncoding>(const AsciiEncoding::TChar* lhs, const AsciiEncoding::TChar* rhs, uword length);
   template<> ngen_api void AsciiEncoding::Encode<AsciiEncoding>(const AsciiEncoding::TChar* from, AsciiEncoding::TChar*& at, uword length);
   template<> ngen_api void AsciiEncoding::Decode<AsciiEncoding>(AsciiEncoding::TChar*& at, const AsciiEncoding::TChar* from, uword length);
}

#endif // __NGEN_ASCIIENCODING_HPP
