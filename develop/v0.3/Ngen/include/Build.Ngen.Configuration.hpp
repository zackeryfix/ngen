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
#ifndef __NGEN_BUILD_CONFIGURATION_HPP
#define __NGEN_BUILD_CONFIGURATION_HPP

#include "Build.Ngen.Token.hpp"

/** @addtogroup configurablebuildtokens
 * @{
 */

/** @brief Determines if the current build of the framework contains debugging symbols. */
#ifdef DEBUG
#	define _tkn_Debug _tknval_True
#else
#	define _tkn_Debug _tknval_False
#endif

/** @brief Determines if the framework will use double precision floating-point
 * arithmetic for complex mathematical data structures. Not available when _tkn_UseParallelComputingTech
 * is _tknval_True. Additionally, GPU shader programs may not support double precision values, which can
 * have a performance penalty when passing structures from the CPU to the graphics device (due to casting).
 */
#define _tkn_UseDoublePrecision _tknval_False

/** @brief Determines if the framework will use parallel computing technology if supported on
 * the underlying hardware.  This can greatly improve performance.
 */
#define _tkn_UseParallelComputingTech _tknval_False

/** @brief Configures the display manager to use when building on Unix/Linux platforms.
 */
#define _tkn_UnixLinux_DisplayManager _tknval_RanDR

/** @brief Determines if the framework will omit exception throwing and strip run-time evaluation of parameters.
 * Turning off exception handling is not recommended, but does decrease execution time.  Use only for RELEASE builds that have been
 * completely debugged and tested.
 */
#define _tkn_NoThrow _tknval_False

/** @brief Determines if the Ngen Framework will be using a 16-bit UTF encoding for compile-time strings.
 */
#define _tkn_UseUnicodeEncoding _tknval_False


#define _tkn_RTIMaxNamespaceDepth 12

/** @} */
#endif // __NGEN_BUILD_CONFIGURATION_HPP
