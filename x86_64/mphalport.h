#include "py/mpconfig.h"


// Receive single character
int mp_hal_stdin_rx_chr(void);

// Send string of given length
mp_uint_t mp_hal_stdout_tx_strn(const char *str, mp_uint_t len);


void mp_hal_stdout_clear();

static inline mp_uint_t mp_hal_ticks_ms(void) {
    return 0;
}

static inline void mp_hal_set_interrupt_char(char c) {
}
