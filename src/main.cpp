/************************************************
 * 
 * @author Yizheng Du
 * @author Thaomi Dao
 * 
 * @file main.cpp
 * 
 * a tamogatchi with various states of wellbeing and levels of care needed
 * 
 * @date 28 November 2025
 * 
 * @version 0.1.0
 ***********************************************/

// Debugging and Arduino libraries
#include "Arduino.h"
#include "TeensyDebug.h"
#pragma GCC optimize("O0")

// Project Specific Libraries
#include <animations.h>

/**
 * Prototypes
 */
void stateMachine()
{
}

/**
 * Setup and Loop
 */
void setup()
{
  debug.begin(SerialUSB1);
  halt_cpu();
}

void loop()
{
  // check for flags
  // call state machine
}

/**
 * Interupts
 */
//timer interrupt
//button interrupt