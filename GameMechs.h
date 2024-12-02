#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <time.h>

#include <cstdlib>

#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

using namespace std;

class GameMechs {
 private:
  char input;
  bool exitFlag;
  bool loseFlag;
  int score;

  int boardSizeX;
  int boardSizeY;

  objPos food;
  Food* foodBucket;

 public:
  GameMechs();
  GameMechs(int boardX, int boardY);
  ~GameMechs();

  bool getExitFlagStatus() const;
  void setExitTrue();
  bool getLoseFlagStatus() const;
  void setLoseFlag();

  char getInput() const;
  void setInput(char this_input);
  void clearInput();

  int getBoardSizeX() const;
  int getBoardSizeY() const;

  int getScore() const;
  void incrementScore(bool isSpecialFood); // Score

  // More methods should be added here
    void generateFood(objPosArrayList& blockOffList);
    Food* getFoodBucket() const; // Access the food bucket
    objPos getFoodPos() const; // Add declaration for project.cpp

};

#endif