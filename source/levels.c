#include <unistd.h>
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

/*
void drawCell(int offx, int offy, int x1, int y1)
{
    for (int i = 0; i < 16; i++) {
         for (int x = offx; x < x1; x++)
         {
             for (int y = offy; y < y1; y++)
                 {
                    drawPixel(x,y, 3);
                 }
         }
    }
}*

void drawLadder(int offx, int offy, int y1)
{
    while(offy<y1)
    {
        drawRect(offx, offy, offx+32 , offy+32, 2, 2);
        offy = offy+32;
    }    
}

/*
void level1(int move)
{
    int dkXoff = 0;
    int dkYoff = 0;

// the original printf library won't work. You have to use uart_puts so that it prints to the serial output.
void printf(char *str) {
	uart_puts(str);
}

uart_init();
fb_init();
    drawBackground();

    offy = 720-64;
    dkXoff = offx;
    dkYoff = offy;
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
    

    if(move==0)
    {

        
    }
    if(move==1)
    {

    }
    if(move==2)
    {

    }
    if(move==3)
    {

    }
    if(move==4)
    {

    }
    if(move==5)
    {

    }
    if(move==6)
    {
        if(offx>0 && offx<1248)
        {
            dkXoff=dkXoff-32;
            myDrawImage(donkeyy.pixel_data, donkeyy.width, donkeyy.height, dkXoff, dkYoff);
        }
    }
    if(move==7)
    {
        if(offx>0 && offx<1248)
        {
            dkXoff=dkXoff+32;
            myDrawImage(donkeyy.pixel_data, donkeyy.width, donkeyy.height, dkXoff, dkYoff);
        }
    }
    if(move==8)
    {

    }
    if(move==9)
    {

    }
    if(move==10)
    {

    }
    if(move==11)
    {

    }

}*/
