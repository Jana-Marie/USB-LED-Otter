#include "sk6812.h"

hsv rgb2hsv(rgb in)
{
    hsv         out;
    double      min, max, delta;

    min = in.r < in.g ? in.r : in.g;
    min = min  < in.b ? min  : in.b;

    max = in.r > in.g ? in.r : in.g;
    max = max  > in.b ? max  : in.b;

    out.v = max;                                // v
    delta = max - min;
    if (delta < 0.00001)
    {
        out.s = 0;
        out.h = 0; // undefined, maybe nan?
        return out;
    }
    if( max > 0.0 ) { // NOTE: if Max is == 0, this divide would cause a crash
        out.s = (delta / max);                  // s
    } else {
        // if max is 0, then r = g = b = 0
        // s = 0, h is undefined
        out.s = 0.0;
        out.h = 0.0;                            // its now undefined
        return out;
    }
    if( in.r >= max )                           // > is bogus, just keeps compilor happy
        out.h = ( in.g - in.b ) / delta;        // between yellow & magenta
    else
    if( in.g >= max )
        out.h = 2.0 + ( in.b - in.r ) / delta;  // between cyan & yellow
    else
        out.h = 4.0 + ( in.r - in.g ) / delta;  // between magenta & cyan

    out.h *= 60.0;                              // degrees

    if( out.h < 0.0 )
        out.h += 360.0;

    return out;
}


rgb hsv2rgb(hsv in)
{
    double      hh, p, q, t, ff;
    long        i;
    rgb         out;

    if(in.s <= 0.0) { 
        out.r = in.v;
        out.g = in.v;
        out.b = in.v;
        return out;
    }
    hh = in.h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = in.v * (1.0 - in.s);
    q = in.v * (1.0 - (in.s * ff));
    t = in.v * (1.0 - (in.s * (1.0 - ff)));

    switch(i) {
    case 0:
        out.r = in.v;
        out.g = t;
        out.b = p;
        break;
    case 1:
        out.r = q;
        out.g = in.v;
        out.b = p;
        break;
    case 2:
        out.r = p;
        out.g = in.v;
        out.b = t;
        break;

    case 3:
        out.r = p;
        out.g = q;
        out.b = in.v;
        break;
    case 4:
        out.r = t;
        out.g = p;
        out.b = in.v;
        break;
    case 5:
    default:
        out.r = in.v;
        out.g = p;
        out.b = q;
        break;
    }
    return out;
}

void set_pixel(uint16_t led, rgb in,uint16_t *_write_buffer) {
	//r
	_write_buffer[((led)*24)+0] = ((int)(in.g*255) & 0x80) ? LED_CMPH:LED_CMPL;
	_write_buffer[((led)*24)+1] = ((int)(in.g*255) & 0x40) ? LED_CMPH:LED_CMPL;
	_write_buffer[((led)*24)+2] = ((int)(in.g*255) & 0x20) ? LED_CMPH:LED_CMPL;
	_write_buffer[((led)*24)+3] = ((int)(in.g*255) & 0x10) ? LED_CMPH:LED_CMPL;
	_write_buffer[((led)*24)+4] = ((int)(in.g*255) & 0x08) ? LED_CMPH:LED_CMPL;
	_write_buffer[((led)*24)+5] = ((int)(in.g*255) & 0x04) ? LED_CMPH:LED_CMPL;
	_write_buffer[((led)*24)+6] = ((int)(in.g*255) & 0x02) ? LED_CMPH:LED_CMPL;
	_write_buffer[((led)*24)+7] = ((int)(in.g*255) & 0x01) ? LED_CMPH:LED_CMPL;
	//g
	_write_buffer[((led)*24)+8]  = ((int)(in.r*255) & 0x80) ? LED_CMPH:LED_CMPL;
	_write_buffer[((led)*24)+9]  = ((int)(in.r*255) & 0x40) ? LED_CMPH:LED_CMPL;
	_write_buffer[((led)*24)+10] = ((int)(in.r*255) & 0x20) ? LED_CMPH:LED_CMPL;
	_write_buffer[((led)*24)+11] = ((int)(in.r*255) & 0x10) ? LED_CMPH:LED_CMPL;
	_write_buffer[((led)*24)+12] = ((int)(in.r*255) & 0x08) ? LED_CMPH:LED_CMPL;
	_write_buffer[((led)*24)+13] = ((int)(in.r*255) & 0x04) ? LED_CMPH:LED_CMPL;
	_write_buffer[((led)*24)+14] = ((int)(in.r*255) & 0x02) ? LED_CMPH:LED_CMPL;
	_write_buffer[((led)*24)+15] = ((int)(in.r*255) & 0x01) ? LED_CMPH:LED_CMPL;
	//b
	_write_buffer[((led)*24)+16] = ((int)(in.b*255) & 0x80) ? LED_CMPH:LED_CMPL;
	_write_buffer[((led)*24)+17] = ((int)(in.b*255) & 0x40) ? LED_CMPH:LED_CMPL;
	_write_buffer[((led)*24)+18] = ((int)(in.b*255) & 0x20) ? LED_CMPH:LED_CMPL;
	_write_buffer[((led)*24)+19] = ((int)(in.b*255) & 0x10) ? LED_CMPH:LED_CMPL;
	_write_buffer[((led)*24)+20] = ((int)(in.b*255) & 0x08) ? LED_CMPH:LED_CMPL;
	_write_buffer[((led)*24)+21] = ((int)(in.b*255) & 0x04) ? LED_CMPH:LED_CMPL;
	_write_buffer[((led)*24)+22] = ((int)(in.b*255) & 0x02) ? LED_CMPH:LED_CMPL;
	_write_buffer[((led)*24)+23] = ((int)(in.b*255) & 0x01) ? LED_CMPH:LED_CMPL;
}
