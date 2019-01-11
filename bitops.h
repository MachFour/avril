//
// Created by max on 1/3/19.
//

#ifndef AVRLIB_BITOPS_H
#define AVRLIB_BITOPS_H

#include <inttypes.h>

// get rid of warnings about unsigned bitwise operations

template <typename T>
inline constexpr uint8_t U8(T x) {
    return static_cast<uint8_t>(x);
}

template <typename T>
inline constexpr uint8_t U7(T x) {
  return static_cast<uint8_t>(x & 0x7f);
}

template <typename T>
inline constexpr uint16_t U16(T x) {
    return static_cast<uint16_t>(x);
}
template <typename T>
inline constexpr int8_t S8(T x) {
    return static_cast<int8_t>(x);
}

template <typename T>
inline constexpr int16_t S16(T x) {
    return static_cast<int16_t>(x);
}

// returns bit at 8th position (MSB for a byte)
template <typename T>
inline constexpr uint8_t MSB8(T x) {
    return U8((x & 0x80u) != 0);

}

// easy way to make uint8_t integer literals
inline constexpr uint8_t operator "" _u8(unsigned long long arg) noexcept {
    return U8(arg);

}
// easy way to make uint16_t integer literals
inline constexpr uint16_t operator "" _u16(unsigned long long arg) noexcept {
    return U16(arg);
}


inline constexpr uint8_t highByte(uint16_t w) {
    return U8(w >> 8u);
}
inline constexpr uint8_t highByte(int16_t w) {
    return U8(U16(w) >> 8u);
}
inline constexpr uint8_t lowByte(uint16_t w) {
    return U8(w);
}
inline constexpr uint8_t lowByte(int16_t w) {
    return U8(w);
}

template<typename S, typename T>
inline constexpr uint8_t byteOr(S b1, T b2) {
    return U8(U8(b1) | U8(b2));
}

template<typename S, typename T>
inline constexpr uint8_t byteAnd(S b1, T b2) {
    return U8(U8(b1) & U8(b2));
}

template<typename S, typename T, typename U>
inline constexpr uint8_t byteOr(S b1, T b2, U b3) {
    return byteOr(byteOr(b1, b2), b3);
}

template<typename S, typename T, typename U>
inline constexpr uint8_t byteAnd(S b1, T b2, U b3) {
    return byteAnd(byteAnd(b1, b2), b3);
}

template<typename T>
inline constexpr uint8_t bitFlag(T b) {
    return U8(1u << U8(b));
}

template<typename T>
inline constexpr uint8_t byteInverse(T b) {
    return U8(~b);
}

//#define mask1(bit1) bitMask(bit1)
//#define mask2(bit1, bit2) byteOr(bitMask(bit1), bitMask(bit2))
//#define mask3(bit1, bit2, bit3) byteOr3(bitMask(bit1), bitMask(bit2), bitMask(bit3))



#endif //AVRLIB_BITOPS_H
