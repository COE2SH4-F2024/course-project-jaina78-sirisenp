#include "objPos.h"

objPos::objPos()
{
    pos = new Pos;
    pos->x = 0;
    pos->y = 0;
    symbol = 0; // NULL
}

// constructor
objPos::objPos(int xPos, int yPos, char sym)
{
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// Respect the rule of six / minimum four
// [TODO] Implement the missing special member functions to meet the minimum four rule

// Deconstructor
objPos::~objPos()
{
    delete pos; // Free the memory allocated for pos
}

// Copy constructor
objPos::objPos(const objPos &other)
{
    pos = new Pos; // Allocate new memory for pos
    pos->x = other.pos->x;
    pos->y = other.pos->y;
    symbol = other.symbol;
}

// Copy assignment operator
objPos &objPos::operator=(const objPos &other)
{
    if (this == &other)
    {
        return *this; // Handle self-assignment
    }

    // Delete old memory
    delete pos;

    // Allocate new memory and copy values
    pos = new Pos;
    pos->x = other.pos->x;
    pos->y = other.pos->y;
    symbol = other.symbol;

    return *this;
}

// Move constructor
objPos::objPos(objPos &&other) noexcept
{
    pos = other.pos; // Take ownership of the pointer
    symbol = other.symbol;

    other.pos = nullptr; // Set the other object's pointer to nullptr
    other.symbol = 0;
}

// Move assignment operator
objPos &objPos::operator=(objPos &&other) noexcept
{
    if (this == &other)
    {
        return *this; // Handle self-assignment
    }

    // Release any resources held by this object
    delete pos;

    // Steal resources from the other object
    pos = other.pos;
    symbol = other.symbol;

    other.pos = nullptr; // Set the other object's pointer to nullptr
    other.symbol = 0;

    return *this;
}

// Set Object Position
void objPos::setObjPos(objPos o)
{
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

void objPos::setObjPos(int xPos, int yPos, char sym)
{
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// Get object Position
objPos objPos::getObjPos() const
{
    objPos returnPos;
    returnPos.pos->x = pos->x;
    returnPos.pos->y = pos->y;
    returnPos.symbol = symbol;

    return returnPos;
}

// Get the symbol
char objPos::getSymbol() const
{
    return symbol;
}

// Equal position
bool objPos::isPosEqual(const objPos *refPos) const
{
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

// Symbol when equal position
char objPos::getSymbolIfPosEqual(const objPos *refPos) const
{
    if (isPosEqual(refPos))
        return symbol;
    else
        return 0;
}
