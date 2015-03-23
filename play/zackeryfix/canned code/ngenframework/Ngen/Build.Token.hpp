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
#ifndef __NGEN_BUILD_TOKEN_HPP
#define __NGEN_BUILD_TOKEN_HPP

#include "Build.Documentation.hpp"

// Custom Keywords -------------------------------------------------------------

/** @brief A cosmetic preprocessor token that is used for identifying arguments passed to
 * functions by reference.
 */
#define inref

/** @brief A cosmetic preprocessor token that is used for marking pure virtual member functions.
 */
#define pure =0

/** @brief A cosmetic preprocessor token that is used for identifying an abstract class.
 */
#define abstract

/** @brief A cosmetic preprocessor token that is used in place of the equal operator.
 */
#define equalto operator==

// Build Tokens ----------------------------------------------------------------

/** @brief A token value representing an unknown value. */
#define _tknval_Unknown 0

/** @brief A token value representing an true value. */
#define _tknval_True 1

/** @brief A token value representing an false value. */
#define _tknval_False -1

/** @brief The Gnu C++ Compiler. */
#define _tknval_Compiler_GCC 1

/** @brief The Microsoft Visual C++ Compiler. */
#define _tknval_Compiler_MSVC 2

/** @brief The Microsoft Windows operating system. */
#define _tknval_Platform_Windows 1

/** @brief The Unix-based operating system. */
#define _tknval_Platform_Unix 2

/** @brief The Apple Macintosh operating system. */
#define _tknval_Platform_Mac 3

/** @brief The Apple iPhone operating system. */
#define _tknval_Platform_iPhone 4

/** @brief The Google Android operating system. */
#define _tknval_Platform_Android 5

/** @brief The Linux kernel powered operating system. */
#define _tknval_Platform_Linux 6

/** @brief A register width of 32-bits. */
#define _tknval_RegisterWidth_32 32

/** @brief A register width of 64-bits. */
#define _tknval_RegisterWidth_64 64

/** @brief A register width of 128-bits. */
#define _tknval_RegisterWidth_128 128

/** @brief An Intel branded central processing unit. */
#define _tknval_Cpu_Intel 1

/** @brief An AMD branded central processing unit. */
#define _tknval_Cpu_Amd 2

/** @brief An ARM branded central processing unit. */
#define _tknval_Cpu_Arm 3

/** @brief An PowerPC branded central processing unit. */
#define _tknval_Cpu_PowerPC 4

/** @brief An SSE instruction set for parallel computing techniques. */
#define _tknval_ParallelCpu_SSE 1

/** @brief A NEON instruction set for parallel computing techniques. */
#define _tknval_ParallelCpu_Neon 2

/** @brief A VFP instruction set for parallel computing techniques. */
#define _tknval_ParallelCpu_VFP 3

/** @brief The big-endian bit-order. */
#define _tknval_Endian_Big 1

/** @brief The little-endian bit-order. */
#define _tknval_Endian_Little 2

/** @brief The X11 window/display manager used by most Linux/Unix distributions. */
#define _tknval_UnixLinux_DisplayManager_X11 1

/** @brief The Wayland window/display manager used in some Linux/Unix distributions. */
#define _tknval_UnixLinux_DisplayManager_Wayland 2

#endif // __NGEN_BUILD_TOKEN_HPP
