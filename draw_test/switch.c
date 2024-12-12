#include <msp430.h>

#include "switch.h"



void switch_init(){

  P2REN |= SWITCHES;

  P2IE |= SWITCHES;

  P2OUT |= SWITCHES;

}
