// Copyright (C) 2009-2025  Davide Gessa

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <types.h>

static inline uint8_t inb(uint16_t port ) {
    register uint8_t value;
 
    __asm__ __volatile__(
        "inb %1, %0\n"
        : "=a" ( value )
        : "dN" ( port )
    );
 
    return value;
}
 
static inline void outb(uint8_t data, uint16_t port ) {
    __asm__ __volatile__(
        "outb %1, %0\n"
        :
        : "dN" ( port ), "a" ( data )
    );
}
 
static inline uint16_t inw(uint16_t port ) {
    register uint16_t value;
 
    __asm__ __volatile__(
        "inw %1, %0\n"
        : "=a" ( value )
        : "dN" ( port )
    );
 
    return value;
}
 
static inline void outw(uint16_t data, uint16_t port ) {
    __asm__ __volatile__(
        "outw %1, %0\n"
        :
        : "dN" ( port ), "a" ( data )
    );
}
 
static inline uint32_t inl(uint16_t port ) {
    register uint32_t value;
 
    __asm__ __volatile__(
        "inl %1, %0\n"
        : "=a" ( value )
        : "dN" ( port )
    );
 
    return value;
}
 
static inline void outl(uint32_t data, uint16_t port ) {
    __asm__ __volatile__(
        "outl %1, %0\n"
        :
        : "dN" ( port ), "a" ( data )
    );
}