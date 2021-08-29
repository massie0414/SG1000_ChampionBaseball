#include "SGlib.h"
#include "PSGlib.h"

// 背景
const unsigned char bgTileData[] = {
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
#define bgTileDataSize 8
const unsigned char bgTileMapData[] = {
        0x00
};
#define bgTileMapDataSize 1
#define bgTileMapDataWidth 1
#define bgTileMapDataHeight 1

const unsigned char bgColourData[] = {
        0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
};
#define bgColourDataSize 8
// 背景 ここまで

// ピッチャー
const unsigned char pitcher1TileData[] = {
        0x07,0x08,0x08,0x3F,0x0A,0x0A,0x04,0x0B,
        0x10,0x34,0x4F,0x48,0x3B,0x0A,0x1E,0x1E,
        0xE0,0x10,0x10,0xF0,0x50,0x50,0x20,0xD0,
        0x08,0x2C,0xF2,0x12,0xDC,0x50,0x78,0x78,
};
#define pitcher1TileDataSize 32
// ピッチャー ここまで

// バッター
const unsigned char batter1TileData[] = {
        0x00,0x00,0x01,0x01,0x01,0x01,0x00,0x00,    // 1
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    // 4
        0x00,0xC0,0x23,0x24,0x24,0x2F,0x97,0x97,    // 2
        0x93,0x51,0x52,0x54,0x79,0x4A,0x4C,0x38,    // 5

        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    // 7
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    // 0
        0x25,0x26,0x1A,0x02,0x02,0x07,0x07,0x01,    // 8
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    // 0

        0x00,0x00,0xF0,0x08,0x08,0xF8,0xF8,0xF8,    // 3
        0xF0,0xE0,0x10,0x08,0x08,0x08,0x48,0x88,    // 6
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    // 0
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    // 0

        0xF0,0x10,0x90,0x90,0x90,0x90,0xF0,0xF0,    // 9
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    // 0
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    // 0
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    // 0
};
#define batter1TileDataSize 8*16
// バッター ここまで

// コンバートテスト
const unsigned char convertTileData[] = {
        0x00,0x00,0x01,0x03,0x0F,0x1F,0x01,0x01, 0x01,0x01,0x01,0x01,0x1F,0x3F,0x00,0x00, 0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x80, 0x80,0x80,0x80,0x80,0xF8,0xFC,0x00,0x00,
};
#define convertTileDataSize 32
// コンバートテスト ここまで


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
    unsigned char batterX = 256 / 2 - 16 / 2;
    unsigned char batterY = 192 - 24;

    // VRAM3800番台に書き込む
    // スプライトの書き込み
    
    unsigned int spriteSize = 0;

    // ピッチャー 4バイト
    tilefrom = spriteSize;  // 開始位置
    spriteSize += 4;
    SG_loadSpritePatterns(
        pitcher1TileData,
        tilefrom,
        pitcher1TileDataSize
    );
    
    // バッター 16バイト
    tilefrom = spriteSize;  // 開始位置
    spriteSize += 16;
    SG_loadSpritePatterns(
        batter1TileData,
        tilefrom,
        batter1TileDataSize
    );

    // コンバートテスト 4バイト
    tilefrom = spriteSize;  // 開始位置
    spriteSize += 4;
    SG_loadSpritePatterns(
        convertTileData,
        tilefrom,
        convertTileDataSize
    );

    // ディスプレイをオンにします
    SG_displayOn(); 

    while (1) {
        // ゲームループ

        if ( SG_getKeysHeld () == PORT_A_KEY_LEFT ){
            pitcherX--;
        }
        if ( SG_getKeysHeld () == PORT_A_KEY_RIGHT ){
            pitcherX++;
        }

        if ( SG_getKeysHeld () == PORT_B_KEY_LEFT ){
            batterX--;
        }
        if ( SG_getKeysHeld () == PORT_B_KEY_RIGHT ){
            batterX++;
        }

        // スプライトを表示する
        SG_initSprites ();
        SG_addSprite (pitcherX  , pitcherY  , 0x00, SG_COLOR_WHITE);	// ピッチャー
        SG_addSprite (batterX   , batterY   , 0x04, SG_COLOR_WHITE);	// バッター
        SG_addSprite (batterX   , batterY+16, 0x08, SG_COLOR_WHITE);	// バッター
        SG_addSprite (batterX+16, batterY   , 0x0C, SG_COLOR_WHITE);	// バッター
        SG_addSprite (batterX+16, batterY+16, 0x10, SG_COLOR_WHITE);	// バッター
        SG_addSprite (100, 100, 0x14, SG_COLOR_WHITE);	// コンバートテスト
        SG_finalizeSprites ();
        SG_copySpritestoSAT ();

        // 次のVBlankが開始するまで待ちます
        SG_waitForVBlank ();
    }
}
