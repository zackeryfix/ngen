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
#ifndef __NGEN_BUILD_LOGIC_HPP
#define __NGEN_BUILD_LOGIC_HPP

#include "Build.Ngen.Macro.hpp"
#include "Build.Ngen.Configuration.hpp"

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
#if defined(__x86_64__) || defined(_M_X64) || defined(__powerpc64__) || defined(__alpha__) || defined(__ia64__) || defined(__s390__) || defined(__s390x__) || defined(_AMD64_) || defined(_M_X64) || defined(_M_AMD64) || defined(__amd64) || defined(_WIN64)
#   define _tkn_RegisterWidth _tknval_RegisterWidth_64
#else
#   define _tkn_RegisterWidth _tknval_RegisterWidth_32
#endif

/** @brief Identifies the target CPUs instruction set. */
#if (defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_X64))) ||\
    (defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__)))
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
#  define api_export __declspec(dllexport)
#  if defined(__MINGW32__)
#     define api_import
#  else
#     define api_import __declspec(dllimport)
#  endif
   /** @brief Used to export or import private symbols from the framework. */
#  define api_private
   /** @brief Used to determine the calling convection to use for a specific routine. */
#	if defined(_STDCALL_SUPPORTED)
#     define api_callconv __stdcall
#	else
#		define api_callconv __cdecl
#	endif
#else // other supported platforms (Linux, MacOSX and iPhone)
#	if (__GNUC__ >= 4) // && defined(NGEN_EXPORT)
#		define api_export __attribute__ ((visibility("default")))
#     define api_import
      /** @brief Used to export or import private symbols from the framework. */
#		define api_private __attribute__ ((visibility("hidden")))
#	else
#     define api_import
#     define api_export
      /** @brief Used to export or import private symbols from the framework. */
#     define api_private
#	endif
   /** @brief Used to determine the calling convection to use for a specific routine. */
#	define api_callconv
#endif

#ifdef NGEN_EXPORT
#  define ngen_api api_export
#else
#  define ngen_api api_import
#endif
#define ngen_callconv api_callconv
#define ngen_api_private api_private

#if _tkn_NoThrow_ == _tknval_True
#	define THROW(e)
#else
#	define THROW(e) throw e
#endif

#if _tkn_Compiler == _tknval_Compiler_GCC
#  define ngen_inline inline __attribute__((__alaways_inline__))
#  define ngen_noinline __attribute__((__noinline__))
#elif _tkn_Compile == _tknval_Compiler_MSVC
#  define ngen_inline __forceinline
#  define ngen_noinline __declspec(noinline)
#else

#endif

#define _tkn_Mute 9999991

#endif // __NGEN_BUILD_LOGIC_HPP
