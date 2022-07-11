/*
 * CCIR476.h - CCIR476 encoder library for Arduino
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


#include "Arduino.h"

#include <stdint.h>

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__) || defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega16U4__)
#include <avr/pgmspace.h>
#endif


class CCIR476
{
public:
  CCIR476(void);
  uint8_t Encode(char);
  char Decode(uint8_t, bool);
  bool isLetter(char);

private:

};