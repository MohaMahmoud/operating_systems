#include "sorting.h"

/**
 * Swap both Integers the pointers are pointing to with each other.
 */
void swap(int *pointer1, int *pointer2)
{  
    int temp = *pointer1;
    *pointer1 = *pointer2;
    *pointer2 = temp;
}

/**
 * Sorts the array toSort with given length ascending using insertion sort.
 */
void insertionSort(int *toSort, size_t length)
{
    for (size_t i = 1; i < length; i++)
    {
        size_t j = i;
        while (j > 0 && toSort[j - 1] > toSort[j])
        {
            swap(&toSort[j], &toSort[j - 1]);  
            j--;
        }
    }
}

/**
 * Creates a new array and copies length elements from src array into the new array.
 * The caller needs to free the new returned array.
 */
int *copy(int *src, size_t length)
{
    int *copy = (int*)malloc(length*sizeof(int));
    for (size_t i = 0; i < length; i++) {
        copy[i] = src[i];
    }
    return copy;
}

/**
  * Merge src array which contains two sorted sub array src[start...middle - 1] and src[middle...end-1].
  * The sub arrays are merged into destToMergeInto with the result sorted as well.
  */
void merge(int *src, size_t start, size_t middle, size_t end, int *destToMergeInto)
{
    size_t i = start;
    size_t j = middle;
    size_t k = start;
    while(i<middle && j<end) {
        if (src[i]<src[j]) {
            destToMergeInto[k] = src[i];
            i++;
        } else {
            destToMergeInto[k] = src[j];
            j++;
        }
        k++;
    }
    while (i < middle) {
        destToMergeInto[k] = src[i];
        i++;
        k++;
    }
    while (j < end) {
        destToMergeInto[k] = src[j];
        j++;
        k++;
    }
}

/**
 * Sorts the array srcToSort recursively with merge sort. 
 * Start and end indicate the current window of srcToSort array this call sorts.
 * The result will be in sortedDest.
 */
void mergeSortRec(int *srcToSort, size_t start, size_t end, int *sortedDest)
{
    if (end - start > 1) {
        size_t middle = (end + start) / 2;
        mergeSortRec(sortedDest, start, middle, srcToSort);
        mergeSortRec(sortedDest, middle, end, srcToSort);
        merge(srcToSort, start, middle, end, sortedDest);
    }
}

/**
 * Sorts the array toSort with given length ascending using merge sort.
 */
void mergeSort(int *toSort, size_t length)
{
    int *copyToSort = copy(toSort, length);
    mergeSortRec(copyToSort, 0, length, toSort);
    free(copyToSort);
}

/**
 * Rotates the array stackOfPancakes[0...numberOfPancakesToFlip-1].
 */
void flip(int *stackOfPancakes, size_t numberOfPancakesToFlip)
{
    int temp;
    size_t middle = numberOfPancakesToFlip/2;
    for (size_t i = 0; i < middle; i++) {
        temp = stackOfPancakes[i];
        stackOfPancakes[i]=stackOfPancakes[numberOfPancakesToFlip-1-i];
        stackOfPancakes[numberOfPancakesToFlip-1-i] = temp;
    }
}

/**
 * Finds the index of the largest number in array with the given length.
 */
size_t findIndexOfMax(int *array, size_t length)
{   
    int max = array[0];
    size_t max_index = 0;
    for (size_t i = 0; i < length; i++) {
        if (array[i] > max) {
            max = array[i];
            max_index = i;
        }
    }
    return max_index;
}

/**
 * Sorts the array toSort with given length ascending using pancake sort.
 */
void pancakeSort(int *toSort, size_t length)
{
    size_t maxIndex = 0;
    for (size_t i = length; i > 1; --i) {
        maxIndex = findIndexOfMax(toSort, i);
        if (maxIndex != i) {
            flip(toSort, maxIndex + 1);
            flip(toSort, i);
        }
    }
}
