#include "GameMechs.h"

#include "MacUILib.h"
#include "Player.h"

GameMechs::GameMechs() {}

GameMechs::GameMechs(int boardX, int boardY) {
  boardSizeX = boardX;
  boardSizeY = boardY;
  score = 0;

  srand(time(nullptr));  // Random seed

  // Initial food position, no overlap with player
  // generateFood(objPos(0, 0, '*'));
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
void GameMechs::generateFood(objPosArrayList& blockOffList) {
  int x, y;

  do {
    x = rand() % (boardSizeX - 2) + 1;
    y = rand() % (boardSizeY - 2) + 1;

    bool overlap = false;
    for (int i = 0; i < blockOffList.getSize(); ++i) {
      objPos temp = blockOffList.getElement(i);
      if (temp.getObjPos().pos->x == x && temp.getObjPos().pos->y == y) {
        overlap = true;
        break;
      }
    }

    if (!overlap) {
      break;
    }
  } while (true);

  // Set the food's position
  food.setObjPos(x, y, '$');
}

objPos GameMechs::getFoodPos() const { return food; }