#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include "objPosArrayList.h"

class Food
{
private:
    objPosArrayList *foodBucket; // Stores all food positions on the heap

public:
    Food();  // Constructor
    ~Food(); // Destructor

    void generateFood(int numFoods, int boardX, int boardY, const objPosArrayList &blockOffList);
    objPos getFood(int index) const; // Specific food position
    int getBucketSize() const;         // Number of food items in the bucket
    void removeFood(int index);      // Remove food after eaten
};

#endif
