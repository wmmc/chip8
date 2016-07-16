#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "cpu.h"

void init_cpu(struct cpu* cpu)
{
  memset( cpu->memory, 0, sizeof(cpu->memory) );
  memset( cpu->V, 0, sizeof(cpu->V) );
  memset( cpu->stack, 0, sizeof(cpu->stack) );
  memset( cpu->graphics, 0, sizeof(cpu->graphics) );
  memset( cpu->keyboard, 0, sizeof(cpu->keyboard) );
  cpu->I = 0;
  cpu->pc = (uint8_t)0x2000;
  cpu->delay_timer = 0;
  cpu->sound_timer = 0;
  uint8_t fonts[80] = { 0xF0, 0x90, 0x90, 0x90, 0xF0, //0
                        0x20, 0x60, 0x20, 0x20, 0x70, //1
                        0xF0, 0x10, 0xF0, 0x80, 0xF0, //2
                        0xF0, 0x10, 0xF0, 0x10, 0xF0, //3
                        0x90, 0x90, 0xF0, 0x10, 0x10, //4
                        0xF0, 0x80, 0xF0, 0x10, 0xF0, //5
                        0xF0, 0x80, 0xF0, 0x90, 0xF0, //6
                        0xF0, 0x10, 0x20, 0x40, 0x40, //7
                        0xF0, 0x90, 0xF0, 0x90, 0xF0, //8
                        0xF0, 0x90, 0xF0, 0x10, 0xF0, //9
                        0xF0, 0x90, 0xF0, 0x90, 0x90, //A
                        0xE0, 0x90, 0xE0, 0x90, 0xE0, //B
                        0xF0, 0x80, 0x80, 0x80, 0xF0, //C
                        0xE0, 0x90, 0x90, 0x90, 0xE0, //D
                        0xF0, 0x80, 0xF0, 0x80, 0xF0, //E
                        0xF0, 0x80, 0xF0, 0x80, 0x80  //F
  };
  memcpy(cpu->memory, fonts, sizeof(fonts) * sizeof(fonts[0]));
}

/* 11111111       0xF0        <= example font for 0: 0xF0, 0x90, 0x90, 0x90, 0xF0 */
/* 10000001       0x90  */
/* 10000001       0x90  */
/* 10000001       0x90  */
/* 11111111       0xF0  */




/* nnn or addr - A 12-bit value, the lowest 12 bits of the instruction */
/*   n or nibble - A 4-bit value, the lowest 4 bits of the instruction */
/*   x - A 4-bit value, the lower 4 bits of the high byte of the instruction */
/*   y - A 4-bit value, the upper 4 bits of the low byte of the instruction */
/*   kk or byte - An 8-bit value, the lowest 8 bits of the instruction */



void execute_opcode(uint16_t opcode, struct cpu* cpu)
{

  switch(opcode & 0xF000)
    {
    case(0x0000):
      switch(opcode)
        {

      /* 0nnn - SYS addr */
      /* Jump to a machine code routine at nnn. */

      /* This instruction is only used on the old computers on which Chip-8 was originally implemented. It is ignored by modern interpreters. */


      /* 00E0 - CLS */
      /* Clear the display. */
        case(0x00E0):
          memset(cpu->graphics, 0, sizeof(cpu->graphics));

      /* 00EE - RET */
      /* Return from a subroutine. */

      /* The interpreter sets the program counter to the address at the top of the stack, then subtracts 1 from the stack pointer. */

          }
    case(0x1000):
      {
      /* 1nnn - JP addr */
      /* Jump to location nnn. */
      /* The interpreter sets the program counter to nnn. */
      uint16_t address = opcode & 0x0FFF;
      cpu->pc = address;
      break;
      }
    case(0x2000):

      /* 2nnn - CALL addr */
      /* Call subroutine at nnn. */

      /* The interpreter increments the stack pointer, then puts the current PC on the top of the stack. The PC is then set to nnn. */
    case(0x3000):
      /* 3xkk - SE Vx, byte */
      /* Skip next instruction if Vx = kk. */
      /* The interpreter compares register Vx to kk, and if they are equal, increments the program counter by 2. */
    case(0x4000):
      /* 4xkk - SNE Vx, byte */
      /* Skip next instruction if Vx != kk. */
      /* The interpreter compares register Vx to kk, and if they are not equal, increments the program counter by 2. */
    case(0x5000):
      /* 5xy0 - SE Vx, Vy */
      /* Skip next instruction if Vx = Vy. */
      /* The interpreter compares register Vx to register Vy, and if they are equal, increments the program counter by 2. */
    case(0x6000):
      /* 6xkk - LD Vx, byte */
      /* Set Vx = kk. */
      /* The interpreter puts the value kk into register Vx. */
    case(0x7000):
      /* 7xkk - ADD Vx, byte */
      /* Set Vx = Vx + kk. */
      /* Adds the value kk to the value of register Vx, then stores the result in Vx. */
    case(0x8000):
      /* 8xy0 - LD Vx, Vy */
      /* Set Vx = Vy. */

      /* Stores the value of register Vy in register Vx. */


      /* 8xy1 - OR Vx, Vy */
      /* Set Vx = Vx OR Vy. */

      /* Performs a bitwise OR on the values of Vx and Vy, then stores the result in Vx. A bitwise OR compares the corrseponding bits from two values, and if either bit is 1, then the same bit in the result is also 1. Otherwise, it is 0. */


      /* 8xy2 - AND Vx, Vy */
      /* Set Vx = Vx AND Vy. */

      /* Performs a bitwise AND on the values of Vx and Vy, then stores the result in Vx. A bitwise AND compares the corrseponding bits from two values, and if both bits are 1, then the same bit in the result is also 1. Otherwise, it is 0. */


      /* 8xy3 - XOR Vx, Vy */
      /* Set Vx = Vx XOR Vy. */

      /* Performs a bitwise exclusive OR on the values of Vx and Vy, then stores the result in Vx. An exclusive OR compares the corrseponding bits from two values, and if the bits are not both the same, then the corresponding bit in the result is set to 1. Otherwise, it is 0. */


      /* 8xy4 - ADD Vx, Vy */
      /* Set Vx = Vx + Vy, set VF = carry. */

      /* The values of Vx and Vy are added together. If the result is greater than 8 bits (i.e., > 255,) VF is set to 1, otherwise 0. Only the lowest 8 bits of the result are kept, and stored in Vx. */


      /* 8xy5 - SUB Vx, Vy */
      /* Set Vx = Vx - Vy, set VF = NOT borrow. */

      /* If Vx > Vy, then VF is set to 1, otherwise 0. Then Vy is subtracted from Vx, and the results stored in Vx. */


      /* 8xy6 - SHR Vx {, Vy} */
      /* Set Vx = Vx SHR 1. */

      /* If the least-significant bit of Vx is 1, then VF is set to 1, otherwise 0. Then Vx is divided by 2. */


      /* 8xy7 - SUBN Vx, Vy */
      /* Set Vx = Vy - Vx, set VF = NOT borrow. */

      /* If Vy > Vx, then VF is set to 1, otherwise 0. Then Vx is subtracted from Vy, and the results stored in Vx. */


      /* 8xyE - SHL Vx {, Vy} */
      /* Set Vx = Vx SHL 1. */

      /* If the most-significant bit of Vx is 1, then VF is set to 1, otherwise to 0. Then Vx is multiplied by 2. */
    case(0x9000):
      /* 9xy0 - SNE Vx, Vy */
      /* Skip next instruction if Vx != Vy. */
      /* The values of Vx and Vy are compared, and if they are not equal, the program counter is increased by 2. */
    case(0xA000):
      /* Annn - LD I, addr */
      /* Set I = nnn. */

      /* The value of register I is set to nnn. */
    case(0xB000):
      /* Bnnn - JP V0, addr */
      /* Jump to location nnn + V0. */

      /* The program counter is set to nnn plus the value of V0. */
    case(0xC000):
      /* Cxkk - RND Vx, byte */
      /* Set Vx = random byte AND kk. */

      /* The interpreter generates a random number from 0 to 255, which is then ANDed with the value kk. The results are stored in Vx. See instruction 8xy2 for more information on AND. */
    case(0xD000):
      /* Dxyn - DRW Vx, Vy, nibble */
      /* Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision. */

      /* The interpreter reads n bytes from memory, starting at the address stored in I. These bytes are then displayed as sprites on screen at coordinates (Vx, Vy). Sprites are XORed onto the existing screen. If this causes any pixels to be erased, VF is set to 1, otherwise it is set to 0. If the sprite is positioned so part of it is outside the coordinates of the display, it wraps around to the opposite side of the screen. See instruction 8xy3 for more information on XOR, and section 2.4, Display, for more information on the Chip-8 screen and sprites. */


    case(0xE000):
      /* Ex9E - SKP Vx */
      /* Skip next instruction if key with the value of Vx is pressed. */

      /* Checks the keyboard, and if the key corresponding to the value of Vx is currently in the down position, PC is increased by 2. */


      /* ExA1 - SKNP Vx */
      /* Skip next instruction if key with the value of Vx is not pressed. */

      /* Checks the keyboard, and if the key corresponding to the value of Vx is currently in the up position, PC is increased by 2. */


    case(0xF000):
      /* Fx07 - LD Vx, DT */
      /* Set Vx = delay timer value. */

      /* The value of DT is placed into Vx. */


      /* Fx0A - LD Vx, K */
      /* Wait for a key press, store the value of the key in Vx. */

      /* All execution stops until a key is pressed, then the value of that key is stored in Vx. */


      /* Fx15 - LD DT, Vx */
      /* Set delay timer = Vx. */

      /* DT is set equal to the value of Vx. */


      /* Fx18 - LD ST, Vx */
      /* Set sound timer = Vx. */

      /* ST is set equal to the value of Vx. */


      /* Fx1E - ADD I, Vx */
      /* Set I = I + Vx. */

      /* The values of I and Vx are added, and the results are stored in I. */


      /* Fx29 - LD F, Vx */
      /* Set I = location of sprite for digit Vx. */

      /* The value of I is set to the location for the hexadecimal sprite corresponding to the value of Vx. See section 2.4, Display, for more information on the Chip-8 hexadecimal font. */


      /* Fx33 - LD B, Vx */
      /* Store BCD representation of Vx in memory locations I, I+1, and I+2. */

      /* The interpreter takes the decimal value of Vx, and places the hundreds digit in memory at location in I, the tens digit at location I+1, and the ones digit at location I+2. */


      /* Fx55 - LD [I], Vx */
      /* Store registers V0 through Vx in memory starting at location I. */

      /* The interpreter copies the values of registers V0 through Vx into memory, starting at the address in I. */


      /* Fx65 - LD Vx, [I] */
      /* Read registers V0 through Vx from memory starting at location I. */

      /* The interpreter reads values from memory starting at location I into registers V0 through Vx. */
    default:
      printf("Opcode not found. Soz mate.\n");
    }
}
