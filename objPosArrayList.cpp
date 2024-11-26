#include "objPosArrayList.h"

// Paste your Tested implementation here.
// Paste your Tested implementation here.
// Paste your Tested implementation here.
#include "objPosArrayList.h"
#include <iostream>

using namespace std;

objPosArrayList::objPosArrayList()
{
    arrayCapacity = ARRAY_MAX_CAP;  // Default array capacity
    listSize = 0;                   // No elements in the list initially
    aList = new objPos[arrayCapacity];  // Allocate memory for the array
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;  // Deallocate the array to avoid memory leaks
}

int objPosArrayList::getSize() const
{
    return listSize;  // Return the number of valid elements in the list
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if (listSize >= arrayCapacity) {
        cout << "Error: List is full!" << endl;
        return;
    }

    // Shift elements to the right to make space for the new head
    for (int i = listSize; i > 0; --i) {
        aList[i] = aList[i - 1];
    }

    // Insert the new element at the head (index 0)
    aList[0] = thisPos;
    listSize++;  // Increase the size of the list
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (listSize >= arrayCapacity) {
        cout << "Error: List is full!" << endl;
        return;
    }

    // Insert the new element at the tail (end of the list)
    aList[listSize] = thisPos;
    listSize++;  // Increase the size of the list
}

void objPosArrayList::removeHead()
{
    if (listSize == 0) {
        cout << "Error: List is empty!" << endl;
        return;
    }

    // Shift elements to the left to fill the space left by the removed head
    for (int i = 0; i < listSize - 1; ++i) {
        aList[i] = aList[i + 1];
    }

    listSize--;  // Decrease the size of the list
}

void objPosArrayList::removeTail()
{
    if (listSize == 0) {
        cout << "Error: List is empty!" << endl;
        return;
    }

    listSize--;  // Just decrease the size of the list (tail is effectively removed)
}

objPos objPosArrayList::getHeadElement() const
{
    if (listSize == 0) {
        cout << "Error: List is empty!" << endl;
        return objPos();  // Return a default objPos object if the list is empty
    }

    return aList[0];  // Return the first element (head)
}

objPos objPosArrayList::getTailElement() const
{
    if (listSize == 0) {
        cout << "Error: List is empty!" << endl;
        return objPos();  // Return a default objPos object if the list is empty
    }

    return aList[listSize - 1];  // Return the last element (tail)
}

objPos objPosArrayList::getElement(int index) const
{
    if (index < 0 || index >= listSize) {
        cout << "Error: Index out of bounds!" << endl;
        return objPos();  // Return a default objPos object if the index is out of bounds
    }

    return aList[index];  // Return the element at the specified index
}
