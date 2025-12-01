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
#define DEBOUNCE_INTERVAL 5 // in milliseconds

#define TIMER1_INTERVAL 100000 // in microseconds
#define DEFAULT_TICKER_VALUE 1 // in timer1 intervals
#define DEFAULT_FLAG_VALUE false

#define NEEDS_TICK_RATE 10 // in timer1 intervals
#define SICK_TICK_RATE 10  // in timer1 intervals
#define REST_TICK_RATE 10  // in timer1 intervals

#define DEFAULT_STATE Satiated
#define DEFAULT_NEEDS 128
#define DEFAULT_LIGHTING true

/****************************
 * Structs and Enums
 ***************************/
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
  uint ticksRemaining;
  uint resetTicks;
  bool flag;
} ticker;

typedef struct
{
  state state;
  uint8_t food;
  uint8_t sleep;
  uint8_t hygiene;
  uint8_t fun;
  uint8_t sickness;
  uint8_t restfullness;
  bool lighting;
} tamogatchiData;

/****************************
 * Global Variables and Peripherals
 ***************************/

Bounce2::Button button1 = Bounce2::Button();
Bounce2::Button button2 = Bounce2::Button();
Bounce2::Button button3 = Bounce2::Button();
Bounce2::Button button4 = Bounce2::Button();

IntervalTimer timer1;

volatile ticker needs = {
    DEFAULT_TICKER_VALUE,
    NEEDS_TICK_RATE,
    DEFAULT_FLAG_VALUE};
volatile ticker sick = {
    DEFAULT_TICKER_VALUE,
    SICK_TICK_RATE,
    DEFAULT_FLAG_VALUE};
volatile ticker rest = {
    DEFAULT_TICKER_VALUE,
    REST_TICK_RATE,
    DEFAULT_FLAG_VALUE};

static tamogatchiData tamogatchi = {
    DEFAULT_STATE,
    DEFAULT_NEEDS,
    DEFAULT_NEEDS,
    DEFAULT_NEEDS,
    DEFAULT_NEEDS,
    DEFAULT_LIGHTING,
};

/****************************
 * Helper Functions
 ***************************/
// sets flags for given ticker
void checkTicker(volatile ticker *ticker)
{
  if (ticker->ticksRemaining == 0)
  {
    ticker->ticksRemaining = ticker->resetTicks;
    ticker->flag = true;
  }
}

// timer interupt call
void updateFlags()
{
  checkTicker(&needs);
  checkTicker(&sick);
  checkTicker(&rest);
}

// tamogatchi state machine function, handles various states and edges
void stateMachine()
{
  switch (tamogatchi.state)
  {
  case Satiated:
    // timer_tick
    // if rand(1,100) <= 5 -> SICK
    // needs_tick
    // if needs < threshold -> UNFULLFILLED
    break;
  case Unfulfilled:
    // needs_tick
    // if hungry = 0 -> DEAD
    // else -> SICK
    // button_input
    // if !lights -> SATIATED
    // else -> SLEEP
    break;
  case Sleeping:
    // needs_tick
    // if needs < threshold -> UNFULLFILLED
    // button_input
    // if lights -> SATIATED
    break;
  case Sick:
    // needs_tick
    // if needs < threshold x2 -> DEAD
    // sick_tick
    // if sick = 0 -> DEAD
    // button_input
    // if medicine -> RECOVERING
    break;
  case Recovering:
    // needs_tick
    // if needs < threshold x2 -> DEAD
    // rest_tick
    // if rest = 0 and needs > threshold x2 -> SATIATED
    break;
  case Dead:
    break;
  }
}

/****************************
 * Setup and Loop
 ***************************/
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

  timer1.begin(updateFlags, TIMER1_INTERVAL);
}

void loop()
{
  button1.update();
  button2.update();
  button3.update();
  button4.update();
  // check for flags
  bool buttonChange = button1.changed() || button2.changed() ||
                      button3.changed() || button4.changed();
  bool tickerFlags = needs.flag || sick.flag || rest.flag;
  if (buttonChange || tickerFlags)
  {
    // call state machine
    stateMachine();
    // clear flags
    needs.flag = false;
    sick.flag = false;
    rest.flag = false;
  }
}