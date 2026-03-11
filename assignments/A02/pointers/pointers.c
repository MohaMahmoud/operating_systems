#include "pointers.h"

int average(int *arrayPointer, unsigned int size)
{
    if (size == 0) {return 0;}
    int sum = 0;   
    for (unsigned int i = 0; i<size; i++) {
        sum+=arrayPointer[i];
    }
    return sum/(int) size;
}

int averageIndirect(int **arrayPointer, unsigned int size)
{
    if (size == 0) {return 0;}
    int sum = 0;
    for (unsigned int i = 0; i<size; i++) {
        sum+= *arrayPointer[i];
    }
    return sum/ (int) size;
    return 0;
}
