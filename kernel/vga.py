# Copyright (C) 2026  Davide Gessa

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

import io

VGA_CRTC_IDX = 0x3D4
VGA_CRTC_DATA = 0x3D5

VGA_MISC_W = 0x3C2
VGA_SEQ_I  = 0x3C4
VGA_SEQ_D  = 0x3C5
VGA_CRTC_I = 0x3D4
VGA_CRTC_D = 0x3D5
VGA_GC_I   = 0x3CE
VGA_GC_D   = 0x3CF
VGA_AC_I   = 0x3C0

def set_cursor(pos):  # pos = row*80 + col (0-3999)
    io.outb(VGA_CRTC_IDX, 0x0F)
    io.outb(VGA_CRTC_DATA, pos & 0xFF)
    io.outb(VGA_CRTC_IDX, 0x0E)
    io.outb(VGA_CRTC_DATA, (pos >> 8) & 0xFF)


def set_vga_mode13h():
    """Switch to 320x200x256 Mode 13h"""
    # 1. Disable screen
    io.outb(VGA_MISC_W, 0x00)
    io.outb(VGA_SEQ_I, 0x01); io.outb(VGA_SEQ_D, 0x01)
    
    # 2. Sequencer setup
    io.outb(VGA_SEQ_I, 0x00); io.outb(VGA_SEQ_D, 0x01)  # Reset
    io.outb(VGA_SEQ_I, 0x02); io.outb(VGA_SEQ_D, 0x0F)  # All planes
    io.outb(VGA_SEQ_I, 0x04); io.outb(VGA_SEQ_D, 0x0E)  # Unlock CRTC
    
    # 3. CRTC registers (320x200)
    crtc = [0x11,0x00, 0x00,0x00, 0x00,0x00, 0x05,0x41,
            0x0F,0x9C, 0xFF,0x50, 0x82,0x55, 0x81,0x2B,
            0x3F,0x80, 0xC3,0xFF, 0x00,0x00, 0x00,0x00,
            0xEA,0x8C, 0xDF,0xE7, 0x04]
    for i, val in enumerate(crtc):
        io.outb(VGA_CRTC_I, i)
        io.outb(VGA_CRTC_D, val)
    
    # 4. Graphics Controller
    gc_regs = [(0,0),(1,0),(2,0),(4,0),(5,0),(6,5)]
    for idx, val in gc_regs:
        io.outb(VGA_GC_I, idx); io.outb(VGA_GC_D, val)
    
    # 5. Attribute Controller (basic palette)
    io.outb(VGA_AC_I, 0x20)  # Palette flip-flop off
    for i in range(16):
        io.outb(VGA_AC_I, i)
    
    # 6. Enable display
    io.outb(VGA_SEQ_I, 0x01); io.outb(VGA_SEQ_D, 0x03)
    io.outb(VGA_MISC_W, 0x23)  # 25MHz, enable