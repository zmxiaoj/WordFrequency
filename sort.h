//
//  sort.h
//  PA1
//
//  Created by He11o_Liu on 2016/10/23.
//  Copyright © 2016 He11o_Liu. All rights reserved.
//

#ifndef sort_h
#define sort_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "head.h"

#define MAXINT 65535
#define MININT -65536

//**********TOOLS*************//
void wordcpy(word *dest,word *src);
int compareAppearTime(word object0,word object1);
int compareWord(word object0,word object1);

//**********SORT*************//
void InsertionSort(word *list,int length,int (*compare)(),int compare_mode);
void MergeSort(word *list,int length,int (*compare)(),int compare_mode);
void HeapSort(word *list,int length,int (*compare)(),int compare_mode);
void QuickSort(word *list,int length,int (*compare)(),int compare_mode);



#endif /* sort_h */
