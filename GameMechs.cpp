#include "GameMechs.h"

#include "MacUILib.h"
#include "Player.h"

GameMechs::GameMechs() {}

GameMechs::GameMechs(int boardX, int boardY)
{
  boardSizeX = boardX;
  boardSizeY = boardY;
  score = 0;

  srand(time(nullptr)); // Random seed

  foodBucket = new Food();
}

bool GameMechs::getExitFlagStatus() const { return exitFlag; }

bool GameMechs::getLoseFlagStatus() const { return loseFlag; }

char GameMechs::getInput() const { return input; }

int GameMechs::getScore() const { return score; }

void GameMechs::incrementScore(bool isSpecialFood)
{

  if (isSpecialFood)
  {
    score += 10; // Special food gives 10 points
  }
  else
  {
    score++; // Regular food gives 1 point
  }
}

int GameMechs::getBoardSizeX() const { return boardSizeX; }

int GameMechs::getBoardSizeY() const { return boardSizeY; }

void GameMechs::setExitTrue() { exitFlag = true; }

void GameMechs::setLoseFlag() { loseFlag = true; }

void GameMechs::setInput(char this_input) { input = this_input; }

void GameMechs::clearInput() { input = 0; }

// Generate food
void GameMechs::generateFood(objPosArrayList &blockOffList)
{
  foodBucket->generateFood(5, boardSizeX, boardSizeY, blockOffList); // Generate 5 foods
}

// Get the food bucket
Food *GameMechs::getFoodBucket() const
{
  return foodBucket;
}

objPos GameMechs::getFoodPos() const
{
  if (foodBucket->getBucketSize() > 0)
  {
    return foodBucket->getFood(0); // Get first food in bucket
  }
  // Return a default objPos if the bucket is empty
  return objPos(-1, -1, ' ');
}