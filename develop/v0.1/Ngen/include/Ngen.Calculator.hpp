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
#ifndef __NGEN_CALCULATOR_HPP
#define __NGEN_CALCULATOR_HPP

#include "Ngen.Typedefs.hpp"
#include <math.h>

namespace Ngen {
   /** @brief A static instance that provides advanced mathematical functions and constants. */
   class Calculator final {
   public:
      /** @brief A constant value representing the Pi ratio. */
      static constexpr float64 Pi = 3.1415926535897932384626433832795028841971693993751;

      inline static float32 Floor(float32 value) {
         return (float32)floor(value);
      }

      inline static float64 Floor(float64 value) {
         return floor(value);
      }

      inline static float32 Ciel(float32 value) {
         return (float32)ceil(value);
      }

      inline static float64 Ceil(float64 value) {
         return ceil(value);
      }

      inline static float32 Sqrt(float64 value) {
         return (float32)sqrt(value);
      }

      inline static float32 Sqrt(float32 value) {
         return sqrt(value);
      }

      inline static float32 Reciprocal(float32 value) {
         return 1.0f / value;
      }

      inline static float64 Reciprocal(float64 value) {
         return 1.0 / value;
      }

      inline static float32 Atan(float32 value) {
         return (float32)atan(value);
      }

      inline static float64 Atan(float64 value) {
         return atan(value);
      }

       inline static float32 Atan2(float32 value, float32 s) {
         return (float32)atan2(value, s);
      }

       inline static float64 Atan2(float64 value, float64 s) {
         return atan2(value, s);
      }
   };

   /** @brief A type definition for the  calculator class. */
   typedef Calculator t_calc;
}
#endif // __NGEN_CALCULATOR_HPP
