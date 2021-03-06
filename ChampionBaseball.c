#include <math.h>

#include "SGlib.h"
#include "PSGlib.h"

// 背景
const unsigned char bgTileData[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x01,0x07,0x0F,0x0F,0x1F,
0x07,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xE0,0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x00,0x00,0x00,0x80,0xE0,0xF0,0xF0,0xF8,
0x3F,0x3F,0x7F,0x7F,0x7F,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,
0xFC,0xFC,0xFE,0xFE,0xFE,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0x7F,0x7F,0x7F,0x3F,0x3F,
0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFE,0xFE,0xFE,0xFC,0xFC,
0x1F,0x0F,0x0F,0x07,0x01,0x00,0x00,0x00,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x3F,0x07,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0xE0,
0xF8,0xF0,0xF0,0xE0,0x80,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x80,0xC0,0xE0,0xF0,
0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x0F,
0xF8,0xFC,0xFE,0xFF,0xFF,0xFF,0x7F,0x3F,
0x1F,0x3F,0x7F,0xFF,0xFF,0xFF,0xFE,0xFC,
0x9F,0xCF,0xE7,0xF3,0xF9,0xFC,0xFE,0xFF,
0xF9,0xF3,0xE7,0xCF,0x9F,0x3F,0x7F,0xFF,
0xFF,0xFF,0x7F,0x3F,0x1F,0x0F,0x07,0x03,
0xFF,0xFF,0xFE,0xFC,0xF8,0xF0,0xE0,0xC0,
0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x03,0x0F,0x1F,0x7F,
0x00,0x03,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,
0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x00,0xC0,0xF8,0xFF,0xFF,0xFF,0xFF,0xFF,
0x00,0x00,0x00,0x00,0xC0,0xF0,0xF8,0xFE,
0xF8,0xFD,0xFF,0xFF,0xFF,0xFF,0x7F,0x3F,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x1F,0xBF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFC,
0xFF,0xFF,0x7F,0x3F,0x1F,0x0F,0x0F,0x0F,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x3F,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFC,
0xFF,0xFF,0xFE,0xFC,0xF8,0xF0,0xF0,0xF0,
0x1F,0x1F,0x1F,0x3F,0x3F,0x3F,0x7F,0x7F,
0x00,0x00,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,
0x00,0x00,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,
0xF8,0xF8,0xF8,0xFC,0xFC,0xFC,0xFE,0xFE,
0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,
0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,
0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0x80,
0xFF,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0xFE,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,
0x80,0xC0,0xE0,0xF0,0xF8,0xFC,0xFE,0xFF,
0x01,0x03,0x07,0x0F,0x1F,0x3F,0x7F,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFE,
0x7F,0x7F,0x3F,0x3F,0x3F,0x1F,0x1F,0x1F,
0x3F,0x3F,0x3F,0x3F,0x3F,0x3F,0x00,0x00,
0xFC,0xFC,0xFC,0xFC,0xFC,0xFC,0x00,0x00,
0xFE,0xFE,0xFC,0xFC,0xFC,0xF8,0xF8,0xF8,
};
#define bgTileDataSize 528

const unsigned char bgTileMapData[] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x02,0x03,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x06,0x06,0x07,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x09,0x09,0x0A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0B,0x0C,0x0D,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,
0x11,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x12,
0x13,0x11,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x12,0x14,
0x15,0x13,0x11,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x12,0x14,0x16,
0x17,0x15,0x13,0x11,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x12,0x14,0x16,0x18,
0x00,0x17,0x15,0x13,0x11,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x12,0x14,0x16,0x18,0x00,
0x00,0x00,0x17,0x15,0x13,0x11,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x12,0x14,0x16,0x18,0x00,0x00,
0x00,0x00,0x00,0x17,0x15,0x13,0x11,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x12,0x14,0x16,0x18,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x17,0x15,0x13,0x11,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x12,0x14,0x16,0x18,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x17,0x15,0x13,0x11,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x12,0x14,0x16,0x18,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x17,0x15,0x13,0x11,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x12,0x14,0x16,0x18,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x17,0x15,0x13,0x11,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x12,0x14,0x16,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x17,0x15,0x13,0x11,0x0F,0x19,0x1A,0x1B,0x1C,0x1D,0x1E,0x10,0x12,0x14,0x16,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x17,0x15,0x13,0x1F,0x20,0x20,0x20,0x20,0x20,0x20,0x21,0x14,0x16,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x17,0x22,0x13,0x23,0x20,0x20,0x20,0x20,0x24,0x14,0x25,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x26,0x20,0x27,0x28,0x20,0x20,0x27,0x28,0x20,0x29,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x2A,0x20,0x2B,0x2C,0x2D,0x2E,0x2B,0x2C,0x20,0x2F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x20,0x2B,0x2C,0x31,0x32,0x2B,0x2C,0x20,0x33,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x34,0x20,0x35,0x36,0x20,0x20,0x35,0x36,0x20,0x37,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
#define bgTileMapDataWidth 32
#define bgTileMapDataHeight 24

const unsigned char bgColourData[] = {
        0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,// 2000
        0x62,0x62,0x62,0x62,0x62,0x62,0x62,0x62,
        0x62,0x62,0x62,0x62,0x62,0x62,0x62,0x62,
        0x62,0x62,0x62,0x62,0x62,0x62,0x62,0x62,
        0x62,0x62,0x62,0x62,0x62,0x62,0x62,0x62,
        0x62,0x62,0x62,0x62,0x62,0x62,0x62,0x62,
        0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,// 2030
        0x62,0x62,0x62,0x62,0x62,0x62,0x62,0x62,// 2038
        0x62,0x62,0x62,0x62,0x62,0x62,0x62,0x62,// 2040
        0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,// 2048
        0x62,0x62,0x62,0x62,0x62,0x62,0x62,0x62,// 2050
        0x62,0x62,0x62,0x62,0x62,0x62,0x62,0x62,// 2058
        0x62,0x62,0x62,0x62,0x62,0x62,0x62,0x62,// 2060
        0x62,0x62,0x62,0x62,0x62,0x62,0x62,0x62,// 2068
        0x62,0x62,0x62,0x62,0x62,0x62,0x62,0x62,// 2070
        0x62,0x62,0x62,0x62,0x62,0x62,0x62,0x62,// 2078
        0x62,0x62,0x62,0x62,0x62,0x62,0x62,0x62,// 2080
        0x62,0x62,0x62,0x62,0x6F,0x6F,0x6F,0x6F,// 2088
        0x62,0x62,0x62,0x62,0x6F,0x6F,0x6F,0x6F,// 2090
        0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,// 98
        0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,//a0
        0x62,0x62,0x62,0x62,0x62,0x62,0x62,0x62,//a8
        0x62,0x62,0x62,0x62,0x62,0x62,0x62,0x62,//b0
        0x62,0x62,0x62,0x62,0x62,0x62,0x62,0x62,//b8
        0x62,0x62,0x62,0x62,0x62,0x62,0x62,0x62,//c0
        0x62,0x62,0x62,0x62,0x62,0x62,0x62,0x62,//c8
        0x62,0x62,0x62,0x62,0x62,0x62,0x62,0x62,//d0
        0x62,0x62,0x62,0x62,0x62,0x62,0x62,0x62,//d8
        0x62,0x62,0x62,0x62,0x62,0x62,0x62,0x62,//e0
        0x62,0x62,0x62,0x62,0x62,0x62,0x62,0x62,//e8
        0x62,0x62,0x62,0x62,0x62,0x62,0x62,0x62,//f0
        0x62,0x62,0x62,0x62,0x6F,0x6F,0x6F,0x6F,//f8
        0x62,0x62,0x62,0x62,0x62,0x62,0x62,0x62,//100
        0x62,0x62,0x62,0x62,0x6F,0x6F,0x6F,0x6F,//108
        0x62,0x62,0x62,0x62,0x62,0x62,0x62,0x62,//110
        0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,//118
        0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,//120
        0x62,0x62,0x62,0x62,0x62,0x62,0x62,0x62,//128
        0x62,0x62,0x62,0x62,0x62,0x62,0x62,0x62,//130
        0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,//138
        0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,//140
        0x62,0x62,0x62,0x62,0x62,0x62,0x62,0x62,//148
        0x62,0x62,0x62,0x62,0x62,0x62,0x62,0x62,//150
        0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,//158
        0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,//160
        0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,//168
        0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,//170
        0x62,0x62,0x62,0x62,0x62,0x62,0x62,0x62,//178
        0x62,0x62,0x62,0x62,0x62,0x62,0x62,0x62,//180
        0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,//188
        0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,//190
        0x62,0x62,0x62,0x62,0x62,0x62,0x62,0x62,//198
        0x62,0x62,0x62,0x62,0x62,0x62,0x62,0x62,//1a0
        0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,//1a8
        0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,0x6F,//1b0
        0x62,0x62,0x62,0x62,0x62,0x62,0x62,0x62,
};
#define bgColourDataSize 528
// 背景 ここまで

// ピッチャー
const unsigned char pitcherTileData[] = {
        0x07,0x08,0x08,0x3F,0x0A,0x0A,0x04,0x0B,
        0x10,0x34,0x4F,0x48,0x3B,0x0A,0x1E,0x1E,
        0xE0,0x10,0x10,0xF0,0x50,0x50,0x20,0xD0,
        0x08,0x2C,0xF2,0x12,0xDC,0x50,0x78,0x78,

        0x07,0x08,0x38,0x5F,0x4A,0x3A,0x24,0x23,
        0x20,0x10,0x0F,0x08,0x0B,0x0A,0x1E,0x1E,
        0xE0,0x10,0x16,0xF9,0x59,0x56,0x24,0xC4,
        0x04,0x08,0xF0,0x10,0xD0,0x50,0x78,0x78,

        0x07,0x08,0x08,0x1F,0x0A,0x1A,0x24,0x27,
        0x18,0x04,0x3F,0x20,0x2F,0x79,0x7B,0x03,
        0xE0,0x10,0x10,0xF0,0x50,0x50,0x20,0xC0,
        0x40,0x40,0xC0,0x40,0x40,0x40,0xC0,0xC0,

        0x60,0x91,0x92,0x7A,0x27,0x12,0x0A,0x05,
        0x04,0x04,0x07,0x04,0x0D,0x0D,0x0E,0x00,
        0x00,0xF8,0x04,0x04,0xFE,0x94,0x94,0x08,
        0xF8,0x24,0xE4,0x38,0xA0,0xA0,0xF0,0xF0,

        0x00,0x00,0x01,0x02,0x02,0x03,0x06,0x0A,
        0x1B,0x1E,0x19,0x1C,0x03,0x01,0x01,0x01,
        0x00,0x00,0xF8,0x04,0x04,0xFE,0x94,0x94,
        0x08,0xF0,0x10,0xC8,0x66,0x59,0xE9,0xE6,
};

const unsigned char pitcherTileMask[] = {
        0x07,0x0F,0x0F,0x3F,0x0F,0x0F,0x07,0x0F, 0x1F,0x3F,0x7F,0x7F,0x3F,0x0E,0x1E,0x1E, 0xE0,0xF0,0xF0,0xF0,0xF0,0xF0,0xE0,0xF0, 0xF8,0xFC,0xFE,0xFE,0xFC,0x70,0x78,0x78,
        0x07,0x0F,0x3F,0x7F,0x7F,0x3F,0x3F,0x3F, 0x3F,0x1F,0x0F,0x0F,0x0F,0x0E,0x1E,0x1E, 0xE0,0xF0,0xF6,0xFF,0xFF,0xFE,0xFC,0xFC, 0xFC,0xF8,0xF0,0xF0,0xF0,0x70,0x78,0x78,
        0x07,0x0F,0x0F,0x1F,0x0F,0x1F,0x3F,0x3F, 0x1F,0x07,0x3F,0x3F,0x3F,0x79,0x7B,0x03, 0xE0,0xF0,0xF0,0xF0,0xF0,0xF0,0xE0,0xC0, 0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,0xC0,
        0x60,0xF1,0xF3,0x7B,0x3F,0x1F,0x0F,0x07, 0x07,0x07,0x07,0x07,0x0F,0x0F,0x0E,0x00, 0x00,0xF8,0xFC,0xFC,0xFE,0xFC,0xFC,0xF8, 0xF8,0xFC,0xFC,0xF8,0xE0,0xE0,0xF0,0xF0,
        0x00,0x00,0x01,0x03,0x03,0x03,0x07,0x0F, 0x1F,0x1F,0x1F,0x1F,0x03,0x01,0x01,0x01, 0x00,0x00,0xF8,0xFC,0xFC,0xFE,0xFC,0xFC, 0xF8,0xF0,0xF0,0xF8,0xFE,0xDF,0xEF,0xE6,
};

#define pitcherTileDataSize 32*5
// ピッチャー ここまで

// バッター
const unsigned char batterTileData[] = {
        0x00,0x00,0x01,0x01,0x01,0x01,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0xC0,0x23,0x24,0x24,0x2F,0x97,0x97, 0x93,0x51,0x52,0x53,0x74,0x48,0x4F,0x3A,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x25,0x25,0x19,0x01,0x01,0x07,0x07,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0xF0,0x08,0x08,0xF8,0xF8,0xF8, 0xF0,0xE0,0x10,0x88,0x08,0x08,0x88,0x08, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0xF0,0x10,0x50,0x50,0x50,0xD0,0xF0,0xF0, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x03,0x04,0x04,0x0F,0x07,0x07, 0x03,0x01,0x02,0x02,0x0C,0x13,0x32,0x4C,
        0x00,0x03,0x04,0x08,0x11,0x12,0x0C,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0xCF,0x32,0x42,0x87,0x07,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0xF0,0x08,0x08,0xF8,0xF8,0xF8, 0xF0,0xE0,0x10,0x08,0x88,0x08,0x48,0x48, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0xF0,0x10,0xD0,0xD0,0xD0,0x50,0xF0,0xF0, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x7F,0x80,0x81,0x7E,0x00,0x00, 0x00,0x00,0x03,0x04,0x04,0x0F,0x07,0x07, 0x03,0x01,0xFF,0x2A,0xEB,0x1C,0x0F,0x02,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x01,0x01,0x01,0x03,0x03,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0xF0,0x08,0x08,0xF8,0xF8,0xF8, 0xF0,0xE0,0x10,0x88,0x08,0x48,0x88,0x08, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0xF0,0x10,0x50,0xD0,0xD0,0x50,0xF0,0xF0, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

        0x00,0x0C,0x12,0x11,0x08,0x04,0x02,0x01, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x03,0x04,0x84,0x8F,0x47,0x27, 0xB3,0x49,0x4E,0x33,0x10,0x0C,0x03,0x02,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x01,0x01,0x01,0x03,0x03,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0xF0,0x08,0x08,0xF8,0xF8,0xF8, 0xF0,0xE0,0x10,0x88,0x08,0x08,0x88,0x08, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0xF0,0x10,0x50,0xD0,0xD0,0x50,0xF0,0xF0, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x03,0x04,0x04,0x0F,0x07,0x07, 0x07,0x09,0x0A,0x06,0x02,0x02,0x02,0x02,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x01,0x01,0x01,0x03,0x03,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x01,0xF2,0x0C,0x0C,0xF9,0xFA,0xFC, 0xF0,0xE0,0x10,0x08,0x08,0x08,0x08,0x08, 0x00,0x80,0x40,0x40,0x80,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0xF0,0x10,0x50,0xD0,0xD0,0x50,0xF0,0xF0, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

const unsigned char batterTileMask[] = {
        0x00,0x00,0x01,0x01,0x01,0x01,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0xC0,0xE3,0xE7,0xE7,0xEF,0xF7,0xF7, 0xF3,0x71,0x73,0x73,0x77,0x7F,0x7F,0x3F,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x3D,0x3D,0x19,0x01,0x01,0x07,0x07,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0xF0,0xF8,0xF8,0xF8,0xF8,0xF8, 0xF0,0xE0,0xF0,0xF8,0xF8,0xF8,0xF8,0xF8, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x03,0x07,0x07,0x0F,0x07,0x07, 0x03,0x01,0x03,0x03,0x0F,0x1F,0x3F,0x7F,
        0x00,0x03,0x07,0x0F,0x1F,0x1E,0x0C,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0xFF,0xF3,0xC3,0x87,0x07,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0xF0,0xF8,0xF8,0xF8,0xF8,0xF8, 0xF0,0xE0,0xF0,0xF8,0xF8,0xF8,0xF8,0xF8, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0xF0,0xF0,0xF0,0xF0,0xF0,0x70,0xF0,0xF0, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x7F,0xFF,0xFF,0x7E,0x00,0x00, 0x00,0x00,0x03,0x07,0x07,0x0F,0x07,0x07, 0x03,0x01,0xFF,0xFF,0xFF,0x1F,0x0F,0x03,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x01,0x01,0x01,0x03,0x03,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0xF0,0xF8,0xF8,0xF8,0xF8,0xF8, 0xF0,0xE0,0xF0,0xF8,0xF8,0xF8,0xF8,0xF8, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0xF0,0xF0,0xF0,0xF0,0xF0,0x70,0xF0,0xF0, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

        0x00,0x0C,0x1E,0x1F,0x0F,0x07,0x03,0x01, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x03,0x07,0x87,0x8F,0xC7,0xE7, 0xF3,0x79,0x7F,0x3F,0x1F,0x0F,0x03,0x03,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x01,0x01,0x01,0x03,0x03,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0xF0,0xF8,0xF8,0xF8,0xF8,0xF8, 0xF0,0xE0,0xF0,0xF8,0xF8,0xF8,0xF8,0xF8, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0xF0,0xF0,0xF0,0xF0,0xF0,0x70,0xF0,0xF0, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,

        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x03,0x07,0x07,0x0F,0x07,0x07, 0x07,0x0F,0x0F,0x07,0x03,0x03,0x03,0x03,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x01,0x01,0x01,0x03,0x03,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x01,0xF3,0xFF,0xFF,0xFF,0xFE,0xFC, 0xF0,0xE0,0xF0,0xF8,0xF8,0xF8,0xF8,0xF8, 0x00,0x80,0xC0,0xC0,0x80,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0xF0,0xF0,0xF0,0xF0,0xF0,0x70,0xF0,0xF0, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

#define batterTileDataSize 8 * 16 * 5

#define BATTER_X (256 / 2 - 4)  // TODO 左バッターの場合
#define BATTER_Y (192 - 32)
// バッター ここまで

// ボール
const unsigned char ballTileData[] = {
        0x3C,0x66,0xC3,0x81,0x81,0xC3,0x66,0x3C,
};

const unsigned char ballTileMask[] = {
        0x3C,0x7E,0xFF,0xFF,0xFF,0xFF,0x7E,0x3C,
};
#define ballTileDataSize 8

#define BALL_X (256 / 2 - 16 / 2)
#define BALL_Y 16
// ボール ここまで


void main (void)
{
    SG_setSpriteMode (SG_SPRITEMODE_LARGE);

    unsigned int tilefrom = 0;  // 開始位置

    // VRAM0000番台に書き込む
    // Tileの書き込み
    for ( int i = 0; i < 3; i++ ){
        SG_loadTilePatterns(
            bgTileData,
            tilefrom+256*i,
            bgTileDataSize
        );
    }

    // VRAM2000番台に書き込む
    // 色の書き込み
    for ( int i = 0; i < 3; i++ ){
        SG_loadTileColours(
            bgColourData,
            tilefrom+256*i,
            bgColourDataSize
        );
    }

    // VRAM1800番台に書き込む
    // タイルマップの書き込み
    unsigned char x = 0;
    unsigned char y = 0;
    SG_loadTileMapArea(
		x,
		y,
		bgTileMapData,
		bgTileMapDataWidth,
		bgTileMapDataHeight
    );

    // ピッチャー
    unsigned char pitcherX = 256 / 2 - 16 / 2;
    unsigned char pitcherY = 0;
    
    // バッター
    unsigned char batterX = BATTER_X;
    unsigned char batterY = BATTER_Y;

    // ボール
    float ballX = BALL_X;
    float ballY = BALL_Y;

    // VRAM3800番台に書き込む
    // スプライトの書き込み
    
    unsigned int spriteSize = 0;

    // ピッチャー 4バイト x 5パターン
    tilefrom = spriteSize;  // 開始位置
    unsigned int pitcherTileAddress1 = tilefrom;
    SG_loadSpritePatterns(
        pitcherTileData,
        tilefrom,
        pitcherTileDataSize
    );
    spriteSize += 4 * 5;

    // ピッチャーマスク（２色目） 4バイト x 5パターン
    tilefrom = spriteSize;  // 開始位置
    unsigned int pitcherTileAddress2 = tilefrom;
    SG_loadSpritePatterns(
        pitcherTileMask,
        tilefrom,
        pitcherTileDataSize
    );
    spriteSize += 4 * 5;
    
    // バッター 16バイト x 5パターン
    tilefrom = spriteSize;  // 開始位置
    unsigned int batterTileAddress1 = tilefrom;
    SG_loadSpritePatterns(
        batterTileData,
        tilefrom,
        batterTileDataSize
    );
    spriteSize += 16 * 5;

    // バッター（２色目） 16バイト x 5パターン
    tilefrom = spriteSize;  // 開始位置
    unsigned int batterTileAddress2 = tilefrom;
    SG_loadSpritePatterns(
        batterTileMask,
        tilefrom,
        batterTileDataSize
    );
    spriteSize += 16 * 5;

    // ボール 1バイト
    tilefrom = spriteSize;  // 開始位置
    unsigned int ballTileAddress1 = tilefrom;
    SG_loadSpritePatterns(
        ballTileData,
        tilefrom,
        ballTileDataSize
    );
    spriteSize += 4;

    // ボール（２色目） 1バイト
    tilefrom = spriteSize;  // 開始位置
    unsigned int ballTileAddress2 = tilefrom;
    SG_loadSpritePatterns(
        ballTileMask,
        tilefrom,
        ballTileDataSize
    );
    spriteSize += 4;

    unsigned char isPitching = 0;
    unsigned char pitchingCount = 0;

    unsigned char isBatting = 0;
    unsigned char battingCount = 0;

    float ballSpeedX = 0;
    float ballSpeedX2 = 0;  // 変化球の時に使用
    float ballSpeedY = 2;

    // ディスプレイをオンにします
    SG_displayOn(); 

    while (1) {
        // ゲームループ

        // １PADの１ボタンを押したら、ボールを投げる
        if ( isPitching == 0 && SG_getKeysPressed () == PORT_A_KEY_1 ){
            isPitching = 1;
            ballSpeedX = 0;
            ballSpeedX2 = 0;  // 変化球の時に使用
            ballSpeedY = 3;
        }

        if ( isPitching == 0 && SG_getKeysPressed () == PORT_A_KEY_2 ){
            // カーブ
            isPitching = 1;
            ballSpeedX = -0.5f;
            ballSpeedX2 = 0.015f;  // 変化球の時に使用
            ballSpeedY = 2;
        }

        if ( isPitching == 1 ) {
            pitchingCount++;
            if ( pitchingCount > 40 ) {
                pitchingCount = 40;
            }
            pitcherTileAddress1 = 0x04 * ( pitchingCount / 10 );    // TODO 0x04が変更される可能性あり
            pitcherTileAddress2 = (4 * 5) + 0x04 * ( pitchingCount / 10 );    // TODO 4*5が変更される可能性あり
        }

        // ２PADの１ボタンを押したら、ボールを投げる
        if ( SG_getKeysPressed () == PORT_B_KEY_1 ){
            isBatting = 1;
        }

        if ( isBatting == 1 ) {
            battingCount++;
            if ( battingCount == 10 ) {
                // ボールの位置が一定の場所なら当たったことにする
                if ( 148 <= ballY && ballY <= 180 ) {
                    double radian = (164 - ballY) / 8;  // TODO ここは適当
                    ballSpeedX = sinf(radian) * 3;
                    ballSpeedX2 = 0;
                    ballSpeedY = -cosf(radian) * 3;
                }
            }
            if ( battingCount >= 25 ) {
                battingCount = 0;
                isBatting = 0;
                batterTileAddress1 = (4 * 5 * 2);              // TODO 変更される可能性あり
                batterTileAddress2 = (4 * 5 * 2) + ( 16 * 5 ); // TODO 変更される可能性あり
            }
            else {
                batterTileAddress1 = (4 * 5 * 2)              + 0x10 * ( battingCount / 5 );    // TODO 変更される可能性あり
                batterTileAddress2 = (4 * 5 * 2) + ( 16 * 5 ) + 0x10 * ( battingCount / 5 );    // TODO 変更される可能性あり
            }
        }

        // スプライトを表示する
        SG_initSprites ();

        // ボール
        if ( pitchingCount == 40 ) {
            SG_addSprite ((int)ballX, ballY, ballTileAddress1, SG_COLOR_BLACK);	// ボール
            SG_addSprite ((int)ballX, ballY, ballTileAddress2, SG_COLOR_WHITE);	// ボール(２色目)
            ballSpeedX += ballSpeedX2;
            ballX += ballSpeedX;
            ballY += ballSpeedY;
            if ( ballY >= 192 || ballY < 16 || 248 < ballX  || ballX < 16 ) {
                ballX = 256 / 2 - 16 / 2;
                ballY = 16;
                ballSpeedX = 0;
                ballSpeedY = 2;
                pitchingCount = 0;
                isPitching = 0;
                pitcherTileAddress1 = 0x00; // TODO 変わる可能性あり
                pitcherTileAddress2 = (4 * 5); // TODO 変わる可能性あり
            }
        }

        SG_addSprite (pitcherX  , pitcherY  , pitcherTileAddress1     , SG_COLOR_BLACK);	// ピッチャー
        SG_addSprite (pitcherX  , pitcherY  , pitcherTileAddress2     , SG_COLOR_WHITE);	// ピッチャー(２色目)
        SG_addSprite (batterX   , batterY   , batterTileAddress1 + 0x00, SG_COLOR_BLACK);	// バッター
        SG_addSprite (batterX   , batterY+16, batterTileAddress1 + 0x04, SG_COLOR_BLACK);	// バッター
        SG_addSprite (batterX+16, batterY   , batterTileAddress1 + 0x08, SG_COLOR_BLACK);	// バッター
        SG_addSprite (batterX+16, batterY+16, batterTileAddress1 + 0x0C, SG_COLOR_BLACK);	// バッター
        SG_addSprite (batterX   , batterY   , batterTileAddress2 + 0x00, SG_COLOR_WHITE);	// バッター(２色目)
        SG_addSprite (batterX   , batterY+16, batterTileAddress2 + 0x04, SG_COLOR_WHITE);	// バッター(２色目)
        SG_addSprite (batterX+16, batterY   , batterTileAddress2 + 0x08, SG_COLOR_WHITE);	// バッター(２色目)
        SG_addSprite (batterX+16, batterY+16, batterTileAddress2 + 0x0C, SG_COLOR_WHITE);	// バッター(２色目)
        
        SG_finalizeSprites ();
        SG_copySpritestoSAT ();

        // 次のVBlankが開始するまで待ちます
        SG_waitForVBlank ();
    }
}
