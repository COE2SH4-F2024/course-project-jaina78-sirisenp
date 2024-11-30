#include "Player.h"

Player::Player(GameMechs *thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(objPos(5, 5, '*'));
    // more actions to be included
}

Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPos Player::getPlayerHead() const
{
    // return the reference to the playerPos arrray list
    return playerPosList->getHeadElement();
}

objPosArrayList *Player::getPlayerPos() const
{
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    int input = mainGameMechsRef->getInput();
    switch (input)
    {
    case 87:
    case 119: // w
        if (myDir != DOWN)
        {
            myDir = UP;
        }
        break;
    case 65:
    case 97: // a
        if (myDir != RIGHT)
        {
            myDir = LEFT;
        }
        break;
    case 83:
    case 115: // s
        if (myDir != UP)
        {
            myDir = DOWN;
        }
        break;
    case 68:
    case 100: // d
        if (myDir != LEFT)
        {
            myDir = RIGHT;
        }
        break;
    default:
        break;
    }
}

void Player::movePlayer(int boardWidth, int boardHeight)
{
    // Get current head position
    objPos head = playerPosList->getHeadElement();
    int newX = head.getObjPos().pos->x;
    int newY = head.getObjPos().pos->y;

    switch (myDir)
    {
    case Dir::UP:
        newY--;
        break;
    case Dir::DOWN:
        newY++;
        break;
    case Dir::LEFT:
        newX--;
        break;
    case Dir::RIGHT:
        newX++;
        break;
    default:
        break;
    }

    // Wrap around logic
    if (newX <= 0)
        newX = boardWidth - 2;
    if (newX >= boardWidth - 1)
        newX = 1;
    if (newY <= 0)
        newY = boardHeight - 2;
    if (newY >= boardHeight - 1)
        newY = 1;

    // Check if the new head position overlaps with food
    objPos food = mainGameMechsRef->getFoodPos(); // Current food position

    if (newX == food.getObjPos().pos->x && newY == food.getObjPos().pos->y)
    {

        playerPosList->insertHead(objPos(newX, newY, '*'));

        mainGameMechsRef->generateFood(head);

        mainGameMechsRef->incrementScore();

        return;
    }
    else
    {
        // Regular movement
        playerPosList->insertHead(objPos(newX, newY, '*'));
        playerPosList->removeTail();
    }
}

// More methods to be added