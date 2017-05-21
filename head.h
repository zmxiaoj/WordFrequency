//
//  head.h
//  PA1
//
//  Created by He11o_Liu on 2016/10/23.
//  Copyright © 2016年 He11o_Liu. All rights reserved.
//

#ifndef head_h
#define head_h


#define WordMaxLength 50
#define ArticleMaxLength 100000
#define Ascending 1
#define Descending (-1)
#define ParamError "Parameter Error\nExample : ./out a.dat b.dat SortMethod(1~4)\n1:InsertionSort 2:MergeSort 3:HeapSort 4:QuickSort\n"
#define SortMethod "Default sort method (Quick Sort) is used\nYou can specify a sort method by adding a parameter\n1:InsertionSort 2:MergeSort 3:HeapSort 4:QuickSort\n"
#define true 1
#define false 0

typedef int bool;


//this list is used to store the exact location evey time this word appear
typedef struct AppearLocation{
    int location;
    struct AppearLocation *next;
}AppearLocation;

typedef struct {
    char word[WordMaxLength];
    int AppearTime;
    AppearLocation* head;//Head pointer of AppearLocation list
    AppearLocation* last;//the last node of AppearLocation list
}word;

typedef struct{
    int listLength;
    word list[ArticleMaxLength];
}wordsList;


#endif /* head_h */
