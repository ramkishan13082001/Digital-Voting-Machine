#include <xc.h>

#define _XTAL_FREQ 20000000

// LCD Function Prototypes
void command(unsigned char cmd);
void data(unsigned char dat);
void lcd_string(char *str);
void lcd_init();
void delay();
void buzzer();
int voteA = 0;
int voteB = 0;
int voteC = 0;
int voteD = 0;

void delay()
{
    int i, j;

    for (i = 0; i < 500; i++) {
        for (j = 0; j < 500; j++) {
        }
    }
}
void buzzer()
{
    RC0=1;
    delay();
    RC0=0;
}
void lcd_init()
{
    delay();

    command(0x38);
    command(0x80);
    command(0x06);
    command(0x0E);
    command(0x01);
}

void command(unsigned char cmd)
{
    LATD = cmd;

    RA0 = 0;
    RA1 = 1;

    delay();

    RA1 = 0;
}

void data(unsigned char dat)
{
    LATD = dat;

    RA0 = 1;
    RA1 = 1;

    delay();

    RA1 = 0;
}

void lcd_string(char *str)
{
    while (*str) {
        data(*str++);
    }
}

void main()
{
    char a, b, c, d;

    ADCON1 = 0x0F; // Make all ports digital

    TRISB = 0xFF;  // PORTB as Input (Buttons)
    TRISD = 0x00;  // PORTD as Output (LCD Data)
    TRISC0 = 0;
    TRISA0 = 0;    // RA0 as Output (LCD RS)
    TRISA1 = 0;    // RA1 as Output (LCD EN)

    lcd_init();

    lcd_string("DIGITAL VOTING");

    delay();

    command(0x01); // Clear screen

    while(1)
    {
        command(0x80);

        lcd_string("PRESS BUTTON");

        if(RB0 == 0)
        {
            voteA++;

            command(0x01);
             buzzer();
            lcd_string("VOTE TO A");

            delay();

            command(0x01);
        }

        else if(RB1 == 0)
        {
            voteB++;

            command(0x01);
            buzzer();
            lcd_string("VOTE TO B");

            delay();

            command(0x01);
        }

        else if(RB2 == 0)
        {
            voteC++;

            command(0x01);
             buzzer();
            lcd_string("VOTE TO C");

            delay();

            command(0x01);
        }

        else if(RB3 == 0)
        {
            voteD++;

            command(0x01);
           buzzer();
            lcd_string("VOTE TO D");

            delay();

            command(0x01);
        }

        else if(RB4 == 0) // Result Button
        {
            command(0x01);

            lcd_string("A=");
          
            a = voteA + 48;
            data(a);

            command(0xC0); // Second line

            lcd_string("B=");
           
            b = voteB + 48;
            data(b);

            delay();

            command(0x01);

            lcd_string("C=");

            c = voteC + 48;
            data(c);

            command(0xC0);

            lcd_string("D=");
           
            d = voteD + 48;
            data(d);

            delay();

            command(0x01);
        }
    }
}