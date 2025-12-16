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

#include "video.h"


vcolor_t video_std_color = 7;
uint8_t video_x = 0;
uint8_t video_y = 0;



void video_putchar(uint8_t ch) {
	char *vidmem = (char *) VIDEO_MEM;
	unsigned int i = 0;
	int x;

	// Calcola la posizione nel buffer video
	i = (video_y * VIDEO_MAX_X * 2) + (video_x * 2);
	
	// Esaminiamo il carattere
	switch(ch)
	{
		case '\n':
			video_y++;
			video_x = 0;
			break;

		case '\r':
			break;
			
		case '\b':
			if(video_x == 0)
			{
				video_x = VIDEO_MAX_X-1;
				video_y = video_y-1;
			}
			video_x--;
			vidmem[i-2] = ' ';
			vidmem[i-1] = video_std_color;
			break;
		
		case '\t':
			for(x = 0; x < VIDEO_TAB_DIM; x++)
				video_putchar(' ');
			break;

		default:
			vidmem[i] = ch;
			i++;
			vidmem[i] = video_std_color;
			video_x++;
			break;
	}


	if(video_y >= VIDEO_MAX_Y)
		video_scroll_dw();
		
	if(video_x >= VIDEO_MAX_X) {
		video_y++;
		video_x = 0;
	}
	
	video_move_cursor(video_x, video_y);
}


void video_backspace() {
	char *vidmem = (char *) VIDEO_MEM;
	unsigned int i = 0;
	int x;

	// Calcola la posizione nel buffer video
	i = (video_y * VIDEO_MAX_X * 2) + (video_x * 2);
	
	if(video_x == 0)
    {
        video_x = VIDEO_MAX_X-1;
        video_y = video_y-1;
    }
    video_x--;
    vidmem[i-2] = ' ';
    vidmem[i-1] = video_std_color;	
}




void video_scroll_dw() {
	char *vidmem = (char *) VIDEO_MEM;
	
	unsigned int x;
	unsigned int y;
	unsigned int i;
	unsigned int j;
	
	
	for(x = 0; x < VIDEO_MAX_X; x++)
	{
		for(y = 0; y <= VIDEO_MAX_Y; y++)
		{
			i = (y * VIDEO_MAX_X * 2) + (x * 2);
			j = ((y+1) * VIDEO_MAX_X * 2) + (x * 2);
			vidmem[i] = vidmem[j];
			i++; j++;
			vidmem[i] = vidmem[j];
 		}
	}
	
	video_y--;		
}



void video_puts(uint8_t *str) {
	while(*str != '\0') {
		video_putchar(*str);
		str++;
	}	
}



void video_gotoxy(uint8_t x, uint8_t y) {
	video_x = x;
	video_y = y;
	video_move_cursor(video_x, video_y);
}


void video_move_cursor(uint8_t x, uint8_t y) {
    __asm__ __volatile__ (
        "movw $0x3D4, %%dx    \n"
        "movb $0x0F, %%al     \n"
        "out  %%al, %%dx      \n"
        "movw $0x3D5, %%dx    \n"
        "movb %0, %%al        \n"
        "out  %%al, %%dx      \n"
        "movw $0x3D4, %%dx    \n"
        "movb $0x0E, %%al     \n"
        "out  %%al, %%dx      \n"
        "movw $0x3D5, %%dx    \n"
        "movb %1, %%al        \n"
        "out  %%al, %%dx      \n"
        :
        : "r"(x), "r"(y)
        : "ax", "dx"
    );
}


void video_clear() {
	unsigned char *vidmem = (unsigned char *) VIDEO_MEM;
	int i = 0;

	while(i < (VIDEO_MAX_X * VIDEO_MAX_Y * 2))
	{
		vidmem[i] = ' ';
		i++;
		vidmem[i] = video_std_color;
		i++;
	}
	video_gotoxy(0,0);
}

void video_set_color(vcolor_t cl) {
	video_std_color = cl;
}
