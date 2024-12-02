#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{

public:
  enum Dir
  {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    STOP
  }; // This is the direction state

  Player(GameMechs *thisGMRef);
  ~Player();

  void movePlayer(int boardWidth, int boardHeight);
  void updatePlayerDir();
  objPos getPlayerHead() const;
  objPosArrayList *getPlayerPos() const;

private:
  objPosArrayList *playerPosList; // Upgraded in iteration 3.
  enum Dir myDir;

  // Need a reference to the Main Game Mechanisms
  GameMechs *mainGameMechsRef;
};

#endif