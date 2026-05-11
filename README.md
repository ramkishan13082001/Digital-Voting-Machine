Project Objective
This is an excellent integrated embedded project because it combines several fundamental concepts into a single, cohesive application. It is perfect after learning basics like LCDs, Keypads, Interrupts, and Timers.

The system will:

Show candidates on the LCD
Allow voting using keypad/buttons
Count and tally votes
Show a success message upon voting
Display final results using a designated result button
Topic	Used For
GPIO	LEDs / Buzzer
LCD	Displaying status and menus
Keypad/Buttons	Capturing user vote input
Interrupts / Polling	Checking the Result Button
Embedded Logic	Voting counters and state management
⚙️
Components Required
Component	Purpose
PIC18F4580	Main controller
LCD 16x2	Display messages
4x Push Buttons	Vote buttons for candidates
1x Push Button	Result button
LEDs & Buzzer	Vote indication & confirmation
20 MHz Crystal	System clock
Resistors	Pull-up/pull-down (10kΩ)
💡
Proteus Simulation Search Keywords
If you are building this in Proteus, search for these exact component names: PIC18F4580, LM016L, BUTTON, CRYSTAL, CAP, BUZZER, RES.

🔌
Connection Guide
🟢 LCD Connections
LCD Pin	PIC Connection
RS	RA0
RW	GND
EN	RA1
D0-D7	PORTD
VDD	+5V
VSS	GND
🔴 Button Connections
Button	PIC Pin
Candidate A	RB0
Candidate B	RB1
Candidate C	RB2
Candidate D	RB3
Result Button	RB4
⚠️
Important: Button Logic
The code uses Active LOW logic. You MUST use 10k pull-up resistors on all button pins (or enable internal pull-ups if applicable) so they read HIGH normally, and LOW when pressed.

🟡 Buzzer & Crystal Connections
Connect the Buzzer to RC0. For the Crystal, connect Pin 1 to OSC1 and Pin 2 to OSC2. Use two 22pF capacitors connected to ground.

💻
MPLAB Project Creation
Open MPLAB X IDE.
Go to File → New Project.
Select Microchip Embedded → Standalone Project.
Select Device: Choose PIC18F4580.
Select Compiler: Choose XC8.
Create a new C source file named main.c.
🧠
Project Logic & Code
The project logic requires vote counters, button detection, LCD initialization, and formatted output generation. Paste the complete code below into your main.c.

C (XC8)
#include <xc.h>

#define _XTAL_FREQ 20000000

// LCD Function Prototypes
void command(unsigned char cmd);
void data(unsigned char dat);
void lcd_string(char *str);
void lcd_init();
void delay();

int voteA = 0;
int voteB = 0;
int voteC = 0;
int voteD = 0;

void main()
{
    ADCON1 = 0x0F; // Make all ports digital

    TRISB = 0xFF;  // PORTB as Input (Buttons)
    TRISD = 0x00;  // PORTD as Output (LCD Data)

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
            lcd_string("VOTE TO A");
            delay();
            command(0x01);
        }
        else if(RB1 == 0)
        {
            voteB++;
            command(0x01);
            lcd_string("VOTE TO B");
            delay();
            command(0x01);
        }
        else if(RB2 == 0)
        {
            voteC++;
            command(0x01);
            lcd_string("VOTE TO C");
            delay();
            command(0x01);
        }
        else if(RB3 == 0)
        {
            voteD++;
            command(0x01);
            lcd_string("VOTE TO D");
            delay();
            command(0x01);
        }
        else if(RB4 == 0) // Result Button
        {
            command(0x01);

            lcd_string("A=");
            data(voteA + 48); // Convert int to ASCII

            command(0xC0); // Second line

            lcd_string("B=");
            data(voteB + 48);

            delay();

            command(0x01);

            lcd_string("C=");
            data(voteC + 48);

            command(0xC0);

            lcd_string("D=");
            data(voteD + 48);

            delay();

            command(0x01);
        }
    }
}
🧩 Code Explanation
TRISB = 0xFF; Sets PORTB as inputs (buttons).
TRISD = 0x00; Sets PORTD as outputs (LCD Data).
if(RB0 == 0) Detects button press (Active LOW logic).
voteA++; Increments the vote counter.
data(voteA + 48); Converts the number to ASCII by adding 48. (Example: 1 + 48 = '1').
command(0x01); Clears the LCD display.
🛠️
How to Build & Simulate
Building the HEX File
Click the Hammer icon in MPLAB X to build the project.
The HEX file is generated automatically.
Path: dist/default/production
Proteus Setup & Expected Output
Place the PIC18F4580 and connect the LCD, Buttons, and Crystal.
Double-click the PIC, and load the generated .hex file.
Run the simulation. You will see DIGITAL VOTING at startup.
Pressing RB0 will show VOTE TO A.
Pressing RB4 will display the total results (e.g. A=2).
