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
#ifndef __NGEN_BUILD_LOGIC_HPP
#define __NGEN_BUILD_LOGIC_HPP

#include "Build.Macro.hpp"
#include "Build.Configuration.hpp"

/** @brief The compiler used to build the framework source code. */
#if defined(__GNUC__)
#   define _tkn_Compiler _tknval_Compiler_GCC
#elif defined(_MSC_VER)
#   define _tkn_Compiler _tknval_Compiler_MSVC
#else
#   define _tkn_Compiler _tknval_Unknown
#endif

/** @brief The version of the compiler used to build the framework binaries */
#if defined(__GNUC__)
#   define _tkn_CompilerVersion __GNUC__
#elif defined(_MSC_VER)
#   define _tkn_CompilerVersion _MSC_VER
#else
#   define _tkn_CompilerVersion 0
#endif

/** @brief The platform where the binaries for framework were compiled.  */
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(_WINDOWS_) || defined(__WIN32_WCE)
#   define _tkn_Platform _tknval_Platform_Windows
#elif defined(_POSIX_VERSION) || defined(__unix__) || defined(__unix)
#  if defined(_linux_)
#     define _tkn_Platform _tknval_Platform_Linux
#  else
#   define _tkn_Platform _tknval_Platform_Unix
#  endif
#elif defined(__APPLE_CC__)
#   if __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ >= 30000 || __IPHONE_OS_VERSION_MIN_REQUIRED >= 30000
#       define _tkn_Platform _tknval_Platform_iPhone
#   else
#       define _tkn_Platform _tknval_Platform_Mac
#   endif
#else
#   define _tkn_Platform _tknval_Unknown
#endif

/** @brief The native bit-width of each register used by the target CPU architecture. */
#if defined(__x86_64__) || defined(_M_X64) || defined(__powerpc64__) || defined(__alpha__) || defined(__ia64__) || defined(__s390__) || defined(__s390x__)
#   define _tkn_RegisterWidth _tknval_RegisterWidth_64
#else
#   define _tkn_RegisterWidth _tknval_RegisterWidth_32
#endif

/** @brief Identifies the target CPUs instruction set. */
#if (defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_X64))) || (defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__)))
#   define _tkn_Cpu _tknval_Cpu_Intel
#elif _tkn_Platform == _tknval_Platform_Mac || _tkn_Platform == _tknval_Platform_iPhone
#	if defined(__BIG_ENDIAN__)
#		define _tkn_Cpu _tknval_Cpu_PowerPC
#	else
#		define _tkn_Cpu _tknval_Cpu_Intel
#	endif
#elif defined(__arm__)
#	define _tkn_Cpu _tknval_Cpu_Arm
#else
#	define _tkn_Cpu _tknval_Unknown
#endif

/** @brief The CPU architecture that describes the instruction set to use for parallel computing techniques. */
#if _tkn_UseParallelComputing == _tknval_True && _tkn_UseDoublePrecision == _tknval_False
#   if _tkn_Cpu == _tknval_Cpu_Intel && (_tkn_Compiler == _tkn_Compiler_MSVC || _tkn_Compiler == _tknval_Compiler_GCC)
#       define _tkn_ParallelCpu _tknval_ParallelCpu_SSE
#       include <xmmintrin.h>
#   elif  defined(__ARM_ARCH_6K__) && defined(__VFP_FP__) && (_tkn_Compiler == _tkn_Compiler_MSVC || _tkn_Compiler == _tknval_Compiler_GCC)
#       define _tkn_ParallelCpu _tknval_ParallelCpu_VFP
#   elif defined(__ARM_ARCH_7A__) && defined(__ARM_NEON__) && (_tkn_Compiler == _tkn_Compiler_MSVC || _tkn_Compiler == _tknval_Compiler_GCC)
#       define _tkn_ParallelCpu _tknval_ParallelCpu_NEON
#   else
#     define _tkn_ParallelCpu _tknval_Unknown
      /** @brief Unsupported because the parallel computing architecture is unknown. */
#     undef _tkn_UseParallelComputing
#     define _tkn_UseParallelComputing _tknval_False
#   endif
#else
#  define _tkn_ParallelCpu _tknval_Unknown
   /** @brief Unsupported because _tkn_UseDoublePrecision is equal to _tknval_True. */
#  undef _tkn_UseParallelComputing
#  define _tkn_UseParallelComputing _tknval_False
#endif

/** @brief Determines if OpenGL extension pointers should be used for the target platform. */
#if ((_tkn_Platform == _tknval_Platform_Unix || _tkn_Platform == _tknval_Platform_Linux) && _tkn_UnixLinux_DisplayManager == _tknval_UnixLinux_DisplayManager_X11)
#   define _tkn_OpenGL_UseExtensionPtr _tknval_True
#else
#   define _tkn_OpenGL_UseExtensionPtr _tknval_False
#endif

/** @brief Used to export or import public symbols from the framework. */
#if _tkn_Platform == _tknval_Platform_Windows
#  if defined(NGEN_EXPORT)
#     define ngen_api __declspec(dllexport)
#  else
#     if defined(__MINGW32__)
#        define ngen_api
#     else
#        define ngen_api __declspec(dllimport)
#     endif
#  endif
   /** @brief Used to export or import private symbols from the framework. */
#  define ngen_api_private
   /** @brief Used to determine the calling convection to use for a specific routine. */
#	if defined(_STDCALL_SUPPORTED)
#     define ngen_callconv __stdcall
#	else
#		define ngen_callconv __cdecl
#	endif
#else // other supported platforms (Linux, MacOSX and iPhone)
#	if (__GNUC__ >= 4) && defined(NGEN_EXPORT)
#		define ngen_api __attribute__ ((visibility("default")))
      /** @brief Used to export or import private symbols from the framework. */
#		define ngen_api_private __attribute__ ((visibility("hidden")))
#	else
#     define ngen_api
      /** @brief Used to export or import private symbols from the framework. */
#     define ngen_api_private
#	endif
   /** @brief Used to determine the calling convection to use for a specific routine. */
#	define ngen_callconv
#endif

#if _tkn_NoThrow_ == _tknval_True
#	define THROW(e)
#else
#	define THROW(e) throw e
#endif

#define _tkn_Mute 9999991

#endif // __NGEN_BUILD_LOGIC_HPP
