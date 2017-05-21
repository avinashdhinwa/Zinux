#include "keyboard.h"

#include "tty.h"

char buffer[BUFFER_SIZE];
int bufferPos = 0;

char scancodeTable[SCANCODE_COUNT];

/*
 * Initialize scancode table (for converting key code to ASCII)
 */
void KEYBOARD_init(void)
{
    int i;

    for(i = 0; i < SCANCODE_COUNT; i++)
        scancodeTable[i] = 0;

    /* Escape */
    scancodeTable[0x01] = 0x1B;

    /* Numbers */
    for(i = 1; i <= 9; i++)
        scancodeTable[i + 0x01] = i + '0';
    scancodeTable[0x0B] = '0';

    i = 0x0C;
    scancodeTable[i++] = '-';
    scancodeTable[i++] = '=';
    scancodeTable[i++] = '\b';
    scancodeTable[i++] = '\t';

    scancodeTable[i++] = 'Q';
    scancodeTable[i++] = 'W';
    scancodeTable[i++] = 'E';
    scancodeTable[i++] = 'R';
    scancodeTable[i++] = 'T';
    scancodeTable[i++] = 'Y';
    scancodeTable[i++] = 'U';
    scancodeTable[i++] = 'I';
    scancodeTable[i++] = 'O';
    scancodeTable[i++] = 'P';
    scancodeTable[i++] = '[';
    scancodeTable[i++] = ']';
    scancodeTable[i++] = '\r';
    i++;
    scancodeTable[i++] = 'A';
    scancodeTable[i++] = 'S';
    scancodeTable[i++] = 'D';
    scancodeTable[i++] = 'F';
    scancodeTable[i++] = 'G';
    scancodeTable[i++] = 'H';
    scancodeTable[i++] = 'J';
    scancodeTable[i++] = 'K';
    scancodeTable[i++] = 'L';
    scancodeTable[i++] = ';';
    scancodeTable[i++] = '\'';
    scancodeTable[i++] = '`';
    i++;
    scancodeTable[i++] = '\\';
    scancodeTable[i++] = 'Z';
    scancodeTable[i++] = 'X';
    scancodeTable[i++] = 'C';
    scancodeTable[i++] = 'V';
    scancodeTable[i++] = 'B';
    scancodeTable[i++] = 'N';
    scancodeTable[i++] = 'M';
    scancodeTable[i++] = ',';
    scancodeTable[i++] = '.';
    scancodeTable[i++] = '/';
    i++;
    scancodeTable[i++] = '*';
    i = 0x47;
    scancodeTable[i++] = '7';
    scancodeTable[i++] = '8';
    scancodeTable[i++] = '9';
    scancodeTable[i++] = '-';
    scancodeTable[i++] = '4';
    scancodeTable[i++] = '5';
    scancodeTable[i++] = '6';
    scancodeTable[i++] = '+';
    scancodeTable[i++] = '1';
    scancodeTable[i++] = '2';
    scancodeTable[i++] = '3';
    scancodeTable[i++] = '0';
    scancodeTable[i++] = '.';

    scancodeTable[0x39] = ' ';
}

void KEYBOARD_push(uint8_t key)
{
    if(bufferPos < BUFFER_SIZE)
        buffer[bufferPos++] = key;
}

uint8_t KEYBOARD_pop(void)
{
    return scancodeTable[buffer[bufferPos]];
}

void handleKeyPress(uint8_t key)
{
    buffer[bufferPos++] = key;

    char ch = scancodeTable[key];
    if(ch == '\r')
        ch = '\n';
    if((ch >= 'A' && ch <= 'Z') ||
        (ch >= '0' && ch <= '9') ||
        ch == '\n' || ch == ' ')
        TTY_putchar(ch);
}
