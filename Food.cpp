#include "Food.h"
#include <cstdlib> // For rand
#include <ctime>   // For seeding rand

// Constructor
Food::Food()
{
    foodBucket = new objPosArrayList(); // Initialize food bucket
}

// Destructor
Food::~Food()
{
    delete foodBucket;
}

// Generate multiple food: special and normal
void Food::generateFood(int numFoods, int boardX, int boardY, const objPosArrayList &blockOffList)
{

    // Clear existing food bucket
    while (foodBucket->getSize() > 0)
    {
        foodBucket->removeTail();
    }

    for (int i = 0; i < numFoods; ++i)
    {
        int x, y;
        bool overlap;

        do
        {
            // Avoid borders
            x = rand() % (boardX - 2) + 1;
            y = rand() % (boardY - 2) + 1;
            overlap = false;

            // Check if new position overlaps with any blocked positions
            for (int j = 0; j < blockOffList.getSize(); ++j)
            {
                objPos temp = blockOffList.getElement(j);
                if (temp.getObjPos().pos->x == x && temp.getObjPos().pos->y == y)
                {
                    overlap = true;
                    break;
                }
            }

            // Check if new position overlaps with existing food
            for (int k = 0; k < foodBucket->getSize(); ++k)
            {
                objPos temp = foodBucket->getElement(k);
                if (temp.getObjPos().pos->x == x && temp.getObjPos().pos->y == y)
                {
                    overlap = true;
                    break;
                }
            }
        } while (overlap);

        // Assign a symbol for the food
        char symbol = (rand() % 10 < 2) ? '&' : '^';  // 20% chance of being special food &
        foodBucket->insertHead(objPos(x, y, symbol)); // Add to bucket
    }
}

// Retrieve specific food position
objPos Food::getFood(int index) const
{
    return foodBucket->getElement(index);
}

// Get total number of food items in bucket
int Food::getBucketSize() const
{
    return foodBucket->getSize();
}

// Remove a food item at a specific index
void Food::removeFood(int index)
{
    // Shift Elements
    int bucketSize = foodBucket->getSize();
    if (index < 0 || index >= bucketSize)
    {
        return; // Index out of bounds
    }
    for (int i = index; i < bucketSize - 1; ++i)
    {
        foodBucket->getElement(i) = foodBucket->getElement(i + 1);
    }
    foodBucket->removeTail();
}
