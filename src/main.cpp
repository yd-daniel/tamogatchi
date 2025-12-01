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
#pragma GCC optimize("O0") // for teensydebug, prevents compiler from hiding labels
#include <Bounce2.h>

// Project Specific Libraries
#include <animations.h>

// Defined Constants
#define BUTTON1_PIN 0
#define BUTTON2_PIN 1
#define BUTTON3_PIN 2
#define BUTTON4_PIN 3
#define BUTTON_PULLUP INPUT_PULLUP
#define DEBOUNCE_INTERVAL 5 // in ms

#define DEFAULT_STATE Satiated
#define DEFAULT_NEEDS 128
#define DEFAULT_LIGHTING true

/**
 * Global Variables and Enums
 */
typedef enum
{
  Satiated,
  Unfulfilled,
  Sleeping,
  Sick,
  Recovering,
  Dead
} state;

typedef struct
{
  state state;
  uint8_t food;
  uint8_t sleep;
  uint8_t hygiene;
  uint8_t fun;
  bool lighting;
} tamogatchiData;

Bounce2::Button button1 = Bounce2::Button();
Bounce2::Button button2 = Bounce2::Button();
Bounce2::Button button3 = Bounce2::Button();
Bounce2::Button button4 = Bounce2::Button();

static tamogatchiData tamogatchi = {
  DEFAULT_STATE,
  DEFAULT_NEEDS,
  DEFAULT_NEEDS,
  DEFAULT_NEEDS,
  DEFAULT_NEEDS,
  DEFAULT_LIGHTING,
};

/**
 * Helper Functions
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

  button1.attach(BUTTON1_PIN, BUTTON_PULLUP);
  button1.interval(DEBOUNCE_INTERVAL);
  button2.attach(BUTTON2_PIN, BUTTON_PULLUP);
  button2.interval(DEBOUNCE_INTERVAL);
  button3.attach(BUTTON3_PIN, BUTTON_PULLUP);
  button3.interval(DEBOUNCE_INTERVAL);
  button4.attach(BUTTON4_PIN, BUTTON_PULLUP);
  button4.interval(DEBOUNCE_INTERVAL);
}

void loop()
{
  button1.update();
  button2.update();
  button3.update();
  button4.update();
  // check for flags
  // call state machine
}

/**
 * Interupts
 */
// timer interrupt
