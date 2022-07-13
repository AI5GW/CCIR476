/*
 *  CCIR476 encoder library for Arduino Example
 *
 * Copyright (C) 2022 Sebastian Westerhold (AI5GW) <sebastian@baltic-lab.com>
 * Web (EN): https://baltic-lab.com
 * Web (DE): https://baltic-labor.de/
 * YouTube (EN): https://www.youtube.com/c/BalticLab
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

// Include Library
#include <CCIR476.h>

CCIR476 CCIR476;

int CCIR;

void setup() {
  Serial.begin(9600);

}

void loop() {

  // Encode the letter 'A' and print result
  CCIR = CCIR476.Encode('A');
  Serial.print("'A' CCIR476 encoded: ");
  Serial.println(CCIR);

  // Check if 'A' is a letter and print result (true)
  Serial.print("Is 'A' a letter? ");
  Serial.println(CCIR476.isLetter('A'));

  // Check if the letter / figures mode has changed. Will return '1' if changed (or on first call), '0' if not changed.
  Serial.print("CCIR476 Mode: ");
  Serial.println(CCIR476.ModeChanged());

  // Encode the letter '!' and print result
  CCIR = CCIR476.Encode('!');
  Serial.println("'!' CCIR 476 encoded: "+CCIR);

  // Check if '!' is a letter and print result (false)
  Serial.println(CCIR476.isLetter('!'));

  delay(1000);

  // Encode the letter 'Z', decode it again and print the result
  Serial.println(CCIR476.Decode(CCIR476.Encode('Z'), CCIR476.isLetter('Z')));
  delay(1000);

  // Encode the character '#', decode it again and print the result
  Serial.println(CCIR476.Decode(CCIR476.Encode('#'), CCIR476.isLetter('#')));
  delay(1000);

  // *** Detect mode automatically from control symbols ***
  Serial.println("Detect Mode automatically...");

  // Decode letters mode control symbol (0x5A)
  Serial.println("Set letters mode through 0x5A control symbol. ");
  CCIR476.Decode(0x5A);

  // Check if the letter / figures mode has changed. Will return '1' if changed (or on first call), '0' if not changed.
  Serial.print("CCIR476 Mode: ");
  Serial.println(CCIR476.ModeChanged());

  // Decode 0x47 ('A' in Letter mode, '-' in figures mode). Should return 'A'
  Serial.println(CCIR476.Decode(0x47));

  // Decode figures mode control symbol (0x36)
  Serial.println("Set figures mode through 0x36 control symbol. ");
  CCIR476.Decode(0x36);

  // Check if the letter / figures mode has changed. Will return '1' if changed (or on first call), '0' if not changed.
  Serial.print("CCIR476 Mode: ");
  Serial.println(CCIR476.ModeChanged());

  // Decode 0x47 ('A' in Letter mode, '-' in figures mode). Will now return '-'
  Serial.println(CCIR476.Decode(0x47));

  delay(1000);

}
