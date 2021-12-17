#include <conio.h>
#include <nes.h>
#include <stdio.h>

typedef unsigned char u8;

#define address(add) (*(u8 *)(add))

void set_background_color(u8 color)
{
    address(0x2006) = 0x3f;  
    address(0x2006) = 0x00;
    address(0x2007) = color;   
}

u8 read_joystick_1()
{
    u8 n=8,joy_state=0;
    address(0x4016)=01;
    address(0x4016)=00;
    while(n){
        joy_state=(joy_state<<1)|address(0x4016)&1;
        --n;
    }
    return joy_state;
}
 
void main()
{  
    unsigned char key;
    u8 index = 0x00;
    set_background_color(index);
    //gotoxy(1,1);
    //cprintf("bg color = 0x%02x",index);
   
    // color range: 0x00 to 0x3f. 
    while(1){       
        key=read_joystick_1();
        //gotoxy(1,1);
        //cprintf("key=%u   ",key);
        if(key == 0x80 || key == 0x40 || key == 0x01 || key == 0x02 || key == 0x04 || key == 0x08) {
            index = index + 1;
            if(index == 0x40)
                index = 0x00;
            set_background_color(index);
            //gotoxy(1,1);
            //cprintf("bg color = 0x%02x",index);
        }
        // make it slower to avoid color jump.
        waitvsync();
        waitvsync();
        waitvsync();
        waitvsync();
        waitvsync();
    }
}
