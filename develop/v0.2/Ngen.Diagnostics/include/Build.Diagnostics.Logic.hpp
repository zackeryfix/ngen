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
#ifndef __NGEN_BUILD_DIAGNOSTICS_LOGIC_HPP
#define __NGEN_BUILD_DIAGNOSTICS_LOGIC_HPP

#include "Ngen.hpp"

/** @brief Used to export or import public symbols from the framework. */
#if TKN_PLATFORMID == TKNVAL_PLATFORMID_WINDOWS
#  if defined(NGEN_DIAGNOSTICS_EXPORT)
#     define ngen_diagnostics_api __declspec(dllexport)
#  else
#     if defined(__MINGW32__)
#        define ngen_diagnostics_api
#     else
#        define ngen_diagnostics_api __declspec(dllimport)
#     endif
#  endif
   /** @brief Used to export or import private symbols from the framework. */
#  define ngen_diagnostics_api_private
   /** @brief Used to determine the calling convection to use for a specific routine. */
#	if defined(_STDCALL_SUPPORTED)
#     define ngen_diagnostics_callconv __stdcall
#	else
#		define ngen_diagnostics_callconv __cdecl
#	endif
#else // other supported platforms (Linux, MacOSX and iPhone)
#	if (__GNUC__ >= 4) && defined(NGEN_DIAGNOSTICS_EXPORT)
#		define ngen_diagnostics_api __attribute__ ((visibility("default")))
      /** @brief Used to export or import private symbols from the framework. */
#		define ngen_diagnostics_api_private __attribute__ ((visibility("hidden")))
#	else
#     define ngen_diagnostics_api
      /** @brief Used to export or import private symbols from the framework. */
#     define ngen_diagnostics_api_private
#	endif
   /** @brief Used to determine the calling convection to use for a specific routine. */
#	define ngen_diagnostics_callconv
#endif

#endif // __NGEN_BUILD_DIAGNOSTICS_LOGIC_HPP
