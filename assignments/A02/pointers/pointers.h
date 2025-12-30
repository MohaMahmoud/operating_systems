#ifndef POINTERS_H
#define POINTERS_H
#include <inttypes.h>

/*!
 * calculate average of int array
 * \param arrayPointer pointer to begin of array
 * \param size the number of elements
 * \return average of array, or 0 for 0 elements
 */
int average(int *arrayPointer, unsigned int size);

/*!
 * calculate average of int array
 * \param arrayPointer pointer to array of int pointers
 * \param size the number of elements
 * \return average of array, or 0 for 0 elements
 */
int averageIndirect(int **arrayPointer, unsigned int size);

#endif

