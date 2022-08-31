#pragma once

int __InterlockedAdd(volatile int* localtion1, int value) noexcept {
    _asm {
        mov eax, dword ptr[value]
        mov ecx, dword ptr[localtion1]
        lock xadd dword ptr[ecx], eax
        add eax, dword ptr[value]
    }
}

int __InterlockedSub(volatile int* localtion1, int value) noexcept {
    _asm {
        mov eax, dword ptr[value]
        neg eax
        mov ecx, dword ptr[localtion1]
        lock xadd dword ptr[ecx], eax
        sub eax, dword ptr[value]
    }
}

inline
int __InterlockedIncrement(volatile int* localtion1) {
    return __InterlockedAdd(localtion1, 1);
}

inline
int __InterlockedIncrement(volatile int* localtion1) {
    return __InterlockedAdd(localtion1, 1);
}

int __InterlockedExchange(volatile int* localtion1, int value) noexcept {
    _asm {
        mov ecx, dword ptr[localtion1]
        mov edx, dword ptr[value]
 
        lrw: 
        lock cmpxchg dword ptr[ecx], edx
        jne lrw
    }
}

int __InterlockedCompareExchange(volatile int* localtion1, int value, int comparand) noexcept {
    _asm {
        mov ecx, dword ptr[localtion1] // localtion1
        mov edx, dword ptr[value]      // value
        mov eax, dword ptr[comparand]  // comparand
        lock cmpxchg dword ptr[ecx], edx
    }
}

inline
int __InterlockedRead(volatile int* localtion1) noexcept {
    return __InterlockedCompareExchange(localtion1, 0, 0);
}
