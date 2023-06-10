/*#include <unistd.h>
#include <stdio.h>
//#include <wiringPi.h>
#include "gpio.h"
#include "uart.h"
#include "fb.h"
#include "img1.h"
#include "dk1.h"
#include "donkeyy.h"
#include "coin.h"
#include "fire.h"
#include "home.h"
#include "kernel.h"
#include "stdbool.h"

#define GPIO_BASE 0xFE200000

int dx =1;
int dy= 1;
int offx = 0;
int offy = 0;

void drawBackground()
{
    for (int i = 0; i < 16; i++) {
         for (int x = 0; x < 1280; x++)
         {
             for (int y = 0; y < 720; y++)
                 {
                     drawPixel(x,y,3);
                 }
         }
    }
}

void drawBlock(int offx, int offy, int x1, int y1)
{
    for (int i = 0; i < 16; i++) {
         for (int x = offx; x < x1; x++)
         {
             for (int y = offy; y < y1; y++)
                 {
                    drawPixel(x,y, 6);
                 }
         }
    }
}
void drawLadder(int offx, int offy, int y1)
{
    while(offy<y1)
    {
        drawRect(offx, offy, offx+32 , offy+32, 2, 2);
        offy = offy+16;
    }    
}

void level1()
{
    drawBackground();

    offy = 720-64;
    myDrawImage(donkeyy.pixel_data, donkeyy.width, donkeyy.height, offx, offy);

    offy = 688;
    int y1 = 720;
    offx = 0;
    int x1 = 1280;

    drawBlock(offx, offy, x1, y1);

    offy = 464;
    y1 = 496;
    offx = 224;
    x1 = 1024;
    drawBlock(offx, offy, x1, y1);

    drawLadder(224,496,688);
    drawLadder(992,496,688);
    myDrawImage(coin.pixel_data, coin.width, coin.height, 640, 432);
    //myDrawImage(fire.pixel_data, fire.width, fire.height, 640, 656);
    
    int dx =1;
    int dy= 1;
    offx = 640;
    offy = 656;
    while(1) {
        if (offx < 128) {
            offx = 128;
            dx = 1;
        }
        else if (offx > 1120) {
            offx = 1120;
            dx = -1;
        }
        /*if (offy < 0) {
            offy = 0;
            dy = 1;
        }
        else if (offy > 300) {
            offy = 300;
            dy = -1;
        }*/
        
       /* for (int i =0; i <= fire.width; i++) {
            for (int j=0; j<= fire.height; j++) {
                myDrawPixel(i+offx,j+offy,0);
            }
        }   *------------
        offx += 30*dx;
       // offy += 10*dy;
        myDrawImage(fire.pixel_data, fire.width, fire.height, offx, offy);
    }
}

void level2()
{
    drawBackground();

    offy = 720-32;
    myDrawImage(donkeyy.pixel_data, donkeyy.width, donkeyy.height, offx, offy);

    offy = 592;
    int y1 = 624;
    offx = 160;
    int x1 = 1088;
    drawBlock(offx, offy, x1, y1);
    drawLadder(160,624,720);
    drawLadder(1056,624,720);

    drawBlock(160, 592, 1088, 624);

    drawLadder(288,496,592);
    drawLadder(448,496,592);
    drawLadder(800,496,592);
    drawLadder(928,496,592);

    drawBlock(288,464,480,496);
    drawBlock(800,464,960,496);

    drawLadder(448,368,464);
    drawLadder(800,368,464);
    drawBlock(448,336,832,368);

    myDrawImage(coin.pixel_data, coin.width, coin.height, 608, 304);
    //myDrawImage(fire.pixel_data, fire.width, fire.height, 640, 656);
    
    int dx =1;
    int dy= 1;
    offx = 96;
    offy = 688;
    while(1) {
        if (offx < 128) {
            offx = 128;
            dx = 1;
        }
        else if (offx > 1120) {
            offx = 1120;
            dx = -1;
        }
        offx += 30*dx;
       
        myDrawImage(fire.pixel_data, fire.width, fire.height, offx, offy);
    }

}

void level3()
{
        drawBackground();

    offy = 720-32;
    myDrawImage(donkeyy.pixel_data, donkeyy.width, donkeyy.height, offx, offy);

/*
    offy = 592;
    int y1 = 624;
    offx = 160;
    int x1 = 1088;
    drawBlock(offx, offy, x1, y1);
    *-----------

    drawLadder(160,592,720);
    drawLadder(1056,592,720);

    drawBlock(160, 560, 1088, 592);

    drawLadder(416,464,560);
    drawLadder(832,464,560);

    drawBlock(320,432,512,464);
    drawBlock(736,432,928,464);

    drawLadder(320,336,432);
    drawLadder(480,336,432);

    drawLadder(736,336,432);
    drawLadder(896,336,432);

    drawBlock(320,304,512,336);
    drawBlock(736,304,928,336);

    myDrawImage(coin.pixel_data, coin.width, coin.height, 416, 272);
    myDrawImage(coin.pixel_data, coin.width, coin.height, 832, 272);

    //myDrawImage(fire.pixel_data, fire.width, fire.height, 640, 656);
    
    int dx =1;
    int dy= 1;
    offx = 96;
    offy = 688;
    while(1) {
        if (offx < 128) {
            offx = 128;
            dx = 1;
        }
        else if (offx > 1120) {
            offx = 1120;
            dx = -1;
        }
        offx += 30*dx;
       
        myDrawImage(fire.pixel_data, fire.width, fire.height, offx, offy);
    }


    return 0;
}

void level4()
{

    drawBackground();

    offy = 720-32;
    myDrawImage(donkeyy.pixel_data, donkeyy.width, donkeyy.height, offx, offy);

/*
    offy = 592;
    int y1 = 624;
    offx = 160;
    int x1 = 1088;
    drawBlock(offx, offy, x1, y1);
    *-------------------------

    drawLadder(288,624,720);
    drawLadder(512,624,720);
    drawLadder(736,624,720);
    drawLadder(960,624,720);

    drawBlock(288, 592, 544, 624);
    drawBlock(736, 592, 992, 624);

    drawLadder(320,496,592);
    drawLadder(480,496,592);
    drawLadder(768,496,592);
    drawLadder(928,496,592);

    drawBlock(320,464,512,496);
    drawBlock(768,464,960,496);

    drawLadder(352,368,464);
    drawLadder(448,368,464);
    drawLadder(800,368,464);
    drawLadder(896,368,464);

    drawBlock(352,336,480,368);
    drawBlock(800,336,928,368);

    myDrawImage(coin.pixel_data, coin.width, coin.height, 416, 304);
    myDrawImage(coin.pixel_data, coin.width, coin.height, 864, 304);

    //myDrawImage(fire.pixel_data, fire.width, fire.height, 640, 656);
    
    int dx =1;
    int dy= 1;
    offx = 96;
    offy = 688;
    while(1) {
        if (offx < 128) {
            offx = 128;
            dx = 1;
        }
        else if (offx > 1120) {
            offx = 1120;
            dx = -1;
        }
        offx += 30*dx;

        myDrawImage(fire.pixel_data, fire.width, fire.height, offx, offy);
        myDrawImage(fire.pixel_data, fire.width, fire.height, offx+132, offy-96);
        myDrawImage(fire.pixel_data, fire.width, fire.height, offx+164, offy-132);
    }


    return 0;

}
void printOnScreen(char* toPrint, int len, int offx, int offy, int zoom)
{
    for(int i=0; i<len; i++)
    {
        drawCharZoomed(toPrint[i], offx,offy,0xf0,zoom);
        offx += 15;
    }

}
void drawStart()
{
    char* title[4] = {'P','L','A','Y'};
    int offx = 528;
    int offy = 288;
    for(int i=0; i<4; i++)
    {
        drawCharZoomed(title[i], offx,offy,0xf0,8);
        offx += 60;
    }
}

void mainScreen()
{
    offx = 0;
    offy = 0;
    uart_init(offx, offy);
    fb_init();
    myDrawImage(home.pixel_data, home.width, home.height,0, 0);
    drawStart();
}


int main()
{

// the original printf library won't work. You have to use uart_puts so that it prints to the serial output.
void printf(char *str) {
	uart_puts(str);
}

uart_init();
fb_init();

offx = 0;
offy = 0;

    drawBackground();

    offy = 720-64;
    myDrawImage(donkeyy.pixel_data, donkeyy.width, donkeyy.height, offx, offy);

    offy = 688;
    int y1 = 720;
    offx = 0;
    int x1 = 1280;

    drawBlock(offx, offy, x1, y1);

    offy = 464;
    y1 = 496;
    offx = 224;
    x1 = 1024;
    drawBlock(offx, offy, x1, y1);

    drawLadder(224,496,688);
    drawLadder(992,496,688);
    myDrawImage(coin.pixel_data, coin.width, coin.height, 640, 432);
    //myDrawImage(fire.pixel_data, fire.width, fire.height, 640, 656);
    
    int dx =1;
    int dy= 1;
    offx = 288;
    offy = 432;
    bool movingForward = true;
    
    while(1) {
        if (offx < 288) {
            offx = 288;
            dx = 1;
            movingForward = true;
        }
        else if (offx > 992) {
            offx = 992;
            dx = -1;
            movingForward = false;
        }
        else if(offx < 992 && movingForward ==true)
        {
            for (int i = 0; i < 16; i++) {
                for (int x = offx-32; x < offx; x++)
                {
                    for (int y = offy; y < offy+32; y++)
                    {
                        drawPixel(x,y,3);
                    }  
                }
            }
            myDrawImage(fire.pixel_data, fire.width, fire.height, offx, offy);
        }
        else if(offx >228 && movingForward ==false)
        {
            for (int i = 0; i < 16; i++) {
                for (int x = offx; x < offx+32; x++)
                {
                    for (int y = offy; y < offy+32; y++)
                    {
                        drawPixel(x,y,3);
                    }  
                }
            }
            myDrawImage(fire.pixel_data, fire.width, fire.height, offx-32, offy);

        }
        else if(offx == 288)
        {
            for (int i = 0; i < 16; i++) {
                for (int x = 256; x < 288; x++)
                {
                    for (int y = offy; y < offy+32; y++)
                    {
                        drawPixel(x,y,3);
                    }  
                }
            }
           // myDrawImage(fire.pixel_data, fire.width, fire.height, offx+32, offy);
        }
        else if(offx == 992)
        {
            for (int i = 0; i < 16; i++) {
                for (int x = 992; x < 1024; x++)
                {
                    for (int y = offy; y < offy+32; y++)
                    {
                        drawPixel(x,y,3);
                    }  
                }
            }
            //myDrawImage(fire.pixel_data, fire.width, fire.height, offx-32, offy);
        }
        offx += 32*dx;
    }

    return 0;

    
}
*/
