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

CMOS_ADDR = 0x70
CMOS_DATA = 0x71

def cmos_read(reg):
    io.outb(CMOS_ADDR, reg)
    return io.inb(CMOS_DATA)

# BCD to decimal
def bcd2dec(bcd):
    return ((bcd & 0xF0) >> 4) * 10 + (bcd & 0x0F)

def rtc():
    seconds = bcd2dec(cmos_read(0x00))
    minutes = bcd2dec(cmos_read(0x02))
    hour = bcd2dec(cmos_read(0x04))
    day =  bcd2dec(cmos_read(0x07))
    month = bcd2dec(cmos_read(0x08))
    year = bcd2dec(cmos_read(0x09)) + 2000
    return (year, month, day, hour, minutes, seconds)
