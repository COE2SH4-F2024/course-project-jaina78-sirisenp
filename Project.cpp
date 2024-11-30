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
  gameMechs->generateFood(player->getPlayerPos()->getHeadElement());
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
  player->movePlayer(LENGTH, HEIGHT);
  if (gameMechs->getInput() == 27)
  {
    gameMechs->setExitTrue();
  }
  gameMechs->clearInput();
}

void DrawScreen(void)
{
  MacUILib_clearScreen();

  // Draw the game board
  for (int y = 0; y < HEIGHT; y++)
  {
    for (int x = 0; x < LENGTH; x++)
    {
      if (y == 0 || y == HEIGHT - 1 || x == 0 || x == LENGTH - 1)
      {
        MacUILib_printf("#");
      }
      else
      {
        bool isPrinted = false;

        // Iterate through the positions in playerPosList
        objPosArrayList *playerPosList = player->getPlayerPos(); // Player positions
        for (int i = 0; i < playerPosList->getSize(); i++)
        {
          objPos currentBodyPart = playerPosList->getElement(i); // i-th body part
          int snakeX = currentBodyPart.getObjPos().pos->x;
          int snakeY = currentBodyPart.getObjPos().pos->y;

          // Check if position matches the current grid position
          if (x == snakeX && y == snakeY)
          {
            MacUILib_printf("%c", currentBodyPart.getSymbol()); // Snake body
            isPrinted = true;
            break;
          }
        }

        // If no snake body is found, print food
        if (!isPrinted && x == gameMechs->getFoodPos().getObjPos().pos->x &&
            y == gameMechs->getFoodPos().getObjPos().pos->y)
        {
          MacUILib_printf("%c", gameMechs->getFoodPos().getSymbol()); // Print food
        }

        // If no snake body or food, print an empty space
        else if (!isPrinted)
        {
          MacUILib_printf(" ");
        }
      }
    }
    MacUILib_printf("\n");
  }

  // Print score
  MacUILib_printf("Score: %d", gameMechs->getScore());
  MacUILib_printf("\n%d, %d, %c\n", player->getPlayerPos()->getElement(0).getObjPos().pos->x, // Head position
                  player->getPlayerPos()->getElement(0).getObjPos().pos->y,
                  player->getPlayerPos()->getElement(0).getSymbol()); // Head symbol

  MacUILib_printf("Press 'ESC' to exit");
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