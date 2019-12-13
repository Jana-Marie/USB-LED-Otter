#include "stm32f0xx_hal.h"
#include "defines.h"
#include <string.h>

uint16_t write_buffer[LED_BUFFER_SIZE];

typedef struct {
    double g;       // a fraction between 0 and 1
    double r;       // a fraction between 0 and 1
    double b;       // a fraction between 0 and 1
}rgb;

typedef struct {
    double h;       // angle in degrees
    double s;       // a fraction between 0 and 1
    double v;       // a fraction between 0 and 1
}hsv;

void set_pixel(uint16_t led, rgb in, uint16_t *_write_buffer);
hsv rgb2hsv(rgb in);
rgb hsv2rgb(hsv in);
