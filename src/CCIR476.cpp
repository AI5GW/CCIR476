/*
 * CCIR476.cpp - CCIR476 encoder library for Arduino
 *
 * Copyright (C) 2022 Sebastian Westerhold (AI5GW) <sebastian@baltic-lab.com>
 * https://baltic-lab.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <CCIR476.h>

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__) || defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega16U4__)
#include <avr/pgmspace.h>
#endif

#include "Arduino.h"


/* Public Class Members */

CCIR476::CCIR476(void)
{

}

uint8_t CCIR476::Encode(char c)
{
	switch (c)
      {       
        // 'LTRS' 0x5A
        case 'A': { return 0x47; }  // 65 
        case 'B': { return 0x72; }
        case 'C': { return 0x1D; }
        case 'D': { return 0x53; }
        case 'E': { return 0x56; }
        case 'F': { return 0x1B; }
        case 'G': { return 0x35; }
        case 'H': { return 0x69; }
        case 'I': { return 0x4D; }
        case 'J': { return 0x17; }
        case 'K': { return 0x1E; }
        case 'L': { return 0x65; }
        case 'M': { return 0x39; }
        case 'N': { return 0x59; }
        case 'O': { return 0x71; }
        case 'P': { return 0x2D; }
        case 'Q': { return 0x2E; }
        case 'R': { return 0x55; }
        case 'S': { return 0x4B; }
        case 'T': { return 0x74; }
        case 'U': { return 0x4E; }
        case 'V': { return 0x3C; }
        case 'W': { return 0x27; }
        case 'X': { return 0x3A; }
        case 'Y': { return 0x2B; }
        case 'Z': { return 0x63; }  // 90

        case 13: { return 0x78; }   // CR
        case 10: { return 0x6C; }   // LF
        case 32: { return 0x5C; }   // SP

        // 'FIGS' 0x36
        case '0': { return 0x2D; }
        case '1': { return 0x2E; }
        case '2': { return 0x27; }
        case '3': { return 0x56; }
        case '4': { return 0x55; }
        case '5': { return 0x74; }
        case '6': { return 0x2B; }
        case '7': { return 0x4E; }
        case '8': { return 0x4D; }
        case '9': { return 0x71; }                 
        case '\'': { return 0x17; }      
        case '!': { return 0x1B; }
        case ':': { return 0x1D; }
        case '(': { return 0x1E; }
        case '&': { return 0x35; }
        case '.': { return 0x39; }
        case '/': { return 0x3A; }
        case '=': { return 0x3C; }
        case '-': { return 0x47; }
        case '$': { return 0x53; }
        case ',': { return 0x59; }
        case '+': { return 0x63; }
        case ')': { return 0x65; }
        case '#': { return 0x69; }
        case '?': { return 0x72; }

        default: { return 0x00; }
      }    
}

char CCIR476::Decode(uint8_t CCIR, bool LTTR)
{

      if (CCIR == 0x78) { return (char)13; }   // CR
      if (CCIR == 0x6C) { return (char)10; }   // LF
      if (CCIR == 0x5C) { return (char)32; }   // SP
      if (CCIR == 0x0F) { return (char)0; }   // ALPHA
      if (CCIR == 0x33) { return (char)0; }    // BETA
      if (CCIR == 0x66) { return (char)0; }     // REP
      if (CCIR == 0x5A) { return (char)0; }    // Mode = Letters
      if (CCIR == 0x36) { return (char)0; }     // Mode = Figures
      
      if (LTTR)
      {
        switch (CCIR)
        {                      
          case 0x47: { return 'A'; }  
          case 0x72: { return 'B'; }
          case 0x1D: { return 'C'; }
          case 0x53: { return 'D'; }
          case 0x56: { return 'E'; }
          case 0x1B: { return 'F'; }
          case 0x35: { return 'G'; }
          case 0x69: { return 'H'; }
          case 0x4D: { return 'I'; }
          case 0x17: { return 'J'; }
          case 0x1E: { return 'K'; }
          case 0x65: { return 'L'; }
          case 0x39: { return 'M'; }
          case 0x59: { return 'N'; }
          case 0x71: { return 'O'; }
          case 0x2D: { return 'P'; }
          case 0x2E: { return 'Q'; }
          case 0x55: { return 'R'; }
          case 0x4B: { return 'S'; }
          case 0x74: { return 'T'; }
          case 0x4E: { return 'U'; }
          case 0x3C: { return 'V'; }
          case 0x27: { return 'W'; }
          case 0x3A: { return 'X'; }
          case 0x2B: { return 'Y'; }
          case 0x63: { return 'Z'; }  
          default: { return (char)0; }
        }        
      }
      else
      {
        switch (CCIR)
        {             
          case 0x2D: { return '0'; }
          case 0x2E: { return '1'; }
          case 0x27: { return '2'; }
          case 0x56: { return '3'; }
          case 0x55: { return '4'; }
          case 0x74: { return '5'; }
          case 0x2B: { return '6'; }
          case 0x4E: { return '7'; }
          case 0x4D: { return '8'; }
          case 0x71: { return '9'; }                 
          case 0x17: { return '\''; }      
          case 0x1B: { return '!'; }
          case 0x1D: { return ':'; }
          case 0x1E: { return '('; }
          case 0x35: { return '&'; }
          case 0x39: { return '.'; }
          case 0x3A: { return '/'; }
          case 0x3C: { return '='; }
          case 0x47: { return '-'; }
          case 0x53: { return '$'; }
          case 0x59: { return ','; }
          case 0x63: { return '+'; }
          case 0x65: { return ')'; }
          case 0x69: { return '#'; }
          case 0x72: { return '?'; }
          default: { return (char)0; }
        }        
      }
}


bool CCIR476::isLetter(char c)
{
      if (((c == 10) || (c == 13) || (c == 32)) == false)
      {
        // test for letter:
        if ((c >= 65)&&(c <= 90))
        {
          return true;
        }
        else
        {
	  return false;
        }
      }
      else
	{
	return false;
	}
}