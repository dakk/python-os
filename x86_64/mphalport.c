#include <unistd.h>
#include "mphalport.h"

#define DEFAULT_ATTR 0x07

volatile unsigned char *video = (volatile unsigned char*)0xB8000;


int mp_hal_stdin_rx_chr(void) {
    // TODO: actually read from keyboard; for now just block forever
    for (;;) { __asm__ __volatile__("hlt"); }
}


mp_uint_t mp_hal_stdout_tx_strn(const char *str, mp_uint_t len) {
    while (len--) {
        if (*str == '\n' || *str == '\r') {
            *str++;
            continue;
        }
        *video++ = *str++;
        *video++ = DEFAULT_ATTR;
    }
    return len;
}


void mp_hal_stdout_clear() {
    int i;
    video = (volatile unsigned char*) 0xB8000;
    for (i = 0; i < 80 * 25; i++) {
        *video++ = ' ';
        *video++ = DEFAULT_ATTR;
    }
    video = (volatile unsigned char*)0xB8000;
}