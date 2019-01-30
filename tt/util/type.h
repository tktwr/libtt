#ifndef tt_type_h
#define tt_type_h

#include <iostream>
#include <array>
#include <limits>

typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;
typedef unsigned long  ulong;


namespace tt {

    typedef std::array<int,    1> Vec1i;
    typedef std::array<float,  1> Vec1f;

    typedef std::array<int,    2> Vec2i;
    typedef std::array<float,  2> Vec2f;

    typedef std::array<int,    3> Vec3i;
    typedef std::array<float,  3> Vec3f;

    typedef std::array<int,    4> Vec4i;
    typedef std::array<float,  4> Vec4f;

    typedef std::array<uchar,  1> Color1uc;
    typedef std::array<ushort, 1> Color1us;
    typedef std::array<float,  1> Color1f;

    typedef std::array<uchar,  2> Color2uc;
    typedef std::array<ushort, 2> Color2us;
    typedef std::array<float,  2> Color2f;

    typedef std::array<uchar,  3> Color3uc;
    typedef std::array<ushort, 3> Color3us;
    typedef std::array<float,  3> Color3f;

    typedef std::array<uchar,  4> Color4uc;
    typedef std::array<ushort, 4> Color4us;
    typedef std::array<float,  4> Color4f;

    //==================================================
    // clamp
    //==================================================
    template<typename T>
    inline T clamp(T v, T l, T h) {
        return (v < l) ? l : (v > h) ? h : v;
    }

    //==================================================
    // convert type
    //==================================================
    inline uchar uint2uchar(uint v) {
        return clamp<uint>(v, std::numeric_limits<uchar>::min(), std::numeric_limits<uchar>::max());
    }
    inline ushort uint2ushort(uint v) {
        return clamp<uint>(v, std::numeric_limits<ushort>::min(), std::numeric_limits<ushort>::max());
    }
    inline uchar float2uchar(float f) {
        return (uchar)(std::numeric_limits<uchar>::max() * clamp(f, 0.f, 1.f));
    }
    inline ushort float2ushort(float f) {
        return (ushort)(std::numeric_limits<ushort>::max() * clamp(f, 0.f, 1.f));
    }

    template<std::size_t N>
    inline std::array<uchar, N> float2uchar(const std::array<float, N>& ar) {
        std::array<uchar, N> a0;
        for (int i=0; i<N; i++) {
            a0[i] = float2uchar(ar[i]);
        }
        return a0;
    }
    template<std::size_t N>
    inline std::array<ushort, N> float2ushort(const std::array<float, N>& ar) {
        std::array<ushort, N> a0;
        for (int i=0; i<N; i++) {
            a0[i] = float2ushort(ar[i]);
        }
        return a0;
    }
    inline Color4uc toColor4uc(const Color4f& c) {
        return float2uchar(c);
    }

    //==================================================
    // IO
    //==================================================
    template<typename T>
    inline std::istream& read(std::istream& is, T& v) { return is >> v; }
    inline std::istream& read(std::istream& is, uchar& v) {
        uint i = 0;
        is >> i;
        v = uint2uchar(i);
        return is;
    }

    template<typename T>
    inline std::ostream& write(std::ostream& os, const T& v) { return os << v; }
    inline std::ostream& write(std::ostream& os, const uchar& v) { return os << int(v); }

    //==================================================
    // add
    //==================================================
    template<typename T>
    inline T      add(const T& v1, const T& v2) { return v1 + v2; }
    inline uchar  add(const uchar& v1, const uchar& v2) { return uint2uchar(v1 + v2); }
    inline ushort add(const ushort& v1, const ushort& v2) { return uint2ushort(v1 + v2); }

    //==================================================
    // sub
    //==================================================
    template<typename T>
    inline T      sub(const T& v1, const T& v2) { return v1 - v2; }
    inline uchar  sub(const uchar& v1, const uchar& v2) { return uint2uchar(v1 - v2); }
    inline ushort sub(const ushort& v1, const ushort& v2) { return uint2ushort(v1 - v2); }

    //==================================================
    // mul
    //==================================================
    template<typename T>
    inline T      mul(const T& v1, const T& v2) { return v1 * v2; }
    inline uchar  mul(const uchar& v1, const uchar& v2) { return uint2uchar(v1 * v2); }
    inline ushort mul(const ushort& v1, const ushort& v2) { return uint2ushort(v1 * v2); }

    //==================================================
    // div
    //==================================================
    template<typename T>
    inline T      div(const T& v1, const T& v2) { return v1 / v2; }
    inline uchar  div(const uchar& v1, const uchar& v2) { return uint2uchar(v1 / v2); }
    inline ushort div(const ushort& v1, const ushort& v2) { return uint2ushort(v1 / v2); }

    //==================================================
    // len
    //==================================================
    template<typename T>
    inline T      len(const T& v1, const T& v2) { return (v1 > v2) ? v1 - v2 : v2 - v1; }

}


template<typename T, std::size_t N>
inline std::istream& operator>>(std::istream& is, std::array<T, N>& ar) {
    for (int i=0; i<N; i++) {
        tt::read(is, ar[i]);
    }
    return is;
}

template<typename T, std::size_t N>
inline std::ostream& operator<<(std::ostream& os, const std::array<T, N>& ar) {
    for (int i=0; i<N; i++) {
        tt::write(os, ar[i]);
        os << " ";
    }
    return os;
}

template<typename T, std::size_t N>
inline std::array<T, N> operator+(const std::array<T, N>& a1, const std::array<T, N>& a2) {
    std::array<T, N> a0;
    for (int i=0; i<N; i++) {
        a0[i] = tt::add(a1[i], a2[i]);
    }
    return a0;
}

template<typename T, std::size_t N>
inline std::array<T, N> operator-(const std::array<T, N>& a1, const std::array<T, N>& a2) {
    std::array<T, N> a0;
    for (int i=0; i<N; i++) {
        a0[i] = tt::sub(a1[i], a2[i]);
    }
    return a0;
}

template<typename T, std::size_t N>
inline std::array<T, N> operator*(const std::array<T, N>& a1, const std::array<T, N>& a2) {
    std::array<T, N> a0;
    for (int i=0; i<N; i++) {
        a0[i] = tt::mul(a1[i], a2[i]);
    }
    return a0;
}

template<typename T, std::size_t N>
inline std::array<T, N> operator*(const std::array<T, N>& a1, float s) {
    std::array<T, N> a0;
    for (int i=0; i<N; i++) {
        a0[i] = tt::mul<float>(a1[i], s);
    }
    return a0;
}

template<typename T, std::size_t N>
inline std::array<T, N> operator*(float s, const std::array<T, N>& a1) {
    std::array<T, N> a0;
    for (int i=0; i<N; i++) {
        a0[i] = tt::mul<float>(s, a1[i]);
    }
    return a0;
}

template<typename T, std::size_t N>
inline std::array<T, N> operator/(const std::array<T, N>& a1, const std::array<T, N>& a2) {
    std::array<T, N> a0;
    for (int i=0; i<N; i++) {
        a0[i] = tt::div(a1[i], a2[i]);
    }
    return a0;
}

#endif  // tt_type_h

