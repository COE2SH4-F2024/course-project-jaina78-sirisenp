#include "Player.h"

Player::Player(GameMechs* thisGMRef) {
  mainGameMechsRef = thisGMRef;
  myDir = STOP;
  playerPos = objPos(10, 5, '*');
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
  switch (mainGameMechsRef->getInput()) {
    case 87:
    case 119:  // w
      if (myDir != DOWN) {
        myDir = UP;
      }
      break;
    case 65:
    case 97:  // a
      if (myDir != RIGHT) {
        myDir = LEFT;
      }
      break;
    case 83:
    case 115:  // s
      if (myDir != UP) {
        myDir = DOWN;
      }
      break;
    case 68:
    case 100:  // d
      if (myDir != LEFT) {
        myDir = RIGHT;
      }
      break;
    default:
      break;
  }
}

void Player::movePlayer() {
  // PPA3 Finite State Machine logic
  int x = playerPos.getObjPos().pos->x;
  int y = playerPos.getObjPos().pos->y;

  switch (myDir) {
    case UP:
      y--;
      if (y < 1) {
        y = mainGameMechsRef->getBoardSizeY() - 2;
      }
      break;
    case LEFT:
      x--;
      if (x < 1) {
        x = mainGameMechsRef->getBoardSizeX() - 2;
      }
      break;
    case DOWN:
      y++;
      if (y > mainGameMechsRef->getBoardSizeY() - 2) {
        y = 1;
      }
      break;
    case RIGHT:
      x++;
      if (x > mainGameMechsRef->getBoardSizeX() - 2) {
        x = 1;
      }
      break;
    default:
      return;  // No movement if direction is STOP
  }

  // Update the player's position
  playerPos.setObjPos(x, y, playerPos.getSymbol());
}

// More methods to be added