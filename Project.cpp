#include <iostream>

#include "MacUILib.h"
#include "Player.h"
#include "objPos.h"

using namespace std;

#define DELAY_CONST 100000

#define HEIGHT 10
#define LENGTH 20

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

Player *player = nullptr;
GameMechs *gameMechs = nullptr;

int main(void)
{
  Initialize();

  while (!gameMechs->getExitFlagStatus())
  {
    GetInput();
    RunLogic();
    DrawScreen();
    LoopDelay();
  }

  CleanUp();
}

void Initialize(void)
{
  MacUILib_init();
  MacUILib_clearScreen();

  gameMechs = new GameMechs(LENGTH, HEIGHT);
  player = new Player(gameMechs);
  // Initial food generation
  gameMechs->generateFood(player->getPlayerPos());
}

void GetInput(void)
{
  if (MacUILib_hasChar() == 1)
  {
    char input = MacUILib_getChar();
    gameMechs->setInput(input);
  }
}
void RunLogic(void)
{
  player->updatePlayerDir();
  player->movePlayer();
  if (gameMechs->getInput() == 27)
  {
    gameMechs->setExitTrue();
  }
  gameMechs->clearInput();
}

void DrawScreen(void)
{
  MacUILib_clearScreen();

  // Iterate through the grid to draw the game board
  for (int y = 0; y < HEIGHT; y++) // Loop through rows
  {
    for (int x = 0; x < LENGTH; x++) // Loop through columns
    {
      // Print border characters
      if (y == 0 || y == HEIGHT - 1 || x == 0 || x == LENGTH - 1)
      {
        MacUILib_printf("#"); // Draw border
      }
      // Print player object at its position
      else if (x == player->getPlayerPos().getObjPos().pos->x &&
               y == player->getPlayerPos().getObjPos().pos->y)
      {
        MacUILib_printf("%c", player->getPlayerPos().getSymbol());
      }
      // Print another object at its position (e.g., $ object)
      else if (x == gameMechs->getFoodPos().getObjPos().pos->x &&
               y == gameMechs->getFoodPos().getObjPos().pos->y)
      {
        MacUILib_printf("%c", gameMechs->getFoodPos().getSymbol());
      }
      else
      {
        MacUILib_printf(" "); // Empty space
      }
    }
    MacUILib_printf("\n");
  }
  MacUILib_printf("Score: %d", gameMechs->getScore());
  MacUILib_printf("\n%d, %d, %c\n", player->getPlayerPos().getObjPos().pos->x,
                  player->getPlayerPos().getObjPos().pos->y,
                  player->getPlayerPos().getSymbol());

  MacUILib_printf("Press 'Esc' to exit");
}

void LoopDelay(void)
{
  MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
  MacUILib_clearScreen();

  MacUILib_uninit();
}
