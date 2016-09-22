//===================== Copyright (C) 2016 Joshua Ashton =====================//
//============================ Licenced Under MIT ============================//
/*!	\file Common.h
	\brief Contains a lot of basic definitions and useful macros.
*/

#ifndef EPHEMERAL_COMMON_H
#define EPHEMERAL_COMMON_H

#include <stdint.h> // For types
#include <assert.h> // For assert

// Exporting setup.
#ifdef EPHEMERAL_STATIC
#define EPHEMERAL_EXPORT
#elif EPHEMERAL_EXPORTS 
#define EPHEMERAL_EXPORT __declspec(dllexport)
#else
#define EPHEMERAL_EXPORT __declspec(dllimport)
#endif

// Are we x64 or x32?
#if defined(_WIN64) || defined (__x86_64__) || defined (_M_X64) || defined (_M_AMD64) || defined(__ppc64__) || defined(__WIN64) || defined(WIN64)
#define EPHEMERAL_ARCHITECTURE_X64
#else
#define EPHEMERAL_ARCHITECTURE_X32
#endif

// What is our compiler?
#if defined(__clang__)
#define EPHEMERAL_COMPILER_CLANG
#elif defined(_MSC_VER)
#define EPHEMERAL_COMPILER_MSVC
#elif defined(__GNUC__) || defined(__GNUG__) && !(defined(__clang__))
#define EPHEMERAL_COMPILER_GNU_GCC
#elif defined(__INTEL_COMPILER)
#define EPHEMERAL_COMPILER_INTEL
#endif

// What operating system are we running on?
#if defined(_WIN32) || defined (_WIN64) || defined (__WIN32) || defined (__WIN64) || defined (WIN32) || defined (WIN64)
#define EPHEMERAL_SYSTEM_WINDOWS
#elif defined (__APPLE__) && defined(__MACH__)
#define EPHEMERAL_SYSTEM_OSX
#define EPHEMERAL_SYSTEM_UNIX
#elif defined (__unix__)
#define EPHEMERAL_SYSTEM_UNIX
#if defined (__linux__)
#define EPHEMERAL_SYSTEM_LINUX
#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
#define EPHEMERAL_SYSTEM_FREEBSD
#else
#define EPHEMERAL_SYSTEM_OTHER_UNIX
#endif
#else
#endif

#if defined(_DEBUG) && !defined(EPHEMERAL_DISABLE_ASSERTS)
#define EPHEMERAL_ASSERT(x) assert(x)
#else
#define EPHEMERAL_ASSERT(x)
#endif

// Compiler weirdness... It gives the function the constructor attribute so it is run on startup.
#ifdef EPHEMERAL_COMPILER_MSVC
  #define EPHEMERAL_PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop) )
  #pragma section(".CRT$XCU",read)
  #define EPHEMERAL_INITIALISER2_(f,p) \
    static void f(void); \
    __declspec(allocate(".CRT$XCU")) void (*f##_)(void) = f; \
    __pragma(comment(linker,"/include:" p #f "_")) \
    static void f(void)
  #ifdef EPHEMERAL_ARCHITECTURE_X64
    #define EPHEMERAL_INITIALISER_NEARLY(f) EPHEMERAL_INITIALISER2_(f,"")
  #else
    #define EPHEMERAL_INITIALISER_NEARLY(f) EPHEMERAL_INITIALISER2_(f,"_")
  #endif
#else
  #define EPHEMERAL_PACK( __Declaration__ ) __Declaration__ __attribute__((__packed__))
  #define EPHEMERAL_INITIALISER_NEARLY(f) \
    static void f(void) __attribute__((constructor)); \
    static void f(void)
#endif

/*!	\def EPHEMERAL_INITIALISER(function)
	\brief Makes a function run at program/dll initialisation.
*/
#define EPHEMERAL_INITIALISER(f) EPHEMERAL_INITIALISER_NEARLY(f)

#endif
