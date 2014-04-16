/*
(c) 2013 +++ Filip Stoklas, aka FipS, http://www.4FipS.com +++
THIS CODE IS FREE - LICENSED UNDER THE MIT LICENSE
ARTICLE URL: http://forums.4fips.com/viewtopic.php?f=3&t=1086

U8glib library URL: https://code.google.com/p/u8glib/
*/

#include "U8glib.h"

U8GLIB_PCD8544 u8g(13, 11, 10, 9, 8); // SPI Com: SCK = 13, MOSI = 11, CS = 10, A0 = 9, Reset = 8

void draw()
{
    u8g.setFont(u8g_font_unifont);
    u8g.drawStr(5, 22, "4FipS.com");
    u8g.drawStr(24, 35, "2013");
}

void setup()
{
    u8g.setColorIndex(1); // pixel on
}

void loop()
{
    u8g.firstPage();

    do
    {
        draw();
    }
    while(u8g.nextPage());

    delay(500);
}
