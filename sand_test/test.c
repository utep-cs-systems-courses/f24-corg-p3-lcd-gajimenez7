#include <libTimer.h>
#include "libTimer.h"
#include "lcdutils.h"
#include "lcddraw.h"

void main(){

  configureClocks();
  lcd_init();
  enableWDTInterrupts();
  

  clearScreen(COLOR_GREEN);
  or_sr(0x18);
}

u_char width = screenWidth, height = screenHeight;
int col = screenWidth/2, row = 0;

int count = 0;

void
__interrupt_vec(WDT_VECTOR) WDT(){
  count++;
  if(count >= 250){
    drawPixel(col, row, COLOR_YELLOW);
    if(row < height){
      row++;
    }
    if(row == height){
      count = 0;
      row = 0;
    }
  }
}
