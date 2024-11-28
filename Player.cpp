#include "Player.h"

Player::Player(GameMechs* thisGMRef) {
  mainGameMechsRef = thisGMRef;
  myDir = STOP;

  playerPos.setObjPos(10, 5, '*');

  // more actions to be included
}

Player::~Player() {
  // delete any heap members here
}

objPos Player::getPlayerPos() const {
  // return the reference to the playerPos arrray list
  return playerPos;
}

void Player::updatePlayerDir() {
  // PPA3 input processing logic
}

void Player::movePlayer() {
  // PPA3 Finite State Machine logic
}

// More methods to be added