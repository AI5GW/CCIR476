CCIR476 Encoder Library for Arduino
==========================
This library offers an easy way to encode and decode CCIR476 symbols on your Arduino for SITOR, AMTOR and Navtex message encoding and decoding.

Library Installation
---------------------
The best way to install the library is via the Arduino Library Manager, which is available if you are using Arduino IDE version 1.6.2 or greater. To install it this way, simply go to the menu Sketch > Include Library > Manage Libraries..., and then in the search box at the upper-right, type "CCIR476". Click on the entry in the list below, then click on the provided "Install" button. By installing the library this way, you will always have notifications of future library updates, and can easily switch between library versions.

If you need to or would like to install the library the old-fashioned was, you can download a copy of the library in a ZIP file. Download a ZIP file of the library from the GitHub repository by using the "Download ZIP" button at the right of the main repository page. Extract the ZIP file, then rename the unzipped folder as "Si5351". Finally, open the Arduino IDE, select menu Sketch > Import Library... > Add Library..., and select the renamed folder that you just downloaded. Restart the IDE and you should have access to the new library.

Example and Functions
-------

here is a simple example named **CCIR476Example.ino** that is placed in your examples menu under the CCIR476 Arduino folder. The commentary below will analyze the available functions. 

First of all, the **CCIR476.h** header file need to be included and the CCIR476 class needs to be instantiated.

    #include <CCIR476.h>
    CCIR476 CCIR476;
    
 After instantiating the CCIR476 class, there are 3 functions available:
 
 - int CCIR476.Encode(char)
 - bool CCIR476.isLetter(char)
 - char CCIR476.Decode(int, bool mode)
 
 CCIR476.Encode() returns the CCIR476 encoded number corresponding to the character supplied in the function's argument. 
    
    CCIR = CCIR476.Encode('A')
    
 CCIR476.isLetter() returns a bolean 'true' if the character supplied through the function's argument is a letter. This function is necessary because CCIR476 allocates the same number twice in the corresponding look-up table; Once for a character and once for a figure. The switching between letters mode and figures mode is done by control symbols. 
    
    CCIR476.isLetter('A')
    
CCIR476.Decode() returns the decoded character. The first parameter passed to the function is the encoded symbol. The second parameter is true if the encoded symbol is a letter. If it is false, the figures look-up table will be used.
    
    CCIR476.Decode(CCIR476.Encode('Z'), CCIR476.isLetter('Z'))
    
    
    
