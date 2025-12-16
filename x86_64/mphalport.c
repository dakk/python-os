#include <unistd.h>
#include "mphalport.h"


// Receive single character
int mp_hal_stdin_rx_chr(void) {
    // TODO: actually read from keyboard; for now just block forever
    for (;;) { __asm__ __volatile__("hlt"); }
}

#define DEFAULT_ATTR 0x07
volatile unsigned short *video = (volatile unsigned short*)0xB8000;

mp_uint_t mp_hal_stdout_tx_strn(const char *str, mp_uint_t len) {
    while (len--) {
        unsigned char c = *str++;
        video[0] = ((unsigned short)DEFAULT_ATTR << 8) | c;
        video++;
    }
    return len;
}


void mp_hal_stdout_clear() {
    int i;
    video = (volatile unsigned short*)0xB8000;
    for (i = 0; i < 80 * 25; i++) {
        video[0] = ((unsigned short)DEFAULT_ATTR << 8) | ' ';
        video++;
    }
    video = (volatile unsigned short*)0xB8000;
}