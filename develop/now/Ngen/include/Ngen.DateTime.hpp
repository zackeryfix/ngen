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
#ifndef __NGEN_DATETIME_HPP
#define __NGEN_DATETIME_HPP

#include "Build.Ngen.External.hpp"

namespace Ngen {

   /** @brief */
   enum class ETimeCoordination {
      Undefined = 1,
      UTC = 2,
      Local = 3
   };

   /** @brief A data structure that represents a snapshot of time. */
   class DateTime final {
   public:
      DateTime(uint64 tick, ETimeCoordination coord = ETimeCoordination::Undefined);

      static DateTime Now(ETimeCoordination coord = ETimeCoordination::Undefined);

      uword Nanosecond() const;
      uword Millisecond() const;
      uint8 Second() const;
      uint8 Minute() const;
      uint8 Hour() const;
      uint8 Day() const;
      uint8 Month() const;
      uint16 Year() const;
      uint8 DayOfWeek() const;
      uint16 DayOfYear() const;
      bool IsLeapYear() const;
      bool IsDayLightSavingsTime() const;

   protected:
      DateTime() {}

      uint64 mTickStamp;
      uint64 mFrequency;
   };

   /** @brief A structure that represents the difference between two high-resolution snapshots in time. */
   class ngen_api TimeSpan final {
   public:
      TimeSpan(uint64 ticks);

      uint64 ElapsedTicks() const;
      uint64 ElapsedNanoseconds() const;
      uint64 ElapsedMilliseconds() const;
      uint64 ElapsedSeconds() const;
      uint64 ElapsedHours() const;
      uint64 ElapsedDays() const;

   protected:

      uint64 mTickStamp;
   };
}

#endif // __NGEN_DATETIME_HPP
