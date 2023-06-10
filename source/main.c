/**
 * Name: Amandeep Kaur UCID: 30153923
 * Name: Venkata Sai Charan Mannem UCID: 30120547
 * This code builds a simple donkey kong game. The player is demonstrated as the monkey and will have to reach to banana. 
 * Between the way there is fire, which if the player touches, one life gets decreased and there is coin which increases the life.
 * There is a main screen followed by the four levels if the player chooses to play and a quit option that ends the game overall.
 * If the player reaches the end screen after playing the game, 
 * the end screen is displayed which gives the player the options to restart and go to the main screen or quit.
 * The code uses functions mentioned in the following lecture slides along with Tutorials in RPi in the course:
 * 1) The General Purpose Input/Output (GPIO) Interface on The Raspberry Pi by Jalal Kawash.
 * 2) Super Nintendo Entertainment System (SNES) Controller by Jalal Kawash.

 * NOTE: 
 * IT CAN TAKE UP TO 10 MINUTES WHILE LOADING PLEASE BE PATIENT.
 */

//The following is initialization of the various things that are used all over the code.
#include <unistd.h>
#include <stdio.h>
#include "gpio.h"
#include "uart.h"
#include <stdbool.h>
#include "fb.h"
#include "img1.h"
#include "dk1.h"
#include "dkong.h"
#include "coin.h"
#include "fire.h"
#include "home.h"
#include "levels.h"
#include "banana.h"
#include "arrow.h"
#include "ss.h"
#include "gameOver.h"
#include "life.h"
#include "zero.h"
#include "one.h"
#include "two.h"
#include "three.h"
#include "four.h"

#define GPIO_BASE 0xFE200000                
#define CLO_REG 0xFE003004

static unsigned *gpio = (unsigned*)GPIO_BASE;                                       //GPIO base
#define INP_GPIO(g) * (gpio+((g)/10)) &= ~(7<<(((g)%10)*3))                         //Setting the function of any pin p to input.
#define OUT_GPIO(g) * (gpio+((g)/10)) |= (1<<(((g)%10)*3))                          //Setting the function of any pin p to output.

#define CLK 11                  //Clock pin
#define LAT 9                   //Latch pin
#define DAT 10                  //Data pin


char* button_names[16] = {"B", "Y", "Select", "Start", "Joy-pad UP", "Joy-pad DOWN", "Joy-pad LEFT", "Joy-pad RIGHT", "A", "X", "Left", "Right", "Unknown", "Unknown", "Unknown", "Unknown"};
bool Buttonpressed[16]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
bool startGame = true;
bool endGame = false;
int dkXoff;
int dkYoff;
bool level1 = false;
bool level2 = false;
bool level3 = false;
bool level4 = false;
bool endScreen = false;
bool startScreen = false;
int arrowX = 0;
int arrowY = 0;
int lifes = 4;
int lifeX = 320;
int lifeY = 688;
char Score[3] = {'0','0','0'};
bool endScreenUp;
bool endScreenDown;
int check = 0;

//The following function draws the background cell when and where needed.
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
}


//The below function prints the input.
void Print_Message(char *str) {
    uart_puts(str);
}


//Initializing GPIO.
void Init_GPIO() {
    INP_GPIO(CLK);
    OUT_GPIO(CLK);
    INP_GPIO(LAT);
    OUT_GPIO(LAT);
    INP_GPIO(DAT);
}

//Writing to the latch pin.
void Write_Latch(int i) {
    if(i == 1) {
        (*GPSET0) = 1 << 9;
    } else {
        (*GPCLR0) = 1 << 9;
    }
}

//Writing to the clock pin.
void Write_Clock(int j) {
    if(j == 1) {
        (*GPSET0) = 1 << 11;
    } else {
        (*GPCLR0) = 1 << 11;
    }
}

//Waiting for the given amount of time.
void Wait(int k) {
    unsigned int *clock = (unsigned int *)CLO_REG;
    unsigned c = *clock + k;
    while(c > *clock);
}

//Reading from the pins.
int Read_Data() {
    int v;
    v = ((*GPLEV0) >> DAT) & 1;
    return v;
}

//Reading data from SNES controller.
void Read_SNES(int *buttons) {
    Write_Clock(1);             //Writing to the clock pin.
    Write_Latch(1);             //Writing to the latch pin.
    Wait(12);                   //Waiting for 12 microseconds.
    Write_Latch(0);             //Writing to the latch.

    int i = 0;
    while(i < 16) {
        Wait(6);
        Write_Clock(0);         // falling edge
        Wait(6);
        buttons[i] = Read_Data();
        Write_Clock(1);
        i++;
    }
}

//This function is used to give display of level 1.
void level_1()
{
    endScreen = false;

    level1 = true;
    lifes = 4;
    int offx = 32;
    int offy = 32;
    lifeX = 320;
    lifeY = 688;

    dkXoff = offx;
    dkYoff = offy;

    drawBackground();

    myDrawImage(dkong.pixel_data, dkong.width, dkong.height, offx, offy);
    
    drawBlock(0,0,1280,32);
    drawBlock(0,0,32,720);
    drawBlock(0,688,1280,720);
    drawBlock(1248,0,1280,720);

    myDrawImage(banana.pixel_data, banana.width,banana.height,1216,32);  

    myDrawImage(fire.pixel_data, fire.width, fire.height,288,128);
    myDrawImage(fire.pixel_data, fire.width, fire.height,800,128);
    myDrawImage(fire.pixel_data, fire.width, fire.height,256,384);
    myDrawImage(fire.pixel_data, fire.width, fire.height,768,384);

    myDrawImage(coin.pixel_data, coin.width, coin.height,128,448);
    myDrawImage(coin.pixel_data, coin.width, coin.height,1056,448);
    
    myDrawImage(life.pixel_data, life.width, life.height,128,688);
    myDrawImage(life.pixel_data, life.width, life.height,192,688);
    myDrawImage(life.pixel_data, life.width, life.height,256,688);
    myDrawImage(life.pixel_data, life.width, life.height,320,688);
}

//This function is used to give display of level 2.
void level_2()
{
    endScreen = false;

    level2 = true;
    lifes = 4;
    int offx = 64;
    int offy = 64;
    lifeX = 320;
    lifeY = 688;


    dkXoff = offx;
    dkYoff = offy;

    drawBackground();

    myDrawImage(dkong.pixel_data, dkong.width, dkong.height, offx, offy);
    
    drawBlock(0,0,1280,64);
    drawBlock(0,0,64,720);
    drawBlock(0,656,1280,720);
    drawBlock(1216,0,1280,720);

    myDrawImage(banana.pixel_data, banana.width,banana.height,1184,64);  

    myDrawImage(fire.pixel_data, fire.width, fire.height,288,128);
    myDrawImage(fire.pixel_data, fire.width, fire.height,800,128);
    myDrawImage(fire.pixel_data, fire.width, fire.height,256,384);
    myDrawImage(fire.pixel_data, fire.width, fire.height,768,384);

    myDrawImage(coin.pixel_data, coin.width, coin.height,128,448);
    myDrawImage(coin.pixel_data, coin.width, coin.height,1056,448);
    
    myDrawImage(life.pixel_data, life.width, life.height,128,688);
    myDrawImage(life.pixel_data, life.width, life.height,192,688);
    myDrawImage(life.pixel_data, life.width, life.height,256,688);
    myDrawImage(life.pixel_data, life.width, life.height,320,688);

}

//This method is used to give display of level 3.

void level_3()
{
    endScreen = false;

    level3 = true;
    lifes = 4;
    int offx = 96;
    int offy = 96;
    lifeX = 320;
    lifeY = 688;

    dkXoff = offx;
    dkYoff = offy;

    drawBackground();

    myDrawImage(dkong.pixel_data, dkong.width, dkong.height, offx, offy);
    
    drawBlock(0,0,1280,96);
    drawBlock(0,0,96,720);
    drawBlock(0,624,1280,720);
    drawBlock(1184,0,1280,720);

    myDrawImage(banana.pixel_data, banana.width,banana.height,1152,96);  

    myDrawImage(fire.pixel_data, fire.width, fire.height,288,128);
    myDrawImage(fire.pixel_data, fire.width, fire.height,800,128);
    myDrawImage(fire.pixel_data, fire.width, fire.height,256,384);
    myDrawImage(fire.pixel_data, fire.width, fire.height,768,384);

    myDrawImage(coin.pixel_data, coin.width, coin.height,128,448);
    myDrawImage(coin.pixel_data, coin.width, coin.height,1056,448);
    
    myDrawImage(life.pixel_data, life.width, life.height,128,688);
    myDrawImage(life.pixel_data, life.width, life.height,192,688);
    myDrawImage(life.pixel_data, life.width, life.height,256,688);
    myDrawImage(life.pixel_data, life.width, life.height,320,688);
}

//This method displays the level 4 in the game.
void level_4()
{
    endScreen = false;

    level4 = true;
    lifes = 4;
    int offx = 128;
    int offy = 128;
    lifeX = 320;
    lifeY = 688;

    dkXoff = offx;
    dkYoff = offy;

    drawBackground();

    myDrawImage(dkong.pixel_data, dkong.width, dkong.height, offx, offy);
    
    drawBlock(0,0,1280,128);
    drawBlock(0,0,128,720);
    drawBlock(0,592,1280,720);
    drawBlock(1152,0,1280,720);

    myDrawImage(banana.pixel_data, banana.width,banana.height,1120,128);  

    myDrawImage(fire.pixel_data, fire.width, fire.height,288,128);
    myDrawImage(fire.pixel_data, fire.width, fire.height,800,128);
    myDrawImage(fire.pixel_data, fire.width, fire.height,256,384);
    myDrawImage(fire.pixel_data, fire.width, fire.height,768,384);

    myDrawImage(coin.pixel_data, coin.width, coin.height,128,448);
    myDrawImage(coin.pixel_data, coin.width, coin.height,1056,448);
    
    myDrawImage(life.pixel_data, life.width, life.height,128,688);
    myDrawImage(life.pixel_data, life.width, life.height,192,688);
    myDrawImage(life.pixel_data, life.width, life.height,256,688);
    myDrawImage(life.pixel_data, life.width, life.height,320,688);
}

//This method draws the start screen.
void start_Screen()
{
    endScreen = false;

    startScreen = true;
    arrowX = 352;
    arrowY = 288;
    myDrawImage(ss.pixel_data, ss.width, ss.height,0,0);
    myDrawImage(arrow.pixel_data, arrow.width, arrow.height,352,288);

}

//This method displays the end Screen.
int end_Screen()
{
    endScreen = true;
   // check = 1;
    /*if(level1)
    {
        myDrawImage(one.pixel_data, one.width, one.height,384,288);
        myDrawImage(zero.pixel_data, zero.width, zero.height,416,288);
        myDrawImage(zero.pixel_data, zero.width, zero.height,448 ,288);

    }
    if(level2)
    {
        myDrawImage(two.pixel_data, two.width, two.height,384,288);
        myDrawImage(zero.pixel_data, zero.width, zero.height,416,288);
        myDrawImage(zero.pixel_data, zero.width, zero.height,448 ,288);
    }
    if(level3)
    {
        myDrawImage(three.pixel_data, three.width, three.height,384,288);
        myDrawImage(zero.pixel_data, zero.width, zero.height,448,288);
        myDrawImage(zero.pixel_data, zero.width, zero.height,352 ,288);
    }
    if(level4)
    {
        myDrawImage(four.pixel_data, four.width, four.height,384,288);
        myDrawImage(zero.pixel_data, zero.width, zero.height,416,288);
        myDrawImage(zero.pixel_data, zero.width, zero.height,448,288);
    }*/
    arrowX = 32;
    arrowY = 416;
    myDrawImage(gameOver.pixel_data, gameOver.width, gameOver.height,0,0);
    myDrawImage(arrow.pixel_data, arrow.width, arrow.height,32,416);
    endScreenUp = true;
    endScreenDown = false;

}

//The main function takes input from the user and moves the donkey kong accordingly.
int main() 
{
    uart_init();
    fb_init();
    int buttons[16] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    int prev_buttons[16] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

    endScreen = false;

    Init_GPIO();                                                      // Initializing GPIO.
    Print_Message("Created by Aman and Charan\n");                    // Printing the creators' names.
    Print_Message("Press a button on the SNES controller\n");         // Message for the user to press a button.

    start_Screen();
    void moveMonkey()
        {
            if(buttons[4]==0)
            {
                if(level1 && dkYoff==32)
                {return;}
                if(level2 && dkYoff==64)
                {return;}
                if(level3 && dkYoff==96)
                {return;}
                if(level4 && dkYoff==128)
                {return;}
                if(startScreen)
                {
                    arrowX = 352;
                    arrowY = 288;
                    myDrawImage(arrow.pixel_data, arrow.width, arrow.height,arrowX,arrowY);
                    drawCell(416,384,416+64,384+64);
                    return;
                }
                /*if(endScreen);
                {
                    arrowX = 32;
                    arrowY = 416;
                    myDrawImage(arrow.pixel_data, arrow.width, arrow.height,32, 416);
                    drawCell(32,480,32+64,480+64);
                    //endScreenUp = false;
                    return;
                    /*
                    if(endScreenUp)
                    {
                        myDrawImage(arrow.pixel_data, arrow.width, arrow.height,32, 416);
                        drawCell(64,480,128,480+96);
                        endScreenUp = false;
                        return;
                    }*
                    
                }*/
                if(level1 || level2 || level3 ||level4)
                {
                    myDrawImage(dkong.pixel_data, dkong.width, dkong.height, dkXoff, dkYoff-32);
                    drawCell(dkXoff,dkYoff,dkXoff+32,dkYoff+32);
                    dkYoff=dkYoff-32;
                }
            }

            if(buttons[5]==0)
            {
                if(dkYoff+32>=656 && level1)
                {return;}
                if(dkYoff+32>=624 && level2)
                {return;}
                if(dkYoff+32>=592 && level3)
                {return;}
                if(dkYoff+32>=560 && level4)
                {return;}
                if(startScreen)
                {
                    arrowX = 416;
                    arrowY = 384;
                    myDrawImage(arrow.pixel_data, arrow.width, arrow.height,arrowX,arrowY);
                    drawCell(352,288,352+64,288+64);
                    return;   
                }
                /*if(endScreen);
                {
                    arrowX = 32;
                    arrowY = 480;
                    myDrawImage(arrow.pixel_data, arrow.width, arrow.height,32, 480);
                    drawCell(32,416,32+64,416+64);
                    return;

                    /*
                    if(endScreenDown)
                    {;
                        myDrawImage(arrow.pixel_data, arrow.width, arrow.height,64, 480);
                        drawCell(64,416,64+64,416+96);
                        check = 1;
                        return;
                    }*
                    
                }*/

                if(level1 || level2 || level3 || level4)
                {
                    myDrawImage(dkong.pixel_data, dkong.width, dkong.height, dkXoff, dkYoff+32);
                    drawCell(dkXoff,dkYoff,dkXoff+32,dkYoff+32);
                    dkYoff = dkYoff+32;
                }

            }if(buttons[6]==0)
            {
                if(dkXoff==32 && level1)
                {return;}
                if(dkXoff==64 && level2)
                {return;}
                if(dkXoff==96 && level3)
                {return;}
                if(dkXoff==128 && level4)
                {return;}

                if(level1 || level2 || level3 || level4)
                {
                    myDrawImage(dkong.pixel_data, dkong.width, dkong.height, dkXoff-32, dkYoff);
                    drawCell(dkXoff,dkYoff,dkXoff+32,dkYoff+32);
                    dkXoff = dkXoff-32;
                }

                

            }if(buttons[7]==0)
            {
                if(dkXoff==1248-32 && level1)
                {return;}
                if(dkXoff==1184 && level2)
                {return;}
                if(dkXoff==1152 && level3)
                {return;}
                if(dkXoff==1120 && level4)
                {return;}

                if(level1 || level2 || level3 || level4)
                {
                    myDrawImage(dkong.pixel_data, dkong.width, dkong.height, dkXoff+32, dkYoff);
                    drawCell(dkXoff,dkYoff,dkXoff+32,dkYoff+32);
                    dkXoff = dkXoff+32;
                }
                
            }
            if(buttons[8]==0)
            {
                if(startScreen && arrowX == 352 && arrowY== 288)
                {
                    startScreen = false;
                    level1 = true;
                    level_1();
                    return;
                }
                if(startScreen && arrowX == 416 && arrowY== 384)
                {
                    endGame = true;
                    check = 0;
                    return;
                }
                if(endScreen);
                {
                    /* && arrowX == 32 && arrowY == 416
                    startScreen = true;
                    endScreen = false;
                    start_Screen();
                    return;*/
                    if(endScreenUp)
                    {
                        endScreen = false;
                        level1 = true;
                        check = 0;
                        start_Screen();
                        return;

                    }
                }
                if(endScreen);
                {
                    // && arrowX == 32 && arrowY ==480
                    /*endGame = true;
                    check = 0;
                    return;
                    */
                    if(endScreenDown)
                    {
                        endGame = true;
                        check = 0;
                        return;
                    }
                }
            }
            if(dkXoff==1248-32 && (dkYoff == 32) && level1==true)
            {
                level1 = false;
                level_2();
            }
            if(dkXoff==1184 && (dkYoff == 64) && level2==true)
            {
                level2 = false;
                level_3();
            }
            if(dkXoff==1152 && (dkYoff == 96) && level3==true)
            {
                level3 = false;
                level_4();
            }
            if(dkXoff==1120 && (dkYoff == 128) && level4==true)
            {
                level4 = false;
                end_Screen();
            }
            if(dkYoff==384)
            {
                if(dkXoff==256 || dkXoff==768)
                {
                    drawBlock(lifeX,lifeY,lifeX+32,lifeY+32);
                    lifeX = lifeX - 64;
                    lifes = lifes-1;
                }
            }
            if(dkYoff==128)
            {
                if(dkXoff==288 || dkXoff==800)
                {
                    drawBlock(lifeX,lifeY,lifeX+32,lifeY+32);
                    lifeX = lifeX - 64;
                    lifes = lifes-1;
                }
            }
            if(dkYoff==448)
            {
                if(dkXoff== 128|| dkXoff==1056)
                {
                    lifeX = lifeX+64;
                    lifes = lifes+1;
                    myDrawImage(life.pixel_data, life.width, life.height,lifeX,lifeY);
                }
            }
            if(lifes==0)
            {
               // endScreen = true;
                end_Screen();
            }

        } 

    while(1)
    {
        Read_SNES(buttons);  
        if(endGame==true)
        {
            break;
        }
        for (int i=0; i<16; i++)
        {
            if(buttons[i]==0 && prev_buttons[i]==1)
            {
                moveMonkey();
                prev_buttons[i] = buttons[i];
                for(int i=0; i<16;i++)
                {
                    prev_buttons[i] = buttons[i];
                }
            }
            prev_buttons[i] = buttons[i];
        }
    }

    drawBlock(0,0,1280,720);
}

