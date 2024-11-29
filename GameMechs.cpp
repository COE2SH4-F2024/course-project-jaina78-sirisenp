#include "GameMechs.h"

#include "MacUILib.h"

GameMechs::GameMechs() {}

GameMechs::GameMechs(int boardX, int boardY)
{
  boardSizeX = boardX;
  boardSizeY = boardY;
  score = 0;

  srand(time(nullptr)); // Initialize random seed

  // Generate initial food position, ensuring it does not overlap with the player at (0, 0)
  generateFood(objPos(0, 0, '*'));
}

// do you need a destructor?
GameMechs::~GameMechs() {}

bool GameMechs::getExitFlagStatus() const { return exitFlag; }

bool GameMechs::getLoseFlagStatus() const { return loseFlag; }

char GameMechs::getInput() const { return input; }

int GameMechs::getScore() const { return score; }

void GameMechs::incrementScore() { score++; }

int GameMechs::getBoardSizeX() const { return boardSizeX; }

int GameMechs::getBoardSizeY() const { return boardSizeY; }

void GameMechs::setExitTrue() { exitFlag = true; }

void GameMechs::setLoseFlag() { exitFlag = true; }

void GameMechs::setInput(char this_input) { input = this_input; }

void GameMechs::clearInput() { input = 0; }

// More methods should be added here
void GameMechs::generateFood(objPos blockOff)
{
  int x, y;

  // Make sure food does not overlap with the blockOff pos
  do
  {
    x = rand() % (boardSizeX - 2) + 1; // Random x within board boundaries
    y = rand() % (boardSizeY - 2) + 1; // Random y within board boundaries
  } while (x == blockOff.getObjPos().pos->x && y == blockOff.getObjPos().pos->y);

  // Set the food position and symbol
  food.setObjPos(x, y, '$');
}

objPos GameMechs::getFoodPos() const
{
  return food;
}