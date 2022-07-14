/*
 * NAVTEX_SIM_LOGIC_OUT.INO - 100 baud SITOR B FEC / NAVTEX Example
 *
 * Copyright (C) 2022 Sebastian Westerhold (AI5GW) <sebastian@baltic-lab.com>
 * Web (EN): https://baltic-lab.com
 * Web (DE): https://baltic-labor.de/
 * YouTube (EN): https://www.youtube.com/c/BalticLab
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */



 /****************************************** DESCRIPTION & USE  ******************************************
 * This sketch shows how to use the CCIR476 library to generate a valid 100 baud NAVTEX messages. The message contains proper synchronisation / phasing signals.
 * SITOR B specific foward error correction (FEC) for the transmitted message symbols is also implemented in this sketch. 
 * 
 * The encoded message will be available on digital Pin 2 (FSK_PIN) for connection to a signal generator. 
 * A logic '0' (space) represents the lower frequency, a logic '1' (mark) represents the higher of the two FSK frequencies. 
 * 
 * For test transmissions on the 518 kHz NAVTEX frequency, space (logic '0') corresponds to a frequency of 517.915 kHz while mark (logic '1') corresponds to a frequency of 518.085 kHz.
 * 
 * This was tested using a Siglent SDG 1032X signal generator utilizing the external FSK modulation functionality as transmitter. The message was received on a 'NAV4 Navtex' receiver.
 * 
 * The functions 'TransmitSpace()' and 'TransmitMark()' can be used to implement DDS-based transmit solutions. A Si5351A based version of this example sketch is also available.
 * 
 */


#include <CCIR476.h>
#include <EEPROM.h>

CCIR476 CCIR476;

int FSK_PIN = 2;


float CENTER_FREQ, SHIFT, MARK_FREQ, SPACE_FREQ;
byte SYMBOL_BUFFER_1, SYMBOL_BUFFER_2, SYMBOL_BUFFER_3;

void setup() 
{
  // Set the 
  pinMode(FSK_PIN, OUTPUT);    
}

void loop() 
{
            // ** Transmit NAVTEX message **
            SendNavtexTestMessage();

            // ** Do nothing. Comment out for continuously repeating NAVTEX message
            while(true);
} 


// ***** Function to send CCIR_ALPHA for T_SYNC milliseconds *****
void TransmitSync(int T_SYNC) 
{
      long T = millis() + T_SYNC;
      while (millis() <= T)
      {
        Transmit_SYMBOL(CCIR_ALPHA);       
      }   
}

// ***** Function to send CCIR_REP and CCIR_ALPHA for T_PHASING milliseconds *****
void TransmitPhasing(int T_PHASING) 
{
      long Tphasing = millis() + T_PHASING;    
      while (millis() <= Tphasing)
      {
        Transmit_SYMBOL(CCIR_REP);
        Transmit_SYMBOL(CCIR_ALPHA);       
      }   
}

// ***** Function to transmit 'space' (lower FSK tone) for BIT_TIME microseconds  *****
void TransmitSpace(int BIT_TIME) 
{
      long NOW = micros();
      long END = NOW + BIT_TIME;
      digitalWrite(FSK_PIN, LOW);
      do { NOW = micros(); } while (NOW < END);
}

// ***** Function to transmit 'mark' (higher FSK tone) for BIT_TIME microseconds  *****
void TransmitMark(int BIT_TIME) 
{
      long NOW = micros();
      long END = NOW + BIT_TIME;
      digitalWrite(FSK_PIN, HIGH);
      do { NOW = micros(); } while (NOW < END);
}

// ***** Function to transmit a single 7-bit CCIR476 encoded symbol *****
void Transmit_SYMBOL(byte SYMBOL) 
{
      for(int i=0; i<7; i++)
      {
        if ((SYMBOL >> i)&(0x01)) 
        {
          TransmitMark(10000); 
        } 
        else 
        {
          TransmitSpace(10000); 
        }
      }    
}

// ***** Function to transmit CCIR476 coded symbols utilizing SITOR-B type forward-error-correction (FEC) *****
void SITOR_Transmit_FEC(byte SYM) 
{      
      Transmit_SYMBOL(SYMBOL_BUFFER_1);
      SYMBOL_BUFFER_1 = SYMBOL_BUFFER_2;
      SYMBOL_BUFFER_2 = SYMBOL_BUFFER_3;
      SYMBOL_BUFFER_3 = SYM;  
      Transmit_SYMBOL(SYMBOL_BUFFER_3);  
}

// ***** Function to transmit supported ASCII characters. Handles the CCIR476 encoding automatically sends mode switch control symbols *****
void TransmitChar(char c) 
{
      byte encoded = CCIR476.Encode(c);
      if (encoded == 0) return;

      // Detect letters / figures mode changes and send CCIR_LETTERS or CCIR_FIGURES control symbols if necessary 
      if (CCIR476.ModeChanged())
      {
          if (CCIR476.getMode())
          {
            SITOR_Transmit_FEC(CCIR_LETTERS);
          }
          else 
          {
            SITOR_Transmit_FEC(CCIR_FIGURES);
          }
      }  

      // Transmit CCIR476 coded symbol
      SITOR_Transmit_FEC(encoded);
    }

// ***** Function to pass strings to TransmitChar() *****
void TransmitString(char str[]) 
{
      int pos = 0; 
      char c = str[pos];
      do {
        TransmitChar(c);
        pos++;
        c = str[pos];
      }
      while (c > 0);
}


// ***** Function to send a valid, CCIR476 encoded NAVTEX message including synchronization, header and end of message signaling *****
void SendNavtexTestMessage() 
{

        // *** Transmit CCIR_ALPHA for 5 second. More than 10 Seconds is recommended, but 5 (and even lower) works for me.
        TransmitSync(5000);

        // *** Transmit CCIR_REP and CCIR_ALPHA for 3 seconds
        TransmitPhasing(3000);

        /// *** Send ZCZC Header  *** //
        SYMBOL_BUFFER_1 = CCIR476.Encode('Z');
        Transmit_SYMBOL(SYMBOL_BUFFER_1);   
        Transmit_SYMBOL(CCIR_ALPHA);
        SYMBOL_BUFFER_2 = CCIR476.Encode('C');
        Transmit_SYMBOL(SYMBOL_BUFFER_2);      
        Transmit_SYMBOL(CCIR_ALPHA);
        SYMBOL_BUFFER_3 = CCIR476.Encode('Z');
        Transmit_SYMBOL(SYMBOL_BUFFER_3);
        TransmitChar('C');
        
        // *** Send station Identifier 'S' ('DWD Pinneberg' in Navarea 1), message type 'A' (Navigational warnings) and message serial number '00' ***
        TransmitChar(' ');
        TransmitChar('J');
        TransmitChar('A');
        TransmitChar('0');
        TransmitChar('0');
        TransmitChar('\r');        
        TransmitChar('\n');     

        /// ******* SEND MESSAGE BODY **************** //
        TransmitString("000000 UC JUL 14\r\nNAVTEX TEST MESSAGE SENT FROM AN ARDUINO\r\n"); 

        // *** Signal End of Message (NNNN)
        TransmitString("NNNN\r\n");

        // *** Send phasing symbols for 3 seconds
        TransmitPhasing(3000);    
}

