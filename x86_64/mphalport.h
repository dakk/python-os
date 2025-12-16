// Copyright (C) 2025  Davide Gessa

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

#include "py/mpconfig.h"

int mp_hal_stdin_rx_chr(void);

mp_uint_t mp_hal_stdout_tx_strn(const char *str, mp_uint_t len);

static inline mp_uint_t mp_hal_ticks_ms(void) {
    return 0;
}

static inline void mp_hal_set_interrupt_char(char c) {
}
