//
//  Macros.h
//  Strategy Game
//
//  Created by Jake Sanders on 7/26/16.
//  Copyright © 2016 Jake Sanders. All rights reserved.
//

#ifndef Macros_h
#define Macros_h

//To make the window fill the entire screen
#define FULL_SCREEN

// ***Resizeability does not work currently*** 
//To make the window resizable
#define RESIZEABLE

//To make the inset of the inner box for display bars the same on both x and y axes
#define EQUAL_BORDERED_DISPLAY_BARS

//To make the selected tile reset after movement
//#define RESET_SELECTED_TILE_AFTER_MOVEMENT

    //Various console outputs

//#define COMBAT_CONSOLE_OUTPUT
//#define SOCKET_CONSOLE_OUTPUT
//#define SCREEN_POSITION_CONSOLE_OUTPUT

    //Other
#define FONT_PATH "Resources/Palatino.ttc"
#define MAXIMUM_SOCKET_MESSAGE_SIZE 65535 //Arbitrary, but 65535 = 2^16 - 1
#define MAX_NUMBER_OF_CONNECTIONS 5 //5 is the max for most systems, so 5 should be set

#endif /* Macros_h */
