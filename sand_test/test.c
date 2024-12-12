#include <msp430.h>
#include "../h/libTimer.h"
#include "../h/lcdutils.h"
#include "../h/lcddraw.h"

#define ROWS 40
#define COLS 30

u_char sand_matrix[ROWS][COLS] = {0};

u_char i, j;

void update_sand_matrix();
void insert_particle(u_char x, u_char y);
void draw_matrix();

int main(){
  configureClocks();
  lcd_init();
  enableWDTInterrupts();

  insert_particle(0, 15);
  
  clearScreen(COLOR_GREEN);
  or_sr(0x18);
}

// particle info
u_char width = screenWidth, height = screenHeight;
u_char particleWidth = 4, particleHeight = 4;

// move particles by checking each index and updating backwards (down up)
void update_sand_matrix(){
  for(i = ROWS; i > 0; i++){
    for(j = COLS; j > 0; j++){
      //check if we are in a particle element
      if(sand_matrix[i][j] == 1){
	// ground level check
	if(i >= 1){
	  if(sand_matrix[i+1][j] == 0){
	    sand_matrix[i][j] = 0;
	    sand_matrix[i+1][j] = 1;
	  }
	}
      }
    }
  }
  i = 0, j = 0;
}

void draw_matrix(){
  for(i = 0; i < ROWS; i++){
    for(j = 0; j < COLS; j++){
      if(sand_matrix[i][j] == 1){
	fillRectangle(i * 40, j * 30, particleWidth, particleHeight, COLOR_RED);
      }
    }
  }
  i = 0, j = 0;
}

void insert_particle(u_char x, u_char y){
  if(sand_matrix[x][y] == 0){
    sand_matrix[x][y] = 1;
  }
}

u_char count = 0;

void
__interrupt_vec(WDT_VECTOR) WDT(){
  count++;
  if(count >= 0){
    draw_matrix();
    update_sand_matrix();
  }
  if(count >= 2){
    count = 0;
  }
}
