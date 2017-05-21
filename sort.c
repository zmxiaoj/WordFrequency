//
//  sort.c
//  PA1
//
//  Created by He11o_Liu on 2016/10/23.
//  Copyright © 2016年 He11o_Liu. All rights reserved.
//

#include "sort.h"

//**********************TOOLS**********************//
/**
 * wordcpy
 * copy (struct word)
 * Param word *dest
 * Param word *src
 * Author Liu Nian
 * 2016-10-22
 */
void wordcpy(word *dest,word *src){
    memcpy(dest,src,sizeof(word));
}

/**
 * wordswap
 * swap (struct word)
 * Param word *object0
 * Param word *object1
 * Author Liu Nian
 * 2016-10-23
 */
void wordswap(word *object0,word *object1){
    word tmpword;
    memcpy(&tmpword,object0,sizeof(word));
    memcpy(object0,object1,sizeof(word));
    memcpy(object1,&tmpword,sizeof(word));
}


/**
 * compareAppearTime
 ************* compare function *************
 * This function is used to compare two word by their AppearTime
 * return -1(smaller) 0(equal) or 1(larger)
 * Author Liu Nian
 * 2016-10-22
 */
int compareAppearTime(word object0,word object1){
    if(object0.AppearTime>object1.AppearTime) return 1;
    else if(object0.AppearTime == object1.AppearTime) return 0;
    else return -1;
}

/**
 * compareWord
 ************* compare function *************
 * This function is used to compare two word by alphabetic order
 * return -1(smaller) 0(equal) or 1(larger)
 * Author Liu Nian
 * 2016-10-22
 */
int compareWord(word object0,word object1){
    char* word0 = object0.word,* word1= object1.word;
    int compareResult = 0;
    compareResult = strcmp(word0, word1);
    if(compareResult ==0) return 0;
    else return compareResult>0?1:-1;
}


//**********************InsertionSort**********************//

/**
 * InsertionSort
 * Param word *list : the start pointer of the list
 * Param int length : how many element need to be sorted (from start pointer)
 * Param int (*compare)() : Compare Function which can tell which object is larger or smaller
 * Param int compare_mode : Ascending/Descending
 **********IMPORTANT***********
 * Compare Funtion should return
 * -1(smaller) 0(equal) or 1(larger)
 ******************************
 * Author Liu Nian
 * 2016-10-22
 */
void InsertionSort(word *list,int length,int (*compare)(),int compare_mode){
    int i = 0 ,j = 0;
    word key;
    for(i = 1;i < length;i++){
        wordcpy(&key, &list[i]);
        j = i - 1;
        while( j>= 0 && compare(list[j],key) == compare_mode){
            wordcpy(&list[j+1], &list[j]);
            j--;
        }
        wordcpy(&list[j+1],&key);
    }
}

//**********************MergeSort**********************//
/**
 * defineInfinite
 * Give object a infinite number depand on compare mode
 * Param word *object
 * Param int compare_mode
 * Author Liu Nian
 * 2016-10-22
 */
void defineInfinite(word *object,int compare_mode){
    if(compare_mode == Descending){
        object->AppearTime = MININT;
        object->word[0] = 'A'-1;
    }
    else{
        object->AppearTime = MAXINT;
        object->word[0] = 'z'+1;
    }
}

/**
 * merge
 * This function is to combine sub sequence
 * Param word *list
 * Param int int p head
 * Param int q middle
 * Param int r tail
 * Param int (*compare)()
 * Param int compare_mode
 * Author Liu Nian
 * 2016-10-23
 */
void merge(word *list,int p,int q,int r,int (*compare)(),int compare_mode){
    int n1 = q-p+1,n2 = r-q;
    int i = 0, j = 0, k = 0;
    word *Left,*Right;
    Left = malloc(sizeof(word)*(n1+1));
    Right = malloc(sizeof(word)*(n2+1));
    for(i = 0; i < n1; i++)
        wordcpy(&Left[i], &list[p+i]);
    for(j = 0; j < n2; j++)
        wordcpy(&Right[j],&list[q+j+1]);
    defineInfinite(&Left[n1],compare_mode);
    defineInfinite(&Right[n2],compare_mode);
    i = 0;j = 0;
    for(k = p;k <= r;k++){
        if(compare(Left[i],Right[j])==compare_mode)
            wordcpy(&list[k],&Right[j++]);
        else wordcpy(&list[k],&Left[i++]);
    }
    free(Left);
    free(Right);
}

/**
 * merge_sort
 * This function is used to divide sequence
 * & call merge to combine them
 * Param word *list
 * Param int int p head
 * Param int r tail
 * Param int (*compare)()
 * Param int compare_mode
 * Author Liu Nian
 * 2016-10-23
 */
void merge_sort(word *list,int p,int r,int (*compare)(),int compare_mode){
    int q;
    if(p<r){
        q = (p+r)/2;
        merge_sort(list, p, q, *compare, compare_mode);
        merge_sort(list, q+1, r, *compare, compare_mode);
        merge(list,p,q,r,*compare,compare_mode);
    }
}

/**
 * MergeSort
 * Param word *list : the start pointer of the list
 * Param int length : how many element need to be sorted (from start pointer)
 * Param int (*compare)() : Compare Function which can tell which object is larger or smaller
 * Param int compare_mode : Ascending/Descending
 **********IMPORTANT***********
 * Compare Funtion should return
 * -1(smaller) 0(equal) or 1(larger)
 ******************************
 * Author Liu Nian
 * 2016-10-23
 */
void MergeSort(word *list,int length,int (*compare)(),int compare_mode){
    merge_sort(list, 0, length - 1, *compare,compare_mode);
}


//**********************HeapSort**********************//
//*****************************************************//



/**
 * heapify
 * suppose that both left child and right child are heap
 * & combine these two heap by adding currnode
 * Param word *list
 * Param int heapsize
 * Param int currnode
 * Param int (*compare)()
 * Param int compare_mode
 * Author Liu Nian
 * 2016-10-23
 */
void heapify(word *list,int heapsize,int currnode,int (*compare)(),int compare_mode){
    int leftchild = 0, rightchild = 0,tmpindex = 0;
    leftchild = currnode * 2;
    rightchild = currnode *2 + 1;
    if(leftchild < heapsize && \
       compare(list[leftchild],list[currnode]) == compare_mode)
        tmpindex = leftchild;
    else tmpindex = currnode;
    //This else case must be tmpindex = currnode
    //(if leftchild or rightchild does't exist,
    //We count on this to give tmpindex a initial value
    if(rightchild < heapsize && \
       compare(list[rightchild],list[tmpindex])== compare_mode)
        tmpindex = rightchild;
    if(tmpindex != currnode){
        wordswap(&list[currnode], &list[tmpindex]);
        heapify(list, heapsize, tmpindex, *compare, compare_mode);
    }
}


/**
 * buildHeap
 * from the last leaf node's father use heapify
 * to build a heap (max heap or min heap depand on compare_mode)
 * Param word *list
 * Param int listlength
 * Param int (*compare)()
 * Param int compare_mode
 * Author Liu Nian
 * 2016-10-23
 */
void buildHeap(word *list,int listlength,int (*compare)(),int compare_mode){
    int i = 0;
    for(i = (listlength - 1)/2;i>=0;i--)
        //from the last leaf node's father to the root
        heapify(list, listlength, i, *compare, compare_mode);
}


/**
 * HeapSort
 * Param word *list : the start pointer of the list
 * Param int length : how many element need to be sorted (from start pointer)
 * Param int (*compare)() : Compare Function which can tell which object is larger or smaller
 * Param int compare_mode : Ascending/Descending
 **********IMPORTANT***********
 * Compare Funtion should return
 * -1(smaller) 0(equal) or 1(larger)
 ******************************
 * Author Liu Nian
 * 2016-10-23
 */
void HeapSort(word *list,int length,int (*compare)(),int compare_mode){
    int i = 0;
    buildHeap(list, length, *compare, compare_mode);
    for(i = length - 1; i > 0;i--){
        wordswap(&list[0], &list[i]);
        length --;
        heapify(list, length, 0, *compare, compare_mode);
    }
}

//**********************QuickSort**********************//
//*****************************************************//


/**
 * partition
 * This function is to divide sequence into tow part
 * one part is larger than pivot_element
 * one part is smaller then pivot_element
 * Param word *list
 * Param int int p head
 * Param int r tail
 * Param int (*compare)()
 * Param int compare_mode
 * Author Liu Nian
 * 2016-10-23
 */
int partition(word *list,int p,int r,int (*compare)(),int compare_mode){
    int pivot_element = r,i = p,j = 0;
    for(j = p; j < r;j++)
        //r is not the last element in list (pivot do)
        if (compare(list[pivot_element],list[j])==compare_mode)
            wordswap(&list[i++], &list[j]);
    wordswap(&list[r],&list[i]);
    return i;
}

/**
 * quick_sort
 * Param word *list
 * Param int int p head
 * Param int r tail
 * Param int (*compare)()
 * Param int compare_mode
 * Author Liu Nian
 * 2016-10-23
 */
void quick_sort(word *list,int p,int r,int (*compare)(),int compare_mode){
    int q;
    if(p < r){
        q = partition(list, p, r, *compare, compare_mode);
        //divide sequence into two part by pivot element
        quick_sort(list, p, q-1, *compare, compare_mode);
        quick_sort(list, q+1, r, *compare, compare_mode);
    }
}

/**
 * QuickSort
 * Param word *list : the start pointer of the list
 * Param int length : how many element need to be sorted (from start pointer)
 * Param int (*compare)() : Compare Function which can tell which object is larger or smaller
 * Param int compare_mode : Ascending/Descending
 **********IMPORTANT***********
 * Compare Funtion should return
 * -1(smaller) 0(equal) or 1(larger)
 ******************************
 * Author Liu Nian
 * 2016-10-23
 */
void QuickSort(word *list,int length,int (*compare)(),int compare_mode){
    quick_sort(list, 0, length-1, *compare, compare_mode);
}

