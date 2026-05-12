# 🗳️ Digital Voting Machine using PIC18F4580

## 📌 Project Overview

This project implements a **Digital Voting Machine** using the **PIC18F4580 Microcontroller** and a **16x2 LCD Display**.  
The system allows users to cast votes using push buttons, stores the vote count for each candidate, and displays the final results when the result button is pressed.

This project combines several important embedded system concepts into one complete application:

- GPIO Programming
- LCD Interfacing
- Push Button Interfacing
- Embedded Logic
- Polling Technique
- MPLAB XC8 Programming
- Proteus Simulation

---

# 🎯 Project Objective

The objective of this project is to design a simple electronic voting system that:

- Displays instructions on LCD
- Allows voting through push buttons
- Counts votes for multiple candidates
- Displays confirmation after each vote
- Shows final voting results using a result button

This project is ideal after learning:

- LCD interfacing
- Keypad/Button interfacing
- Timers
- Interrupts/Polling
- Embedded C Programming

---

# ⚙️ Components Required

| Component | Purpose |
|---|---|
| PIC18F4580 | Main controller |
| LCD 16x2 (LM016L) | Display messages |
| 4 Push Buttons | Candidate voting buttons |
| 1 Push Button | Result button |
| Buzzer | Vote confirmation |
| LEDs | Status indication |
| 20 MHz Crystal | System clock |
| 22pF Capacitors | Crystal stabilization |
| 10kΩ Resistors | Pull-up resistors |

---

# 🔍 Proteus Components Search Keywords

Use these exact names in Proteus:

```text
PIC18F4580
LM016L
BUTTON
CRYSTAL
CAP
BUZZER
RES
```

---

# 📁 Project Files

```text
README.md
newmain.c
Makefile
Proteus Project Files
Simulation Screenshot
```

---

# 📷 Project Screenshot

![Digital Voting Machine](Screenshot%20(2713).png)

---

# 🔌 Circuit Connections

## 🟢 LCD Connections

| LCD Pin | PIC18F4580 Connection |
|---|---|
| RS | RA0 |
| RW | GND |
| EN | RA1 |
| D0-D7 | PORTD |
| VDD | +5V |
| VSS | GND |

---

## 🔴 Button Connections

| Button | PIC Pin |
|---|---|
| Candidate A | RB0 |
| Candidate B | RB1 |
| Candidate C | RB2 |
| Candidate D | RB3 |
| Result Button | RB4 |

---

# ⚠️ Important Note About Buttons

The project uses **Active LOW Logic**.

This means:

- Normal State → Logic HIGH (`1`)
- Pressed State → Logic LOW (`0`)

Therefore, use:

- External **10kΩ pull-up resistors**
OR
- Internal pull-ups (if enabled)

Without pull-ups, button readings may become unstable.

---

# 🟡 Buzzer Connection

| Device | PIC Pin |
|---|---|
| Buzzer | RC0 |

The buzzer can be used as a vote confirmation indicator.

---

# 🟠 Crystal Oscillator Connection

| Crystal Pin | PIC Connection |
|---|---|
| Pin 1 | OSC1 |
| Pin 2 | OSC2 |

Use:

- 20 MHz Crystal
- Two 22pF capacitors connected to GND

---

# 💻 MPLAB X Project Creation

## Step 1: Create New Project

Open MPLAB X IDE and go to:

```text
File → New Project
```

---

## Step 2: Select Project Type

Choose:

```text
Microchip Embedded → Standalone Project
```

---

## Step 3: Select Device

Choose:

```text
PIC18F4580
```

---

## Step 4: Select Compiler

Choose:

```text
XC8 Compiler
```

---

## Step 5: Add Source File

Create a new source file:

```text
main.c
```

Paste the project code into this file.

---

# 🧠 Project Logic

The firmware performs the following operations:

1. Initializes LCD
2. Configures PORTB as input
3. Displays startup message
4. Waits for button press
5. Increments corresponding vote counter
6. Displays vote confirmation
7. Shows final result when RB4 is pressed

---

# 📄 Main Code

```c
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
    ADCON1 = 0x0F;

    TRISB = 0xFF;
    TRISD = 0x00;

    TRISA0 = 0;
    TRISA1 = 0;

    lcd_init();

    lcd_string("DIGITAL VOTING");

    delay();

    command(0x01);

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

        else if(RB4 == 0)
        {
            command(0x01);

            lcd_string("A=");
            data(voteA + 48);

            command(0xC0);

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
```

---

# 🧩 Code Explanation

## `TRISB = 0xFF;`

Configures PORTB as input for push buttons.

---

## `TRISD = 0x00;`

Configures PORTD as output for LCD data transfer.

---

## `if(RB0 == 0)`

Checks whether Candidate A button is pressed.

Since Active LOW logic is used:

- `0` → Pressed
- `1` → Not Pressed

---

## `voteA++;`

Increments vote count for Candidate A.

---

## `data(voteA + 48);`

Converts integer to ASCII.

Example:

```text
1 + 48 = ASCII '1'
```

---

## `command(0x01);`

Clears the LCD display.

---

# ▶️ How to Build the Project

Click the:

```text
Hammer Icon
```

in MPLAB X IDE.

The HEX file is generated automatically.

Generated path:

```text
dist/default/production
```

---

# 🧪 Proteus Simulation Steps

1. Open Proteus
2. Place all required components
3. Connect LCD and buttons
4. Load generated HEX file into PIC18F4580
5. Run simulation

---

# ✅ Expected Output

## Startup Screen

```text
DIGITAL VOTING
```

---

## Voting Screen

```text
PRESS BUTTON
```

---

## After Voting for Candidate A

```text
VOTE TO A
```

---

## Result Display

```text
A=2
B=1
```

Then:

```text
C=0
D=3
```

---

# 📚 Concepts Covered

- Embedded C Programming
- GPIO Interfacing
- LCD Interfacing
- Button Interfacing
- Polling Technique
- ASCII Conversion
- Embedded State Management
- PIC18F4580 Architecture

---

# 🚀 Future Improvements

You can improve this project by adding:

- EEPROM vote storage
- Password protection
- RTC timestamping
- Interrupt-based voting
- UART result transmission
- GSM result notification
- Fingerprint authentication
- IoT cloud monitoring

---

# 👨‍💻 Author

**Ramkishan**  
Embedded Systems & VLSI Enthusiast

---
