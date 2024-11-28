#include <iostream>

#include "MacUILib.h"
#include "Player.h"
#include "objPos.h"

using namespace std;

#define DELAY_CONST 100000

#define HEIGHT 10
#define LENGTH 20

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

// Initialize the player object with objPos
objPos otherObject(3, 3,
                   '$');  // Another object at position (3, 3) with symbol '$'

Player* player = nullptr;
GameMechs* gameMechs = nullptr;

int main(void) {
  Initialize();

  while (exitFlag == false) {
    GetInput();
    RunLogic();
    DrawScreen();
    LoopDelay();
  }

  CleanUp();
}

void Initialize(void) {
  MacUILib_init();
  MacUILib_clearScreen();

  gameMechs = new GameMechs(LENGTH, HEIGHT);
  player = new Player(gameMechs);
  player->getPlayerPos().setObjPos(10, 5, '*');

  exitFlag = false;
}

void GetInput(void) {
  if (MacUILib_hasChar() == 1) {
    char input = MacUILib_getChar();
    gameMechs->setInput(input);
  }
}
void RunLogic(void) {
  player->updatePlayerDir();
  player->movePlayer();
  gameMechs->clearInput();
}

void DrawScreen(void) {
  MacUILib_clearScreen();

  // Iterate through the grid to draw the game board
  for (int y = 0; y < HEIGHT; y++)  // Loop through rows
  {
    for (int x = 0; x < LENGTH; x++)  // Loop through columns
    {
      // Print border characters
      if (y == 0 || y == HEIGHT - 1 || x == 0 || x == LENGTH - 1) {
        MacUILib_printf("#");  // Draw border
      }
      // Print player object at its position
      else if (x == player->getPlayerPos().getObjPos().pos->x &&
               y == player->getPlayerPos().getObjPos().pos->y) {
        MacUILib_printf("%c", player->getPlayerPos().getSymbol());
      }
      // Print another object at its position (e.g., $ object)
      else if (x == otherObject.getObjPos().pos->x &&
               y == otherObject.getObjPos().pos->y) {
        MacUILib_printf("%c", otherObject.getSymbol());
      } else {
        MacUILib_printf(" ");  // Empty space
      }
    }
    MacUILib_printf("\n");
  }
  MacUILib_printf("\n%d, %d", player->getPlayerPos().getObjPos().pos->x,
                  player->getPlayerPos().getObjPos().pos->y);
}

void LoopDelay(void) {
  MacUILib_Delay(DELAY_CONST);  // 0.1s delay
}

void CleanUp(void) {
  MacUILib_clearScreen();

  MacUILib_uninit();
}
