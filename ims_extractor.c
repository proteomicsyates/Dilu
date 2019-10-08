#define PY_SSIZE_T_CLEAN
#include "Python.h"
#ifndef Py_PYTHON_H
    #error Python headers needed to compile C extensions, please install development version of Python.
#elif PY_VERSION_HEX < 0x02060000 || (0x03000000 <= PY_VERSION_HEX && PY_VERSION_HEX < 0x03020000)
    #error Cython requires Python 2.6+ or Python 3.2+.
#else
#define CYTHON_ABI "0_25_2"
#include <stddef.h>
#ifndef offsetof
  #define offsetof(type, member) ( (size_t) & ((type*)0) -> member )
#endif
#if !defined(WIN32) && !defined(MS_WINDOWS)
  #ifndef __stdcall
    #define __stdcall
  #endif
  #ifndef __cdecl
    #define __cdecl
  #endif
  #ifndef __fastcall
    #define __fastcall
  #endif
#endif
#ifndef DL_IMPORT
  #define DL_IMPORT(t) t
#endif
#ifndef DL_EXPORT
  #define DL_EXPORT(t) t
#endif
#ifndef HAVE_LONG_LONG
  #if PY_VERSION_HEX >= 0x03030000 || (PY_MAJOR_VERSION == 2 && PY_VERSION_HEX >= 0x02070000)
    #define HAVE_LONG_LONG
  #endif
#endif
#ifndef PY_LONG_LONG
  #define PY_LONG_LONG LONG_LONG
#endif
#ifndef Py_HUGE_VAL
  #define Py_HUGE_VAL HUGE_VAL
#endif
#ifdef PYPY_VERSION
  #define CYTHON_COMPILING_IN_PYPY 1
  #define CYTHON_COMPILING_IN_PYSTON 0
  #define CYTHON_COMPILING_IN_CPYTHON 0
  #undef CYTHON_USE_TYPE_SLOTS
  #define CYTHON_USE_TYPE_SLOTS 0
  #undef CYTHON_USE_ASYNC_SLOTS
  #define CYTHON_USE_ASYNC_SLOTS 0
  #undef CYTHON_USE_PYLIST_INTERNALS
  #define CYTHON_USE_PYLIST_INTERNALS 0
  #undef CYTHON_USE_UNICODE_INTERNALS
  #define CYTHON_USE_UNICODE_INTERNALS 0
  #undef CYTHON_USE_UNICODE_WRITER
  #define CYTHON_USE_UNICODE_WRITER 0
  #undef CYTHON_USE_PYLONG_INTERNALS
  #define CYTHON_USE_PYLONG_INTERNALS 0
  #undef CYTHON_AVOID_BORROWED_REFS
  #define CYTHON_AVOID_BORROWED_REFS 1
  #undef CYTHON_ASSUME_SAFE_MACROS
  #define CYTHON_ASSUME_SAFE_MACROS 0
  #undef CYTHON_UNPACK_METHODS
  #define CYTHON_UNPACK_METHODS 0
  #undef CYTHON_FAST_THREAD_STATE
  #define CYTHON_FAST_THREAD_STATE 0
  #undef CYTHON_FAST_PYCALL
  #define CYTHON_FAST_PYCALL 0
#elif defined(PYSTON_VERSION)
  #define CYTHON_COMPILING_IN_PYPY 0
  #define CYTHON_COMPILING_IN_PYSTON 1
  #define CYTHON_COMPILING_IN_CPYTHON 0
  #ifndef CYTHON_USE_TYPE_SLOTS
    #define CYTHON_USE_TYPE_SLOTS 1
  #endif
  #undef CYTHON_USE_ASYNC_SLOTS
  #define CYTHON_USE_ASYNC_SLOTS 0
  #undef CYTHON_USE_PYLIST_INTERNALS
  #define CYTHON_USE_PYLIST_INTERNALS 0
  #ifndef CYTHON_USE_UNICODE_INTERNALS
    #define CYTHON_USE_UNICODE_INTERNALS 1
  #endif
  #undef CYTHON_USE_UNICODE_WRITER
  #define CYTHON_USE_UNICODE_WRITER 0
  #undef CYTHON_USE_PYLONG_INTERNALS
  #define CYTHON_USE_PYLONG_INTERNALS 0
  #ifndef CYTHON_AVOID_BORROWED_REFS
    #define CYTHON_AVOID_BORROWED_REFS 0
  #endif
  #ifndef CYTHON_ASSUME_SAFE_MACROS
    #define CYTHON_ASSUME_SAFE_MACROS 1
  #endif
  #ifndef CYTHON_UNPACK_METHODS
    #define CYTHON_UNPACK_METHODS 1
  #endif
  #undef CYTHON_FAST_THREAD_STATE
  #define CYTHON_FAST_THREAD_STATE 0
  #undef CYTHON_FAST_PYCALL
  #define CYTHON_FAST_PYCALL 0
#else
  #define CYTHON_COMPILING_IN_PYPY 0
  #define CYTHON_COMPILING_IN_PYSTON 0
  #define CYTHON_COMPILING_IN_CPYTHON 1
  #ifndef CYTHON_USE_TYPE_SLOTS
    #define CYTHON_USE_TYPE_SLOTS 1
  #endif
  #if PY_MAJOR_VERSION < 3
    #undef CYTHON_USE_ASYNC_SLOTS
    #define CYTHON_USE_ASYNC_SLOTS 0
  #elif !defined(CYTHON_USE_ASYNC_SLOTS)
    #define CYTHON_USE_ASYNC_SLOTS 1
  #endif
  #if PY_VERSION_HEX < 0x02070000
    #undef CYTHON_USE_PYLONG_INTERNALS
    #define CYTHON_USE_PYLONG_INTERNALS 0
  #elif !defined(CYTHON_USE_PYLONG_INTERNALS)
    #define CYTHON_USE_PYLONG_INTERNALS 1
  #endif
  #ifndef CYTHON_USE_PYLIST_INTERNALS
    #define CYTHON_USE_PYLIST_INTERNALS 1
  #endif
  #ifndef CYTHON_USE_UNICODE_INTERNALS
    #define CYTHON_USE_UNICODE_INTERNALS 1
  #endif
  #if PY_VERSION_HEX < 0x030300F0
    #undef CYTHON_USE_UNICODE_WRITER
    #define CYTHON_USE_UNICODE_WRITER 0
  #elif !defined(CYTHON_USE_UNICODE_WRITER)
    #define CYTHON_USE_UNICODE_WRITER 1
  #endif
  #ifndef CYTHON_AVOID_BORROWED_REFS
    #define CYTHON_AVOID_BORROWED_REFS 0
  #endif
  #ifndef CYTHON_ASSUME_SAFE_MACROS
    #define CYTHON_ASSUME_SAFE_MACROS 1
  #endif
  #ifndef CYTHON_UNPACK_METHODS
    #define CYTHON_UNPACK_METHODS 1
  #endif
  #ifndef CYTHON_FAST_THREAD_STATE
    #define CYTHON_FAST_THREAD_STATE 1
  #endif
  #ifndef CYTHON_FAST_PYCALL
    #define CYTHON_FAST_PYCALL 1
  #endif
#endif
#if !defined(CYTHON_FAST_PYCCALL)
#define CYTHON_FAST_PYCCALL  (CYTHON_FAST_PYCALL && PY_VERSION_HEX >= 0x030600B1)
#endif
#if CYTHON_USE_PYLONG_INTERNALS
  #include "longintrepr.h"
  #undef SHIFT
  #undef BASE
  #undef MASK
#endif
#if CYTHON_COMPILING_IN_PYPY && PY_VERSION_HEX < 0x02070600 && !defined(Py_OptimizeFlag)
  #define Py_OptimizeFlag 0
#endif
#define __PYX_BUILD_PY_SSIZE_T "n"
#define CYTHON_FORMAT_SSIZE_T "z"
#if PY_MAJOR_VERSION < 3
  #define __Pyx_BUILTIN_MODULE_NAME "__builtin__"
  #define __Pyx_PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)\
          PyCode_New(a+k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)
  #define __Pyx_DefaultClassType PyClass_Type
#else
  #define __Pyx_BUILTIN_MODULE_NAME "builtins"
  #define __Pyx_PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)\
          PyCode_New(a, k, l, s, f, code, c, n, v, fv, cell, fn, name, fline, lnos)
  #define __Pyx_DefaultClassType PyType_Type
#endif
#ifndef Py_TPFLAGS_CHECKTYPES
  #define Py_TPFLAGS_CHECKTYPES 0
#endif
#ifndef Py_TPFLAGS_HAVE_INDEX
  #define Py_TPFLAGS_HAVE_INDEX 0
#endif
#ifndef Py_TPFLAGS_HAVE_NEWBUFFER
  #define Py_TPFLAGS_HAVE_NEWBUFFER 0
#endif
#ifndef Py_TPFLAGS_HAVE_FINALIZE
  #define Py_TPFLAGS_HAVE_FINALIZE 0
#endif
#ifndef METH_FASTCALL
  #define METH_FASTCALL 0x80
  typedef PyObject *(*__Pyx_PyCFunctionFast) (PyObject *self, PyObject **args,
                                              Py_ssize_t nargs, PyObject *kwnames);
#else
  #define __Pyx_PyCFunctionFast _PyCFunctionFast
#endif
#if CYTHON_FAST_PYCCALL
#define __Pyx_PyFastCFunction_Check(func)\
    ((PyCFunction_Check(func) && (METH_FASTCALL == (PyCFunction_GET_FLAGS(func) & ~(METH_CLASS | METH_STATIC | METH_COEXIST)))))
#else
#define __Pyx_PyFastCFunction_Check(func) 0
#endif
#if PY_VERSION_HEX > 0x03030000 && defined(PyUnicode_KIND)
  #define CYTHON_PEP393_ENABLED 1
  #define __Pyx_PyUnicode_READY(op)       (likely(PyUnicode_IS_READY(op)) ?\
                                              0 : _PyUnicode_Ready((PyObject *)(op)))
  #define __Pyx_PyUnicode_GET_LENGTH(u)   PyUnicode_GET_LENGTH(u)
  #define __Pyx_PyUnicode_READ_CHAR(u, i) PyUnicode_READ_CHAR(u, i)
  #define __Pyx_PyUnicode_MAX_CHAR_VALUE(u)   PyUnicode_MAX_CHAR_VALUE(u)
  #define __Pyx_PyUnicode_KIND(u)         PyUnicode_KIND(u)
  #define __Pyx_PyUnicode_DATA(u)         PyUnicode_DATA(u)
  #define __Pyx_PyUnicode_READ(k, d, i)   PyUnicode_READ(k, d, i)
  #define __Pyx_PyUnicode_WRITE(k, d, i, ch)  PyUnicode_WRITE(k, d, i, ch)
  #define __Pyx_PyUnicode_IS_TRUE(u)      (0 != (likely(PyUnicode_IS_READY(u)) ? PyUnicode_GET_LENGTH(u) : PyUnicode_GET_SIZE(u)))
#else
  #define CYTHON_PEP393_ENABLED 0
  #define PyUnicode_1BYTE_KIND  1
  #define PyUnicode_2BYTE_KIND  2
  #define PyUnicode_4BYTE_KIND  4
  #define __Pyx_PyUnicode_READY(op)       (0)
  #define __Pyx_PyUnicode_GET_LENGTH(u)   PyUnicode_GET_SIZE(u)
  #define __Pyx_PyUnicode_READ_CHAR(u, i) ((Py_UCS4)(PyUnicode_AS_UNICODE(u)[i]))
  #define __Pyx_PyUnicode_MAX_CHAR_VALUE(u)   ((sizeof(Py_UNICODE) == 2) ? 65535 : 1114111)
  #define __Pyx_PyUnicode_KIND(u)         (sizeof(Py_UNICODE))
  #define __Pyx_PyUnicode_DATA(u)         ((void*)PyUnicode_AS_UNICODE(u))
  #define __Pyx_PyUnicode_READ(k, d, i)   ((void)(k), (Py_UCS4)(((Py_UNICODE*)d)[i]))
  #define __Pyx_PyUnicode_WRITE(k, d, i, ch)  (((void)(k)), ((Py_UNICODE*)d)[i] = ch)
  #define __Pyx_PyUnicode_IS_TRUE(u)      (0 != PyUnicode_GET_SIZE(u))
#endif
#if CYTHON_COMPILING_IN_PYPY
  #define __Pyx_PyUnicode_Concat(a, b)      PyNumber_Add(a, b)
  #define __Pyx_PyUnicode_ConcatSafe(a, b)  PyNumber_Add(a, b)
#else
  #define __Pyx_PyUnicode_Concat(a, b)      PyUnicode_Concat(a, b)
  #define __Pyx_PyUnicode_ConcatSafe(a, b)  ((unlikely((a) == Py_None) || unlikely((b) == Py_None)) ?\
      PyNumber_Add(a, b) : __Pyx_PyUnicode_Concat(a, b))
#endif
#if CYTHON_COMPILING_IN_PYPY && !defined(PyUnicode_Contains)
  #define PyUnicode_Contains(u, s)  PySequence_Contains(u, s)
#endif
#if CYTHON_COMPILING_IN_PYPY && !defined(PyByteArray_Check)
  #define PyByteArray_Check(obj)  PyObject_TypeCheck(obj, &PyByteArray_Type)
#endif
#if CYTHON_COMPILING_IN_PYPY && !defined(PyObject_Format)
  #define PyObject_Format(obj, fmt)  PyObject_CallMethod(obj, "__format__", "O", fmt)
#endif
#if CYTHON_COMPILING_IN_PYPY && !defined(PyObject_Malloc)
  #define PyObject_Malloc(s)   PyMem_Malloc(s)
  #define PyObject_Free(p)     PyMem_Free(p)
  #define PyObject_Realloc(p)  PyMem_Realloc(p)
#endif
#if CYTHON_COMPILING_IN_PYSTON
  #define __Pyx_PyCode_HasFreeVars(co)  PyCode_HasFreeVars(co)
  #define __Pyx_PyFrame_SetLineNumber(frame, lineno) PyFrame_SetLineNumber(frame, lineno)
#else
  #define __Pyx_PyCode_HasFreeVars(co)  (PyCode_GetNumFree(co) > 0)
  #define __Pyx_PyFrame_SetLineNumber(frame, lineno)  (frame)->f_lineno = (lineno)
#endif
#define __Pyx_PyString_FormatSafe(a, b)   ((unlikely((a) == Py_None)) ? PyNumber_Remainder(a, b) : __Pyx_PyString_Format(a, b))
#define __Pyx_PyUnicode_FormatSafe(a, b)  ((unlikely((a) == Py_None)) ? PyNumber_Remainder(a, b) : PyUnicode_Format(a, b))
#if PY_MAJOR_VERSION >= 3
  #define __Pyx_PyString_Format(a, b)  PyUnicode_Format(a, b)
#else
  #define __Pyx_PyString_Format(a, b)  PyString_Format(a, b)
#endif
#if PY_MAJOR_VERSION < 3 && !defined(PyObject_ASCII)
  #define PyObject_ASCII(o)            PyObject_Repr(o)
#endif
#if PY_MAJOR_VERSION >= 3
  #define PyBaseString_Type            PyUnicode_Type
  #define PyStringObject               PyUnicodeObject
  #define PyString_Type                PyUnicode_Type
  #define PyString_Check               PyUnicode_Check
  #define PyString_CheckExact          PyUnicode_CheckExact
#endif
#if PY_MAJOR_VERSION >= 3
  #define __Pyx_PyBaseString_Check(obj) PyUnicode_Check(obj)
  #define __Pyx_PyBaseString_CheckExact(obj) PyUnicode_CheckExact(obj)
#else
  #define __Pyx_PyBaseString_Check(obj) (PyString_Check(obj) || PyUnicode_Check(obj))
  #define __Pyx_PyBaseString_CheckExact(obj) (PyString_CheckExact(obj) || PyUnicode_CheckExact(obj))
#endif
#ifndef PySet_CheckExact
  #define PySet_CheckExact(obj)        (Py_TYPE(obj) == &PySet_Type)
#endif
#define __Pyx_TypeCheck(obj, type) PyObject_TypeCheck(obj, (PyTypeObject *)type)
#define __Pyx_PyException_Check(obj) __Pyx_TypeCheck(obj, PyExc_Exception)
#if PY_MAJOR_VERSION >= 3
  #define PyIntObject                  PyLongObject
  #define PyInt_Type                   PyLong_Type
  #define PyInt_Check(op)              PyLong_Check(op)
  #define PyInt_CheckExact(op)         PyLong_CheckExact(op)
  #define PyInt_FromString             PyLong_FromString
  #define PyInt_FromUnicode            PyLong_FromUnicode
  #define PyInt_FromLong               PyLong_FromLong
  #define PyInt_FromSize_t             PyLong_FromSize_t
  #define PyInt_FromSsize_t            PyLong_FromSsize_t
  #define PyInt_AsLong                 PyLong_AsLong
  #define PyInt_AS_LONG                PyLong_AS_LONG
  #define PyInt_AsSsize_t              PyLong_AsSsize_t
  #define PyInt_AsUnsignedLongMask     PyLong_AsUnsignedLongMask
  #define PyInt_AsUnsignedLongLongMask PyLong_AsUnsignedLongLongMask
  #define PyNumber_Int                 PyNumber_Long
#endif
#if PY_MAJOR_VERSION >= 3
  #define PyBoolObject                 PyLongObject
#endif
#if PY_MAJOR_VERSION >= 3 && CYTHON_COMPILING_IN_PYPY
  #ifndef PyUnicode_InternFromString
    #define PyUnicode_InternFromString(s) PyUnicode_FromString(s)
  #endif
#endif
#if PY_VERSION_HEX < 0x030200A4
  typedef long Py_hash_t;
  #define __Pyx_PyInt_FromHash_t PyInt_FromLong
  #define __Pyx_PyInt_AsHash_t   PyInt_AsLong
#else
  #define __Pyx_PyInt_FromHash_t PyInt_FromSsize_t
  #define __Pyx_PyInt_AsHash_t   PyInt_AsSsize_t
#endif
#if PY_MAJOR_VERSION >= 3
  #define __Pyx_PyMethod_New(func, self, klass) ((self) ? PyMethod_New(func, self) : PyInstanceMethod_New(func))
#else
  #define __Pyx_PyMethod_New(func, self, klass) PyMethod_New(func, self, klass)
#endif
#if CYTHON_USE_ASYNC_SLOTS
  #if PY_VERSION_HEX >= 0x030500B1
    #define __Pyx_PyAsyncMethodsStruct PyAsyncMethods
    #define __Pyx_PyType_AsAsync(obj) (Py_TYPE(obj)->tp_as_async)
  #else
    typedef struct {
        unaryfunc am_await;
        unaryfunc am_aiter;
        unaryfunc am_anext;
    } __Pyx_PyAsyncMethodsStruct;
    #define __Pyx_PyType_AsAsync(obj) ((__Pyx_PyAsyncMethodsStruct*) (Py_TYPE(obj)->tp_reserved))
  #endif
#else
  #define __Pyx_PyType_AsAsync(obj) NULL
#endif
#ifndef CYTHON_RESTRICT
  #if defined(__GNUC__)
    #define CYTHON_RESTRICT __restrict__
  #elif defined(_MSC_VER) && _MSC_VER >= 1400
    #define CYTHON_RESTRICT __restrict
  #elif defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    #define CYTHON_RESTRICT restrict
  #else
    #define CYTHON_RESTRICT
  #endif
#endif
#ifndef CYTHON_UNUSED
# if defined(__GNUC__)
#   if !(defined(__cplusplus)) || (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#     define CYTHON_UNUSED __attribute__ ((__unused__))
#   else
#     define CYTHON_UNUSED
#   endif
# elif defined(__ICC) || (defined(__INTEL_COMPILER) && !defined(_MSC_VER))
#   define CYTHON_UNUSED __attribute__ ((__unused__))
# else
#   define CYTHON_UNUSED
# endif
#endif
#ifndef CYTHON_MAYBE_UNUSED_VAR
#  if defined(__cplusplus)
     template<class T> void CYTHON_MAYBE_UNUSED_VAR( const T& ) { }
#  else
#    define CYTHON_MAYBE_UNUSED_VAR(x) (void)(x)
#  endif
#endif
#ifndef CYTHON_NCP_UNUSED
# if CYTHON_COMPILING_IN_CPYTHON
#  define CYTHON_NCP_UNUSED
# else
#  define CYTHON_NCP_UNUSED CYTHON_UNUSED
# endif
#endif
#define __Pyx_void_to_None(void_result) ((void)(void_result), Py_INCREF(Py_None), Py_None)

#ifndef CYTHON_INLINE
  #if defined(__clang__)
    #define CYTHON_INLINE __inline__ __attribute__ ((__unused__))
  #elif defined(__GNUC__)
    #define CYTHON_INLINE __inline__
  #elif defined(_MSC_VER)
    #define CYTHON_INLINE __inline
  #elif defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    #define CYTHON_INLINE inline
  #else
    #define CYTHON_INLINE
  #endif
#endif

#if defined(WIN32) || defined(MS_WINDOWS)
  #define _USE_MATH_DEFINES
#endif
#include <math.h>
#ifdef NAN
#define __PYX_NAN() ((float) NAN)
#else
static CYTHON_INLINE float __PYX_NAN() {
  float value;
  memset(&value, 0xFF, sizeof(value));
  return value;
}
#endif
#if defined(__CYGWIN__) && defined(_LDBL_EQ_DBL)
#define __Pyx_truncl trunc
#else
#define __Pyx_truncl truncl
#endif


#define __PYX_ERR(f_index, lineno, Ln_error) \
{ \
  __pyx_filename = __pyx_f[f_index]; __pyx_lineno = lineno; __pyx_clineno = __LINE__; goto Ln_error; \
}

#if PY_MAJOR_VERSION >= 3
  #define __Pyx_PyNumber_Divide(x,y)         PyNumber_TrueDivide(x,y)
  #define __Pyx_PyNumber_InPlaceDivide(x,y)  PyNumber_InPlaceTrueDivide(x,y)
#else
  #define __Pyx_PyNumber_Divide(x,y)         PyNumber_Divide(x,y)
  #define __Pyx_PyNumber_InPlaceDivide(x,y)  PyNumber_InPlaceDivide(x,y)
#endif

#ifndef __PYX_EXTERN_C
  #ifdef __cplusplus
    #define __PYX_EXTERN_C extern "C"
  #else
    #define __PYX_EXTERN_C extern
  #endif
#endif

#define __PYX_HAVE__ims_extractor
#define __PYX_HAVE_API__ims_extractor
#ifdef _OPENMP
#include <omp.h>
#endif /* _OPENMP */

#ifdef PYREX_WITHOUT_ASSERTIONS
#define CYTHON_WITHOUT_ASSERTIONS
#endif

typedef struct {PyObject **p; const char *s; const Py_ssize_t n; const char* encoding;
                const char is_unicode; const char is_str; const char intern; } __Pyx_StringTabEntry;

#define __PYX_DEFAULT_STRING_ENCODING_IS_ASCII 0
#define __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT 0
#define __PYX_DEFAULT_STRING_ENCODING ""
#define __Pyx_PyObject_FromString __Pyx_PyBytes_FromString
#define __Pyx_PyObject_FromStringAndSize __Pyx_PyBytes_FromStringAndSize
#define __Pyx_uchar_cast(c) ((unsigned char)c)
#define __Pyx_long_cast(x) ((long)x)
#define __Pyx_fits_Py_ssize_t(v, type, is_signed)  (\
    (sizeof(type) < sizeof(Py_ssize_t))  ||\
    (sizeof(type) > sizeof(Py_ssize_t) &&\
          likely(v < (type)PY_SSIZE_T_MAX ||\
                 v == (type)PY_SSIZE_T_MAX)  &&\
          (!is_signed || likely(v > (type)PY_SSIZE_T_MIN ||\
                                v == (type)PY_SSIZE_T_MIN)))  ||\
    (sizeof(type) == sizeof(Py_ssize_t) &&\
          (is_signed || likely(v < (type)PY_SSIZE_T_MAX ||\
                               v == (type)PY_SSIZE_T_MAX)))  )
#if defined (__cplusplus) && __cplusplus >= 201103L
    #include <cstdlib>
    #define __Pyx_sst_abs(value) std::abs(value)
#elif SIZEOF_INT >= SIZEOF_SIZE_T
    #define __Pyx_sst_abs(value) abs(value)
#elif SIZEOF_LONG >= SIZEOF_SIZE_T
    #define __Pyx_sst_abs(value) labs(value)
#elif defined (_MSC_VER) && defined (_M_X64)
    #define __Pyx_sst_abs(value) _abs64(value)
#elif defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    #define __Pyx_sst_abs(value) llabs(value)
#elif defined (__GNUC__)
    #define __Pyx_sst_abs(value) __builtin_llabs(value)
#else
    #define __Pyx_sst_abs(value) ((value<0) ? -value : value)
#endif
static CYTHON_INLINE char* __Pyx_PyObject_AsString(PyObject*);
static CYTHON_INLINE char* __Pyx_PyObject_AsStringAndSize(PyObject*, Py_ssize_t* length);
#define __Pyx_PyByteArray_FromString(s) PyByteArray_FromStringAndSize((const char*)s, strlen((const char*)s))
#define __Pyx_PyByteArray_FromStringAndSize(s, l) PyByteArray_FromStringAndSize((const char*)s, l)
#define __Pyx_PyBytes_FromString        PyBytes_FromString
#define __Pyx_PyBytes_FromStringAndSize PyBytes_FromStringAndSize
static CYTHON_INLINE PyObject* __Pyx_PyUnicode_FromString(const char*);
#if PY_MAJOR_VERSION < 3
    #define __Pyx_PyStr_FromString        __Pyx_PyBytes_FromString
    #define __Pyx_PyStr_FromStringAndSize __Pyx_PyBytes_FromStringAndSize
#else
    #define __Pyx_PyStr_FromString        __Pyx_PyUnicode_FromString
    #define __Pyx_PyStr_FromStringAndSize __Pyx_PyUnicode_FromStringAndSize
#endif
#define __Pyx_PyObject_AsSString(s)    ((signed char*) __Pyx_PyObject_AsString(s))
#define __Pyx_PyObject_AsUString(s)    ((unsigned char*) __Pyx_PyObject_AsString(s))
#define __Pyx_PyObject_FromCString(s)  __Pyx_PyObject_FromString((const char*)s)
#define __Pyx_PyBytes_FromCString(s)   __Pyx_PyBytes_FromString((const char*)s)
#define __Pyx_PyByteArray_FromCString(s)   __Pyx_PyByteArray_FromString((const char*)s)
#define __Pyx_PyStr_FromCString(s)     __Pyx_PyStr_FromString((const char*)s)
#define __Pyx_PyUnicode_FromCString(s) __Pyx_PyUnicode_FromString((const char*)s)
#if PY_MAJOR_VERSION < 3
static CYTHON_INLINE size_t __Pyx_Py_UNICODE_strlen(const Py_UNICODE *u)
{
    const Py_UNICODE *u_end = u;
    while (*u_end++) ;
    return (size_t)(u_end - u - 1);
}
#else
#define __Pyx_Py_UNICODE_strlen Py_UNICODE_strlen
#endif
#define __Pyx_PyUnicode_FromUnicode(u)       PyUnicode_FromUnicode(u, __Pyx_Py_UNICODE_strlen(u))
#define __Pyx_PyUnicode_FromUnicodeAndLength PyUnicode_FromUnicode
#define __Pyx_PyUnicode_AsUnicode            PyUnicode_AsUnicode
#define __Pyx_NewRef(obj) (Py_INCREF(obj), obj)
#define __Pyx_Owned_Py_None(b) __Pyx_NewRef(Py_None)
#define __Pyx_PyBool_FromLong(b) ((b) ? __Pyx_NewRef(Py_True) : __Pyx_NewRef(Py_False))
static CYTHON_INLINE int __Pyx_PyObject_IsTrue(PyObject*);
static CYTHON_INLINE PyObject* __Pyx_PyNumber_IntOrLong(PyObject* x);
static CYTHON_INLINE Py_ssize_t __Pyx_PyIndex_AsSsize_t(PyObject*);
static CYTHON_INLINE PyObject * __Pyx_PyInt_FromSize_t(size_t);
#if CYTHON_ASSUME_SAFE_MACROS
#define __pyx_PyFloat_AsDouble(x) (PyFloat_CheckExact(x) ? PyFloat_AS_DOUBLE(x) : PyFloat_AsDouble(x))
#else
#define __pyx_PyFloat_AsDouble(x) PyFloat_AsDouble(x)
#endif
#define __pyx_PyFloat_AsFloat(x) ((float) __pyx_PyFloat_AsDouble(x))
#if PY_MAJOR_VERSION >= 3
#define __Pyx_PyNumber_Int(x) (PyLong_CheckExact(x) ? __Pyx_NewRef(x) : PyNumber_Long(x))
#else
#define __Pyx_PyNumber_Int(x) (PyInt_CheckExact(x) ? __Pyx_NewRef(x) : PyNumber_Int(x))
#endif
#define __Pyx_PyNumber_Float(x) (PyFloat_CheckExact(x) ? __Pyx_NewRef(x) : PyNumber_Float(x))
#if PY_MAJOR_VERSION < 3 && __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
static int __Pyx_sys_getdefaultencoding_not_ascii;
static int __Pyx_init_sys_getdefaultencoding_params(void) {
    PyObject* sys;
    PyObject* default_encoding = NULL;
    PyObject* ascii_chars_u = NULL;
    PyObject* ascii_chars_b = NULL;
    const char* default_encoding_c;
    sys = PyImport_ImportModule("sys");
    if (!sys) goto bad;
    default_encoding = PyObject_CallMethod(sys, (char*) "getdefaultencoding", NULL);
    Py_DECREF(sys);
    if (!default_encoding) goto bad;
    default_encoding_c = PyBytes_AsString(default_encoding);
    if (!default_encoding_c) goto bad;
    if (strcmp(default_encoding_c, "ascii") == 0) {
        __Pyx_sys_getdefaultencoding_not_ascii = 0;
    } else {
        char ascii_chars[128];
        int c;
        for (c = 0; c < 128; c++) {
            ascii_chars[c] = c;
        }
        __Pyx_sys_getdefaultencoding_not_ascii = 1;
        ascii_chars_u = PyUnicode_DecodeASCII(ascii_chars, 128, NULL);
        if (!ascii_chars_u) goto bad;
        ascii_chars_b = PyUnicode_AsEncodedString(ascii_chars_u, default_encoding_c, NULL);
        if (!ascii_chars_b || !PyBytes_Check(ascii_chars_b) || memcmp(ascii_chars, PyBytes_AS_STRING(ascii_chars_b), 128) != 0) {
            PyErr_Format(
                PyExc_ValueError,
                "This module compiled with c_string_encoding=ascii, but default encoding '%.200s' is not a superset of ascii.",
                default_encoding_c);
            goto bad;
        }
        Py_DECREF(ascii_chars_u);
        Py_DECREF(ascii_chars_b);
    }
    Py_DECREF(default_encoding);
    return 0;
bad:
    Py_XDECREF(default_encoding);
    Py_XDECREF(ascii_chars_u);
    Py_XDECREF(ascii_chars_b);
    return -1;
}
#endif
#if __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT && PY_MAJOR_VERSION >= 3
#define __Pyx_PyUnicode_FromStringAndSize(c_str, size) PyUnicode_DecodeUTF8(c_str, size, NULL)
#else
#define __Pyx_PyUnicode_FromStringAndSize(c_str, size) PyUnicode_Decode(c_str, size, __PYX_DEFAULT_STRING_ENCODING, NULL)
#if __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT
static char* __PYX_DEFAULT_STRING_ENCODING;
static int __Pyx_init_sys_getdefaultencoding_params(void) {
    PyObject* sys;
    PyObject* default_encoding = NULL;
    char* default_encoding_c;
    sys = PyImport_ImportModule("sys");
    if (!sys) goto bad;
    default_encoding = PyObject_CallMethod(sys, (char*) (const char*) "getdefaultencoding", NULL);
    Py_DECREF(sys);
    if (!default_encoding) goto bad;
    default_encoding_c = PyBytes_AsString(default_encoding);
    if (!default_encoding_c) goto bad;
    __PYX_DEFAULT_STRING_ENCODING = (char*) malloc(strlen(default_encoding_c));
    if (!__PYX_DEFAULT_STRING_ENCODING) goto bad;
    strcpy(__PYX_DEFAULT_STRING_ENCODING, default_encoding_c);
    Py_DECREF(default_encoding);
    return 0;
bad:
    Py_XDECREF(default_encoding);
    return -1;
}
#endif
#endif


/* Test for GCC > 2.95 */
#if defined(__GNUC__)     && (__GNUC__ > 2 || (__GNUC__ == 2 && (__GNUC_MINOR__ > 95)))
  #define likely(x)   __builtin_expect(!!(x), 1)
  #define unlikely(x) __builtin_expect(!!(x), 0)
#else /* !__GNUC__ or GCC < 2.95 */
  #define likely(x)   (x)
  #define unlikely(x) (x)
#endif /* __GNUC__ */

static PyObject *__pyx_m;
static PyObject *__pyx_d;
static PyObject *__pyx_b;
static PyObject *__pyx_empty_tuple;
static PyObject *__pyx_empty_bytes;
static PyObject *__pyx_empty_unicode;
static int __pyx_lineno;
static int __pyx_clineno = 0;
static const char * __pyx_cfilenm= __FILE__;
static const char *__pyx_filename;


static const char *__pyx_f[] = {
  "ims_extractor.pyx",
};

/*--- Type declarations ---*/

/* --- Runtime support code (head) --- */
/* Refnanny.proto */
#ifndef CYTHON_REFNANNY
  #define CYTHON_REFNANNY 0
#endif
#if CYTHON_REFNANNY
  typedef struct {
    void (*INCREF)(void*, PyObject*, int);
    void (*DECREF)(void*, PyObject*, int);
    void (*GOTREF)(void*, PyObject*, int);
    void (*GIVEREF)(void*, PyObject*, int);
    void* (*SetupContext)(const char*, int, const char*);
    void (*FinishContext)(void**);
  } __Pyx_RefNannyAPIStruct;
  static __Pyx_RefNannyAPIStruct *__Pyx_RefNanny = NULL;
  static __Pyx_RefNannyAPIStruct *__Pyx_RefNannyImportAPI(const char *modname);
  #define __Pyx_RefNannyDeclarations void *__pyx_refnanny = NULL;
#ifdef WITH_THREAD
  #define __Pyx_RefNannySetupContext(name, acquire_gil)\
          if (acquire_gil) {\
              PyGILState_STATE __pyx_gilstate_save = PyGILState_Ensure();\
              __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__);\
              PyGILState_Release(__pyx_gilstate_save);\
          } else {\
              __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__);\
          }
#else
  #define __Pyx_RefNannySetupContext(name, acquire_gil)\
          __pyx_refnanny = __Pyx_RefNanny->SetupContext((name), __LINE__, __FILE__)
#endif
  #define __Pyx_RefNannyFinishContext()\
          __Pyx_RefNanny->FinishContext(&__pyx_refnanny)
  #define __Pyx_INCREF(r)  __Pyx_RefNanny->INCREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_DECREF(r)  __Pyx_RefNanny->DECREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_GOTREF(r)  __Pyx_RefNanny->GOTREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_GIVEREF(r) __Pyx_RefNanny->GIVEREF(__pyx_refnanny, (PyObject *)(r), __LINE__)
  #define __Pyx_XINCREF(r)  do { if((r) != NULL) {__Pyx_INCREF(r); }} while(0)
  #define __Pyx_XDECREF(r)  do { if((r) != NULL) {__Pyx_DECREF(r); }} while(0)
  #define __Pyx_XGOTREF(r)  do { if((r) != NULL) {__Pyx_GOTREF(r); }} while(0)
  #define __Pyx_XGIVEREF(r) do { if((r) != NULL) {__Pyx_GIVEREF(r);}} while(0)
#else
  #define __Pyx_RefNannyDeclarations
  #define __Pyx_RefNannySetupContext(name, acquire_gil)
  #define __Pyx_RefNannyFinishContext()
  #define __Pyx_INCREF(r) Py_INCREF(r)
  #define __Pyx_DECREF(r) Py_DECREF(r)
  #define __Pyx_GOTREF(r)
  #define __Pyx_GIVEREF(r)
  #define __Pyx_XINCREF(r) Py_XINCREF(r)
  #define __Pyx_XDECREF(r) Py_XDECREF(r)
  #define __Pyx_XGOTREF(r)
  #define __Pyx_XGIVEREF(r)
#endif
#define __Pyx_XDECREF_SET(r, v) do {\
        PyObject *tmp = (PyObject *) r;\
        r = v; __Pyx_XDECREF(tmp);\
    } while (0)
#define __Pyx_DECREF_SET(r, v) do {\
        PyObject *tmp = (PyObject *) r;\
        r = v; __Pyx_DECREF(tmp);\
    } while (0)
#define __Pyx_CLEAR(r)    do { PyObject* tmp = ((PyObject*)(r)); r = NULL; __Pyx_DECREF(tmp);} while(0)
#define __Pyx_XCLEAR(r)   do { if((r) != NULL) {PyObject* tmp = ((PyObject*)(r)); r = NULL; __Pyx_DECREF(tmp);}} while(0)

/* PyObjectGetAttrStr.proto */
#if CYTHON_USE_TYPE_SLOTS
static CYTHON_INLINE PyObject* __Pyx_PyObject_GetAttrStr(PyObject* obj, PyObject* attr_name) {
    PyTypeObject* tp = Py_TYPE(obj);
    if (likely(tp->tp_getattro))
        return tp->tp_getattro(obj, attr_name);
#if PY_MAJOR_VERSION < 3
    if (likely(tp->tp_getattr))
        return tp->tp_getattr(obj, PyString_AS_STRING(attr_name));
#endif
    return PyObject_GetAttr(obj, attr_name);
}
#else
#define __Pyx_PyObject_GetAttrStr(o,n) PyObject_GetAttr(o,n)
#endif

/* GetBuiltinName.proto */
static PyObject *__Pyx_GetBuiltinName(PyObject *name);

/* GetItemInt.proto */
#define __Pyx_GetItemInt(o, i, type, is_signed, to_py_func, is_list, wraparound, boundscheck)\
    (__Pyx_fits_Py_ssize_t(i, type, is_signed) ?\
    __Pyx_GetItemInt_Fast(o, (Py_ssize_t)i, is_list, wraparound, boundscheck) :\
    (is_list ? (PyErr_SetString(PyExc_IndexError, "list index out of range"), (PyObject*)NULL) :\
               __Pyx_GetItemInt_Generic(o, to_py_func(i))))
#define __Pyx_GetItemInt_List(o, i, type, is_signed, to_py_func, is_list, wraparound, boundscheck)\
    (__Pyx_fits_Py_ssize_t(i, type, is_signed) ?\
    __Pyx_GetItemInt_List_Fast(o, (Py_ssize_t)i, wraparound, boundscheck) :\
    (PyErr_SetString(PyExc_IndexError, "list index out of range"), (PyObject*)NULL))
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_List_Fast(PyObject *o, Py_ssize_t i,
                                                              int wraparound, int boundscheck);
#define __Pyx_GetItemInt_Tuple(o, i, type, is_signed, to_py_func, is_list, wraparound, boundscheck)\
    (__Pyx_fits_Py_ssize_t(i, type, is_signed) ?\
    __Pyx_GetItemInt_Tuple_Fast(o, (Py_ssize_t)i, wraparound, boundscheck) :\
    (PyErr_SetString(PyExc_IndexError, "tuple index out of range"), (PyObject*)NULL))
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Tuple_Fast(PyObject *o, Py_ssize_t i,
                                                              int wraparound, int boundscheck);
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Generic(PyObject *o, PyObject* j);
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Fast(PyObject *o, Py_ssize_t i,
                                                     int is_list, int wraparound, int boundscheck);

/* PyCFunctionFastCall.proto */
#if CYTHON_FAST_PYCCALL
static CYTHON_INLINE PyObject *__Pyx_PyCFunction_FastCall(PyObject *func, PyObject **args, Py_ssize_t nargs);
#else
#define __Pyx_PyCFunction_FastCall(func, args, nargs)  (assert(0), NULL)
#endif

/* PyFunctionFastCall.proto */
#if CYTHON_FAST_PYCALL
#define __Pyx_PyFunction_FastCall(func, args, nargs)\
    __Pyx_PyFunction_FastCallDict((func), (args), (nargs), NULL)
#if 1 || PY_VERSION_HEX < 0x030600B1
static PyObject *__Pyx_PyFunction_FastCallDict(PyObject *func, PyObject **args, int nargs, PyObject *kwargs);
#else
#define __Pyx_PyFunction_FastCallDict(func, args, nargs, kwargs) _PyFunction_FastCallDict(func, args, nargs, kwargs)
#endif
#endif

/* PyObjectCall.proto */
#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_Call(PyObject *func, PyObject *arg, PyObject *kw);
#else
#define __Pyx_PyObject_Call(func, arg, kw) PyObject_Call(func, arg, kw)
#endif

/* PyObjectCallMethO.proto */
#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallMethO(PyObject *func, PyObject *arg);
#endif

/* PyObjectCallOneArg.proto */
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallOneArg(PyObject *func, PyObject *arg);

/* PyObjectCallNoArg.proto */
#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallNoArg(PyObject *func);
#else
#define __Pyx_PyObject_CallNoArg(func) __Pyx_PyObject_Call(func, __pyx_empty_tuple, NULL)
#endif

/* PyIntBinop.proto */
#if !CYTHON_COMPILING_IN_PYPY
static PyObject* __Pyx_PyInt_SubtractObjC(PyObject *op1, PyObject *op2, long intval, int inplace);
#else
#define __Pyx_PyInt_SubtractObjC(op1, op2, intval, inplace)\
    (inplace ? PyNumber_InPlaceSubtract(op1, op2) : PyNumber_Subtract(op1, op2))
#endif

/* GetModuleGlobalName.proto */
static CYTHON_INLINE PyObject *__Pyx_GetModuleGlobalName(PyObject *name);

/* IncludeStringH.proto */
#include <string.h>

/* BytesEquals.proto */
static CYTHON_INLINE int __Pyx_PyBytes_Equals(PyObject* s1, PyObject* s2, int equals);

/* UnicodeEquals.proto */
static CYTHON_INLINE int __Pyx_PyUnicode_Equals(PyObject* s1, PyObject* s2, int equals);

/* StrEquals.proto */
#if PY_MAJOR_VERSION >= 3
#define __Pyx_PyString_Equals __Pyx_PyUnicode_Equals
#else
#define __Pyx_PyString_Equals __Pyx_PyBytes_Equals
#endif

/* ListAppend.proto */
#if CYTHON_USE_PYLIST_INTERNALS && CYTHON_ASSUME_SAFE_MACROS
static CYTHON_INLINE int __Pyx_PyList_Append(PyObject* list, PyObject* x) {
    PyListObject* L = (PyListObject*) list;
    Py_ssize_t len = Py_SIZE(list);
    if (likely(L->allocated > len) & likely(len > (L->allocated >> 1))) {
        Py_INCREF(x);
        PyList_SET_ITEM(list, len, x);
        Py_SIZE(list) = len+1;
        return 0;
    }
    return PyList_Append(list, x);
}
#else
#define __Pyx_PyList_Append(L,x) PyList_Append(L,x)
#endif

/* PyIntBinop.proto */
#if !CYTHON_COMPILING_IN_PYPY
static PyObject* __Pyx_PyInt_AddObjC(PyObject *op1, PyObject *op2, long intval, int inplace);
#else
#define __Pyx_PyInt_AddObjC(op1, op2, intval, inplace)\
    (inplace ? PyNumber_InPlaceAdd(op1, op2) : PyNumber_Add(op1, op2))
#endif

/* ListCompAppend.proto */
#if CYTHON_USE_PYLIST_INTERNALS && CYTHON_ASSUME_SAFE_MACROS
static CYTHON_INLINE int __Pyx_ListComp_Append(PyObject* list, PyObject* x) {
    PyListObject* L = (PyListObject*) list;
    Py_ssize_t len = Py_SIZE(list);
    if (likely(L->allocated > len)) {
        Py_INCREF(x);
        PyList_SET_ITEM(list, len, x);
        Py_SIZE(list) = len+1;
        return 0;
    }
    return PyList_Append(list, x);
}
#else
#define __Pyx_ListComp_Append(L,x) PyList_Append(L,x)
#endif

/* PyObjectLookupSpecial.proto */
#if CYTHON_COMPILING_IN_CPYTHON && PY_VERSION_HEX >= 0x02070000
static CYTHON_INLINE PyObject* __Pyx_PyObject_LookupSpecial(PyObject* obj, PyObject* attr_name) {
    PyObject *res;
    PyTypeObject *tp = Py_TYPE(obj);
#if PY_MAJOR_VERSION < 3
    if (unlikely(PyInstance_Check(obj)))
        return __Pyx_PyObject_GetAttrStr(obj, attr_name);
#endif
    res = _PyType_Lookup(tp, attr_name);
    if (likely(res)) {
        descrgetfunc f = Py_TYPE(res)->tp_descr_get;
        if (!f) {
            Py_INCREF(res);
        } else {
            res = f(res, obj, (PyObject *)tp);
        }
    } else {
        PyErr_SetObject(PyExc_AttributeError, attr_name);
    }
    return res;
}
#else
#define __Pyx_PyObject_LookupSpecial(o,n) __Pyx_PyObject_GetAttrStr(o,n)
#endif

/* PyThreadStateGet.proto */
#if CYTHON_FAST_THREAD_STATE
#define __Pyx_PyThreadState_declare  PyThreadState *__pyx_tstate;
#define __Pyx_PyThreadState_assign  __pyx_tstate = PyThreadState_GET();
#else
#define __Pyx_PyThreadState_declare
#define __Pyx_PyThreadState_assign
#endif

/* SaveResetException.proto */
#if CYTHON_FAST_THREAD_STATE
#define __Pyx_ExceptionSave(type, value, tb)  __Pyx__ExceptionSave(__pyx_tstate, type, value, tb)
static CYTHON_INLINE void __Pyx__ExceptionSave(PyThreadState *tstate, PyObject **type, PyObject **value, PyObject **tb);
#define __Pyx_ExceptionReset(type, value, tb)  __Pyx__ExceptionReset(__pyx_tstate, type, value, tb)
static CYTHON_INLINE void __Pyx__ExceptionReset(PyThreadState *tstate, PyObject *type, PyObject *value, PyObject *tb);
#else
#define __Pyx_ExceptionSave(type, value, tb)   PyErr_GetExcInfo(type, value, tb)
#define __Pyx_ExceptionReset(type, value, tb)  PyErr_SetExcInfo(type, value, tb)
#endif

/* GetException.proto */
#if CYTHON_FAST_THREAD_STATE
#define __Pyx_GetException(type, value, tb)  __Pyx__GetException(__pyx_tstate, type, value, tb)
static int __Pyx__GetException(PyThreadState *tstate, PyObject **type, PyObject **value, PyObject **tb);
#else
static int __Pyx_GetException(PyObject **type, PyObject **value, PyObject **tb);
#endif

/* PyErrFetchRestore.proto */
#if CYTHON_FAST_THREAD_STATE
#define __Pyx_ErrRestoreWithState(type, value, tb)  __Pyx_ErrRestoreInState(PyThreadState_GET(), type, value, tb)
#define __Pyx_ErrFetchWithState(type, value, tb)    __Pyx_ErrFetchInState(PyThreadState_GET(), type, value, tb)
#define __Pyx_ErrRestore(type, value, tb)  __Pyx_ErrRestoreInState(__pyx_tstate, type, value, tb)
#define __Pyx_ErrFetch(type, value, tb)    __Pyx_ErrFetchInState(__pyx_tstate, type, value, tb)
static CYTHON_INLINE void __Pyx_ErrRestoreInState(PyThreadState *tstate, PyObject *type, PyObject *value, PyObject *tb);
static CYTHON_INLINE void __Pyx_ErrFetchInState(PyThreadState *tstate, PyObject **type, PyObject **value, PyObject **tb);
#else
#define __Pyx_ErrRestoreWithState(type, value, tb)  PyErr_Restore(type, value, tb)
#define __Pyx_ErrFetchWithState(type, value, tb)  PyErr_Fetch(type, value, tb)
#define __Pyx_ErrRestore(type, value, tb)  PyErr_Restore(type, value, tb)
#define __Pyx_ErrFetch(type, value, tb)  PyErr_Fetch(type, value, tb)
#endif

/* None.proto */
static CYTHON_INLINE void __Pyx_RaiseUnboundLocalError(const char *varname);

/* DictGetItem.proto */
#if PY_MAJOR_VERSION >= 3 && !CYTHON_COMPILING_IN_PYPY
static PyObject *__Pyx_PyDict_GetItem(PyObject *d, PyObject* key) {
    PyObject *value;
    value = PyDict_GetItemWithError(d, key);
    if (unlikely(!value)) {
        if (!PyErr_Occurred()) {
            PyObject* args = PyTuple_Pack(1, key);
            if (likely(args))
                PyErr_SetObject(PyExc_KeyError, args);
            Py_XDECREF(args);
        }
        return NULL;
    }
    Py_INCREF(value);
    return value;
}
#else
    #define __Pyx_PyDict_GetItem(d, key) PyObject_GetItem(d, key)
#endif

/* SliceTupleAndList.proto */
#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyList_GetSlice(PyObject* src, Py_ssize_t start, Py_ssize_t stop);
static CYTHON_INLINE PyObject* __Pyx_PyTuple_GetSlice(PyObject* src, Py_ssize_t start, Py_ssize_t stop);
#else
#define __Pyx_PyList_GetSlice(seq, start, stop)   PySequence_GetSlice(seq, start, stop)
#define __Pyx_PyTuple_GetSlice(seq, start, stop)  PySequence_GetSlice(seq, start, stop)
#endif

/* StringJoin.proto */
#if PY_MAJOR_VERSION < 3
#define __Pyx_PyString_Join __Pyx_PyBytes_Join
#define __Pyx_PyBaseString_Join(s, v) (PyUnicode_CheckExact(s) ? PyUnicode_Join(s, v) : __Pyx_PyBytes_Join(s, v))
#else
#define __Pyx_PyString_Join PyUnicode_Join
#define __Pyx_PyBaseString_Join PyUnicode_Join
#endif
#if CYTHON_COMPILING_IN_CPYTHON
    #if PY_MAJOR_VERSION < 3
    #define __Pyx_PyBytes_Join _PyString_Join
    #else
    #define __Pyx_PyBytes_Join _PyBytes_Join
    #endif
#else
static CYTHON_INLINE PyObject* __Pyx_PyBytes_Join(PyObject* sep, PyObject* values);
#endif

/* Import.proto */
static PyObject *__Pyx_Import(PyObject *name, PyObject *from_list, int level);

/* ImportFrom.proto */
static PyObject* __Pyx_ImportFrom(PyObject* module, PyObject* name);

/* CodeObjectCache.proto */
typedef struct {
    PyCodeObject* code_object;
    int code_line;
} __Pyx_CodeObjectCacheEntry;
struct __Pyx_CodeObjectCache {
    int count;
    int max_count;
    __Pyx_CodeObjectCacheEntry* entries;
};
static struct __Pyx_CodeObjectCache __pyx_code_cache = {0,0,NULL};
static int __pyx_bisect_code_objects(__Pyx_CodeObjectCacheEntry* entries, int count, int code_line);
static PyCodeObject *__pyx_find_code_object(int code_line);
static void __pyx_insert_code_object(int code_line, PyCodeObject* code_object);

/* AddTraceback.proto */
static void __Pyx_AddTraceback(const char *funcname, int c_line,
                               int py_line, const char *filename);

/* CIntToPy.proto */
static CYTHON_INLINE PyObject* __Pyx_PyInt_From_long(long value);

/* Print.proto */
static int __Pyx_Print(PyObject*, PyObject *, int);
#if CYTHON_COMPILING_IN_PYPY || PY_MAJOR_VERSION >= 3
static PyObject* __pyx_print = 0;
static PyObject* __pyx_print_kwargs = 0;
#endif

/* PrintOne.proto */
static int __Pyx_PrintOne(PyObject* stream, PyObject *o);

/* CIntFromPy.proto */
static CYTHON_INLINE long __Pyx_PyInt_As_long(PyObject *);

/* CIntFromPy.proto */
static CYTHON_INLINE int __Pyx_PyInt_As_int(PyObject *);

/* CheckBinaryVersion.proto */
static int __Pyx_check_binary_version(void);

/* InitStrings.proto */
static int __Pyx_InitStrings(__Pyx_StringTabEntry *t);


/* Module declarations from 'ims_extractor' */
#define __Pyx_MODULE_NAME "ims_extractor"
int __pyx_module_is_main_ims_extractor = 0;

/* Implementation of 'ims_extractor' */
static PyObject *__pyx_builtin_xrange;
static PyObject *__pyx_builtin_open;
static PyObject *__pyx_builtin_map;
static PyObject *__pyx_builtin_range;
static PyObject *__pyx_builtin_enumerate;
static const char __pyx_k_[] = " ";
static const char __pyx_k_a[] = "a";
static const char __pyx_k_b[] = "b";
static const char __pyx_k_f[] = "f";
static const char __pyx_k_i[] = "i";
static const char __pyx_k_m[] = "m";
static const char __pyx_k_n[] = "n";
static const char __pyx_k_w[] = "w";
static const char __pyx_k__3[] = "\t";
static const char __pyx_k__5[] = "\n";
static const char __pyx_k__6[] = "";
static const char __pyx_k__8[] = "\r";
static const char __pyx_k_ii[] = "ii";
static const char __pyx_k_os[] = "os";
static const char __pyx_k_wb[] = "wb";
static const char __pyx_k_xa[] = "xa";
static const char __pyx_k_xi[] = "xi";
static const char __pyx_k_xm[] = "xm";
static const char __pyx_k__10[] = "#----------------------------------------------------#";
static const char __pyx_k__11[] = ".";
static const char __pyx_k__14[] = "\\";
static const char __pyx_k__16[] = "                         |";
static const char __pyx_k__18[] = "|";
static const char __pyx_k__20[] = "                    |";
static const char __pyx_k__22[] = " |";
static const char __pyx_k__25[] = ",";
static const char __pyx_k__26[] = "                   |";
static const char __pyx_k__29[] = "_";
static const char __pyx_k_end[] = "end";
static const char __pyx_k_idx[] = "idx";
static const char __pyx_k_iii[] = "iii";
static const char __pyx_k_ims[] = ".ims";
static const char __pyx_k_log[] = "log";
static const char __pyx_k_map[] = "map";
static const char __pyx_k_ms1[] = ".ms1";
static const char __pyx_k_myi[] = "myi";
static const char __pyx_k_sub[] = "sub";
static const char __pyx_k_tic[] = "tic";
static const char __pyx_k_exit[] = "__exit__";
static const char __pyx_k_file[] = "file";
static const char __pyx_k_intt[] = "intt";
static const char __pyx_k_item[] = "item";
static const char __pyx_k_join[] = "join";
static const char __pyx_k_line[] = "line";
static const char __pyx_k_main[] = "__main__";
static const char __pyx_k_math[] = "math";
static const char __pyx_k_open[] = "open";
static const char __pyx_k_path[] = "path";
static const char __pyx_k_test[] = "__test__";
static const char __pyx_k_time[] = "time";
static const char __pyx_k_10_4f[] = "{:10.4f}";
static const char __pyx_k_TIC_f[] = "TIC: %f\n";
static const char __pyx_k_array[] = "array";
static const char __pyx_k_clock[] = "clock";
static const char __pyx_k_close[] = "close";
static const char __pyx_k_count[] = "count";
static const char __pyx_k_datax[] = "datax";
static const char __pyx_k_effct[] = "effct";
static const char __pyx_k_enter[] = "__enter__";
static const char __pyx_k_file2[] = "file2";
static const char __pyx_k_file3[] = "file3";
static const char __pyx_k_lines[] = "lines";
static const char __pyx_k_ljust[] = "ljust";
static const char __pyx_k_log10[] = "log10";
static const char __pyx_k_print[] = "print";
static const char __pyx_k_range[] = "range";
static const char __pyx_k_split[] = "split";
static const char __pyx_k_start[] = "start";
static const char __pyx_k_timex[] = "timex";
static const char __pyx_k_total[] = "total";
static const char __pyx_k_value[] = "value";
static const char __pyx_k_write[] = "write";
static const char __pyx_k_format[] = "format";
static const char __pyx_k_import[] = "__import__";
static const char __pyx_k_isfile[] = "isfile";
static const char __pyx_k_remove[] = "remove";
static const char __pyx_k_start1[] = "start1";
static const char __pyx_k_tofile[] = "tofile";
static const char __pyx_k_xrange[] = "xrange";
static const char __pyx_k_RetTime[] = "RetTime";
static const char __pyx_k_Writing[] = "| Writing";
static const char __pyx_k_int_max[] = "int_max";
static const char __pyx_k_isalpha[] = "isalpha";
static const char __pyx_k_max_int[] = "max_int";
static const char __pyx_k_replace[] = "replace";
static const char __pyx_k_sublist[] = "sublist";
static const char __pyx_k_All_done[] = "| All done!                                          |";
static const char __pyx_k_Dilu_IMS[] = "#--------------------Dilu-IMS------------------------#";
static const char __pyx_k_end_time[] = "end_time";
static const char __pyx_k_last_idx[] = "last_idx";
static const char __pyx_k_max_mass[] = "max_mass";
static const char __pyx_k_operator[] = "operator";
static const char __pyx_k_peak_pos[] = "peak_pos";
static const char __pyx_k_position[] = "position";
static const char __pyx_k_ret_time[] = "ret_time";
static const char __pyx_k_temp_int[] = "temp_int";
static const char __pyx_k_time_end[] = "time_end";
static const char __pyx_k_enumerate[] = "enumerate";
static const char __pyx_k_file_name[] = "file_name";
static const char __pyx_k_increment[] = "increment";
static const char __pyx_k_lastvalue[] = "lastvalue";
static const char __pyx_k_load_data[] = "load_data";
static const char __pyx_k_log_array[] = "log_array";
static const char __pyx_k_max_drift[] = "max_drift";
static const char __pyx_k_res_array[] = "res_array";
static const char __pyx_k_retention[] = "retention";
static const char __pyx_k_start_idx[] = "start_idx";
static const char __pyx_k_temp_data[] = "temp_data";
static const char __pyx_k_temp_diff[] = "temp_diff";
static const char __pyx_k_zero_fill[] = "zero_fill";
static const char __pyx_k_difference[] = "difference";
static const char __pyx_k_file_exist[] = "file_exist!";
static const char __pyx_k_floatarray[] = "floatarray";
static const char __pyx_k_log_factor[] = "log_factor";
static const char __pyx_k_peak_count[] = "peak_count";
static const char __pyx_k_res_factor[] = "res_factor";
static const char __pyx_k_resolution[] = "resolution";
static const char __pyx_k_start_time[] = "start_time";
static const char __pyx_k_time_start[] = "time_start";
static const char __pyx_k_total_spec[] = "total_spec";
static const char __pyx_k_valid_spec[] = "valid_spec";
static const char __pyx_k_floatarray2[] = "floatarray2";
static const char __pyx_k_floatarray3[] = "floatarray3";
static const char __pyx_k_mass_center[] = "mass_center";
static const char __pyx_k_Loading_data[] = "| Loading data...                                    |";
static const char __pyx_k_Time_spent_s[] = "| Time spent(s):";
static const char __pyx_k_extract_file[] = "extract_file";
static const char __pyx_k_ppm_accuracy[] = "ppm accuracy        |";
static const char __pyx_k_file_name_ims[] = "file_name_ims";
static const char __pyx_k_frequency_csv[] = "_frequency.csv";
static const char __pyx_k_ims_extractor[] = "ims_extractor";
static const char __pyx_k_num_of_valley[] = "num_of_valley";
static const char __pyx_k_file_name_freq[] = "file_name_freq";
static const char __pyx_k_intensity_dict[] = "intensity_dict";
static const char __pyx_k_low_mass_array[] = "low_mass_array";
static const char __pyx_k_time_available[] = "time_available";
static const char __pyx_k_zero_fill_flat[] = "zero_fill_flat";
static const char __pyx_k_low_mass_factor[] = "low_mass_factor";
static const char __pyx_k_sequential_spec[] = "sequential_spec";
static const char __pyx_k_temp_peak_count[] = "temp_peak_count";
static const char __pyx_k_Dilu_initialized[] = "| Dilu initialized                                   |";
static const char __pyx_k_Analyzing_spectra[] = "| Analyzing spectra...                               |";
static const char __pyx_k_Features_combined[] = "| Features combined.                                 |";
static const char __pyx_k_Detecting_features[] = "| Detecting features...                              |";
static const char __pyx_k_Total_time_spent_s[] = "| Total time spent(s):";
static const char __pyx_k_spectra_analyzed_at[] = "spectra analyzed at";
static const char __pyx_k_Total_features_detected[] = "| Total features detected:";
static const char __pyx_k_All_data_loaded_from_disk[] = "| All data loaded from disk                          |";
static const char __pyx_k_Yu_Tom_Gao_Yates_Lab_TSRI[] = "|           Yu (Tom) Gao @ Yates Lab, TSRI           |";
static const char __pyx_k_E_Python_ims_extractor_pyx[] = "E:\\Python\\ims_extractor.pyx";
static const char __pyx_k_Feature_detection_finished[] = "| Feature detection finished.                        |";
static const char __pyx_k_Combining_features_to_spectra[] = "| Combining features to spectra....                  |";
static const char __pyx_k_Thanks_for_using_Dilu_bathygao[] = "| Thanks for using Dilu, bathygao@gmail.com          |";
static const char __pyx_k_Number_of_spectra_for_inspectio[] = "| Number of spectra for inspection:";
static PyObject *__pyx_kp_s_;
static PyObject *__pyx_kp_s_10_4f;
static PyObject *__pyx_kp_s_All_data_loaded_from_disk;
static PyObject *__pyx_kp_s_All_done;
static PyObject *__pyx_kp_s_Analyzing_spectra;
static PyObject *__pyx_kp_s_Combining_features_to_spectra;
static PyObject *__pyx_kp_s_Detecting_features;
static PyObject *__pyx_kp_s_Dilu_IMS;
static PyObject *__pyx_kp_s_Dilu_initialized;
static PyObject *__pyx_kp_s_E_Python_ims_extractor_pyx;
static PyObject *__pyx_kp_s_Feature_detection_finished;
static PyObject *__pyx_kp_s_Features_combined;
static PyObject *__pyx_kp_s_Loading_data;
static PyObject *__pyx_kp_s_Number_of_spectra_for_inspectio;
static PyObject *__pyx_n_s_RetTime;
static PyObject *__pyx_kp_s_TIC_f;
static PyObject *__pyx_kp_s_Thanks_for_using_Dilu_bathygao;
static PyObject *__pyx_kp_s_Time_spent_s;
static PyObject *__pyx_kp_s_Total_features_detected;
static PyObject *__pyx_kp_s_Total_time_spent_s;
static PyObject *__pyx_kp_s_Writing;
static PyObject *__pyx_kp_s_Yu_Tom_Gao_Yates_Lab_TSRI;
static PyObject *__pyx_kp_s__10;
static PyObject *__pyx_kp_s__11;
static PyObject *__pyx_kp_s__14;
static PyObject *__pyx_kp_s__16;
static PyObject *__pyx_kp_s__18;
static PyObject *__pyx_kp_s__20;
static PyObject *__pyx_kp_s__22;
static PyObject *__pyx_kp_s__25;
static PyObject *__pyx_kp_s__26;
static PyObject *__pyx_n_s__29;
static PyObject *__pyx_kp_s__3;
static PyObject *__pyx_kp_s__5;
static PyObject *__pyx_kp_s__6;
static PyObject *__pyx_kp_s__8;
static PyObject *__pyx_n_s_a;
static PyObject *__pyx_n_s_array;
static PyObject *__pyx_n_s_b;
static PyObject *__pyx_n_s_clock;
static PyObject *__pyx_n_s_close;
static PyObject *__pyx_n_s_count;
static PyObject *__pyx_n_s_datax;
static PyObject *__pyx_n_s_difference;
static PyObject *__pyx_n_s_effct;
static PyObject *__pyx_n_s_end;
static PyObject *__pyx_n_s_end_time;
static PyObject *__pyx_n_s_enter;
static PyObject *__pyx_n_s_enumerate;
static PyObject *__pyx_n_s_exit;
static PyObject *__pyx_n_s_extract_file;
static PyObject *__pyx_n_s_f;
static PyObject *__pyx_n_s_file;
static PyObject *__pyx_n_s_file2;
static PyObject *__pyx_n_s_file3;
static PyObject *__pyx_kp_s_file_exist;
static PyObject *__pyx_n_s_file_name;
static PyObject *__pyx_n_s_file_name_freq;
static PyObject *__pyx_n_s_file_name_ims;
static PyObject *__pyx_n_s_floatarray;
static PyObject *__pyx_n_s_floatarray2;
static PyObject *__pyx_n_s_floatarray3;
static PyObject *__pyx_n_s_format;
static PyObject *__pyx_kp_s_frequency_csv;
static PyObject *__pyx_n_s_i;
static PyObject *__pyx_n_s_idx;
static PyObject *__pyx_n_s_ii;
static PyObject *__pyx_n_s_iii;
static PyObject *__pyx_n_s_import;
static PyObject *__pyx_kp_s_ims;
static PyObject *__pyx_n_s_ims_extractor;
static PyObject *__pyx_n_s_increment;
static PyObject *__pyx_n_s_int_max;
static PyObject *__pyx_n_s_intensity_dict;
static PyObject *__pyx_n_s_intt;
static PyObject *__pyx_n_s_isalpha;
static PyObject *__pyx_n_s_isfile;
static PyObject *__pyx_n_s_item;
static PyObject *__pyx_n_s_join;
static PyObject *__pyx_n_s_last_idx;
static PyObject *__pyx_n_s_lastvalue;
static PyObject *__pyx_n_s_line;
static PyObject *__pyx_n_s_lines;
static PyObject *__pyx_n_s_ljust;
static PyObject *__pyx_n_s_load_data;
static PyObject *__pyx_n_s_log;
static PyObject *__pyx_n_s_log10;
static PyObject *__pyx_n_s_log_array;
static PyObject *__pyx_n_s_log_factor;
static PyObject *__pyx_n_s_low_mass_array;
static PyObject *__pyx_n_s_low_mass_factor;
static PyObject *__pyx_n_s_m;
static PyObject *__pyx_n_s_main;
static PyObject *__pyx_n_s_map;
static PyObject *__pyx_n_s_mass_center;
static PyObject *__pyx_n_s_math;
static PyObject *__pyx_n_s_max_drift;
static PyObject *__pyx_n_s_max_int;
static PyObject *__pyx_n_s_max_mass;
static PyObject *__pyx_kp_s_ms1;
static PyObject *__pyx_n_s_myi;
static PyObject *__pyx_n_s_n;
static PyObject *__pyx_n_s_num_of_valley;
static PyObject *__pyx_n_s_open;
static PyObject *__pyx_n_s_operator;
static PyObject *__pyx_n_s_os;
static PyObject *__pyx_n_s_path;
static PyObject *__pyx_n_s_peak_count;
static PyObject *__pyx_n_s_peak_pos;
static PyObject *__pyx_n_s_position;
static PyObject *__pyx_kp_s_ppm_accuracy;
static PyObject *__pyx_n_s_print;
static PyObject *__pyx_n_s_range;
static PyObject *__pyx_n_s_remove;
static PyObject *__pyx_n_s_replace;
static PyObject *__pyx_n_s_res_array;
static PyObject *__pyx_n_s_res_factor;
static PyObject *__pyx_n_s_resolution;
static PyObject *__pyx_n_s_ret_time;
static PyObject *__pyx_n_s_retention;
static PyObject *__pyx_n_s_sequential_spec;
static PyObject *__pyx_kp_s_spectra_analyzed_at;
static PyObject *__pyx_n_s_split;
static PyObject *__pyx_n_s_start;
static PyObject *__pyx_n_s_start1;
static PyObject *__pyx_n_s_start_idx;
static PyObject *__pyx_n_s_start_time;
static PyObject *__pyx_n_s_sub;
static PyObject *__pyx_n_s_sublist;
static PyObject *__pyx_n_s_temp_data;
static PyObject *__pyx_n_s_temp_diff;
static PyObject *__pyx_n_s_temp_int;
static PyObject *__pyx_n_s_temp_peak_count;
static PyObject *__pyx_n_s_test;
static PyObject *__pyx_n_s_tic;
static PyObject *__pyx_n_s_time;
static PyObject *__pyx_n_s_time_available;
static PyObject *__pyx_n_s_time_end;
static PyObject *__pyx_n_s_time_start;
static PyObject *__pyx_n_s_timex;
static PyObject *__pyx_n_s_tofile;
static PyObject *__pyx_n_s_total;
static PyObject *__pyx_n_s_total_spec;
static PyObject *__pyx_n_s_valid_spec;
static PyObject *__pyx_n_s_value;
static PyObject *__pyx_n_s_w;
static PyObject *__pyx_n_s_wb;
static PyObject *__pyx_n_s_write;
static PyObject *__pyx_n_s_xa;
static PyObject *__pyx_n_s_xi;
static PyObject *__pyx_n_s_xm;
static PyObject *__pyx_n_s_xrange;
static PyObject *__pyx_n_s_zero_fill;
static PyObject *__pyx_n_s_zero_fill_flat;
static PyObject *__pyx_pf_13ims_extractor_load_data(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_line); /* proto */
static PyObject *__pyx_pf_13ims_extractor_2extract_file(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_file_name); /* proto */
static PyObject *__pyx_float_0_0;
static PyObject *__pyx_float_0_1;
static PyObject *__pyx_float_0_5;
static PyObject *__pyx_float_0_05;
static PyObject *__pyx_float_300000000_0;
static PyObject *__pyx_float_130_288149137774;
static PyObject *__pyx_float_169897000_433602;
static PyObject *__pyx_float_173_717445321994;
static PyObject *__pyx_float_217_146698086756;
static PyObject *__pyx_float_230102999_566398;
static PyObject *__pyx_float_247712125_471966;
static PyObject *__pyx_float_260_575907412860;
static PyObject *__pyx_float_260205999_132796;
static PyObject *__pyx_float_269897000_433602;
static PyObject *__pyx_float_277815125_038364;
static PyObject *__pyx_float_284509804_001426;
static PyObject *__pyx_float_290308998_699194;
static PyObject *__pyx_float_295424250_943933;
static PyObject *__pyx_float_304_005073319681;
static PyObject *__pyx_float_304139268_515822;
static PyObject *__pyx_float_307918124_604763;
static PyObject *__pyx_float_311394335_230684;
static PyObject *__pyx_float_314612803_567824;
static PyObject *__pyx_float_317609125_905568;
static PyObject *__pyx_float_320411998_265592;
static PyObject *__pyx_float_323044892_137827;
static PyObject *__pyx_float_325527250_510331;
static PyObject *__pyx_float_327875360_095283;
static PyObject *__pyx_float_330102999_566398;
static PyObject *__pyx_float_332221929_473392;
static PyObject *__pyx_float_334242268_082221;
static PyObject *__pyx_float_336172783_601759;
static PyObject *__pyx_float_338021124_171161;
static PyObject *__pyx_float_339794000_867204;
static PyObject *__pyx_float_341497334_797082;
static PyObject *__pyx_float_343136376_415899;
static PyObject *__pyx_float_344715803_134222;
static PyObject *__pyx_float_346239799_789896;
static PyObject *__pyx_float_347_434195788019;
static PyObject *__pyx_float_347712125_471966;
static PyObject *__pyx_float_349136169_383427;
static PyObject *__pyx_float_350514997_831991;
static PyObject *__pyx_float_351851393_987789;
static PyObject *__pyx_float_353147891_704225;
static PyObject *__pyx_float_354406804_435028;
static PyObject *__pyx_float_355630250_076729;
static PyObject *__pyx_float_356820172_406700;
static PyObject *__pyx_float_357978359_661681;
static PyObject *__pyx_float_359106460_702650;
static PyObject *__pyx_float_360205999_132796;
static PyObject *__pyx_float_361278385_671974;
static PyObject *__pyx_float_362324929_039790;
static PyObject *__pyx_float_363346845_557959;
static PyObject *__pyx_float_364345267_648619;
static PyObject *__pyx_float_365321251_377534;
static PyObject *__pyx_float_366275783_168157;
static PyObject *__pyx_float_367209785_793572;
static PyObject *__pyx_float_368124123_737559;
static PyObject *__pyx_float_369019608_002851;
static PyObject *__pyx_float_369897000_433602;
static PyObject *__pyx_float_390_863274827603;
static PyObject *__pyx_float_43_4294264720428;
static PyObject *__pyx_float_434_292310448164;
static PyObject *__pyx_float_477_721302630502;
static PyObject *__pyx_float_521_150251384347;
static PyObject *__pyx_float_564_579156719430;
static PyObject *__pyx_float_608_008018616550;
static PyObject *__pyx_float_651_436837095082;
static PyObject *__pyx_float_694_865612135824;
static PyObject *__pyx_float_738_294343748509;
static PyObject *__pyx_float_781_723031942865;
static PyObject *__pyx_float_825_151676699693;
static PyObject *__pyx_float_86_8588095243675;
static PyObject *__pyx_float_868_580278028723;
static PyObject *__pyx_int_0;
static PyObject *__pyx_int_1;
static PyObject *__pyx_int_2;
static PyObject *__pyx_int_3;
static PyObject *__pyx_int_8;
static PyObject *__pyx_int_15;
static PyObject *__pyx_int_25;
static PyObject *__pyx_int_41;
static PyObject *__pyx_int_50;
static PyObject *__pyx_int_60;
static PyObject *__pyx_int_99;
static PyObject *__pyx_int_100;
static PyObject *__pyx_int_2000;
static PyObject *__pyx_int_1000000;
static PyObject *__pyx_int_1229628;
static PyObject *__pyx_int_1844441;
static PyObject *__pyx_int_3688881;
static PyObject *__pyx_int_100000000;
static PyObject *__pyx_int_200000000;
static PyObject *__pyx_int_neg_100;
static PyObject *__pyx_tuple__2;
static PyObject *__pyx_tuple__4;
static PyObject *__pyx_tuple__7;
static PyObject *__pyx_tuple__9;
static PyObject *__pyx_slice__24;
static PyObject *__pyx_tuple__12;
static PyObject *__pyx_tuple__13;
static PyObject *__pyx_tuple__15;
static PyObject *__pyx_tuple__17;
static PyObject *__pyx_tuple__19;
static PyObject *__pyx_tuple__21;
static PyObject *__pyx_tuple__23;
static PyObject *__pyx_tuple__27;
static PyObject *__pyx_tuple__30;
static PyObject *__pyx_codeobj__28;
static PyObject *__pyx_codeobj__31;

/* "ims_extractor.pyx":11
 * 
 * 
 * def load_data(line):             # <<<<<<<<<<<<<<
 *     global ret_time
 *     if not line[0].isalpha():  # if start with 0-9 then get all data into its position
 */

/* Python wrapper */
static PyObject *__pyx_pw_13ims_extractor_1load_data(PyObject *__pyx_self, PyObject *__pyx_v_line); /*proto*/
static PyMethodDef __pyx_mdef_13ims_extractor_1load_data = {"load_data", (PyCFunction)__pyx_pw_13ims_extractor_1load_data, METH_O, 0};
static PyObject *__pyx_pw_13ims_extractor_1load_data(PyObject *__pyx_self, PyObject *__pyx_v_line) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("load_data (wrapper)", 0);
  __pyx_r = __pyx_pf_13ims_extractor_load_data(__pyx_self, ((PyObject *)__pyx_v_line));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_13ims_extractor_load_data(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_line) {
  PyObject *__pyx_v_m = NULL;
  PyObject *__pyx_v_position = NULL;
  PyObject *__pyx_v_n = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_t_4;
  int __pyx_t_5;
  PyObject *__pyx_t_6 = NULL;
  PyObject *__pyx_t_7 = NULL;
  __Pyx_RefNannySetupContext("load_data", 0);

  /* "ims_extractor.pyx":13
 * def load_data(line):
 *     global ret_time
 *     if not line[0].isalpha():  # if start with 0-9 then get all data into its position             # <<<<<<<<<<<<<<
 *         m = line.split(' ')
 *         position = int((log(float(m[0])) * 100000000 - low_mass_factor) / log_factor) - 1  # calculate the position of specific m/z in datax[]
 */
  __pyx_t_2 = __Pyx_GetItemInt(__pyx_v_line, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 13, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_isalpha); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 13, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = NULL;
  if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_3))) {
    __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_3);
    if (likely(__pyx_t_2)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
      __Pyx_INCREF(__pyx_t_2);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_3, function);
    }
  }
  if (__pyx_t_2) {
    __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 13, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  } else {
    __pyx_t_1 = __Pyx_PyObject_CallNoArg(__pyx_t_3); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 13, __pyx_L1_error)
  }
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_4 = __Pyx_PyObject_IsTrue(__pyx_t_1); if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(0, 13, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_5 = ((!__pyx_t_4) != 0);
  if (__pyx_t_5) {

    /* "ims_extractor.pyx":14
 *     global ret_time
 *     if not line[0].isalpha():  # if start with 0-9 then get all data into its position
 *         m = line.split(' ')             # <<<<<<<<<<<<<<
 *         position = int((log(float(m[0])) * 100000000 - low_mass_factor) / log_factor) - 1  # calculate the position of specific m/z in datax[]
 *         return position, float(m[0]), float(m[1])
 */
    __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_line, __pyx_n_s_split); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 14, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_tuple__2, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 14, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_v_m = __pyx_t_3;
    __pyx_t_3 = 0;

    /* "ims_extractor.pyx":15
 *     if not line[0].isalpha():  # if start with 0-9 then get all data into its position
 *         m = line.split(' ')
 *         position = int((log(float(m[0])) * 100000000 - low_mass_factor) / log_factor) - 1  # calculate the position of specific m/z in datax[]             # <<<<<<<<<<<<<<
 *         return position, float(m[0]), float(m[1])
 *         # datax[position]=datax[position]+[float(m[0]), float(m[1]), ret_time]	#put the value in a format [m/z intensity retention_time] to specific position in datax[]
 */
    __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_log); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 15, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_2 = __Pyx_GetItemInt(__pyx_v_m, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 15, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_6 = __Pyx_PyNumber_Float(__pyx_t_2); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 15, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_t_2 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_1))) {
      __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_1);
      if (likely(__pyx_t_2)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_1);
        __Pyx_INCREF(__pyx_t_2);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_1, function);
      }
    }
    if (!__pyx_t_2) {
      __pyx_t_3 = __Pyx_PyObject_CallOneArg(__pyx_t_1, __pyx_t_6); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 15, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
      __Pyx_GOTREF(__pyx_t_3);
    } else {
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_1)) {
        PyObject *__pyx_temp[2] = {__pyx_t_2, __pyx_t_6};
        __pyx_t_3 = __Pyx_PyFunction_FastCall(__pyx_t_1, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 15, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
        __Pyx_GOTREF(__pyx_t_3);
        __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_1)) {
        PyObject *__pyx_temp[2] = {__pyx_t_2, __pyx_t_6};
        __pyx_t_3 = __Pyx_PyCFunction_FastCall(__pyx_t_1, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 15, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
        __Pyx_GOTREF(__pyx_t_3);
        __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
      } else
      #endif
      {
        __pyx_t_7 = PyTuple_New(1+1); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 15, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_7);
        __Pyx_GIVEREF(__pyx_t_2); PyTuple_SET_ITEM(__pyx_t_7, 0, __pyx_t_2); __pyx_t_2 = NULL;
        __Pyx_GIVEREF(__pyx_t_6);
        PyTuple_SET_ITEM(__pyx_t_7, 0+1, __pyx_t_6);
        __pyx_t_6 = 0;
        __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_7, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 15, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
      }
    }
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_1 = PyNumber_Multiply(__pyx_t_3, __pyx_int_100000000); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 15, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_low_mass_factor); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 15, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_7 = PyNumber_Subtract(__pyx_t_1, __pyx_t_3); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 15, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_log_factor); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 15, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_1 = __Pyx_PyNumber_Divide(__pyx_t_7, __pyx_t_3); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 15, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyNumber_Int(__pyx_t_1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 15, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_1 = __Pyx_PyInt_SubtractObjC(__pyx_t_3, __pyx_int_1, 1, 0); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 15, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_v_position = __pyx_t_1;
    __pyx_t_1 = 0;

    /* "ims_extractor.pyx":16
 *         m = line.split(' ')
 *         position = int((log(float(m[0])) * 100000000 - low_mass_factor) / log_factor) - 1  # calculate the position of specific m/z in datax[]
 *         return position, float(m[0]), float(m[1])             # <<<<<<<<<<<<<<
 *         # datax[position]=datax[position]+[float(m[0]), float(m[1]), ret_time]	#put the value in a format [m/z intensity retention_time] to specific position in datax[]
 *     else:  # if start with alpha then acquire retention time
 */
    __Pyx_XDECREF(__pyx_r);
    __pyx_t_1 = __Pyx_GetItemInt(__pyx_v_m, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 16, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_3 = __Pyx_PyNumber_Float(__pyx_t_1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 16, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_1 = __Pyx_GetItemInt(__pyx_v_m, 1, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 16, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_7 = __Pyx_PyNumber_Float(__pyx_t_1); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 16, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_1 = PyTuple_New(3); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 16, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_INCREF(__pyx_v_position);
    __Pyx_GIVEREF(__pyx_v_position);
    PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_v_position);
    __Pyx_GIVEREF(__pyx_t_3);
    PyTuple_SET_ITEM(__pyx_t_1, 1, __pyx_t_3);
    __Pyx_GIVEREF(__pyx_t_7);
    PyTuple_SET_ITEM(__pyx_t_1, 2, __pyx_t_7);
    __pyx_t_3 = 0;
    __pyx_t_7 = 0;
    __pyx_r = __pyx_t_1;
    __pyx_t_1 = 0;
    goto __pyx_L0;

    /* "ims_extractor.pyx":13
 * def load_data(line):
 *     global ret_time
 *     if not line[0].isalpha():  # if start with 0-9 then get all data into its position             # <<<<<<<<<<<<<<
 *         m = line.split(' ')
 *         position = int((log(float(m[0])) * 100000000 - low_mass_factor) / log_factor) - 1  # calculate the position of specific m/z in datax[]
 */
  }

  /* "ims_extractor.pyx":19
 *         # datax[position]=datax[position]+[float(m[0]), float(m[1]), ret_time]	#put the value in a format [m/z intensity retention_time] to specific position in datax[]
 *     else:  # if start with alpha then acquire retention time
 *         n = line.split('\t')             # <<<<<<<<<<<<<<
 *         if n[1] == 'RetTime':
 *             ret_time = float(n[2].replace('\n', '').replace('\r', ''))
 */
  /*else*/ {
    __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_line, __pyx_n_s_split); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 19, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_7 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_tuple__4, NULL); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 19, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_v_n = __pyx_t_7;
    __pyx_t_7 = 0;

    /* "ims_extractor.pyx":20
 *     else:  # if start with alpha then acquire retention time
 *         n = line.split('\t')
 *         if n[1] == 'RetTime':             # <<<<<<<<<<<<<<
 *             ret_time = float(n[2].replace('\n', '').replace('\r', ''))
 *             return [ret_time]
 */
    __pyx_t_7 = __Pyx_GetItemInt(__pyx_v_n, 1, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 20, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __pyx_t_5 = (__Pyx_PyString_Equals(__pyx_t_7, __pyx_n_s_RetTime, Py_EQ)); if (unlikely(__pyx_t_5 < 0)) __PYX_ERR(0, 20, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
    if (__pyx_t_5) {

      /* "ims_extractor.pyx":21
 *         n = line.split('\t')
 *         if n[1] == 'RetTime':
 *             ret_time = float(n[2].replace('\n', '').replace('\r', ''))             # <<<<<<<<<<<<<<
 *             return [ret_time]
 *         return []
 */
      __pyx_t_7 = __Pyx_GetItemInt(__pyx_v_n, 2, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 21, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_t_7, __pyx_n_s_replace); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 21, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
      __pyx_t_7 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_tuple__7, NULL); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 21, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_t_7, __pyx_n_s_replace); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 21, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
      __pyx_t_7 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_tuple__9, NULL); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 21, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      __pyx_t_1 = __Pyx_PyNumber_Float(__pyx_t_7); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 21, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_7); __pyx_t_7 = 0;
      if (PyDict_SetItem(__pyx_d, __pyx_n_s_ret_time, __pyx_t_1) < 0) __PYX_ERR(0, 21, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

      /* "ims_extractor.pyx":22
 *         if n[1] == 'RetTime':
 *             ret_time = float(n[2].replace('\n', '').replace('\r', ''))
 *             return [ret_time]             # <<<<<<<<<<<<<<
 *         return []
 * 
 */
      __Pyx_XDECREF(__pyx_r);
      __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_ret_time); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 22, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __pyx_t_7 = PyList_New(1); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 22, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_7);
      __Pyx_GIVEREF(__pyx_t_1);
      PyList_SET_ITEM(__pyx_t_7, 0, __pyx_t_1);
      __pyx_t_1 = 0;
      __pyx_r = __pyx_t_7;
      __pyx_t_7 = 0;
      goto __pyx_L0;

      /* "ims_extractor.pyx":20
 *     else:  # if start with alpha then acquire retention time
 *         n = line.split('\t')
 *         if n[1] == 'RetTime':             # <<<<<<<<<<<<<<
 *             ret_time = float(n[2].replace('\n', '').replace('\r', ''))
 *             return [ret_time]
 */
    }

    /* "ims_extractor.pyx":23
 *             ret_time = float(n[2].replace('\n', '').replace('\r', ''))
 *             return [ret_time]
 *         return []             # <<<<<<<<<<<<<<
 * 
 * 
 */
    __Pyx_XDECREF(__pyx_r);
    __pyx_t_7 = PyList_New(0); if (unlikely(!__pyx_t_7)) __PYX_ERR(0, 23, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_7);
    __pyx_r = __pyx_t_7;
    __pyx_t_7 = 0;
    goto __pyx_L0;
  }

  /* "ims_extractor.pyx":11
 * 
 * 
 * def load_data(line):             # <<<<<<<<<<<<<<
 *     global ret_time
 *     if not line[0].isalpha():  # if start with 0-9 then get all data into its position
 */

  /* function exit code */
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_7);
  __Pyx_AddTraceback("ims_extractor.load_data", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_m);
  __Pyx_XDECREF(__pyx_v_position);
  __Pyx_XDECREF(__pyx_v_n);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

/* "ims_extractor.pyx":29
 * 
 * 
 * def extract_file(file_name):             # <<<<<<<<<<<<<<
 * 
 *     global start_time,end_time,tic,max_drift,resolution,res_factor,res_array,log_array,low_mass_array,log_factor,low_mass_factor,ret_time
 */

/* Python wrapper */
static PyObject *__pyx_pw_13ims_extractor_3extract_file(PyObject *__pyx_self, PyObject *__pyx_v_file_name); /*proto*/
static PyMethodDef __pyx_mdef_13ims_extractor_3extract_file = {"extract_file", (PyCFunction)__pyx_pw_13ims_extractor_3extract_file, METH_O, 0};
static PyObject *__pyx_pw_13ims_extractor_3extract_file(PyObject *__pyx_self, PyObject *__pyx_v_file_name) {
  PyObject *__pyx_r = 0;
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("extract_file (wrapper)", 0);
  __pyx_r = __pyx_pf_13ims_extractor_2extract_file(__pyx_self, ((PyObject *)__pyx_v_file_name));

  /* function exit code */
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyObject *__pyx_pf_13ims_extractor_2extract_file(CYTHON_UNUSED PyObject *__pyx_self, PyObject *__pyx_v_file_name) {
  PyObject *__pyx_v_start = NULL;
  PyObject *__pyx_v_retention = NULL;
  PyObject *__pyx_v_xa = NULL;
  PyObject *__pyx_v_xi = NULL;
  PyObject *__pyx_v_xm = NULL;
  PyObject *__pyx_v_datax = NULL;
  PyObject *__pyx_v_file_name_ims = NULL;
  PyObject *__pyx_v_file_name_freq = NULL;
  PyObject *__pyx_v_file2 = NULL;
  PyObject *__pyx_v_end = NULL;
  PyObject *__pyx_v_timex = NULL;
  PyObject *__pyx_v_start1 = NULL;
  PyObject *__pyx_v_lines = NULL;
  PyObject *__pyx_v_temp_data = NULL;
  PyObject *__pyx_v_item = NULL;
  PyObject *__pyx_v_effct = NULL;
  PyObject *__pyx_v_i = NULL;
  PyObject *__pyx_v_a = NULL;
  PyObject *__pyx_v_b = NULL;
  PyObject *__pyx_v_valid_spec = NULL;
  PyObject *__pyx_v_sequential_spec = NULL;
  PyObject *__pyx_v_intensity_dict = NULL;
  PyObject *__pyx_v_total = NULL;
  PyObject *__pyx_v_count = NULL;
  Py_ssize_t __pyx_v_myi;
  PyObject *__pyx_v_lastvalue = NULL;
  PyObject *__pyx_v_last_idx = NULL;
  PyObject *__pyx_v_start_idx = NULL;
  PyObject *__pyx_v_idx = NULL;
  PyObject *__pyx_v_value = NULL;
  PyObject *__pyx_v_peak_count = NULL;
  PyObject *__pyx_v_mass_center = NULL;
  PyObject *__pyx_v_ii = NULL;
  PyObject *__pyx_v_max_mass = NULL;
  PyObject *__pyx_v_max_int = NULL;
  PyObject *__pyx_v_int_max = NULL;
  PyObject *__pyx_v_intt = NULL;
  PyObject *__pyx_v_temp_int = NULL;
  PyObject *__pyx_v_temp_diff = NULL;
  PyObject *__pyx_v_peak_pos = NULL;
  PyObject *__pyx_v_temp_peak_count = NULL;
  PyObject *__pyx_v_iii = NULL;
  PyObject *__pyx_v_num_of_valley = NULL;
  PyObject *__pyx_v_zero_fill = NULL;
  PyObject *__pyx_v_time_available = NULL;
  PyObject *__pyx_v_time_start = NULL;
  PyObject *__pyx_v_time_end = NULL;
  double __pyx_v_increment;
  PyObject *__pyx_v_difference = NULL;
  PyObject *__pyx_v_zero_fill_flat = NULL;
  Py_ssize_t __pyx_v_total_spec;
  PyObject *__pyx_v_floatarray3 = NULL;
  PyObject *__pyx_v_floatarray = NULL;
  PyObject *__pyx_v_floatarray2 = NULL;
  PyObject *__pyx_v_file3 = NULL;
  CYTHON_UNUSED PyObject *__pyx_v__ = NULL;
  PyObject *__pyx_v_sublist = NULL;
  PyObject *__pyx_r = NULL;
  __Pyx_RefNannyDeclarations
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  PyObject *__pyx_t_3 = NULL;
  int __pyx_t_4;
  int __pyx_t_5;
  PyObject *__pyx_t_6 = NULL;
  Py_ssize_t __pyx_t_7;
  PyObject *(*__pyx_t_8)(PyObject *);
  int __pyx_t_9;
  PyObject *__pyx_t_10 = NULL;
  PyObject *__pyx_t_11 = NULL;
  PyObject *__pyx_t_12 = NULL;
  PyObject *__pyx_t_13 = NULL;
  PyObject *__pyx_t_14 = NULL;
  PyObject *__pyx_t_15 = NULL;
  Py_ssize_t __pyx_t_16;
  PyObject *__pyx_t_17 = NULL;
  PyObject *__pyx_t_18 = NULL;
  PyObject *__pyx_t_19 = NULL;
  PyObject *__pyx_t_20 = NULL;
  int __pyx_t_21;
  __Pyx_RefNannySetupContext("extract_file", 0);

  /* "ims_extractor.pyx":32
 * 
 *     global start_time,end_time,tic,max_drift,resolution,res_factor,res_array,log_array,low_mass_array,log_factor,low_mass_factor,ret_time
 *     start_time = 0             # <<<<<<<<<<<<<<
 *     end_time = 60
 *     tic = 0.0
 */
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_start_time, __pyx_int_0) < 0) __PYX_ERR(0, 32, __pyx_L1_error)

  /* "ims_extractor.pyx":33
 *     global start_time,end_time,tic,max_drift,resolution,res_factor,res_array,log_array,low_mass_array,log_factor,low_mass_factor,ret_time
 *     start_time = 0
 *     end_time = 60             # <<<<<<<<<<<<<<
 *     tic = 0.0
 * 
 */
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_end_time, __pyx_int_60) < 0) __PYX_ERR(0, 33, __pyx_L1_error)

  /* "ims_extractor.pyx":34
 *     start_time = 0
 *     end_time = 60
 *     tic = 0.0             # <<<<<<<<<<<<<<
 * 
 *     max_drift = 25  # 5ppm for combining peaks
 */
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_tic, __pyx_float_0_0) < 0) __PYX_ERR(0, 34, __pyx_L1_error)

  /* "ims_extractor.pyx":36
 *     tic = 0.0
 * 
 *     max_drift = 25  # 5ppm for combining peaks             # <<<<<<<<<<<<<<
 *     resolution = 1  # 1ppm for feature detection accuracy
 *     res_factor = 1000000 / resolution
 */
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_max_drift, __pyx_int_25) < 0) __PYX_ERR(0, 36, __pyx_L1_error)

  /* "ims_extractor.pyx":37
 * 
 *     max_drift = 25  # 5ppm for combining peaks
 *     resolution = 1  # 1ppm for feature detection accuracy             # <<<<<<<<<<<<<<
 *     res_factor = 1000000 / resolution
 *     res_array = [3688881, 1844441, 1229628]
 */
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_resolution, __pyx_int_1) < 0) __PYX_ERR(0, 37, __pyx_L1_error)

  /* "ims_extractor.pyx":38
 *     max_drift = 25  # 5ppm for combining peaks
 *     resolution = 1  # 1ppm for feature detection accuracy
 *     res_factor = 1000000 / resolution             # <<<<<<<<<<<<<<
 *     res_array = [3688881, 1844441, 1229628]
 *     # res_array numbers of elements of range 50-2000 with 1, 2, 3...20 ppm  =[log(high_mass)-log(low_mass)]/log(1+resolution/1E6)
 */
  __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_resolution); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 38, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __Pyx_PyNumber_Divide(__pyx_int_1000000, __pyx_t_1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 38, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_res_factor, __pyx_t_2) < 0) __PYX_ERR(0, 38, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "ims_extractor.pyx":39
 *     resolution = 1  # 1ppm for feature detection accuracy
 *     res_factor = 1000000 / resolution
 *     res_array = [3688881, 1844441, 1229628]             # <<<<<<<<<<<<<<
 *     # res_array numbers of elements of range 50-2000 with 1, 2, 3...20 ppm  =[log(high_mass)-log(low_mass)]/log(1+resolution/1E6)
 * 
 */
  __pyx_t_2 = PyList_New(3); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 39, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_int_3688881);
  __Pyx_GIVEREF(__pyx_int_3688881);
  PyList_SET_ITEM(__pyx_t_2, 0, __pyx_int_3688881);
  __Pyx_INCREF(__pyx_int_1844441);
  __Pyx_GIVEREF(__pyx_int_1844441);
  PyList_SET_ITEM(__pyx_t_2, 1, __pyx_int_1844441);
  __Pyx_INCREF(__pyx_int_1229628);
  __Pyx_GIVEREF(__pyx_int_1229628);
  PyList_SET_ITEM(__pyx_t_2, 2, __pyx_int_1229628);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_res_array, __pyx_t_2) < 0) __PYX_ERR(0, 39, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "ims_extractor.pyx":43
 * 
 *     # res_array numbers of elements of range 200-2000 with 1, 2, 3...20 ppm  =[log(high_mass)-log(low_mass)]/log(1+resolution/1E6)
 *     log_array = [43.4294264720428, 86.8588095243675, 130.288149137774, 173.717445321994,             # <<<<<<<<<<<<<<
 *                  217.146698086756, 260.575907412860, 304.005073319681, 347.434195788019,
 *                  390.863274827603, 434.292310448164, 477.721302630502, 521.150251384347,
 */
  __pyx_t_2 = PyList_New(20); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 43, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_float_43_4294264720428);
  __Pyx_GIVEREF(__pyx_float_43_4294264720428);
  PyList_SET_ITEM(__pyx_t_2, 0, __pyx_float_43_4294264720428);
  __Pyx_INCREF(__pyx_float_86_8588095243675);
  __Pyx_GIVEREF(__pyx_float_86_8588095243675);
  PyList_SET_ITEM(__pyx_t_2, 1, __pyx_float_86_8588095243675);
  __Pyx_INCREF(__pyx_float_130_288149137774);
  __Pyx_GIVEREF(__pyx_float_130_288149137774);
  PyList_SET_ITEM(__pyx_t_2, 2, __pyx_float_130_288149137774);
  __Pyx_INCREF(__pyx_float_173_717445321994);
  __Pyx_GIVEREF(__pyx_float_173_717445321994);
  PyList_SET_ITEM(__pyx_t_2, 3, __pyx_float_173_717445321994);
  __Pyx_INCREF(__pyx_float_217_146698086756);
  __Pyx_GIVEREF(__pyx_float_217_146698086756);
  PyList_SET_ITEM(__pyx_t_2, 4, __pyx_float_217_146698086756);
  __Pyx_INCREF(__pyx_float_260_575907412860);
  __Pyx_GIVEREF(__pyx_float_260_575907412860);
  PyList_SET_ITEM(__pyx_t_2, 5, __pyx_float_260_575907412860);
  __Pyx_INCREF(__pyx_float_304_005073319681);
  __Pyx_GIVEREF(__pyx_float_304_005073319681);
  PyList_SET_ITEM(__pyx_t_2, 6, __pyx_float_304_005073319681);
  __Pyx_INCREF(__pyx_float_347_434195788019);
  __Pyx_GIVEREF(__pyx_float_347_434195788019);
  PyList_SET_ITEM(__pyx_t_2, 7, __pyx_float_347_434195788019);
  __Pyx_INCREF(__pyx_float_390_863274827603);
  __Pyx_GIVEREF(__pyx_float_390_863274827603);
  PyList_SET_ITEM(__pyx_t_2, 8, __pyx_float_390_863274827603);
  __Pyx_INCREF(__pyx_float_434_292310448164);
  __Pyx_GIVEREF(__pyx_float_434_292310448164);
  PyList_SET_ITEM(__pyx_t_2, 9, __pyx_float_434_292310448164);
  __Pyx_INCREF(__pyx_float_477_721302630502);
  __Pyx_GIVEREF(__pyx_float_477_721302630502);
  PyList_SET_ITEM(__pyx_t_2, 10, __pyx_float_477_721302630502);
  __Pyx_INCREF(__pyx_float_521_150251384347);
  __Pyx_GIVEREF(__pyx_float_521_150251384347);
  PyList_SET_ITEM(__pyx_t_2, 11, __pyx_float_521_150251384347);
  __Pyx_INCREF(__pyx_float_564_579156719430);
  __Pyx_GIVEREF(__pyx_float_564_579156719430);
  PyList_SET_ITEM(__pyx_t_2, 12, __pyx_float_564_579156719430);
  __Pyx_INCREF(__pyx_float_608_008018616550);
  __Pyx_GIVEREF(__pyx_float_608_008018616550);
  PyList_SET_ITEM(__pyx_t_2, 13, __pyx_float_608_008018616550);
  __Pyx_INCREF(__pyx_float_651_436837095082);
  __Pyx_GIVEREF(__pyx_float_651_436837095082);
  PyList_SET_ITEM(__pyx_t_2, 14, __pyx_float_651_436837095082);
  __Pyx_INCREF(__pyx_float_694_865612135824);
  __Pyx_GIVEREF(__pyx_float_694_865612135824);
  PyList_SET_ITEM(__pyx_t_2, 15, __pyx_float_694_865612135824);
  __Pyx_INCREF(__pyx_float_738_294343748509);
  __Pyx_GIVEREF(__pyx_float_738_294343748509);
  PyList_SET_ITEM(__pyx_t_2, 16, __pyx_float_738_294343748509);
  __Pyx_INCREF(__pyx_float_781_723031942865);
  __Pyx_GIVEREF(__pyx_float_781_723031942865);
  PyList_SET_ITEM(__pyx_t_2, 17, __pyx_float_781_723031942865);
  __Pyx_INCREF(__pyx_float_825_151676699693);
  __Pyx_GIVEREF(__pyx_float_825_151676699693);
  PyList_SET_ITEM(__pyx_t_2, 18, __pyx_float_825_151676699693);
  __Pyx_INCREF(__pyx_float_868_580278028723);
  __Pyx_GIVEREF(__pyx_float_868_580278028723);
  PyList_SET_ITEM(__pyx_t_2, 19, __pyx_float_868_580278028723);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_log_array, __pyx_t_2) < 0) __PYX_ERR(0, 43, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "ims_extractor.pyx":49
 *                  738.294343748509, 781.723031942865, 825.151676699693, 868.580278028723]
 *     # log_array = log(1+resolution/1E6)*1E8
 *     low_mass_array = [169897000.433602, 200000000, 230102999.566398, 247712125.471966, 260205999.132796,             # <<<<<<<<<<<<<<
 *                       269897000.433602, 277815125.038364, 284509804.001426,
 *                       290308998.699194, 295424250.943933, 300000000.0, 304139268.515822,
 */
  __pyx_t_2 = PyList_New(51); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 49, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_float_169897000_433602);
  __Pyx_GIVEREF(__pyx_float_169897000_433602);
  PyList_SET_ITEM(__pyx_t_2, 0, __pyx_float_169897000_433602);
  __Pyx_INCREF(__pyx_int_200000000);
  __Pyx_GIVEREF(__pyx_int_200000000);
  PyList_SET_ITEM(__pyx_t_2, 1, __pyx_int_200000000);
  __Pyx_INCREF(__pyx_float_230102999_566398);
  __Pyx_GIVEREF(__pyx_float_230102999_566398);
  PyList_SET_ITEM(__pyx_t_2, 2, __pyx_float_230102999_566398);
  __Pyx_INCREF(__pyx_float_247712125_471966);
  __Pyx_GIVEREF(__pyx_float_247712125_471966);
  PyList_SET_ITEM(__pyx_t_2, 3, __pyx_float_247712125_471966);
  __Pyx_INCREF(__pyx_float_260205999_132796);
  __Pyx_GIVEREF(__pyx_float_260205999_132796);
  PyList_SET_ITEM(__pyx_t_2, 4, __pyx_float_260205999_132796);
  __Pyx_INCREF(__pyx_float_269897000_433602);
  __Pyx_GIVEREF(__pyx_float_269897000_433602);
  PyList_SET_ITEM(__pyx_t_2, 5, __pyx_float_269897000_433602);
  __Pyx_INCREF(__pyx_float_277815125_038364);
  __Pyx_GIVEREF(__pyx_float_277815125_038364);
  PyList_SET_ITEM(__pyx_t_2, 6, __pyx_float_277815125_038364);
  __Pyx_INCREF(__pyx_float_284509804_001426);
  __Pyx_GIVEREF(__pyx_float_284509804_001426);
  PyList_SET_ITEM(__pyx_t_2, 7, __pyx_float_284509804_001426);
  __Pyx_INCREF(__pyx_float_290308998_699194);
  __Pyx_GIVEREF(__pyx_float_290308998_699194);
  PyList_SET_ITEM(__pyx_t_2, 8, __pyx_float_290308998_699194);
  __Pyx_INCREF(__pyx_float_295424250_943933);
  __Pyx_GIVEREF(__pyx_float_295424250_943933);
  PyList_SET_ITEM(__pyx_t_2, 9, __pyx_float_295424250_943933);
  __Pyx_INCREF(__pyx_float_300000000_0);
  __Pyx_GIVEREF(__pyx_float_300000000_0);
  PyList_SET_ITEM(__pyx_t_2, 10, __pyx_float_300000000_0);
  __Pyx_INCREF(__pyx_float_304139268_515822);
  __Pyx_GIVEREF(__pyx_float_304139268_515822);
  PyList_SET_ITEM(__pyx_t_2, 11, __pyx_float_304139268_515822);
  __Pyx_INCREF(__pyx_float_307918124_604763);
  __Pyx_GIVEREF(__pyx_float_307918124_604763);
  PyList_SET_ITEM(__pyx_t_2, 12, __pyx_float_307918124_604763);
  __Pyx_INCREF(__pyx_float_311394335_230684);
  __Pyx_GIVEREF(__pyx_float_311394335_230684);
  PyList_SET_ITEM(__pyx_t_2, 13, __pyx_float_311394335_230684);
  __Pyx_INCREF(__pyx_float_314612803_567824);
  __Pyx_GIVEREF(__pyx_float_314612803_567824);
  PyList_SET_ITEM(__pyx_t_2, 14, __pyx_float_314612803_567824);
  __Pyx_INCREF(__pyx_float_317609125_905568);
  __Pyx_GIVEREF(__pyx_float_317609125_905568);
  PyList_SET_ITEM(__pyx_t_2, 15, __pyx_float_317609125_905568);
  __Pyx_INCREF(__pyx_float_320411998_265592);
  __Pyx_GIVEREF(__pyx_float_320411998_265592);
  PyList_SET_ITEM(__pyx_t_2, 16, __pyx_float_320411998_265592);
  __Pyx_INCREF(__pyx_float_323044892_137827);
  __Pyx_GIVEREF(__pyx_float_323044892_137827);
  PyList_SET_ITEM(__pyx_t_2, 17, __pyx_float_323044892_137827);
  __Pyx_INCREF(__pyx_float_325527250_510331);
  __Pyx_GIVEREF(__pyx_float_325527250_510331);
  PyList_SET_ITEM(__pyx_t_2, 18, __pyx_float_325527250_510331);
  __Pyx_INCREF(__pyx_float_327875360_095283);
  __Pyx_GIVEREF(__pyx_float_327875360_095283);
  PyList_SET_ITEM(__pyx_t_2, 19, __pyx_float_327875360_095283);
  __Pyx_INCREF(__pyx_float_330102999_566398);
  __Pyx_GIVEREF(__pyx_float_330102999_566398);
  PyList_SET_ITEM(__pyx_t_2, 20, __pyx_float_330102999_566398);
  __Pyx_INCREF(__pyx_float_332221929_473392);
  __Pyx_GIVEREF(__pyx_float_332221929_473392);
  PyList_SET_ITEM(__pyx_t_2, 21, __pyx_float_332221929_473392);
  __Pyx_INCREF(__pyx_float_334242268_082221);
  __Pyx_GIVEREF(__pyx_float_334242268_082221);
  PyList_SET_ITEM(__pyx_t_2, 22, __pyx_float_334242268_082221);
  __Pyx_INCREF(__pyx_float_336172783_601759);
  __Pyx_GIVEREF(__pyx_float_336172783_601759);
  PyList_SET_ITEM(__pyx_t_2, 23, __pyx_float_336172783_601759);
  __Pyx_INCREF(__pyx_float_338021124_171161);
  __Pyx_GIVEREF(__pyx_float_338021124_171161);
  PyList_SET_ITEM(__pyx_t_2, 24, __pyx_float_338021124_171161);
  __Pyx_INCREF(__pyx_float_339794000_867204);
  __Pyx_GIVEREF(__pyx_float_339794000_867204);
  PyList_SET_ITEM(__pyx_t_2, 25, __pyx_float_339794000_867204);
  __Pyx_INCREF(__pyx_float_341497334_797082);
  __Pyx_GIVEREF(__pyx_float_341497334_797082);
  PyList_SET_ITEM(__pyx_t_2, 26, __pyx_float_341497334_797082);
  __Pyx_INCREF(__pyx_float_343136376_415899);
  __Pyx_GIVEREF(__pyx_float_343136376_415899);
  PyList_SET_ITEM(__pyx_t_2, 27, __pyx_float_343136376_415899);
  __Pyx_INCREF(__pyx_float_344715803_134222);
  __Pyx_GIVEREF(__pyx_float_344715803_134222);
  PyList_SET_ITEM(__pyx_t_2, 28, __pyx_float_344715803_134222);
  __Pyx_INCREF(__pyx_float_346239799_789896);
  __Pyx_GIVEREF(__pyx_float_346239799_789896);
  PyList_SET_ITEM(__pyx_t_2, 29, __pyx_float_346239799_789896);
  __Pyx_INCREF(__pyx_float_347712125_471966);
  __Pyx_GIVEREF(__pyx_float_347712125_471966);
  PyList_SET_ITEM(__pyx_t_2, 30, __pyx_float_347712125_471966);
  __Pyx_INCREF(__pyx_float_349136169_383427);
  __Pyx_GIVEREF(__pyx_float_349136169_383427);
  PyList_SET_ITEM(__pyx_t_2, 31, __pyx_float_349136169_383427);
  __Pyx_INCREF(__pyx_float_350514997_831991);
  __Pyx_GIVEREF(__pyx_float_350514997_831991);
  PyList_SET_ITEM(__pyx_t_2, 32, __pyx_float_350514997_831991);
  __Pyx_INCREF(__pyx_float_351851393_987789);
  __Pyx_GIVEREF(__pyx_float_351851393_987789);
  PyList_SET_ITEM(__pyx_t_2, 33, __pyx_float_351851393_987789);
  __Pyx_INCREF(__pyx_float_353147891_704225);
  __Pyx_GIVEREF(__pyx_float_353147891_704225);
  PyList_SET_ITEM(__pyx_t_2, 34, __pyx_float_353147891_704225);
  __Pyx_INCREF(__pyx_float_354406804_435028);
  __Pyx_GIVEREF(__pyx_float_354406804_435028);
  PyList_SET_ITEM(__pyx_t_2, 35, __pyx_float_354406804_435028);
  __Pyx_INCREF(__pyx_float_355630250_076729);
  __Pyx_GIVEREF(__pyx_float_355630250_076729);
  PyList_SET_ITEM(__pyx_t_2, 36, __pyx_float_355630250_076729);
  __Pyx_INCREF(__pyx_float_356820172_406700);
  __Pyx_GIVEREF(__pyx_float_356820172_406700);
  PyList_SET_ITEM(__pyx_t_2, 37, __pyx_float_356820172_406700);
  __Pyx_INCREF(__pyx_float_357978359_661681);
  __Pyx_GIVEREF(__pyx_float_357978359_661681);
  PyList_SET_ITEM(__pyx_t_2, 38, __pyx_float_357978359_661681);
  __Pyx_INCREF(__pyx_float_359106460_702650);
  __Pyx_GIVEREF(__pyx_float_359106460_702650);
  PyList_SET_ITEM(__pyx_t_2, 39, __pyx_float_359106460_702650);
  __Pyx_INCREF(__pyx_float_360205999_132796);
  __Pyx_GIVEREF(__pyx_float_360205999_132796);
  PyList_SET_ITEM(__pyx_t_2, 40, __pyx_float_360205999_132796);
  __Pyx_INCREF(__pyx_float_361278385_671974);
  __Pyx_GIVEREF(__pyx_float_361278385_671974);
  PyList_SET_ITEM(__pyx_t_2, 41, __pyx_float_361278385_671974);
  __Pyx_INCREF(__pyx_float_362324929_039790);
  __Pyx_GIVEREF(__pyx_float_362324929_039790);
  PyList_SET_ITEM(__pyx_t_2, 42, __pyx_float_362324929_039790);
  __Pyx_INCREF(__pyx_float_363346845_557959);
  __Pyx_GIVEREF(__pyx_float_363346845_557959);
  PyList_SET_ITEM(__pyx_t_2, 43, __pyx_float_363346845_557959);
  __Pyx_INCREF(__pyx_float_364345267_648619);
  __Pyx_GIVEREF(__pyx_float_364345267_648619);
  PyList_SET_ITEM(__pyx_t_2, 44, __pyx_float_364345267_648619);
  __Pyx_INCREF(__pyx_float_365321251_377534);
  __Pyx_GIVEREF(__pyx_float_365321251_377534);
  PyList_SET_ITEM(__pyx_t_2, 45, __pyx_float_365321251_377534);
  __Pyx_INCREF(__pyx_float_366275783_168157);
  __Pyx_GIVEREF(__pyx_float_366275783_168157);
  PyList_SET_ITEM(__pyx_t_2, 46, __pyx_float_366275783_168157);
  __Pyx_INCREF(__pyx_float_367209785_793572);
  __Pyx_GIVEREF(__pyx_float_367209785_793572);
  PyList_SET_ITEM(__pyx_t_2, 47, __pyx_float_367209785_793572);
  __Pyx_INCREF(__pyx_float_368124123_737559);
  __Pyx_GIVEREF(__pyx_float_368124123_737559);
  PyList_SET_ITEM(__pyx_t_2, 48, __pyx_float_368124123_737559);
  __Pyx_INCREF(__pyx_float_369019608_002851);
  __Pyx_GIVEREF(__pyx_float_369019608_002851);
  PyList_SET_ITEM(__pyx_t_2, 49, __pyx_float_369019608_002851);
  __Pyx_INCREF(__pyx_float_369897000_433602);
  __Pyx_GIVEREF(__pyx_float_369897000_433602);
  PyList_SET_ITEM(__pyx_t_2, 50, __pyx_float_369897000_433602);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_low_mass_array, __pyx_t_2) < 0) __PYX_ERR(0, 49, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "ims_extractor.pyx":66
 *                       368124123.737559, 369019608.002851, 369897000.433602]
 *     # low_mass_array = log(low_mass)*1E8, 50, 100, 200,
 *     log_factor = log_array[resolution - 1]             # <<<<<<<<<<<<<<
 *     # log_factor get the proper 1E8 * log value of 1+resolution/1E6
 *     low_mass_factor = low_mass_array[0]
 */
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_log_array); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 66, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_resolution); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 66, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_3 = __Pyx_PyInt_SubtractObjC(__pyx_t_1, __pyx_int_1, 1, 0); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 66, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyObject_GetItem(__pyx_t_2, __pyx_t_3); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 66, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_log_factor, __pyx_t_1) < 0) __PYX_ERR(0, 66, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "ims_extractor.pyx":68
 *     log_factor = log_array[resolution - 1]
 *     # log_factor get the proper 1E8 * log value of 1+resolution/1E6
 *     low_mass_factor = low_mass_array[0]             # <<<<<<<<<<<<<<
 *     # 50, 100,200,....50000
 *     # low_mass_factor get the proper 1E8 * log value of low mass
 */
  __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_low_mass_array); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 68, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_3 = __Pyx_GetItemInt(__pyx_t_1, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 68, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_low_mass_factor, __pyx_t_3) < 0) __PYX_ERR(0, 68, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

  /* "ims_extractor.pyx":71
 *     # 50, 100,200,....50000
 *     # low_mass_factor get the proper 1E8 * log value of low mass
 *     ret_time = 0             # <<<<<<<<<<<<<<
 * 
 * 
 */
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_ret_time, __pyx_int_0) < 0) __PYX_ERR(0, 71, __pyx_L1_error)

  /* "ims_extractor.pyx":74
 * 
 * 
 *     print ""             # <<<<<<<<<<<<<<
 *     print "#--------------------Dilu-IMS------------------------#"
 *     print "|           Yu (Tom) Gao @ Yates Lab, TSRI           |"
 */
  if (__Pyx_PrintOne(0, __pyx_kp_s__6) < 0) __PYX_ERR(0, 74, __pyx_L1_error)

  /* "ims_extractor.pyx":75
 * 
 *     print ""
 *     print "#--------------------Dilu-IMS------------------------#"             # <<<<<<<<<<<<<<
 *     print "|           Yu (Tom) Gao @ Yates Lab, TSRI           |"
 *     print "#----------------------------------------------------#"
 */
  if (__Pyx_PrintOne(0, __pyx_kp_s_Dilu_IMS) < 0) __PYX_ERR(0, 75, __pyx_L1_error)

  /* "ims_extractor.pyx":76
 *     print ""
 *     print "#--------------------Dilu-IMS------------------------#"
 *     print "|           Yu (Tom) Gao @ Yates Lab, TSRI           |"             # <<<<<<<<<<<<<<
 *     print "#----------------------------------------------------#"
 *     start = time.clock()
 */
  if (__Pyx_PrintOne(0, __pyx_kp_s_Yu_Tom_Gao_Yates_Lab_TSRI) < 0) __PYX_ERR(0, 76, __pyx_L1_error)

  /* "ims_extractor.pyx":77
 *     print "#--------------------Dilu-IMS------------------------#"
 *     print "|           Yu (Tom) Gao @ Yates Lab, TSRI           |"
 *     print "#----------------------------------------------------#"             # <<<<<<<<<<<<<<
 *     start = time.clock()
 *     retention = 0
 */
  if (__Pyx_PrintOne(0, __pyx_kp_s__10) < 0) __PYX_ERR(0, 77, __pyx_L1_error)

  /* "ims_extractor.pyx":78
 *     print "|           Yu (Tom) Gao @ Yates Lab, TSRI           |"
 *     print "#----------------------------------------------------#"
 *     start = time.clock()             # <<<<<<<<<<<<<<
 *     retention = 0
 *     xa = []
 */
  __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_time); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 78, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_clock); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 78, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = NULL;
  if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_2))) {
    __pyx_t_1 = PyMethod_GET_SELF(__pyx_t_2);
    if (likely(__pyx_t_1)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
      __Pyx_INCREF(__pyx_t_1);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_2, function);
    }
  }
  if (__pyx_t_1) {
    __pyx_t_3 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_t_1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 78, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  } else {
    __pyx_t_3 = __Pyx_PyObject_CallNoArg(__pyx_t_2); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 78, __pyx_L1_error)
  }
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_v_start = __pyx_t_3;
  __pyx_t_3 = 0;

  /* "ims_extractor.pyx":79
 *     print "#----------------------------------------------------#"
 *     start = time.clock()
 *     retention = 0             # <<<<<<<<<<<<<<
 *     xa = []
 *     xi = 0
 */
  __Pyx_INCREF(__pyx_int_0);
  __pyx_v_retention = __pyx_int_0;

  /* "ims_extractor.pyx":80
 *     start = time.clock()
 *     retention = 0
 *     xa = []             # <<<<<<<<<<<<<<
 *     xi = 0
 *     xm = float(50)
 */
  __pyx_t_3 = PyList_New(0); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 80, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_v_xa = ((PyObject*)__pyx_t_3);
  __pyx_t_3 = 0;

  /* "ims_extractor.pyx":81
 *     retention = 0
 *     xa = []
 *     xi = 0             # <<<<<<<<<<<<<<
 *     xm = float(50)
 *     while xi < 2000:
 */
  __Pyx_INCREF(__pyx_int_0);
  __pyx_v_xi = __pyx_int_0;

  /* "ims_extractor.pyx":82
 *     xa = []
 *     xi = 0
 *     xm = float(50)             # <<<<<<<<<<<<<<
 *     while xi < 2000:
 *         xm += xm / res_factor
 */
  __pyx_t_3 = __Pyx_PyNumber_Float(__pyx_int_50); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 82, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_v_xm = __pyx_t_3;
  __pyx_t_3 = 0;

  /* "ims_extractor.pyx":83
 *     xi = 0
 *     xm = float(50)
 *     while xi < 2000:             # <<<<<<<<<<<<<<
 *         xm += xm / res_factor
 *         xa.append(xm)
 */
  while (1) {
    __pyx_t_3 = PyObject_RichCompare(__pyx_v_xi, __pyx_int_2000, Py_LT); __Pyx_XGOTREF(__pyx_t_3); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 83, __pyx_L1_error)
    __pyx_t_4 = __Pyx_PyObject_IsTrue(__pyx_t_3); if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(0, 83, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    if (!__pyx_t_4) break;

    /* "ims_extractor.pyx":84
 *     xm = float(50)
 *     while xi < 2000:
 *         xm += xm / res_factor             # <<<<<<<<<<<<<<
 *         xa.append(xm)
 *         xi = int(xm)
 */
    __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_res_factor); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 84, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_2 = __Pyx_PyNumber_Divide(__pyx_v_xm, __pyx_t_3); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 84, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_t_3 = PyNumber_InPlaceAdd(__pyx_v_xm, __pyx_t_2); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 84, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_DECREF_SET(__pyx_v_xm, __pyx_t_3);
    __pyx_t_3 = 0;

    /* "ims_extractor.pyx":85
 *     while xi < 2000:
 *         xm += xm / res_factor
 *         xa.append(xm)             # <<<<<<<<<<<<<<
 *         xi = int(xm)
 *     datax = [list([]) for _ in xrange(res_array[resolution - 1] + 1)]
 */
    __pyx_t_5 = __Pyx_PyList_Append(__pyx_v_xa, __pyx_v_xm); if (unlikely(__pyx_t_5 == -1)) __PYX_ERR(0, 85, __pyx_L1_error)

    /* "ims_extractor.pyx":86
 *         xm += xm / res_factor
 *         xa.append(xm)
 *         xi = int(xm)             # <<<<<<<<<<<<<<
 *     datax = [list([]) for _ in xrange(res_array[resolution - 1] + 1)]
 *     # construct a huge array datax[] to contain each resolution bin
 */
    __pyx_t_3 = __Pyx_PyNumber_Int(__pyx_v_xm); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 86, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF_SET(__pyx_v_xi, __pyx_t_3);
    __pyx_t_3 = 0;
  }

  /* "ims_extractor.pyx":87
 *         xa.append(xm)
 *         xi = int(xm)
 *     datax = [list([]) for _ in xrange(res_array[resolution - 1] + 1)]             # <<<<<<<<<<<<<<
 *     # construct a huge array datax[] to contain each resolution bin
 * 
 */
  __pyx_t_3 = PyList_New(0); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 87, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_res_array); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 87, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_resolution); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 87, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __pyx_t_6 = __Pyx_PyInt_SubtractObjC(__pyx_t_1, __pyx_int_1, 1, 0); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 87, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyObject_GetItem(__pyx_t_2, __pyx_t_6); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 87, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __pyx_t_6 = __Pyx_PyInt_AddObjC(__pyx_t_1, __pyx_int_1, 1, 0); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 87, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyTuple_New(1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 87, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_GIVEREF(__pyx_t_6);
  PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_t_6);
  __pyx_t_6 = 0;
  __pyx_t_6 = __Pyx_PyObject_Call(__pyx_builtin_xrange, __pyx_t_1, NULL); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 87, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  if (likely(PyList_CheckExact(__pyx_t_6)) || PyTuple_CheckExact(__pyx_t_6)) {
    __pyx_t_1 = __pyx_t_6; __Pyx_INCREF(__pyx_t_1); __pyx_t_7 = 0;
    __pyx_t_8 = NULL;
  } else {
    __pyx_t_7 = -1; __pyx_t_1 = PyObject_GetIter(__pyx_t_6); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 87, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_8 = Py_TYPE(__pyx_t_1)->tp_iternext; if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 87, __pyx_L1_error)
  }
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  for (;;) {
    if (likely(!__pyx_t_8)) {
      if (likely(PyList_CheckExact(__pyx_t_1))) {
        if (__pyx_t_7 >= PyList_GET_SIZE(__pyx_t_1)) break;
        #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
        __pyx_t_6 = PyList_GET_ITEM(__pyx_t_1, __pyx_t_7); __Pyx_INCREF(__pyx_t_6); __pyx_t_7++; if (unlikely(0 < 0)) __PYX_ERR(0, 87, __pyx_L1_error)
        #else
        __pyx_t_6 = PySequence_ITEM(__pyx_t_1, __pyx_t_7); __pyx_t_7++; if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 87, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_6);
        #endif
      } else {
        if (__pyx_t_7 >= PyTuple_GET_SIZE(__pyx_t_1)) break;
        #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
        __pyx_t_6 = PyTuple_GET_ITEM(__pyx_t_1, __pyx_t_7); __Pyx_INCREF(__pyx_t_6); __pyx_t_7++; if (unlikely(0 < 0)) __PYX_ERR(0, 87, __pyx_L1_error)
        #else
        __pyx_t_6 = PySequence_ITEM(__pyx_t_1, __pyx_t_7); __pyx_t_7++; if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 87, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_6);
        #endif
      }
    } else {
      __pyx_t_6 = __pyx_t_8(__pyx_t_1);
      if (unlikely(!__pyx_t_6)) {
        PyObject* exc_type = PyErr_Occurred();
        if (exc_type) {
          if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
          else __PYX_ERR(0, 87, __pyx_L1_error)
        }
        break;
      }
      __Pyx_GOTREF(__pyx_t_6);
    }
    __Pyx_XDECREF_SET(__pyx_v__, __pyx_t_6);
    __pyx_t_6 = 0;
    __pyx_t_6 = PyList_New(0); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 87, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_2 = PySequence_List(__pyx_t_6); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 87, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    if (unlikely(__Pyx_ListComp_Append(__pyx_t_3, (PyObject*)__pyx_t_2))) __PYX_ERR(0, 87, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  }
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_v_datax = ((PyObject*)__pyx_t_3);
  __pyx_t_3 = 0;

  /* "ims_extractor.pyx":90
 *     # construct a huge array datax[] to contain each resolution bin
 * 
 *     file_name_ims = file_name + '.ims'             # <<<<<<<<<<<<<<
 * 
 *     file_name_freq = file_name.split('.')[0] + '_frequency.csv'
 */
  __pyx_t_3 = PyNumber_Add(__pyx_v_file_name, __pyx_kp_s_ims); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 90, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_v_file_name_ims = __pyx_t_3;
  __pyx_t_3 = 0;

  /* "ims_extractor.pyx":92
 *     file_name_ims = file_name + '.ims'
 * 
 *     file_name_freq = file_name.split('.')[0] + '_frequency.csv'             # <<<<<<<<<<<<<<
 *     # file1 = open(file_name, 'r')
 *     #print file_name_ims
 */
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_v_file_name, __pyx_n_s_split); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 92, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_tuple__12, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 92, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = __Pyx_GetItemInt(__pyx_t_1, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 92, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = PyNumber_Add(__pyx_t_3, __pyx_kp_s_frequency_csv); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 92, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_v_file_name_freq = __pyx_t_1;
  __pyx_t_1 = 0;

  /* "ims_extractor.pyx":97
 *     #print file_name_ims, file_name.replace('.ms1', '') + '\\' + file_name.split('\\')[-1] + '.ims'
 *     #time.sleep(50)
 *     if os.path.isfile(file_name_ims) or os.path.isfile(file_name.replace('.ms1', '') + '\\' + file_name.split('\\')[-1] + '.ims'):             # <<<<<<<<<<<<<<
 *         print "file_exist!"
 *     else:
 */
  __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_os); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 97, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_path); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 97, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_isfile); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 97, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = NULL;
  if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_3))) {
    __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_3);
    if (likely(__pyx_t_2)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
      __Pyx_INCREF(__pyx_t_2);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_3, function);
    }
  }
  if (!__pyx_t_2) {
    __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_v_file_name_ims); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 97, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_3)) {
      PyObject *__pyx_temp[2] = {__pyx_t_2, __pyx_v_file_name_ims};
      __pyx_t_1 = __Pyx_PyFunction_FastCall(__pyx_t_3, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 97, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_GOTREF(__pyx_t_1);
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_3)) {
      PyObject *__pyx_temp[2] = {__pyx_t_2, __pyx_v_file_name_ims};
      __pyx_t_1 = __Pyx_PyCFunction_FastCall(__pyx_t_3, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 97, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
      __Pyx_GOTREF(__pyx_t_1);
    } else
    #endif
    {
      __pyx_t_6 = PyTuple_New(1+1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 97, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_6);
      __Pyx_GIVEREF(__pyx_t_2); PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_2); __pyx_t_2 = NULL;
      __Pyx_INCREF(__pyx_v_file_name_ims);
      __Pyx_GIVEREF(__pyx_v_file_name_ims);
      PyTuple_SET_ITEM(__pyx_t_6, 0+1, __pyx_v_file_name_ims);
      __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_t_6, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 97, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_9 = __Pyx_PyObject_IsTrue(__pyx_t_1); if (unlikely(__pyx_t_9 < 0)) __PYX_ERR(0, 97, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  if (!__pyx_t_9) {
  } else {
    __pyx_t_4 = __pyx_t_9;
    goto __pyx_L8_bool_binop_done;
  }
  __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_os); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 97, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_path); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 97, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_6, __pyx_n_s_isfile); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 97, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_3);
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_v_file_name, __pyx_n_s_replace); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 97, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_6, __pyx_tuple__13, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 97, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __pyx_t_6 = PyNumber_Add(__pyx_t_2, __pyx_kp_s__14); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 97, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_6);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_file_name, __pyx_n_s_split); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 97, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __pyx_t_10 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_tuple__15, NULL); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 97, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_10);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_GetItemInt(__pyx_t_10, -1L, long, 1, __Pyx_PyInt_From_long, 0, 1, 1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 97, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
  __pyx_t_10 = PyNumber_Add(__pyx_t_6, __pyx_t_2); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 97, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_10);
  __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = PyNumber_Add(__pyx_t_10, __pyx_kp_s_ims); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 97, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
  __pyx_t_10 = NULL;
  if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_3))) {
    __pyx_t_10 = PyMethod_GET_SELF(__pyx_t_3);
    if (likely(__pyx_t_10)) {
      PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
      __Pyx_INCREF(__pyx_t_10);
      __Pyx_INCREF(function);
      __Pyx_DECREF_SET(__pyx_t_3, function);
    }
  }
  if (!__pyx_t_10) {
    __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 97, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_GOTREF(__pyx_t_1);
  } else {
    #if CYTHON_FAST_PYCALL
    if (PyFunction_Check(__pyx_t_3)) {
      PyObject *__pyx_temp[2] = {__pyx_t_10, __pyx_t_2};
      __pyx_t_1 = __Pyx_PyFunction_FastCall(__pyx_t_3, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 97, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_10); __pyx_t_10 = 0;
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    } else
    #endif
    #if CYTHON_FAST_PYCCALL
    if (__Pyx_PyFastCFunction_Check(__pyx_t_3)) {
      PyObject *__pyx_temp[2] = {__pyx_t_10, __pyx_t_2};
      __pyx_t_1 = __Pyx_PyCFunction_FastCall(__pyx_t_3, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 97, __pyx_L1_error)
      __Pyx_XDECREF(__pyx_t_10); __pyx_t_10 = 0;
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    } else
    #endif
    {
      __pyx_t_6 = PyTuple_New(1+1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 97, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_6);
      __Pyx_GIVEREF(__pyx_t_10); PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_10); __pyx_t_10 = NULL;
      __Pyx_GIVEREF(__pyx_t_2);
      PyTuple_SET_ITEM(__pyx_t_6, 0+1, __pyx_t_2);
      __pyx_t_2 = 0;
      __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_t_6, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 97, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    }
  }
  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
  __pyx_t_9 = __Pyx_PyObject_IsTrue(__pyx_t_1); if (unlikely(__pyx_t_9 < 0)) __PYX_ERR(0, 97, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_4 = __pyx_t_9;
  __pyx_L8_bool_binop_done:;
  if (__pyx_t_4) {

    /* "ims_extractor.pyx":98
 *     #time.sleep(50)
 *     if os.path.isfile(file_name_ims) or os.path.isfile(file_name.replace('.ms1', '') + '\\' + file_name.split('\\')[-1] + '.ims'):
 *         print "file_exist!"             # <<<<<<<<<<<<<<
 *     else:
 *         file2 = open(file_name_ims, 'wb')
 */
    if (__Pyx_PrintOne(0, __pyx_kp_s_file_exist) < 0) __PYX_ERR(0, 98, __pyx_L1_error)

    /* "ims_extractor.pyx":97
 *     #print file_name_ims, file_name.replace('.ms1', '') + '\\' + file_name.split('\\')[-1] + '.ims'
 *     #time.sleep(50)
 *     if os.path.isfile(file_name_ims) or os.path.isfile(file_name.replace('.ms1', '') + '\\' + file_name.split('\\')[-1] + '.ims'):             # <<<<<<<<<<<<<<
 *         print "file_exist!"
 *     else:
 */
    goto __pyx_L7;
  }

  /* "ims_extractor.pyx":100
 *         print "file_exist!"
 *     else:
 *         file2 = open(file_name_ims, 'wb')             # <<<<<<<<<<<<<<
 * 
 *         print "| Dilu initialized                                   |"
 */
  /*else*/ {
    __pyx_t_1 = PyTuple_New(2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 100, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_INCREF(__pyx_v_file_name_ims);
    __Pyx_GIVEREF(__pyx_v_file_name_ims);
    PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_v_file_name_ims);
    __Pyx_INCREF(__pyx_n_s_wb);
    __Pyx_GIVEREF(__pyx_n_s_wb);
    PyTuple_SET_ITEM(__pyx_t_1, 1, __pyx_n_s_wb);
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_builtin_open, __pyx_t_1, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 100, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_v_file2 = __pyx_t_3;
    __pyx_t_3 = 0;

    /* "ims_extractor.pyx":102
 *         file2 = open(file_name_ims, 'wb')
 * 
 *         print "| Dilu initialized                                   |"             # <<<<<<<<<<<<<<
 * 
 *         end = time.clock()
 */
    if (__Pyx_PrintOne(0, __pyx_kp_s_Dilu_initialized) < 0) __PYX_ERR(0, 102, __pyx_L1_error)

    /* "ims_extractor.pyx":104
 *         print "| Dilu initialized                                   |"
 * 
 *         end = time.clock()             # <<<<<<<<<<<<<<
 *         timex = (end - start)
 *         print "| Time spent(s):", "{:10.4f}".format(timex), "                         |"
 */
    __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_time); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 104, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_clock); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 104, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_1 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_6))) {
      __pyx_t_1 = PyMethod_GET_SELF(__pyx_t_6);
      if (likely(__pyx_t_1)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_6);
        __Pyx_INCREF(__pyx_t_1);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_6, function);
      }
    }
    if (__pyx_t_1) {
      __pyx_t_3 = __Pyx_PyObject_CallOneArg(__pyx_t_6, __pyx_t_1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 104, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    } else {
      __pyx_t_3 = __Pyx_PyObject_CallNoArg(__pyx_t_6); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 104, __pyx_L1_error)
    }
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __pyx_v_end = __pyx_t_3;
    __pyx_t_3 = 0;

    /* "ims_extractor.pyx":105
 * 
 *         end = time.clock()
 *         timex = (end - start)             # <<<<<<<<<<<<<<
 *         print "| Time spent(s):", "{:10.4f}".format(timex), "                         |"
 *         print "#----------------------------------------------------#"
 */
    __pyx_t_3 = PyNumber_Subtract(__pyx_v_end, __pyx_v_start); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 105, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_v_timex = __pyx_t_3;
    __pyx_t_3 = 0;

    /* "ims_extractor.pyx":106
 *         end = time.clock()
 *         timex = (end - start)
 *         print "| Time spent(s):", "{:10.4f}".format(timex), "                         |"             # <<<<<<<<<<<<<<
 *         print "#----------------------------------------------------#"
 *         print "| Loading data...                                    |"
 */
    __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_kp_s_10_4f, __pyx_n_s_format); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 106, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_1 = NULL;
    if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_6))) {
      __pyx_t_1 = PyMethod_GET_SELF(__pyx_t_6);
      if (likely(__pyx_t_1)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_6);
        __Pyx_INCREF(__pyx_t_1);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_6, function);
      }
    }
    if (!__pyx_t_1) {
      __pyx_t_3 = __Pyx_PyObject_CallOneArg(__pyx_t_6, __pyx_v_timex); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 106, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
    } else {
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_6)) {
        PyObject *__pyx_temp[2] = {__pyx_t_1, __pyx_v_timex};
        __pyx_t_3 = __Pyx_PyFunction_FastCall(__pyx_t_6, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 106, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;
        __Pyx_GOTREF(__pyx_t_3);
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_6)) {
        PyObject *__pyx_temp[2] = {__pyx_t_1, __pyx_v_timex};
        __pyx_t_3 = __Pyx_PyCFunction_FastCall(__pyx_t_6, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 106, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;
        __Pyx_GOTREF(__pyx_t_3);
      } else
      #endif
      {
        __pyx_t_2 = PyTuple_New(1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 106, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_2);
        __Pyx_GIVEREF(__pyx_t_1); PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_1); __pyx_t_1 = NULL;
        __Pyx_INCREF(__pyx_v_timex);
        __Pyx_GIVEREF(__pyx_v_timex);
        PyTuple_SET_ITEM(__pyx_t_2, 0+1, __pyx_v_timex);
        __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_6, __pyx_t_2, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 106, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      }
    }
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __pyx_t_6 = PyTuple_New(3); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 106, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_INCREF(__pyx_kp_s_Time_spent_s);
    __Pyx_GIVEREF(__pyx_kp_s_Time_spent_s);
    PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_kp_s_Time_spent_s);
    __Pyx_GIVEREF(__pyx_t_3);
    PyTuple_SET_ITEM(__pyx_t_6, 1, __pyx_t_3);
    __Pyx_INCREF(__pyx_kp_s__16);
    __Pyx_GIVEREF(__pyx_kp_s__16);
    PyTuple_SET_ITEM(__pyx_t_6, 2, __pyx_kp_s__16);
    __pyx_t_3 = 0;
    if (__Pyx_Print(0, __pyx_t_6, 1) < 0) __PYX_ERR(0, 106, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;

    /* "ims_extractor.pyx":107
 *         timex = (end - start)
 *         print "| Time spent(s):", "{:10.4f}".format(timex), "                         |"
 *         print "#----------------------------------------------------#"             # <<<<<<<<<<<<<<
 *         print "| Loading data...                                    |"
 *         start1 = time.clock()
 */
    if (__Pyx_PrintOne(0, __pyx_kp_s__10) < 0) __PYX_ERR(0, 107, __pyx_L1_error)

    /* "ims_extractor.pyx":108
 *         print "| Time spent(s):", "{:10.4f}".format(timex), "                         |"
 *         print "#----------------------------------------------------#"
 *         print "| Loading data...                                    |"             # <<<<<<<<<<<<<<
 *         start1 = time.clock()
 * 
 */
    if (__Pyx_PrintOne(0, __pyx_kp_s_Loading_data) < 0) __PYX_ERR(0, 108, __pyx_L1_error)

    /* "ims_extractor.pyx":109
 *         print "#----------------------------------------------------#"
 *         print "| Loading data...                                    |"
 *         start1 = time.clock()             # <<<<<<<<<<<<<<
 * 
 *         # pool = multiprocessing.Pool(processes=multiprocessing.cpu_count())
 */
    __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_time); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 109, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_clock); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 109, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_t_3 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_2))) {
      __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_2);
      if (likely(__pyx_t_3)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
        __Pyx_INCREF(__pyx_t_3);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_2, function);
      }
    }
    if (__pyx_t_3) {
      __pyx_t_6 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_t_3); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 109, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    } else {
      __pyx_t_6 = __Pyx_PyObject_CallNoArg(__pyx_t_2); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 109, __pyx_L1_error)
    }
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_v_start1 = __pyx_t_6;
    __pyx_t_6 = 0;

    /* "ims_extractor.pyx":112
 * 
 *         # pool = multiprocessing.Pool(processes=multiprocessing.cpu_count())
 *         with open(file_name) as lines:             # <<<<<<<<<<<<<<
 *             temp_data = map(load_data, lines)
 *         # pool.close()
 */
    /*with:*/ {
      __pyx_t_6 = PyTuple_New(1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 112, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_6);
      __Pyx_INCREF(__pyx_v_file_name);
      __Pyx_GIVEREF(__pyx_v_file_name);
      PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_v_file_name);
      __pyx_t_2 = __Pyx_PyObject_Call(__pyx_builtin_open, __pyx_t_6, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 112, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
      __pyx_t_11 = __Pyx_PyObject_LookupSpecial(__pyx_t_2, __pyx_n_s_exit); if (unlikely(!__pyx_t_11)) __PYX_ERR(0, 112, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_11);
      __pyx_t_3 = __Pyx_PyObject_LookupSpecial(__pyx_t_2, __pyx_n_s_enter); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 112, __pyx_L10_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_1 = NULL;
      if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_3))) {
        __pyx_t_1 = PyMethod_GET_SELF(__pyx_t_3);
        if (likely(__pyx_t_1)) {
          PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
          __Pyx_INCREF(__pyx_t_1);
          __Pyx_INCREF(function);
          __Pyx_DECREF_SET(__pyx_t_3, function);
        }
      }
      if (__pyx_t_1) {
        __pyx_t_6 = __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_t_1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 112, __pyx_L10_error)
        __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      } else {
        __pyx_t_6 = __Pyx_PyObject_CallNoArg(__pyx_t_3); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 112, __pyx_L10_error)
      }
      __Pyx_GOTREF(__pyx_t_6);
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __pyx_t_3 = __pyx_t_6;
      __pyx_t_6 = 0;
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
      /*try:*/ {
        {
          __Pyx_PyThreadState_declare
          __Pyx_PyThreadState_assign
          __Pyx_ExceptionSave(&__pyx_t_12, &__pyx_t_13, &__pyx_t_14);
          __Pyx_XGOTREF(__pyx_t_12);
          __Pyx_XGOTREF(__pyx_t_13);
          __Pyx_XGOTREF(__pyx_t_14);
          /*try:*/ {
            __pyx_v_lines = __pyx_t_3;
            __pyx_t_3 = 0;

            /* "ims_extractor.pyx":113
 *         # pool = multiprocessing.Pool(processes=multiprocessing.cpu_count())
 *         with open(file_name) as lines:
 *             temp_data = map(load_data, lines)             # <<<<<<<<<<<<<<
 *         # pool.close()
 *         # pool.join()
 */
            __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_load_data); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 113, __pyx_L14_error)
            __Pyx_GOTREF(__pyx_t_3);
            __pyx_t_2 = PyTuple_New(2); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 113, __pyx_L14_error)
            __Pyx_GOTREF(__pyx_t_2);
            __Pyx_GIVEREF(__pyx_t_3);
            PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_3);
            __Pyx_INCREF(__pyx_v_lines);
            __Pyx_GIVEREF(__pyx_v_lines);
            PyTuple_SET_ITEM(__pyx_t_2, 1, __pyx_v_lines);
            __pyx_t_3 = 0;
            __pyx_t_3 = __Pyx_PyObject_Call(__pyx_builtin_map, __pyx_t_2, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 113, __pyx_L14_error)
            __Pyx_GOTREF(__pyx_t_3);
            __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
            __pyx_v_temp_data = __pyx_t_3;
            __pyx_t_3 = 0;

            /* "ims_extractor.pyx":112
 * 
 *         # pool = multiprocessing.Pool(processes=multiprocessing.cpu_count())
 *         with open(file_name) as lines:             # <<<<<<<<<<<<<<
 *             temp_data = map(load_data, lines)
 *         # pool.close()
 */
          }
          __Pyx_XDECREF(__pyx_t_12); __pyx_t_12 = 0;
          __Pyx_XDECREF(__pyx_t_13); __pyx_t_13 = 0;
          __Pyx_XDECREF(__pyx_t_14); __pyx_t_14 = 0;
          goto __pyx_L21_try_end;
          __pyx_L14_error:;
          __Pyx_PyThreadState_assign
          __Pyx_XDECREF(__pyx_t_10); __pyx_t_10 = 0;
          __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;
          __Pyx_XDECREF(__pyx_t_6); __pyx_t_6 = 0;
          __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
          __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
          /*except:*/ {
            __Pyx_AddTraceback("ims_extractor.extract_file", __pyx_clineno, __pyx_lineno, __pyx_filename);
            if (__Pyx_GetException(&__pyx_t_3, &__pyx_t_2, &__pyx_t_6) < 0) __PYX_ERR(0, 112, __pyx_L16_except_error)
            __Pyx_GOTREF(__pyx_t_3);
            __Pyx_GOTREF(__pyx_t_2);
            __Pyx_GOTREF(__pyx_t_6);
            __pyx_t_1 = PyTuple_Pack(3, __pyx_t_3, __pyx_t_2, __pyx_t_6); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 112, __pyx_L16_except_error)
            __Pyx_GOTREF(__pyx_t_1);
            __pyx_t_15 = __Pyx_PyObject_Call(__pyx_t_11, __pyx_t_1, NULL);
            __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
            __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
            if (unlikely(!__pyx_t_15)) __PYX_ERR(0, 112, __pyx_L16_except_error)
            __Pyx_GOTREF(__pyx_t_15);
            __pyx_t_4 = __Pyx_PyObject_IsTrue(__pyx_t_15);
            __Pyx_DECREF(__pyx_t_15); __pyx_t_15 = 0;
            if (__pyx_t_4 < 0) __PYX_ERR(0, 112, __pyx_L16_except_error)
            __pyx_t_9 = ((!(__pyx_t_4 != 0)) != 0);
            if (__pyx_t_9) {
              __Pyx_GIVEREF(__pyx_t_3);
              __Pyx_GIVEREF(__pyx_t_2);
              __Pyx_XGIVEREF(__pyx_t_6);
              __Pyx_ErrRestoreWithState(__pyx_t_3, __pyx_t_2, __pyx_t_6);
              __pyx_t_3 = 0; __pyx_t_2 = 0; __pyx_t_6 = 0; 
              __PYX_ERR(0, 112, __pyx_L16_except_error)
            }
            __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
            __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
            __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
            goto __pyx_L15_exception_handled;
          }
          __pyx_L16_except_error:;
          __Pyx_PyThreadState_assign
          __Pyx_XGIVEREF(__pyx_t_12);
          __Pyx_XGIVEREF(__pyx_t_13);
          __Pyx_XGIVEREF(__pyx_t_14);
          __Pyx_ExceptionReset(__pyx_t_12, __pyx_t_13, __pyx_t_14);
          goto __pyx_L1_error;
          __pyx_L15_exception_handled:;
          __Pyx_PyThreadState_assign
          __Pyx_XGIVEREF(__pyx_t_12);
          __Pyx_XGIVEREF(__pyx_t_13);
          __Pyx_XGIVEREF(__pyx_t_14);
          __Pyx_ExceptionReset(__pyx_t_12, __pyx_t_13, __pyx_t_14);
          __pyx_L21_try_end:;
        }
      }
      /*finally:*/ {
        /*normal exit:*/{
          if (__pyx_t_11) {
            __pyx_t_14 = __Pyx_PyObject_Call(__pyx_t_11, __pyx_tuple__17, NULL);
            __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
            if (unlikely(!__pyx_t_14)) __PYX_ERR(0, 112, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_14);
            __Pyx_DECREF(__pyx_t_14); __pyx_t_14 = 0;
          }
          goto __pyx_L13;
        }
        __pyx_L13:;
      }
      goto __pyx_L25;
      __pyx_L10_error:;
      __Pyx_DECREF(__pyx_t_11); __pyx_t_11 = 0;
      goto __pyx_L1_error;
      __pyx_L25:;
    }

    /* "ims_extractor.pyx":117
 *         # pool.join()
 * 
 *         print "| All data loaded from disk                          |"             # <<<<<<<<<<<<<<
 *         end = time.clock()
 *         timex = (end - start1)
 */
    if (__Pyx_PrintOne(0, __pyx_kp_s_All_data_loaded_from_disk) < 0) __PYX_ERR(0, 117, __pyx_L1_error)

    /* "ims_extractor.pyx":118
 * 
 *         print "| All data loaded from disk                          |"
 *         end = time.clock()             # <<<<<<<<<<<<<<
 *         timex = (end - start1)
 *         print "| Time spent(s):", "{:10.4f}".format(timex), "                         |"
 */
    __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_time); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 118, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_clock); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 118, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_t_2 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_3))) {
      __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_3);
      if (likely(__pyx_t_2)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
        __Pyx_INCREF(__pyx_t_2);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_3, function);
      }
    }
    if (__pyx_t_2) {
      __pyx_t_6 = __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_t_2); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 118, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    } else {
      __pyx_t_6 = __Pyx_PyObject_CallNoArg(__pyx_t_3); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 118, __pyx_L1_error)
    }
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __Pyx_DECREF_SET(__pyx_v_end, __pyx_t_6);
    __pyx_t_6 = 0;

    /* "ims_extractor.pyx":119
 *         print "| All data loaded from disk                          |"
 *         end = time.clock()
 *         timex = (end - start1)             # <<<<<<<<<<<<<<
 *         print "| Time spent(s):", "{:10.4f}".format(timex), "                         |"
 *         print "#----------------------------------------------------#"
 */
    __pyx_t_6 = PyNumber_Subtract(__pyx_v_end, __pyx_v_start1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 119, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF_SET(__pyx_v_timex, __pyx_t_6);
    __pyx_t_6 = 0;

    /* "ims_extractor.pyx":120
 *         end = time.clock()
 *         timex = (end - start1)
 *         print "| Time spent(s):", "{:10.4f}".format(timex), "                         |"             # <<<<<<<<<<<<<<
 *         print "#----------------------------------------------------#"
 *         print "| Analyzing spectra...                               |"
 */
    __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_kp_s_10_4f, __pyx_n_s_format); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 120, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_2 = NULL;
    if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_3))) {
      __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_3);
      if (likely(__pyx_t_2)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
        __Pyx_INCREF(__pyx_t_2);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_3, function);
      }
    }
    if (!__pyx_t_2) {
      __pyx_t_6 = __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_v_timex); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 120, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_6);
    } else {
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_3)) {
        PyObject *__pyx_temp[2] = {__pyx_t_2, __pyx_v_timex};
        __pyx_t_6 = __Pyx_PyFunction_FastCall(__pyx_t_3, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 120, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
        __Pyx_GOTREF(__pyx_t_6);
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_3)) {
        PyObject *__pyx_temp[2] = {__pyx_t_2, __pyx_v_timex};
        __pyx_t_6 = __Pyx_PyCFunction_FastCall(__pyx_t_3, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 120, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
        __Pyx_GOTREF(__pyx_t_6);
      } else
      #endif
      {
        __pyx_t_1 = PyTuple_New(1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 120, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        __Pyx_GIVEREF(__pyx_t_2); PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_t_2); __pyx_t_2 = NULL;
        __Pyx_INCREF(__pyx_v_timex);
        __Pyx_GIVEREF(__pyx_v_timex);
        PyTuple_SET_ITEM(__pyx_t_1, 0+1, __pyx_v_timex);
        __pyx_t_6 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_t_1, NULL); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 120, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_6);
        __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      }
    }
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_t_3 = PyTuple_New(3); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 120, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_INCREF(__pyx_kp_s_Time_spent_s);
    __Pyx_GIVEREF(__pyx_kp_s_Time_spent_s);
    PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_kp_s_Time_spent_s);
    __Pyx_GIVEREF(__pyx_t_6);
    PyTuple_SET_ITEM(__pyx_t_3, 1, __pyx_t_6);
    __Pyx_INCREF(__pyx_kp_s__16);
    __Pyx_GIVEREF(__pyx_kp_s__16);
    PyTuple_SET_ITEM(__pyx_t_3, 2, __pyx_kp_s__16);
    __pyx_t_6 = 0;
    if (__Pyx_Print(0, __pyx_t_3, 1) < 0) __PYX_ERR(0, 120, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

    /* "ims_extractor.pyx":121
 *         timex = (end - start1)
 *         print "| Time spent(s):", "{:10.4f}".format(timex), "                         |"
 *         print "#----------------------------------------------------#"             # <<<<<<<<<<<<<<
 *         print "| Analyzing spectra...                               |"
 *         start1 = time.clock()
 */
    if (__Pyx_PrintOne(0, __pyx_kp_s__10) < 0) __PYX_ERR(0, 121, __pyx_L1_error)

    /* "ims_extractor.pyx":122
 *         print "| Time spent(s):", "{:10.4f}".format(timex), "                         |"
 *         print "#----------------------------------------------------#"
 *         print "| Analyzing spectra...                               |"             # <<<<<<<<<<<<<<
 *         start1 = time.clock()
 * 
 */
    if (__Pyx_PrintOne(0, __pyx_kp_s_Analyzing_spectra) < 0) __PYX_ERR(0, 122, __pyx_L1_error)

    /* "ims_extractor.pyx":123
 *         print "#----------------------------------------------------#"
 *         print "| Analyzing spectra...                               |"
 *         start1 = time.clock()             # <<<<<<<<<<<<<<
 * 
 *         for item in temp_data:
 */
    __pyx_t_6 = __Pyx_GetModuleGlobalName(__pyx_n_s_time); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 123, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_t_6, __pyx_n_s_clock); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 123, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __pyx_t_6 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_1))) {
      __pyx_t_6 = PyMethod_GET_SELF(__pyx_t_1);
      if (likely(__pyx_t_6)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_1);
        __Pyx_INCREF(__pyx_t_6);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_1, function);
      }
    }
    if (__pyx_t_6) {
      __pyx_t_3 = __Pyx_PyObject_CallOneArg(__pyx_t_1, __pyx_t_6); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 123, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    } else {
      __pyx_t_3 = __Pyx_PyObject_CallNoArg(__pyx_t_1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 123, __pyx_L1_error)
    }
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __Pyx_DECREF_SET(__pyx_v_start1, __pyx_t_3);
    __pyx_t_3 = 0;

    /* "ims_extractor.pyx":125
 *         start1 = time.clock()
 * 
 *         for item in temp_data:             # <<<<<<<<<<<<<<
 *             if len(item) == 1:
 *                 retention = item[0]
 */
    if (unlikely(!__pyx_v_temp_data)) { __Pyx_RaiseUnboundLocalError("temp_data"); __PYX_ERR(0, 125, __pyx_L1_error) }
    if (likely(PyList_CheckExact(__pyx_v_temp_data)) || PyTuple_CheckExact(__pyx_v_temp_data)) {
      __pyx_t_3 = __pyx_v_temp_data; __Pyx_INCREF(__pyx_t_3); __pyx_t_7 = 0;
      __pyx_t_8 = NULL;
    } else {
      __pyx_t_7 = -1; __pyx_t_3 = PyObject_GetIter(__pyx_v_temp_data); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 125, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_8 = Py_TYPE(__pyx_t_3)->tp_iternext; if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 125, __pyx_L1_error)
    }
    for (;;) {
      if (likely(!__pyx_t_8)) {
        if (likely(PyList_CheckExact(__pyx_t_3))) {
          if (__pyx_t_7 >= PyList_GET_SIZE(__pyx_t_3)) break;
          #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
          __pyx_t_1 = PyList_GET_ITEM(__pyx_t_3, __pyx_t_7); __Pyx_INCREF(__pyx_t_1); __pyx_t_7++; if (unlikely(0 < 0)) __PYX_ERR(0, 125, __pyx_L1_error)
          #else
          __pyx_t_1 = PySequence_ITEM(__pyx_t_3, __pyx_t_7); __pyx_t_7++; if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 125, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_1);
          #endif
        } else {
          if (__pyx_t_7 >= PyTuple_GET_SIZE(__pyx_t_3)) break;
          #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
          __pyx_t_1 = PyTuple_GET_ITEM(__pyx_t_3, __pyx_t_7); __Pyx_INCREF(__pyx_t_1); __pyx_t_7++; if (unlikely(0 < 0)) __PYX_ERR(0, 125, __pyx_L1_error)
          #else
          __pyx_t_1 = PySequence_ITEM(__pyx_t_3, __pyx_t_7); __pyx_t_7++; if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 125, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_1);
          #endif
        }
      } else {
        __pyx_t_1 = __pyx_t_8(__pyx_t_3);
        if (unlikely(!__pyx_t_1)) {
          PyObject* exc_type = PyErr_Occurred();
          if (exc_type) {
            if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
            else __PYX_ERR(0, 125, __pyx_L1_error)
          }
          break;
        }
        __Pyx_GOTREF(__pyx_t_1);
      }
      __Pyx_XDECREF_SET(__pyx_v_item, __pyx_t_1);
      __pyx_t_1 = 0;

      /* "ims_extractor.pyx":126
 * 
 *         for item in temp_data:
 *             if len(item) == 1:             # <<<<<<<<<<<<<<
 *                 retention = item[0]
 *             if len(item) == 3:
 */
      __pyx_t_16 = PyObject_Length(__pyx_v_item); if (unlikely(__pyx_t_16 == -1)) __PYX_ERR(0, 126, __pyx_L1_error)
      __pyx_t_9 = ((__pyx_t_16 == 1) != 0);
      if (__pyx_t_9) {

        /* "ims_extractor.pyx":127
 *         for item in temp_data:
 *             if len(item) == 1:
 *                 retention = item[0]             # <<<<<<<<<<<<<<
 *             if len(item) == 3:
 *                 datax[item[0]] += [item[1], item[2], retention]
 */
        __pyx_t_1 = __Pyx_GetItemInt(__pyx_v_item, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 127, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        __Pyx_DECREF_SET(__pyx_v_retention, __pyx_t_1);
        __pyx_t_1 = 0;

        /* "ims_extractor.pyx":126
 * 
 *         for item in temp_data:
 *             if len(item) == 1:             # <<<<<<<<<<<<<<
 *                 retention = item[0]
 *             if len(item) == 3:
 */
      }

      /* "ims_extractor.pyx":128
 *             if len(item) == 1:
 *                 retention = item[0]
 *             if len(item) == 3:             # <<<<<<<<<<<<<<
 *                 datax[item[0]] += [item[1], item[2], retention]
 * 
 */
      __pyx_t_16 = PyObject_Length(__pyx_v_item); if (unlikely(__pyx_t_16 == -1)) __PYX_ERR(0, 128, __pyx_L1_error)
      __pyx_t_9 = ((__pyx_t_16 == 3) != 0);
      if (__pyx_t_9) {

        /* "ims_extractor.pyx":129
 *                 retention = item[0]
 *             if len(item) == 3:
 *                 datax[item[0]] += [item[1], item[2], retention]             # <<<<<<<<<<<<<<
 * 
 *         end_time = retention
 */
        __pyx_t_1 = __Pyx_GetItemInt(__pyx_v_item, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 129, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        __pyx_t_6 = PyObject_GetItem(__pyx_v_datax, __pyx_t_1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 129, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_6);
        __pyx_t_2 = __Pyx_GetItemInt(__pyx_v_item, 1, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 129, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_2);
        __pyx_t_10 = __Pyx_GetItemInt(__pyx_v_item, 2, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 129, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_10);
        __pyx_t_17 = PyList_New(3); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 129, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_17);
        __Pyx_GIVEREF(__pyx_t_2);
        PyList_SET_ITEM(__pyx_t_17, 0, __pyx_t_2);
        __Pyx_GIVEREF(__pyx_t_10);
        PyList_SET_ITEM(__pyx_t_17, 1, __pyx_t_10);
        __Pyx_INCREF(__pyx_v_retention);
        __Pyx_GIVEREF(__pyx_v_retention);
        PyList_SET_ITEM(__pyx_t_17, 2, __pyx_v_retention);
        __pyx_t_2 = 0;
        __pyx_t_10 = 0;
        __pyx_t_10 = PyNumber_InPlaceAdd(__pyx_t_6, __pyx_t_17); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 129, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_10);
        __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
        __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
        if (unlikely(PyObject_SetItem(__pyx_v_datax, __pyx_t_1, __pyx_t_10) < 0)) __PYX_ERR(0, 129, __pyx_L1_error)
        __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
        __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

        /* "ims_extractor.pyx":128
 *             if len(item) == 1:
 *                 retention = item[0]
 *             if len(item) == 3:             # <<<<<<<<<<<<<<
 *                 datax[item[0]] += [item[1], item[2], retention]
 * 
 */
      }

      /* "ims_extractor.pyx":125
 *         start1 = time.clock()
 * 
 *         for item in temp_data:             # <<<<<<<<<<<<<<
 *             if len(item) == 1:
 *                 retention = item[0]
 */
    }
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

    /* "ims_extractor.pyx":131
 *                 datax[item[0]] += [item[1], item[2], retention]
 * 
 *         end_time = retention             # <<<<<<<<<<<<<<
 * 
 *         end = time.clock()
 */
    if (PyDict_SetItem(__pyx_d, __pyx_n_s_end_time, __pyx_v_retention) < 0) __PYX_ERR(0, 131, __pyx_L1_error)

    /* "ims_extractor.pyx":133
 *         end_time = retention
 * 
 *         end = time.clock()             # <<<<<<<<<<<<<<
 *         timex = (end - start1)
 *         effct = 0
 */
    __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_time); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 133, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_10 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_clock); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 133, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_10);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_1 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_10))) {
      __pyx_t_1 = PyMethod_GET_SELF(__pyx_t_10);
      if (likely(__pyx_t_1)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_10);
        __Pyx_INCREF(__pyx_t_1);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_10, function);
      }
    }
    if (__pyx_t_1) {
      __pyx_t_3 = __Pyx_PyObject_CallOneArg(__pyx_t_10, __pyx_t_1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 133, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    } else {
      __pyx_t_3 = __Pyx_PyObject_CallNoArg(__pyx_t_10); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 133, __pyx_L1_error)
    }
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
    __Pyx_DECREF_SET(__pyx_v_end, __pyx_t_3);
    __pyx_t_3 = 0;

    /* "ims_extractor.pyx":134
 * 
 *         end = time.clock()
 *         timex = (end - start1)             # <<<<<<<<<<<<<<
 *         effct = 0
 *         for item in datax:
 */
    __pyx_t_3 = PyNumber_Subtract(__pyx_v_end, __pyx_v_start1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 134, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF_SET(__pyx_v_timex, __pyx_t_3);
    __pyx_t_3 = 0;

    /* "ims_extractor.pyx":135
 *         end = time.clock()
 *         timex = (end - start1)
 *         effct = 0             # <<<<<<<<<<<<<<
 *         for item in datax:
 *             if len(item) != 0:
 */
    __Pyx_INCREF(__pyx_int_0);
    __pyx_v_effct = __pyx_int_0;

    /* "ims_extractor.pyx":136
 *         timex = (end - start1)
 *         effct = 0
 *         for item in datax:             # <<<<<<<<<<<<<<
 *             if len(item) != 0:
 *                 effct += 1
 */
    __pyx_t_3 = __pyx_v_datax; __Pyx_INCREF(__pyx_t_3); __pyx_t_7 = 0;
    for (;;) {
      if (__pyx_t_7 >= PyList_GET_SIZE(__pyx_t_3)) break;
      #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
      __pyx_t_10 = PyList_GET_ITEM(__pyx_t_3, __pyx_t_7); __Pyx_INCREF(__pyx_t_10); __pyx_t_7++; if (unlikely(0 < 0)) __PYX_ERR(0, 136, __pyx_L1_error)
      #else
      __pyx_t_10 = PySequence_ITEM(__pyx_t_3, __pyx_t_7); __pyx_t_7++; if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 136, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_10);
      #endif
      __Pyx_XDECREF_SET(__pyx_v_item, __pyx_t_10);
      __pyx_t_10 = 0;

      /* "ims_extractor.pyx":137
 *         effct = 0
 *         for item in datax:
 *             if len(item) != 0:             # <<<<<<<<<<<<<<
 *                 effct += 1
 * 
 */
      __pyx_t_16 = PyObject_Length(__pyx_v_item); if (unlikely(__pyx_t_16 == -1)) __PYX_ERR(0, 137, __pyx_L1_error)
      __pyx_t_9 = ((__pyx_t_16 != 0) != 0);
      if (__pyx_t_9) {

        /* "ims_extractor.pyx":138
 *         for item in datax:
 *             if len(item) != 0:
 *                 effct += 1             # <<<<<<<<<<<<<<
 * 
 *         print "|", str(len(datax)).ljust(8), "spectra analyzed at", resolution, "ppm accuracy        |"
 */
        __pyx_t_10 = __Pyx_PyInt_AddObjC(__pyx_v_effct, __pyx_int_1, 1, 1); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 138, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_10);
        __Pyx_DECREF_SET(__pyx_v_effct, __pyx_t_10);
        __pyx_t_10 = 0;

        /* "ims_extractor.pyx":137
 *         effct = 0
 *         for item in datax:
 *             if len(item) != 0:             # <<<<<<<<<<<<<<
 *                 effct += 1
 * 
 */
      }

      /* "ims_extractor.pyx":136
 *         timex = (end - start1)
 *         effct = 0
 *         for item in datax:             # <<<<<<<<<<<<<<
 *             if len(item) != 0:
 *                 effct += 1
 */
    }
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

    /* "ims_extractor.pyx":140
 *                 effct += 1
 * 
 *         print "|", str(len(datax)).ljust(8), "spectra analyzed at", resolution, "ppm accuracy        |"             # <<<<<<<<<<<<<<
 *         # print effct, float(effct)/float(len(datax))
 *         print "| Time spent(s):", "{:10.4f}".format(timex), "                         |"
 */
    __pyx_t_7 = PyList_GET_SIZE(__pyx_v_datax); if (unlikely(__pyx_t_7 == -1)) __PYX_ERR(0, 140, __pyx_L1_error)
    __pyx_t_3 = PyInt_FromSsize_t(__pyx_t_7); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 140, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_10 = PyTuple_New(1); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 140, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_10);
    __Pyx_GIVEREF(__pyx_t_3);
    PyTuple_SET_ITEM(__pyx_t_10, 0, __pyx_t_3);
    __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(((PyObject *)(&PyString_Type)), __pyx_t_10, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 140, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
    __pyx_t_10 = __Pyx_PyObject_GetAttrStr(__pyx_t_3, __pyx_n_s_ljust); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 140, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_10);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_10, __pyx_tuple__19, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 140, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
    __pyx_t_10 = __Pyx_GetModuleGlobalName(__pyx_n_s_resolution); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 140, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_10);
    __pyx_t_1 = PyTuple_New(5); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 140, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_INCREF(__pyx_kp_s__18);
    __Pyx_GIVEREF(__pyx_kp_s__18);
    PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_kp_s__18);
    __Pyx_GIVEREF(__pyx_t_3);
    PyTuple_SET_ITEM(__pyx_t_1, 1, __pyx_t_3);
    __Pyx_INCREF(__pyx_kp_s_spectra_analyzed_at);
    __Pyx_GIVEREF(__pyx_kp_s_spectra_analyzed_at);
    PyTuple_SET_ITEM(__pyx_t_1, 2, __pyx_kp_s_spectra_analyzed_at);
    __Pyx_GIVEREF(__pyx_t_10);
    PyTuple_SET_ITEM(__pyx_t_1, 3, __pyx_t_10);
    __Pyx_INCREF(__pyx_kp_s_ppm_accuracy);
    __Pyx_GIVEREF(__pyx_kp_s_ppm_accuracy);
    PyTuple_SET_ITEM(__pyx_t_1, 4, __pyx_kp_s_ppm_accuracy);
    __pyx_t_3 = 0;
    __pyx_t_10 = 0;
    if (__Pyx_Print(0, __pyx_t_1, 1) < 0) __PYX_ERR(0, 140, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

    /* "ims_extractor.pyx":142
 *         print "|", str(len(datax)).ljust(8), "spectra analyzed at", resolution, "ppm accuracy        |"
 *         # print effct, float(effct)/float(len(datax))
 *         print "| Time spent(s):", "{:10.4f}".format(timex), "                         |"             # <<<<<<<<<<<<<<
 *         print "#----------------------------------------------------#"
 *         print "| Detecting features...                              |"
 */
    __pyx_t_10 = __Pyx_PyObject_GetAttrStr(__pyx_kp_s_10_4f, __pyx_n_s_format); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 142, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_10);
    __pyx_t_3 = NULL;
    if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_10))) {
      __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_10);
      if (likely(__pyx_t_3)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_10);
        __Pyx_INCREF(__pyx_t_3);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_10, function);
      }
    }
    if (!__pyx_t_3) {
      __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_10, __pyx_v_timex); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 142, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
    } else {
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_10)) {
        PyObject *__pyx_temp[2] = {__pyx_t_3, __pyx_v_timex};
        __pyx_t_1 = __Pyx_PyFunction_FastCall(__pyx_t_10, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 142, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
        __Pyx_GOTREF(__pyx_t_1);
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_10)) {
        PyObject *__pyx_temp[2] = {__pyx_t_3, __pyx_v_timex};
        __pyx_t_1 = __Pyx_PyCFunction_FastCall(__pyx_t_10, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 142, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
        __Pyx_GOTREF(__pyx_t_1);
      } else
      #endif
      {
        __pyx_t_17 = PyTuple_New(1+1); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 142, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_17);
        __Pyx_GIVEREF(__pyx_t_3); PyTuple_SET_ITEM(__pyx_t_17, 0, __pyx_t_3); __pyx_t_3 = NULL;
        __Pyx_INCREF(__pyx_v_timex);
        __Pyx_GIVEREF(__pyx_v_timex);
        PyTuple_SET_ITEM(__pyx_t_17, 0+1, __pyx_v_timex);
        __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_10, __pyx_t_17, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 142, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
      }
    }
    __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
    __pyx_t_10 = PyTuple_New(3); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 142, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_10);
    __Pyx_INCREF(__pyx_kp_s_Time_spent_s);
    __Pyx_GIVEREF(__pyx_kp_s_Time_spent_s);
    PyTuple_SET_ITEM(__pyx_t_10, 0, __pyx_kp_s_Time_spent_s);
    __Pyx_GIVEREF(__pyx_t_1);
    PyTuple_SET_ITEM(__pyx_t_10, 1, __pyx_t_1);
    __Pyx_INCREF(__pyx_kp_s__16);
    __Pyx_GIVEREF(__pyx_kp_s__16);
    PyTuple_SET_ITEM(__pyx_t_10, 2, __pyx_kp_s__16);
    __pyx_t_1 = 0;
    if (__Pyx_Print(0, __pyx_t_10, 1) < 0) __PYX_ERR(0, 142, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;

    /* "ims_extractor.pyx":143
 *         # print effct, float(effct)/float(len(datax))
 *         print "| Time spent(s):", "{:10.4f}".format(timex), "                         |"
 *         print "#----------------------------------------------------#"             # <<<<<<<<<<<<<<
 *         print "| Detecting features...                              |"
 * 
 */
    if (__Pyx_PrintOne(0, __pyx_kp_s__10) < 0) __PYX_ERR(0, 143, __pyx_L1_error)

    /* "ims_extractor.pyx":144
 *         print "| Time spent(s):", "{:10.4f}".format(timex), "                         |"
 *         print "#----------------------------------------------------#"
 *         print "| Detecting features...                              |"             # <<<<<<<<<<<<<<
 * 
 *         start1 = time.clock()
 */
    if (__Pyx_PrintOne(0, __pyx_kp_s_Detecting_features) < 0) __PYX_ERR(0, 144, __pyx_L1_error)

    /* "ims_extractor.pyx":146
 *         print "| Detecting features...                              |"
 * 
 *         start1 = time.clock()             # <<<<<<<<<<<<<<
 * 
 *         i = 0
 */
    __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_time); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 146, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_17 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_clock); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 146, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_17);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_1 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_17))) {
      __pyx_t_1 = PyMethod_GET_SELF(__pyx_t_17);
      if (likely(__pyx_t_1)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_17);
        __Pyx_INCREF(__pyx_t_1);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_17, function);
      }
    }
    if (__pyx_t_1) {
      __pyx_t_10 = __Pyx_PyObject_CallOneArg(__pyx_t_17, __pyx_t_1); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 146, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    } else {
      __pyx_t_10 = __Pyx_PyObject_CallNoArg(__pyx_t_17); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 146, __pyx_L1_error)
    }
    __Pyx_GOTREF(__pyx_t_10);
    __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
    __Pyx_DECREF_SET(__pyx_v_start1, __pyx_t_10);
    __pyx_t_10 = 0;

    /* "ims_extractor.pyx":148
 *         start1 = time.clock()
 * 
 *         i = 0             # <<<<<<<<<<<<<<
 *         a = {}
 *         b = []
 */
    __Pyx_INCREF(__pyx_int_0);
    __pyx_v_i = __pyx_int_0;

    /* "ims_extractor.pyx":149
 * 
 *         i = 0
 *         a = {}             # <<<<<<<<<<<<<<
 *         b = []
 *         valid_spec = []
 */
    __pyx_t_10 = PyDict_New(); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 149, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_10);
    __pyx_v_a = ((PyObject*)__pyx_t_10);
    __pyx_t_10 = 0;

    /* "ims_extractor.pyx":150
 *         i = 0
 *         a = {}
 *         b = []             # <<<<<<<<<<<<<<
 *         valid_spec = []
 *         sequential_spec = []
 */
    __pyx_t_10 = PyList_New(0); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 150, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_10);
    __pyx_v_b = ((PyObject*)__pyx_t_10);
    __pyx_t_10 = 0;

    /* "ims_extractor.pyx":151
 *         a = {}
 *         b = []
 *         valid_spec = []             # <<<<<<<<<<<<<<
 *         sequential_spec = []
 *         intensity_dict = {}
 */
    __pyx_t_10 = PyList_New(0); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 151, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_10);
    __pyx_v_valid_spec = ((PyObject*)__pyx_t_10);
    __pyx_t_10 = 0;

    /* "ims_extractor.pyx":152
 *         b = []
 *         valid_spec = []
 *         sequential_spec = []             # <<<<<<<<<<<<<<
 *         intensity_dict = {}
 * 
 */
    __pyx_t_10 = PyList_New(0); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 152, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_10);
    __pyx_v_sequential_spec = ((PyObject*)__pyx_t_10);
    __pyx_t_10 = 0;

    /* "ims_extractor.pyx":153
 *         valid_spec = []
 *         sequential_spec = []
 *         intensity_dict = {}             # <<<<<<<<<<<<<<
 * 
 *         while i < len(datax):  # write the whole array in ims format
 */
    __pyx_t_10 = PyDict_New(); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 153, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_10);
    __pyx_v_intensity_dict = ((PyObject*)__pyx_t_10);
    __pyx_t_10 = 0;

    /* "ims_extractor.pyx":155
 *         intensity_dict = {}
 * 
 *         while i < len(datax):  # write the whole array in ims format             # <<<<<<<<<<<<<<
 * 
 *             if len(datax[i]) >= 12:  # filter out all bins that contains little data, 66 means 22 points
 */
    while (1) {
      __pyx_t_7 = PyList_GET_SIZE(__pyx_v_datax); if (unlikely(__pyx_t_7 == -1)) __PYX_ERR(0, 155, __pyx_L1_error)
      __pyx_t_10 = PyInt_FromSsize_t(__pyx_t_7); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 155, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_10);
      __pyx_t_17 = PyObject_RichCompare(__pyx_v_i, __pyx_t_10, Py_LT); __Pyx_XGOTREF(__pyx_t_17); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 155, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
      __pyx_t_9 = __Pyx_PyObject_IsTrue(__pyx_t_17); if (unlikely(__pyx_t_9 < 0)) __PYX_ERR(0, 155, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
      if (!__pyx_t_9) break;

      /* "ims_extractor.pyx":157
 *         while i < len(datax):  # write the whole array in ims format
 * 
 *             if len(datax[i]) >= 12:  # filter out all bins that contains little data, 66 means 22 points             # <<<<<<<<<<<<<<
 *                 total = 0
 *                 count = 0
 */
      __pyx_t_17 = PyObject_GetItem(__pyx_v_datax, __pyx_v_i); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 157, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_17);
      __pyx_t_7 = PyObject_Length(__pyx_t_17); if (unlikely(__pyx_t_7 == -1)) __PYX_ERR(0, 157, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
      __pyx_t_9 = ((__pyx_t_7 >= 12) != 0);
      if (__pyx_t_9) {

        /* "ims_extractor.pyx":158
 * 
 *             if len(datax[i]) >= 12:  # filter out all bins that contains little data, 66 means 22 points
 *                 total = 0             # <<<<<<<<<<<<<<
 *                 count = 0
 *                 for myi in range(1, len(datax[i]), 3):  # range=1,4,7,10....len(datax[i])
 */
        __Pyx_INCREF(__pyx_int_0);
        __Pyx_XDECREF_SET(__pyx_v_total, __pyx_int_0);

        /* "ims_extractor.pyx":159
 *             if len(datax[i]) >= 12:  # filter out all bins that contains little data, 66 means 22 points
 *                 total = 0
 *                 count = 0             # <<<<<<<<<<<<<<
 *                 for myi in range(1, len(datax[i]), 3):  # range=1,4,7,10....len(datax[i])
 *                     total += int(datax[i][myi])
 */
        __Pyx_INCREF(__pyx_int_0);
        __Pyx_XDECREF_SET(__pyx_v_count, __pyx_int_0);

        /* "ims_extractor.pyx":160
 *                 total = 0
 *                 count = 0
 *                 for myi in range(1, len(datax[i]), 3):  # range=1,4,7,10....len(datax[i])             # <<<<<<<<<<<<<<
 *                     total += int(datax[i][myi])
 *                     count += 1
 */
        __pyx_t_17 = PyObject_GetItem(__pyx_v_datax, __pyx_v_i); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 160, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_17);
        __pyx_t_7 = PyObject_Length(__pyx_t_17); if (unlikely(__pyx_t_7 == -1)) __PYX_ERR(0, 160, __pyx_L1_error)
        __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
        for (__pyx_t_16 = 1; __pyx_t_16 < __pyx_t_7; __pyx_t_16+=3) {
          __pyx_v_myi = __pyx_t_16;

          /* "ims_extractor.pyx":161
 *                 count = 0
 *                 for myi in range(1, len(datax[i]), 3):  # range=1,4,7,10....len(datax[i])
 *                     total += int(datax[i][myi])             # <<<<<<<<<<<<<<
 *                     count += 1
 *                 # a.append([len(datax[i]), i, total/count])  # for frequency calculation
 */
          __pyx_t_17 = PyObject_GetItem(__pyx_v_datax, __pyx_v_i); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 161, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_17);
          __pyx_t_10 = __Pyx_GetItemInt(__pyx_t_17, __pyx_v_myi, Py_ssize_t, 1, PyInt_FromSsize_t, 0, 1, 1); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 161, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_10);
          __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
          __pyx_t_17 = __Pyx_PyNumber_Int(__pyx_t_10); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 161, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_17);
          __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
          __pyx_t_10 = PyNumber_InPlaceAdd(__pyx_v_total, __pyx_t_17); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 161, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_10);
          __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
          __Pyx_DECREF_SET(__pyx_v_total, __pyx_t_10);
          __pyx_t_10 = 0;

          /* "ims_extractor.pyx":162
 *                 for myi in range(1, len(datax[i]), 3):  # range=1,4,7,10....len(datax[i])
 *                     total += int(datax[i][myi])
 *                     count += 1             # <<<<<<<<<<<<<<
 *                 # a.append([len(datax[i]), i, total/count])  # for frequency calculation
 *                 tic += total
 */
          __pyx_t_10 = __Pyx_PyInt_AddObjC(__pyx_v_count, __pyx_int_1, 1, 1); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 162, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_10);
          __Pyx_DECREF_SET(__pyx_v_count, __pyx_t_10);
          __pyx_t_10 = 0;
        }

        /* "ims_extractor.pyx":164
 *                     count += 1
 *                 # a.append([len(datax[i]), i, total/count])  # for frequency calculation
 *                 tic += total             # <<<<<<<<<<<<<<
 *                 # print tic
 *                 valid_spec.append(i)
 */
        __pyx_t_10 = __Pyx_GetModuleGlobalName(__pyx_n_s_tic); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 164, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_10);
        __pyx_t_17 = PyNumber_InPlaceAdd(__pyx_t_10, __pyx_v_total); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 164, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_17);
        __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
        if (PyDict_SetItem(__pyx_d, __pyx_n_s_tic, __pyx_t_17) < 0) __PYX_ERR(0, 164, __pyx_L1_error)
        __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;

        /* "ims_extractor.pyx":166
 *                 tic += total
 *                 # print tic
 *                 valid_spec.append(i)             # <<<<<<<<<<<<<<
 *                 intensity_dict[i] = total
 *                 a[i] = count
 */
        __pyx_t_5 = __Pyx_PyList_Append(__pyx_v_valid_spec, __pyx_v_i); if (unlikely(__pyx_t_5 == -1)) __PYX_ERR(0, 166, __pyx_L1_error)

        /* "ims_extractor.pyx":167
 *                 # print tic
 *                 valid_spec.append(i)
 *                 intensity_dict[i] = total             # <<<<<<<<<<<<<<
 *                 a[i] = count
 *             i += 1
 */
        if (unlikely(PyDict_SetItem(__pyx_v_intensity_dict, __pyx_v_i, __pyx_v_total) < 0)) __PYX_ERR(0, 167, __pyx_L1_error)

        /* "ims_extractor.pyx":168
 *                 valid_spec.append(i)
 *                 intensity_dict[i] = total
 *                 a[i] = count             # <<<<<<<<<<<<<<
 *             i += 1
 *         # print max(valid_spec)
 */
        if (unlikely(PyDict_SetItem(__pyx_v_a, __pyx_v_i, __pyx_v_count) < 0)) __PYX_ERR(0, 168, __pyx_L1_error)

        /* "ims_extractor.pyx":157
 *         while i < len(datax):  # write the whole array in ims format
 * 
 *             if len(datax[i]) >= 12:  # filter out all bins that contains little data, 66 means 22 points             # <<<<<<<<<<<<<<
 *                 total = 0
 *                 count = 0
 */
      }

      /* "ims_extractor.pyx":169
 *                 intensity_dict[i] = total
 *                 a[i] = count
 *             i += 1             # <<<<<<<<<<<<<<
 *         # print max(valid_spec)
 * 
 */
      __pyx_t_17 = __Pyx_PyInt_AddObjC(__pyx_v_i, __pyx_int_1, 1, 1); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 169, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_17);
      __Pyx_DECREF_SET(__pyx_v_i, __pyx_t_17);
      __pyx_t_17 = 0;
    }

    /* "ims_extractor.pyx":176
 * #            sequential_spec.append([temp_m[0], len(temp_m)])
 * 
 *         lastvalue = -100             # <<<<<<<<<<<<<<
 *         last_idx = 1
 *         start_idx = 0
 */
    __Pyx_INCREF(__pyx_int_neg_100);
    __pyx_v_lastvalue = __pyx_int_neg_100;

    /* "ims_extractor.pyx":177
 * 
 *         lastvalue = -100
 *         last_idx = 1             # <<<<<<<<<<<<<<
 *         start_idx = 0
 * 
 */
    __Pyx_INCREF(__pyx_int_1);
    __pyx_v_last_idx = __pyx_int_1;

    /* "ims_extractor.pyx":178
 *         lastvalue = -100
 *         last_idx = 1
 *         start_idx = 0             # <<<<<<<<<<<<<<
 * 
 *         for idx, value in enumerate(valid_spec):
 */
    __Pyx_INCREF(__pyx_int_0);
    __pyx_v_start_idx = __pyx_int_0;

    /* "ims_extractor.pyx":180
 *         start_idx = 0
 * 
 *         for idx, value in enumerate(valid_spec):             # <<<<<<<<<<<<<<
 *             if value == lastvalue + 1:
 *                 last_idx += 1
 */
    __Pyx_INCREF(__pyx_int_0);
    __pyx_t_17 = __pyx_int_0;
    __pyx_t_10 = __pyx_v_valid_spec; __Pyx_INCREF(__pyx_t_10); __pyx_t_7 = 0;
    for (;;) {
      if (__pyx_t_7 >= PyList_GET_SIZE(__pyx_t_10)) break;
      #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
      __pyx_t_1 = PyList_GET_ITEM(__pyx_t_10, __pyx_t_7); __Pyx_INCREF(__pyx_t_1); __pyx_t_7++; if (unlikely(0 < 0)) __PYX_ERR(0, 180, __pyx_L1_error)
      #else
      __pyx_t_1 = PySequence_ITEM(__pyx_t_10, __pyx_t_7); __pyx_t_7++; if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 180, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      #endif
      __Pyx_XDECREF_SET(__pyx_v_value, __pyx_t_1);
      __pyx_t_1 = 0;
      __Pyx_INCREF(__pyx_t_17);
      __Pyx_XDECREF_SET(__pyx_v_idx, __pyx_t_17);
      __pyx_t_1 = __Pyx_PyInt_AddObjC(__pyx_t_17, __pyx_int_1, 1, 0); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 180, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_17);
      __pyx_t_17 = __pyx_t_1;
      __pyx_t_1 = 0;

      /* "ims_extractor.pyx":181
 * 
 *         for idx, value in enumerate(valid_spec):
 *             if value == lastvalue + 1:             # <<<<<<<<<<<<<<
 *                 last_idx += 1
 *             elif last_idx >= 1:
 */
      __pyx_t_1 = __Pyx_PyInt_AddObjC(__pyx_v_lastvalue, __pyx_int_1, 1, 0); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 181, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __pyx_t_3 = PyObject_RichCompare(__pyx_v_value, __pyx_t_1, Py_EQ); __Pyx_XGOTREF(__pyx_t_3); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 181, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      __pyx_t_9 = __Pyx_PyObject_IsTrue(__pyx_t_3); if (unlikely(__pyx_t_9 < 0)) __PYX_ERR(0, 181, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      if (__pyx_t_9) {

        /* "ims_extractor.pyx":182
 *         for idx, value in enumerate(valid_spec):
 *             if value == lastvalue + 1:
 *                 last_idx += 1             # <<<<<<<<<<<<<<
 *             elif last_idx >= 1:
 *                 sequential_spec.append((valid_spec[start_idx], last_idx))
 */
        __pyx_t_3 = __Pyx_PyInt_AddObjC(__pyx_v_last_idx, __pyx_int_1, 1, 1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 182, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __Pyx_DECREF_SET(__pyx_v_last_idx, __pyx_t_3);
        __pyx_t_3 = 0;

        /* "ims_extractor.pyx":181
 * 
 *         for idx, value in enumerate(valid_spec):
 *             if value == lastvalue + 1:             # <<<<<<<<<<<<<<
 *                 last_idx += 1
 *             elif last_idx >= 1:
 */
        goto __pyx_L40;
      }

      /* "ims_extractor.pyx":183
 *             if value == lastvalue + 1:
 *                 last_idx += 1
 *             elif last_idx >= 1:             # <<<<<<<<<<<<<<
 *                 sequential_spec.append((valid_spec[start_idx], last_idx))
 *                 start_idx = idx
 */
      __pyx_t_3 = PyObject_RichCompare(__pyx_v_last_idx, __pyx_int_1, Py_GE); __Pyx_XGOTREF(__pyx_t_3); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 183, __pyx_L1_error)
      __pyx_t_9 = __Pyx_PyObject_IsTrue(__pyx_t_3); if (unlikely(__pyx_t_9 < 0)) __PYX_ERR(0, 183, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      if (__pyx_t_9) {

        /* "ims_extractor.pyx":184
 *                 last_idx += 1
 *             elif last_idx >= 1:
 *                 sequential_spec.append((valid_spec[start_idx], last_idx))             # <<<<<<<<<<<<<<
 *                 start_idx = idx
 *                 last_idx = 1
 */
        __pyx_t_3 = PyObject_GetItem(__pyx_v_valid_spec, __pyx_v_start_idx); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 184, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __pyx_t_1 = PyTuple_New(2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 184, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        __Pyx_GIVEREF(__pyx_t_3);
        PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_t_3);
        __Pyx_INCREF(__pyx_v_last_idx);
        __Pyx_GIVEREF(__pyx_v_last_idx);
        PyTuple_SET_ITEM(__pyx_t_1, 1, __pyx_v_last_idx);
        __pyx_t_3 = 0;
        __pyx_t_5 = __Pyx_PyList_Append(__pyx_v_sequential_spec, __pyx_t_1); if (unlikely(__pyx_t_5 == -1)) __PYX_ERR(0, 184, __pyx_L1_error)
        __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

        /* "ims_extractor.pyx":185
 *             elif last_idx >= 1:
 *                 sequential_spec.append((valid_spec[start_idx], last_idx))
 *                 start_idx = idx             # <<<<<<<<<<<<<<
 *                 last_idx = 1
 *             else:
 */
        __Pyx_INCREF(__pyx_v_idx);
        __Pyx_DECREF_SET(__pyx_v_start_idx, __pyx_v_idx);

        /* "ims_extractor.pyx":186
 *                 sequential_spec.append((valid_spec[start_idx], last_idx))
 *                 start_idx = idx
 *                 last_idx = 1             # <<<<<<<<<<<<<<
 *             else:
 *                 start_idx = idx
 */
        __Pyx_INCREF(__pyx_int_1);
        __Pyx_DECREF_SET(__pyx_v_last_idx, __pyx_int_1);

        /* "ims_extractor.pyx":183
 *             if value == lastvalue + 1:
 *                 last_idx += 1
 *             elif last_idx >= 1:             # <<<<<<<<<<<<<<
 *                 sequential_spec.append((valid_spec[start_idx], last_idx))
 *                 start_idx = idx
 */
        goto __pyx_L40;
      }

      /* "ims_extractor.pyx":188
 *                 last_idx = 1
 *             else:
 *                 start_idx = idx             # <<<<<<<<<<<<<<
 *             lastvalue = value
 * 
 */
      /*else*/ {
        __Pyx_INCREF(__pyx_v_idx);
        __Pyx_DECREF_SET(__pyx_v_start_idx, __pyx_v_idx);
      }
      __pyx_L40:;

      /* "ims_extractor.pyx":189
 *             else:
 *                 start_idx = idx
 *             lastvalue = value             # <<<<<<<<<<<<<<
 * 
 *         print "| Feature detection finished.                        |"
 */
      __Pyx_INCREF(__pyx_v_value);
      __Pyx_DECREF_SET(__pyx_v_lastvalue, __pyx_v_value);

      /* "ims_extractor.pyx":180
 *         start_idx = 0
 * 
 *         for idx, value in enumerate(valid_spec):             # <<<<<<<<<<<<<<
 *             if value == lastvalue + 1:
 *                 last_idx += 1
 */
    }
    __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
    __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;

    /* "ims_extractor.pyx":191
 *             lastvalue = value
 * 
 *         print "| Feature detection finished.                        |"             # <<<<<<<<<<<<<<
 *         end = time.clock()
 *         timex = (end - start1)
 */
    if (__Pyx_PrintOne(0, __pyx_kp_s_Feature_detection_finished) < 0) __PYX_ERR(0, 191, __pyx_L1_error)

    /* "ims_extractor.pyx":192
 * 
 *         print "| Feature detection finished.                        |"
 *         end = time.clock()             # <<<<<<<<<<<<<<
 *         timex = (end - start1)
 *         print "| Time spent(s):", "{:10.4f}".format(timex), "                         |"
 */
    __pyx_t_10 = __Pyx_GetModuleGlobalName(__pyx_n_s_time); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 192, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_10);
    __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_t_10, __pyx_n_s_clock); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 192, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
    __pyx_t_10 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_1))) {
      __pyx_t_10 = PyMethod_GET_SELF(__pyx_t_1);
      if (likely(__pyx_t_10)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_1);
        __Pyx_INCREF(__pyx_t_10);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_1, function);
      }
    }
    if (__pyx_t_10) {
      __pyx_t_17 = __Pyx_PyObject_CallOneArg(__pyx_t_1, __pyx_t_10); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 192, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
    } else {
      __pyx_t_17 = __Pyx_PyObject_CallNoArg(__pyx_t_1); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 192, __pyx_L1_error)
    }
    __Pyx_GOTREF(__pyx_t_17);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __Pyx_DECREF_SET(__pyx_v_end, __pyx_t_17);
    __pyx_t_17 = 0;

    /* "ims_extractor.pyx":193
 *         print "| Feature detection finished.                        |"
 *         end = time.clock()
 *         timex = (end - start1)             # <<<<<<<<<<<<<<
 *         print "| Time spent(s):", "{:10.4f}".format(timex), "                         |"
 *         print "| Total features detected:", len(valid_spec), "                    |"
 */
    __pyx_t_17 = PyNumber_Subtract(__pyx_v_end, __pyx_v_start1); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 193, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_17);
    __Pyx_DECREF_SET(__pyx_v_timex, __pyx_t_17);
    __pyx_t_17 = 0;

    /* "ims_extractor.pyx":194
 *         end = time.clock()
 *         timex = (end - start1)
 *         print "| Time spent(s):", "{:10.4f}".format(timex), "                         |"             # <<<<<<<<<<<<<<
 *         print "| Total features detected:", len(valid_spec), "                    |"
 *         print "#----------------------------------------------------#"
 */
    __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_kp_s_10_4f, __pyx_n_s_format); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 194, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_10 = NULL;
    if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_1))) {
      __pyx_t_10 = PyMethod_GET_SELF(__pyx_t_1);
      if (likely(__pyx_t_10)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_1);
        __Pyx_INCREF(__pyx_t_10);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_1, function);
      }
    }
    if (!__pyx_t_10) {
      __pyx_t_17 = __Pyx_PyObject_CallOneArg(__pyx_t_1, __pyx_v_timex); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 194, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_17);
    } else {
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_1)) {
        PyObject *__pyx_temp[2] = {__pyx_t_10, __pyx_v_timex};
        __pyx_t_17 = __Pyx_PyFunction_FastCall(__pyx_t_1, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 194, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_10); __pyx_t_10 = 0;
        __Pyx_GOTREF(__pyx_t_17);
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_1)) {
        PyObject *__pyx_temp[2] = {__pyx_t_10, __pyx_v_timex};
        __pyx_t_17 = __Pyx_PyCFunction_FastCall(__pyx_t_1, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 194, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_10); __pyx_t_10 = 0;
        __Pyx_GOTREF(__pyx_t_17);
      } else
      #endif
      {
        __pyx_t_3 = PyTuple_New(1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 194, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __Pyx_GIVEREF(__pyx_t_10); PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_10); __pyx_t_10 = NULL;
        __Pyx_INCREF(__pyx_v_timex);
        __Pyx_GIVEREF(__pyx_v_timex);
        PyTuple_SET_ITEM(__pyx_t_3, 0+1, __pyx_v_timex);
        __pyx_t_17 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_3, NULL); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 194, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_17);
        __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      }
    }
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_1 = PyTuple_New(3); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 194, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_INCREF(__pyx_kp_s_Time_spent_s);
    __Pyx_GIVEREF(__pyx_kp_s_Time_spent_s);
    PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_kp_s_Time_spent_s);
    __Pyx_GIVEREF(__pyx_t_17);
    PyTuple_SET_ITEM(__pyx_t_1, 1, __pyx_t_17);
    __Pyx_INCREF(__pyx_kp_s__16);
    __Pyx_GIVEREF(__pyx_kp_s__16);
    PyTuple_SET_ITEM(__pyx_t_1, 2, __pyx_kp_s__16);
    __pyx_t_17 = 0;
    if (__Pyx_Print(0, __pyx_t_1, 1) < 0) __PYX_ERR(0, 194, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

    /* "ims_extractor.pyx":195
 *         timex = (end - start1)
 *         print "| Time spent(s):", "{:10.4f}".format(timex), "                         |"
 *         print "| Total features detected:", len(valid_spec), "                    |"             # <<<<<<<<<<<<<<
 *         print "#----------------------------------------------------#"
 *         print "| Combining features to spectra....                  |"
 */
    __pyx_t_7 = PyList_GET_SIZE(__pyx_v_valid_spec); if (unlikely(__pyx_t_7 == -1)) __PYX_ERR(0, 195, __pyx_L1_error)
    __pyx_t_1 = PyInt_FromSsize_t(__pyx_t_7); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 195, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_17 = PyTuple_New(3); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 195, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_17);
    __Pyx_INCREF(__pyx_kp_s_Total_features_detected);
    __Pyx_GIVEREF(__pyx_kp_s_Total_features_detected);
    PyTuple_SET_ITEM(__pyx_t_17, 0, __pyx_kp_s_Total_features_detected);
    __Pyx_GIVEREF(__pyx_t_1);
    PyTuple_SET_ITEM(__pyx_t_17, 1, __pyx_t_1);
    __Pyx_INCREF(__pyx_kp_s__20);
    __Pyx_GIVEREF(__pyx_kp_s__20);
    PyTuple_SET_ITEM(__pyx_t_17, 2, __pyx_kp_s__20);
    __pyx_t_1 = 0;
    if (__Pyx_Print(0, __pyx_t_17, 1) < 0) __PYX_ERR(0, 195, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;

    /* "ims_extractor.pyx":196
 *         print "| Time spent(s):", "{:10.4f}".format(timex), "                         |"
 *         print "| Total features detected:", len(valid_spec), "                    |"
 *         print "#----------------------------------------------------#"             # <<<<<<<<<<<<<<
 *         print "| Combining features to spectra....                  |"
 *         start1 = time.clock()
 */
    if (__Pyx_PrintOne(0, __pyx_kp_s__10) < 0) __PYX_ERR(0, 196, __pyx_L1_error)

    /* "ims_extractor.pyx":197
 *         print "| Total features detected:", len(valid_spec), "                    |"
 *         print "#----------------------------------------------------#"
 *         print "| Combining features to spectra....                  |"             # <<<<<<<<<<<<<<
 *         start1 = time.clock()
 * 
 */
    if (__Pyx_PrintOne(0, __pyx_kp_s_Combining_features_to_spectra) < 0) __PYX_ERR(0, 197, __pyx_L1_error)

    /* "ims_extractor.pyx":198
 *         print "#----------------------------------------------------#"
 *         print "| Combining features to spectra....                  |"
 *         start1 = time.clock()             # <<<<<<<<<<<<<<
 * 
 *         i = 0
 */
    __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_time); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 198, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_1, __pyx_n_s_clock); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 198, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_1 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_3))) {
      __pyx_t_1 = PyMethod_GET_SELF(__pyx_t_3);
      if (likely(__pyx_t_1)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
        __Pyx_INCREF(__pyx_t_1);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_3, function);
      }
    }
    if (__pyx_t_1) {
      __pyx_t_17 = __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_t_1); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 198, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    } else {
      __pyx_t_17 = __Pyx_PyObject_CallNoArg(__pyx_t_3); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 198, __pyx_L1_error)
    }
    __Pyx_GOTREF(__pyx_t_17);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __Pyx_DECREF_SET(__pyx_v_start1, __pyx_t_17);
    __pyx_t_17 = 0;

    /* "ims_extractor.pyx":200
 *         start1 = time.clock()
 * 
 *         i = 0             # <<<<<<<<<<<<<<
 *         # sequential_spec [ array of first sequential spectra, number of spectra]
 *         peak_count = []
 */
    __Pyx_INCREF(__pyx_int_0);
    __Pyx_DECREF_SET(__pyx_v_i, __pyx_int_0);

    /* "ims_extractor.pyx":202
 *         i = 0
 *         # sequential_spec [ array of first sequential spectra, number of spectra]
 *         peak_count = []             # <<<<<<<<<<<<<<
 *         mass_center = {}
 *         while i < len(sequential_spec):
 */
    __pyx_t_17 = PyList_New(0); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 202, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_17);
    __pyx_v_peak_count = ((PyObject*)__pyx_t_17);
    __pyx_t_17 = 0;

    /* "ims_extractor.pyx":203
 *         # sequential_spec [ array of first sequential spectra, number of spectra]
 *         peak_count = []
 *         mass_center = {}             # <<<<<<<<<<<<<<
 *         while i < len(sequential_spec):
 *             if sequential_spec[i][1] < max_drift:  # if spec number is less than the max_drift, combine them all
 */
    __pyx_t_17 = PyDict_New(); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 203, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_17);
    __pyx_v_mass_center = ((PyObject*)__pyx_t_17);
    __pyx_t_17 = 0;

    /* "ims_extractor.pyx":204
 *         peak_count = []
 *         mass_center = {}
 *         while i < len(sequential_spec):             # <<<<<<<<<<<<<<
 *             if sequential_spec[i][1] < max_drift:  # if spec number is less than the max_drift, combine them all
 *                 ii = 1
 */
    while (1) {
      __pyx_t_7 = PyList_GET_SIZE(__pyx_v_sequential_spec); if (unlikely(__pyx_t_7 == -1)) __PYX_ERR(0, 204, __pyx_L1_error)
      __pyx_t_17 = PyInt_FromSsize_t(__pyx_t_7); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 204, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_17);
      __pyx_t_3 = PyObject_RichCompare(__pyx_v_i, __pyx_t_17, Py_LT); __Pyx_XGOTREF(__pyx_t_3); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 204, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
      __pyx_t_9 = __Pyx_PyObject_IsTrue(__pyx_t_3); if (unlikely(__pyx_t_9 < 0)) __PYX_ERR(0, 204, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      if (!__pyx_t_9) break;

      /* "ims_extractor.pyx":205
 *         mass_center = {}
 *         while i < len(sequential_spec):
 *             if sequential_spec[i][1] < max_drift:  # if spec number is less than the max_drift, combine them all             # <<<<<<<<<<<<<<
 *                 ii = 1
 *                 while ii < sequential_spec[i][1]:
 */
      __pyx_t_3 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 205, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_17 = __Pyx_GetItemInt(__pyx_t_3, 1, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 205, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_17);
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __pyx_t_3 = __Pyx_GetModuleGlobalName(__pyx_n_s_max_drift); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 205, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_3);
      __pyx_t_1 = PyObject_RichCompare(__pyx_t_17, __pyx_t_3, Py_LT); __Pyx_XGOTREF(__pyx_t_1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 205, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      __pyx_t_9 = __Pyx_PyObject_IsTrue(__pyx_t_1); if (unlikely(__pyx_t_9 < 0)) __PYX_ERR(0, 205, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      if (__pyx_t_9) {

        /* "ims_extractor.pyx":206
 *         while i < len(sequential_spec):
 *             if sequential_spec[i][1] < max_drift:  # if spec number is less than the max_drift, combine them all
 *                 ii = 1             # <<<<<<<<<<<<<<
 *                 while ii < sequential_spec[i][1]:
 *                     datax[sequential_spec[i][0]] += datax[sequential_spec[i][0] + ii]
 */
        __Pyx_INCREF(__pyx_int_1);
        __Pyx_XDECREF_SET(__pyx_v_ii, __pyx_int_1);

        /* "ims_extractor.pyx":207
 *             if sequential_spec[i][1] < max_drift:  # if spec number is less than the max_drift, combine them all
 *                 ii = 1
 *                 while ii < sequential_spec[i][1]:             # <<<<<<<<<<<<<<
 *                     datax[sequential_spec[i][0]] += datax[sequential_spec[i][0] + ii]
 *                     valid_spec.remove(sequential_spec[i][0] + ii)
 */
        while (1) {
          __pyx_t_1 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 207, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_1);
          __pyx_t_3 = __Pyx_GetItemInt(__pyx_t_1, 1, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 207, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_3);
          __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
          __pyx_t_1 = PyObject_RichCompare(__pyx_v_ii, __pyx_t_3, Py_LT); __Pyx_XGOTREF(__pyx_t_1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 207, __pyx_L1_error)
          __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
          __pyx_t_9 = __Pyx_PyObject_IsTrue(__pyx_t_1); if (unlikely(__pyx_t_9 < 0)) __PYX_ERR(0, 207, __pyx_L1_error)
          __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
          if (!__pyx_t_9) break;

          /* "ims_extractor.pyx":208
 *                 ii = 1
 *                 while ii < sequential_spec[i][1]:
 *                     datax[sequential_spec[i][0]] += datax[sequential_spec[i][0] + ii]             # <<<<<<<<<<<<<<
 *                     valid_spec.remove(sequential_spec[i][0] + ii)
 *                     ii += 1
 */
          __pyx_t_1 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 208, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_1);
          __pyx_t_3 = __Pyx_GetItemInt(__pyx_t_1, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 208, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_3);
          __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
          __pyx_t_1 = PyObject_GetItem(__pyx_v_datax, __pyx_t_3); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 208, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_1);
          __pyx_t_17 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 208, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_17);
          __pyx_t_10 = __Pyx_GetItemInt(__pyx_t_17, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 208, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_10);
          __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
          __pyx_t_17 = PyNumber_Add(__pyx_t_10, __pyx_v_ii); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 208, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_17);
          __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
          __pyx_t_10 = PyObject_GetItem(__pyx_v_datax, __pyx_t_17); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 208, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_10);
          __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
          __pyx_t_17 = PyNumber_InPlaceAdd(__pyx_t_1, __pyx_t_10); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 208, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_17);
          __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
          __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
          if (unlikely(PyObject_SetItem(__pyx_v_datax, __pyx_t_3, __pyx_t_17) < 0)) __PYX_ERR(0, 208, __pyx_L1_error)
          __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
          __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

          /* "ims_extractor.pyx":209
 *                 while ii < sequential_spec[i][1]:
 *                     datax[sequential_spec[i][0]] += datax[sequential_spec[i][0] + ii]
 *                     valid_spec.remove(sequential_spec[i][0] + ii)             # <<<<<<<<<<<<<<
 *                     ii += 1
 *                 max_mass = datax[sequential_spec[i][0]][0]
 */
          __pyx_t_17 = __Pyx_PyObject_GetAttrStr(__pyx_v_valid_spec, __pyx_n_s_remove); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 209, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_17);
          __pyx_t_10 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 209, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_10);
          __pyx_t_1 = __Pyx_GetItemInt(__pyx_t_10, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 209, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_1);
          __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
          __pyx_t_10 = PyNumber_Add(__pyx_t_1, __pyx_v_ii); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 209, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_10);
          __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
          __pyx_t_1 = NULL;
          if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_17))) {
            __pyx_t_1 = PyMethod_GET_SELF(__pyx_t_17);
            if (likely(__pyx_t_1)) {
              PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_17);
              __Pyx_INCREF(__pyx_t_1);
              __Pyx_INCREF(function);
              __Pyx_DECREF_SET(__pyx_t_17, function);
            }
          }
          if (!__pyx_t_1) {
            __pyx_t_3 = __Pyx_PyObject_CallOneArg(__pyx_t_17, __pyx_t_10); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 209, __pyx_L1_error)
            __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
            __Pyx_GOTREF(__pyx_t_3);
          } else {
            #if CYTHON_FAST_PYCALL
            if (PyFunction_Check(__pyx_t_17)) {
              PyObject *__pyx_temp[2] = {__pyx_t_1, __pyx_t_10};
              __pyx_t_3 = __Pyx_PyFunction_FastCall(__pyx_t_17, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 209, __pyx_L1_error)
              __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;
              __Pyx_GOTREF(__pyx_t_3);
              __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
            } else
            #endif
            #if CYTHON_FAST_PYCCALL
            if (__Pyx_PyFastCFunction_Check(__pyx_t_17)) {
              PyObject *__pyx_temp[2] = {__pyx_t_1, __pyx_t_10};
              __pyx_t_3 = __Pyx_PyCFunction_FastCall(__pyx_t_17, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 209, __pyx_L1_error)
              __Pyx_XDECREF(__pyx_t_1); __pyx_t_1 = 0;
              __Pyx_GOTREF(__pyx_t_3);
              __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
            } else
            #endif
            {
              __pyx_t_6 = PyTuple_New(1+1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 209, __pyx_L1_error)
              __Pyx_GOTREF(__pyx_t_6);
              __Pyx_GIVEREF(__pyx_t_1); PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_1); __pyx_t_1 = NULL;
              __Pyx_GIVEREF(__pyx_t_10);
              PyTuple_SET_ITEM(__pyx_t_6, 0+1, __pyx_t_10);
              __pyx_t_10 = 0;
              __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_17, __pyx_t_6, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 209, __pyx_L1_error)
              __Pyx_GOTREF(__pyx_t_3);
              __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
            }
          }
          __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
          __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

          /* "ims_extractor.pyx":210
 *                     datax[sequential_spec[i][0]] += datax[sequential_spec[i][0] + ii]
 *                     valid_spec.remove(sequential_spec[i][0] + ii)
 *                     ii += 1             # <<<<<<<<<<<<<<
 *                 max_mass = datax[sequential_spec[i][0]][0]
 *                 # if 443.9<max_mass<444:
 */
          __pyx_t_3 = __Pyx_PyInt_AddObjC(__pyx_v_ii, __pyx_int_1, 1, 1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 210, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_3);
          __Pyx_DECREF_SET(__pyx_v_ii, __pyx_t_3);
          __pyx_t_3 = 0;
        }

        /* "ims_extractor.pyx":211
 *                     valid_spec.remove(sequential_spec[i][0] + ii)
 *                     ii += 1
 *                 max_mass = datax[sequential_spec[i][0]][0]             # <<<<<<<<<<<<<<
 *                 # if 443.9<max_mass<444:
 *                 # print datax[sequential_spec[i][0]]
 */
        __pyx_t_3 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 211, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __pyx_t_17 = __Pyx_GetItemInt(__pyx_t_3, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 211, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_17);
        __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
        __pyx_t_3 = PyObject_GetItem(__pyx_v_datax, __pyx_t_17); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 211, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
        __pyx_t_17 = __Pyx_GetItemInt(__pyx_t_3, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 211, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_17);
        __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
        __Pyx_XDECREF_SET(__pyx_v_max_mass, __pyx_t_17);
        __pyx_t_17 = 0;

        /* "ims_extractor.pyx":215
 *                 # print datax[sequential_spec[i][0]]
 * 
 *                 max_int = datax[sequential_spec[i][0]][1]             # <<<<<<<<<<<<<<
 * 
 *                 for int_max in range(1, len(datax[sequential_spec[i][0]]), 3):
 */
        __pyx_t_17 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 215, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_17);
        __pyx_t_3 = __Pyx_GetItemInt(__pyx_t_17, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 215, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
        __pyx_t_17 = PyObject_GetItem(__pyx_v_datax, __pyx_t_3); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 215, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_17);
        __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
        __pyx_t_3 = __Pyx_GetItemInt(__pyx_t_17, 1, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 215, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
        __Pyx_XDECREF_SET(__pyx_v_max_int, __pyx_t_3);
        __pyx_t_3 = 0;

        /* "ims_extractor.pyx":217
 *                 max_int = datax[sequential_spec[i][0]][1]
 * 
 *                 for int_max in range(1, len(datax[sequential_spec[i][0]]), 3):             # <<<<<<<<<<<<<<
 *                     intt = datax[sequential_spec[i][0]][int_max]
 *                     if intt > max_int:
 */
        __pyx_t_3 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 217, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __pyx_t_17 = __Pyx_GetItemInt(__pyx_t_3, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 217, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_17);
        __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
        __pyx_t_3 = PyObject_GetItem(__pyx_v_datax, __pyx_t_17); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 217, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
        __pyx_t_7 = PyObject_Length(__pyx_t_3); if (unlikely(__pyx_t_7 == -1)) __PYX_ERR(0, 217, __pyx_L1_error)
        __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
        __pyx_t_3 = PyInt_FromSsize_t(__pyx_t_7); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 217, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __pyx_t_17 = PyTuple_New(3); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 217, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_17);
        __Pyx_INCREF(__pyx_int_1);
        __Pyx_GIVEREF(__pyx_int_1);
        PyTuple_SET_ITEM(__pyx_t_17, 0, __pyx_int_1);
        __Pyx_GIVEREF(__pyx_t_3);
        PyTuple_SET_ITEM(__pyx_t_17, 1, __pyx_t_3);
        __Pyx_INCREF(__pyx_int_3);
        __Pyx_GIVEREF(__pyx_int_3);
        PyTuple_SET_ITEM(__pyx_t_17, 2, __pyx_int_3);
        __pyx_t_3 = 0;
        __pyx_t_3 = __Pyx_PyObject_Call(__pyx_builtin_range, __pyx_t_17, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 217, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
        if (likely(PyList_CheckExact(__pyx_t_3)) || PyTuple_CheckExact(__pyx_t_3)) {
          __pyx_t_17 = __pyx_t_3; __Pyx_INCREF(__pyx_t_17); __pyx_t_7 = 0;
          __pyx_t_8 = NULL;
        } else {
          __pyx_t_7 = -1; __pyx_t_17 = PyObject_GetIter(__pyx_t_3); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 217, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_17);
          __pyx_t_8 = Py_TYPE(__pyx_t_17)->tp_iternext; if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 217, __pyx_L1_error)
        }
        __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
        for (;;) {
          if (likely(!__pyx_t_8)) {
            if (likely(PyList_CheckExact(__pyx_t_17))) {
              if (__pyx_t_7 >= PyList_GET_SIZE(__pyx_t_17)) break;
              #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
              __pyx_t_3 = PyList_GET_ITEM(__pyx_t_17, __pyx_t_7); __Pyx_INCREF(__pyx_t_3); __pyx_t_7++; if (unlikely(0 < 0)) __PYX_ERR(0, 217, __pyx_L1_error)
              #else
              __pyx_t_3 = PySequence_ITEM(__pyx_t_17, __pyx_t_7); __pyx_t_7++; if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 217, __pyx_L1_error)
              __Pyx_GOTREF(__pyx_t_3);
              #endif
            } else {
              if (__pyx_t_7 >= PyTuple_GET_SIZE(__pyx_t_17)) break;
              #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
              __pyx_t_3 = PyTuple_GET_ITEM(__pyx_t_17, __pyx_t_7); __Pyx_INCREF(__pyx_t_3); __pyx_t_7++; if (unlikely(0 < 0)) __PYX_ERR(0, 217, __pyx_L1_error)
              #else
              __pyx_t_3 = PySequence_ITEM(__pyx_t_17, __pyx_t_7); __pyx_t_7++; if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 217, __pyx_L1_error)
              __Pyx_GOTREF(__pyx_t_3);
              #endif
            }
          } else {
            __pyx_t_3 = __pyx_t_8(__pyx_t_17);
            if (unlikely(!__pyx_t_3)) {
              PyObject* exc_type = PyErr_Occurred();
              if (exc_type) {
                if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
                else __PYX_ERR(0, 217, __pyx_L1_error)
              }
              break;
            }
            __Pyx_GOTREF(__pyx_t_3);
          }
          __Pyx_XDECREF_SET(__pyx_v_int_max, __pyx_t_3);
          __pyx_t_3 = 0;

          /* "ims_extractor.pyx":218
 * 
 *                 for int_max in range(1, len(datax[sequential_spec[i][0]]), 3):
 *                     intt = datax[sequential_spec[i][0]][int_max]             # <<<<<<<<<<<<<<
 *                     if intt > max_int:
 *                         max_int = intt
 */
          __pyx_t_3 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 218, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_3);
          __pyx_t_6 = __Pyx_GetItemInt(__pyx_t_3, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 218, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_6);
          __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
          __pyx_t_3 = PyObject_GetItem(__pyx_v_datax, __pyx_t_6); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 218, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_3);
          __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
          __pyx_t_6 = PyObject_GetItem(__pyx_t_3, __pyx_v_int_max); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 218, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_6);
          __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
          __Pyx_XDECREF_SET(__pyx_v_intt, __pyx_t_6);
          __pyx_t_6 = 0;

          /* "ims_extractor.pyx":219
 *                 for int_max in range(1, len(datax[sequential_spec[i][0]]), 3):
 *                     intt = datax[sequential_spec[i][0]][int_max]
 *                     if intt > max_int:             # <<<<<<<<<<<<<<
 *                         max_int = intt
 *                         max_mass = datax[sequential_spec[i][0]][int_max - 1]
 */
          __pyx_t_6 = PyObject_RichCompare(__pyx_v_intt, __pyx_v_max_int, Py_GT); __Pyx_XGOTREF(__pyx_t_6); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 219, __pyx_L1_error)
          __pyx_t_9 = __Pyx_PyObject_IsTrue(__pyx_t_6); if (unlikely(__pyx_t_9 < 0)) __PYX_ERR(0, 219, __pyx_L1_error)
          __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
          if (__pyx_t_9) {

            /* "ims_extractor.pyx":220
 *                     intt = datax[sequential_spec[i][0]][int_max]
 *                     if intt > max_int:
 *                         max_int = intt             # <<<<<<<<<<<<<<
 *                         max_mass = datax[sequential_spec[i][0]][int_max - 1]
 *                         # ret_ct=datax[sequential_spec[i][0]][int_max-2]
 */
            __Pyx_INCREF(__pyx_v_intt);
            __Pyx_DECREF_SET(__pyx_v_max_int, __pyx_v_intt);

            /* "ims_extractor.pyx":221
 *                     if intt > max_int:
 *                         max_int = intt
 *                         max_mass = datax[sequential_spec[i][0]][int_max - 1]             # <<<<<<<<<<<<<<
 *                         # ret_ct=datax[sequential_spec[i][0]][int_max-2]
 *                 # print datax[sequential_spec[i][0]], max_mass, max_int
 */
            __pyx_t_6 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 221, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_6);
            __pyx_t_3 = __Pyx_GetItemInt(__pyx_t_6, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 221, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_3);
            __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
            __pyx_t_6 = PyObject_GetItem(__pyx_v_datax, __pyx_t_3); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 221, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_6);
            __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
            __pyx_t_3 = __Pyx_PyInt_SubtractObjC(__pyx_v_int_max, __pyx_int_1, 1, 0); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 221, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_3);
            __pyx_t_10 = PyObject_GetItem(__pyx_t_6, __pyx_t_3); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 221, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_10);
            __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
            __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
            __Pyx_DECREF_SET(__pyx_v_max_mass, __pyx_t_10);
            __pyx_t_10 = 0;

            /* "ims_extractor.pyx":219
 *                 for int_max in range(1, len(datax[sequential_spec[i][0]]), 3):
 *                     intt = datax[sequential_spec[i][0]][int_max]
 *                     if intt > max_int:             # <<<<<<<<<<<<<<
 *                         max_int = intt
 *                         max_mass = datax[sequential_spec[i][0]][int_max - 1]
 */
          }

          /* "ims_extractor.pyx":217
 *                 max_int = datax[sequential_spec[i][0]][1]
 * 
 *                 for int_max in range(1, len(datax[sequential_spec[i][0]]), 3):             # <<<<<<<<<<<<<<
 *                     intt = datax[sequential_spec[i][0]][int_max]
 *                     if intt > max_int:
 */
        }
        __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;

        /* "ims_extractor.pyx":227
 *                 # if 443.9<max_mass<444:
 *                 #            print ret_ct
 *                 mass_center[sequential_spec[i][0]] = max_mass             # <<<<<<<<<<<<<<
 *             else:
 *                 ii = 0
 */
        __pyx_t_17 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 227, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_17);
        __pyx_t_10 = __Pyx_GetItemInt(__pyx_t_17, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 227, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_10);
        __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
        if (unlikely(PyDict_SetItem(__pyx_v_mass_center, __pyx_t_10, __pyx_v_max_mass) < 0)) __PYX_ERR(0, 227, __pyx_L1_error)
        __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;

        /* "ims_extractor.pyx":205
 *         mass_center = {}
 *         while i < len(sequential_spec):
 *             if sequential_spec[i][1] < max_drift:  # if spec number is less than the max_drift, combine them all             # <<<<<<<<<<<<<<
 *                 ii = 1
 *                 while ii < sequential_spec[i][1]:
 */
        goto __pyx_L43;
      }

      /* "ims_extractor.pyx":229
 *                 mass_center[sequential_spec[i][0]] = max_mass
 *             else:
 *                 ii = 0             # <<<<<<<<<<<<<<
 *                 temp_int = []
 *                 while ii < sequential_spec[i][1]:
 */
      /*else*/ {
        __Pyx_INCREF(__pyx_int_0);
        __Pyx_XDECREF_SET(__pyx_v_ii, __pyx_int_0);

        /* "ims_extractor.pyx":230
 *             else:
 *                 ii = 0
 *                 temp_int = []             # <<<<<<<<<<<<<<
 *                 while ii < sequential_spec[i][1]:
 *                     temp_int.append(intensity_dict[sequential_spec[i][0] + ii])
 */
        __pyx_t_10 = PyList_New(0); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 230, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_10);
        __Pyx_XDECREF_SET(__pyx_v_temp_int, ((PyObject*)__pyx_t_10));
        __pyx_t_10 = 0;

        /* "ims_extractor.pyx":231
 *                 ii = 0
 *                 temp_int = []
 *                 while ii < sequential_spec[i][1]:             # <<<<<<<<<<<<<<
 *                     temp_int.append(intensity_dict[sequential_spec[i][0] + ii])
 *                     ii += 1
 */
        while (1) {
          __pyx_t_10 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 231, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_10);
          __pyx_t_17 = __Pyx_GetItemInt(__pyx_t_10, 1, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 231, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_17);
          __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
          __pyx_t_10 = PyObject_RichCompare(__pyx_v_ii, __pyx_t_17, Py_LT); __Pyx_XGOTREF(__pyx_t_10); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 231, __pyx_L1_error)
          __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
          __pyx_t_9 = __Pyx_PyObject_IsTrue(__pyx_t_10); if (unlikely(__pyx_t_9 < 0)) __PYX_ERR(0, 231, __pyx_L1_error)
          __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
          if (!__pyx_t_9) break;

          /* "ims_extractor.pyx":232
 *                 temp_int = []
 *                 while ii < sequential_spec[i][1]:
 *                     temp_int.append(intensity_dict[sequential_spec[i][0] + ii])             # <<<<<<<<<<<<<<
 *                     ii += 1
 *                 temp_diff = map(sub, temp_int[1:len(temp_int)],
 */
          __pyx_t_10 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 232, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_10);
          __pyx_t_17 = __Pyx_GetItemInt(__pyx_t_10, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 232, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_17);
          __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
          __pyx_t_10 = PyNumber_Add(__pyx_t_17, __pyx_v_ii); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 232, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_10);
          __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
          __pyx_t_17 = __Pyx_PyDict_GetItem(__pyx_v_intensity_dict, __pyx_t_10); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 232, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_17);
          __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
          __pyx_t_5 = __Pyx_PyList_Append(__pyx_v_temp_int, __pyx_t_17); if (unlikely(__pyx_t_5 == -1)) __PYX_ERR(0, 232, __pyx_L1_error)
          __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;

          /* "ims_extractor.pyx":233
 *                 while ii < sequential_spec[i][1]:
 *                     temp_int.append(intensity_dict[sequential_spec[i][0] + ii])
 *                     ii += 1             # <<<<<<<<<<<<<<
 *                 temp_diff = map(sub, temp_int[1:len(temp_int)],
 *                                 temp_int[0:len(temp_int) - 1])  # calculate the first order difference of intensity list
 */
          __pyx_t_17 = __Pyx_PyInt_AddObjC(__pyx_v_ii, __pyx_int_1, 1, 1); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 233, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_17);
          __Pyx_DECREF_SET(__pyx_v_ii, __pyx_t_17);
          __pyx_t_17 = 0;
        }

        /* "ims_extractor.pyx":234
 *                     temp_int.append(intensity_dict[sequential_spec[i][0] + ii])
 *                     ii += 1
 *                 temp_diff = map(sub, temp_int[1:len(temp_int)],             # <<<<<<<<<<<<<<
 *                                 temp_int[0:len(temp_int) - 1])  # calculate the first order difference of intensity list
 *                 ii = 1
 */
        __pyx_t_17 = __Pyx_GetModuleGlobalName(__pyx_n_s_sub); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 234, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_17);
        __pyx_t_7 = PyList_GET_SIZE(__pyx_v_temp_int); if (unlikely(__pyx_t_7 == -1)) __PYX_ERR(0, 234, __pyx_L1_error)
        __pyx_t_10 = __Pyx_PyList_GetSlice(__pyx_v_temp_int, 1, __pyx_t_7); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 234, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_10);

        /* "ims_extractor.pyx":235
 *                     ii += 1
 *                 temp_diff = map(sub, temp_int[1:len(temp_int)],
 *                                 temp_int[0:len(temp_int) - 1])  # calculate the first order difference of intensity list             # <<<<<<<<<<<<<<
 *                 ii = 1
 *                 peak_pos = []
 */
        __pyx_t_7 = PyList_GET_SIZE(__pyx_v_temp_int); if (unlikely(__pyx_t_7 == -1)) __PYX_ERR(0, 235, __pyx_L1_error)
        __pyx_t_3 = __Pyx_PyList_GetSlice(__pyx_v_temp_int, 0, (__pyx_t_7 - 1)); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 235, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);

        /* "ims_extractor.pyx":234
 *                     temp_int.append(intensity_dict[sequential_spec[i][0] + ii])
 *                     ii += 1
 *                 temp_diff = map(sub, temp_int[1:len(temp_int)],             # <<<<<<<<<<<<<<
 *                                 temp_int[0:len(temp_int) - 1])  # calculate the first order difference of intensity list
 *                 ii = 1
 */
        __pyx_t_6 = PyTuple_New(3); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 234, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_6);
        __Pyx_GIVEREF(__pyx_t_17);
        PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_17);
        __Pyx_GIVEREF(__pyx_t_10);
        PyTuple_SET_ITEM(__pyx_t_6, 1, __pyx_t_10);
        __Pyx_GIVEREF(__pyx_t_3);
        PyTuple_SET_ITEM(__pyx_t_6, 2, __pyx_t_3);
        __pyx_t_17 = 0;
        __pyx_t_10 = 0;
        __pyx_t_3 = 0;
        __pyx_t_3 = __Pyx_PyObject_Call(__pyx_builtin_map, __pyx_t_6, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 234, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
        __Pyx_XDECREF_SET(__pyx_v_temp_diff, __pyx_t_3);
        __pyx_t_3 = 0;

        /* "ims_extractor.pyx":236
 *                 temp_diff = map(sub, temp_int[1:len(temp_int)],
 *                                 temp_int[0:len(temp_int) - 1])  # calculate the first order difference of intensity list
 *                 ii = 1             # <<<<<<<<<<<<<<
 *                 peak_pos = []
 *                 temp_peak_count = 0
 */
        __Pyx_INCREF(__pyx_int_1);
        __Pyx_DECREF_SET(__pyx_v_ii, __pyx_int_1);

        /* "ims_extractor.pyx":237
 *                                 temp_int[0:len(temp_int) - 1])  # calculate the first order difference of intensity list
 *                 ii = 1
 *                 peak_pos = []             # <<<<<<<<<<<<<<
 *                 temp_peak_count = 0
 *                 while ii < len(temp_diff):
 */
        __pyx_t_3 = PyList_New(0); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 237, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __Pyx_XDECREF_SET(__pyx_v_peak_pos, ((PyObject*)__pyx_t_3));
        __pyx_t_3 = 0;

        /* "ims_extractor.pyx":238
 *                 ii = 1
 *                 peak_pos = []
 *                 temp_peak_count = 0             # <<<<<<<<<<<<<<
 *                 while ii < len(temp_diff):
 *                     if temp_diff[ii - 1] >= 0 > temp_diff[ii]:  # detect all peaks
 */
        __Pyx_INCREF(__pyx_int_0);
        __Pyx_XDECREF_SET(__pyx_v_temp_peak_count, __pyx_int_0);

        /* "ims_extractor.pyx":239
 *                 peak_pos = []
 *                 temp_peak_count = 0
 *                 while ii < len(temp_diff):             # <<<<<<<<<<<<<<
 *                     if temp_diff[ii - 1] >= 0 > temp_diff[ii]:  # detect all peaks
 *                         temp_peak_count += 1
 */
        while (1) {
          __pyx_t_7 = PyObject_Length(__pyx_v_temp_diff); if (unlikely(__pyx_t_7 == -1)) __PYX_ERR(0, 239, __pyx_L1_error)
          __pyx_t_3 = PyInt_FromSsize_t(__pyx_t_7); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 239, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_3);
          __pyx_t_6 = PyObject_RichCompare(__pyx_v_ii, __pyx_t_3, Py_LT); __Pyx_XGOTREF(__pyx_t_6); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 239, __pyx_L1_error)
          __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
          __pyx_t_9 = __Pyx_PyObject_IsTrue(__pyx_t_6); if (unlikely(__pyx_t_9 < 0)) __PYX_ERR(0, 239, __pyx_L1_error)
          __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
          if (!__pyx_t_9) break;

          /* "ims_extractor.pyx":240
 *                 temp_peak_count = 0
 *                 while ii < len(temp_diff):
 *                     if temp_diff[ii - 1] >= 0 > temp_diff[ii]:  # detect all peaks             # <<<<<<<<<<<<<<
 *                         temp_peak_count += 1
 *                         peak_pos.append(ii)
 */
          __pyx_t_6 = __Pyx_PyInt_SubtractObjC(__pyx_v_ii, __pyx_int_1, 1, 0); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 240, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_6);
          __pyx_t_3 = PyObject_GetItem(__pyx_v_temp_diff, __pyx_t_6); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 240, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_3);
          __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
          __pyx_t_6 = PyObject_RichCompare(__pyx_t_3, __pyx_int_0, Py_GE); __Pyx_XGOTREF(__pyx_t_6); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 240, __pyx_L1_error)
          if (__Pyx_PyObject_IsTrue(__pyx_t_6)) {
            __Pyx_DECREF(__pyx_t_6);
            __pyx_t_10 = PyObject_GetItem(__pyx_v_temp_diff, __pyx_v_ii); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 240, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_10);
            __pyx_t_6 = PyObject_RichCompare(__pyx_int_0, __pyx_t_10, Py_GT); __Pyx_XGOTREF(__pyx_t_6); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 240, __pyx_L1_error)
            __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
          }
          __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
          __pyx_t_9 = __Pyx_PyObject_IsTrue(__pyx_t_6); if (unlikely(__pyx_t_9 < 0)) __PYX_ERR(0, 240, __pyx_L1_error)
          __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
          if (__pyx_t_9) {

            /* "ims_extractor.pyx":241
 *                 while ii < len(temp_diff):
 *                     if temp_diff[ii - 1] >= 0 > temp_diff[ii]:  # detect all peaks
 *                         temp_peak_count += 1             # <<<<<<<<<<<<<<
 *                         peak_pos.append(ii)
 *                     ii += 1
 */
            __pyx_t_6 = __Pyx_PyInt_AddObjC(__pyx_v_temp_peak_count, __pyx_int_1, 1, 1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 241, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_6);
            __Pyx_DECREF_SET(__pyx_v_temp_peak_count, __pyx_t_6);
            __pyx_t_6 = 0;

            /* "ims_extractor.pyx":242
 *                     if temp_diff[ii - 1] >= 0 > temp_diff[ii]:  # detect all peaks
 *                         temp_peak_count += 1
 *                         peak_pos.append(ii)             # <<<<<<<<<<<<<<
 *                     ii += 1
 *                 if temp_peak_count <= 1:
 */
            __pyx_t_5 = __Pyx_PyList_Append(__pyx_v_peak_pos, __pyx_v_ii); if (unlikely(__pyx_t_5 == -1)) __PYX_ERR(0, 242, __pyx_L1_error)

            /* "ims_extractor.pyx":240
 *                 temp_peak_count = 0
 *                 while ii < len(temp_diff):
 *                     if temp_diff[ii - 1] >= 0 > temp_diff[ii]:  # detect all peaks             # <<<<<<<<<<<<<<
 *                         temp_peak_count += 1
 *                         peak_pos.append(ii)
 */
          }

          /* "ims_extractor.pyx":243
 *                         temp_peak_count += 1
 *                         peak_pos.append(ii)
 *                     ii += 1             # <<<<<<<<<<<<<<
 *                 if temp_peak_count <= 1:
 *                     iii = 1
 */
          __pyx_t_6 = __Pyx_PyInt_AddObjC(__pyx_v_ii, __pyx_int_1, 1, 1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 243, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_6);
          __Pyx_DECREF_SET(__pyx_v_ii, __pyx_t_6);
          __pyx_t_6 = 0;
        }

        /* "ims_extractor.pyx":244
 *                         peak_pos.append(ii)
 *                     ii += 1
 *                 if temp_peak_count <= 1:             # <<<<<<<<<<<<<<
 *                     iii = 1
 *                     mass_center[sequential_spec[i][0]] = datax[sequential_spec[i][0] + peak_pos[0]][0]
 */
        __pyx_t_6 = PyObject_RichCompare(__pyx_v_temp_peak_count, __pyx_int_1, Py_LE); __Pyx_XGOTREF(__pyx_t_6); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 244, __pyx_L1_error)
        __pyx_t_9 = __Pyx_PyObject_IsTrue(__pyx_t_6); if (unlikely(__pyx_t_9 < 0)) __PYX_ERR(0, 244, __pyx_L1_error)
        __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
        if (__pyx_t_9) {

          /* "ims_extractor.pyx":245
 *                     ii += 1
 *                 if temp_peak_count <= 1:
 *                     iii = 1             # <<<<<<<<<<<<<<
 *                     mass_center[sequential_spec[i][0]] = datax[sequential_spec[i][0] + peak_pos[0]][0]
 *                     # print mass_center[sequential_spec[i][0]]
 */
          __Pyx_INCREF(__pyx_int_1);
          __Pyx_XDECREF_SET(__pyx_v_iii, __pyx_int_1);

          /* "ims_extractor.pyx":246
 *                 if temp_peak_count <= 1:
 *                     iii = 1
 *                     mass_center[sequential_spec[i][0]] = datax[sequential_spec[i][0] + peak_pos[0]][0]             # <<<<<<<<<<<<<<
 *                     # print mass_center[sequential_spec[i][0]]
 *                     while iii < sequential_spec[i][1]:  # in case there is only 1 peak, combine them all
 */
          __pyx_t_6 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 246, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_6);
          __pyx_t_3 = __Pyx_GetItemInt(__pyx_t_6, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 246, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_3);
          __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
          __pyx_t_6 = __Pyx_GetItemInt_List(__pyx_v_peak_pos, 0, long, 1, __Pyx_PyInt_From_long, 1, 0, 1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 246, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_6);
          __pyx_t_10 = PyNumber_Add(__pyx_t_3, __pyx_t_6); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 246, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_10);
          __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
          __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
          __pyx_t_6 = PyObject_GetItem(__pyx_v_datax, __pyx_t_10); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 246, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_6);
          __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
          __pyx_t_10 = __Pyx_GetItemInt(__pyx_t_6, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 246, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_10);
          __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
          __pyx_t_6 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 246, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_6);
          __pyx_t_3 = __Pyx_GetItemInt(__pyx_t_6, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 246, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_3);
          __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
          if (unlikely(PyDict_SetItem(__pyx_v_mass_center, __pyx_t_3, __pyx_t_10) < 0)) __PYX_ERR(0, 246, __pyx_L1_error)
          __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
          __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;

          /* "ims_extractor.pyx":248
 *                     mass_center[sequential_spec[i][0]] = datax[sequential_spec[i][0] + peak_pos[0]][0]
 *                     # print mass_center[sequential_spec[i][0]]
 *                     while iii < sequential_spec[i][1]:  # in case there is only 1 peak, combine them all             # <<<<<<<<<<<<<<
 *                         datax[sequential_spec[i][0]] += datax[sequential_spec[i][0] + iii]
 *                         valid_spec.remove(sequential_spec[i][0] + iii)
 */
          while (1) {
            __pyx_t_10 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 248, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_10);
            __pyx_t_3 = __Pyx_GetItemInt(__pyx_t_10, 1, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 248, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_3);
            __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
            __pyx_t_10 = PyObject_RichCompare(__pyx_v_iii, __pyx_t_3, Py_LT); __Pyx_XGOTREF(__pyx_t_10); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 248, __pyx_L1_error)
            __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
            __pyx_t_9 = __Pyx_PyObject_IsTrue(__pyx_t_10); if (unlikely(__pyx_t_9 < 0)) __PYX_ERR(0, 248, __pyx_L1_error)
            __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
            if (!__pyx_t_9) break;

            /* "ims_extractor.pyx":249
 *                     # print mass_center[sequential_spec[i][0]]
 *                     while iii < sequential_spec[i][1]:  # in case there is only 1 peak, combine them all
 *                         datax[sequential_spec[i][0]] += datax[sequential_spec[i][0] + iii]             # <<<<<<<<<<<<<<
 *                         valid_spec.remove(sequential_spec[i][0] + iii)
 *                         intensity_dict[sequential_spec[i][0]] += intensity_dict[sequential_spec[i][0] + iii]
 */
            __pyx_t_10 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 249, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_10);
            __pyx_t_3 = __Pyx_GetItemInt(__pyx_t_10, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 249, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_3);
            __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
            __pyx_t_10 = PyObject_GetItem(__pyx_v_datax, __pyx_t_3); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 249, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_10);
            __pyx_t_6 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 249, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_6);
            __pyx_t_17 = __Pyx_GetItemInt(__pyx_t_6, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 249, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_17);
            __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
            __pyx_t_6 = PyNumber_Add(__pyx_t_17, __pyx_v_iii); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 249, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_6);
            __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
            __pyx_t_17 = PyObject_GetItem(__pyx_v_datax, __pyx_t_6); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 249, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_17);
            __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
            __pyx_t_6 = PyNumber_InPlaceAdd(__pyx_t_10, __pyx_t_17); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 249, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_6);
            __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
            __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
            if (unlikely(PyObject_SetItem(__pyx_v_datax, __pyx_t_3, __pyx_t_6) < 0)) __PYX_ERR(0, 249, __pyx_L1_error)
            __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
            __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

            /* "ims_extractor.pyx":250
 *                     while iii < sequential_spec[i][1]:  # in case there is only 1 peak, combine them all
 *                         datax[sequential_spec[i][0]] += datax[sequential_spec[i][0] + iii]
 *                         valid_spec.remove(sequential_spec[i][0] + iii)             # <<<<<<<<<<<<<<
 *                         intensity_dict[sequential_spec[i][0]] += intensity_dict[sequential_spec[i][0] + iii]
 *                         iii += 1
 */
            __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_v_valid_spec, __pyx_n_s_remove); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 250, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_6);
            __pyx_t_17 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 250, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_17);
            __pyx_t_10 = __Pyx_GetItemInt(__pyx_t_17, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 250, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_10);
            __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
            __pyx_t_17 = PyNumber_Add(__pyx_t_10, __pyx_v_iii); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 250, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_17);
            __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
            __pyx_t_10 = NULL;
            if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_6))) {
              __pyx_t_10 = PyMethod_GET_SELF(__pyx_t_6);
              if (likely(__pyx_t_10)) {
                PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_6);
                __Pyx_INCREF(__pyx_t_10);
                __Pyx_INCREF(function);
                __Pyx_DECREF_SET(__pyx_t_6, function);
              }
            }
            if (!__pyx_t_10) {
              __pyx_t_3 = __Pyx_PyObject_CallOneArg(__pyx_t_6, __pyx_t_17); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 250, __pyx_L1_error)
              __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
              __Pyx_GOTREF(__pyx_t_3);
            } else {
              #if CYTHON_FAST_PYCALL
              if (PyFunction_Check(__pyx_t_6)) {
                PyObject *__pyx_temp[2] = {__pyx_t_10, __pyx_t_17};
                __pyx_t_3 = __Pyx_PyFunction_FastCall(__pyx_t_6, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 250, __pyx_L1_error)
                __Pyx_XDECREF(__pyx_t_10); __pyx_t_10 = 0;
                __Pyx_GOTREF(__pyx_t_3);
                __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
              } else
              #endif
              #if CYTHON_FAST_PYCCALL
              if (__Pyx_PyFastCFunction_Check(__pyx_t_6)) {
                PyObject *__pyx_temp[2] = {__pyx_t_10, __pyx_t_17};
                __pyx_t_3 = __Pyx_PyCFunction_FastCall(__pyx_t_6, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 250, __pyx_L1_error)
                __Pyx_XDECREF(__pyx_t_10); __pyx_t_10 = 0;
                __Pyx_GOTREF(__pyx_t_3);
                __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
              } else
              #endif
              {
                __pyx_t_1 = PyTuple_New(1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 250, __pyx_L1_error)
                __Pyx_GOTREF(__pyx_t_1);
                __Pyx_GIVEREF(__pyx_t_10); PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_t_10); __pyx_t_10 = NULL;
                __Pyx_GIVEREF(__pyx_t_17);
                PyTuple_SET_ITEM(__pyx_t_1, 0+1, __pyx_t_17);
                __pyx_t_17 = 0;
                __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_6, __pyx_t_1, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 250, __pyx_L1_error)
                __Pyx_GOTREF(__pyx_t_3);
                __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
              }
            }
            __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
            __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

            /* "ims_extractor.pyx":251
 *                         datax[sequential_spec[i][0]] += datax[sequential_spec[i][0] + iii]
 *                         valid_spec.remove(sequential_spec[i][0] + iii)
 *                         intensity_dict[sequential_spec[i][0]] += intensity_dict[sequential_spec[i][0] + iii]             # <<<<<<<<<<<<<<
 *                         iii += 1
 *                 else:
 */
            __pyx_t_3 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 251, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_3);
            __pyx_t_6 = __Pyx_GetItemInt(__pyx_t_3, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 251, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_6);
            __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
            __pyx_t_3 = __Pyx_PyDict_GetItem(__pyx_v_intensity_dict, __pyx_t_6); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 251, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_3);
            __pyx_t_1 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 251, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_1);
            __pyx_t_17 = __Pyx_GetItemInt(__pyx_t_1, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 251, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_17);
            __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
            __pyx_t_1 = PyNumber_Add(__pyx_t_17, __pyx_v_iii); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 251, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_1);
            __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
            __pyx_t_17 = __Pyx_PyDict_GetItem(__pyx_v_intensity_dict, __pyx_t_1); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 251, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_17);
            __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
            __pyx_t_1 = PyNumber_InPlaceAdd(__pyx_t_3, __pyx_t_17); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 251, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_1);
            __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
            __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
            if (unlikely(PyDict_SetItem(__pyx_v_intensity_dict, __pyx_t_6, __pyx_t_1) < 0)) __PYX_ERR(0, 251, __pyx_L1_error)
            __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
            __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;

            /* "ims_extractor.pyx":252
 *                         valid_spec.remove(sequential_spec[i][0] + iii)
 *                         intensity_dict[sequential_spec[i][0]] += intensity_dict[sequential_spec[i][0] + iii]
 *                         iii += 1             # <<<<<<<<<<<<<<
 *                 else:
 *                     ii = 1
 */
            __pyx_t_6 = __Pyx_PyInt_AddObjC(__pyx_v_iii, __pyx_int_1, 1, 1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 252, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_6);
            __Pyx_DECREF_SET(__pyx_v_iii, __pyx_t_6);
            __pyx_t_6 = 0;
          }

          /* "ims_extractor.pyx":244
 *                         peak_pos.append(ii)
 *                     ii += 1
 *                 if temp_peak_count <= 1:             # <<<<<<<<<<<<<<
 *                     iii = 1
 *                     mass_center[sequential_spec[i][0]] = datax[sequential_spec[i][0] + peak_pos[0]][0]
 */
          goto __pyx_L54;
        }

        /* "ims_extractor.pyx":254
 *                         iii += 1
 *                 else:
 *                     ii = 1             # <<<<<<<<<<<<<<
 *                     num_of_valley = 1
 *                     while num_of_valley < temp_peak_count:
 */
        /*else*/ {
          __Pyx_INCREF(__pyx_int_1);
          __Pyx_DECREF_SET(__pyx_v_ii, __pyx_int_1);

          /* "ims_extractor.pyx":255
 *                 else:
 *                     ii = 1
 *                     num_of_valley = 1             # <<<<<<<<<<<<<<
 *                     while num_of_valley < temp_peak_count:
 *                         iii = peak_pos[num_of_valley - 1]
 */
          __Pyx_INCREF(__pyx_int_1);
          __Pyx_XDECREF_SET(__pyx_v_num_of_valley, __pyx_int_1);

          /* "ims_extractor.pyx":256
 *                     ii = 1
 *                     num_of_valley = 1
 *                     while num_of_valley < temp_peak_count:             # <<<<<<<<<<<<<<
 *                         iii = peak_pos[num_of_valley - 1]
 *                         while not (temp_diff[iii - 1] <= 0 < temp_diff[iii]):
 */
          while (1) {
            __pyx_t_6 = PyObject_RichCompare(__pyx_v_num_of_valley, __pyx_v_temp_peak_count, Py_LT); __Pyx_XGOTREF(__pyx_t_6); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 256, __pyx_L1_error)
            __pyx_t_9 = __Pyx_PyObject_IsTrue(__pyx_t_6); if (unlikely(__pyx_t_9 < 0)) __PYX_ERR(0, 256, __pyx_L1_error)
            __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
            if (!__pyx_t_9) break;

            /* "ims_extractor.pyx":257
 *                     num_of_valley = 1
 *                     while num_of_valley < temp_peak_count:
 *                         iii = peak_pos[num_of_valley - 1]             # <<<<<<<<<<<<<<
 *                         while not (temp_diff[iii - 1] <= 0 < temp_diff[iii]):
 *                             # find the first valley after first peak
 */
            __pyx_t_6 = __Pyx_PyInt_SubtractObjC(__pyx_v_num_of_valley, __pyx_int_1, 1, 0); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 257, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_6);
            __pyx_t_1 = PyObject_GetItem(__pyx_v_peak_pos, __pyx_t_6); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 257, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_1);
            __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
            __Pyx_XDECREF_SET(__pyx_v_iii, __pyx_t_1);
            __pyx_t_1 = 0;

            /* "ims_extractor.pyx":258
 *                     while num_of_valley < temp_peak_count:
 *                         iii = peak_pos[num_of_valley - 1]
 *                         while not (temp_diff[iii - 1] <= 0 < temp_diff[iii]):             # <<<<<<<<<<<<<<
 *                             # find the first valley after first peak
 *                             iii += 1
 */
            while (1) {
              __pyx_t_1 = __Pyx_PyInt_SubtractObjC(__pyx_v_iii, __pyx_int_1, 1, 0); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 258, __pyx_L1_error)
              __Pyx_GOTREF(__pyx_t_1);
              __pyx_t_6 = PyObject_GetItem(__pyx_v_temp_diff, __pyx_t_1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 258, __pyx_L1_error)
              __Pyx_GOTREF(__pyx_t_6);
              __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
              __pyx_t_1 = PyObject_RichCompare(__pyx_t_6, __pyx_int_0, Py_LE); __Pyx_XGOTREF(__pyx_t_1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 258, __pyx_L1_error)
              if (__Pyx_PyObject_IsTrue(__pyx_t_1)) {
                __Pyx_DECREF(__pyx_t_1);
                __pyx_t_17 = PyObject_GetItem(__pyx_v_temp_diff, __pyx_v_iii); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 258, __pyx_L1_error)
                __Pyx_GOTREF(__pyx_t_17);
                __pyx_t_1 = PyObject_RichCompare(__pyx_int_0, __pyx_t_17, Py_LT); __Pyx_XGOTREF(__pyx_t_1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 258, __pyx_L1_error)
                __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
              }
              __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
              __pyx_t_9 = __Pyx_PyObject_IsTrue(__pyx_t_1); if (unlikely(__pyx_t_9 < 0)) __PYX_ERR(0, 258, __pyx_L1_error)
              __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
              __pyx_t_4 = ((!__pyx_t_9) != 0);
              if (!__pyx_t_4) break;

              /* "ims_extractor.pyx":260
 *                         while not (temp_diff[iii - 1] <= 0 < temp_diff[iii]):
 *                             # find the first valley after first peak
 *                             iii += 1             # <<<<<<<<<<<<<<
 *                         mass_center[sequential_spec[i][0]] = datax[sequential_spec[i][0] + peak_pos[num_of_valley]][0]
 *                         # print mass_center[sequential_spec[i][0]]
 */
              __pyx_t_1 = __Pyx_PyInt_AddObjC(__pyx_v_iii, __pyx_int_1, 1, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 260, __pyx_L1_error)
              __Pyx_GOTREF(__pyx_t_1);
              __Pyx_DECREF_SET(__pyx_v_iii, __pyx_t_1);
              __pyx_t_1 = 0;
            }

            /* "ims_extractor.pyx":261
 *                             # find the first valley after first peak
 *                             iii += 1
 *                         mass_center[sequential_spec[i][0]] = datax[sequential_spec[i][0] + peak_pos[num_of_valley]][0]             # <<<<<<<<<<<<<<
 *                         # print mass_center[sequential_spec[i][0]]
 *                         while ii < iii:  # Combine everything before the first valley
 */
            __pyx_t_1 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 261, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_1);
            __pyx_t_6 = __Pyx_GetItemInt(__pyx_t_1, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 261, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_6);
            __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
            __pyx_t_1 = PyObject_GetItem(__pyx_v_peak_pos, __pyx_v_num_of_valley); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 261, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_1);
            __pyx_t_17 = PyNumber_Add(__pyx_t_6, __pyx_t_1); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 261, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_17);
            __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
            __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
            __pyx_t_1 = PyObject_GetItem(__pyx_v_datax, __pyx_t_17); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 261, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_1);
            __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
            __pyx_t_17 = __Pyx_GetItemInt(__pyx_t_1, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 261, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_17);
            __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
            __pyx_t_1 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 261, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_1);
            __pyx_t_6 = __Pyx_GetItemInt(__pyx_t_1, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 261, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_6);
            __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
            if (unlikely(PyDict_SetItem(__pyx_v_mass_center, __pyx_t_6, __pyx_t_17) < 0)) __PYX_ERR(0, 261, __pyx_L1_error)
            __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
            __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;

            /* "ims_extractor.pyx":263
 *                         mass_center[sequential_spec[i][0]] = datax[sequential_spec[i][0] + peak_pos[num_of_valley]][0]
 *                         # print mass_center[sequential_spec[i][0]]
 *                         while ii < iii:  # Combine everything before the first valley             # <<<<<<<<<<<<<<
 *                             datax[sequential_spec[i][0]] += datax[sequential_spec[i][0] + ii]
 *                             valid_spec.remove(sequential_spec[i][0] + ii)
 */
            while (1) {
              __pyx_t_17 = PyObject_RichCompare(__pyx_v_ii, __pyx_v_iii, Py_LT); __Pyx_XGOTREF(__pyx_t_17); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 263, __pyx_L1_error)
              __pyx_t_4 = __Pyx_PyObject_IsTrue(__pyx_t_17); if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(0, 263, __pyx_L1_error)
              __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
              if (!__pyx_t_4) break;

              /* "ims_extractor.pyx":264
 *                         # print mass_center[sequential_spec[i][0]]
 *                         while ii < iii:  # Combine everything before the first valley
 *                             datax[sequential_spec[i][0]] += datax[sequential_spec[i][0] + ii]             # <<<<<<<<<<<<<<
 *                             valid_spec.remove(sequential_spec[i][0] + ii)
 *                             intensity_dict[sequential_spec[i][0]] += intensity_dict[sequential_spec[i][0] + ii]
 */
              __pyx_t_17 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 264, __pyx_L1_error)
              __Pyx_GOTREF(__pyx_t_17);
              __pyx_t_6 = __Pyx_GetItemInt(__pyx_t_17, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 264, __pyx_L1_error)
              __Pyx_GOTREF(__pyx_t_6);
              __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
              __pyx_t_17 = PyObject_GetItem(__pyx_v_datax, __pyx_t_6); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 264, __pyx_L1_error)
              __Pyx_GOTREF(__pyx_t_17);
              __pyx_t_1 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 264, __pyx_L1_error)
              __Pyx_GOTREF(__pyx_t_1);
              __pyx_t_3 = __Pyx_GetItemInt(__pyx_t_1, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 264, __pyx_L1_error)
              __Pyx_GOTREF(__pyx_t_3);
              __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
              __pyx_t_1 = PyNumber_Add(__pyx_t_3, __pyx_v_ii); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 264, __pyx_L1_error)
              __Pyx_GOTREF(__pyx_t_1);
              __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
              __pyx_t_3 = PyObject_GetItem(__pyx_v_datax, __pyx_t_1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 264, __pyx_L1_error)
              __Pyx_GOTREF(__pyx_t_3);
              __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
              __pyx_t_1 = PyNumber_InPlaceAdd(__pyx_t_17, __pyx_t_3); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 264, __pyx_L1_error)
              __Pyx_GOTREF(__pyx_t_1);
              __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
              __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
              if (unlikely(PyObject_SetItem(__pyx_v_datax, __pyx_t_6, __pyx_t_1) < 0)) __PYX_ERR(0, 264, __pyx_L1_error)
              __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
              __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;

              /* "ims_extractor.pyx":265
 *                         while ii < iii:  # Combine everything before the first valley
 *                             datax[sequential_spec[i][0]] += datax[sequential_spec[i][0] + ii]
 *                             valid_spec.remove(sequential_spec[i][0] + ii)             # <<<<<<<<<<<<<<
 *                             intensity_dict[sequential_spec[i][0]] += intensity_dict[sequential_spec[i][0] + ii]
 *                             ii += 1
 */
              __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_valid_spec, __pyx_n_s_remove); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 265, __pyx_L1_error)
              __Pyx_GOTREF(__pyx_t_1);
              __pyx_t_3 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 265, __pyx_L1_error)
              __Pyx_GOTREF(__pyx_t_3);
              __pyx_t_17 = __Pyx_GetItemInt(__pyx_t_3, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 265, __pyx_L1_error)
              __Pyx_GOTREF(__pyx_t_17);
              __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
              __pyx_t_3 = PyNumber_Add(__pyx_t_17, __pyx_v_ii); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 265, __pyx_L1_error)
              __Pyx_GOTREF(__pyx_t_3);
              __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
              __pyx_t_17 = NULL;
              if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_1))) {
                __pyx_t_17 = PyMethod_GET_SELF(__pyx_t_1);
                if (likely(__pyx_t_17)) {
                  PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_1);
                  __Pyx_INCREF(__pyx_t_17);
                  __Pyx_INCREF(function);
                  __Pyx_DECREF_SET(__pyx_t_1, function);
                }
              }
              if (!__pyx_t_17) {
                __pyx_t_6 = __Pyx_PyObject_CallOneArg(__pyx_t_1, __pyx_t_3); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 265, __pyx_L1_error)
                __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
                __Pyx_GOTREF(__pyx_t_6);
              } else {
                #if CYTHON_FAST_PYCALL
                if (PyFunction_Check(__pyx_t_1)) {
                  PyObject *__pyx_temp[2] = {__pyx_t_17, __pyx_t_3};
                  __pyx_t_6 = __Pyx_PyFunction_FastCall(__pyx_t_1, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 265, __pyx_L1_error)
                  __Pyx_XDECREF(__pyx_t_17); __pyx_t_17 = 0;
                  __Pyx_GOTREF(__pyx_t_6);
                  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
                } else
                #endif
                #if CYTHON_FAST_PYCCALL
                if (__Pyx_PyFastCFunction_Check(__pyx_t_1)) {
                  PyObject *__pyx_temp[2] = {__pyx_t_17, __pyx_t_3};
                  __pyx_t_6 = __Pyx_PyCFunction_FastCall(__pyx_t_1, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 265, __pyx_L1_error)
                  __Pyx_XDECREF(__pyx_t_17); __pyx_t_17 = 0;
                  __Pyx_GOTREF(__pyx_t_6);
                  __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
                } else
                #endif
                {
                  __pyx_t_10 = PyTuple_New(1+1); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 265, __pyx_L1_error)
                  __Pyx_GOTREF(__pyx_t_10);
                  __Pyx_GIVEREF(__pyx_t_17); PyTuple_SET_ITEM(__pyx_t_10, 0, __pyx_t_17); __pyx_t_17 = NULL;
                  __Pyx_GIVEREF(__pyx_t_3);
                  PyTuple_SET_ITEM(__pyx_t_10, 0+1, __pyx_t_3);
                  __pyx_t_3 = 0;
                  __pyx_t_6 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_10, NULL); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 265, __pyx_L1_error)
                  __Pyx_GOTREF(__pyx_t_6);
                  __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
                }
              }
              __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
              __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;

              /* "ims_extractor.pyx":266
 *                             datax[sequential_spec[i][0]] += datax[sequential_spec[i][0] + ii]
 *                             valid_spec.remove(sequential_spec[i][0] + ii)
 *                             intensity_dict[sequential_spec[i][0]] += intensity_dict[sequential_spec[i][0] + ii]             # <<<<<<<<<<<<<<
 *                             ii += 1
 *                         num_of_valley += 1
 */
              __pyx_t_6 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 266, __pyx_L1_error)
              __Pyx_GOTREF(__pyx_t_6);
              __pyx_t_1 = __Pyx_GetItemInt(__pyx_t_6, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 266, __pyx_L1_error)
              __Pyx_GOTREF(__pyx_t_1);
              __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
              __pyx_t_6 = __Pyx_PyDict_GetItem(__pyx_v_intensity_dict, __pyx_t_1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 266, __pyx_L1_error)
              __Pyx_GOTREF(__pyx_t_6);
              __pyx_t_10 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 266, __pyx_L1_error)
              __Pyx_GOTREF(__pyx_t_10);
              __pyx_t_3 = __Pyx_GetItemInt(__pyx_t_10, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 266, __pyx_L1_error)
              __Pyx_GOTREF(__pyx_t_3);
              __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
              __pyx_t_10 = PyNumber_Add(__pyx_t_3, __pyx_v_ii); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 266, __pyx_L1_error)
              __Pyx_GOTREF(__pyx_t_10);
              __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
              __pyx_t_3 = __Pyx_PyDict_GetItem(__pyx_v_intensity_dict, __pyx_t_10); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 266, __pyx_L1_error)
              __Pyx_GOTREF(__pyx_t_3);
              __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
              __pyx_t_10 = PyNumber_InPlaceAdd(__pyx_t_6, __pyx_t_3); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 266, __pyx_L1_error)
              __Pyx_GOTREF(__pyx_t_10);
              __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
              __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
              if (unlikely(PyDict_SetItem(__pyx_v_intensity_dict, __pyx_t_1, __pyx_t_10) < 0)) __PYX_ERR(0, 266, __pyx_L1_error)
              __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
              __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

              /* "ims_extractor.pyx":267
 *                             valid_spec.remove(sequential_spec[i][0] + ii)
 *                             intensity_dict[sequential_spec[i][0]] += intensity_dict[sequential_spec[i][0] + ii]
 *                             ii += 1             # <<<<<<<<<<<<<<
 *                         num_of_valley += 1
 *                     mass_center[sequential_spec[i][0]] = datax[sequential_spec[i][0] + peak_pos[-1]][0]
 */
              __pyx_t_1 = __Pyx_PyInt_AddObjC(__pyx_v_ii, __pyx_int_1, 1, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 267, __pyx_L1_error)
              __Pyx_GOTREF(__pyx_t_1);
              __Pyx_DECREF_SET(__pyx_v_ii, __pyx_t_1);
              __pyx_t_1 = 0;
            }

            /* "ims_extractor.pyx":268
 *                             intensity_dict[sequential_spec[i][0]] += intensity_dict[sequential_spec[i][0] + ii]
 *                             ii += 1
 *                         num_of_valley += 1             # <<<<<<<<<<<<<<
 *                     mass_center[sequential_spec[i][0]] = datax[sequential_spec[i][0] + peak_pos[-1]][0]
 *                     # print mass_center[sequential_spec[i][0]]
 */
            __pyx_t_1 = __Pyx_PyInt_AddObjC(__pyx_v_num_of_valley, __pyx_int_1, 1, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 268, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_1);
            __Pyx_DECREF_SET(__pyx_v_num_of_valley, __pyx_t_1);
            __pyx_t_1 = 0;
          }

          /* "ims_extractor.pyx":269
 *                             ii += 1
 *                         num_of_valley += 1
 *                     mass_center[sequential_spec[i][0]] = datax[sequential_spec[i][0] + peak_pos[-1]][0]             # <<<<<<<<<<<<<<
 *                     # print mass_center[sequential_spec[i][0]]
 *                     while iii < sequential_spec[i][1]:  # collect everything else
 */
          __pyx_t_1 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 269, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_1);
          __pyx_t_10 = __Pyx_GetItemInt(__pyx_t_1, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 269, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_10);
          __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
          __pyx_t_1 = __Pyx_GetItemInt_List(__pyx_v_peak_pos, -1L, long, 1, __Pyx_PyInt_From_long, 1, 1, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 269, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_1);
          __pyx_t_3 = PyNumber_Add(__pyx_t_10, __pyx_t_1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 269, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_3);
          __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
          __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
          __pyx_t_1 = PyObject_GetItem(__pyx_v_datax, __pyx_t_3); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 269, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_1);
          __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
          __pyx_t_3 = __Pyx_GetItemInt(__pyx_t_1, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 269, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_3);
          __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
          __pyx_t_1 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 269, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_1);
          __pyx_t_10 = __Pyx_GetItemInt(__pyx_t_1, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 269, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_10);
          __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
          if (unlikely(PyDict_SetItem(__pyx_v_mass_center, __pyx_t_10, __pyx_t_3) < 0)) __PYX_ERR(0, 269, __pyx_L1_error)
          __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
          __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

          /* "ims_extractor.pyx":271
 *                     mass_center[sequential_spec[i][0]] = datax[sequential_spec[i][0] + peak_pos[-1]][0]
 *                     # print mass_center[sequential_spec[i][0]]
 *                     while iii < sequential_spec[i][1]:  # collect everything else             # <<<<<<<<<<<<<<
 *                         datax[sequential_spec[i][0]] += datax[sequential_spec[i][0] + iii]
 *                         valid_spec.remove(sequential_spec[i][0] + iii)
 */
          while (1) {
            if (unlikely(!__pyx_v_iii)) { __Pyx_RaiseUnboundLocalError("iii"); __PYX_ERR(0, 271, __pyx_L1_error) }
            __pyx_t_3 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 271, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_3);
            __pyx_t_10 = __Pyx_GetItemInt(__pyx_t_3, 1, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 271, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_10);
            __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
            __pyx_t_3 = PyObject_RichCompare(__pyx_v_iii, __pyx_t_10, Py_LT); __Pyx_XGOTREF(__pyx_t_3); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 271, __pyx_L1_error)
            __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
            __pyx_t_4 = __Pyx_PyObject_IsTrue(__pyx_t_3); if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(0, 271, __pyx_L1_error)
            __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
            if (!__pyx_t_4) break;

            /* "ims_extractor.pyx":272
 *                     # print mass_center[sequential_spec[i][0]]
 *                     while iii < sequential_spec[i][1]:  # collect everything else
 *                         datax[sequential_spec[i][0]] += datax[sequential_spec[i][0] + iii]             # <<<<<<<<<<<<<<
 *                         valid_spec.remove(sequential_spec[i][0] + iii)
 *                         intensity_dict[sequential_spec[i][0]] += intensity_dict[sequential_spec[i][0] + iii]
 */
            __pyx_t_3 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 272, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_3);
            __pyx_t_10 = __Pyx_GetItemInt(__pyx_t_3, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 272, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_10);
            __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
            __pyx_t_3 = PyObject_GetItem(__pyx_v_datax, __pyx_t_10); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 272, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_3);
            __pyx_t_1 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 272, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_1);
            __pyx_t_6 = __Pyx_GetItemInt(__pyx_t_1, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 272, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_6);
            __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
            if (unlikely(!__pyx_v_iii)) { __Pyx_RaiseUnboundLocalError("iii"); __PYX_ERR(0, 272, __pyx_L1_error) }
            __pyx_t_1 = PyNumber_Add(__pyx_t_6, __pyx_v_iii); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 272, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_1);
            __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
            __pyx_t_6 = PyObject_GetItem(__pyx_v_datax, __pyx_t_1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 272, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_6);
            __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
            __pyx_t_1 = PyNumber_InPlaceAdd(__pyx_t_3, __pyx_t_6); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 272, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_1);
            __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
            __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
            if (unlikely(PyObject_SetItem(__pyx_v_datax, __pyx_t_10, __pyx_t_1) < 0)) __PYX_ERR(0, 272, __pyx_L1_error)
            __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
            __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;

            /* "ims_extractor.pyx":273
 *                     while iii < sequential_spec[i][1]:  # collect everything else
 *                         datax[sequential_spec[i][0]] += datax[sequential_spec[i][0] + iii]
 *                         valid_spec.remove(sequential_spec[i][0] + iii)             # <<<<<<<<<<<<<<
 *                         intensity_dict[sequential_spec[i][0]] += intensity_dict[sequential_spec[i][0] + iii]
 *                         iii += 1
 */
            __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_valid_spec, __pyx_n_s_remove); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 273, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_1);
            __pyx_t_6 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 273, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_6);
            __pyx_t_3 = __Pyx_GetItemInt(__pyx_t_6, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 273, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_3);
            __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
            if (unlikely(!__pyx_v_iii)) { __Pyx_RaiseUnboundLocalError("iii"); __PYX_ERR(0, 273, __pyx_L1_error) }
            __pyx_t_6 = PyNumber_Add(__pyx_t_3, __pyx_v_iii); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 273, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_6);
            __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
            __pyx_t_3 = NULL;
            if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_1))) {
              __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_1);
              if (likely(__pyx_t_3)) {
                PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_1);
                __Pyx_INCREF(__pyx_t_3);
                __Pyx_INCREF(function);
                __Pyx_DECREF_SET(__pyx_t_1, function);
              }
            }
            if (!__pyx_t_3) {
              __pyx_t_10 = __Pyx_PyObject_CallOneArg(__pyx_t_1, __pyx_t_6); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 273, __pyx_L1_error)
              __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
              __Pyx_GOTREF(__pyx_t_10);
            } else {
              #if CYTHON_FAST_PYCALL
              if (PyFunction_Check(__pyx_t_1)) {
                PyObject *__pyx_temp[2] = {__pyx_t_3, __pyx_t_6};
                __pyx_t_10 = __Pyx_PyFunction_FastCall(__pyx_t_1, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 273, __pyx_L1_error)
                __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
                __Pyx_GOTREF(__pyx_t_10);
                __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
              } else
              #endif
              #if CYTHON_FAST_PYCCALL
              if (__Pyx_PyFastCFunction_Check(__pyx_t_1)) {
                PyObject *__pyx_temp[2] = {__pyx_t_3, __pyx_t_6};
                __pyx_t_10 = __Pyx_PyCFunction_FastCall(__pyx_t_1, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 273, __pyx_L1_error)
                __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
                __Pyx_GOTREF(__pyx_t_10);
                __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
              } else
              #endif
              {
                __pyx_t_17 = PyTuple_New(1+1); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 273, __pyx_L1_error)
                __Pyx_GOTREF(__pyx_t_17);
                __Pyx_GIVEREF(__pyx_t_3); PyTuple_SET_ITEM(__pyx_t_17, 0, __pyx_t_3); __pyx_t_3 = NULL;
                __Pyx_GIVEREF(__pyx_t_6);
                PyTuple_SET_ITEM(__pyx_t_17, 0+1, __pyx_t_6);
                __pyx_t_6 = 0;
                __pyx_t_10 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_17, NULL); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 273, __pyx_L1_error)
                __Pyx_GOTREF(__pyx_t_10);
                __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
              }
            }
            __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
            __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;

            /* "ims_extractor.pyx":274
 *                         datax[sequential_spec[i][0]] += datax[sequential_spec[i][0] + iii]
 *                         valid_spec.remove(sequential_spec[i][0] + iii)
 *                         intensity_dict[sequential_spec[i][0]] += intensity_dict[sequential_spec[i][0] + iii]             # <<<<<<<<<<<<<<
 *                         iii += 1
 *                         # print temp_int, temp_diff,iii
 */
            __pyx_t_10 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 274, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_10);
            __pyx_t_1 = __Pyx_GetItemInt(__pyx_t_10, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 274, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_1);
            __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
            __pyx_t_10 = __Pyx_PyDict_GetItem(__pyx_v_intensity_dict, __pyx_t_1); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 274, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_10);
            __pyx_t_17 = PyObject_GetItem(__pyx_v_sequential_spec, __pyx_v_i); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 274, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_17);
            __pyx_t_6 = __Pyx_GetItemInt(__pyx_t_17, 0, long, 1, __Pyx_PyInt_From_long, 0, 0, 1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 274, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_6);
            __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
            if (unlikely(!__pyx_v_iii)) { __Pyx_RaiseUnboundLocalError("iii"); __PYX_ERR(0, 274, __pyx_L1_error) }
            __pyx_t_17 = PyNumber_Add(__pyx_t_6, __pyx_v_iii); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 274, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_17);
            __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
            __pyx_t_6 = __Pyx_PyDict_GetItem(__pyx_v_intensity_dict, __pyx_t_17); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 274, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_6);
            __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
            __pyx_t_17 = PyNumber_InPlaceAdd(__pyx_t_10, __pyx_t_6); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 274, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_17);
            __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
            __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
            if (unlikely(PyDict_SetItem(__pyx_v_intensity_dict, __pyx_t_1, __pyx_t_17) < 0)) __PYX_ERR(0, 274, __pyx_L1_error)
            __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
            __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

            /* "ims_extractor.pyx":275
 *                         valid_spec.remove(sequential_spec[i][0] + iii)
 *                         intensity_dict[sequential_spec[i][0]] += intensity_dict[sequential_spec[i][0] + iii]
 *                         iii += 1             # <<<<<<<<<<<<<<
 *                         # print temp_int, temp_diff,iii
 *                 peak_count.append(temp_peak_count)
 */
            if (unlikely(!__pyx_v_iii)) { __Pyx_RaiseUnboundLocalError("iii"); __PYX_ERR(0, 275, __pyx_L1_error) }
            __pyx_t_1 = __Pyx_PyInt_AddObjC(__pyx_v_iii, __pyx_int_1, 1, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 275, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_1);
            __Pyx_XDECREF_SET(__pyx_v_iii, __pyx_t_1);
            __pyx_t_1 = 0;
          }
        }
        __pyx_L54:;

        /* "ims_extractor.pyx":277
 *                         iii += 1
 *                         # print temp_int, temp_diff,iii
 *                 peak_count.append(temp_peak_count)             # <<<<<<<<<<<<<<
 * 
 *             i += 1
 */
        __pyx_t_5 = __Pyx_PyList_Append(__pyx_v_peak_count, __pyx_v_temp_peak_count); if (unlikely(__pyx_t_5 == -1)) __PYX_ERR(0, 277, __pyx_L1_error)
      }
      __pyx_L43:;

      /* "ims_extractor.pyx":279
 *                 peak_count.append(temp_peak_count)
 * 
 *             i += 1             # <<<<<<<<<<<<<<
 * 
 *         # pool2 = multiprocessing.Pool(processes=multiprocessing.cpu_count())
 */
      __pyx_t_1 = __Pyx_PyInt_AddObjC(__pyx_v_i, __pyx_int_1, 1, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 279, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF_SET(__pyx_v_i, __pyx_t_1);
      __pyx_t_1 = 0;
    }

    /* "ims_extractor.pyx":286
 *         # pool2.join()
 * 
 *         print "| Features combined.                                 |"             # <<<<<<<<<<<<<<
 *         end = time.clock()
 *         timex = (end - start1)
 */
    if (__Pyx_PrintOne(0, __pyx_kp_s_Features_combined) < 0) __PYX_ERR(0, 286, __pyx_L1_error)

    /* "ims_extractor.pyx":287
 * 
 *         print "| Features combined.                                 |"
 *         end = time.clock()             # <<<<<<<<<<<<<<
 *         timex = (end - start1)
 *         print "| Time spent(s):", "{:10.4f}".format(timex), "                         |"
 */
    __pyx_t_17 = __Pyx_GetModuleGlobalName(__pyx_n_s_time); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 287, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_17);
    __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_t_17, __pyx_n_s_clock); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 287, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
    __pyx_t_17 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_6))) {
      __pyx_t_17 = PyMethod_GET_SELF(__pyx_t_6);
      if (likely(__pyx_t_17)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_6);
        __Pyx_INCREF(__pyx_t_17);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_6, function);
      }
    }
    if (__pyx_t_17) {
      __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_6, __pyx_t_17); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 287, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
    } else {
      __pyx_t_1 = __Pyx_PyObject_CallNoArg(__pyx_t_6); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 287, __pyx_L1_error)
    }
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __Pyx_DECREF_SET(__pyx_v_end, __pyx_t_1);
    __pyx_t_1 = 0;

    /* "ims_extractor.pyx":288
 *         print "| Features combined.                                 |"
 *         end = time.clock()
 *         timex = (end - start1)             # <<<<<<<<<<<<<<
 *         print "| Time spent(s):", "{:10.4f}".format(timex), "                         |"
 *         print "| Number of spectra for inspection:", str(len(valid_spec)).ljust(15), " |"
 */
    __pyx_t_1 = PyNumber_Subtract(__pyx_v_end, __pyx_v_start1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 288, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF_SET(__pyx_v_timex, __pyx_t_1);
    __pyx_t_1 = 0;

    /* "ims_extractor.pyx":289
 *         end = time.clock()
 *         timex = (end - start1)
 *         print "| Time spent(s):", "{:10.4f}".format(timex), "                         |"             # <<<<<<<<<<<<<<
 *         print "| Number of spectra for inspection:", str(len(valid_spec)).ljust(15), " |"
 *         print "#----------------------------------------------------#"
 */
    __pyx_t_6 = __Pyx_PyObject_GetAttrStr(__pyx_kp_s_10_4f, __pyx_n_s_format); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 289, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_17 = NULL;
    if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_6))) {
      __pyx_t_17 = PyMethod_GET_SELF(__pyx_t_6);
      if (likely(__pyx_t_17)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_6);
        __Pyx_INCREF(__pyx_t_17);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_6, function);
      }
    }
    if (!__pyx_t_17) {
      __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_6, __pyx_v_timex); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 289, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
    } else {
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_6)) {
        PyObject *__pyx_temp[2] = {__pyx_t_17, __pyx_v_timex};
        __pyx_t_1 = __Pyx_PyFunction_FastCall(__pyx_t_6, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 289, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_17); __pyx_t_17 = 0;
        __Pyx_GOTREF(__pyx_t_1);
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_6)) {
        PyObject *__pyx_temp[2] = {__pyx_t_17, __pyx_v_timex};
        __pyx_t_1 = __Pyx_PyCFunction_FastCall(__pyx_t_6, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 289, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_17); __pyx_t_17 = 0;
        __Pyx_GOTREF(__pyx_t_1);
      } else
      #endif
      {
        __pyx_t_10 = PyTuple_New(1+1); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 289, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_10);
        __Pyx_GIVEREF(__pyx_t_17); PyTuple_SET_ITEM(__pyx_t_10, 0, __pyx_t_17); __pyx_t_17 = NULL;
        __Pyx_INCREF(__pyx_v_timex);
        __Pyx_GIVEREF(__pyx_v_timex);
        PyTuple_SET_ITEM(__pyx_t_10, 0+1, __pyx_v_timex);
        __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_6, __pyx_t_10, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 289, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
      }
    }
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __pyx_t_6 = PyTuple_New(3); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 289, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_INCREF(__pyx_kp_s_Time_spent_s);
    __Pyx_GIVEREF(__pyx_kp_s_Time_spent_s);
    PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_kp_s_Time_spent_s);
    __Pyx_GIVEREF(__pyx_t_1);
    PyTuple_SET_ITEM(__pyx_t_6, 1, __pyx_t_1);
    __Pyx_INCREF(__pyx_kp_s__16);
    __Pyx_GIVEREF(__pyx_kp_s__16);
    PyTuple_SET_ITEM(__pyx_t_6, 2, __pyx_kp_s__16);
    __pyx_t_1 = 0;
    if (__Pyx_Print(0, __pyx_t_6, 1) < 0) __PYX_ERR(0, 289, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;

    /* "ims_extractor.pyx":290
 *         timex = (end - start1)
 *         print "| Time spent(s):", "{:10.4f}".format(timex), "                         |"
 *         print "| Number of spectra for inspection:", str(len(valid_spec)).ljust(15), " |"             # <<<<<<<<<<<<<<
 *         print "#----------------------------------------------------#"
 *         print "| Writing", file_name_ims.ljust(41), " |"
 */
    __pyx_t_7 = PyList_GET_SIZE(__pyx_v_valid_spec); if (unlikely(__pyx_t_7 == -1)) __PYX_ERR(0, 290, __pyx_L1_error)
    __pyx_t_6 = PyInt_FromSsize_t(__pyx_t_7); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 290, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_1 = PyTuple_New(1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 290, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_GIVEREF(__pyx_t_6);
    PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_t_6);
    __pyx_t_6 = 0;
    __pyx_t_6 = __Pyx_PyObject_Call(((PyObject *)(&PyString_Type)), __pyx_t_1, NULL); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 290, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_t_6, __pyx_n_s_ljust); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 290, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __pyx_t_6 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_tuple__21, NULL); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 290, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_1 = PyTuple_New(3); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 290, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_INCREF(__pyx_kp_s_Number_of_spectra_for_inspectio);
    __Pyx_GIVEREF(__pyx_kp_s_Number_of_spectra_for_inspectio);
    PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_kp_s_Number_of_spectra_for_inspectio);
    __Pyx_GIVEREF(__pyx_t_6);
    PyTuple_SET_ITEM(__pyx_t_1, 1, __pyx_t_6);
    __Pyx_INCREF(__pyx_kp_s__22);
    __Pyx_GIVEREF(__pyx_kp_s__22);
    PyTuple_SET_ITEM(__pyx_t_1, 2, __pyx_kp_s__22);
    __pyx_t_6 = 0;
    if (__Pyx_Print(0, __pyx_t_1, 1) < 0) __PYX_ERR(0, 290, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

    /* "ims_extractor.pyx":291
 *         print "| Time spent(s):", "{:10.4f}".format(timex), "                         |"
 *         print "| Number of spectra for inspection:", str(len(valid_spec)).ljust(15), " |"
 *         print "#----------------------------------------------------#"             # <<<<<<<<<<<<<<
 *         print "| Writing", file_name_ims.ljust(41), " |"
 *         start1 = time.clock()
 */
    if (__Pyx_PrintOne(0, __pyx_kp_s__10) < 0) __PYX_ERR(0, 291, __pyx_L1_error)

    /* "ims_extractor.pyx":292
 *         print "| Number of spectra for inspection:", str(len(valid_spec)).ljust(15), " |"
 *         print "#----------------------------------------------------#"
 *         print "| Writing", file_name_ims.ljust(41), " |"             # <<<<<<<<<<<<<<
 *         start1 = time.clock()
 * 
 */
    __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_file_name_ims, __pyx_n_s_ljust); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 292, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_6 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_tuple__23, NULL); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 292, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __pyx_t_1 = PyTuple_New(3); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 292, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_INCREF(__pyx_kp_s_Writing);
    __Pyx_GIVEREF(__pyx_kp_s_Writing);
    PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_kp_s_Writing);
    __Pyx_GIVEREF(__pyx_t_6);
    PyTuple_SET_ITEM(__pyx_t_1, 1, __pyx_t_6);
    __Pyx_INCREF(__pyx_kp_s__22);
    __Pyx_GIVEREF(__pyx_kp_s__22);
    PyTuple_SET_ITEM(__pyx_t_1, 2, __pyx_kp_s__22);
    __pyx_t_6 = 0;
    if (__Pyx_Print(0, __pyx_t_1, 1) < 0) __PYX_ERR(0, 292, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

    /* "ims_extractor.pyx":293
 *         print "#----------------------------------------------------#"
 *         print "| Writing", file_name_ims.ljust(41), " |"
 *         start1 = time.clock()             # <<<<<<<<<<<<<<
 * 
 *         i = 0
 */
    __pyx_t_6 = __Pyx_GetModuleGlobalName(__pyx_n_s_time); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 293, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_10 = __Pyx_PyObject_GetAttrStr(__pyx_t_6, __pyx_n_s_clock); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 293, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_10);
    __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    __pyx_t_6 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_10))) {
      __pyx_t_6 = PyMethod_GET_SELF(__pyx_t_10);
      if (likely(__pyx_t_6)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_10);
        __Pyx_INCREF(__pyx_t_6);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_10, function);
      }
    }
    if (__pyx_t_6) {
      __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_10, __pyx_t_6); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 293, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
    } else {
      __pyx_t_1 = __Pyx_PyObject_CallNoArg(__pyx_t_10); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 293, __pyx_L1_error)
    }
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
    __Pyx_DECREF_SET(__pyx_v_start1, __pyx_t_1);
    __pyx_t_1 = 0;

    /* "ims_extractor.pyx":295
 *         start1 = time.clock()
 * 
 *         i = 0             # <<<<<<<<<<<<<<
 *         iii = 0
 *         # print len(datax[1]), len(datax[2]), len(datax[3]), len(datax[4]), len(datax[5]), len(datax[6]), len(datax[7])
 */
    __Pyx_INCREF(__pyx_int_0);
    __Pyx_DECREF_SET(__pyx_v_i, __pyx_int_0);

    /* "ims_extractor.pyx":296
 * 
 *         i = 0
 *         iii = 0             # <<<<<<<<<<<<<<
 *         # print len(datax[1]), len(datax[2]), len(datax[3]), len(datax[4]), len(datax[5]), len(datax[6]), len(datax[7])
 *         while i < len(valid_spec):  # write the whole array in ims format
 */
    __Pyx_INCREF(__pyx_int_0);
    __Pyx_XDECREF_SET(__pyx_v_iii, __pyx_int_0);

    /* "ims_extractor.pyx":298
 *         iii = 0
 *         # print len(datax[1]), len(datax[2]), len(datax[3]), len(datax[4]), len(datax[5]), len(datax[6]), len(datax[7])
 *         while i < len(valid_spec):  # write the whole array in ims format             # <<<<<<<<<<<<<<
 *             if len(datax[valid_spec[i]]) > 33:
 *                 ii = 2
 */
    while (1) {
      __pyx_t_7 = PyList_GET_SIZE(__pyx_v_valid_spec); if (unlikely(__pyx_t_7 == -1)) __PYX_ERR(0, 298, __pyx_L1_error)
      __pyx_t_1 = PyInt_FromSsize_t(__pyx_t_7); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 298, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __pyx_t_10 = PyObject_RichCompare(__pyx_v_i, __pyx_t_1, Py_LT); __Pyx_XGOTREF(__pyx_t_10); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 298, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      __pyx_t_4 = __Pyx_PyObject_IsTrue(__pyx_t_10); if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(0, 298, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
      if (!__pyx_t_4) break;

      /* "ims_extractor.pyx":299
 *         # print len(datax[1]), len(datax[2]), len(datax[3]), len(datax[4]), len(datax[5]), len(datax[6]), len(datax[7])
 *         while i < len(valid_spec):  # write the whole array in ims format
 *             if len(datax[valid_spec[i]]) > 33:             # <<<<<<<<<<<<<<
 *                 ii = 2
 *                 zero_fill = []
 */
      __pyx_t_10 = PyObject_GetItem(__pyx_v_valid_spec, __pyx_v_i); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 299, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_10);
      __pyx_t_1 = PyObject_GetItem(__pyx_v_datax, __pyx_t_10); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 299, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
      __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
      __pyx_t_7 = PyObject_Length(__pyx_t_1); if (unlikely(__pyx_t_7 == -1)) __PYX_ERR(0, 299, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
      __pyx_t_4 = ((__pyx_t_7 > 33) != 0);
      if (__pyx_t_4) {

        /* "ims_extractor.pyx":300
 *         while i < len(valid_spec):  # write the whole array in ims format
 *             if len(datax[valid_spec[i]]) > 33:
 *                 ii = 2             # <<<<<<<<<<<<<<
 *                 zero_fill = []
 *                 time_available = sorted(datax[valid_spec[i]][2::3])
 */
        __Pyx_INCREF(__pyx_int_2);
        __Pyx_XDECREF_SET(__pyx_v_ii, __pyx_int_2);

        /* "ims_extractor.pyx":301
 *             if len(datax[valid_spec[i]]) > 33:
 *                 ii = 2
 *                 zero_fill = []             # <<<<<<<<<<<<<<
 *                 time_available = sorted(datax[valid_spec[i]][2::3])
 *                 time_start = time_available[0]
 */
        __pyx_t_1 = PyList_New(0); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 301, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        __Pyx_XDECREF_SET(__pyx_v_zero_fill, ((PyObject*)__pyx_t_1));
        __pyx_t_1 = 0;

        /* "ims_extractor.pyx":302
 *                 ii = 2
 *                 zero_fill = []
 *                 time_available = sorted(datax[valid_spec[i]][2::3])             # <<<<<<<<<<<<<<
 *                 time_start = time_available[0]
 *                 time_end = time_available[-1]
 */
        __pyx_t_10 = PyObject_GetItem(__pyx_v_valid_spec, __pyx_v_i); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 302, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_10);
        __pyx_t_6 = PyObject_GetItem(__pyx_v_datax, __pyx_t_10); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 302, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_6);
        __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
        __pyx_t_10 = PyObject_GetItem(__pyx_t_6, __pyx_slice__24); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 302, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_10);
        __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
        __pyx_t_6 = PySequence_List(__pyx_t_10); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 302, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_6);
        __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
        __pyx_t_1 = ((PyObject*)__pyx_t_6);
        __pyx_t_6 = 0;
        __pyx_t_5 = PyList_Sort(__pyx_t_1); if (unlikely(__pyx_t_5 == -1)) __PYX_ERR(0, 302, __pyx_L1_error)
        __Pyx_XDECREF_SET(__pyx_v_time_available, ((PyObject*)__pyx_t_1));
        __pyx_t_1 = 0;

        /* "ims_extractor.pyx":303
 *                 zero_fill = []
 *                 time_available = sorted(datax[valid_spec[i]][2::3])
 *                 time_start = time_available[0]             # <<<<<<<<<<<<<<
 *                 time_end = time_available[-1]
 * 
 */
        if (unlikely(__pyx_v_time_available == Py_None)) {
          PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
          __PYX_ERR(0, 303, __pyx_L1_error)
        }
        __pyx_t_1 = __Pyx_GetItemInt_List(__pyx_v_time_available, 0, long, 1, __Pyx_PyInt_From_long, 1, 0, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 303, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        __Pyx_XDECREF_SET(__pyx_v_time_start, __pyx_t_1);
        __pyx_t_1 = 0;

        /* "ims_extractor.pyx":304
 *                 time_available = sorted(datax[valid_spec[i]][2::3])
 *                 time_start = time_available[0]
 *                 time_end = time_available[-1]             # <<<<<<<<<<<<<<
 * 
 *                 ii = 0
 */
        if (unlikely(__pyx_v_time_available == Py_None)) {
          PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
          __PYX_ERR(0, 304, __pyx_L1_error)
        }
        __pyx_t_1 = __Pyx_GetItemInt_List(__pyx_v_time_available, -1L, long, 1, __Pyx_PyInt_From_long, 1, 1, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 304, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        __Pyx_XDECREF_SET(__pyx_v_time_end, __pyx_t_1);
        __pyx_t_1 = 0;

        /* "ims_extractor.pyx":306
 *                 time_end = time_available[-1]
 * 
 *                 ii = 0             # <<<<<<<<<<<<<<
 *                 increment = 0.02
 *                 while ii < 99:
 */
        __Pyx_INCREF(__pyx_int_0);
        __Pyx_DECREF_SET(__pyx_v_ii, __pyx_int_0);

        /* "ims_extractor.pyx":307
 * 
 *                 ii = 0
 *                 increment = 0.02             # <<<<<<<<<<<<<<
 *                 while ii < 99:
 *                     zero_fill.append([xa[valid_spec[i]], 1, time_end])
 */
        __pyx_v_increment = 0.02;

        /* "ims_extractor.pyx":308
 *                 ii = 0
 *                 increment = 0.02
 *                 while ii < 99:             # <<<<<<<<<<<<<<
 *                     zero_fill.append([xa[valid_spec[i]], 1, time_end])
 *                     if time_start > 0:
 */
        while (1) {
          __pyx_t_1 = PyObject_RichCompare(__pyx_v_ii, __pyx_int_99, Py_LT); __Pyx_XGOTREF(__pyx_t_1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 308, __pyx_L1_error)
          __pyx_t_4 = __Pyx_PyObject_IsTrue(__pyx_t_1); if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(0, 308, __pyx_L1_error)
          __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
          if (!__pyx_t_4) break;

          /* "ims_extractor.pyx":309
 *                 increment = 0.02
 *                 while ii < 99:
 *                     zero_fill.append([xa[valid_spec[i]], 1, time_end])             # <<<<<<<<<<<<<<
 *                     if time_start > 0:
 *                         zero_fill.append([xa[valid_spec[i]], 1, time_start])
 */
          __pyx_t_1 = PyObject_GetItem(__pyx_v_valid_spec, __pyx_v_i); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 309, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_1);
          __pyx_t_6 = PyObject_GetItem(__pyx_v_xa, __pyx_t_1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 309, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_6);
          __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
          __pyx_t_1 = PyList_New(3); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 309, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_1);
          __Pyx_GIVEREF(__pyx_t_6);
          PyList_SET_ITEM(__pyx_t_1, 0, __pyx_t_6);
          __Pyx_INCREF(__pyx_int_1);
          __Pyx_GIVEREF(__pyx_int_1);
          PyList_SET_ITEM(__pyx_t_1, 1, __pyx_int_1);
          __Pyx_INCREF(__pyx_v_time_end);
          __Pyx_GIVEREF(__pyx_v_time_end);
          PyList_SET_ITEM(__pyx_t_1, 2, __pyx_v_time_end);
          __pyx_t_6 = 0;
          __pyx_t_5 = __Pyx_PyList_Append(__pyx_v_zero_fill, __pyx_t_1); if (unlikely(__pyx_t_5 == -1)) __PYX_ERR(0, 309, __pyx_L1_error)
          __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

          /* "ims_extractor.pyx":310
 *                 while ii < 99:
 *                     zero_fill.append([xa[valid_spec[i]], 1, time_end])
 *                     if time_start > 0:             # <<<<<<<<<<<<<<
 *                         zero_fill.append([xa[valid_spec[i]], 1, time_start])
 *                         time_start -= increment
 */
          __pyx_t_1 = PyObject_RichCompare(__pyx_v_time_start, __pyx_int_0, Py_GT); __Pyx_XGOTREF(__pyx_t_1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 310, __pyx_L1_error)
          __pyx_t_4 = __Pyx_PyObject_IsTrue(__pyx_t_1); if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(0, 310, __pyx_L1_error)
          __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
          if (__pyx_t_4) {

            /* "ims_extractor.pyx":311
 *                     zero_fill.append([xa[valid_spec[i]], 1, time_end])
 *                     if time_start > 0:
 *                         zero_fill.append([xa[valid_spec[i]], 1, time_start])             # <<<<<<<<<<<<<<
 *                         time_start -= increment
 *                     time_end += increment
 */
            __pyx_t_1 = PyObject_GetItem(__pyx_v_valid_spec, __pyx_v_i); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 311, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_1);
            __pyx_t_6 = PyObject_GetItem(__pyx_v_xa, __pyx_t_1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 311, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_6);
            __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
            __pyx_t_1 = PyList_New(3); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 311, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_1);
            __Pyx_GIVEREF(__pyx_t_6);
            PyList_SET_ITEM(__pyx_t_1, 0, __pyx_t_6);
            __Pyx_INCREF(__pyx_int_1);
            __Pyx_GIVEREF(__pyx_int_1);
            PyList_SET_ITEM(__pyx_t_1, 1, __pyx_int_1);
            __Pyx_INCREF(__pyx_v_time_start);
            __Pyx_GIVEREF(__pyx_v_time_start);
            PyList_SET_ITEM(__pyx_t_1, 2, __pyx_v_time_start);
            __pyx_t_6 = 0;
            __pyx_t_5 = __Pyx_PyList_Append(__pyx_v_zero_fill, __pyx_t_1); if (unlikely(__pyx_t_5 == -1)) __PYX_ERR(0, 311, __pyx_L1_error)
            __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

            /* "ims_extractor.pyx":312
 *                     if time_start > 0:
 *                         zero_fill.append([xa[valid_spec[i]], 1, time_start])
 *                         time_start -= increment             # <<<<<<<<<<<<<<
 *                     time_end += increment
 *                     ii += 1
 */
            __pyx_t_1 = PyFloat_FromDouble(__pyx_v_increment); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 312, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_1);
            __pyx_t_6 = PyNumber_InPlaceSubtract(__pyx_v_time_start, __pyx_t_1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 312, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_6);
            __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
            __Pyx_DECREF_SET(__pyx_v_time_start, __pyx_t_6);
            __pyx_t_6 = 0;

            /* "ims_extractor.pyx":310
 *                 while ii < 99:
 *                     zero_fill.append([xa[valid_spec[i]], 1, time_end])
 *                     if time_start > 0:             # <<<<<<<<<<<<<<
 *                         zero_fill.append([xa[valid_spec[i]], 1, time_start])
 *                         time_start -= increment
 */
          }

          /* "ims_extractor.pyx":313
 *                         zero_fill.append([xa[valid_spec[i]], 1, time_start])
 *                         time_start -= increment
 *                     time_end += increment             # <<<<<<<<<<<<<<
 *                     ii += 1
 *                 zero_fill.append([xa[valid_spec[i]], 1, start_time])  # add start_time
 */
          __pyx_t_6 = PyFloat_FromDouble(__pyx_v_increment); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 313, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_6);
          __pyx_t_1 = PyNumber_InPlaceAdd(__pyx_v_time_end, __pyx_t_6); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 313, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_1);
          __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
          __Pyx_DECREF_SET(__pyx_v_time_end, __pyx_t_1);
          __pyx_t_1 = 0;

          /* "ims_extractor.pyx":314
 *                         time_start -= increment
 *                     time_end += increment
 *                     ii += 1             # <<<<<<<<<<<<<<
 *                 zero_fill.append([xa[valid_spec[i]], 1, start_time])  # add start_time
 *                 zero_fill.append([xa[valid_spec[i]], 1, end_time])  # add end_time
 */
          __pyx_t_1 = __Pyx_PyInt_AddObjC(__pyx_v_ii, __pyx_int_1, 1, 1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 314, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_1);
          __Pyx_DECREF_SET(__pyx_v_ii, __pyx_t_1);
          __pyx_t_1 = 0;
        }

        /* "ims_extractor.pyx":315
 *                     time_end += increment
 *                     ii += 1
 *                 zero_fill.append([xa[valid_spec[i]], 1, start_time])  # add start_time             # <<<<<<<<<<<<<<
 *                 zero_fill.append([xa[valid_spec[i]], 1, end_time])  # add end_time
 *                 ii = 1
 */
        __pyx_t_1 = PyObject_GetItem(__pyx_v_valid_spec, __pyx_v_i); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 315, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        __pyx_t_6 = PyObject_GetItem(__pyx_v_xa, __pyx_t_1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 315, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_6);
        __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
        __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_start_time); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 315, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        __pyx_t_10 = PyList_New(3); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 315, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_10);
        __Pyx_GIVEREF(__pyx_t_6);
        PyList_SET_ITEM(__pyx_t_10, 0, __pyx_t_6);
        __Pyx_INCREF(__pyx_int_1);
        __Pyx_GIVEREF(__pyx_int_1);
        PyList_SET_ITEM(__pyx_t_10, 1, __pyx_int_1);
        __Pyx_GIVEREF(__pyx_t_1);
        PyList_SET_ITEM(__pyx_t_10, 2, __pyx_t_1);
        __pyx_t_6 = 0;
        __pyx_t_1 = 0;
        __pyx_t_5 = __Pyx_PyList_Append(__pyx_v_zero_fill, __pyx_t_10); if (unlikely(__pyx_t_5 == -1)) __PYX_ERR(0, 315, __pyx_L1_error)
        __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;

        /* "ims_extractor.pyx":316
 *                     ii += 1
 *                 zero_fill.append([xa[valid_spec[i]], 1, start_time])  # add start_time
 *                 zero_fill.append([xa[valid_spec[i]], 1, end_time])  # add end_time             # <<<<<<<<<<<<<<
 *                 ii = 1
 *                 while ii < len(time_available):
 */
        __pyx_t_10 = PyObject_GetItem(__pyx_v_valid_spec, __pyx_v_i); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 316, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_10);
        __pyx_t_1 = PyObject_GetItem(__pyx_v_xa, __pyx_t_10); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 316, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
        __pyx_t_10 = __Pyx_GetModuleGlobalName(__pyx_n_s_end_time); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 316, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_10);
        __pyx_t_6 = PyList_New(3); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 316, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_6);
        __Pyx_GIVEREF(__pyx_t_1);
        PyList_SET_ITEM(__pyx_t_6, 0, __pyx_t_1);
        __Pyx_INCREF(__pyx_int_1);
        __Pyx_GIVEREF(__pyx_int_1);
        PyList_SET_ITEM(__pyx_t_6, 1, __pyx_int_1);
        __Pyx_GIVEREF(__pyx_t_10);
        PyList_SET_ITEM(__pyx_t_6, 2, __pyx_t_10);
        __pyx_t_1 = 0;
        __pyx_t_10 = 0;
        __pyx_t_5 = __Pyx_PyList_Append(__pyx_v_zero_fill, __pyx_t_6); if (unlikely(__pyx_t_5 == -1)) __PYX_ERR(0, 316, __pyx_L1_error)
        __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;

        /* "ims_extractor.pyx":317
 *                 zero_fill.append([xa[valid_spec[i]], 1, start_time])  # add start_time
 *                 zero_fill.append([xa[valid_spec[i]], 1, end_time])  # add end_time
 *                 ii = 1             # <<<<<<<<<<<<<<
 *                 while ii < len(time_available):
 *                     iii = time_available[ii]
 */
        __Pyx_INCREF(__pyx_int_1);
        __Pyx_DECREF_SET(__pyx_v_ii, __pyx_int_1);

        /* "ims_extractor.pyx":318
 *                 zero_fill.append([xa[valid_spec[i]], 1, end_time])  # add end_time
 *                 ii = 1
 *                 while ii < len(time_available):             # <<<<<<<<<<<<<<
 *                     iii = time_available[ii]
 *                     difference = (iii - time_available[ii - 1]) / 100  # fill 100 zero points between peaks instead of 5
 */
        while (1) {
          if (unlikely(__pyx_v_time_available == Py_None)) {
            PyErr_SetString(PyExc_TypeError, "object of type 'NoneType' has no len()");
            __PYX_ERR(0, 318, __pyx_L1_error)
          }
          __pyx_t_7 = PyList_GET_SIZE(__pyx_v_time_available); if (unlikely(__pyx_t_7 == -1)) __PYX_ERR(0, 318, __pyx_L1_error)
          __pyx_t_6 = PyInt_FromSsize_t(__pyx_t_7); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 318, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_6);
          __pyx_t_10 = PyObject_RichCompare(__pyx_v_ii, __pyx_t_6, Py_LT); __Pyx_XGOTREF(__pyx_t_10); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 318, __pyx_L1_error)
          __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
          __pyx_t_4 = __Pyx_PyObject_IsTrue(__pyx_t_10); if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(0, 318, __pyx_L1_error)
          __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
          if (!__pyx_t_4) break;

          /* "ims_extractor.pyx":319
 *                 ii = 1
 *                 while ii < len(time_available):
 *                     iii = time_available[ii]             # <<<<<<<<<<<<<<
 *                     difference = (iii - time_available[ii - 1]) / 100  # fill 100 zero points between peaks instead of 5
 *                     if difference > 0.5:
 */
          if (unlikely(__pyx_v_time_available == Py_None)) {
            PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
            __PYX_ERR(0, 319, __pyx_L1_error)
          }
          __pyx_t_10 = PyObject_GetItem(__pyx_v_time_available, __pyx_v_ii); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 319, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_10);
          __Pyx_DECREF_SET(__pyx_v_iii, __pyx_t_10);
          __pyx_t_10 = 0;

          /* "ims_extractor.pyx":320
 *                 while ii < len(time_available):
 *                     iii = time_available[ii]
 *                     difference = (iii - time_available[ii - 1]) / 100  # fill 100 zero points between peaks instead of 5             # <<<<<<<<<<<<<<
 *                     if difference > 0.5:
 *                         difference = 0.5
 */
          if (unlikely(__pyx_v_time_available == Py_None)) {
            PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
            __PYX_ERR(0, 320, __pyx_L1_error)
          }
          __pyx_t_10 = __Pyx_PyInt_SubtractObjC(__pyx_v_ii, __pyx_int_1, 1, 0); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 320, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_10);
          __pyx_t_6 = PyObject_GetItem(__pyx_v_time_available, __pyx_t_10); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 320, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_6);
          __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
          __pyx_t_10 = PyNumber_Subtract(__pyx_v_iii, __pyx_t_6); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 320, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_10);
          __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
          __pyx_t_6 = __Pyx_PyNumber_Divide(__pyx_t_10, __pyx_int_100); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 320, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_6);
          __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
          __Pyx_XDECREF_SET(__pyx_v_difference, __pyx_t_6);
          __pyx_t_6 = 0;

          /* "ims_extractor.pyx":321
 *                     iii = time_available[ii]
 *                     difference = (iii - time_available[ii - 1]) / 100  # fill 100 zero points between peaks instead of 5
 *                     if difference > 0.5:             # <<<<<<<<<<<<<<
 *                         difference = 0.5
 *                     if difference < 0.05:
 */
          __pyx_t_6 = PyObject_RichCompare(__pyx_v_difference, __pyx_float_0_5, Py_GT); __Pyx_XGOTREF(__pyx_t_6); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 321, __pyx_L1_error)
          __pyx_t_4 = __Pyx_PyObject_IsTrue(__pyx_t_6); if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(0, 321, __pyx_L1_error)
          __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
          if (__pyx_t_4) {

            /* "ims_extractor.pyx":322
 *                     difference = (iii - time_available[ii - 1]) / 100  # fill 100 zero points between peaks instead of 5
 *                     if difference > 0.5:
 *                         difference = 0.5             # <<<<<<<<<<<<<<
 *                     if difference < 0.05:
 *                         difference = 0.05
 */
            __Pyx_INCREF(__pyx_float_0_5);
            __Pyx_DECREF_SET(__pyx_v_difference, __pyx_float_0_5);

            /* "ims_extractor.pyx":321
 *                     iii = time_available[ii]
 *                     difference = (iii - time_available[ii - 1]) / 100  # fill 100 zero points between peaks instead of 5
 *                     if difference > 0.5:             # <<<<<<<<<<<<<<
 *                         difference = 0.5
 *                     if difference < 0.05:
 */
          }

          /* "ims_extractor.pyx":323
 *                     if difference > 0.5:
 *                         difference = 0.5
 *                     if difference < 0.05:             # <<<<<<<<<<<<<<
 *                         difference = 0.05
 *                     while iii - time_available[ii - 1] > 0.1:
 */
          __pyx_t_6 = PyObject_RichCompare(__pyx_v_difference, __pyx_float_0_05, Py_LT); __Pyx_XGOTREF(__pyx_t_6); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 323, __pyx_L1_error)
          __pyx_t_4 = __Pyx_PyObject_IsTrue(__pyx_t_6); if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(0, 323, __pyx_L1_error)
          __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
          if (__pyx_t_4) {

            /* "ims_extractor.pyx":324
 *                         difference = 0.5
 *                     if difference < 0.05:
 *                         difference = 0.05             # <<<<<<<<<<<<<<
 *                     while iii - time_available[ii - 1] > 0.1:
 *                         iii -= difference
 */
            __Pyx_INCREF(__pyx_float_0_05);
            __Pyx_DECREF_SET(__pyx_v_difference, __pyx_float_0_05);

            /* "ims_extractor.pyx":323
 *                     if difference > 0.5:
 *                         difference = 0.5
 *                     if difference < 0.05:             # <<<<<<<<<<<<<<
 *                         difference = 0.05
 *                     while iii - time_available[ii - 1] > 0.1:
 */
          }

          /* "ims_extractor.pyx":325
 *                     if difference < 0.05:
 *                         difference = 0.05
 *                     while iii - time_available[ii - 1] > 0.1:             # <<<<<<<<<<<<<<
 *                         iii -= difference
 *                         zero_fill.append([xa[valid_spec[i]], 1, iii])
 */
          while (1) {
            if (unlikely(__pyx_v_time_available == Py_None)) {
              PyErr_SetString(PyExc_TypeError, "'NoneType' object is not subscriptable");
              __PYX_ERR(0, 325, __pyx_L1_error)
            }
            __pyx_t_6 = __Pyx_PyInt_SubtractObjC(__pyx_v_ii, __pyx_int_1, 1, 0); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 325, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_6);
            __pyx_t_10 = PyObject_GetItem(__pyx_v_time_available, __pyx_t_6); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 325, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_10);
            __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
            __pyx_t_6 = PyNumber_Subtract(__pyx_v_iii, __pyx_t_10); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 325, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_6);
            __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
            __pyx_t_10 = PyObject_RichCompare(__pyx_t_6, __pyx_float_0_1, Py_GT); __Pyx_XGOTREF(__pyx_t_10); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 325, __pyx_L1_error)
            __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
            __pyx_t_4 = __Pyx_PyObject_IsTrue(__pyx_t_10); if (unlikely(__pyx_t_4 < 0)) __PYX_ERR(0, 325, __pyx_L1_error)
            __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
            if (!__pyx_t_4) break;

            /* "ims_extractor.pyx":326
 *                         difference = 0.05
 *                     while iii - time_available[ii - 1] > 0.1:
 *                         iii -= difference             # <<<<<<<<<<<<<<
 *                         zero_fill.append([xa[valid_spec[i]], 1, iii])
 *                     ii += 1
 */
            __pyx_t_10 = PyNumber_InPlaceSubtract(__pyx_v_iii, __pyx_v_difference); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 326, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_10);
            __Pyx_DECREF_SET(__pyx_v_iii, __pyx_t_10);
            __pyx_t_10 = 0;

            /* "ims_extractor.pyx":327
 *                     while iii - time_available[ii - 1] > 0.1:
 *                         iii -= difference
 *                         zero_fill.append([xa[valid_spec[i]], 1, iii])             # <<<<<<<<<<<<<<
 *                     ii += 1
 * 
 */
            __pyx_t_10 = PyObject_GetItem(__pyx_v_valid_spec, __pyx_v_i); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 327, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_10);
            __pyx_t_6 = PyObject_GetItem(__pyx_v_xa, __pyx_t_10); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 327, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_6);
            __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
            __pyx_t_10 = PyList_New(3); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 327, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_10);
            __Pyx_GIVEREF(__pyx_t_6);
            PyList_SET_ITEM(__pyx_t_10, 0, __pyx_t_6);
            __Pyx_INCREF(__pyx_int_1);
            __Pyx_GIVEREF(__pyx_int_1);
            PyList_SET_ITEM(__pyx_t_10, 1, __pyx_int_1);
            __Pyx_INCREF(__pyx_v_iii);
            __Pyx_GIVEREF(__pyx_v_iii);
            PyList_SET_ITEM(__pyx_t_10, 2, __pyx_v_iii);
            __pyx_t_6 = 0;
            __pyx_t_5 = __Pyx_PyList_Append(__pyx_v_zero_fill, __pyx_t_10); if (unlikely(__pyx_t_5 == -1)) __PYX_ERR(0, 327, __pyx_L1_error)
            __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
          }

          /* "ims_extractor.pyx":328
 *                         iii -= difference
 *                         zero_fill.append([xa[valid_spec[i]], 1, iii])
 *                     ii += 1             # <<<<<<<<<<<<<<
 * 
 *                 zero_fill_flat = [item for sublist in zero_fill for item in sublist]
 */
          __pyx_t_10 = __Pyx_PyInt_AddObjC(__pyx_v_ii, __pyx_int_1, 1, 1); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 328, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_10);
          __Pyx_DECREF_SET(__pyx_v_ii, __pyx_t_10);
          __pyx_t_10 = 0;
        }

        /* "ims_extractor.pyx":330
 *                     ii += 1
 * 
 *                 zero_fill_flat = [item for sublist in zero_fill for item in sublist]             # <<<<<<<<<<<<<<
 * 
 *                 total_spec = len(datax[valid_spec[i]]) + len(zero_fill_flat)
 */
        __pyx_t_10 = PyList_New(0); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 330, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_10);
        __pyx_t_6 = __pyx_v_zero_fill; __Pyx_INCREF(__pyx_t_6); __pyx_t_7 = 0;
        for (;;) {
          if (__pyx_t_7 >= PyList_GET_SIZE(__pyx_t_6)) break;
          #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
          __pyx_t_1 = PyList_GET_ITEM(__pyx_t_6, __pyx_t_7); __Pyx_INCREF(__pyx_t_1); __pyx_t_7++; if (unlikely(0 < 0)) __PYX_ERR(0, 330, __pyx_L1_error)
          #else
          __pyx_t_1 = PySequence_ITEM(__pyx_t_6, __pyx_t_7); __pyx_t_7++; if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 330, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_1);
          #endif
          __Pyx_XDECREF_SET(__pyx_v_sublist, __pyx_t_1);
          __pyx_t_1 = 0;
          if (likely(PyList_CheckExact(__pyx_v_sublist)) || PyTuple_CheckExact(__pyx_v_sublist)) {
            __pyx_t_1 = __pyx_v_sublist; __Pyx_INCREF(__pyx_t_1); __pyx_t_16 = 0;
            __pyx_t_8 = NULL;
          } else {
            __pyx_t_16 = -1; __pyx_t_1 = PyObject_GetIter(__pyx_v_sublist); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 330, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_1);
            __pyx_t_8 = Py_TYPE(__pyx_t_1)->tp_iternext; if (unlikely(!__pyx_t_8)) __PYX_ERR(0, 330, __pyx_L1_error)
          }
          for (;;) {
            if (likely(!__pyx_t_8)) {
              if (likely(PyList_CheckExact(__pyx_t_1))) {
                if (__pyx_t_16 >= PyList_GET_SIZE(__pyx_t_1)) break;
                #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
                __pyx_t_17 = PyList_GET_ITEM(__pyx_t_1, __pyx_t_16); __Pyx_INCREF(__pyx_t_17); __pyx_t_16++; if (unlikely(0 < 0)) __PYX_ERR(0, 330, __pyx_L1_error)
                #else
                __pyx_t_17 = PySequence_ITEM(__pyx_t_1, __pyx_t_16); __pyx_t_16++; if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 330, __pyx_L1_error)
                __Pyx_GOTREF(__pyx_t_17);
                #endif
              } else {
                if (__pyx_t_16 >= PyTuple_GET_SIZE(__pyx_t_1)) break;
                #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
                __pyx_t_17 = PyTuple_GET_ITEM(__pyx_t_1, __pyx_t_16); __Pyx_INCREF(__pyx_t_17); __pyx_t_16++; if (unlikely(0 < 0)) __PYX_ERR(0, 330, __pyx_L1_error)
                #else
                __pyx_t_17 = PySequence_ITEM(__pyx_t_1, __pyx_t_16); __pyx_t_16++; if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 330, __pyx_L1_error)
                __Pyx_GOTREF(__pyx_t_17);
                #endif
              }
            } else {
              __pyx_t_17 = __pyx_t_8(__pyx_t_1);
              if (unlikely(!__pyx_t_17)) {
                PyObject* exc_type = PyErr_Occurred();
                if (exc_type) {
                  if (likely(exc_type == PyExc_StopIteration || PyErr_GivenExceptionMatches(exc_type, PyExc_StopIteration))) PyErr_Clear();
                  else __PYX_ERR(0, 330, __pyx_L1_error)
                }
                break;
              }
              __Pyx_GOTREF(__pyx_t_17);
            }
            __Pyx_XDECREF_SET(__pyx_v_item, __pyx_t_17);
            __pyx_t_17 = 0;
            if (unlikely(__Pyx_ListComp_Append(__pyx_t_10, (PyObject*)__pyx_v_item))) __PYX_ERR(0, 330, __pyx_L1_error)
          }
          __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
        }
        __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
        __Pyx_XDECREF_SET(__pyx_v_zero_fill_flat, ((PyObject*)__pyx_t_10));
        __pyx_t_10 = 0;

        /* "ims_extractor.pyx":332
 *                 zero_fill_flat = [item for sublist in zero_fill for item in sublist]
 * 
 *                 total_spec = len(datax[valid_spec[i]]) + len(zero_fill_flat)             # <<<<<<<<<<<<<<
 * 
 *                 # filter out all bins that contains little data, 66 means 22 points
 */
        __pyx_t_10 = PyObject_GetItem(__pyx_v_valid_spec, __pyx_v_i); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 332, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_10);
        __pyx_t_6 = PyObject_GetItem(__pyx_v_datax, __pyx_t_10); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 332, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_6);
        __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
        __pyx_t_7 = PyObject_Length(__pyx_t_6); if (unlikely(__pyx_t_7 == -1)) __PYX_ERR(0, 332, __pyx_L1_error)
        __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
        __pyx_t_16 = PyList_GET_SIZE(__pyx_v_zero_fill_flat); if (unlikely(__pyx_t_16 == -1)) __PYX_ERR(0, 332, __pyx_L1_error)
        __pyx_v_total_spec = (__pyx_t_7 + __pyx_t_16);

        /* "ims_extractor.pyx":336
 *                 # filter out all bins that contains little data, 66 means 22 points
 *                 # print mass_center[valid_spec[i]]
 *                 floatarray3 = array('f', [mass_center[valid_spec[i]], total_spec, log(intensity_dict[valid_spec[i]])])             # <<<<<<<<<<<<<<
 *                 # print xa[valid_spec[i]],mass_center[valid_spec[i]]
 *                 # first generate header [m/z number_of_point*3 log_value_of_total_intensity]
 */
        __pyx_t_10 = __Pyx_GetModuleGlobalName(__pyx_n_s_array); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 336, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_10);
        __pyx_t_1 = PyObject_GetItem(__pyx_v_valid_spec, __pyx_v_i); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 336, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        __pyx_t_17 = __Pyx_PyDict_GetItem(__pyx_v_mass_center, __pyx_t_1); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 336, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_17);
        __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
        __pyx_t_1 = PyInt_FromSsize_t(__pyx_v_total_spec); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 336, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_log); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 336, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_2);
        __pyx_t_18 = PyObject_GetItem(__pyx_v_valid_spec, __pyx_v_i); if (unlikely(!__pyx_t_18)) __PYX_ERR(0, 336, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_18);
        __pyx_t_19 = __Pyx_PyDict_GetItem(__pyx_v_intensity_dict, __pyx_t_18); if (unlikely(!__pyx_t_19)) __PYX_ERR(0, 336, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_19);
        __Pyx_DECREF(__pyx_t_18); __pyx_t_18 = 0;
        __pyx_t_18 = NULL;
        if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_2))) {
          __pyx_t_18 = PyMethod_GET_SELF(__pyx_t_2);
          if (likely(__pyx_t_18)) {
            PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
            __Pyx_INCREF(__pyx_t_18);
            __Pyx_INCREF(function);
            __Pyx_DECREF_SET(__pyx_t_2, function);
          }
        }
        if (!__pyx_t_18) {
          __pyx_t_3 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_t_19); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 336, __pyx_L1_error)
          __Pyx_DECREF(__pyx_t_19); __pyx_t_19 = 0;
          __Pyx_GOTREF(__pyx_t_3);
        } else {
          #if CYTHON_FAST_PYCALL
          if (PyFunction_Check(__pyx_t_2)) {
            PyObject *__pyx_temp[2] = {__pyx_t_18, __pyx_t_19};
            __pyx_t_3 = __Pyx_PyFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 336, __pyx_L1_error)
            __Pyx_XDECREF(__pyx_t_18); __pyx_t_18 = 0;
            __Pyx_GOTREF(__pyx_t_3);
            __Pyx_DECREF(__pyx_t_19); __pyx_t_19 = 0;
          } else
          #endif
          #if CYTHON_FAST_PYCCALL
          if (__Pyx_PyFastCFunction_Check(__pyx_t_2)) {
            PyObject *__pyx_temp[2] = {__pyx_t_18, __pyx_t_19};
            __pyx_t_3 = __Pyx_PyCFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 336, __pyx_L1_error)
            __Pyx_XDECREF(__pyx_t_18); __pyx_t_18 = 0;
            __Pyx_GOTREF(__pyx_t_3);
            __Pyx_DECREF(__pyx_t_19); __pyx_t_19 = 0;
          } else
          #endif
          {
            __pyx_t_20 = PyTuple_New(1+1); if (unlikely(!__pyx_t_20)) __PYX_ERR(0, 336, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_20);
            __Pyx_GIVEREF(__pyx_t_18); PyTuple_SET_ITEM(__pyx_t_20, 0, __pyx_t_18); __pyx_t_18 = NULL;
            __Pyx_GIVEREF(__pyx_t_19);
            PyTuple_SET_ITEM(__pyx_t_20, 0+1, __pyx_t_19);
            __pyx_t_19 = 0;
            __pyx_t_3 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_20, NULL); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 336, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_3);
            __Pyx_DECREF(__pyx_t_20); __pyx_t_20 = 0;
          }
        }
        __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
        __pyx_t_2 = PyList_New(3); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 336, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_2);
        __Pyx_GIVEREF(__pyx_t_17);
        PyList_SET_ITEM(__pyx_t_2, 0, __pyx_t_17);
        __Pyx_GIVEREF(__pyx_t_1);
        PyList_SET_ITEM(__pyx_t_2, 1, __pyx_t_1);
        __Pyx_GIVEREF(__pyx_t_3);
        PyList_SET_ITEM(__pyx_t_2, 2, __pyx_t_3);
        __pyx_t_17 = 0;
        __pyx_t_1 = 0;
        __pyx_t_3 = 0;
        __pyx_t_3 = NULL;
        __pyx_t_21 = 0;
        if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_10))) {
          __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_10);
          if (likely(__pyx_t_3)) {
            PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_10);
            __Pyx_INCREF(__pyx_t_3);
            __Pyx_INCREF(function);
            __Pyx_DECREF_SET(__pyx_t_10, function);
            __pyx_t_21 = 1;
          }
        }
        #if CYTHON_FAST_PYCALL
        if (PyFunction_Check(__pyx_t_10)) {
          PyObject *__pyx_temp[3] = {__pyx_t_3, __pyx_n_s_f, __pyx_t_2};
          __pyx_t_6 = __Pyx_PyFunction_FastCall(__pyx_t_10, __pyx_temp+1-__pyx_t_21, 2+__pyx_t_21); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 336, __pyx_L1_error)
          __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
          __Pyx_GOTREF(__pyx_t_6);
          __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
        } else
        #endif
        #if CYTHON_FAST_PYCCALL
        if (__Pyx_PyFastCFunction_Check(__pyx_t_10)) {
          PyObject *__pyx_temp[3] = {__pyx_t_3, __pyx_n_s_f, __pyx_t_2};
          __pyx_t_6 = __Pyx_PyCFunction_FastCall(__pyx_t_10, __pyx_temp+1-__pyx_t_21, 2+__pyx_t_21); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 336, __pyx_L1_error)
          __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
          __Pyx_GOTREF(__pyx_t_6);
          __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
        } else
        #endif
        {
          __pyx_t_1 = PyTuple_New(2+__pyx_t_21); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 336, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_1);
          if (__pyx_t_3) {
            __Pyx_GIVEREF(__pyx_t_3); PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_t_3); __pyx_t_3 = NULL;
          }
          __Pyx_INCREF(__pyx_n_s_f);
          __Pyx_GIVEREF(__pyx_n_s_f);
          PyTuple_SET_ITEM(__pyx_t_1, 0+__pyx_t_21, __pyx_n_s_f);
          __Pyx_GIVEREF(__pyx_t_2);
          PyTuple_SET_ITEM(__pyx_t_1, 1+__pyx_t_21, __pyx_t_2);
          __pyx_t_2 = 0;
          __pyx_t_6 = __Pyx_PyObject_Call(__pyx_t_10, __pyx_t_1, NULL); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 336, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_6);
          __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
        }
        __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
        __Pyx_XDECREF_SET(__pyx_v_floatarray3, __pyx_t_6);
        __pyx_t_6 = 0;

        /* "ims_extractor.pyx":339
 *                 # print xa[valid_spec[i]],mass_center[valid_spec[i]]
 *                 # first generate header [m/z number_of_point*3 log_value_of_total_intensity]
 *                 b.append([str(len(datax[valid_spec[i]])), str(valid_spec[i]), str(log(intensity_dict[valid_spec[i]]))])             # <<<<<<<<<<<<<<
 *                 # b.append([str(len(datax[valid_spec[i]])), str(valid_spec[i]), str(a[valid_spec[i]])])
 * 
 */
        __pyx_t_6 = PyObject_GetItem(__pyx_v_valid_spec, __pyx_v_i); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 339, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_6);
        __pyx_t_10 = PyObject_GetItem(__pyx_v_datax, __pyx_t_6); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 339, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_10);
        __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
        __pyx_t_16 = PyObject_Length(__pyx_t_10); if (unlikely(__pyx_t_16 == -1)) __PYX_ERR(0, 339, __pyx_L1_error)
        __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
        __pyx_t_10 = PyInt_FromSsize_t(__pyx_t_16); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 339, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_10);
        __pyx_t_6 = PyTuple_New(1); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 339, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_6);
        __Pyx_GIVEREF(__pyx_t_10);
        PyTuple_SET_ITEM(__pyx_t_6, 0, __pyx_t_10);
        __pyx_t_10 = 0;
        __pyx_t_10 = __Pyx_PyObject_Call(((PyObject *)(&PyString_Type)), __pyx_t_6, NULL); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 339, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_10);
        __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
        __pyx_t_6 = PyObject_GetItem(__pyx_v_valid_spec, __pyx_v_i); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 339, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_6);
        __pyx_t_1 = PyTuple_New(1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 339, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        __Pyx_GIVEREF(__pyx_t_6);
        PyTuple_SET_ITEM(__pyx_t_1, 0, __pyx_t_6);
        __pyx_t_6 = 0;
        __pyx_t_6 = __Pyx_PyObject_Call(((PyObject *)(&PyString_Type)), __pyx_t_1, NULL); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 339, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_6);
        __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
        __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_log); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 339, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_2);
        __pyx_t_3 = PyObject_GetItem(__pyx_v_valid_spec, __pyx_v_i); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 339, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __pyx_t_17 = __Pyx_PyDict_GetItem(__pyx_v_intensity_dict, __pyx_t_3); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 339, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_17);
        __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
        __pyx_t_3 = NULL;
        if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_2))) {
          __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_2);
          if (likely(__pyx_t_3)) {
            PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
            __Pyx_INCREF(__pyx_t_3);
            __Pyx_INCREF(function);
            __Pyx_DECREF_SET(__pyx_t_2, function);
          }
        }
        if (!__pyx_t_3) {
          __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_t_17); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 339, __pyx_L1_error)
          __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
          __Pyx_GOTREF(__pyx_t_1);
        } else {
          #if CYTHON_FAST_PYCALL
          if (PyFunction_Check(__pyx_t_2)) {
            PyObject *__pyx_temp[2] = {__pyx_t_3, __pyx_t_17};
            __pyx_t_1 = __Pyx_PyFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 339, __pyx_L1_error)
            __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
            __Pyx_GOTREF(__pyx_t_1);
            __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
          } else
          #endif
          #if CYTHON_FAST_PYCCALL
          if (__Pyx_PyFastCFunction_Check(__pyx_t_2)) {
            PyObject *__pyx_temp[2] = {__pyx_t_3, __pyx_t_17};
            __pyx_t_1 = __Pyx_PyCFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 339, __pyx_L1_error)
            __Pyx_XDECREF(__pyx_t_3); __pyx_t_3 = 0;
            __Pyx_GOTREF(__pyx_t_1);
            __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
          } else
          #endif
          {
            __pyx_t_20 = PyTuple_New(1+1); if (unlikely(!__pyx_t_20)) __PYX_ERR(0, 339, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_20);
            __Pyx_GIVEREF(__pyx_t_3); PyTuple_SET_ITEM(__pyx_t_20, 0, __pyx_t_3); __pyx_t_3 = NULL;
            __Pyx_GIVEREF(__pyx_t_17);
            PyTuple_SET_ITEM(__pyx_t_20, 0+1, __pyx_t_17);
            __pyx_t_17 = 0;
            __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_20, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 339, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_1);
            __Pyx_DECREF(__pyx_t_20); __pyx_t_20 = 0;
          }
        }
        __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
        __pyx_t_2 = PyTuple_New(1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 339, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_2);
        __Pyx_GIVEREF(__pyx_t_1);
        PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_t_1);
        __pyx_t_1 = 0;
        __pyx_t_1 = __Pyx_PyObject_Call(((PyObject *)(&PyString_Type)), __pyx_t_2, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 339, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
        __pyx_t_2 = PyList_New(3); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 339, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_2);
        __Pyx_GIVEREF(__pyx_t_10);
        PyList_SET_ITEM(__pyx_t_2, 0, __pyx_t_10);
        __Pyx_GIVEREF(__pyx_t_6);
        PyList_SET_ITEM(__pyx_t_2, 1, __pyx_t_6);
        __Pyx_GIVEREF(__pyx_t_1);
        PyList_SET_ITEM(__pyx_t_2, 2, __pyx_t_1);
        __pyx_t_10 = 0;
        __pyx_t_6 = 0;
        __pyx_t_1 = 0;
        __pyx_t_5 = __Pyx_PyList_Append(__pyx_v_b, __pyx_t_2); if (unlikely(__pyx_t_5 == -1)) __PYX_ERR(0, 339, __pyx_L1_error)
        __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

        /* "ims_extractor.pyx":342
 *                 # b.append([str(len(datax[valid_spec[i]])), str(valid_spec[i]), str(a[valid_spec[i]])])
 * 
 *                 floatarray = array('f', datax[valid_spec[i]])  # now generate all the data [m/z intensity ret_time]....             # <<<<<<<<<<<<<<
 *                 floatarray2 = array('f', zero_fill_flat)
 *                 # floatarray2=array('f',datat)
 */
        __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_array); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 342, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        __pyx_t_6 = PyObject_GetItem(__pyx_v_valid_spec, __pyx_v_i); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 342, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_6);
        __pyx_t_10 = PyObject_GetItem(__pyx_v_datax, __pyx_t_6); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 342, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_10);
        __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
        __pyx_t_6 = NULL;
        __pyx_t_21 = 0;
        if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_1))) {
          __pyx_t_6 = PyMethod_GET_SELF(__pyx_t_1);
          if (likely(__pyx_t_6)) {
            PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_1);
            __Pyx_INCREF(__pyx_t_6);
            __Pyx_INCREF(function);
            __Pyx_DECREF_SET(__pyx_t_1, function);
            __pyx_t_21 = 1;
          }
        }
        #if CYTHON_FAST_PYCALL
        if (PyFunction_Check(__pyx_t_1)) {
          PyObject *__pyx_temp[3] = {__pyx_t_6, __pyx_n_s_f, __pyx_t_10};
          __pyx_t_2 = __Pyx_PyFunction_FastCall(__pyx_t_1, __pyx_temp+1-__pyx_t_21, 2+__pyx_t_21); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 342, __pyx_L1_error)
          __Pyx_XDECREF(__pyx_t_6); __pyx_t_6 = 0;
          __Pyx_GOTREF(__pyx_t_2);
          __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
        } else
        #endif
        #if CYTHON_FAST_PYCCALL
        if (__Pyx_PyFastCFunction_Check(__pyx_t_1)) {
          PyObject *__pyx_temp[3] = {__pyx_t_6, __pyx_n_s_f, __pyx_t_10};
          __pyx_t_2 = __Pyx_PyCFunction_FastCall(__pyx_t_1, __pyx_temp+1-__pyx_t_21, 2+__pyx_t_21); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 342, __pyx_L1_error)
          __Pyx_XDECREF(__pyx_t_6); __pyx_t_6 = 0;
          __Pyx_GOTREF(__pyx_t_2);
          __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
        } else
        #endif
        {
          __pyx_t_20 = PyTuple_New(2+__pyx_t_21); if (unlikely(!__pyx_t_20)) __PYX_ERR(0, 342, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_20);
          if (__pyx_t_6) {
            __Pyx_GIVEREF(__pyx_t_6); PyTuple_SET_ITEM(__pyx_t_20, 0, __pyx_t_6); __pyx_t_6 = NULL;
          }
          __Pyx_INCREF(__pyx_n_s_f);
          __Pyx_GIVEREF(__pyx_n_s_f);
          PyTuple_SET_ITEM(__pyx_t_20, 0+__pyx_t_21, __pyx_n_s_f);
          __Pyx_GIVEREF(__pyx_t_10);
          PyTuple_SET_ITEM(__pyx_t_20, 1+__pyx_t_21, __pyx_t_10);
          __pyx_t_10 = 0;
          __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_20, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 342, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_2);
          __Pyx_DECREF(__pyx_t_20); __pyx_t_20 = 0;
        }
        __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
        __Pyx_XDECREF_SET(__pyx_v_floatarray, __pyx_t_2);
        __pyx_t_2 = 0;

        /* "ims_extractor.pyx":343
 * 
 *                 floatarray = array('f', datax[valid_spec[i]])  # now generate all the data [m/z intensity ret_time]....
 *                 floatarray2 = array('f', zero_fill_flat)             # <<<<<<<<<<<<<<
 *                 # floatarray2=array('f',datat)
 *                 floatarray3.tofile(file2)
 */
        __pyx_t_1 = __Pyx_GetModuleGlobalName(__pyx_n_s_array); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 343, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        __pyx_t_20 = NULL;
        __pyx_t_21 = 0;
        if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_1))) {
          __pyx_t_20 = PyMethod_GET_SELF(__pyx_t_1);
          if (likely(__pyx_t_20)) {
            PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_1);
            __Pyx_INCREF(__pyx_t_20);
            __Pyx_INCREF(function);
            __Pyx_DECREF_SET(__pyx_t_1, function);
            __pyx_t_21 = 1;
          }
        }
        #if CYTHON_FAST_PYCALL
        if (PyFunction_Check(__pyx_t_1)) {
          PyObject *__pyx_temp[3] = {__pyx_t_20, __pyx_n_s_f, __pyx_v_zero_fill_flat};
          __pyx_t_2 = __Pyx_PyFunction_FastCall(__pyx_t_1, __pyx_temp+1-__pyx_t_21, 2+__pyx_t_21); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 343, __pyx_L1_error)
          __Pyx_XDECREF(__pyx_t_20); __pyx_t_20 = 0;
          __Pyx_GOTREF(__pyx_t_2);
        } else
        #endif
        #if CYTHON_FAST_PYCCALL
        if (__Pyx_PyFastCFunction_Check(__pyx_t_1)) {
          PyObject *__pyx_temp[3] = {__pyx_t_20, __pyx_n_s_f, __pyx_v_zero_fill_flat};
          __pyx_t_2 = __Pyx_PyCFunction_FastCall(__pyx_t_1, __pyx_temp+1-__pyx_t_21, 2+__pyx_t_21); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 343, __pyx_L1_error)
          __Pyx_XDECREF(__pyx_t_20); __pyx_t_20 = 0;
          __Pyx_GOTREF(__pyx_t_2);
        } else
        #endif
        {
          __pyx_t_10 = PyTuple_New(2+__pyx_t_21); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 343, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_10);
          if (__pyx_t_20) {
            __Pyx_GIVEREF(__pyx_t_20); PyTuple_SET_ITEM(__pyx_t_10, 0, __pyx_t_20); __pyx_t_20 = NULL;
          }
          __Pyx_INCREF(__pyx_n_s_f);
          __Pyx_GIVEREF(__pyx_n_s_f);
          PyTuple_SET_ITEM(__pyx_t_10, 0+__pyx_t_21, __pyx_n_s_f);
          __Pyx_INCREF(__pyx_v_zero_fill_flat);
          __Pyx_GIVEREF(__pyx_v_zero_fill_flat);
          PyTuple_SET_ITEM(__pyx_t_10, 1+__pyx_t_21, __pyx_v_zero_fill_flat);
          __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_10, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 343, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_2);
          __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
        }
        __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
        __Pyx_XDECREF_SET(__pyx_v_floatarray2, __pyx_t_2);
        __pyx_t_2 = 0;

        /* "ims_extractor.pyx":345
 *                 floatarray2 = array('f', zero_fill_flat)
 *                 # floatarray2=array('f',datat)
 *                 floatarray3.tofile(file2)             # <<<<<<<<<<<<<<
 *                 floatarray.tofile(file2)
 *                 floatarray2.tofile(file2)
 */
        __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_floatarray3, __pyx_n_s_tofile); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 345, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        __pyx_t_10 = NULL;
        if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_1))) {
          __pyx_t_10 = PyMethod_GET_SELF(__pyx_t_1);
          if (likely(__pyx_t_10)) {
            PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_1);
            __Pyx_INCREF(__pyx_t_10);
            __Pyx_INCREF(function);
            __Pyx_DECREF_SET(__pyx_t_1, function);
          }
        }
        if (!__pyx_t_10) {
          __pyx_t_2 = __Pyx_PyObject_CallOneArg(__pyx_t_1, __pyx_v_file2); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 345, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_2);
        } else {
          #if CYTHON_FAST_PYCALL
          if (PyFunction_Check(__pyx_t_1)) {
            PyObject *__pyx_temp[2] = {__pyx_t_10, __pyx_v_file2};
            __pyx_t_2 = __Pyx_PyFunction_FastCall(__pyx_t_1, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 345, __pyx_L1_error)
            __Pyx_XDECREF(__pyx_t_10); __pyx_t_10 = 0;
            __Pyx_GOTREF(__pyx_t_2);
          } else
          #endif
          #if CYTHON_FAST_PYCCALL
          if (__Pyx_PyFastCFunction_Check(__pyx_t_1)) {
            PyObject *__pyx_temp[2] = {__pyx_t_10, __pyx_v_file2};
            __pyx_t_2 = __Pyx_PyCFunction_FastCall(__pyx_t_1, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 345, __pyx_L1_error)
            __Pyx_XDECREF(__pyx_t_10); __pyx_t_10 = 0;
            __Pyx_GOTREF(__pyx_t_2);
          } else
          #endif
          {
            __pyx_t_20 = PyTuple_New(1+1); if (unlikely(!__pyx_t_20)) __PYX_ERR(0, 345, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_20);
            __Pyx_GIVEREF(__pyx_t_10); PyTuple_SET_ITEM(__pyx_t_20, 0, __pyx_t_10); __pyx_t_10 = NULL;
            __Pyx_INCREF(__pyx_v_file2);
            __Pyx_GIVEREF(__pyx_v_file2);
            PyTuple_SET_ITEM(__pyx_t_20, 0+1, __pyx_v_file2);
            __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_20, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 345, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_2);
            __Pyx_DECREF(__pyx_t_20); __pyx_t_20 = 0;
          }
        }
        __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
        __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

        /* "ims_extractor.pyx":346
 *                 # floatarray2=array('f',datat)
 *                 floatarray3.tofile(file2)
 *                 floatarray.tofile(file2)             # <<<<<<<<<<<<<<
 *                 floatarray2.tofile(file2)
 *                 # floatarray2.tofile(file2)
 */
        __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_floatarray, __pyx_n_s_tofile); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 346, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        __pyx_t_20 = NULL;
        if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_1))) {
          __pyx_t_20 = PyMethod_GET_SELF(__pyx_t_1);
          if (likely(__pyx_t_20)) {
            PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_1);
            __Pyx_INCREF(__pyx_t_20);
            __Pyx_INCREF(function);
            __Pyx_DECREF_SET(__pyx_t_1, function);
          }
        }
        if (!__pyx_t_20) {
          __pyx_t_2 = __Pyx_PyObject_CallOneArg(__pyx_t_1, __pyx_v_file2); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 346, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_2);
        } else {
          #if CYTHON_FAST_PYCALL
          if (PyFunction_Check(__pyx_t_1)) {
            PyObject *__pyx_temp[2] = {__pyx_t_20, __pyx_v_file2};
            __pyx_t_2 = __Pyx_PyFunction_FastCall(__pyx_t_1, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 346, __pyx_L1_error)
            __Pyx_XDECREF(__pyx_t_20); __pyx_t_20 = 0;
            __Pyx_GOTREF(__pyx_t_2);
          } else
          #endif
          #if CYTHON_FAST_PYCCALL
          if (__Pyx_PyFastCFunction_Check(__pyx_t_1)) {
            PyObject *__pyx_temp[2] = {__pyx_t_20, __pyx_v_file2};
            __pyx_t_2 = __Pyx_PyCFunction_FastCall(__pyx_t_1, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 346, __pyx_L1_error)
            __Pyx_XDECREF(__pyx_t_20); __pyx_t_20 = 0;
            __Pyx_GOTREF(__pyx_t_2);
          } else
          #endif
          {
            __pyx_t_10 = PyTuple_New(1+1); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 346, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_10);
            __Pyx_GIVEREF(__pyx_t_20); PyTuple_SET_ITEM(__pyx_t_10, 0, __pyx_t_20); __pyx_t_20 = NULL;
            __Pyx_INCREF(__pyx_v_file2);
            __Pyx_GIVEREF(__pyx_v_file2);
            PyTuple_SET_ITEM(__pyx_t_10, 0+1, __pyx_v_file2);
            __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_10, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 346, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_2);
            __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
          }
        }
        __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
        __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

        /* "ims_extractor.pyx":347
 *                 floatarray3.tofile(file2)
 *                 floatarray.tofile(file2)
 *                 floatarray2.tofile(file2)             # <<<<<<<<<<<<<<
 *                 # floatarray2.tofile(file2)
 *             i += 1
 */
        __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_floatarray2, __pyx_n_s_tofile); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 347, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        __pyx_t_10 = NULL;
        if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_1))) {
          __pyx_t_10 = PyMethod_GET_SELF(__pyx_t_1);
          if (likely(__pyx_t_10)) {
            PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_1);
            __Pyx_INCREF(__pyx_t_10);
            __Pyx_INCREF(function);
            __Pyx_DECREF_SET(__pyx_t_1, function);
          }
        }
        if (!__pyx_t_10) {
          __pyx_t_2 = __Pyx_PyObject_CallOneArg(__pyx_t_1, __pyx_v_file2); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 347, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_2);
        } else {
          #if CYTHON_FAST_PYCALL
          if (PyFunction_Check(__pyx_t_1)) {
            PyObject *__pyx_temp[2] = {__pyx_t_10, __pyx_v_file2};
            __pyx_t_2 = __Pyx_PyFunction_FastCall(__pyx_t_1, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 347, __pyx_L1_error)
            __Pyx_XDECREF(__pyx_t_10); __pyx_t_10 = 0;
            __Pyx_GOTREF(__pyx_t_2);
          } else
          #endif
          #if CYTHON_FAST_PYCCALL
          if (__Pyx_PyFastCFunction_Check(__pyx_t_1)) {
            PyObject *__pyx_temp[2] = {__pyx_t_10, __pyx_v_file2};
            __pyx_t_2 = __Pyx_PyCFunction_FastCall(__pyx_t_1, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 347, __pyx_L1_error)
            __Pyx_XDECREF(__pyx_t_10); __pyx_t_10 = 0;
            __Pyx_GOTREF(__pyx_t_2);
          } else
          #endif
          {
            __pyx_t_20 = PyTuple_New(1+1); if (unlikely(!__pyx_t_20)) __PYX_ERR(0, 347, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_20);
            __Pyx_GIVEREF(__pyx_t_10); PyTuple_SET_ITEM(__pyx_t_20, 0, __pyx_t_10); __pyx_t_10 = NULL;
            __Pyx_INCREF(__pyx_v_file2);
            __Pyx_GIVEREF(__pyx_v_file2);
            PyTuple_SET_ITEM(__pyx_t_20, 0+1, __pyx_v_file2);
            __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_1, __pyx_t_20, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 347, __pyx_L1_error)
            __Pyx_GOTREF(__pyx_t_2);
            __Pyx_DECREF(__pyx_t_20); __pyx_t_20 = 0;
          }
        }
        __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
        __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

        /* "ims_extractor.pyx":299
 *         # print len(datax[1]), len(datax[2]), len(datax[3]), len(datax[4]), len(datax[5]), len(datax[6]), len(datax[7])
 *         while i < len(valid_spec):  # write the whole array in ims format
 *             if len(datax[valid_spec[i]]) > 33:             # <<<<<<<<<<<<<<
 *                 ii = 2
 *                 zero_fill = []
 */
      }

      /* "ims_extractor.pyx":349
 *                 floatarray2.tofile(file2)
 *                 # floatarray2.tofile(file2)
 *             i += 1             # <<<<<<<<<<<<<<
 * 
 *         file2.close()
 */
      __pyx_t_2 = __Pyx_PyInt_AddObjC(__pyx_v_i, __pyx_int_1, 1, 1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 349, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      __Pyx_DECREF_SET(__pyx_v_i, __pyx_t_2);
      __pyx_t_2 = 0;
    }

    /* "ims_extractor.pyx":351
 *             i += 1
 * 
 *         file2.close()             # <<<<<<<<<<<<<<
 *         # print datax[2387549],len(datax[2387549])#, log(intensity_dict[2387552])
 * 
 */
    __pyx_t_1 = __Pyx_PyObject_GetAttrStr(__pyx_v_file2, __pyx_n_s_close); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 351, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __pyx_t_20 = NULL;
    if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_1))) {
      __pyx_t_20 = PyMethod_GET_SELF(__pyx_t_1);
      if (likely(__pyx_t_20)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_1);
        __Pyx_INCREF(__pyx_t_20);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_1, function);
      }
    }
    if (__pyx_t_20) {
      __pyx_t_2 = __Pyx_PyObject_CallOneArg(__pyx_t_1, __pyx_t_20); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 351, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_20); __pyx_t_20 = 0;
    } else {
      __pyx_t_2 = __Pyx_PyObject_CallNoArg(__pyx_t_1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 351, __pyx_L1_error)
    }
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

    /* "ims_extractor.pyx":354
 *         # print datax[2387549],len(datax[2387549])#, log(intensity_dict[2387552])
 * 
 *         file3 = open(file_name_freq, 'w')             # <<<<<<<<<<<<<<
 *         # floatarray2=array('f',a)
 *         # floatarray2=array('f',datat)
 */
    __pyx_t_2 = PyTuple_New(2); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 354, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __Pyx_INCREF(__pyx_v_file_name_freq);
    __Pyx_GIVEREF(__pyx_v_file_name_freq);
    PyTuple_SET_ITEM(__pyx_t_2, 0, __pyx_v_file_name_freq);
    __Pyx_INCREF(__pyx_n_s_w);
    __Pyx_GIVEREF(__pyx_n_s_w);
    PyTuple_SET_ITEM(__pyx_t_2, 1, __pyx_n_s_w);
    __pyx_t_1 = __Pyx_PyObject_Call(__pyx_builtin_open, __pyx_t_2, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 354, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_v_file3 = __pyx_t_1;
    __pyx_t_1 = 0;

    /* "ims_extractor.pyx":361
 *         # print len(datax[90]),datax[90]
 * 
 *         for item in b:             # <<<<<<<<<<<<<<
 *             file3.write(",".join(item) + "\n")
 *         file3.write("TIC: %f\n" % log(tic))
 */
    __pyx_t_1 = __pyx_v_b; __Pyx_INCREF(__pyx_t_1); __pyx_t_16 = 0;
    for (;;) {
      if (__pyx_t_16 >= PyList_GET_SIZE(__pyx_t_1)) break;
      #if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
      __pyx_t_2 = PyList_GET_ITEM(__pyx_t_1, __pyx_t_16); __Pyx_INCREF(__pyx_t_2); __pyx_t_16++; if (unlikely(0 < 0)) __PYX_ERR(0, 361, __pyx_L1_error)
      #else
      __pyx_t_2 = PySequence_ITEM(__pyx_t_1, __pyx_t_16); __pyx_t_16++; if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 361, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_2);
      #endif
      __Pyx_XDECREF_SET(__pyx_v_item, __pyx_t_2);
      __pyx_t_2 = 0;

      /* "ims_extractor.pyx":362
 * 
 *         for item in b:
 *             file3.write(",".join(item) + "\n")             # <<<<<<<<<<<<<<
 *         file3.write("TIC: %f\n" % log(tic))
 *         file3.close()
 */
      __pyx_t_20 = __Pyx_PyObject_GetAttrStr(__pyx_v_file3, __pyx_n_s_write); if (unlikely(!__pyx_t_20)) __PYX_ERR(0, 362, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_20);
      __pyx_t_10 = __Pyx_PyString_Join(__pyx_kp_s__25, __pyx_v_item); if (unlikely(!__pyx_t_10)) __PYX_ERR(0, 362, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_10);
      __pyx_t_6 = PyNumber_Add(__pyx_t_10, __pyx_kp_s__5); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 362, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_6);
      __Pyx_DECREF(__pyx_t_10); __pyx_t_10 = 0;
      __pyx_t_10 = NULL;
      if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_20))) {
        __pyx_t_10 = PyMethod_GET_SELF(__pyx_t_20);
        if (likely(__pyx_t_10)) {
          PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_20);
          __Pyx_INCREF(__pyx_t_10);
          __Pyx_INCREF(function);
          __Pyx_DECREF_SET(__pyx_t_20, function);
        }
      }
      if (!__pyx_t_10) {
        __pyx_t_2 = __Pyx_PyObject_CallOneArg(__pyx_t_20, __pyx_t_6); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 362, __pyx_L1_error)
        __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
        __Pyx_GOTREF(__pyx_t_2);
      } else {
        #if CYTHON_FAST_PYCALL
        if (PyFunction_Check(__pyx_t_20)) {
          PyObject *__pyx_temp[2] = {__pyx_t_10, __pyx_t_6};
          __pyx_t_2 = __Pyx_PyFunction_FastCall(__pyx_t_20, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 362, __pyx_L1_error)
          __Pyx_XDECREF(__pyx_t_10); __pyx_t_10 = 0;
          __Pyx_GOTREF(__pyx_t_2);
          __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
        } else
        #endif
        #if CYTHON_FAST_PYCCALL
        if (__Pyx_PyFastCFunction_Check(__pyx_t_20)) {
          PyObject *__pyx_temp[2] = {__pyx_t_10, __pyx_t_6};
          __pyx_t_2 = __Pyx_PyCFunction_FastCall(__pyx_t_20, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 362, __pyx_L1_error)
          __Pyx_XDECREF(__pyx_t_10); __pyx_t_10 = 0;
          __Pyx_GOTREF(__pyx_t_2);
          __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
        } else
        #endif
        {
          __pyx_t_17 = PyTuple_New(1+1); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 362, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_17);
          __Pyx_GIVEREF(__pyx_t_10); PyTuple_SET_ITEM(__pyx_t_17, 0, __pyx_t_10); __pyx_t_10 = NULL;
          __Pyx_GIVEREF(__pyx_t_6);
          PyTuple_SET_ITEM(__pyx_t_17, 0+1, __pyx_t_6);
          __pyx_t_6 = 0;
          __pyx_t_2 = __Pyx_PyObject_Call(__pyx_t_20, __pyx_t_17, NULL); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 362, __pyx_L1_error)
          __Pyx_GOTREF(__pyx_t_2);
          __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
        }
      }
      __Pyx_DECREF(__pyx_t_20); __pyx_t_20 = 0;
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

      /* "ims_extractor.pyx":361
 *         # print len(datax[90]),datax[90]
 * 
 *         for item in b:             # <<<<<<<<<<<<<<
 *             file3.write(",".join(item) + "\n")
 *         file3.write("TIC: %f\n" % log(tic))
 */
    }
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

    /* "ims_extractor.pyx":363
 *         for item in b:
 *             file3.write(",".join(item) + "\n")
 *         file3.write("TIC: %f\n" % log(tic))             # <<<<<<<<<<<<<<
 *         file3.close()
 * 
 */
    __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_file3, __pyx_n_s_write); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 363, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_17 = __Pyx_GetModuleGlobalName(__pyx_n_s_log); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 363, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_17);
    __pyx_t_6 = __Pyx_GetModuleGlobalName(__pyx_n_s_tic); if (unlikely(!__pyx_t_6)) __PYX_ERR(0, 363, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_6);
    __pyx_t_10 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_17))) {
      __pyx_t_10 = PyMethod_GET_SELF(__pyx_t_17);
      if (likely(__pyx_t_10)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_17);
        __Pyx_INCREF(__pyx_t_10);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_17, function);
      }
    }
    if (!__pyx_t_10) {
      __pyx_t_20 = __Pyx_PyObject_CallOneArg(__pyx_t_17, __pyx_t_6); if (unlikely(!__pyx_t_20)) __PYX_ERR(0, 363, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
      __Pyx_GOTREF(__pyx_t_20);
    } else {
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_17)) {
        PyObject *__pyx_temp[2] = {__pyx_t_10, __pyx_t_6};
        __pyx_t_20 = __Pyx_PyFunction_FastCall(__pyx_t_17, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_20)) __PYX_ERR(0, 363, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_10); __pyx_t_10 = 0;
        __Pyx_GOTREF(__pyx_t_20);
        __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_17)) {
        PyObject *__pyx_temp[2] = {__pyx_t_10, __pyx_t_6};
        __pyx_t_20 = __Pyx_PyCFunction_FastCall(__pyx_t_17, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_20)) __PYX_ERR(0, 363, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_10); __pyx_t_10 = 0;
        __Pyx_GOTREF(__pyx_t_20);
        __Pyx_DECREF(__pyx_t_6); __pyx_t_6 = 0;
      } else
      #endif
      {
        __pyx_t_3 = PyTuple_New(1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 363, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __Pyx_GIVEREF(__pyx_t_10); PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_10); __pyx_t_10 = NULL;
        __Pyx_GIVEREF(__pyx_t_6);
        PyTuple_SET_ITEM(__pyx_t_3, 0+1, __pyx_t_6);
        __pyx_t_6 = 0;
        __pyx_t_20 = __Pyx_PyObject_Call(__pyx_t_17, __pyx_t_3, NULL); if (unlikely(!__pyx_t_20)) __PYX_ERR(0, 363, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_20);
        __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      }
    }
    __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
    __pyx_t_17 = __Pyx_PyString_Format(__pyx_kp_s_TIC_f, __pyx_t_20); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 363, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_17);
    __Pyx_DECREF(__pyx_t_20); __pyx_t_20 = 0;
    __pyx_t_20 = NULL;
    if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_2))) {
      __pyx_t_20 = PyMethod_GET_SELF(__pyx_t_2);
      if (likely(__pyx_t_20)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
        __Pyx_INCREF(__pyx_t_20);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_2, function);
      }
    }
    if (!__pyx_t_20) {
      __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_t_17); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 363, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
      __Pyx_GOTREF(__pyx_t_1);
    } else {
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_2)) {
        PyObject *__pyx_temp[2] = {__pyx_t_20, __pyx_t_17};
        __pyx_t_1 = __Pyx_PyFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 363, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_20); __pyx_t_20 = 0;
        __Pyx_GOTREF(__pyx_t_1);
        __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_2)) {
        PyObject *__pyx_temp[2] = {__pyx_t_20, __pyx_t_17};
        __pyx_t_1 = __Pyx_PyCFunction_FastCall(__pyx_t_2, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 363, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_20); __pyx_t_20 = 0;
        __Pyx_GOTREF(__pyx_t_1);
        __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
      } else
      #endif
      {
        __pyx_t_3 = PyTuple_New(1+1); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 363, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_3);
        __Pyx_GIVEREF(__pyx_t_20); PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_t_20); __pyx_t_20 = NULL;
        __Pyx_GIVEREF(__pyx_t_17);
        PyTuple_SET_ITEM(__pyx_t_3, 0+1, __pyx_t_17);
        __pyx_t_17 = 0;
        __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_2, __pyx_t_3, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 363, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
      }
    }
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

    /* "ims_extractor.pyx":364
 *             file3.write(",".join(item) + "\n")
 *         file3.write("TIC: %f\n" % log(tic))
 *         file3.close()             # <<<<<<<<<<<<<<
 * 
 * 
 */
    __pyx_t_2 = __Pyx_PyObject_GetAttrStr(__pyx_v_file3, __pyx_n_s_close); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 364, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_3 = NULL;
    if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_2))) {
      __pyx_t_3 = PyMethod_GET_SELF(__pyx_t_2);
      if (likely(__pyx_t_3)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_2);
        __Pyx_INCREF(__pyx_t_3);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_2, function);
      }
    }
    if (__pyx_t_3) {
      __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_2, __pyx_t_3); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 364, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    } else {
      __pyx_t_1 = __Pyx_PyObject_CallNoArg(__pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 364, __pyx_L1_error)
    }
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

    /* "ims_extractor.pyx":368
 * 
 * 
 *         end = time.clock()             # <<<<<<<<<<<<<<
 *         timex = (end - start)
 *         print "#----------------------------------------------------#"
 */
    __pyx_t_2 = __Pyx_GetModuleGlobalName(__pyx_n_s_time); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 368, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_2);
    __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_t_2, __pyx_n_s_clock); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 368, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    __pyx_t_2 = NULL;
    if (CYTHON_UNPACK_METHODS && unlikely(PyMethod_Check(__pyx_t_3))) {
      __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_3);
      if (likely(__pyx_t_2)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
        __Pyx_INCREF(__pyx_t_2);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_3, function);
      }
    }
    if (__pyx_t_2) {
      __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_t_2); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 368, __pyx_L1_error)
      __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
    } else {
      __pyx_t_1 = __Pyx_PyObject_CallNoArg(__pyx_t_3); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 368, __pyx_L1_error)
    }
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __Pyx_DECREF_SET(__pyx_v_end, __pyx_t_1);
    __pyx_t_1 = 0;

    /* "ims_extractor.pyx":369
 * 
 *         end = time.clock()
 *         timex = (end - start)             # <<<<<<<<<<<<<<
 *         print "#----------------------------------------------------#"
 *         print "| All done!                                          |"
 */
    __pyx_t_1 = PyNumber_Subtract(__pyx_v_end, __pyx_v_start); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 369, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_1);
    __Pyx_DECREF_SET(__pyx_v_timex, __pyx_t_1);
    __pyx_t_1 = 0;

    /* "ims_extractor.pyx":370
 *         end = time.clock()
 *         timex = (end - start)
 *         print "#----------------------------------------------------#"             # <<<<<<<<<<<<<<
 *         print "| All done!                                          |"
 *         print "| Thanks for using Dilu, bathygao@gmail.com          |"
 */
    if (__Pyx_PrintOne(0, __pyx_kp_s__10) < 0) __PYX_ERR(0, 370, __pyx_L1_error)

    /* "ims_extractor.pyx":371
 *         timex = (end - start)
 *         print "#----------------------------------------------------#"
 *         print "| All done!                                          |"             # <<<<<<<<<<<<<<
 *         print "| Thanks for using Dilu, bathygao@gmail.com          |"
 *         print "| Total time spent(s):", "{:10.4f}".format(timex), "                   |"
 */
    if (__Pyx_PrintOne(0, __pyx_kp_s_All_done) < 0) __PYX_ERR(0, 371, __pyx_L1_error)

    /* "ims_extractor.pyx":372
 *         print "#----------------------------------------------------#"
 *         print "| All done!                                          |"
 *         print "| Thanks for using Dilu, bathygao@gmail.com          |"             # <<<<<<<<<<<<<<
 *         print "| Total time spent(s):", "{:10.4f}".format(timex), "                   |"
 *         print "#----------------------------------------------------#"
 */
    if (__Pyx_PrintOne(0, __pyx_kp_s_Thanks_for_using_Dilu_bathygao) < 0) __PYX_ERR(0, 372, __pyx_L1_error)

    /* "ims_extractor.pyx":373
 *         print "| All done!                                          |"
 *         print "| Thanks for using Dilu, bathygao@gmail.com          |"
 *         print "| Total time spent(s):", "{:10.4f}".format(timex), "                   |"             # <<<<<<<<<<<<<<
 *         print "#----------------------------------------------------#"
 *         # print timex, len(a)
 */
    __pyx_t_3 = __Pyx_PyObject_GetAttrStr(__pyx_kp_s_10_4f, __pyx_n_s_format); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 373, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __pyx_t_2 = NULL;
    if (CYTHON_UNPACK_METHODS && likely(PyMethod_Check(__pyx_t_3))) {
      __pyx_t_2 = PyMethod_GET_SELF(__pyx_t_3);
      if (likely(__pyx_t_2)) {
        PyObject* function = PyMethod_GET_FUNCTION(__pyx_t_3);
        __Pyx_INCREF(__pyx_t_2);
        __Pyx_INCREF(function);
        __Pyx_DECREF_SET(__pyx_t_3, function);
      }
    }
    if (!__pyx_t_2) {
      __pyx_t_1 = __Pyx_PyObject_CallOneArg(__pyx_t_3, __pyx_v_timex); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 373, __pyx_L1_error)
      __Pyx_GOTREF(__pyx_t_1);
    } else {
      #if CYTHON_FAST_PYCALL
      if (PyFunction_Check(__pyx_t_3)) {
        PyObject *__pyx_temp[2] = {__pyx_t_2, __pyx_v_timex};
        __pyx_t_1 = __Pyx_PyFunction_FastCall(__pyx_t_3, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 373, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
        __Pyx_GOTREF(__pyx_t_1);
      } else
      #endif
      #if CYTHON_FAST_PYCCALL
      if (__Pyx_PyFastCFunction_Check(__pyx_t_3)) {
        PyObject *__pyx_temp[2] = {__pyx_t_2, __pyx_v_timex};
        __pyx_t_1 = __Pyx_PyCFunction_FastCall(__pyx_t_3, __pyx_temp+1-1, 1+1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 373, __pyx_L1_error)
        __Pyx_XDECREF(__pyx_t_2); __pyx_t_2 = 0;
        __Pyx_GOTREF(__pyx_t_1);
      } else
      #endif
      {
        __pyx_t_17 = PyTuple_New(1+1); if (unlikely(!__pyx_t_17)) __PYX_ERR(0, 373, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_17);
        __Pyx_GIVEREF(__pyx_t_2); PyTuple_SET_ITEM(__pyx_t_17, 0, __pyx_t_2); __pyx_t_2 = NULL;
        __Pyx_INCREF(__pyx_v_timex);
        __Pyx_GIVEREF(__pyx_v_timex);
        PyTuple_SET_ITEM(__pyx_t_17, 0+1, __pyx_v_timex);
        __pyx_t_1 = __Pyx_PyObject_Call(__pyx_t_3, __pyx_t_17, NULL); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 373, __pyx_L1_error)
        __Pyx_GOTREF(__pyx_t_1);
        __Pyx_DECREF(__pyx_t_17); __pyx_t_17 = 0;
      }
    }
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;
    __pyx_t_3 = PyTuple_New(3); if (unlikely(!__pyx_t_3)) __PYX_ERR(0, 373, __pyx_L1_error)
    __Pyx_GOTREF(__pyx_t_3);
    __Pyx_INCREF(__pyx_kp_s_Total_time_spent_s);
    __Pyx_GIVEREF(__pyx_kp_s_Total_time_spent_s);
    PyTuple_SET_ITEM(__pyx_t_3, 0, __pyx_kp_s_Total_time_spent_s);
    __Pyx_GIVEREF(__pyx_t_1);
    PyTuple_SET_ITEM(__pyx_t_3, 1, __pyx_t_1);
    __Pyx_INCREF(__pyx_kp_s__26);
    __Pyx_GIVEREF(__pyx_kp_s__26);
    PyTuple_SET_ITEM(__pyx_t_3, 2, __pyx_kp_s__26);
    __pyx_t_1 = 0;
    if (__Pyx_Print(0, __pyx_t_3, 1) < 0) __PYX_ERR(0, 373, __pyx_L1_error)
    __Pyx_DECREF(__pyx_t_3); __pyx_t_3 = 0;

    /* "ims_extractor.pyx":374
 *         print "| Thanks for using Dilu, bathygao@gmail.com          |"
 *         print "| Total time spent(s):", "{:10.4f}".format(timex), "                   |"
 *         print "#----------------------------------------------------#"             # <<<<<<<<<<<<<<
 *         # print timex, len(a)
 */
    if (__Pyx_PrintOne(0, __pyx_kp_s__10) < 0) __PYX_ERR(0, 374, __pyx_L1_error)
  }
  __pyx_L7:;

  /* "ims_extractor.pyx":29
 * 
 * 
 * def extract_file(file_name):             # <<<<<<<<<<<<<<
 * 
 *     global start_time,end_time,tic,max_drift,resolution,res_factor,res_array,log_array,low_mass_array,log_factor,low_mass_factor,ret_time
 */

  /* function exit code */
  __pyx_r = Py_None; __Pyx_INCREF(Py_None);
  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  __Pyx_XDECREF(__pyx_t_3);
  __Pyx_XDECREF(__pyx_t_6);
  __Pyx_XDECREF(__pyx_t_10);
  __Pyx_XDECREF(__pyx_t_17);
  __Pyx_XDECREF(__pyx_t_18);
  __Pyx_XDECREF(__pyx_t_19);
  __Pyx_XDECREF(__pyx_t_20);
  __Pyx_AddTraceback("ims_extractor.extract_file", __pyx_clineno, __pyx_lineno, __pyx_filename);
  __pyx_r = NULL;
  __pyx_L0:;
  __Pyx_XDECREF(__pyx_v_start);
  __Pyx_XDECREF(__pyx_v_retention);
  __Pyx_XDECREF(__pyx_v_xa);
  __Pyx_XDECREF(__pyx_v_xi);
  __Pyx_XDECREF(__pyx_v_xm);
  __Pyx_XDECREF(__pyx_v_datax);
  __Pyx_XDECREF(__pyx_v_file_name_ims);
  __Pyx_XDECREF(__pyx_v_file_name_freq);
  __Pyx_XDECREF(__pyx_v_file2);
  __Pyx_XDECREF(__pyx_v_end);
  __Pyx_XDECREF(__pyx_v_timex);
  __Pyx_XDECREF(__pyx_v_start1);
  __Pyx_XDECREF(__pyx_v_lines);
  __Pyx_XDECREF(__pyx_v_temp_data);
  __Pyx_XDECREF(__pyx_v_item);
  __Pyx_XDECREF(__pyx_v_effct);
  __Pyx_XDECREF(__pyx_v_i);
  __Pyx_XDECREF(__pyx_v_a);
  __Pyx_XDECREF(__pyx_v_b);
  __Pyx_XDECREF(__pyx_v_valid_spec);
  __Pyx_XDECREF(__pyx_v_sequential_spec);
  __Pyx_XDECREF(__pyx_v_intensity_dict);
  __Pyx_XDECREF(__pyx_v_total);
  __Pyx_XDECREF(__pyx_v_count);
  __Pyx_XDECREF(__pyx_v_lastvalue);
  __Pyx_XDECREF(__pyx_v_last_idx);
  __Pyx_XDECREF(__pyx_v_start_idx);
  __Pyx_XDECREF(__pyx_v_idx);
  __Pyx_XDECREF(__pyx_v_value);
  __Pyx_XDECREF(__pyx_v_peak_count);
  __Pyx_XDECREF(__pyx_v_mass_center);
  __Pyx_XDECREF(__pyx_v_ii);
  __Pyx_XDECREF(__pyx_v_max_mass);
  __Pyx_XDECREF(__pyx_v_max_int);
  __Pyx_XDECREF(__pyx_v_int_max);
  __Pyx_XDECREF(__pyx_v_intt);
  __Pyx_XDECREF(__pyx_v_temp_int);
  __Pyx_XDECREF(__pyx_v_temp_diff);
  __Pyx_XDECREF(__pyx_v_peak_pos);
  __Pyx_XDECREF(__pyx_v_temp_peak_count);
  __Pyx_XDECREF(__pyx_v_iii);
  __Pyx_XDECREF(__pyx_v_num_of_valley);
  __Pyx_XDECREF(__pyx_v_zero_fill);
  __Pyx_XDECREF(__pyx_v_time_available);
  __Pyx_XDECREF(__pyx_v_time_start);
  __Pyx_XDECREF(__pyx_v_time_end);
  __Pyx_XDECREF(__pyx_v_difference);
  __Pyx_XDECREF(__pyx_v_zero_fill_flat);
  __Pyx_XDECREF(__pyx_v_floatarray3);
  __Pyx_XDECREF(__pyx_v_floatarray);
  __Pyx_XDECREF(__pyx_v_floatarray2);
  __Pyx_XDECREF(__pyx_v_file3);
  __Pyx_XDECREF(__pyx_v__);
  __Pyx_XDECREF(__pyx_v_sublist);
  __Pyx_XGIVEREF(__pyx_r);
  __Pyx_RefNannyFinishContext();
  return __pyx_r;
}

static PyMethodDef __pyx_methods[] = {
  {0, 0, 0, 0}
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef __pyx_moduledef = {
  #if PY_VERSION_HEX < 0x03020000
    { PyObject_HEAD_INIT(NULL) NULL, 0, NULL },
  #else
    PyModuleDef_HEAD_INIT,
  #endif
    "ims_extractor",
    0, /* m_doc */
    -1, /* m_size */
    __pyx_methods /* m_methods */,
    NULL, /* m_reload */
    NULL, /* m_traverse */
    NULL, /* m_clear */
    NULL /* m_free */
};
#endif

static __Pyx_StringTabEntry __pyx_string_tab[] = {
  {&__pyx_kp_s_, __pyx_k_, sizeof(__pyx_k_), 0, 0, 1, 0},
  {&__pyx_kp_s_10_4f, __pyx_k_10_4f, sizeof(__pyx_k_10_4f), 0, 0, 1, 0},
  {&__pyx_kp_s_All_data_loaded_from_disk, __pyx_k_All_data_loaded_from_disk, sizeof(__pyx_k_All_data_loaded_from_disk), 0, 0, 1, 0},
  {&__pyx_kp_s_All_done, __pyx_k_All_done, sizeof(__pyx_k_All_done), 0, 0, 1, 0},
  {&__pyx_kp_s_Analyzing_spectra, __pyx_k_Analyzing_spectra, sizeof(__pyx_k_Analyzing_spectra), 0, 0, 1, 0},
  {&__pyx_kp_s_Combining_features_to_spectra, __pyx_k_Combining_features_to_spectra, sizeof(__pyx_k_Combining_features_to_spectra), 0, 0, 1, 0},
  {&__pyx_kp_s_Detecting_features, __pyx_k_Detecting_features, sizeof(__pyx_k_Detecting_features), 0, 0, 1, 0},
  {&__pyx_kp_s_Dilu_IMS, __pyx_k_Dilu_IMS, sizeof(__pyx_k_Dilu_IMS), 0, 0, 1, 0},
  {&__pyx_kp_s_Dilu_initialized, __pyx_k_Dilu_initialized, sizeof(__pyx_k_Dilu_initialized), 0, 0, 1, 0},
  {&__pyx_kp_s_E_Python_ims_extractor_pyx, __pyx_k_E_Python_ims_extractor_pyx, sizeof(__pyx_k_E_Python_ims_extractor_pyx), 0, 0, 1, 0},
  {&__pyx_kp_s_Feature_detection_finished, __pyx_k_Feature_detection_finished, sizeof(__pyx_k_Feature_detection_finished), 0, 0, 1, 0},
  {&__pyx_kp_s_Features_combined, __pyx_k_Features_combined, sizeof(__pyx_k_Features_combined), 0, 0, 1, 0},
  {&__pyx_kp_s_Loading_data, __pyx_k_Loading_data, sizeof(__pyx_k_Loading_data), 0, 0, 1, 0},
  {&__pyx_kp_s_Number_of_spectra_for_inspectio, __pyx_k_Number_of_spectra_for_inspectio, sizeof(__pyx_k_Number_of_spectra_for_inspectio), 0, 0, 1, 0},
  {&__pyx_n_s_RetTime, __pyx_k_RetTime, sizeof(__pyx_k_RetTime), 0, 0, 1, 1},
  {&__pyx_kp_s_TIC_f, __pyx_k_TIC_f, sizeof(__pyx_k_TIC_f), 0, 0, 1, 0},
  {&__pyx_kp_s_Thanks_for_using_Dilu_bathygao, __pyx_k_Thanks_for_using_Dilu_bathygao, sizeof(__pyx_k_Thanks_for_using_Dilu_bathygao), 0, 0, 1, 0},
  {&__pyx_kp_s_Time_spent_s, __pyx_k_Time_spent_s, sizeof(__pyx_k_Time_spent_s), 0, 0, 1, 0},
  {&__pyx_kp_s_Total_features_detected, __pyx_k_Total_features_detected, sizeof(__pyx_k_Total_features_detected), 0, 0, 1, 0},
  {&__pyx_kp_s_Total_time_spent_s, __pyx_k_Total_time_spent_s, sizeof(__pyx_k_Total_time_spent_s), 0, 0, 1, 0},
  {&__pyx_kp_s_Writing, __pyx_k_Writing, sizeof(__pyx_k_Writing), 0, 0, 1, 0},
  {&__pyx_kp_s_Yu_Tom_Gao_Yates_Lab_TSRI, __pyx_k_Yu_Tom_Gao_Yates_Lab_TSRI, sizeof(__pyx_k_Yu_Tom_Gao_Yates_Lab_TSRI), 0, 0, 1, 0},
  {&__pyx_kp_s__10, __pyx_k__10, sizeof(__pyx_k__10), 0, 0, 1, 0},
  {&__pyx_kp_s__11, __pyx_k__11, sizeof(__pyx_k__11), 0, 0, 1, 0},
  {&__pyx_kp_s__14, __pyx_k__14, sizeof(__pyx_k__14), 0, 0, 1, 0},
  {&__pyx_kp_s__16, __pyx_k__16, sizeof(__pyx_k__16), 0, 0, 1, 0},
  {&__pyx_kp_s__18, __pyx_k__18, sizeof(__pyx_k__18), 0, 0, 1, 0},
  {&__pyx_kp_s__20, __pyx_k__20, sizeof(__pyx_k__20), 0, 0, 1, 0},
  {&__pyx_kp_s__22, __pyx_k__22, sizeof(__pyx_k__22), 0, 0, 1, 0},
  {&__pyx_kp_s__25, __pyx_k__25, sizeof(__pyx_k__25), 0, 0, 1, 0},
  {&__pyx_kp_s__26, __pyx_k__26, sizeof(__pyx_k__26), 0, 0, 1, 0},
  {&__pyx_n_s__29, __pyx_k__29, sizeof(__pyx_k__29), 0, 0, 1, 1},
  {&__pyx_kp_s__3, __pyx_k__3, sizeof(__pyx_k__3), 0, 0, 1, 0},
  {&__pyx_kp_s__5, __pyx_k__5, sizeof(__pyx_k__5), 0, 0, 1, 0},
  {&__pyx_kp_s__6, __pyx_k__6, sizeof(__pyx_k__6), 0, 0, 1, 0},
  {&__pyx_kp_s__8, __pyx_k__8, sizeof(__pyx_k__8), 0, 0, 1, 0},
  {&__pyx_n_s_a, __pyx_k_a, sizeof(__pyx_k_a), 0, 0, 1, 1},
  {&__pyx_n_s_array, __pyx_k_array, sizeof(__pyx_k_array), 0, 0, 1, 1},
  {&__pyx_n_s_b, __pyx_k_b, sizeof(__pyx_k_b), 0, 0, 1, 1},
  {&__pyx_n_s_clock, __pyx_k_clock, sizeof(__pyx_k_clock), 0, 0, 1, 1},
  {&__pyx_n_s_close, __pyx_k_close, sizeof(__pyx_k_close), 0, 0, 1, 1},
  {&__pyx_n_s_count, __pyx_k_count, sizeof(__pyx_k_count), 0, 0, 1, 1},
  {&__pyx_n_s_datax, __pyx_k_datax, sizeof(__pyx_k_datax), 0, 0, 1, 1},
  {&__pyx_n_s_difference, __pyx_k_difference, sizeof(__pyx_k_difference), 0, 0, 1, 1},
  {&__pyx_n_s_effct, __pyx_k_effct, sizeof(__pyx_k_effct), 0, 0, 1, 1},
  {&__pyx_n_s_end, __pyx_k_end, sizeof(__pyx_k_end), 0, 0, 1, 1},
  {&__pyx_n_s_end_time, __pyx_k_end_time, sizeof(__pyx_k_end_time), 0, 0, 1, 1},
  {&__pyx_n_s_enter, __pyx_k_enter, sizeof(__pyx_k_enter), 0, 0, 1, 1},
  {&__pyx_n_s_enumerate, __pyx_k_enumerate, sizeof(__pyx_k_enumerate), 0, 0, 1, 1},
  {&__pyx_n_s_exit, __pyx_k_exit, sizeof(__pyx_k_exit), 0, 0, 1, 1},
  {&__pyx_n_s_extract_file, __pyx_k_extract_file, sizeof(__pyx_k_extract_file), 0, 0, 1, 1},
  {&__pyx_n_s_f, __pyx_k_f, sizeof(__pyx_k_f), 0, 0, 1, 1},
  {&__pyx_n_s_file, __pyx_k_file, sizeof(__pyx_k_file), 0, 0, 1, 1},
  {&__pyx_n_s_file2, __pyx_k_file2, sizeof(__pyx_k_file2), 0, 0, 1, 1},
  {&__pyx_n_s_file3, __pyx_k_file3, sizeof(__pyx_k_file3), 0, 0, 1, 1},
  {&__pyx_kp_s_file_exist, __pyx_k_file_exist, sizeof(__pyx_k_file_exist), 0, 0, 1, 0},
  {&__pyx_n_s_file_name, __pyx_k_file_name, sizeof(__pyx_k_file_name), 0, 0, 1, 1},
  {&__pyx_n_s_file_name_freq, __pyx_k_file_name_freq, sizeof(__pyx_k_file_name_freq), 0, 0, 1, 1},
  {&__pyx_n_s_file_name_ims, __pyx_k_file_name_ims, sizeof(__pyx_k_file_name_ims), 0, 0, 1, 1},
  {&__pyx_n_s_floatarray, __pyx_k_floatarray, sizeof(__pyx_k_floatarray), 0, 0, 1, 1},
  {&__pyx_n_s_floatarray2, __pyx_k_floatarray2, sizeof(__pyx_k_floatarray2), 0, 0, 1, 1},
  {&__pyx_n_s_floatarray3, __pyx_k_floatarray3, sizeof(__pyx_k_floatarray3), 0, 0, 1, 1},
  {&__pyx_n_s_format, __pyx_k_format, sizeof(__pyx_k_format), 0, 0, 1, 1},
  {&__pyx_kp_s_frequency_csv, __pyx_k_frequency_csv, sizeof(__pyx_k_frequency_csv), 0, 0, 1, 0},
  {&__pyx_n_s_i, __pyx_k_i, sizeof(__pyx_k_i), 0, 0, 1, 1},
  {&__pyx_n_s_idx, __pyx_k_idx, sizeof(__pyx_k_idx), 0, 0, 1, 1},
  {&__pyx_n_s_ii, __pyx_k_ii, sizeof(__pyx_k_ii), 0, 0, 1, 1},
  {&__pyx_n_s_iii, __pyx_k_iii, sizeof(__pyx_k_iii), 0, 0, 1, 1},
  {&__pyx_n_s_import, __pyx_k_import, sizeof(__pyx_k_import), 0, 0, 1, 1},
  {&__pyx_kp_s_ims, __pyx_k_ims, sizeof(__pyx_k_ims), 0, 0, 1, 0},
  {&__pyx_n_s_ims_extractor, __pyx_k_ims_extractor, sizeof(__pyx_k_ims_extractor), 0, 0, 1, 1},
  {&__pyx_n_s_increment, __pyx_k_increment, sizeof(__pyx_k_increment), 0, 0, 1, 1},
  {&__pyx_n_s_int_max, __pyx_k_int_max, sizeof(__pyx_k_int_max), 0, 0, 1, 1},
  {&__pyx_n_s_intensity_dict, __pyx_k_intensity_dict, sizeof(__pyx_k_intensity_dict), 0, 0, 1, 1},
  {&__pyx_n_s_intt, __pyx_k_intt, sizeof(__pyx_k_intt), 0, 0, 1, 1},
  {&__pyx_n_s_isalpha, __pyx_k_isalpha, sizeof(__pyx_k_isalpha), 0, 0, 1, 1},
  {&__pyx_n_s_isfile, __pyx_k_isfile, sizeof(__pyx_k_isfile), 0, 0, 1, 1},
  {&__pyx_n_s_item, __pyx_k_item, sizeof(__pyx_k_item), 0, 0, 1, 1},
  {&__pyx_n_s_join, __pyx_k_join, sizeof(__pyx_k_join), 0, 0, 1, 1},
  {&__pyx_n_s_last_idx, __pyx_k_last_idx, sizeof(__pyx_k_last_idx), 0, 0, 1, 1},
  {&__pyx_n_s_lastvalue, __pyx_k_lastvalue, sizeof(__pyx_k_lastvalue), 0, 0, 1, 1},
  {&__pyx_n_s_line, __pyx_k_line, sizeof(__pyx_k_line), 0, 0, 1, 1},
  {&__pyx_n_s_lines, __pyx_k_lines, sizeof(__pyx_k_lines), 0, 0, 1, 1},
  {&__pyx_n_s_ljust, __pyx_k_ljust, sizeof(__pyx_k_ljust), 0, 0, 1, 1},
  {&__pyx_n_s_load_data, __pyx_k_load_data, sizeof(__pyx_k_load_data), 0, 0, 1, 1},
  {&__pyx_n_s_log, __pyx_k_log, sizeof(__pyx_k_log), 0, 0, 1, 1},
  {&__pyx_n_s_log10, __pyx_k_log10, sizeof(__pyx_k_log10), 0, 0, 1, 1},
  {&__pyx_n_s_log_array, __pyx_k_log_array, sizeof(__pyx_k_log_array), 0, 0, 1, 1},
  {&__pyx_n_s_log_factor, __pyx_k_log_factor, sizeof(__pyx_k_log_factor), 0, 0, 1, 1},
  {&__pyx_n_s_low_mass_array, __pyx_k_low_mass_array, sizeof(__pyx_k_low_mass_array), 0, 0, 1, 1},
  {&__pyx_n_s_low_mass_factor, __pyx_k_low_mass_factor, sizeof(__pyx_k_low_mass_factor), 0, 0, 1, 1},
  {&__pyx_n_s_m, __pyx_k_m, sizeof(__pyx_k_m), 0, 0, 1, 1},
  {&__pyx_n_s_main, __pyx_k_main, sizeof(__pyx_k_main), 0, 0, 1, 1},
  {&__pyx_n_s_map, __pyx_k_map, sizeof(__pyx_k_map), 0, 0, 1, 1},
  {&__pyx_n_s_mass_center, __pyx_k_mass_center, sizeof(__pyx_k_mass_center), 0, 0, 1, 1},
  {&__pyx_n_s_math, __pyx_k_math, sizeof(__pyx_k_math), 0, 0, 1, 1},
  {&__pyx_n_s_max_drift, __pyx_k_max_drift, sizeof(__pyx_k_max_drift), 0, 0, 1, 1},
  {&__pyx_n_s_max_int, __pyx_k_max_int, sizeof(__pyx_k_max_int), 0, 0, 1, 1},
  {&__pyx_n_s_max_mass, __pyx_k_max_mass, sizeof(__pyx_k_max_mass), 0, 0, 1, 1},
  {&__pyx_kp_s_ms1, __pyx_k_ms1, sizeof(__pyx_k_ms1), 0, 0, 1, 0},
  {&__pyx_n_s_myi, __pyx_k_myi, sizeof(__pyx_k_myi), 0, 0, 1, 1},
  {&__pyx_n_s_n, __pyx_k_n, sizeof(__pyx_k_n), 0, 0, 1, 1},
  {&__pyx_n_s_num_of_valley, __pyx_k_num_of_valley, sizeof(__pyx_k_num_of_valley), 0, 0, 1, 1},
  {&__pyx_n_s_open, __pyx_k_open, sizeof(__pyx_k_open), 0, 0, 1, 1},
  {&__pyx_n_s_operator, __pyx_k_operator, sizeof(__pyx_k_operator), 0, 0, 1, 1},
  {&__pyx_n_s_os, __pyx_k_os, sizeof(__pyx_k_os), 0, 0, 1, 1},
  {&__pyx_n_s_path, __pyx_k_path, sizeof(__pyx_k_path), 0, 0, 1, 1},
  {&__pyx_n_s_peak_count, __pyx_k_peak_count, sizeof(__pyx_k_peak_count), 0, 0, 1, 1},
  {&__pyx_n_s_peak_pos, __pyx_k_peak_pos, sizeof(__pyx_k_peak_pos), 0, 0, 1, 1},
  {&__pyx_n_s_position, __pyx_k_position, sizeof(__pyx_k_position), 0, 0, 1, 1},
  {&__pyx_kp_s_ppm_accuracy, __pyx_k_ppm_accuracy, sizeof(__pyx_k_ppm_accuracy), 0, 0, 1, 0},
  {&__pyx_n_s_print, __pyx_k_print, sizeof(__pyx_k_print), 0, 0, 1, 1},
  {&__pyx_n_s_range, __pyx_k_range, sizeof(__pyx_k_range), 0, 0, 1, 1},
  {&__pyx_n_s_remove, __pyx_k_remove, sizeof(__pyx_k_remove), 0, 0, 1, 1},
  {&__pyx_n_s_replace, __pyx_k_replace, sizeof(__pyx_k_replace), 0, 0, 1, 1},
  {&__pyx_n_s_res_array, __pyx_k_res_array, sizeof(__pyx_k_res_array), 0, 0, 1, 1},
  {&__pyx_n_s_res_factor, __pyx_k_res_factor, sizeof(__pyx_k_res_factor), 0, 0, 1, 1},
  {&__pyx_n_s_resolution, __pyx_k_resolution, sizeof(__pyx_k_resolution), 0, 0, 1, 1},
  {&__pyx_n_s_ret_time, __pyx_k_ret_time, sizeof(__pyx_k_ret_time), 0, 0, 1, 1},
  {&__pyx_n_s_retention, __pyx_k_retention, sizeof(__pyx_k_retention), 0, 0, 1, 1},
  {&__pyx_n_s_sequential_spec, __pyx_k_sequential_spec, sizeof(__pyx_k_sequential_spec), 0, 0, 1, 1},
  {&__pyx_kp_s_spectra_analyzed_at, __pyx_k_spectra_analyzed_at, sizeof(__pyx_k_spectra_analyzed_at), 0, 0, 1, 0},
  {&__pyx_n_s_split, __pyx_k_split, sizeof(__pyx_k_split), 0, 0, 1, 1},
  {&__pyx_n_s_start, __pyx_k_start, sizeof(__pyx_k_start), 0, 0, 1, 1},
  {&__pyx_n_s_start1, __pyx_k_start1, sizeof(__pyx_k_start1), 0, 0, 1, 1},
  {&__pyx_n_s_start_idx, __pyx_k_start_idx, sizeof(__pyx_k_start_idx), 0, 0, 1, 1},
  {&__pyx_n_s_start_time, __pyx_k_start_time, sizeof(__pyx_k_start_time), 0, 0, 1, 1},
  {&__pyx_n_s_sub, __pyx_k_sub, sizeof(__pyx_k_sub), 0, 0, 1, 1},
  {&__pyx_n_s_sublist, __pyx_k_sublist, sizeof(__pyx_k_sublist), 0, 0, 1, 1},
  {&__pyx_n_s_temp_data, __pyx_k_temp_data, sizeof(__pyx_k_temp_data), 0, 0, 1, 1},
  {&__pyx_n_s_temp_diff, __pyx_k_temp_diff, sizeof(__pyx_k_temp_diff), 0, 0, 1, 1},
  {&__pyx_n_s_temp_int, __pyx_k_temp_int, sizeof(__pyx_k_temp_int), 0, 0, 1, 1},
  {&__pyx_n_s_temp_peak_count, __pyx_k_temp_peak_count, sizeof(__pyx_k_temp_peak_count), 0, 0, 1, 1},
  {&__pyx_n_s_test, __pyx_k_test, sizeof(__pyx_k_test), 0, 0, 1, 1},
  {&__pyx_n_s_tic, __pyx_k_tic, sizeof(__pyx_k_tic), 0, 0, 1, 1},
  {&__pyx_n_s_time, __pyx_k_time, sizeof(__pyx_k_time), 0, 0, 1, 1},
  {&__pyx_n_s_time_available, __pyx_k_time_available, sizeof(__pyx_k_time_available), 0, 0, 1, 1},
  {&__pyx_n_s_time_end, __pyx_k_time_end, sizeof(__pyx_k_time_end), 0, 0, 1, 1},
  {&__pyx_n_s_time_start, __pyx_k_time_start, sizeof(__pyx_k_time_start), 0, 0, 1, 1},
  {&__pyx_n_s_timex, __pyx_k_timex, sizeof(__pyx_k_timex), 0, 0, 1, 1},
  {&__pyx_n_s_tofile, __pyx_k_tofile, sizeof(__pyx_k_tofile), 0, 0, 1, 1},
  {&__pyx_n_s_total, __pyx_k_total, sizeof(__pyx_k_total), 0, 0, 1, 1},
  {&__pyx_n_s_total_spec, __pyx_k_total_spec, sizeof(__pyx_k_total_spec), 0, 0, 1, 1},
  {&__pyx_n_s_valid_spec, __pyx_k_valid_spec, sizeof(__pyx_k_valid_spec), 0, 0, 1, 1},
  {&__pyx_n_s_value, __pyx_k_value, sizeof(__pyx_k_value), 0, 0, 1, 1},
  {&__pyx_n_s_w, __pyx_k_w, sizeof(__pyx_k_w), 0, 0, 1, 1},
  {&__pyx_n_s_wb, __pyx_k_wb, sizeof(__pyx_k_wb), 0, 0, 1, 1},
  {&__pyx_n_s_write, __pyx_k_write, sizeof(__pyx_k_write), 0, 0, 1, 1},
  {&__pyx_n_s_xa, __pyx_k_xa, sizeof(__pyx_k_xa), 0, 0, 1, 1},
  {&__pyx_n_s_xi, __pyx_k_xi, sizeof(__pyx_k_xi), 0, 0, 1, 1},
  {&__pyx_n_s_xm, __pyx_k_xm, sizeof(__pyx_k_xm), 0, 0, 1, 1},
  {&__pyx_n_s_xrange, __pyx_k_xrange, sizeof(__pyx_k_xrange), 0, 0, 1, 1},
  {&__pyx_n_s_zero_fill, __pyx_k_zero_fill, sizeof(__pyx_k_zero_fill), 0, 0, 1, 1},
  {&__pyx_n_s_zero_fill_flat, __pyx_k_zero_fill_flat, sizeof(__pyx_k_zero_fill_flat), 0, 0, 1, 1},
  {0, 0, 0, 0, 0, 0, 0}
};
static int __Pyx_InitCachedBuiltins(void) {
  #if PY_MAJOR_VERSION >= 3
  __pyx_builtin_xrange = __Pyx_GetBuiltinName(__pyx_n_s_range); if (!__pyx_builtin_xrange) __PYX_ERR(0, 87, __pyx_L1_error)
  #else
  __pyx_builtin_xrange = __Pyx_GetBuiltinName(__pyx_n_s_xrange); if (!__pyx_builtin_xrange) __PYX_ERR(0, 87, __pyx_L1_error)
  #endif
  __pyx_builtin_open = __Pyx_GetBuiltinName(__pyx_n_s_open); if (!__pyx_builtin_open) __PYX_ERR(0, 100, __pyx_L1_error)
  __pyx_builtin_map = __Pyx_GetBuiltinName(__pyx_n_s_map); if (!__pyx_builtin_map) __PYX_ERR(0, 113, __pyx_L1_error)
  __pyx_builtin_range = __Pyx_GetBuiltinName(__pyx_n_s_range); if (!__pyx_builtin_range) __PYX_ERR(0, 160, __pyx_L1_error)
  __pyx_builtin_enumerate = __Pyx_GetBuiltinName(__pyx_n_s_enumerate); if (!__pyx_builtin_enumerate) __PYX_ERR(0, 180, __pyx_L1_error)
  return 0;
  __pyx_L1_error:;
  return -1;
}

static int __Pyx_InitCachedConstants(void) {
  __Pyx_RefNannyDeclarations
  __Pyx_RefNannySetupContext("__Pyx_InitCachedConstants", 0);

  /* "ims_extractor.pyx":14
 *     global ret_time
 *     if not line[0].isalpha():  # if start with 0-9 then get all data into its position
 *         m = line.split(' ')             # <<<<<<<<<<<<<<
 *         position = int((log(float(m[0])) * 100000000 - low_mass_factor) / log_factor) - 1  # calculate the position of specific m/z in datax[]
 *         return position, float(m[0]), float(m[1])
 */
  __pyx_tuple__2 = PyTuple_Pack(1, __pyx_kp_s_); if (unlikely(!__pyx_tuple__2)) __PYX_ERR(0, 14, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__2);
  __Pyx_GIVEREF(__pyx_tuple__2);

  /* "ims_extractor.pyx":19
 *         # datax[position]=datax[position]+[float(m[0]), float(m[1]), ret_time]	#put the value in a format [m/z intensity retention_time] to specific position in datax[]
 *     else:  # if start with alpha then acquire retention time
 *         n = line.split('\t')             # <<<<<<<<<<<<<<
 *         if n[1] == 'RetTime':
 *             ret_time = float(n[2].replace('\n', '').replace('\r', ''))
 */
  __pyx_tuple__4 = PyTuple_Pack(1, __pyx_kp_s__3); if (unlikely(!__pyx_tuple__4)) __PYX_ERR(0, 19, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__4);
  __Pyx_GIVEREF(__pyx_tuple__4);

  /* "ims_extractor.pyx":21
 *         n = line.split('\t')
 *         if n[1] == 'RetTime':
 *             ret_time = float(n[2].replace('\n', '').replace('\r', ''))             # <<<<<<<<<<<<<<
 *             return [ret_time]
 *         return []
 */
  __pyx_tuple__7 = PyTuple_Pack(2, __pyx_kp_s__5, __pyx_kp_s__6); if (unlikely(!__pyx_tuple__7)) __PYX_ERR(0, 21, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__7);
  __Pyx_GIVEREF(__pyx_tuple__7);
  __pyx_tuple__9 = PyTuple_Pack(2, __pyx_kp_s__8, __pyx_kp_s__6); if (unlikely(!__pyx_tuple__9)) __PYX_ERR(0, 21, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__9);
  __Pyx_GIVEREF(__pyx_tuple__9);

  /* "ims_extractor.pyx":92
 *     file_name_ims = file_name + '.ims'
 * 
 *     file_name_freq = file_name.split('.')[0] + '_frequency.csv'             # <<<<<<<<<<<<<<
 *     # file1 = open(file_name, 'r')
 *     #print file_name_ims
 */
  __pyx_tuple__12 = PyTuple_Pack(1, __pyx_kp_s__11); if (unlikely(!__pyx_tuple__12)) __PYX_ERR(0, 92, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__12);
  __Pyx_GIVEREF(__pyx_tuple__12);

  /* "ims_extractor.pyx":97
 *     #print file_name_ims, file_name.replace('.ms1', '') + '\\' + file_name.split('\\')[-1] + '.ims'
 *     #time.sleep(50)
 *     if os.path.isfile(file_name_ims) or os.path.isfile(file_name.replace('.ms1', '') + '\\' + file_name.split('\\')[-1] + '.ims'):             # <<<<<<<<<<<<<<
 *         print "file_exist!"
 *     else:
 */
  __pyx_tuple__13 = PyTuple_Pack(2, __pyx_kp_s_ms1, __pyx_kp_s__6); if (unlikely(!__pyx_tuple__13)) __PYX_ERR(0, 97, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__13);
  __Pyx_GIVEREF(__pyx_tuple__13);
  __pyx_tuple__15 = PyTuple_Pack(1, __pyx_kp_s__14); if (unlikely(!__pyx_tuple__15)) __PYX_ERR(0, 97, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__15);
  __Pyx_GIVEREF(__pyx_tuple__15);

  /* "ims_extractor.pyx":112
 * 
 *         # pool = multiprocessing.Pool(processes=multiprocessing.cpu_count())
 *         with open(file_name) as lines:             # <<<<<<<<<<<<<<
 *             temp_data = map(load_data, lines)
 *         # pool.close()
 */
  __pyx_tuple__17 = PyTuple_Pack(3, Py_None, Py_None, Py_None); if (unlikely(!__pyx_tuple__17)) __PYX_ERR(0, 112, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__17);
  __Pyx_GIVEREF(__pyx_tuple__17);

  /* "ims_extractor.pyx":140
 *                 effct += 1
 * 
 *         print "|", str(len(datax)).ljust(8), "spectra analyzed at", resolution, "ppm accuracy        |"             # <<<<<<<<<<<<<<
 *         # print effct, float(effct)/float(len(datax))
 *         print "| Time spent(s):", "{:10.4f}".format(timex), "                         |"
 */
  __pyx_tuple__19 = PyTuple_Pack(1, __pyx_int_8); if (unlikely(!__pyx_tuple__19)) __PYX_ERR(0, 140, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__19);
  __Pyx_GIVEREF(__pyx_tuple__19);

  /* "ims_extractor.pyx":290
 *         timex = (end - start1)
 *         print "| Time spent(s):", "{:10.4f}".format(timex), "                         |"
 *         print "| Number of spectra for inspection:", str(len(valid_spec)).ljust(15), " |"             # <<<<<<<<<<<<<<
 *         print "#----------------------------------------------------#"
 *         print "| Writing", file_name_ims.ljust(41), " |"
 */
  __pyx_tuple__21 = PyTuple_Pack(1, __pyx_int_15); if (unlikely(!__pyx_tuple__21)) __PYX_ERR(0, 290, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__21);
  __Pyx_GIVEREF(__pyx_tuple__21);

  /* "ims_extractor.pyx":292
 *         print "| Number of spectra for inspection:", str(len(valid_spec)).ljust(15), " |"
 *         print "#----------------------------------------------------#"
 *         print "| Writing", file_name_ims.ljust(41), " |"             # <<<<<<<<<<<<<<
 *         start1 = time.clock()
 * 
 */
  __pyx_tuple__23 = PyTuple_Pack(1, __pyx_int_41); if (unlikely(!__pyx_tuple__23)) __PYX_ERR(0, 292, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__23);
  __Pyx_GIVEREF(__pyx_tuple__23);

  /* "ims_extractor.pyx":302
 *                 ii = 2
 *                 zero_fill = []
 *                 time_available = sorted(datax[valid_spec[i]][2::3])             # <<<<<<<<<<<<<<
 *                 time_start = time_available[0]
 *                 time_end = time_available[-1]
 */
  __pyx_slice__24 = PySlice_New(__pyx_int_2, Py_None, __pyx_int_3); if (unlikely(!__pyx_slice__24)) __PYX_ERR(0, 302, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_slice__24);
  __Pyx_GIVEREF(__pyx_slice__24);

  /* "ims_extractor.pyx":11
 * 
 * 
 * def load_data(line):             # <<<<<<<<<<<<<<
 *     global ret_time
 *     if not line[0].isalpha():  # if start with 0-9 then get all data into its position
 */
  __pyx_tuple__27 = PyTuple_Pack(4, __pyx_n_s_line, __pyx_n_s_m, __pyx_n_s_position, __pyx_n_s_n); if (unlikely(!__pyx_tuple__27)) __PYX_ERR(0, 11, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__27);
  __Pyx_GIVEREF(__pyx_tuple__27);
  __pyx_codeobj__28 = (PyObject*)__Pyx_PyCode_New(1, 0, 4, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__27, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_E_Python_ims_extractor_pyx, __pyx_n_s_load_data, 11, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__28)) __PYX_ERR(0, 11, __pyx_L1_error)

  /* "ims_extractor.pyx":29
 * 
 * 
 * def extract_file(file_name):             # <<<<<<<<<<<<<<
 * 
 *     global start_time,end_time,tic,max_drift,resolution,res_factor,res_array,log_array,low_mass_array,log_factor,low_mass_factor,ret_time
 */
  __pyx_tuple__30 = PyTuple_Pack(58, __pyx_n_s_file_name, __pyx_n_s_start, __pyx_n_s_retention, __pyx_n_s_xa, __pyx_n_s_xi, __pyx_n_s_xm, __pyx_n_s_datax, __pyx_n_s_file_name_ims, __pyx_n_s_file_name_freq, __pyx_n_s_file2, __pyx_n_s_end, __pyx_n_s_timex, __pyx_n_s_start1, __pyx_n_s_lines, __pyx_n_s_temp_data, __pyx_n_s_item, __pyx_n_s_effct, __pyx_n_s_i, __pyx_n_s_a, __pyx_n_s_b, __pyx_n_s_valid_spec, __pyx_n_s_sequential_spec, __pyx_n_s_intensity_dict, __pyx_n_s_total, __pyx_n_s_count, __pyx_n_s_myi, __pyx_n_s_lastvalue, __pyx_n_s_last_idx, __pyx_n_s_start_idx, __pyx_n_s_idx, __pyx_n_s_value, __pyx_n_s_peak_count, __pyx_n_s_mass_center, __pyx_n_s_ii, __pyx_n_s_max_mass, __pyx_n_s_max_int, __pyx_n_s_int_max, __pyx_n_s_intt, __pyx_n_s_temp_int, __pyx_n_s_temp_diff, __pyx_n_s_peak_pos, __pyx_n_s_temp_peak_count, __pyx_n_s_iii, __pyx_n_s_num_of_valley, __pyx_n_s_zero_fill, __pyx_n_s_time_available, __pyx_n_s_time_start, __pyx_n_s_time_end, __pyx_n_s_increment, __pyx_n_s_difference, __pyx_n_s_zero_fill_flat, __pyx_n_s_total_spec, __pyx_n_s_floatarray3, __pyx_n_s_floatarray, __pyx_n_s_floatarray2, __pyx_n_s_file3, __pyx_n_s__29, __pyx_n_s_sublist); if (unlikely(!__pyx_tuple__30)) __PYX_ERR(0, 29, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_tuple__30);
  __Pyx_GIVEREF(__pyx_tuple__30);
  __pyx_codeobj__31 = (PyObject*)__Pyx_PyCode_New(1, 0, 58, 0, 0, __pyx_empty_bytes, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_tuple__30, __pyx_empty_tuple, __pyx_empty_tuple, __pyx_kp_s_E_Python_ims_extractor_pyx, __pyx_n_s_extract_file, 29, __pyx_empty_bytes); if (unlikely(!__pyx_codeobj__31)) __PYX_ERR(0, 29, __pyx_L1_error)
  __Pyx_RefNannyFinishContext();
  return 0;
  __pyx_L1_error:;
  __Pyx_RefNannyFinishContext();
  return -1;
}

static int __Pyx_InitGlobals(void) {
  if (__Pyx_InitStrings(__pyx_string_tab) < 0) __PYX_ERR(0, 1, __pyx_L1_error);
  __pyx_float_0_0 = PyFloat_FromDouble(0.0); if (unlikely(!__pyx_float_0_0)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_0_1 = PyFloat_FromDouble(0.1); if (unlikely(!__pyx_float_0_1)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_0_5 = PyFloat_FromDouble(0.5); if (unlikely(!__pyx_float_0_5)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_0_05 = PyFloat_FromDouble(0.05); if (unlikely(!__pyx_float_0_05)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_300000000_0 = PyFloat_FromDouble(300000000.0); if (unlikely(!__pyx_float_300000000_0)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_130_288149137774 = PyFloat_FromDouble(130.288149137774); if (unlikely(!__pyx_float_130_288149137774)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_169897000_433602 = PyFloat_FromDouble(169897000.433602); if (unlikely(!__pyx_float_169897000_433602)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_173_717445321994 = PyFloat_FromDouble(173.717445321994); if (unlikely(!__pyx_float_173_717445321994)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_217_146698086756 = PyFloat_FromDouble(217.146698086756); if (unlikely(!__pyx_float_217_146698086756)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_230102999_566398 = PyFloat_FromDouble(230102999.566398); if (unlikely(!__pyx_float_230102999_566398)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_247712125_471966 = PyFloat_FromDouble(247712125.471966); if (unlikely(!__pyx_float_247712125_471966)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_260_575907412860 = PyFloat_FromDouble(260.575907412860); if (unlikely(!__pyx_float_260_575907412860)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_260205999_132796 = PyFloat_FromDouble(260205999.132796); if (unlikely(!__pyx_float_260205999_132796)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_269897000_433602 = PyFloat_FromDouble(269897000.433602); if (unlikely(!__pyx_float_269897000_433602)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_277815125_038364 = PyFloat_FromDouble(277815125.038364); if (unlikely(!__pyx_float_277815125_038364)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_284509804_001426 = PyFloat_FromDouble(284509804.001426); if (unlikely(!__pyx_float_284509804_001426)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_290308998_699194 = PyFloat_FromDouble(290308998.699194); if (unlikely(!__pyx_float_290308998_699194)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_295424250_943933 = PyFloat_FromDouble(295424250.943933); if (unlikely(!__pyx_float_295424250_943933)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_304_005073319681 = PyFloat_FromDouble(304.005073319681); if (unlikely(!__pyx_float_304_005073319681)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_304139268_515822 = PyFloat_FromDouble(304139268.515822); if (unlikely(!__pyx_float_304139268_515822)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_307918124_604763 = PyFloat_FromDouble(307918124.604763); if (unlikely(!__pyx_float_307918124_604763)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_311394335_230684 = PyFloat_FromDouble(311394335.230684); if (unlikely(!__pyx_float_311394335_230684)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_314612803_567824 = PyFloat_FromDouble(314612803.567824); if (unlikely(!__pyx_float_314612803_567824)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_317609125_905568 = PyFloat_FromDouble(317609125.905568); if (unlikely(!__pyx_float_317609125_905568)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_320411998_265592 = PyFloat_FromDouble(320411998.265592); if (unlikely(!__pyx_float_320411998_265592)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_323044892_137827 = PyFloat_FromDouble(323044892.137827); if (unlikely(!__pyx_float_323044892_137827)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_325527250_510331 = PyFloat_FromDouble(325527250.510331); if (unlikely(!__pyx_float_325527250_510331)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_327875360_095283 = PyFloat_FromDouble(327875360.095283); if (unlikely(!__pyx_float_327875360_095283)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_330102999_566398 = PyFloat_FromDouble(330102999.566398); if (unlikely(!__pyx_float_330102999_566398)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_332221929_473392 = PyFloat_FromDouble(332221929.473392); if (unlikely(!__pyx_float_332221929_473392)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_334242268_082221 = PyFloat_FromDouble(334242268.082221); if (unlikely(!__pyx_float_334242268_082221)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_336172783_601759 = PyFloat_FromDouble(336172783.601759); if (unlikely(!__pyx_float_336172783_601759)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_338021124_171161 = PyFloat_FromDouble(338021124.171161); if (unlikely(!__pyx_float_338021124_171161)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_339794000_867204 = PyFloat_FromDouble(339794000.867204); if (unlikely(!__pyx_float_339794000_867204)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_341497334_797082 = PyFloat_FromDouble(341497334.797082); if (unlikely(!__pyx_float_341497334_797082)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_343136376_415899 = PyFloat_FromDouble(343136376.415899); if (unlikely(!__pyx_float_343136376_415899)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_344715803_134222 = PyFloat_FromDouble(344715803.134222); if (unlikely(!__pyx_float_344715803_134222)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_346239799_789896 = PyFloat_FromDouble(346239799.789896); if (unlikely(!__pyx_float_346239799_789896)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_347_434195788019 = PyFloat_FromDouble(347.434195788019); if (unlikely(!__pyx_float_347_434195788019)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_347712125_471966 = PyFloat_FromDouble(347712125.471966); if (unlikely(!__pyx_float_347712125_471966)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_349136169_383427 = PyFloat_FromDouble(349136169.383427); if (unlikely(!__pyx_float_349136169_383427)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_350514997_831991 = PyFloat_FromDouble(350514997.831991); if (unlikely(!__pyx_float_350514997_831991)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_351851393_987789 = PyFloat_FromDouble(351851393.987789); if (unlikely(!__pyx_float_351851393_987789)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_353147891_704225 = PyFloat_FromDouble(353147891.704225); if (unlikely(!__pyx_float_353147891_704225)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_354406804_435028 = PyFloat_FromDouble(354406804.435028); if (unlikely(!__pyx_float_354406804_435028)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_355630250_076729 = PyFloat_FromDouble(355630250.076729); if (unlikely(!__pyx_float_355630250_076729)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_356820172_406700 = PyFloat_FromDouble(356820172.406700); if (unlikely(!__pyx_float_356820172_406700)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_357978359_661681 = PyFloat_FromDouble(357978359.661681); if (unlikely(!__pyx_float_357978359_661681)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_359106460_702650 = PyFloat_FromDouble(359106460.702650); if (unlikely(!__pyx_float_359106460_702650)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_360205999_132796 = PyFloat_FromDouble(360205999.132796); if (unlikely(!__pyx_float_360205999_132796)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_361278385_671974 = PyFloat_FromDouble(361278385.671974); if (unlikely(!__pyx_float_361278385_671974)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_362324929_039790 = PyFloat_FromDouble(362324929.039790); if (unlikely(!__pyx_float_362324929_039790)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_363346845_557959 = PyFloat_FromDouble(363346845.557959); if (unlikely(!__pyx_float_363346845_557959)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_364345267_648619 = PyFloat_FromDouble(364345267.648619); if (unlikely(!__pyx_float_364345267_648619)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_365321251_377534 = PyFloat_FromDouble(365321251.377534); if (unlikely(!__pyx_float_365321251_377534)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_366275783_168157 = PyFloat_FromDouble(366275783.168157); if (unlikely(!__pyx_float_366275783_168157)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_367209785_793572 = PyFloat_FromDouble(367209785.793572); if (unlikely(!__pyx_float_367209785_793572)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_368124123_737559 = PyFloat_FromDouble(368124123.737559); if (unlikely(!__pyx_float_368124123_737559)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_369019608_002851 = PyFloat_FromDouble(369019608.002851); if (unlikely(!__pyx_float_369019608_002851)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_369897000_433602 = PyFloat_FromDouble(369897000.433602); if (unlikely(!__pyx_float_369897000_433602)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_390_863274827603 = PyFloat_FromDouble(390.863274827603); if (unlikely(!__pyx_float_390_863274827603)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_43_4294264720428 = PyFloat_FromDouble(43.4294264720428); if (unlikely(!__pyx_float_43_4294264720428)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_434_292310448164 = PyFloat_FromDouble(434.292310448164); if (unlikely(!__pyx_float_434_292310448164)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_477_721302630502 = PyFloat_FromDouble(477.721302630502); if (unlikely(!__pyx_float_477_721302630502)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_521_150251384347 = PyFloat_FromDouble(521.150251384347); if (unlikely(!__pyx_float_521_150251384347)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_564_579156719430 = PyFloat_FromDouble(564.579156719430); if (unlikely(!__pyx_float_564_579156719430)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_608_008018616550 = PyFloat_FromDouble(608.008018616550); if (unlikely(!__pyx_float_608_008018616550)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_651_436837095082 = PyFloat_FromDouble(651.436837095082); if (unlikely(!__pyx_float_651_436837095082)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_694_865612135824 = PyFloat_FromDouble(694.865612135824); if (unlikely(!__pyx_float_694_865612135824)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_738_294343748509 = PyFloat_FromDouble(738.294343748509); if (unlikely(!__pyx_float_738_294343748509)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_781_723031942865 = PyFloat_FromDouble(781.723031942865); if (unlikely(!__pyx_float_781_723031942865)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_825_151676699693 = PyFloat_FromDouble(825.151676699693); if (unlikely(!__pyx_float_825_151676699693)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_86_8588095243675 = PyFloat_FromDouble(86.8588095243675); if (unlikely(!__pyx_float_86_8588095243675)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_float_868_580278028723 = PyFloat_FromDouble(868.580278028723); if (unlikely(!__pyx_float_868_580278028723)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_0 = PyInt_FromLong(0); if (unlikely(!__pyx_int_0)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_1 = PyInt_FromLong(1); if (unlikely(!__pyx_int_1)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_2 = PyInt_FromLong(2); if (unlikely(!__pyx_int_2)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_3 = PyInt_FromLong(3); if (unlikely(!__pyx_int_3)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_8 = PyInt_FromLong(8); if (unlikely(!__pyx_int_8)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_15 = PyInt_FromLong(15); if (unlikely(!__pyx_int_15)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_25 = PyInt_FromLong(25); if (unlikely(!__pyx_int_25)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_41 = PyInt_FromLong(41); if (unlikely(!__pyx_int_41)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_50 = PyInt_FromLong(50); if (unlikely(!__pyx_int_50)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_60 = PyInt_FromLong(60); if (unlikely(!__pyx_int_60)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_99 = PyInt_FromLong(99); if (unlikely(!__pyx_int_99)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_100 = PyInt_FromLong(100); if (unlikely(!__pyx_int_100)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_2000 = PyInt_FromLong(2000); if (unlikely(!__pyx_int_2000)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_1000000 = PyInt_FromLong(1000000L); if (unlikely(!__pyx_int_1000000)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_1229628 = PyInt_FromLong(1229628L); if (unlikely(!__pyx_int_1229628)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_1844441 = PyInt_FromLong(1844441L); if (unlikely(!__pyx_int_1844441)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_3688881 = PyInt_FromLong(3688881L); if (unlikely(!__pyx_int_3688881)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_100000000 = PyInt_FromLong(100000000L); if (unlikely(!__pyx_int_100000000)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_200000000 = PyInt_FromLong(200000000L); if (unlikely(!__pyx_int_200000000)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_int_neg_100 = PyInt_FromLong(-100); if (unlikely(!__pyx_int_neg_100)) __PYX_ERR(0, 1, __pyx_L1_error)
  return 0;
  __pyx_L1_error:;
  return -1;
}

#if PY_MAJOR_VERSION < 3
PyMODINIT_FUNC initims_extractor(void); /*proto*/
PyMODINIT_FUNC initims_extractor(void)
#else
PyMODINIT_FUNC PyInit_ims_extractor(void); /*proto*/
PyMODINIT_FUNC PyInit_ims_extractor(void)
#endif
{
  PyObject *__pyx_t_1 = NULL;
  PyObject *__pyx_t_2 = NULL;
  __Pyx_RefNannyDeclarations
  #if CYTHON_REFNANNY
  __Pyx_RefNanny = __Pyx_RefNannyImportAPI("refnanny");
  if (!__Pyx_RefNanny) {
      PyErr_Clear();
      __Pyx_RefNanny = __Pyx_RefNannyImportAPI("Cython.Runtime.refnanny");
      if (!__Pyx_RefNanny)
          Py_FatalError("failed to import 'refnanny' module");
  }
  #endif
  __Pyx_RefNannySetupContext("PyMODINIT_FUNC PyInit_ims_extractor(void)", 0);
  if (__Pyx_check_binary_version() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_empty_tuple = PyTuple_New(0); if (unlikely(!__pyx_empty_tuple)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_empty_bytes = PyBytes_FromStringAndSize("", 0); if (unlikely(!__pyx_empty_bytes)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_empty_unicode = PyUnicode_FromStringAndSize("", 0); if (unlikely(!__pyx_empty_unicode)) __PYX_ERR(0, 1, __pyx_L1_error)
  #ifdef __Pyx_CyFunction_USED
  if (__pyx_CyFunction_init() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  #endif
  #ifdef __Pyx_FusedFunction_USED
  if (__pyx_FusedFunction_init() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  #endif
  #ifdef __Pyx_Coroutine_USED
  if (__pyx_Coroutine_init() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  #endif
  #ifdef __Pyx_Generator_USED
  if (__pyx_Generator_init() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  #endif
  #ifdef __Pyx_StopAsyncIteration_USED
  if (__pyx_StopAsyncIteration_init() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  #endif
  /*--- Library function declarations ---*/
  /*--- Threads initialization code ---*/
  #if defined(__PYX_FORCE_INIT_THREADS) && __PYX_FORCE_INIT_THREADS
  #ifdef WITH_THREAD /* Python build with threading support? */
  PyEval_InitThreads();
  #endif
  #endif
  /*--- Module creation code ---*/
  #if PY_MAJOR_VERSION < 3
  __pyx_m = Py_InitModule4("ims_extractor", __pyx_methods, 0, 0, PYTHON_API_VERSION); Py_XINCREF(__pyx_m);
  #else
  __pyx_m = PyModule_Create(&__pyx_moduledef);
  #endif
  if (unlikely(!__pyx_m)) __PYX_ERR(0, 1, __pyx_L1_error)
  __pyx_d = PyModule_GetDict(__pyx_m); if (unlikely(!__pyx_d)) __PYX_ERR(0, 1, __pyx_L1_error)
  Py_INCREF(__pyx_d);
  __pyx_b = PyImport_AddModule(__Pyx_BUILTIN_MODULE_NAME); if (unlikely(!__pyx_b)) __PYX_ERR(0, 1, __pyx_L1_error)
  #if CYTHON_COMPILING_IN_PYPY
  Py_INCREF(__pyx_b);
  #endif
  if (PyObject_SetAttrString(__pyx_m, "__builtins__", __pyx_b) < 0) __PYX_ERR(0, 1, __pyx_L1_error);
  /*--- Initialize various global constants etc. ---*/
  if (__Pyx_InitGlobals() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  #if PY_MAJOR_VERSION < 3 && (__PYX_DEFAULT_STRING_ENCODING_IS_ASCII || __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT)
  if (__Pyx_init_sys_getdefaultencoding_params() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  #endif
  if (__pyx_module_is_main_ims_extractor) {
    if (PyObject_SetAttrString(__pyx_m, "__name__", __pyx_n_s_main) < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  }
  #if PY_MAJOR_VERSION >= 3
  {
    PyObject *modules = PyImport_GetModuleDict(); if (unlikely(!modules)) __PYX_ERR(0, 1, __pyx_L1_error)
    if (!PyDict_GetItemString(modules, "ims_extractor")) {
      if (unlikely(PyDict_SetItemString(modules, "ims_extractor", __pyx_m) < 0)) __PYX_ERR(0, 1, __pyx_L1_error)
    }
  }
  #endif
  /*--- Builtin init code ---*/
  if (__Pyx_InitCachedBuiltins() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  /*--- Constants init code ---*/
  if (__Pyx_InitCachedConstants() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  /*--- Global init code ---*/
  /*--- Variable export code ---*/
  /*--- Function export code ---*/
  /*--- Type init code ---*/
  /*--- Type import code ---*/
  /*--- Variable import code ---*/
  /*--- Function import code ---*/
  /*--- Execution code ---*/
  #if defined(__Pyx_Generator_USED) || defined(__Pyx_Coroutine_USED)
  if (__Pyx_patch_abc() < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  #endif

  /* "ims_extractor.pyx":2
 * #!/usr/bin/env python
 * import os             # <<<<<<<<<<<<<<
 * from math import log10 as log
 * from array import array
 */
  __pyx_t_1 = __Pyx_Import(__pyx_n_s_os, 0, -1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 2, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_os, __pyx_t_1) < 0) __PYX_ERR(0, 2, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "ims_extractor.pyx":3
 * #!/usr/bin/env python
 * import os
 * from math import log10 as log             # <<<<<<<<<<<<<<
 * from array import array
 * import time
 */
  __pyx_t_1 = PyList_New(1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 3, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__pyx_n_s_log10);
  __Pyx_GIVEREF(__pyx_n_s_log10);
  PyList_SET_ITEM(__pyx_t_1, 0, __pyx_n_s_log10);
  __pyx_t_2 = __Pyx_Import(__pyx_n_s_math, __pyx_t_1, -1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 3, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_ImportFrom(__pyx_t_2, __pyx_n_s_log10); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 3, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_log, __pyx_t_1) < 0) __PYX_ERR(0, 3, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "ims_extractor.pyx":4
 * import os
 * from math import log10 as log
 * from array import array             # <<<<<<<<<<<<<<
 * import time
 * from operator import sub
 */
  __pyx_t_2 = PyList_New(1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 4, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_INCREF(__pyx_n_s_array);
  __Pyx_GIVEREF(__pyx_n_s_array);
  PyList_SET_ITEM(__pyx_t_2, 0, __pyx_n_s_array);
  __pyx_t_1 = __Pyx_Import(__pyx_n_s_array, __pyx_t_2, -1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 4, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __pyx_t_2 = __Pyx_ImportFrom(__pyx_t_1, __pyx_n_s_array); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 4, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_array, __pyx_t_2) < 0) __PYX_ERR(0, 4, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "ims_extractor.pyx":5
 * from math import log10 as log
 * from array import array
 * import time             # <<<<<<<<<<<<<<
 * from operator import sub
 * 
 */
  __pyx_t_1 = __Pyx_Import(__pyx_n_s_time, 0, -1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 5, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_time, __pyx_t_1) < 0) __PYX_ERR(0, 5, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;

  /* "ims_extractor.pyx":6
 * from array import array
 * import time
 * from operator import sub             # <<<<<<<<<<<<<<
 * 
 * 
 */
  __pyx_t_1 = PyList_New(1); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 6, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  __Pyx_INCREF(__pyx_n_s_sub);
  __Pyx_GIVEREF(__pyx_n_s_sub);
  PyList_SET_ITEM(__pyx_t_1, 0, __pyx_n_s_sub);
  __pyx_t_2 = __Pyx_Import(__pyx_n_s_operator, __pyx_t_1, -1); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 6, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __pyx_t_1 = __Pyx_ImportFrom(__pyx_t_2, __pyx_n_s_sub); if (unlikely(!__pyx_t_1)) __PYX_ERR(0, 6, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_1);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_sub, __pyx_t_1) < 0) __PYX_ERR(0, 6, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_1); __pyx_t_1 = 0;
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "ims_extractor.pyx":11
 * 
 * 
 * def load_data(line):             # <<<<<<<<<<<<<<
 *     global ret_time
 *     if not line[0].isalpha():  # if start with 0-9 then get all data into its position
 */
  __pyx_t_2 = PyCFunction_NewEx(&__pyx_mdef_13ims_extractor_1load_data, NULL, __pyx_n_s_ims_extractor); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 11, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_load_data, __pyx_t_2) < 0) __PYX_ERR(0, 11, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "ims_extractor.pyx":29
 * 
 * 
 * def extract_file(file_name):             # <<<<<<<<<<<<<<
 * 
 *     global start_time,end_time,tic,max_drift,resolution,res_factor,res_array,log_array,low_mass_array,log_factor,low_mass_factor,ret_time
 */
  __pyx_t_2 = PyCFunction_NewEx(&__pyx_mdef_13ims_extractor_3extract_file, NULL, __pyx_n_s_ims_extractor); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 29, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_extract_file, __pyx_t_2) < 0) __PYX_ERR(0, 29, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /* "ims_extractor.pyx":1
 * #!/usr/bin/env python             # <<<<<<<<<<<<<<
 * import os
 * from math import log10 as log
 */
  __pyx_t_2 = PyDict_New(); if (unlikely(!__pyx_t_2)) __PYX_ERR(0, 1, __pyx_L1_error)
  __Pyx_GOTREF(__pyx_t_2);
  if (PyDict_SetItem(__pyx_d, __pyx_n_s_test, __pyx_t_2) < 0) __PYX_ERR(0, 1, __pyx_L1_error)
  __Pyx_DECREF(__pyx_t_2); __pyx_t_2 = 0;

  /*--- Wrapped vars code ---*/

  goto __pyx_L0;
  __pyx_L1_error:;
  __Pyx_XDECREF(__pyx_t_1);
  __Pyx_XDECREF(__pyx_t_2);
  if (__pyx_m) {
    if (__pyx_d) {
      __Pyx_AddTraceback("init ims_extractor", __pyx_clineno, __pyx_lineno, __pyx_filename);
    }
    Py_DECREF(__pyx_m); __pyx_m = 0;
  } else if (!PyErr_Occurred()) {
    PyErr_SetString(PyExc_ImportError, "init ims_extractor");
  }
  __pyx_L0:;
  __Pyx_RefNannyFinishContext();
  #if PY_MAJOR_VERSION < 3
  return;
  #else
  return __pyx_m;
  #endif
}

/* --- Runtime support code --- */
/* Refnanny */
#if CYTHON_REFNANNY
static __Pyx_RefNannyAPIStruct *__Pyx_RefNannyImportAPI(const char *modname) {
    PyObject *m = NULL, *p = NULL;
    void *r = NULL;
    m = PyImport_ImportModule((char *)modname);
    if (!m) goto end;
    p = PyObject_GetAttrString(m, (char *)"RefNannyAPI");
    if (!p) goto end;
    r = PyLong_AsVoidPtr(p);
end:
    Py_XDECREF(p);
    Py_XDECREF(m);
    return (__Pyx_RefNannyAPIStruct *)r;
}
#endif

/* GetBuiltinName */
static PyObject *__Pyx_GetBuiltinName(PyObject *name) {
    PyObject* result = __Pyx_PyObject_GetAttrStr(__pyx_b, name);
    if (unlikely(!result)) {
        PyErr_Format(PyExc_NameError,
#if PY_MAJOR_VERSION >= 3
            "name '%U' is not defined", name);
#else
            "name '%.200s' is not defined", PyString_AS_STRING(name));
#endif
    }
    return result;
}

/* GetItemInt */
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Generic(PyObject *o, PyObject* j) {
    PyObject *r;
    if (!j) return NULL;
    r = PyObject_GetItem(o, j);
    Py_DECREF(j);
    return r;
}
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_List_Fast(PyObject *o, Py_ssize_t i,
                                                              CYTHON_NCP_UNUSED int wraparound,
                                                              CYTHON_NCP_UNUSED int boundscheck) {
#if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
    if (wraparound & unlikely(i < 0)) i += PyList_GET_SIZE(o);
    if ((!boundscheck) || likely((0 <= i) & (i < PyList_GET_SIZE(o)))) {
        PyObject *r = PyList_GET_ITEM(o, i);
        Py_INCREF(r);
        return r;
    }
    return __Pyx_GetItemInt_Generic(o, PyInt_FromSsize_t(i));
#else
    return PySequence_GetItem(o, i);
#endif
}
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Tuple_Fast(PyObject *o, Py_ssize_t i,
                                                              CYTHON_NCP_UNUSED int wraparound,
                                                              CYTHON_NCP_UNUSED int boundscheck) {
#if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS
    if (wraparound & unlikely(i < 0)) i += PyTuple_GET_SIZE(o);
    if ((!boundscheck) || likely((0 <= i) & (i < PyTuple_GET_SIZE(o)))) {
        PyObject *r = PyTuple_GET_ITEM(o, i);
        Py_INCREF(r);
        return r;
    }
    return __Pyx_GetItemInt_Generic(o, PyInt_FromSsize_t(i));
#else
    return PySequence_GetItem(o, i);
#endif
}
static CYTHON_INLINE PyObject *__Pyx_GetItemInt_Fast(PyObject *o, Py_ssize_t i, int is_list,
                                                     CYTHON_NCP_UNUSED int wraparound,
                                                     CYTHON_NCP_UNUSED int boundscheck) {
#if CYTHON_ASSUME_SAFE_MACROS && !CYTHON_AVOID_BORROWED_REFS && CYTHON_USE_TYPE_SLOTS
    if (is_list || PyList_CheckExact(o)) {
        Py_ssize_t n = ((!wraparound) | likely(i >= 0)) ? i : i + PyList_GET_SIZE(o);
        if ((!boundscheck) || (likely((n >= 0) & (n < PyList_GET_SIZE(o))))) {
            PyObject *r = PyList_GET_ITEM(o, n);
            Py_INCREF(r);
            return r;
        }
    }
    else if (PyTuple_CheckExact(o)) {
        Py_ssize_t n = ((!wraparound) | likely(i >= 0)) ? i : i + PyTuple_GET_SIZE(o);
        if ((!boundscheck) || likely((n >= 0) & (n < PyTuple_GET_SIZE(o)))) {
            PyObject *r = PyTuple_GET_ITEM(o, n);
            Py_INCREF(r);
            return r;
        }
    } else {
        PySequenceMethods *m = Py_TYPE(o)->tp_as_sequence;
        if (likely(m && m->sq_item)) {
            if (wraparound && unlikely(i < 0) && likely(m->sq_length)) {
                Py_ssize_t l = m->sq_length(o);
                if (likely(l >= 0)) {
                    i += l;
                } else {
                    if (!PyErr_ExceptionMatches(PyExc_OverflowError))
                        return NULL;
                    PyErr_Clear();
                }
            }
            return m->sq_item(o, i);
        }
    }
#else
    if (is_list || PySequence_Check(o)) {
        return PySequence_GetItem(o, i);
    }
#endif
    return __Pyx_GetItemInt_Generic(o, PyInt_FromSsize_t(i));
}

/* PyCFunctionFastCall */
#if CYTHON_FAST_PYCCALL
static CYTHON_INLINE PyObject * __Pyx_PyCFunction_FastCall(PyObject *func_obj, PyObject **args, Py_ssize_t nargs) {
    PyCFunctionObject *func = (PyCFunctionObject*)func_obj;
    PyCFunction meth = PyCFunction_GET_FUNCTION(func);
    PyObject *self = PyCFunction_GET_SELF(func);
    assert(PyCFunction_Check(func));
    assert(METH_FASTCALL == (PyCFunction_GET_FLAGS(func) & ~(METH_CLASS | METH_STATIC | METH_COEXIST)));
    assert(nargs >= 0);
    assert(nargs == 0 || args != NULL);
    /* _PyCFunction_FastCallDict() must not be called with an exception set,
       because it may clear it (directly or indirectly) and so the
       caller loses its exception */
    assert(!PyErr_Occurred());
    return (*((__Pyx_PyCFunctionFast)meth)) (self, args, nargs, NULL);
}
#endif  // CYTHON_FAST_PYCCALL

/* PyFunctionFastCall */
#if CYTHON_FAST_PYCALL
#include "frameobject.h"
static PyObject* __Pyx_PyFunction_FastCallNoKw(PyCodeObject *co, PyObject **args, Py_ssize_t na,
                                               PyObject *globals) {
    PyFrameObject *f;
    PyThreadState *tstate = PyThreadState_GET();
    PyObject **fastlocals;
    Py_ssize_t i;
    PyObject *result;
    assert(globals != NULL);
    /* XXX Perhaps we should create a specialized
       PyFrame_New() that doesn't take locals, but does
       take builtins without sanity checking them.
       */
    assert(tstate != NULL);
    f = PyFrame_New(tstate, co, globals, NULL);
    if (f == NULL) {
        return NULL;
    }
    fastlocals = f->f_localsplus;
    for (i = 0; i < na; i++) {
        Py_INCREF(*args);
        fastlocals[i] = *args++;
    }
    result = PyEval_EvalFrameEx(f,0);
    ++tstate->recursion_depth;
    Py_DECREF(f);
    --tstate->recursion_depth;
    return result;
}
#if 1 || PY_VERSION_HEX < 0x030600B1
static PyObject *__Pyx_PyFunction_FastCallDict(PyObject *func, PyObject **args, int nargs, PyObject *kwargs) {
    PyCodeObject *co = (PyCodeObject *)PyFunction_GET_CODE(func);
    PyObject *globals = PyFunction_GET_GLOBALS(func);
    PyObject *argdefs = PyFunction_GET_DEFAULTS(func);
    PyObject *closure;
#if PY_MAJOR_VERSION >= 3
    PyObject *kwdefs;
#endif
    PyObject *kwtuple, **k;
    PyObject **d;
    Py_ssize_t nd;
    Py_ssize_t nk;
    PyObject *result;
    assert(kwargs == NULL || PyDict_Check(kwargs));
    nk = kwargs ? PyDict_Size(kwargs) : 0;
    if (Py_EnterRecursiveCall((char*)" while calling a Python object")) {
        return NULL;
    }
    if (
#if PY_MAJOR_VERSION >= 3
            co->co_kwonlyargcount == 0 &&
#endif
            likely(kwargs == NULL || nk == 0) &&
            co->co_flags == (CO_OPTIMIZED | CO_NEWLOCALS | CO_NOFREE)) {
        if (argdefs == NULL && co->co_argcount == nargs) {
            result = __Pyx_PyFunction_FastCallNoKw(co, args, nargs, globals);
            goto done;
        }
        else if (nargs == 0 && argdefs != NULL
                 && co->co_argcount == Py_SIZE(argdefs)) {
            /* function called with no arguments, but all parameters have
               a default value: use default values as arguments .*/
            args = &PyTuple_GET_ITEM(argdefs, 0);
            result =__Pyx_PyFunction_FastCallNoKw(co, args, Py_SIZE(argdefs), globals);
            goto done;
        }
    }
    if (kwargs != NULL) {
        Py_ssize_t pos, i;
        kwtuple = PyTuple_New(2 * nk);
        if (kwtuple == NULL) {
            result = NULL;
            goto done;
        }
        k = &PyTuple_GET_ITEM(kwtuple, 0);
        pos = i = 0;
        while (PyDict_Next(kwargs, &pos, &k[i], &k[i+1])) {
            Py_INCREF(k[i]);
            Py_INCREF(k[i+1]);
            i += 2;
        }
        nk = i / 2;
    }
    else {
        kwtuple = NULL;
        k = NULL;
    }
    closure = PyFunction_GET_CLOSURE(func);
#if PY_MAJOR_VERSION >= 3
    kwdefs = PyFunction_GET_KW_DEFAULTS(func);
#endif
    if (argdefs != NULL) {
        d = &PyTuple_GET_ITEM(argdefs, 0);
        nd = Py_SIZE(argdefs);
    }
    else {
        d = NULL;
        nd = 0;
    }
#if PY_MAJOR_VERSION >= 3
    result = PyEval_EvalCodeEx((PyObject*)co, globals, (PyObject *)NULL,
                               args, nargs,
                               k, (int)nk,
                               d, (int)nd, kwdefs, closure);
#else
    result = PyEval_EvalCodeEx(co, globals, (PyObject *)NULL,
                               args, nargs,
                               k, (int)nk,
                               d, (int)nd, closure);
#endif
    Py_XDECREF(kwtuple);
done:
    Py_LeaveRecursiveCall();
    return result;
}
#endif  // CPython < 3.6
#endif  // CYTHON_FAST_PYCALL

/* PyObjectCall */
#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_Call(PyObject *func, PyObject *arg, PyObject *kw) {
    PyObject *result;
    ternaryfunc call = func->ob_type->tp_call;
    if (unlikely(!call))
        return PyObject_Call(func, arg, kw);
    if (unlikely(Py_EnterRecursiveCall((char*)" while calling a Python object")))
        return NULL;
    result = (*call)(func, arg, kw);
    Py_LeaveRecursiveCall();
    if (unlikely(!result) && unlikely(!PyErr_Occurred())) {
        PyErr_SetString(
            PyExc_SystemError,
            "NULL result without error in PyObject_Call");
    }
    return result;
}
#endif

/* PyObjectCallMethO */
#if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallMethO(PyObject *func, PyObject *arg) {
    PyObject *self, *result;
    PyCFunction cfunc;
    cfunc = PyCFunction_GET_FUNCTION(func);
    self = PyCFunction_GET_SELF(func);
    if (unlikely(Py_EnterRecursiveCall((char*)" while calling a Python object")))
        return NULL;
    result = cfunc(self, arg);
    Py_LeaveRecursiveCall();
    if (unlikely(!result) && unlikely(!PyErr_Occurred())) {
        PyErr_SetString(
            PyExc_SystemError,
            "NULL result without error in PyObject_Call");
    }
    return result;
}
#endif

/* PyObjectCallOneArg */
#if CYTHON_COMPILING_IN_CPYTHON
static PyObject* __Pyx__PyObject_CallOneArg(PyObject *func, PyObject *arg) {
    PyObject *result;
    PyObject *args = PyTuple_New(1);
    if (unlikely(!args)) return NULL;
    Py_INCREF(arg);
    PyTuple_SET_ITEM(args, 0, arg);
    result = __Pyx_PyObject_Call(func, args, NULL);
    Py_DECREF(args);
    return result;
}
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallOneArg(PyObject *func, PyObject *arg) {
#if CYTHON_FAST_PYCALL
    if (PyFunction_Check(func)) {
        return __Pyx_PyFunction_FastCall(func, &arg, 1);
    }
#endif
#ifdef __Pyx_CyFunction_USED
    if (likely(PyCFunction_Check(func) || PyObject_TypeCheck(func, __pyx_CyFunctionType))) {
#else
    if (likely(PyCFunction_Check(func))) {
#endif
        if (likely(PyCFunction_GET_FLAGS(func) & METH_O)) {
            return __Pyx_PyObject_CallMethO(func, arg);
#if CYTHON_FAST_PYCCALL
        } else if (PyCFunction_GET_FLAGS(func) & METH_FASTCALL) {
            return __Pyx_PyCFunction_FastCall(func, &arg, 1);
#endif
        }
    }
    return __Pyx__PyObject_CallOneArg(func, arg);
}
#else
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallOneArg(PyObject *func, PyObject *arg) {
    PyObject *result;
    PyObject *args = PyTuple_Pack(1, arg);
    if (unlikely(!args)) return NULL;
    result = __Pyx_PyObject_Call(func, args, NULL);
    Py_DECREF(args);
    return result;
}
#endif

/* PyObjectCallNoArg */
  #if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyObject_CallNoArg(PyObject *func) {
#if CYTHON_FAST_PYCALL
    if (PyFunction_Check(func)) {
        return __Pyx_PyFunction_FastCall(func, NULL, 0);
    }
#endif
#ifdef __Pyx_CyFunction_USED
    if (likely(PyCFunction_Check(func) || PyObject_TypeCheck(func, __pyx_CyFunctionType))) {
#else
    if (likely(PyCFunction_Check(func))) {
#endif
        if (likely(PyCFunction_GET_FLAGS(func) & METH_NOARGS)) {
            return __Pyx_PyObject_CallMethO(func, NULL);
        }
    }
    return __Pyx_PyObject_Call(func, __pyx_empty_tuple, NULL);
}
#endif

/* PyIntBinop */
    #if !CYTHON_COMPILING_IN_PYPY
static PyObject* __Pyx_PyInt_SubtractObjC(PyObject *op1, PyObject *op2, CYTHON_UNUSED long intval, CYTHON_UNUSED int inplace) {
    #if PY_MAJOR_VERSION < 3
    if (likely(PyInt_CheckExact(op1))) {
        const long b = intval;
        long x;
        long a = PyInt_AS_LONG(op1);
            x = (long)((unsigned long)a - b);
            if (likely((x^a) >= 0 || (x^~b) >= 0))
                return PyInt_FromLong(x);
            return PyLong_Type.tp_as_number->nb_subtract(op1, op2);
    }
    #endif
    #if CYTHON_USE_PYLONG_INTERNALS
    if (likely(PyLong_CheckExact(op1))) {
        const long b = intval;
        long a, x;
#ifdef HAVE_LONG_LONG
        const PY_LONG_LONG llb = intval;
        PY_LONG_LONG lla, llx;
#endif
        const digit* digits = ((PyLongObject*)op1)->ob_digit;
        const Py_ssize_t size = Py_SIZE(op1);
        if (likely(__Pyx_sst_abs(size) <= 1)) {
            a = likely(size) ? digits[0] : 0;
            if (size == -1) a = -a;
        } else {
            switch (size) {
                case -2:
                    if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
                        a = -(long) (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 2 * PyLong_SHIFT) {
                        lla = -(PY_LONG_LONG) (((((unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                case 2:
                    if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
                        a = (long) (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 2 * PyLong_SHIFT) {
                        lla = (PY_LONG_LONG) (((((unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                case -3:
                    if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
                        a = -(long) (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 3 * PyLong_SHIFT) {
                        lla = -(PY_LONG_LONG) (((((((unsigned PY_LONG_LONG)digits[2]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                case 3:
                    if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
                        a = (long) (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 3 * PyLong_SHIFT) {
                        lla = (PY_LONG_LONG) (((((((unsigned PY_LONG_LONG)digits[2]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                case -4:
                    if (8 * sizeof(long) - 1 > 4 * PyLong_SHIFT) {
                        a = -(long) (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 4 * PyLong_SHIFT) {
                        lla = -(PY_LONG_LONG) (((((((((unsigned PY_LONG_LONG)digits[3]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[2]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                case 4:
                    if (8 * sizeof(long) - 1 > 4 * PyLong_SHIFT) {
                        a = (long) (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 4 * PyLong_SHIFT) {
                        lla = (PY_LONG_LONG) (((((((((unsigned PY_LONG_LONG)digits[3]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[2]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                default: return PyLong_Type.tp_as_number->nb_subtract(op1, op2);
            }
        }
                x = a - b;
            return PyLong_FromLong(x);
#ifdef HAVE_LONG_LONG
        long_long:
                llx = lla - llb;
            return PyLong_FromLongLong(llx);
#endif
        
        
    }
    #endif
    if (PyFloat_CheckExact(op1)) {
        const long b = intval;
        double a = PyFloat_AS_DOUBLE(op1);
            double result;
            PyFPE_START_PROTECT("subtract", return NULL)
            result = ((double)a) - (double)b;
            PyFPE_END_PROTECT(result)
            return PyFloat_FromDouble(result);
    }
    return (inplace ? PyNumber_InPlaceSubtract : PyNumber_Subtract)(op1, op2);
}
#endif

/* GetModuleGlobalName */
    static CYTHON_INLINE PyObject *__Pyx_GetModuleGlobalName(PyObject *name) {
    PyObject *result;
#if !CYTHON_AVOID_BORROWED_REFS
    result = PyDict_GetItem(__pyx_d, name);
    if (likely(result)) {
        Py_INCREF(result);
    } else {
#else
    result = PyObject_GetItem(__pyx_d, name);
    if (!result) {
        PyErr_Clear();
#endif
        result = __Pyx_GetBuiltinName(name);
    }
    return result;
}

/* BytesEquals */
      static CYTHON_INLINE int __Pyx_PyBytes_Equals(PyObject* s1, PyObject* s2, int equals) {
#if CYTHON_COMPILING_IN_PYPY
    return PyObject_RichCompareBool(s1, s2, equals);
#else
    if (s1 == s2) {
        return (equals == Py_EQ);
    } else if (PyBytes_CheckExact(s1) & PyBytes_CheckExact(s2)) {
        const char *ps1, *ps2;
        Py_ssize_t length = PyBytes_GET_SIZE(s1);
        if (length != PyBytes_GET_SIZE(s2))
            return (equals == Py_NE);
        ps1 = PyBytes_AS_STRING(s1);
        ps2 = PyBytes_AS_STRING(s2);
        if (ps1[0] != ps2[0]) {
            return (equals == Py_NE);
        } else if (length == 1) {
            return (equals == Py_EQ);
        } else {
            int result = memcmp(ps1, ps2, (size_t)length);
            return (equals == Py_EQ) ? (result == 0) : (result != 0);
        }
    } else if ((s1 == Py_None) & PyBytes_CheckExact(s2)) {
        return (equals == Py_NE);
    } else if ((s2 == Py_None) & PyBytes_CheckExact(s1)) {
        return (equals == Py_NE);
    } else {
        int result;
        PyObject* py_result = PyObject_RichCompare(s1, s2, equals);
        if (!py_result)
            return -1;
        result = __Pyx_PyObject_IsTrue(py_result);
        Py_DECREF(py_result);
        return result;
    }
#endif
}

/* UnicodeEquals */
      static CYTHON_INLINE int __Pyx_PyUnicode_Equals(PyObject* s1, PyObject* s2, int equals) {
#if CYTHON_COMPILING_IN_PYPY
    return PyObject_RichCompareBool(s1, s2, equals);
#else
#if PY_MAJOR_VERSION < 3
    PyObject* owned_ref = NULL;
#endif
    int s1_is_unicode, s2_is_unicode;
    if (s1 == s2) {
        goto return_eq;
    }
    s1_is_unicode = PyUnicode_CheckExact(s1);
    s2_is_unicode = PyUnicode_CheckExact(s2);
#if PY_MAJOR_VERSION < 3
    if ((s1_is_unicode & (!s2_is_unicode)) && PyString_CheckExact(s2)) {
        owned_ref = PyUnicode_FromObject(s2);
        if (unlikely(!owned_ref))
            return -1;
        s2 = owned_ref;
        s2_is_unicode = 1;
    } else if ((s2_is_unicode & (!s1_is_unicode)) && PyString_CheckExact(s1)) {
        owned_ref = PyUnicode_FromObject(s1);
        if (unlikely(!owned_ref))
            return -1;
        s1 = owned_ref;
        s1_is_unicode = 1;
    } else if (((!s2_is_unicode) & (!s1_is_unicode))) {
        return __Pyx_PyBytes_Equals(s1, s2, equals);
    }
#endif
    if (s1_is_unicode & s2_is_unicode) {
        Py_ssize_t length;
        int kind;
        void *data1, *data2;
        if (unlikely(__Pyx_PyUnicode_READY(s1) < 0) || unlikely(__Pyx_PyUnicode_READY(s2) < 0))
            return -1;
        length = __Pyx_PyUnicode_GET_LENGTH(s1);
        if (length != __Pyx_PyUnicode_GET_LENGTH(s2)) {
            goto return_ne;
        }
        kind = __Pyx_PyUnicode_KIND(s1);
        if (kind != __Pyx_PyUnicode_KIND(s2)) {
            goto return_ne;
        }
        data1 = __Pyx_PyUnicode_DATA(s1);
        data2 = __Pyx_PyUnicode_DATA(s2);
        if (__Pyx_PyUnicode_READ(kind, data1, 0) != __Pyx_PyUnicode_READ(kind, data2, 0)) {
            goto return_ne;
        } else if (length == 1) {
            goto return_eq;
        } else {
            int result = memcmp(data1, data2, (size_t)(length * kind));
            #if PY_MAJOR_VERSION < 3
            Py_XDECREF(owned_ref);
            #endif
            return (equals == Py_EQ) ? (result == 0) : (result != 0);
        }
    } else if ((s1 == Py_None) & s2_is_unicode) {
        goto return_ne;
    } else if ((s2 == Py_None) & s1_is_unicode) {
        goto return_ne;
    } else {
        int result;
        PyObject* py_result = PyObject_RichCompare(s1, s2, equals);
        if (!py_result)
            return -1;
        result = __Pyx_PyObject_IsTrue(py_result);
        Py_DECREF(py_result);
        return result;
    }
return_eq:
    #if PY_MAJOR_VERSION < 3
    Py_XDECREF(owned_ref);
    #endif
    return (equals == Py_EQ);
return_ne:
    #if PY_MAJOR_VERSION < 3
    Py_XDECREF(owned_ref);
    #endif
    return (equals == Py_NE);
#endif
}

/* PyIntBinop */
      #if !CYTHON_COMPILING_IN_PYPY
static PyObject* __Pyx_PyInt_AddObjC(PyObject *op1, PyObject *op2, CYTHON_UNUSED long intval, CYTHON_UNUSED int inplace) {
    #if PY_MAJOR_VERSION < 3
    if (likely(PyInt_CheckExact(op1))) {
        const long b = intval;
        long x;
        long a = PyInt_AS_LONG(op1);
            x = (long)((unsigned long)a + b);
            if (likely((x^a) >= 0 || (x^b) >= 0))
                return PyInt_FromLong(x);
            return PyLong_Type.tp_as_number->nb_add(op1, op2);
    }
    #endif
    #if CYTHON_USE_PYLONG_INTERNALS
    if (likely(PyLong_CheckExact(op1))) {
        const long b = intval;
        long a, x;
#ifdef HAVE_LONG_LONG
        const PY_LONG_LONG llb = intval;
        PY_LONG_LONG lla, llx;
#endif
        const digit* digits = ((PyLongObject*)op1)->ob_digit;
        const Py_ssize_t size = Py_SIZE(op1);
        if (likely(__Pyx_sst_abs(size) <= 1)) {
            a = likely(size) ? digits[0] : 0;
            if (size == -1) a = -a;
        } else {
            switch (size) {
                case -2:
                    if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
                        a = -(long) (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 2 * PyLong_SHIFT) {
                        lla = -(PY_LONG_LONG) (((((unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                case 2:
                    if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
                        a = (long) (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 2 * PyLong_SHIFT) {
                        lla = (PY_LONG_LONG) (((((unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                case -3:
                    if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
                        a = -(long) (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 3 * PyLong_SHIFT) {
                        lla = -(PY_LONG_LONG) (((((((unsigned PY_LONG_LONG)digits[2]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                case 3:
                    if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
                        a = (long) (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 3 * PyLong_SHIFT) {
                        lla = (PY_LONG_LONG) (((((((unsigned PY_LONG_LONG)digits[2]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                case -4:
                    if (8 * sizeof(long) - 1 > 4 * PyLong_SHIFT) {
                        a = -(long) (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 4 * PyLong_SHIFT) {
                        lla = -(PY_LONG_LONG) (((((((((unsigned PY_LONG_LONG)digits[3]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[2]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                case 4:
                    if (8 * sizeof(long) - 1 > 4 * PyLong_SHIFT) {
                        a = (long) (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0]));
                        break;
#ifdef HAVE_LONG_LONG
                    } else if (8 * sizeof(PY_LONG_LONG) - 1 > 4 * PyLong_SHIFT) {
                        lla = (PY_LONG_LONG) (((((((((unsigned PY_LONG_LONG)digits[3]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[2]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[1]) << PyLong_SHIFT) | (unsigned PY_LONG_LONG)digits[0]));
                        goto long_long;
#endif
                    }
                default: return PyLong_Type.tp_as_number->nb_add(op1, op2);
            }
        }
                x = a + b;
            return PyLong_FromLong(x);
#ifdef HAVE_LONG_LONG
        long_long:
                llx = lla + llb;
            return PyLong_FromLongLong(llx);
#endif
        
        
    }
    #endif
    if (PyFloat_CheckExact(op1)) {
        const long b = intval;
        double a = PyFloat_AS_DOUBLE(op1);
            double result;
            PyFPE_START_PROTECT("add", return NULL)
            result = ((double)a) + (double)b;
            PyFPE_END_PROTECT(result)
            return PyFloat_FromDouble(result);
    }
    return (inplace ? PyNumber_InPlaceAdd : PyNumber_Add)(op1, op2);
}
#endif

/* SaveResetException */
      #if CYTHON_FAST_THREAD_STATE
static CYTHON_INLINE void __Pyx__ExceptionSave(PyThreadState *tstate, PyObject **type, PyObject **value, PyObject **tb) {
    *type = tstate->exc_type;
    *value = tstate->exc_value;
    *tb = tstate->exc_traceback;
    Py_XINCREF(*type);
    Py_XINCREF(*value);
    Py_XINCREF(*tb);
}
static CYTHON_INLINE void __Pyx__ExceptionReset(PyThreadState *tstate, PyObject *type, PyObject *value, PyObject *tb) {
    PyObject *tmp_type, *tmp_value, *tmp_tb;
    tmp_type = tstate->exc_type;
    tmp_value = tstate->exc_value;
    tmp_tb = tstate->exc_traceback;
    tstate->exc_type = type;
    tstate->exc_value = value;
    tstate->exc_traceback = tb;
    Py_XDECREF(tmp_type);
    Py_XDECREF(tmp_value);
    Py_XDECREF(tmp_tb);
}
#endif

/* GetException */
      #if CYTHON_FAST_THREAD_STATE
static int __Pyx__GetException(PyThreadState *tstate, PyObject **type, PyObject **value, PyObject **tb) {
#else
static int __Pyx_GetException(PyObject **type, PyObject **value, PyObject **tb) {
#endif
    PyObject *local_type, *local_value, *local_tb;
#if CYTHON_FAST_THREAD_STATE
    PyObject *tmp_type, *tmp_value, *tmp_tb;
    local_type = tstate->curexc_type;
    local_value = tstate->curexc_value;
    local_tb = tstate->curexc_traceback;
    tstate->curexc_type = 0;
    tstate->curexc_value = 0;
    tstate->curexc_traceback = 0;
#else
    PyErr_Fetch(&local_type, &local_value, &local_tb);
#endif
    PyErr_NormalizeException(&local_type, &local_value, &local_tb);
#if CYTHON_FAST_THREAD_STATE
    if (unlikely(tstate->curexc_type))
#else
    if (unlikely(PyErr_Occurred()))
#endif
        goto bad;
    #if PY_MAJOR_VERSION >= 3
    if (local_tb) {
        if (unlikely(PyException_SetTraceback(local_value, local_tb) < 0))
            goto bad;
    }
    #endif
    Py_XINCREF(local_tb);
    Py_XINCREF(local_type);
    Py_XINCREF(local_value);
    *type = local_type;
    *value = local_value;
    *tb = local_tb;
#if CYTHON_FAST_THREAD_STATE
    tmp_type = tstate->exc_type;
    tmp_value = tstate->exc_value;
    tmp_tb = tstate->exc_traceback;
    tstate->exc_type = local_type;
    tstate->exc_value = local_value;
    tstate->exc_traceback = local_tb;
    Py_XDECREF(tmp_type);
    Py_XDECREF(tmp_value);
    Py_XDECREF(tmp_tb);
#else
    PyErr_SetExcInfo(local_type, local_value, local_tb);
#endif
    return 0;
bad:
    *type = 0;
    *value = 0;
    *tb = 0;
    Py_XDECREF(local_type);
    Py_XDECREF(local_value);
    Py_XDECREF(local_tb);
    return -1;
}

/* PyErrFetchRestore */
        #if CYTHON_FAST_THREAD_STATE
static CYTHON_INLINE void __Pyx_ErrRestoreInState(PyThreadState *tstate, PyObject *type, PyObject *value, PyObject *tb) {
    PyObject *tmp_type, *tmp_value, *tmp_tb;
    tmp_type = tstate->curexc_type;
    tmp_value = tstate->curexc_value;
    tmp_tb = tstate->curexc_traceback;
    tstate->curexc_type = type;
    tstate->curexc_value = value;
    tstate->curexc_traceback = tb;
    Py_XDECREF(tmp_type);
    Py_XDECREF(tmp_value);
    Py_XDECREF(tmp_tb);
}
static CYTHON_INLINE void __Pyx_ErrFetchInState(PyThreadState *tstate, PyObject **type, PyObject **value, PyObject **tb) {
    *type = tstate->curexc_type;
    *value = tstate->curexc_value;
    *tb = tstate->curexc_traceback;
    tstate->curexc_type = 0;
    tstate->curexc_value = 0;
    tstate->curexc_traceback = 0;
}
#endif

/* None */
        static CYTHON_INLINE void __Pyx_RaiseUnboundLocalError(const char *varname) {
    PyErr_Format(PyExc_UnboundLocalError, "local variable '%s' referenced before assignment", varname);
}

/* SliceTupleAndList */
        #if CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE void __Pyx_crop_slice(Py_ssize_t* _start, Py_ssize_t* _stop, Py_ssize_t* _length) {
    Py_ssize_t start = *_start, stop = *_stop, length = *_length;
    if (start < 0) {
        start += length;
        if (start < 0)
            start = 0;
    }
    if (stop < 0)
        stop += length;
    else if (stop > length)
        stop = length;
    *_length = stop - start;
    *_start = start;
    *_stop = stop;
}
static CYTHON_INLINE void __Pyx_copy_object_array(PyObject** CYTHON_RESTRICT src, PyObject** CYTHON_RESTRICT dest, Py_ssize_t length) {
    PyObject *v;
    Py_ssize_t i;
    for (i = 0; i < length; i++) {
        v = dest[i] = src[i];
        Py_INCREF(v);
    }
}
static CYTHON_INLINE PyObject* __Pyx_PyList_GetSlice(
            PyObject* src, Py_ssize_t start, Py_ssize_t stop) {
    PyObject* dest;
    Py_ssize_t length = PyList_GET_SIZE(src);
    __Pyx_crop_slice(&start, &stop, &length);
    if (unlikely(length <= 0))
        return PyList_New(0);
    dest = PyList_New(length);
    if (unlikely(!dest))
        return NULL;
    __Pyx_copy_object_array(
        ((PyListObject*)src)->ob_item + start,
        ((PyListObject*)dest)->ob_item,
        length);
    return dest;
}
static CYTHON_INLINE PyObject* __Pyx_PyTuple_GetSlice(
            PyObject* src, Py_ssize_t start, Py_ssize_t stop) {
    PyObject* dest;
    Py_ssize_t length = PyTuple_GET_SIZE(src);
    __Pyx_crop_slice(&start, &stop, &length);
    if (unlikely(length <= 0))
        return PyTuple_New(0);
    dest = PyTuple_New(length);
    if (unlikely(!dest))
        return NULL;
    __Pyx_copy_object_array(
        ((PyTupleObject*)src)->ob_item + start,
        ((PyTupleObject*)dest)->ob_item,
        length);
    return dest;
}
#endif

/* StringJoin */
        #if !CYTHON_COMPILING_IN_CPYTHON
static CYTHON_INLINE PyObject* __Pyx_PyBytes_Join(PyObject* sep, PyObject* values) {
    return PyObject_CallMethodObjArgs(sep, __pyx_n_s_join, values, NULL);
}
#endif

/* Import */
        static PyObject *__Pyx_Import(PyObject *name, PyObject *from_list, int level) {
    PyObject *empty_list = 0;
    PyObject *module = 0;
    PyObject *global_dict = 0;
    PyObject *empty_dict = 0;
    PyObject *list;
    #if PY_VERSION_HEX < 0x03030000
    PyObject *py_import;
    py_import = __Pyx_PyObject_GetAttrStr(__pyx_b, __pyx_n_s_import);
    if (!py_import)
        goto bad;
    #endif
    if (from_list)
        list = from_list;
    else {
        empty_list = PyList_New(0);
        if (!empty_list)
            goto bad;
        list = empty_list;
    }
    global_dict = PyModule_GetDict(__pyx_m);
    if (!global_dict)
        goto bad;
    empty_dict = PyDict_New();
    if (!empty_dict)
        goto bad;
    {
        #if PY_MAJOR_VERSION >= 3
        if (level == -1) {
            if (strchr(__Pyx_MODULE_NAME, '.')) {
                #if PY_VERSION_HEX < 0x03030000
                PyObject *py_level = PyInt_FromLong(1);
                if (!py_level)
                    goto bad;
                module = PyObject_CallFunctionObjArgs(py_import,
                    name, global_dict, empty_dict, list, py_level, NULL);
                Py_DECREF(py_level);
                #else
                module = PyImport_ImportModuleLevelObject(
                    name, global_dict, empty_dict, list, 1);
                #endif
                if (!module) {
                    if (!PyErr_ExceptionMatches(PyExc_ImportError))
                        goto bad;
                    PyErr_Clear();
                }
            }
            level = 0;
        }
        #endif
        if (!module) {
            #if PY_VERSION_HEX < 0x03030000
            PyObject *py_level = PyInt_FromLong(level);
            if (!py_level)
                goto bad;
            module = PyObject_CallFunctionObjArgs(py_import,
                name, global_dict, empty_dict, list, py_level, NULL);
            Py_DECREF(py_level);
            #else
            module = PyImport_ImportModuleLevelObject(
                name, global_dict, empty_dict, list, level);
            #endif
        }
    }
bad:
    #if PY_VERSION_HEX < 0x03030000
    Py_XDECREF(py_import);
    #endif
    Py_XDECREF(empty_list);
    Py_XDECREF(empty_dict);
    return module;
}

/* ImportFrom */
        static PyObject* __Pyx_ImportFrom(PyObject* module, PyObject* name) {
    PyObject* value = __Pyx_PyObject_GetAttrStr(module, name);
    if (unlikely(!value) && PyErr_ExceptionMatches(PyExc_AttributeError)) {
        PyErr_Format(PyExc_ImportError,
        #if PY_MAJOR_VERSION < 3
            "cannot import name %.230s", PyString_AS_STRING(name));
        #else
            "cannot import name %S", name);
        #endif
    }
    return value;
}

/* CodeObjectCache */
        static int __pyx_bisect_code_objects(__Pyx_CodeObjectCacheEntry* entries, int count, int code_line) {
    int start = 0, mid = 0, end = count - 1;
    if (end >= 0 && code_line > entries[end].code_line) {
        return count;
    }
    while (start < end) {
        mid = start + (end - start) / 2;
        if (code_line < entries[mid].code_line) {
            end = mid;
        } else if (code_line > entries[mid].code_line) {
             start = mid + 1;
        } else {
            return mid;
        }
    }
    if (code_line <= entries[mid].code_line) {
        return mid;
    } else {
        return mid + 1;
    }
}
static PyCodeObject *__pyx_find_code_object(int code_line) {
    PyCodeObject* code_object;
    int pos;
    if (unlikely(!code_line) || unlikely(!__pyx_code_cache.entries)) {
        return NULL;
    }
    pos = __pyx_bisect_code_objects(__pyx_code_cache.entries, __pyx_code_cache.count, code_line);
    if (unlikely(pos >= __pyx_code_cache.count) || unlikely(__pyx_code_cache.entries[pos].code_line != code_line)) {
        return NULL;
    }
    code_object = __pyx_code_cache.entries[pos].code_object;
    Py_INCREF(code_object);
    return code_object;
}
static void __pyx_insert_code_object(int code_line, PyCodeObject* code_object) {
    int pos, i;
    __Pyx_CodeObjectCacheEntry* entries = __pyx_code_cache.entries;
    if (unlikely(!code_line)) {
        return;
    }
    if (unlikely(!entries)) {
        entries = (__Pyx_CodeObjectCacheEntry*)PyMem_Malloc(64*sizeof(__Pyx_CodeObjectCacheEntry));
        if (likely(entries)) {
            __pyx_code_cache.entries = entries;
            __pyx_code_cache.max_count = 64;
            __pyx_code_cache.count = 1;
            entries[0].code_line = code_line;
            entries[0].code_object = code_object;
            Py_INCREF(code_object);
        }
        return;
    }
    pos = __pyx_bisect_code_objects(__pyx_code_cache.entries, __pyx_code_cache.count, code_line);
    if ((pos < __pyx_code_cache.count) && unlikely(__pyx_code_cache.entries[pos].code_line == code_line)) {
        PyCodeObject* tmp = entries[pos].code_object;
        entries[pos].code_object = code_object;
        Py_DECREF(tmp);
        return;
    }
    if (__pyx_code_cache.count == __pyx_code_cache.max_count) {
        int new_max = __pyx_code_cache.max_count + 64;
        entries = (__Pyx_CodeObjectCacheEntry*)PyMem_Realloc(
            __pyx_code_cache.entries, (size_t)new_max*sizeof(__Pyx_CodeObjectCacheEntry));
        if (unlikely(!entries)) {
            return;
        }
        __pyx_code_cache.entries = entries;
        __pyx_code_cache.max_count = new_max;
    }
    for (i=__pyx_code_cache.count; i>pos; i--) {
        entries[i] = entries[i-1];
    }
    entries[pos].code_line = code_line;
    entries[pos].code_object = code_object;
    __pyx_code_cache.count++;
    Py_INCREF(code_object);
}

/* AddTraceback */
        #include "compile.h"
#include "frameobject.h"
#include "traceback.h"
static PyCodeObject* __Pyx_CreateCodeObjectForTraceback(
            const char *funcname, int c_line,
            int py_line, const char *filename) {
    PyCodeObject *py_code = 0;
    PyObject *py_srcfile = 0;
    PyObject *py_funcname = 0;
    #if PY_MAJOR_VERSION < 3
    py_srcfile = PyString_FromString(filename);
    #else
    py_srcfile = PyUnicode_FromString(filename);
    #endif
    if (!py_srcfile) goto bad;
    if (c_line) {
        #if PY_MAJOR_VERSION < 3
        py_funcname = PyString_FromFormat( "%s (%s:%d)", funcname, __pyx_cfilenm, c_line);
        #else
        py_funcname = PyUnicode_FromFormat( "%s (%s:%d)", funcname, __pyx_cfilenm, c_line);
        #endif
    }
    else {
        #if PY_MAJOR_VERSION < 3
        py_funcname = PyString_FromString(funcname);
        #else
        py_funcname = PyUnicode_FromString(funcname);
        #endif
    }
    if (!py_funcname) goto bad;
    py_code = __Pyx_PyCode_New(
        0,
        0,
        0,
        0,
        0,
        __pyx_empty_bytes, /*PyObject *code,*/
        __pyx_empty_tuple, /*PyObject *consts,*/
        __pyx_empty_tuple, /*PyObject *names,*/
        __pyx_empty_tuple, /*PyObject *varnames,*/
        __pyx_empty_tuple, /*PyObject *freevars,*/
        __pyx_empty_tuple, /*PyObject *cellvars,*/
        py_srcfile,   /*PyObject *filename,*/
        py_funcname,  /*PyObject *name,*/
        py_line,
        __pyx_empty_bytes  /*PyObject *lnotab*/
    );
    Py_DECREF(py_srcfile);
    Py_DECREF(py_funcname);
    return py_code;
bad:
    Py_XDECREF(py_srcfile);
    Py_XDECREF(py_funcname);
    return NULL;
}
static void __Pyx_AddTraceback(const char *funcname, int c_line,
                               int py_line, const char *filename) {
    PyCodeObject *py_code = 0;
    PyFrameObject *py_frame = 0;
    py_code = __pyx_find_code_object(c_line ? c_line : py_line);
    if (!py_code) {
        py_code = __Pyx_CreateCodeObjectForTraceback(
            funcname, c_line, py_line, filename);
        if (!py_code) goto bad;
        __pyx_insert_code_object(c_line ? c_line : py_line, py_code);
    }
    py_frame = PyFrame_New(
        PyThreadState_GET(), /*PyThreadState *tstate,*/
        py_code,             /*PyCodeObject *code,*/
        __pyx_d,      /*PyObject *globals,*/
        0                    /*PyObject *locals*/
    );
    if (!py_frame) goto bad;
    __Pyx_PyFrame_SetLineNumber(py_frame, py_line);
    PyTraceBack_Here(py_frame);
bad:
    Py_XDECREF(py_code);
    Py_XDECREF(py_frame);
}

/* CIntToPy */
        static CYTHON_INLINE PyObject* __Pyx_PyInt_From_long(long value) {
    const long neg_one = (long) -1, const_zero = (long) 0;
    const int is_unsigned = neg_one > const_zero;
    if (is_unsigned) {
        if (sizeof(long) < sizeof(long)) {
            return PyInt_FromLong((long) value);
        } else if (sizeof(long) <= sizeof(unsigned long)) {
            return PyLong_FromUnsignedLong((unsigned long) value);
#ifdef HAVE_LONG_LONG
        } else if (sizeof(long) <= sizeof(unsigned PY_LONG_LONG)) {
            return PyLong_FromUnsignedLongLong((unsigned PY_LONG_LONG) value);
#endif
        }
    } else {
        if (sizeof(long) <= sizeof(long)) {
            return PyInt_FromLong((long) value);
#ifdef HAVE_LONG_LONG
        } else if (sizeof(long) <= sizeof(PY_LONG_LONG)) {
            return PyLong_FromLongLong((PY_LONG_LONG) value);
#endif
        }
    }
    {
        int one = 1; int little = (int)*(unsigned char *)&one;
        unsigned char *bytes = (unsigned char *)&value;
        return _PyLong_FromByteArray(bytes, sizeof(long),
                                     little, !is_unsigned);
    }
}

/* Print */
        #if !CYTHON_COMPILING_IN_PYPY && PY_MAJOR_VERSION < 3
static PyObject *__Pyx_GetStdout(void) {
    PyObject *f = PySys_GetObject((char *)"stdout");
    if (!f) {
        PyErr_SetString(PyExc_RuntimeError, "lost sys.stdout");
    }
    return f;
}
static int __Pyx_Print(PyObject* f, PyObject *arg_tuple, int newline) {
    int i;
    if (!f) {
        if (!(f = __Pyx_GetStdout()))
            return -1;
    }
    Py_INCREF(f);
    for (i=0; i < PyTuple_GET_SIZE(arg_tuple); i++) {
        PyObject* v;
        if (PyFile_SoftSpace(f, 1)) {
            if (PyFile_WriteString(" ", f) < 0)
                goto error;
        }
        v = PyTuple_GET_ITEM(arg_tuple, i);
        if (PyFile_WriteObject(v, f, Py_PRINT_RAW) < 0)
            goto error;
        if (PyString_Check(v)) {
            char *s = PyString_AsString(v);
            Py_ssize_t len = PyString_Size(v);
            if (len > 0) {
                switch (s[len-1]) {
                    case ' ': break;
                    case '\f': case '\r': case '\n': case '\t': case '\v':
                        PyFile_SoftSpace(f, 0);
                        break;
                    default:  break;
                }
            }
        }
    }
    if (newline) {
        if (PyFile_WriteString("\n", f) < 0)
            goto error;
        PyFile_SoftSpace(f, 0);
    }
    Py_DECREF(f);
    return 0;
error:
    Py_DECREF(f);
    return -1;
}
#else
static int __Pyx_Print(PyObject* stream, PyObject *arg_tuple, int newline) {
    PyObject* kwargs = 0;
    PyObject* result = 0;
    PyObject* end_string;
    if (unlikely(!__pyx_print)) {
        __pyx_print = PyObject_GetAttr(__pyx_b, __pyx_n_s_print);
        if (!__pyx_print)
            return -1;
    }
    if (stream) {
        kwargs = PyDict_New();
        if (unlikely(!kwargs))
            return -1;
        if (unlikely(PyDict_SetItem(kwargs, __pyx_n_s_file, stream) < 0))
            goto bad;
        if (!newline) {
            end_string = PyUnicode_FromStringAndSize(" ", 1);
            if (unlikely(!end_string))
                goto bad;
            if (PyDict_SetItem(kwargs, __pyx_n_s_end, end_string) < 0) {
                Py_DECREF(end_string);
                goto bad;
            }
            Py_DECREF(end_string);
        }
    } else if (!newline) {
        if (unlikely(!__pyx_print_kwargs)) {
            __pyx_print_kwargs = PyDict_New();
            if (unlikely(!__pyx_print_kwargs))
                return -1;
            end_string = PyUnicode_FromStringAndSize(" ", 1);
            if (unlikely(!end_string))
                return -1;
            if (PyDict_SetItem(__pyx_print_kwargs, __pyx_n_s_end, end_string) < 0) {
                Py_DECREF(end_string);
                return -1;
            }
            Py_DECREF(end_string);
        }
        kwargs = __pyx_print_kwargs;
    }
    result = PyObject_Call(__pyx_print, arg_tuple, kwargs);
    if (unlikely(kwargs) && (kwargs != __pyx_print_kwargs))
        Py_DECREF(kwargs);
    if (!result)
        return -1;
    Py_DECREF(result);
    return 0;
bad:
    if (kwargs != __pyx_print_kwargs)
        Py_XDECREF(kwargs);
    return -1;
}
#endif

/* PrintOne */
        #if !CYTHON_COMPILING_IN_PYPY && PY_MAJOR_VERSION < 3
static int __Pyx_PrintOne(PyObject* f, PyObject *o) {
    if (!f) {
        if (!(f = __Pyx_GetStdout()))
            return -1;
    }
    Py_INCREF(f);
    if (PyFile_SoftSpace(f, 0)) {
        if (PyFile_WriteString(" ", f) < 0)
            goto error;
    }
    if (PyFile_WriteObject(o, f, Py_PRINT_RAW) < 0)
        goto error;
    if (PyFile_WriteString("\n", f) < 0)
        goto error;
    Py_DECREF(f);
    return 0;
error:
    Py_DECREF(f);
    return -1;
    /* the line below is just to avoid C compiler
     * warnings about unused functions */
    return __Pyx_Print(f, NULL, 0);
}
#else
static int __Pyx_PrintOne(PyObject* stream, PyObject *o) {
    int res;
    PyObject* arg_tuple = PyTuple_Pack(1, o);
    if (unlikely(!arg_tuple))
        return -1;
    res = __Pyx_Print(stream, arg_tuple, 1);
    Py_DECREF(arg_tuple);
    return res;
}
#endif

/* CIntFromPyVerify */
        #define __PYX_VERIFY_RETURN_INT(target_type, func_type, func_value)\
    __PYX__VERIFY_RETURN_INT(target_type, func_type, func_value, 0)
#define __PYX_VERIFY_RETURN_INT_EXC(target_type, func_type, func_value)\
    __PYX__VERIFY_RETURN_INT(target_type, func_type, func_value, 1)
#define __PYX__VERIFY_RETURN_INT(target_type, func_type, func_value, exc)\
    {\
        func_type value = func_value;\
        if (sizeof(target_type) < sizeof(func_type)) {\
            if (unlikely(value != (func_type) (target_type) value)) {\
                func_type zero = 0;\
                if (exc && unlikely(value == (func_type)-1 && PyErr_Occurred()))\
                    return (target_type) -1;\
                if (is_unsigned && unlikely(value < zero))\
                    goto raise_neg_overflow;\
                else\
                    goto raise_overflow;\
            }\
        }\
        return (target_type) value;\
    }

/* CIntFromPy */
        static CYTHON_INLINE long __Pyx_PyInt_As_long(PyObject *x) {
    const long neg_one = (long) -1, const_zero = (long) 0;
    const int is_unsigned = neg_one > const_zero;
#if PY_MAJOR_VERSION < 3
    if (likely(PyInt_Check(x))) {
        if (sizeof(long) < sizeof(long)) {
            __PYX_VERIFY_RETURN_INT(long, long, PyInt_AS_LONG(x))
        } else {
            long val = PyInt_AS_LONG(x);
            if (is_unsigned && unlikely(val < 0)) {
                goto raise_neg_overflow;
            }
            return (long) val;
        }
    } else
#endif
    if (likely(PyLong_Check(x))) {
        if (is_unsigned) {
#if CYTHON_USE_PYLONG_INTERNALS
            const digit* digits = ((PyLongObject*)x)->ob_digit;
            switch (Py_SIZE(x)) {
                case  0: return (long) 0;
                case  1: __PYX_VERIFY_RETURN_INT(long, digit, digits[0])
                case 2:
                    if (8 * sizeof(long) > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, unsigned long, (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) >= 2 * PyLong_SHIFT) {
                            return (long) (((((long)digits[1]) << PyLong_SHIFT) | (long)digits[0]));
                        }
                    }
                    break;
                case 3:
                    if (8 * sizeof(long) > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, unsigned long, (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) >= 3 * PyLong_SHIFT) {
                            return (long) (((((((long)digits[2]) << PyLong_SHIFT) | (long)digits[1]) << PyLong_SHIFT) | (long)digits[0]));
                        }
                    }
                    break;
                case 4:
                    if (8 * sizeof(long) > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, unsigned long, (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) >= 4 * PyLong_SHIFT) {
                            return (long) (((((((((long)digits[3]) << PyLong_SHIFT) | (long)digits[2]) << PyLong_SHIFT) | (long)digits[1]) << PyLong_SHIFT) | (long)digits[0]));
                        }
                    }
                    break;
            }
#endif
#if CYTHON_COMPILING_IN_CPYTHON
            if (unlikely(Py_SIZE(x) < 0)) {
                goto raise_neg_overflow;
            }
#else
            {
                int result = PyObject_RichCompareBool(x, Py_False, Py_LT);
                if (unlikely(result < 0))
                    return (long) -1;
                if (unlikely(result == 1))
                    goto raise_neg_overflow;
            }
#endif
            if (sizeof(long) <= sizeof(unsigned long)) {
                __PYX_VERIFY_RETURN_INT_EXC(long, unsigned long, PyLong_AsUnsignedLong(x))
#ifdef HAVE_LONG_LONG
            } else if (sizeof(long) <= sizeof(unsigned PY_LONG_LONG)) {
                __PYX_VERIFY_RETURN_INT_EXC(long, unsigned PY_LONG_LONG, PyLong_AsUnsignedLongLong(x))
#endif
            }
        } else {
#if CYTHON_USE_PYLONG_INTERNALS
            const digit* digits = ((PyLongObject*)x)->ob_digit;
            switch (Py_SIZE(x)) {
                case  0: return (long) 0;
                case -1: __PYX_VERIFY_RETURN_INT(long, sdigit, (sdigit) (-(sdigit)digits[0]))
                case  1: __PYX_VERIFY_RETURN_INT(long,  digit, +digits[0])
                case -2:
                    if (8 * sizeof(long) - 1 > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, long, -(long) (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
                            return (long) (((long)-1)*(((((long)digits[1]) << PyLong_SHIFT) | (long)digits[0])));
                        }
                    }
                    break;
                case 2:
                    if (8 * sizeof(long) > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, unsigned long, (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
                            return (long) ((((((long)digits[1]) << PyLong_SHIFT) | (long)digits[0])));
                        }
                    }
                    break;
                case -3:
                    if (8 * sizeof(long) - 1 > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, long, -(long) (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
                            return (long) (((long)-1)*(((((((long)digits[2]) << PyLong_SHIFT) | (long)digits[1]) << PyLong_SHIFT) | (long)digits[0])));
                        }
                    }
                    break;
                case 3:
                    if (8 * sizeof(long) > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, unsigned long, (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
                            return (long) ((((((((long)digits[2]) << PyLong_SHIFT) | (long)digits[1]) << PyLong_SHIFT) | (long)digits[0])));
                        }
                    }
                    break;
                case -4:
                    if (8 * sizeof(long) - 1 > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, long, -(long) (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) - 1 > 4 * PyLong_SHIFT) {
                            return (long) (((long)-1)*(((((((((long)digits[3]) << PyLong_SHIFT) | (long)digits[2]) << PyLong_SHIFT) | (long)digits[1]) << PyLong_SHIFT) | (long)digits[0])));
                        }
                    }
                    break;
                case 4:
                    if (8 * sizeof(long) > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(long, unsigned long, (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(long) - 1 > 4 * PyLong_SHIFT) {
                            return (long) ((((((((((long)digits[3]) << PyLong_SHIFT) | (long)digits[2]) << PyLong_SHIFT) | (long)digits[1]) << PyLong_SHIFT) | (long)digits[0])));
                        }
                    }
                    break;
            }
#endif
            if (sizeof(long) <= sizeof(long)) {
                __PYX_VERIFY_RETURN_INT_EXC(long, long, PyLong_AsLong(x))
#ifdef HAVE_LONG_LONG
            } else if (sizeof(long) <= sizeof(PY_LONG_LONG)) {
                __PYX_VERIFY_RETURN_INT_EXC(long, PY_LONG_LONG, PyLong_AsLongLong(x))
#endif
            }
        }
        {
#if CYTHON_COMPILING_IN_PYPY && !defined(_PyLong_AsByteArray)
            PyErr_SetString(PyExc_RuntimeError,
                            "_PyLong_AsByteArray() not available in PyPy, cannot convert large numbers");
#else
            long val;
            PyObject *v = __Pyx_PyNumber_IntOrLong(x);
 #if PY_MAJOR_VERSION < 3
            if (likely(v) && !PyLong_Check(v)) {
                PyObject *tmp = v;
                v = PyNumber_Long(tmp);
                Py_DECREF(tmp);
            }
 #endif
            if (likely(v)) {
                int one = 1; int is_little = (int)*(unsigned char *)&one;
                unsigned char *bytes = (unsigned char *)&val;
                int ret = _PyLong_AsByteArray((PyLongObject *)v,
                                              bytes, sizeof(val),
                                              is_little, !is_unsigned);
                Py_DECREF(v);
                if (likely(!ret))
                    return val;
            }
#endif
            return (long) -1;
        }
    } else {
        long val;
        PyObject *tmp = __Pyx_PyNumber_IntOrLong(x);
        if (!tmp) return (long) -1;
        val = __Pyx_PyInt_As_long(tmp);
        Py_DECREF(tmp);
        return val;
    }
raise_overflow:
    PyErr_SetString(PyExc_OverflowError,
        "value too large to convert to long");
    return (long) -1;
raise_neg_overflow:
    PyErr_SetString(PyExc_OverflowError,
        "can't convert negative value to long");
    return (long) -1;
}

/* CIntFromPy */
        static CYTHON_INLINE int __Pyx_PyInt_As_int(PyObject *x) {
    const int neg_one = (int) -1, const_zero = (int) 0;
    const int is_unsigned = neg_one > const_zero;
#if PY_MAJOR_VERSION < 3
    if (likely(PyInt_Check(x))) {
        if (sizeof(int) < sizeof(long)) {
            __PYX_VERIFY_RETURN_INT(int, long, PyInt_AS_LONG(x))
        } else {
            long val = PyInt_AS_LONG(x);
            if (is_unsigned && unlikely(val < 0)) {
                goto raise_neg_overflow;
            }
            return (int) val;
        }
    } else
#endif
    if (likely(PyLong_Check(x))) {
        if (is_unsigned) {
#if CYTHON_USE_PYLONG_INTERNALS
            const digit* digits = ((PyLongObject*)x)->ob_digit;
            switch (Py_SIZE(x)) {
                case  0: return (int) 0;
                case  1: __PYX_VERIFY_RETURN_INT(int, digit, digits[0])
                case 2:
                    if (8 * sizeof(int) > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, unsigned long, (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) >= 2 * PyLong_SHIFT) {
                            return (int) (((((int)digits[1]) << PyLong_SHIFT) | (int)digits[0]));
                        }
                    }
                    break;
                case 3:
                    if (8 * sizeof(int) > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, unsigned long, (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) >= 3 * PyLong_SHIFT) {
                            return (int) (((((((int)digits[2]) << PyLong_SHIFT) | (int)digits[1]) << PyLong_SHIFT) | (int)digits[0]));
                        }
                    }
                    break;
                case 4:
                    if (8 * sizeof(int) > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, unsigned long, (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) >= 4 * PyLong_SHIFT) {
                            return (int) (((((((((int)digits[3]) << PyLong_SHIFT) | (int)digits[2]) << PyLong_SHIFT) | (int)digits[1]) << PyLong_SHIFT) | (int)digits[0]));
                        }
                    }
                    break;
            }
#endif
#if CYTHON_COMPILING_IN_CPYTHON
            if (unlikely(Py_SIZE(x) < 0)) {
                goto raise_neg_overflow;
            }
#else
            {
                int result = PyObject_RichCompareBool(x, Py_False, Py_LT);
                if (unlikely(result < 0))
                    return (int) -1;
                if (unlikely(result == 1))
                    goto raise_neg_overflow;
            }
#endif
            if (sizeof(int) <= sizeof(unsigned long)) {
                __PYX_VERIFY_RETURN_INT_EXC(int, unsigned long, PyLong_AsUnsignedLong(x))
#ifdef HAVE_LONG_LONG
            } else if (sizeof(int) <= sizeof(unsigned PY_LONG_LONG)) {
                __PYX_VERIFY_RETURN_INT_EXC(int, unsigned PY_LONG_LONG, PyLong_AsUnsignedLongLong(x))
#endif
            }
        } else {
#if CYTHON_USE_PYLONG_INTERNALS
            const digit* digits = ((PyLongObject*)x)->ob_digit;
            switch (Py_SIZE(x)) {
                case  0: return (int) 0;
                case -1: __PYX_VERIFY_RETURN_INT(int, sdigit, (sdigit) (-(sdigit)digits[0]))
                case  1: __PYX_VERIFY_RETURN_INT(int,  digit, +digits[0])
                case -2:
                    if (8 * sizeof(int) - 1 > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, long, -(long) (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) - 1 > 2 * PyLong_SHIFT) {
                            return (int) (((int)-1)*(((((int)digits[1]) << PyLong_SHIFT) | (int)digits[0])));
                        }
                    }
                    break;
                case 2:
                    if (8 * sizeof(int) > 1 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 2 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, unsigned long, (((((unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) - 1 > 2 * PyLong_SHIFT) {
                            return (int) ((((((int)digits[1]) << PyLong_SHIFT) | (int)digits[0])));
                        }
                    }
                    break;
                case -3:
                    if (8 * sizeof(int) - 1 > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, long, -(long) (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) - 1 > 3 * PyLong_SHIFT) {
                            return (int) (((int)-1)*(((((((int)digits[2]) << PyLong_SHIFT) | (int)digits[1]) << PyLong_SHIFT) | (int)digits[0])));
                        }
                    }
                    break;
                case 3:
                    if (8 * sizeof(int) > 2 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 3 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, unsigned long, (((((((unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) - 1 > 3 * PyLong_SHIFT) {
                            return (int) ((((((((int)digits[2]) << PyLong_SHIFT) | (int)digits[1]) << PyLong_SHIFT) | (int)digits[0])));
                        }
                    }
                    break;
                case -4:
                    if (8 * sizeof(int) - 1 > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, long, -(long) (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) - 1 > 4 * PyLong_SHIFT) {
                            return (int) (((int)-1)*(((((((((int)digits[3]) << PyLong_SHIFT) | (int)digits[2]) << PyLong_SHIFT) | (int)digits[1]) << PyLong_SHIFT) | (int)digits[0])));
                        }
                    }
                    break;
                case 4:
                    if (8 * sizeof(int) > 3 * PyLong_SHIFT) {
                        if (8 * sizeof(unsigned long) > 4 * PyLong_SHIFT) {
                            __PYX_VERIFY_RETURN_INT(int, unsigned long, (((((((((unsigned long)digits[3]) << PyLong_SHIFT) | (unsigned long)digits[2]) << PyLong_SHIFT) | (unsigned long)digits[1]) << PyLong_SHIFT) | (unsigned long)digits[0])))
                        } else if (8 * sizeof(int) - 1 > 4 * PyLong_SHIFT) {
                            return (int) ((((((((((int)digits[3]) << PyLong_SHIFT) | (int)digits[2]) << PyLong_SHIFT) | (int)digits[1]) << PyLong_SHIFT) | (int)digits[0])));
                        }
                    }
                    break;
            }
#endif
            if (sizeof(int) <= sizeof(long)) {
                __PYX_VERIFY_RETURN_INT_EXC(int, long, PyLong_AsLong(x))
#ifdef HAVE_LONG_LONG
            } else if (sizeof(int) <= sizeof(PY_LONG_LONG)) {
                __PYX_VERIFY_RETURN_INT_EXC(int, PY_LONG_LONG, PyLong_AsLongLong(x))
#endif
            }
        }
        {
#if CYTHON_COMPILING_IN_PYPY && !defined(_PyLong_AsByteArray)
            PyErr_SetString(PyExc_RuntimeError,
                            "_PyLong_AsByteArray() not available in PyPy, cannot convert large numbers");
#else
            int val;
            PyObject *v = __Pyx_PyNumber_IntOrLong(x);
 #if PY_MAJOR_VERSION < 3
            if (likely(v) && !PyLong_Check(v)) {
                PyObject *tmp = v;
                v = PyNumber_Long(tmp);
                Py_DECREF(tmp);
            }
 #endif
            if (likely(v)) {
                int one = 1; int is_little = (int)*(unsigned char *)&one;
                unsigned char *bytes = (unsigned char *)&val;
                int ret = _PyLong_AsByteArray((PyLongObject *)v,
                                              bytes, sizeof(val),
                                              is_little, !is_unsigned);
                Py_DECREF(v);
                if (likely(!ret))
                    return val;
            }
#endif
            return (int) -1;
        }
    } else {
        int val;
        PyObject *tmp = __Pyx_PyNumber_IntOrLong(x);
        if (!tmp) return (int) -1;
        val = __Pyx_PyInt_As_int(tmp);
        Py_DECREF(tmp);
        return val;
    }
raise_overflow:
    PyErr_SetString(PyExc_OverflowError,
        "value too large to convert to int");
    return (int) -1;
raise_neg_overflow:
    PyErr_SetString(PyExc_OverflowError,
        "can't convert negative value to int");
    return (int) -1;
}

/* CheckBinaryVersion */
        static int __Pyx_check_binary_version(void) {
    char ctversion[4], rtversion[4];
    PyOS_snprintf(ctversion, 4, "%d.%d", PY_MAJOR_VERSION, PY_MINOR_VERSION);
    PyOS_snprintf(rtversion, 4, "%s", Py_GetVersion());
    if (ctversion[0] != rtversion[0] || ctversion[2] != rtversion[2]) {
        char message[200];
        PyOS_snprintf(message, sizeof(message),
                      "compiletime version %s of module '%.100s' "
                      "does not match runtime version %s",
                      ctversion, __Pyx_MODULE_NAME, rtversion);
        return PyErr_WarnEx(NULL, message, 1);
    }
    return 0;
}

/* InitStrings */
        static int __Pyx_InitStrings(__Pyx_StringTabEntry *t) {
    while (t->p) {
        #if PY_MAJOR_VERSION < 3
        if (t->is_unicode) {
            *t->p = PyUnicode_DecodeUTF8(t->s, t->n - 1, NULL);
        } else if (t->intern) {
            *t->p = PyString_InternFromString(t->s);
        } else {
            *t->p = PyString_FromStringAndSize(t->s, t->n - 1);
        }
        #else
        if (t->is_unicode | t->is_str) {
            if (t->intern) {
                *t->p = PyUnicode_InternFromString(t->s);
            } else if (t->encoding) {
                *t->p = PyUnicode_Decode(t->s, t->n - 1, t->encoding, NULL);
            } else {
                *t->p = PyUnicode_FromStringAndSize(t->s, t->n - 1);
            }
        } else {
            *t->p = PyBytes_FromStringAndSize(t->s, t->n - 1);
        }
        #endif
        if (!*t->p)
            return -1;
        ++t;
    }
    return 0;
}

static CYTHON_INLINE PyObject* __Pyx_PyUnicode_FromString(const char* c_str) {
    return __Pyx_PyUnicode_FromStringAndSize(c_str, (Py_ssize_t)strlen(c_str));
}
static CYTHON_INLINE char* __Pyx_PyObject_AsString(PyObject* o) {
    Py_ssize_t ignore;
    return __Pyx_PyObject_AsStringAndSize(o, &ignore);
}
static CYTHON_INLINE char* __Pyx_PyObject_AsStringAndSize(PyObject* o, Py_ssize_t *length) {
#if CYTHON_COMPILING_IN_CPYTHON && (__PYX_DEFAULT_STRING_ENCODING_IS_ASCII || __PYX_DEFAULT_STRING_ENCODING_IS_DEFAULT)
    if (
#if PY_MAJOR_VERSION < 3 && __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
            __Pyx_sys_getdefaultencoding_not_ascii &&
#endif
            PyUnicode_Check(o)) {
#if PY_VERSION_HEX < 0x03030000
        char* defenc_c;
        PyObject* defenc = _PyUnicode_AsDefaultEncodedString(o, NULL);
        if (!defenc) return NULL;
        defenc_c = PyBytes_AS_STRING(defenc);
#if __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
        {
            char* end = defenc_c + PyBytes_GET_SIZE(defenc);
            char* c;
            for (c = defenc_c; c < end; c++) {
                if ((unsigned char) (*c) >= 128) {
                    PyUnicode_AsASCIIString(o);
                    return NULL;
                }
            }
        }
#endif
        *length = PyBytes_GET_SIZE(defenc);
        return defenc_c;
#else
        if (__Pyx_PyUnicode_READY(o) == -1) return NULL;
#if __PYX_DEFAULT_STRING_ENCODING_IS_ASCII
        if (PyUnicode_IS_ASCII(o)) {
            *length = PyUnicode_GET_LENGTH(o);
            return PyUnicode_AsUTF8(o);
        } else {
            PyUnicode_AsASCIIString(o);
            return NULL;
        }
#else
        return PyUnicode_AsUTF8AndSize(o, length);
#endif
#endif
    } else
#endif
#if (!CYTHON_COMPILING_IN_PYPY) || (defined(PyByteArray_AS_STRING) && defined(PyByteArray_GET_SIZE))
    if (PyByteArray_Check(o)) {
        *length = PyByteArray_GET_SIZE(o);
        return PyByteArray_AS_STRING(o);
    } else
#endif
    {
        char* result;
        int r = PyBytes_AsStringAndSize(o, &result, length);
        if (unlikely(r < 0)) {
            return NULL;
        } else {
            return result;
        }
    }
}
static CYTHON_INLINE int __Pyx_PyObject_IsTrue(PyObject* x) {
   int is_true = x == Py_True;
   if (is_true | (x == Py_False) | (x == Py_None)) return is_true;
   else return PyObject_IsTrue(x);
}
static CYTHON_INLINE PyObject* __Pyx_PyNumber_IntOrLong(PyObject* x) {
#if CYTHON_USE_TYPE_SLOTS
  PyNumberMethods *m;
#endif
  const char *name = NULL;
  PyObject *res = NULL;
#if PY_MAJOR_VERSION < 3
  if (PyInt_Check(x) || PyLong_Check(x))
#else
  if (PyLong_Check(x))
#endif
    return __Pyx_NewRef(x);
#if CYTHON_USE_TYPE_SLOTS
  m = Py_TYPE(x)->tp_as_number;
  #if PY_MAJOR_VERSION < 3
  if (m && m->nb_int) {
    name = "int";
    res = PyNumber_Int(x);
  }
  else if (m && m->nb_long) {
    name = "long";
    res = PyNumber_Long(x);
  }
  #else
  if (m && m->nb_int) {
    name = "int";
    res = PyNumber_Long(x);
  }
  #endif
#else
  res = PyNumber_Int(x);
#endif
  if (res) {
#if PY_MAJOR_VERSION < 3
    if (!PyInt_Check(res) && !PyLong_Check(res)) {
#else
    if (!PyLong_Check(res)) {
#endif
      PyErr_Format(PyExc_TypeError,
                   "__%.4s__ returned non-%.4s (type %.200s)",
                   name, name, Py_TYPE(res)->tp_name);
      Py_DECREF(res);
      return NULL;
    }
  }
  else if (!PyErr_Occurred()) {
    PyErr_SetString(PyExc_TypeError,
                    "an integer is required");
  }
  return res;
}
static CYTHON_INLINE Py_ssize_t __Pyx_PyIndex_AsSsize_t(PyObject* b) {
  Py_ssize_t ival;
  PyObject *x;
#if PY_MAJOR_VERSION < 3
  if (likely(PyInt_CheckExact(b))) {
    if (sizeof(Py_ssize_t) >= sizeof(long))
        return PyInt_AS_LONG(b);
    else
        return PyInt_AsSsize_t(x);
  }
#endif
  if (likely(PyLong_CheckExact(b))) {
    #if CYTHON_USE_PYLONG_INTERNALS
    const digit* digits = ((PyLongObject*)b)->ob_digit;
    const Py_ssize_t size = Py_SIZE(b);
    if (likely(__Pyx_sst_abs(size) <= 1)) {
        ival = likely(size) ? digits[0] : 0;
        if (size == -1) ival = -ival;
        return ival;
    } else {
      switch (size) {
         case 2:
           if (8 * sizeof(Py_ssize_t) > 2 * PyLong_SHIFT) {
             return (Py_ssize_t) (((((size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0]));
           }
           break;
         case -2:
           if (8 * sizeof(Py_ssize_t) > 2 * PyLong_SHIFT) {
             return -(Py_ssize_t) (((((size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0]));
           }
           break;
         case 3:
           if (8 * sizeof(Py_ssize_t) > 3 * PyLong_SHIFT) {
             return (Py_ssize_t) (((((((size_t)digits[2]) << PyLong_SHIFT) | (size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0]));
           }
           break;
         case -3:
           if (8 * sizeof(Py_ssize_t) > 3 * PyLong_SHIFT) {
             return -(Py_ssize_t) (((((((size_t)digits[2]) << PyLong_SHIFT) | (size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0]));
           }
           break;
         case 4:
           if (8 * sizeof(Py_ssize_t) > 4 * PyLong_SHIFT) {
             return (Py_ssize_t) (((((((((size_t)digits[3]) << PyLong_SHIFT) | (size_t)digits[2]) << PyLong_SHIFT) | (size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0]));
           }
           break;
         case -4:
           if (8 * sizeof(Py_ssize_t) > 4 * PyLong_SHIFT) {
             return -(Py_ssize_t) (((((((((size_t)digits[3]) << PyLong_SHIFT) | (size_t)digits[2]) << PyLong_SHIFT) | (size_t)digits[1]) << PyLong_SHIFT) | (size_t)digits[0]));
           }
           break;
      }
    }
    #endif
    return PyLong_AsSsize_t(b);
  }
  x = PyNumber_Index(b);
  if (!x) return -1;
  ival = PyInt_AsSsize_t(x);
  Py_DECREF(x);
  return ival;
}
static CYTHON_INLINE PyObject * __Pyx_PyInt_FromSize_t(size_t ival) {
    return PyInt_FromSize_t(ival);
}


#endif /* Py_PYTHON_H */
