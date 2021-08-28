#include "SGlib.h"
#include "PSGlib.h"

// コンバーターから出力されたソースコード
const unsigned char pitcher1TileData[] = {
        0x07,0x08,0x08,0x3F,0x0A,0x0A,0x04,0x0B, 0xE0,0x10,0x10,0xF0,0x50,0x50,0x20,0xD0, 0x10,0x34,0x4F,0x48,0x3B,0x0A,0x1E,0x1E, 0x08,0x2C,0xF2,0x12,0xDC,0x50,0x78,0x78,
};
#define pitcher1TileDataSize 32

const unsigned char pitcher1TileMapData[] = {
        0x01,0x02,0x03,0x04,
};
#define pitcher1TileMapDataSize 5
#define pitcher1TileMapDataWidth 2
#define pitcher1TileMapDataHeight 2

const unsigned char pitcher1ColourData[] = {
        0xF1,0xF1,0xF1,0xF1,0xF1,0xF1,0xF1,0xF1, 0xF1,0xF1,0xF1,0xF1,0xF1,0xF1,0xF1,0xF1, 0xF1,0xF1,0xF1,0xF1,0xF1,0xF1,0xF1,0xF1, 0xF1,0xF1,0xF1,0xF1,0xF1,0xF1,0xF1,0xF1,
};
#define pitcher1ColourDataSize 32
// コンバーターから出力されたソースコード　ここまで

void main (void)
{
    SG_setSpriteMode (SG_SPRITEMODE_LARGE);

    unsigned int tilefrom = 1;  // 開始位置

    // VRAM0000番台に書き込む
    // Tileの書き込み
    SG_loadTilePatterns(
        pitcher1TileData,
        tilefrom,
        pitcher1TileDataSize
    );
    SG_loadTilePatterns(
        pitcher1TileData,
        tilefrom+256,
        pitcher1TileDataSize
    );

    // VRAM2000番台に書き込む
    // 色の書き込み
    SG_loadTileColours(
        pitcher1ColourData,
        tilefrom,
        pitcher1ColourDataSize
    );
    SG_loadTileColours(
        pitcher1ColourData,
        tilefrom+256,
        pitcher1ColourDataSize
    );

    // VRAM1800番台に書き込む
    // タイルマップの書き込み
    unsigned char x = 0;
    unsigned char y = 0;
    SG_loadTileMapArea(
		x,
		y,
		pitcher1TileMapData,
		pitcher1TileMapDataWidth,
		pitcher1TileMapDataHeight
    );

    // ディスプレイをオンにします
    SG_displayOn(); 

    while (1) {
        // ゲームループ

        // 次のVBlankが開始するまで待ちます
        SG_waitForVBlank ();
    }
}
