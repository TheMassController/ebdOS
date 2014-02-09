L 1 "../src/task.c"
N/*
N * task.h
N *
N *  Created on: 12 nov. 2013
N *      Author: VersD @ hr.nl
N *
N */
N#include <stdlib.h>
L 1 "C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdlib.h" 1
N/*****************************************************************************/
N/* stdlib.h   v4.9.9                                                         */
N/*                                                                           */
N/* Copyright (c) 1993-2013 Texas Instruments Incorporated                    */
N/* http://www.ti.com/                                                        */
N/*                                                                           */
N/*  Redistribution and  use in source  and binary forms, with  or without    */
N/*  modification,  are permitted provided  that the  following conditions    */
N/*  are met:                                                                 */
N/*                                                                           */
N/*     Redistributions  of source  code must  retain the  above copyright    */
N/*     notice, this list of conditions and the following disclaimer.         */
N/*                                                                           */
N/*     Redistributions in binary form  must reproduce the above copyright    */
N/*     notice, this  list of conditions  and the following  disclaimer in    */
N/*     the  documentation  and/or   other  materials  provided  with  the    */
N/*     distribution.                                                         */
N/*                                                                           */
N/*     Neither the  name of Texas Instruments Incorporated  nor the names    */
N/*     of its  contributors may  be used to  endorse or  promote products    */
N/*     derived  from   this  software  without   specific  prior  written    */
N/*     permission.                                                           */
N/*                                                                           */
N/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS    */
N/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT    */
N/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    */
N/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT    */
N/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    */
N/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT    */
N/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    */
N/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    */
N/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT    */
N/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    */
N/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     */
N/*                                                                           */
N/*****************************************************************************/
N
N#ifndef _STDLIB
N#define _STDLIB
N
N/*---------------------------------------------------------------------------*/
N/* Attributes are only available in relaxed ANSI mode.                       */
N/*---------------------------------------------------------------------------*/
N#ifndef __ATTRIBUTE
N#if __TI_STRICT_ANSI_MODE__
X#if 0
S#define __ATTRIBUTE(attr)
N#else
N#define __ATTRIBUTE(attr) __attribute__(attr)
N#endif
N#endif
N
N/*---------------------------------------------------------------------------*/
N/* A header file conforming to ARM CLIB ABI (GENC-003539), should            */
N/* define _AEABI_PORTABLE when _AEABI_PORTABILITY_LEVEL is defined.          */
N/*---------------------------------------------------------------------------*/
N#if defined(_AEABI_PORTABILITY_LEVEL) && !defined(_AEABI_PORTABLE)
X#if 0L && !0L
S#define _AEABI_PORTABLE
N#endif
N
N/*---------------------------------------------------------------------------*/
N/* The macro definition that guards CLIB ABI (GENC-003539) requirements.     */
N/*---------------------------------------------------------------------------*/
N#if defined(__TI_EABI_SUPPORT__)
X#if 1L
N#define _AEABI_PORTABILITY_CHECK (defined(__TMS470__) && \
N	                          defined(__TI_EABI_SUPPORT__) && \
N	                          _AEABI_PORTABILITY_LEVEL != 0)
X#define _AEABI_PORTABILITY_CHECK (defined(__TMS470__) && 	                          defined(__TI_EABI_SUPPORT__) && 	                          _AEABI_PORTABILITY_LEVEL != 0)
N#else
S#define _AEABI_PORTABILITY_CHECK 0
N#endif
N
N#ifdef __cplusplus
S//----------------------------------------------------------------------------
S// <cstdlib> IS RECOMMENDED OVER <stdlib.h>.  <stdlib.h> IS PROVIDED FOR 
S// COMPATIBILITY WITH C AND THIS USAGE IS DEPRECATED IN C++
S//----------------------------------------------------------------------------
Sextern "C" namespace std {
N#endif /* !__cplusplus */
N
Ntypedef struct { int quot, rem; } div_t;
N
Ntypedef struct { int quot, rem; } ldiv_t;
N
N#define _LLONG_AVAILABLE 1
Ntypedef struct { long long quot, rem; } lldiv_t;
N
N#if _AEABI_PORTABILITY_CHECK
X#if (1L && 1L && _AEABI_PORTABILITY_LEVEL != 0)
Sextern int __aeabi_MB_CUR_MAX(void);
S#define MB_CUR_MAX ( __aeabi_MB_CUR_MAX() )
N#else
N#define MB_CUR_MAX    1
N#endif /* _AEABI_PORTABILITY_CHECK */
N
N#ifndef NULL
N#define NULL          0
N#endif
N
N#ifndef _SIZE_T
N#define _SIZE_T
Ntypedef __SIZE_T_TYPE__ size_t;
Xtypedef unsigned size_t;
N#endif
N
N#ifndef __cplusplus
N#ifndef _WCHAR_T
N#define _WCHAR_T
Ntypedef __WCHAR_T_TYPE__ wchar_t;
Xtypedef unsigned short wchar_t;
N#endif
N#endif
N
N#define EXIT_FAILURE  1
N#define EXIT_SUCCESS  0
N
N#define RAND_MAX      32767
N
N#include <linkage.h>
L 1 "C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/linkage.h" 1
N/*****************************************************************************/
N/* linkage.h   v4.9.9                                                        */
N/*                                                                           */
N/* Copyright (c) 1998-2013 Texas Instruments Incorporated                    */
N/* http://www.ti.com/                                                        */
N/*                                                                           */
N/*  Redistribution and  use in source  and binary forms, with  or without    */
N/*  modification,  are permitted provided  that the  following conditions    */
N/*  are met:                                                                 */
N/*                                                                           */
N/*     Redistributions  of source  code must  retain the  above copyright    */
N/*     notice, this list of conditions and the following disclaimer.         */
N/*                                                                           */
N/*     Redistributions in binary form  must reproduce the above copyright    */
N/*     notice, this  list of conditions  and the following  disclaimer in    */
N/*     the  documentation  and/or   other  materials  provided  with  the    */
N/*     distribution.                                                         */
N/*                                                                           */
N/*     Neither the  name of Texas Instruments Incorporated  nor the names    */
N/*     of its  contributors may  be used to  endorse or  promote products    */
N/*     derived  from   this  software  without   specific  prior  written    */
N/*     permission.                                                           */
N/*                                                                           */
N/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS    */
N/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT    */
N/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    */
N/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT    */
N/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    */
N/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT    */
N/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    */
N/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    */
N/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT    */
N/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    */
N/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     */
N/*                                                                           */
N/*****************************************************************************/
N
N#ifndef _LINKAGE
N#define _LINKAGE
N
N/* No modifiers are needed to access code or data */
N
N#define _CODE_ACCESS
N#define _DATA_ACCESS
N#define _DATA_ACCESS_NEAR
N
N/*--------------------------------------------------------------------------*/
N/* Define _IDECL ==> how inline functions are declared                      */
N/*--------------------------------------------------------------------------*/
N#ifdef _INLINE
S#define _IDECL static __inline
S#define _IDEFN static __inline
S#define __INLINE static __inline
N#else
N#define _IDECL extern _CODE_ACCESS
N#define _IDEFN _CODE_ACCESS
N#define __INLINE __EXTERN
N#endif
N
N#endif /* ifndef _LINKAGE */
L 115 "C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdlib.h" 2
N
N/*---------------------------------------------------------------*/
N/* NOTE - Normally, abs, labs, and fabs are expanded inline, so  */
N/*        no formal definition is really required. However, ANSI */
N/*        requires that they exist as separate functions, so     */
N/*        they are supplied in the library.  The prototype is    */
N/*        here mainly for documentation.                         */
N/*---------------------------------------------------------------*/
N    _CODE_ACCESS  int       abs(int _val); 
X      int       abs(int _val); 
N    _CODE_ACCESS  long      labs(long _val);
X      long      labs(long _val);
N#if defined(_LLONG_AVAILABLE)
X#if 1L
N    _CODE_ACCESS  long long llabs(long long _val);
X      long long llabs(long long _val);
N#endif
N    _CODE_ACCESS int       atoi(const char *_st);
X     int       atoi(const char *_st);
N    _CODE_ACCESS long      atol(const char *_st);
X     long      atol(const char *_st);
N#if defined(_LLONG_AVAILABLE)
X#if 1L
N    _CODE_ACCESS long long atoll(const char *_st);
X     long long atoll(const char *_st);
N#endif
N    _CODE_ACCESS int       ltoa(long val, char *buffer);
X     int       ltoa(long val, char *buffer);
N          _IDECL double    atof(const char *_st);
X          extern  double    atof(const char *_st);
N
N    _CODE_ACCESS long      strtol(const char *_st, char **_endptr, int _base);
X     long      strtol(const char *_st, char **_endptr, int _base);
N    _CODE_ACCESS unsigned long strtoul(const char *_st, char **_endptr,
X     unsigned long strtoul(const char *_st, char **_endptr,
N    					  int _base);
N#if defined(_LLONG_AVAILABLE)
X#if 1L
N    _CODE_ACCESS long long strtoll(const char *_st, char **_endptr, int _base);
X     long long strtoll(const char *_st, char **_endptr, int _base);
N    _CODE_ACCESS unsigned long long strtoull(const char *_st, char **_endptr,
X     unsigned long long strtoull(const char *_st, char **_endptr,
N					     int _base);
N#endif
N    _CODE_ACCESS double    strtod(const char *_st, char **_endptr);
X     double    strtod(const char *_st, char **_endptr);
N    _CODE_ACCESS long double strtold(const char *_st, char **_endptr);
X     long double strtold(const char *_st, char **_endptr);
N    
N    _CODE_ACCESS int    rand(void);
X     int    rand(void);
N    _CODE_ACCESS void   srand(unsigned _seed);
X     void   srand(unsigned _seed);
N    
N    _CODE_ACCESS void  *calloc(size_t _num, size_t _size)
X     void  *calloc(size_t _num, size_t _size)
N               __ATTRIBUTE((malloc));
X               __attribute__((malloc));
N    _CODE_ACCESS void  *malloc(size_t _size)
X     void  *malloc(size_t _size)
N               __ATTRIBUTE((malloc));
X               __attribute__((malloc));
N    _CODE_ACCESS void  *realloc(void *_ptr, size_t _size)
X     void  *realloc(void *_ptr, size_t _size)
N               __ATTRIBUTE((malloc));
X               __attribute__((malloc));
N    _CODE_ACCESS void   free(void *_ptr);
X     void   free(void *_ptr);
N    _CODE_ACCESS void  *memalign(size_t _aln, size_t _size)
X     void  *memalign(size_t _aln, size_t _size)
N               __ATTRIBUTE((malloc));
X               __attribute__((malloc));
N    
N    _CODE_ACCESS void   abort(void); 
X     void   abort(void); 
N
N    typedef void (*__TI_atexit_fn)(void);
N    _CODE_ACCESS int    atexit(__TI_atexit_fn _func);
X     int    atexit(__TI_atexit_fn _func);
N
N    typedef int (*__TI_compar_fn)(const void *,const void *);
N    _CODE_ACCESS void  *bsearch(const void *_key, const void *_base,
X     void  *bsearch(const void *_key, const void *_base,
N                                size_t _nmemb, size_t _size, 
N                                __TI_compar_fn compar);
N    _CODE_ACCESS void   qsort(void *_base, size_t _nmemb, size_t _size, 
X     void   qsort(void *_base, size_t _nmemb, size_t _size, 
N                              __TI_compar_fn compar);
N
N    _CODE_ACCESS void   exit(int _status);
X     void   exit(int _status);
N    
N    _CODE_ACCESS div_t  div(int _numer, int _denom);
X     div_t  div(int _numer, int _denom);
N    _CODE_ACCESS ldiv_t ldiv(long _numer, long _denom);
X     ldiv_t ldiv(long _numer, long _denom);
N#if defined(_LLONG_AVAILABLE)
X#if 1L
N    _CODE_ACCESS lldiv_t lldiv(long long _numer, long long _denom);
X     lldiv_t lldiv(long long _numer, long long _denom);
N#endif
N
N    _CODE_ACCESS char  *getenv(const char *_string);
X     char  *getenv(const char *_string);
N    _CODE_ACCESS int    system(const char *_name);
X     int    system(const char *_name);
N
N    _CODE_ACCESS int    mblen(const char *, size_t);
X     int    mblen(const char *, size_t);
N    _CODE_ACCESS size_t mbstowcs(wchar_t *, const char *, size_t);
X     size_t mbstowcs(wchar_t *, const char *, size_t);
N    _CODE_ACCESS int    mbtowc(wchar_t *, const char *, size_t);
X     int    mbtowc(wchar_t *, const char *, size_t);
N
N    _CODE_ACCESS size_t wcstombs(char *, const wchar_t *, size_t);
X     size_t wcstombs(char *, const wchar_t *, size_t);
N    _CODE_ACCESS int    wctomb(char *, wchar_t);
X     int    wctomb(char *, wchar_t);
N
N#ifdef __cplusplus
S} /* extern "C" namespace std */
N#endif /* __cplusplus */
N
N
N#ifdef _INLINE
S
S#ifdef __cplusplus
Snamespace std {
S#endif
S
Sstatic __inline double atof(const char *_st) 
S{
S  return strtod(_st, (char **)0); 
S}
S
S#ifdef __cplusplus
S} /* namespace std */
S#endif
S
N#endif  /* _INLINE */
N
N#ifdef __cplusplus
S#if __TI_STRICT_ANSI_MODE__
Snamespace std {
S    _CODE_ACCESS inline int atexit(void (*func)(void))
S        {
S            return atexit((__TI_atexit_fn)func);
S        }
S
S    _CODE_ACCESS inline void  *bsearch(const void *_key, const void *_base,
S                                       size_t _nmemb, size_t _size, 
S                                       int (*compar)(const void *,const void *))
S        {
S            return bsearch(_key, _base, _nmemb, _size, (__TI_compar_fn)compar);
S        }
S
S    _CODE_ACCESS inline void   qsort(void *_base, size_t _nmemb, size_t _size, 
S                                     int (*_compar)(const void *, const void *))
S        {
S            return qsort(_base, _nmemb, _size, (__TI_compar_fn)_compar);
S        }
S}
S#endif
N#endif
N
N#endif  /* ! _STDLIB */
N
N#if defined(__cplusplus) && !defined(_CPP_STYLE_HEADER)
X#if 0L && !0L
Susing std::div_t;
Susing std::ldiv_t;
S#if defined(_LLONG_AVAILABLE)
Susing std::lldiv_t;
S#endif
Susing std::size_t;
Susing std::abs;
Susing std::labs;
Susing std::atoi;
Susing std::atol;
S#if defined(_LLONG_AVAILABLE)
Susing std::llabs;
Susing std::atoll;
S#endif
Susing std::atof;
Susing std::strtol;
Susing std::strtoul;
S#if defined(_LLONG_AVAILABLE)
Susing std::strtoll;
Susing std::strtoull;
S#endif
Susing std::strtod;
Susing std::rand;
Susing std::srand;
Susing std::calloc;
Susing std::malloc;
Susing std::realloc;
Susing std::free;
Susing std::memalign;
Susing std::abort;
Susing std::atexit;
Susing std::bsearch;
Susing std::qsort;
Susing std::exit;
Susing std::div;
Susing std::ldiv;
S#if defined(_LLONG_AVAILABLE)
Susing std::lldiv;
S#endif
Susing std::getenv;
Susing std::system;
S#if _AEABI_PORTABILITY_CHECK
Susing std::__aeabi_MB_CUR_MAX;
S#endif /* _AEABI_PORTABILITY_CHECK */
N#endif /* ! _CPP_STYLE_HEADER */
N
L 9 "../src/task.c" 2
N#include "task.h"
L 1 "..\src\task.h" 1
N/*
N * task.h
N *
N *  Created on: 12 nov. 2013
N *      Author: VersD @ hr.nl
N *
N */
N
N#ifndef TASK_H_
N#define TASK_H_
N
N#include <stdint.h>
L 1 "C:/ti/ccsv5/tools/compiler/arm_4.9.9/include/stdint.h" 1
N/*****************************************************************************/
N/* STDINT.H v4.9.9                                                           */
N/*                                                                           */
N/* Copyright (c) 2002-2013 Texas Instruments Incorporated                    */
N/* http://www.ti.com/                                                        */
N/*                                                                           */
N/*  Redistribution and  use in source  and binary forms, with  or without    */
N/*  modification,  are permitted provided  that the  following conditions    */
N/*  are met:                                                                 */
N/*                                                                           */
N/*     Redistributions  of source  code must  retain the  above copyright    */
N/*     notice, this list of conditions and the following disclaimer.         */
N/*                                                                           */
N/*     Redistributions in binary form  must reproduce the above copyright    */
N/*     notice, this  list of conditions  and the following  disclaimer in    */
N/*     the  documentation  and/or   other  materials  provided  with  the    */
N/*     distribution.                                                         */
N/*                                                                           */
N/*     Neither the  name of Texas Instruments Incorporated  nor the names    */
N/*     of its  contributors may  be used to  endorse or  promote products    */
N/*     derived  from   this  software  without   specific  prior  written    */
N/*     permission.                                                           */
N/*                                                                           */
N/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS    */
N/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT    */
N/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    */
N/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT    */
N/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    */
N/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT    */
N/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    */
N/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    */
N/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT    */
N/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    */
N/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     */
N/*                                                                           */
N/*****************************************************************************/
N#ifndef _STDINT_H_
N#define _STDINT_H_
N
N/* 7.18.1.1 Exact-width integer types */
N
N    typedef   signed char   int8_t;
N    typedef unsigned char  uint8_t;
N    typedef          short  int16_t;
N    typedef unsigned short uint16_t;
N    typedef          int    int32_t;
N    typedef unsigned int   uint32_t;
N
N
N    typedef          long long  int64_t;
N    typedef unsigned long long uint64_t;
N
N/* 7.18.1.2 Minimum-width integer types */
N
N    typedef  int8_t   int_least8_t;
N    typedef uint8_t  uint_least8_t;
N
N    typedef  int16_t  int_least16_t;
N    typedef uint16_t uint_least16_t;
N    typedef  int32_t  int_least32_t;
N    typedef uint32_t uint_least32_t;
N
N
N    typedef  int64_t  int_least64_t;
N    typedef uint64_t uint_least64_t;
N
N/* 7.18.1.3 Fastest minimum-width integer types */
N
N    typedef  int32_t  int_fast8_t;
N    typedef uint32_t uint_fast8_t;
N    typedef  int32_t  int_fast16_t;
N    typedef uint32_t uint_fast16_t;
N
N    typedef  int32_t  int_fast32_t;
N    typedef uint32_t uint_fast32_t;
N
N
N    typedef  int64_t  int_fast64_t;
N    typedef uint64_t uint_fast64_t;
N
N/* 7.18.1.4 Integer types capable of holding object pointers */
N    typedef          int intptr_t;
N    typedef unsigned int uintptr_t;
N
N/* 7.18.1.5 Greatest-width integer types */
N    typedef          long long intmax_t;
N    typedef unsigned long long uintmax_t;
N
N/* 
N   According to footnotes in the 1999 C standard, "C++ implementations
N   should define these macros only when __STDC_LIMIT_MACROS is defined
N   before <stdint.h> is included." 
N*/
N#if !defined(__cplusplus) || defined(__STDC_LIMIT_MACROS)
X#if !0L || 0L
N
N/* 7.18.2 Limits of specified width integer types */
N
N    #define  INT8_MAX   0x7f
N    #define  INT8_MIN   (-INT8_MAX-1)
N    #define UINT8_MAX   0xff
N
N    #define  INT16_MAX  0x7fff
N    #define  INT16_MIN  (-INT16_MAX-1)
N    #define UINT16_MAX  0xffff
N
N    #define  INT32_MAX  0x7fffffff
N    #define  INT32_MIN  (-INT32_MAX-1)
N    #define UINT32_MAX  0xffffffff
N
N
N    #define  INT64_MAX  0x7fffffffffffffff
N    #define  INT64_MIN  (-INT64_MAX-1)
N    #define UINT64_MAX  0xffffffffffffffff
N
N    #define  INT_LEAST8_MAX   (INT8_MAX)
N    #define  INT_LEAST8_MIN   (INT8_MIN)
N    #define UINT_LEAST8_MAX   (UINT8_MAX)
N
N    #define  INT_LEAST16_MAX  (INT16_MAX)
N    #define  INT_LEAST16_MIN  (INT16_MIN)
N    #define UINT_LEAST16_MAX  (UINT16_MAX)
N    #define  INT_LEAST32_MAX  (INT32_MAX)
N    #define  INT_LEAST32_MIN  (INT32_MIN)
N    #define UINT_LEAST32_MAX  (UINT32_MAX)
N
N
N    #define  INT_LEAST64_MAX  (INT64_MAX)
N    #define  INT_LEAST64_MIN  (INT64_MIN)
N    #define UINT_LEAST64_MAX  (UINT64_MAX)
N
N    #define  INT_FAST8_MAX   (INT32_MAX)
N    #define  INT_FAST8_MIN   (INT32_MIN)
N    #define UINT_FAST8_MAX   (UINT32_MAX)
N    #define  INT_FAST16_MAX  (INT32_MAX)
N    #define  INT_FAST16_MIN  (INT32_MIN)
N    #define UINT_FAST16_MAX  (UINT32_MAX)
N
N    #define  INT_FAST32_MAX  (INT32_MAX)
N    #define  INT_FAST32_MIN  (INT32_MIN)
N    #define UINT_FAST32_MAX  (UINT32_MAX)
N
N
N    #define  INT_FAST64_MAX  (INT64_MAX)
N    #define  INT_FAST64_MIN  (INT64_MIN)
N    #define UINT_FAST64_MAX  (UINT64_MAX)
N
N    #define INTPTR_MAX   (INT32_MAX)
N    #define INTPTR_MIN   (INT32_MIN)
N    #define UINTPTR_MAX  (UINT32_MAX)
N
N    #define INTMAX_MIN   (INT64_MIN)
N    #define INTMAX_MAX   (INT64_MAX)
N    #define UINTMAX_MAX  (UINT64_MAX)
N
N/* 7.18.3 Limits of other integer types */
N
N    #define PTRDIFF_MAX (INT32_MAX)
N    #define PTRDIFF_MIN (INT32_MIN)
N
N    #define SIG_ATOMIC_MIN (INT32_MIN)
N    #define SIG_ATOMIC_MAX (INT32_MAX)
N
N    #define SIZE_MAX (INT32_MAX)
N
N#ifndef WCHAR_MAX
N#define WCHAR_MAX 0xffffu
N#endif
N
N#ifndef WCHAR_MIN
N#define WCHAR_MIN 0
N#endif
N
N    #define WINT_MIN (INT32_MIN)
N    #define WINT_MAX (INT32_MAX)
N
N/* 7.18.4.1 Macros for minimum-width integer constants */
N
N/*
N   There is a defect report filed against the C99 standard concerning how 
N   the (U)INTN_C macros should be implemented.  Please refer to --
N   http://wwwold.dkuug.dk/JTC1/SC22/WG14/www/docs/dr_209.htm 
N   for more information.  These macros are implemented according to the
N   suggestion given at this web site.
N*/
N
N    #define  INT8_C(value)  ((int_least8_t)(value))
N    #define UINT8_C(value)  ((uint_least8_t)(value))
N    #define  INT16_C(value) ((int_least16_t)(value))
N    #define UINT16_C(value) ((uint_least16_t)(value))
N    #define  INT32_C(value) ((int_least32_t)(value))
N    #define UINT32_C(value) ((uint_least32_t)(value))
N
N
N    #define  INT64_C(value) ((int_least64_t)(value))
N    #define UINT64_C(value) ((uint_least64_t)(value))
N
N/* 7.18.4.2 Macros for greatest-width integer constants */
N
N    #define  INTMAX_C(value) ((intmax_t)(value))
N    #define UINTMAX_C(value) ((uintmax_t)(value))
N
N#endif /* !defined(__cplusplus) || defined(__STDC_LIMIT_MACROS) */
N
N#endif /* _STDINT_H_ */
L 13 "..\src\task.h" 2
N
N#define MAX_TASKS 16
N#define TASK_MASK 0x0000000F
N
N//What states can our task have?
Nenum taskState{RUNNING, READY, WAITING};
N
N//The task itself
Ntypedef struct _task{
N	int * 			stack; 				//pointer to the stack (on the heap?)
N
N	void(*function)(void);				//function to execute
N	enum taskState	state;				//Tasks have a state
N	uint8_t 		uiPriority;			//Tasks have a priority
N	uint32_t		uiCounter;			//Tasks have a counter for delays
N
N	char			bInitialized;
N} task;
N
N//Add new task to the taskList
Nvoid addTaskToList(void(*function)(void), int stackSize, int priority);
N
N#endif /* TASK_H_ */
L 10 "../src/task.c" 2
N#include "schedule.h"
L 1 "..\src\schedule.h" 1
N/*
N * schedule.h
N *
N *  Created on: 12 nov. 2013
N *      Author: VersD @ hr.nl
N *
N */
N
N#ifndef SCHEDULE_H_
N#define SCHEDULE_H_
N
N#include "task.h"
N
N#define MAIN_RETURN 	0xFFFFFFF9 //Tells the handler to return using the MSP
N#define THREAD_RETURN 	0xFFFFFFFD //Tells the handler to return using the PSP
N
N//The ISR functions
Nvoid SystickISR(void);
Nvoid PendSVISR(void);
N
N//The (external) assembly functions
Nvoid pushRegistersToCurrentPSP(int iVar);
Nvoid popRegistersFromCurrentPSP(int iVar);
Nvoid * readPSP(int iVar);
Nvoid writePSP(void * ptr);
Nvoid * readMSP(int iVar);
Nvoid writeMSP(void * ptr);
N
N//The Scheduler
Ntask * getNextTask();
N
N#endif /* SCHEDULE_H_ */
L 11 "../src/task.c" 2
N
N//Array of tasks
Ntask taskList[MAX_TASKS];
Xtask taskList[16];
N
N//currentTask used by the scheduler
Nextern task * currentTask;
N
N
N/*
N * Function to add a new task to the taskList
N * Not sorted, prioritized or any of that kind.
N *
N * It simply allocates memory for the new task stack,
N * fills the stack up so that the context switch will
N * successfully pop these registers and start running
N * at the correct address when returning from the ISR
N */
Nvoid addTaskToList(void(*function)(void), int stackSize, int priority)
N{
N	uint8_t i=0;
N
N	//Simply find the next empty spot
N	while(taskList[i].function != 0){
N		//increment i and roll back at the limit
N		i++;
N		i &= TASK_MASK;
X		i &= 0x0000000F;
N	}
N
N	//The new and latest task will become the currentTask
N	currentTask = &taskList[i];
N
N	currentTask->function = function;
N
N	//Allocate memory... do we wanna use malloc??
N	currentTask->stack = (int *)malloc(stackSize)+stackSize;
N
N	//now we initialize the stack for when we return the first time from the scheduler
N	//This is the 'hardware' stack
N	*((currentTask->stack)--) 	= 0x01000000;					//XSPR	nothing special , no fpu etc.
N	*((currentTask->stack)--) 	= (int)currentTask->function; 	//set PC to function pointer, cast as int to silence the compiler
N	*((currentTask->stack)--) 	= 0xFFFFFFFD;					//LR
N	*((currentTask->stack)--) 	= 0x0000000C;					//R12	Initial values used for debugging purposes
N	*((currentTask->stack)--) 	= 0x00000003;					//R3
N	*((currentTask->stack)--) 	= 0x00000002;					//R2
N	*((currentTask->stack)--) 	= 0x00000001;					//R1
N	*((currentTask->stack)) 	= 0x00000000;					//R0
N
N	//Update the CPU PSP with our new stack pointer
N	writePSP(currentTask->stack);
N
N	/*
N	 * Initialize the task properties
N	 */
N	currentTask->state 			= READY;
N	currentTask->bInitialized 	= 0;
N	currentTask->uiPriority 	= priority;
N
N
N	return;
N}
