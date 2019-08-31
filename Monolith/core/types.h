#pragma once

namespace Monolith
{
    using u8  = unsigned char;
    using u16 = unsigned short;
    using u32 = unsigned long;
    using u64 = unsigned long long;

    using s8  = signed char;
    using s16 = signed short;
    using s32 = signed long;
    using s64 = signed long long;

    using f32 = float;

    constexpr u8 u8Max = 0xFF;
    constexpr u16 u16Max = 0xFFFF;
    constexpr u32 u32Max = 0xFFFFFFFF;
    constexpr u64 u64Max = 0xFFFFFFFFFFFFFFFF;
    constexpr s8 s8Max = 0x7F;
    constexpr s16 s16Max = 0x7FFF;
    constexpr s32 s32Max = 0x7FFFFFFF;
    constexpr s64 s64Max = 0x7FFFFFFFFFFFFFFF;
}