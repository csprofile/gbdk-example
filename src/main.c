#include <gb/gb.h>
#include "data.h"

void init();
void checkInput();
void updateSwitches();
void moveSprites();
void checkColision();


// The player array will hold the player's position as X ([0]) and Y ([1])
int player[2];
int enemy1[2];
int enemy2[2];
int lastDirectionUpDown;
int lastDirectionLeftRight;
int nextMoveDelayCount;
int moveDelay = 1;
int bgTest = 0;

void moveSprite(){
	// Move the sprite in the first movable sprite list (0)
	//  the the position of X (player[0]) and y (player[1])
	if (nextMoveDelayCount == 0){
		if (lastDirectionLeftRight != 0){
			player[0] = player[0] + lastDirectionLeftRight;
		}else if (lastDirectionUpDown != 0) {
			player[1] = player[1] + lastDirectionUpDown;
		}
		move_sprite(0, player[0], player[1]);
		nextMoveDelayCount = moveDelay;
	}else{
		nextMoveDelayCount --;
	}

	enemy1[0] = enemy1[0] + 1;
	move_sprite(1, enemy1[0], enemy1[1]);

	enemy2[1] = enemy2[1] + 1;
	move_sprite(2, enemy2[0], enemy2[1]);
}

void main() {

	init();
	
	while(1) {
		checkInput();				// Check for user input (and act on it)
		updateSwitches();			// Make sure the SHOW_SPRITES and SHOW_BKG switches are on each loop
		wait_vbl_done();			// Wait until VBLANK to avoid corrupting memory
	}
	
}

void init() {
	DISPLAY_ON;					  // Turn on the display
	set_bkg_data(0, 4, mapTiles); //Uses 4 tiles from mapTiles
	set_bkg_tiles(0,0,20,18,map); //20 x 18 = full map
	
	// Load the the 'sprites' tiles into sprite memory
	set_sprite_data(0, 2, spriteTiles);
	
	// Set the first movable sprite (0) to be the first tile in the sprite memory (0)
	set_sprite_tile(0,0); //POS 0 will have sprite 0 from the array
	set_sprite_tile(1,0); //POS 1 will have sprite 0 too (the same image)
	
	set_sprite_tile(2,0); //POS 1 will have sprite 0 too (the same image)
	move_sprite(2, 8, 16);

	player[0] = 80;
	player[1] = 72;
	enemy1[0] = 88;
	enemy1[1] = 80;
	enemy2[0] = 8;
	enemy2[1] = 16;

	lastDirectionUpDown = 0;
	lastDirectionLeftRight = 0;
	nextMoveDelayCount = moveDelay;
}

void updateSwitches() {
	
	HIDE_WIN;
	SHOW_SPRITES;
	SHOW_BKG;
	
}

void checkInput() {	
	// UP
	if (joypad() & J_UP) {
		lastDirectionUpDown = -1;
		lastDirectionLeftRight = 0;
	}

	// DOWN
	if (joypad() & J_DOWN) {
		lastDirectionUpDown = 1;
		lastDirectionLeftRight = 0;
	}

	// LEFT
	if (joypad() & J_LEFT) {
		lastDirectionUpDown = 0;
		lastDirectionLeftRight = -1;
	}	
	
	// RIGHT
	if (joypad() & J_RIGHT) {
		lastDirectionUpDown = 0;
		lastDirectionLeftRight = 1;
	}

	moveSprite();
}