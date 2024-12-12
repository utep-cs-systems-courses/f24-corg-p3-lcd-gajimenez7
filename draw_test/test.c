#include <msp430.h>
#include "../h/libTimer.h"
#include "../h/lcdutils.h"
#include "../h/lcddraw.h"

#include "buzzer.h"
#include "switch.h"

static u_char button1Down;
static u_char button2Down;
static u_char button3Down;

int main(){

  configureClocks();
  lcd_init();
  enableWDTInterrupts();

  switch_init();
  buzzer_init();
  
  clearScreen(COLOR_GREEN);
  or_sr(0x18);
}

void switch_interrupt_handler(){
  char p2val = P2IN;
  P2IES |= (p2val & SWITCHES);
  P2IES &= (p2val | ~SWITCHES);
  if(p2val & SW1){
    button1Down = 1;
  }
  if(p2val & SW2){
    button2Down = 1;
  }
  if(p2val & SW3){
    button3Down = 1;
  }
}

u_char width = screenWidth, height = screenHeight;
u_char col1 = screenWidth/2, col2 = (screenWidth/2) - 8, col3 = (screenWidth/2) + 8;
u_char row1 = 4, row2 = 4, row3 = 4;
u_char rectWidth = 4, rectHeight = 4;

int count_1 = 0, count_2 = 0, count_3;
int count2_1 = 0, count2_2 = 0, count2_3 = 0;

void grain1(){
  fillRectangle(col1, row1, rectWidth, rectHeight, COLOR_RED);
  if(row1 < height){
    if(row1 > 3){
      fillRectangle(col1, row1 - 3, rectWidth, rectHeight, COLOR_GREEN);
    }
    row1++;
    count_1 = 0;
  }
  if(row1 == height - (count2_1 * 3)){
    row1 = 0;
    count2_1++;
  }
  if(count2_1 * 3 >= height){
    count2_1 = 0;
  }
}

void grain2(){
  fillRectangle(col2, row2, rectWidth, rectHeight, COLOR_ORANGE);
  if(row2 < height){
    if(row2 > 3){
      fillRectangle(col2, row2 - 3, rectWidth, rectHeight, COLOR_GREEN);
    }
    row2++;
    count_2 = 0;
  }
  if(row2 == height - (count2_2 * 3)){
    row2 = 0;
    count2_2++;
  }
  if(count2_2 * 3 >= height){
    count2_2 = 0;
  }
}

void grain3(){
  fillRectangle(col3, row3, rectWidth, rectHeight, COLOR_BLUE);
  if(row3 < height){
    if(row3 > 3){
      fillRectangle(col3, row3 - 3, rectWidth, rectHeight, COLOR_GREEN);
    }
    row3++;
    count_3 = 0;
  }
  if(row3 == height - (count2_3 * 3)){
    row3 = 0;
    count2_3++;
  }
  if(count2_3 * 3 >= height){
    count2_3 = 0;
  }
}

void
__interrupt_vec(PORT2_VECTOR) Port_2(){
  if(P2IFG & SWITCHES){
    P2IFG &= ~SWITCHES;
    switch_interrupt_handler();
  }
}

void
__interrupt_vec(WDT_VECTOR) WDT(){
  count_1++;
  count_2++;
  count_3++;
  if(count_1 >= 1 && button1Down){
    grain1();
  }
  if(count_2 >= 2 && button2Down){
    grain2();
  }
  if(count_3 >= 3 && button3Down){
    grain3();
  }
}
