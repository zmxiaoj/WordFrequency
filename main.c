/***
 *  This programs is to count the total numbers of words of the Article
 *  & How many times each word have appeared in this Article
 **********Input**********
 *  The input consists of a sequence of words, numbers, and symbols,
 *  separated by blanks, punctuation marks, and/or line breakers (end of line).
 *********output**********
 *  The output contains a number indicating the total number of words and numbers
 *  followed by a list of words (in the order of their occurrences (from the
 *  largest to the smallest)and alphabetic order (from ‘a’ to ‘z’)), their
 *  occurrences, and a list of numbers representing their appearing order in the
 *  article
 *  Created by He11o_Liu on 2016/10/22.
 *  Copyright © 2016 He11o_Liu. All rights reserved.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "head.h"
#include "sort.h"

void ShowWordsList(wordsList *WordsList,FILE *output);
void ModifyWordsList(char *object,wordsList *WordsList,int objectLoc);

int main(int argc, const char * argv[]) {
    char Article[100000] ;
    int ArticleLength = 0,i = 0,WordGeneratorCounter = 0;
    char WordGenerator[WordMaxLength];
    bool is_generating_new_word = false;
    bool is_sabbreviate = false;
    int currAppearTime = 0,SameAppearTimeLength = 0;
    char FileReadChar;
    word* SameAppearTimeStart = NULL;
    wordsList WordsList;
    FILE *input,*output;
    void (*sort)();

    //init wordslist
    WordsList.listLength = 0;

    // check input & confirm sort method
    if(argc == 3){printf(SortMethod);sort = *QuickSort;}
    else if(argc == 4){
        if(argv[3][0]<'1'&&argv[3][0]>'4'){printf(SortMethod);sort = *QuickSort;}
        else {
            switch (argv[3][0]) {
                case '1':{sort = *InsertionSort;printf("Sort Method : InsertionSort\n");};break;
                case '2':{sort = *MergeSort;printf("Sort Method : MergeSort\n");};break;
                case '3':{sort = *HeapSort;printf("Sort Method : HeapSort\n");};break;
                case '4':{sort = *QuickSort;printf("Sort Method : QuickSort\n");};break;
            }
        }
    }
    else{printf(ParamError);exit(1);}
    if((input = fopen(argv[1],"r"))==NULL){printf("Cannot find input file %s\n",argv[1]);exit(1);}
    if((output = fopen(argv[2],"w"))==NULL){printf("Cannot create output file %s",argv[2]);exit(1);}

    //read article
    FileReadChar=fgetc(input);
    while(FileReadChar!=EOF){
        Article[i++]=FileReadChar;
        FileReadChar=fgetc(input);
    }

    i = 0;
    //traversal of article and generate words list
    while(true){
        if((Article[i]>='a'&&Article[i]<='z')||\
           (Article[i]>='A'&&Article[i]<='Z')||\
           (Article[i]=='-'&&Article[i+1]!='-'&&WordGeneratorCounter!=0)||\
           (Article[i]=='\'')||(Article[i]=='.'&&(Article[i+2]=='.'||is_sabbreviate))){
               //Generate a new word
               WordGenerator[WordGeneratorCounter++]=Article[i];
               is_generating_new_word = true;
               if(Article[i]=='.') is_sabbreviate = true;
           } else if(is_generating_new_word){
               //Add this new word into words list
               is_sabbreviate = false;
               is_generating_new_word = false;
               WordGenerator[WordGeneratorCounter]='\0';
               WordGeneratorCounter = 0;
               //special case
               if(strcmp(WordGenerator,".")!=0){
                   ArticleLength ++;
                   ModifyWordsList(WordGenerator, &WordsList, ArticleLength);
               }
           }
        if(Article[i] == '\0') break;
        i++;
    }

    //Use ChangeIndex array to sort the list
    //Sort by AppearTime (Descending way)
    sort(WordsList.list, WordsList.listLength,*compareAppearTime,Descending);

    //Sort by alphabetic order
    currAppearTime = WordsList.list[0].AppearTime;
    SameAppearTimeLength = 1;
    SameAppearTimeStart = &WordsList.list[0];
    //As we have already sort the AppearTime
    //Next step is to check how many word have the same AppearTime
    //And then sort them by alphabetic order
    for(i = 1; true ;i++){
        if(i == WordsList.listLength){//end of wordlist
            sort(SameAppearTimeStart, SameAppearTimeLength, *compareWord,Ascending);
            break;
        }else if(WordsList.list[i].AppearTime == currAppearTime){//same appearTime
            SameAppearTimeLength ++;
        }else{
            //sort by alphabetic order
            InsertionSort(SameAppearTimeStart, SameAppearTimeLength, *compareWord,Ascending);
            //prepare for the next group of words which have the same appearTime
            currAppearTime = WordsList.list[i].AppearTime;
            SameAppearTimeStart = &WordsList.list[i];
            SameAppearTimeLength = 1;
        }
    }
    //Write data into output file
    fprintf(output,"%d\n",ArticleLength);
    ShowWordsList(&WordsList,output);
    //Close file
    fclose(input);
    fclose(output);
    return 0;
}

/**
 * ModifyWordsList
 * Param char *object  : Word need to be added into the list
 * Param wordsList *WordsList
 * Param int objectLoc : Object's Exact Location in article
 * Author Liu Nian
 * 2016-10-22
 */
void ModifyWordsList(char *object,wordsList *WordsList,int objectLoc){
    int i = 0;
    bool word_already_exists = false;
    AppearLocation* tmpNode;

    for(i = 0; i < WordsList->listLength;i++){
        if(strcmp(object,WordsList->list[i].word)==0){
            word_already_exists = true;
            //use last node pointer to add new node (Appear location list)
            tmpNode = malloc(sizeof(AppearLocation));
            tmpNode -> location = objectLoc;
            tmpNode -> next = NULL;
            WordsList->list[i].last->next = tmpNode;
            WordsList->list[i].last = tmpNode;
            WordsList->list[i].AppearTime ++;
            break;
        }
    }
    if(word_already_exists==false){
        //create new Appear location list (head)
        strcpy(WordsList->list[WordsList->listLength].word,object);
        WordsList->list[WordsList->listLength].head = malloc(sizeof(AppearLocation));
        WordsList->list[WordsList->listLength].head->location = objectLoc;
        WordsList->list[WordsList->listLength].head->next = NULL;
        WordsList->list[WordsList->listLength].last = WordsList->list[WordsList->listLength].head;
        WordsList->list[WordsList->listLength].AppearTime = 1;
        WordsList->listLength ++;
    }
}

/**
 * ShowWordsList
 * Param wordsList *WordsList
 * Author Liu Nian
 * 2016-10-22
 */
void ShowWordsList(wordsList *WordsList,FILE *output){

    int i = 0;
    AppearLocation* tmpNode;
    for(i = 0; i < WordsList->listLength;i++){
        fprintf(output,"%s %d ",WordsList->list[i].word,WordsList->list[i].AppearTime);
        tmpNode = WordsList->list[i].head;
        while(tmpNode){
            fprintf(output,"%d ",tmpNode->location);
            tmpNode = tmpNode -> next;
        }
        fprintf(output,"\n");
    }
}
