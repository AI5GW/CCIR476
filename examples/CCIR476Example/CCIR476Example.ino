/*
 *  CCIR476 encoder library for Arduino Example
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
  Serial.println(CCIR);

  // Check if 'A' is a letter and print result (true)
  Serial.println(CCIR476.isLetter('A'));

  // Encode the letter '!' and print result
  CCIR = CCIR476.Encode('!');
  Serial.println(CCIR);

  // Check if '!' is a letter and print result (false)
  Serial.println(CCIR476.isLetter('!'));

  delay(1000);

  // Encode the letter 'Z', decode it again and print the result
  Serial.println(CCIR476.Decode(CCIR476.Encode('Z'), CCIR476.isLetter('Z')));
  delay(1000);

  // Encode the character '#', decode it again and print the result
  Serial.println(CCIR476.Decode(CCIR476.Encode('#'), CCIR476.isLetter('#')));
  delay(1000);

}
