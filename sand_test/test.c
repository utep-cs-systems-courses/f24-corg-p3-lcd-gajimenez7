#include <msp430.h>
#include "../h/libTimer.h"
#include "../h/lcdutils.h"
#include "../h/lcddraw.h"

#define ROWS 40
#define COLS 30

#define SET_BIT(array, row, col) \
  (array[(row * COLS + col) / 8] |= (1 << ((row * COLS + col) % 8)))

#define CLEAR_BIT(array, row, col) \
  (array[(row * COLS + col) / 8] &= ~(1 << ((row * COLS + col) % 8)))

#define GET_BIT(array, row, col) \
  ((array[(row * COLS + col) / 8] >> ((row * COLS + col) % 8)) & 1)

// create a bitfield to hold particle positions
u_char sand_matrix[(ROWS * COLS + 7)/ 8] = {0};

void update_sand_matrix();
void insert_particle(u_char x, u_char y);
void draw_matrix();

int main(){
  configureClocks();
  lcd_init();
  enableWDTInterrupts();

  insert_particle(40, 30);
  
  clearScreen(COLOR_GREEN);
  or_sr(0x18);
}

// particle info
u_char width = screenWidth, height = screenHeight;
u_char particleWidth = 4, particleHeight = 4;

// move particles by checking each index and updating backwards (down up)
void update_sand_matrix(){
  u_char i, j;
  for(i = ROWS; i > 0; i--){
    for(j = COLS; j > 0; j--){
      // check if current bit is particle
      if(GET_BIT(sand_matrix, i, j)){
	  // ground check
	  if(i >= 0){
	    // move particle down
	    CLEAR_BIT(sand_matrix, i, j);
	    SET_BIT(sand_matrix, i+1, j);
	  }
	}
    }
  }
}
	
void draw_matrix(){
  u_char i, j;
  for(i = 0; i < ROWS; i++){
    for(j = 0; j < COLS; j++){
      if(GET_BIT(sand_matrix, i, j)){
	fillRectangle(i * 20, j * 15, particleWidth, particleHeight, COLOR_RED);
      }
    }
  }
}

void insert_particle(u_char x, u_char y){
  if(!GET_BIT(sand_matrix, x, y)){
    SET_BIT(sand_matrix, x, y);
  }
}
 
u_char count = 0;

void
__interrupt_vec(WDT_VECTOR) WDT(){
  count++;
  if(count >= 2){
    draw_matrix();
    update_sand_matrix();
    count = 0;
  }
}
