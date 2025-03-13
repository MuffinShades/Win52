#pragma once
#include <iostream>
#include <cstring>
#include <vector>
#include "types.hpp"

template<class _Ty> inline static void ZeroMem(_Ty* dat, size_t sz) {
    if (dat == nullptr) return;
    memset(dat, 0, sizeof(_Ty) * sz);
}

inline static void ZeroMem(void* dat, size_t sz) {
    if (dat == nullptr) return;
    memset(dat, 0, sz);
}

inline static size_t GetNumSz(const unsigned long long num) {
    unsigned long long compare = 1;
    size_t nBytes = 0;
    const size_t mxSz = sizeof(unsigned long long);

    while (num >= compare) {
        nBytes++;
        compare <<= 8;
    }

    return nBytes;
}

inline static float lerp(float a, float b, float t) {
    return a + t * (b - a);
}

struct Point {
    float x, y;
};

#define GMask(l) ((1 << (l)) - 1)
#define MAKE_MASK GMask

static inline std::vector<std::string> SplitString(std::string str, const char delim) {
    std::vector<std::string> res;
    const size_t len = str.length();
    std::string collector = "";
    const char* cStr = str.c_str();

    for (size_t i = 0; i < len; i++) {
        if (cStr[i] == delim) {
            res.push_back(collector);
            collector = "";
        }
        else
            collector += cStr[i];
    }

    res.push_back(collector);

    return res;
}

#define MAKE_LONG_BE(b0, b1, b2, b3, b4, b5, b6, b7) \
    ((b0) << 56) | \
    ((b1) << 48) | \
    ((b2) << 40) | \
    ((b3) << 32) | \
    ((b4) << 24) | \
    ((b5) << 16) | \
    ((b6) <<  8) | \
    ((b7) <<  0)

#define MAKE_LONG_LE(b0, b1, b2, b3, b4, b5, b6, b7) \
    ((b7) << 56) | \
    ((b6) << 48) | \
    ((b5) << 40) | \
    ((b4) << 32) | \
    ((b3) << 24) | \
    ((b2) << 16) | \
    ((b1) <<  8) | \
    ((b0) <<  0)

#define MAKE_INT_BE(b0, b1, b2, b3) \
    ((b0) << 24) | \
    ((b1) << 16) | \
    ((b2) <<  8) | \
    ((b3) <<  0)

#define MAKE_INT_LE(b0, b1, b2, b3) \
    ((b3) << 24) | \
    ((b2) << 16) | \
    ((b1) <<  8) | \
    ((b0) <<  0)

#define MAKE_SHORT_BE(b0, b1) \
    ((b0) <<  8) | \
    ((b1) <<  0)

#define MAKE_SHORT_LE(b0, b1) \
    ((b1) <<  8) | \
    ((b0) <<  0)

static inline u64 modifyByte(u64 val, i32 b, byte v) {
    u64 mask = ((1 << (sizeof(u64) << 3)) - 1);
    b <<= 3;
    mask ^= 0xff << b;
    val &= mask;
    return val | (v << b);
}

static bool _strCompare(std::string s1, std::string s2, bool lcmp = true, size_t slen = 0) {
    //length comparision
    if (lcmp)
        if (s1.length() != s2.length())
            return false;

    //compare chars
    const char* sc1 = s1.c_str(), * sc2 = s2.c_str();
    size_t sl = slen > 0 ? slen : s1.length();

    while (sl--)
        if (*sc1++ != *sc2++)
            return false;

    return true;
}

template<typename _Ty> static inline void _safe_free_a(_Ty* m) {
    if (!m) return;
    else {
        try {
            delete[] m;
            m = nullptr;
        }
        catch (std::exception e) {
            //oof
            m = nullptr;
            return;
        }
    }
}

template<typename _Ty> static inline void _safe_free_b(_Ty* m) {
    if (!m) return;
    else {
        try {
            delete m;
            m = nullptr;
        }
        catch (std::exception e) {
            //oof
            m = nullptr;
            return;
        }
    }
}

template<typename _Ty> static _Ty ArrMax(_Ty* arr, size_t len) {
    _Ty max = 0;

    for (size_t i = 0; i < len; i++)
        if (arr[i] > max) max = arr[i];

    return max;
}

template<typename _Ty> static void memfill(void* ptr, _Ty val, size_t nCopy) {
    if (nCopy < 0 || !ptr)
        return;

    _Ty* t_ptr = (_Ty*)ptr;

    for (size_t i = 0; i < nCopy; i++)
        *t_ptr++ = val;
}

static u64 NumReverse(u64 v, size_t bSz) {
    u64 r = 0;

    for (i32 i = 0; i < bSz; i++, r <<= 8, v >>= 8)
        r |= (v & 0xff);

    return r >> 8;
}

#ifndef max
#define max(a, b) ((a) > (b)) ? (a) : (b)
#endif

#ifndef min
#define min(a, b) ((a) < (b)) ? (a) : (b)
#endif

#ifndef clamp
#define clamp(a, max, min) ((a) > (max) ? (max) : ((a) < (min) : (min) : (a)));
#endif

/**
 *
 * Void buffer macros to make void buffers
 * less annoying
 *
 * VOID_BUF_ADD -> adds a value to the buffer
 * VOID_BUF_GET -> gets current value in a buffer
 * VOID_BUF_INC -> goes to next element in buffer
 * VOID_BUF_SET -> set current value in a void buffer
 * VOID_BUF_SI -> basically a void buf set followed by a void buf inc
 *
 */
#define VOID_BUF_ADD(buf, val) (buf) = (char*)(buf) + 1; \
                                *((char*)(buf)) = (val)
#define VOID_BUF_GET(buf) (*((char*)(buf)))
#define VOID_BUF_INC(buf) (buf) = (char*)(buf) + 1
#define VOID_BUF_SET(buf, val) *((char*)(buf)) = (val)
#define VOID_BUF_SI(buf, val) *((char*)(buf)) = (val); \
                               (buf) = (char*)(buf) + 1


#define foreach_ptr(type, cur, ptr, sz) \
    for (\
        type *cur=(ptr),*__end=((ptr)+(sz)); \
        cur<__end;cur++\
    )

 //same as foreach_ptr but m is for manual as in cur ins't incremented each iteration, it's manual
#define foreach_ptr_m(type, cur, ptr, sz) \
    for (\
        type *cur=(ptr),*__end=((ptr)+(sz)); \
        cur<__end;\
    )

#define forrange(n) \
    for (i64 i = 0; i < (n); i++)

/*#ifndef clamp
#define clamp(v, n, x) max((n), min((v), (x)))
#endif*/

#ifndef inRange
#define inRange(v, n, x) ((v) > (n)) && ((v) < (x))
#endif

template<class _Ty> static bool _bufCmp(_Ty* buf1, _Ty* buf2, size_t bSz) {
    if (!buf1 || !buf2) return false;

    for (size_t i = 0; i < bSz; i++)
        if (*buf1++ != *buf2++)
            return false;

    return true;
}

//fast version of modulo for certain bases
#define fast_modBase2(val, shift) ((val) & ((1 << (shift)) - 1))
#define fast_mod2(val) (val) & 1
#define fast_mod4(val) (val) & 3
#define fast_mod8(val) (val) & 7
#define fast_mod16(val) (val) & 15
#define fast_mod32(val) (val) & 31
#define fast_mod64(val) (val) & 63
#define fast_mod128(val) (val) & 127
#define fast_mod256(val) (val) & 255
#define fast_mod512(val) (val) & 511

static size_t computeMaxMod(u64 val) {
    u64 p = 1, n = 0;

    while (!(val & p)) {
        p <<= 1;
        n++;
    }

    return n;
}

//faster log functions that are also aligned for certain bases
#define __log_def(align) {  \
    i32 c = 0;              \
                            \
    while (val >>= align)   \
        c++;                \
                            \
    return c;               \
}

static i32 fast_log2(i32 val) __log_def(1)
static i32 fast_log4(i32 val) __log_def(2)
static i32 fast_log8(i32 val) __log_def(3)
static i32 fast_log16(i32 val) __log_def(4)
static i32 fast_log32(i32 val) __log_def(5)
static i32 fast_log64(i32 val) __log_def(6)


static u64 endian_swap(u64 val, size_t nBytes) {
    switch (nBytes) {
    case 2:
        return ((val & 0xff00) >> 8) | ((val & 0xff) << 8);
    case 3:
        return ((val & 0xff0000) >> 16) | ((val & 0xff) << 16);
    case 4:
        return ((val & 0x000000ff) << 24) |
            ((val & 0x0000ff00) << 8) |
            ((val & 0x00ff0000) >> 8) |
            ((val & 0xff000000) >> 24);
    case 5:
        return ((val & 0x00000000ffULL) << 32) |
            ((val & 0x000000ff00ULL) << 16) |
            ((val & 0x00ff000000ULL) >> 16) |
            ((val & 0xff00000000ULL) >> 32);
    case 6:
        return ((val & 0x0000000000ffULL) << 40) |
            ((val & 0x00000000ff00ULL) << 24) |
            ((val & 0x000000ff0000ULL) << 8) |
            ((val & 0x0000ff000000ULL) >> 8) |
            ((val & 0x00ff00000000ULL) >> 24) |
            ((val & 0xff0000000000ULL) >> 40);
    case 7:
        return ((val & 0x000000000000ffULL) << 48) |
            ((val & 0x0000000000ff00ULL) << 32) |
            ((val & 0x00000000ff0000ULL) << 16) |
            ((val & 0x0000ff00000000ULL) >> 16) |
            ((val & 0x00ff0000000000ULL) >> 32) |
            ((val & 0xff000000000000ULL) >> 48);
    case 8:
        return
            ((val & 0x00000000000000ffULL) << 56) | ((val & 0xff00000000000000ULL) >> 56) |
            ((val & 0x000000000000ff00ULL) << 40) | ((val & 0x00ff000000000000ULL) >> 40) |
            ((val & 0x0000000000ff0000ULL) << 24) | ((val & 0x0000ff0000000000ULL) >> 24) |
            ((val & 0x00000000ff000000ULL) << 8) | ((val & 0x000000ff00000000ULL) >> 8);
    default:
        return val;
    }
}

enum IntFormat {
    IntFormat_BigEndian = 0,
    IntFormat_LittleEndian = 1
};

constexpr static IntFormat __getOSEndian() {
    /*union _endian_test {
        u64 a = 1;
        byte b;
    };*/
    const int v = 1;
    //return (_endian_test()).b ? ByteStream_LittleEndian : ByteStream_BigEndian;
    return ((*((char*)&v)) == 1) ? IntFormat_LittleEndian : IntFormat_BigEndian;
}

