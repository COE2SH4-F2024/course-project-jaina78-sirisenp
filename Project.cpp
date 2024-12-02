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

// Global objects for the player and game mechanics
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

  // Create game mechanics and player objects
  gameMechs = new GameMechs(LENGTH, HEIGHT);
  player = new Player(gameMechs);

  // Initial food generation
  gameMechs->generateFood(*player->getPlayerPos());
}

void GetInput(void)
{
  // Check if a key has been pressed
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
  // ESC is exit key
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
  if (!gameMechs->getLoseFlagStatus())
  {
    for (int y = 0; y < HEIGHT; y++)
    {
      for (int x = 0; x < LENGTH; x++)
      {
        if (y == 0 || y == HEIGHT - 1 || x == 0 || x == LENGTH - 1)
        {
          MacUILib_printf("#"); // Print border
        }
        else
        {
          bool isPrinted = false;

          // Iterate through the positions for snake body
          objPosArrayList *playerPosList = player->getPlayerPos();
          for (int i = 0; i < playerPosList->getSize(); i++)
          {
            objPos currentBodyPart = playerPosList->getElement(i);
            int snakeX = currentBodyPart.getObjPos().pos->x;
            int snakeY = currentBodyPart.getObjPos().pos->y;

            if (x == snakeX && y == snakeY)
            {
              MacUILib_printf("%c", currentBodyPart.getSymbol()); // Print snake body
              isPrinted = true;
              break;
            }
          }

          // If no snake body part is found, check for food
          if (!isPrinted)
          {
            // Iterate through all the food items in foodBucket
            for (int i = 0; i < gameMechs->getFoodBucket()->getBucketSize(); i++)
            {
              objPos currentFood = gameMechs->getFoodBucket()->getFood(i);
              int foodX = currentFood.getObjPos().pos->x;
              int foodY = currentFood.getObjPos().pos->y;

              // Check if the current grid position matches any food position
              if (x == foodX && y == foodY)
              {
                MacUILib_printf("%c", currentFood.getSymbol()); // Print food symbol
                isPrinted = true;
                break; // Stop once food is printed at this position
              }
            }
          }

          // If no snake body part or food found, print an empty space
          if (!isPrinted)
          {
            MacUILib_printf(" ");
          }
        }
      }
      MacUILib_printf("\n");
    }

    // Display game instructions and score
    MacUILib_printf("Use the WASD keys to move the snake\nEat food (^) to grow OR special food (&) for +10 score\nAvoid bumping into yourself or you will lose!\n");
    MacUILib_printf("Score: %d\n", gameMechs->getScore());
  }
  else
  {
    MacUILib_printf("You lost!\nScore: %d\n", gameMechs->getScore());
  }

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