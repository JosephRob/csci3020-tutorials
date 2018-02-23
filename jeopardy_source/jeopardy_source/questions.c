/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "questions.h"

// Initializes the array of questions for the game
void initialize_game(void){
    FILE * f=fopen("JEOPARDY_CSV.txt","r");
    srand(time(NULL));

    char line[512];
    int next=5*(1000+rand()%1000)-1;
    char *token1, *token2, *token3;
    for(int y=0;y<3;y++){
        for(int x=0;x<next;x++){
            fgets(line, 255,(FILE * )f);
        }
        for(int x=0;x<4;x++){
            fgets(line, 255,(FILE * )f);
            //printf("%s",line);
            token1=strtok(line,"\t");
            token2=strtok(NULL,"\t");
            token3=strtok(NULL,"\t");
            //printf("AAA\n");
            strcpy(questions[4*y+x].category,token1);
            strcpy(questions[4*y+x].question,token2);
            strcpy(questions[4*y+x].answer,token3);
            questions[4*y+x].value=(100)*(x+1);
            questions[4*y+x].answered=0;
        }
    }
    

    // initialize each question struct and assign it to the questions array
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void){
    int len=0;
    for(int x=0;x<3;x++){
        printf("%s\t",questions[4*x].category);
    }
    printf("\n");
    for(int x=0;x<12;x++){
        len=strlen(questions[(x/3)+4*(x%3)].category);
        if(x%3==0){
            printf("\n");
        }
        if(questions[(x/3)+4*(x%3)].answered==0){
            printf("%d",questions[(x/3)+4*(x%3)].value);
            len-=3;
        }
        for(int x=0;x<len;x++){
            printf(" ");
        }
        printf("\t");
    }
    printf("\n\n");
}

// Displays the question for the category and dollar value
void display_question(char *category, int value){
    //printf("|%s|\t%d\n",category,value);
    for(int x=0;x<3;x++){
        if(strcmp(questions[4*x].category,category)==0){
            //printf("%s\t%d:\t",category,value);
            switch(value){
                case 100:
                questions[x*4].answered=1;
                printf("%s\n",questions[x*4].question);
                break;
                case 200:
                questions[x*4+1].answered=1;
                printf("%s\n",questions[x*4+1].question);
                break;
                case 300:
                questions[x*4+2].answered=1;
                printf("%s\n",questions[x*4+2].question);
                break;
                case 400: 
                questions[x*4+3].answered=1;
                printf("%s\n",questions[x*4+3].question);
                break;
                default:
                printf("invalid value\n");
            }
        }
    }
}
// Gets the answer for the category and dollar value
char* get_answer(char *category, int value){
    //printf("|%s|\t%d\n",category,value);
    for(int x=0;x<3;x++){
        if(strcmp(questions[4*x].category,category)==0){
            //printf("%s\t%d:\t",category,value);
            switch(value){
                case 100:
                questions[x*4].answered=1;
                return questions[x*4].answer;
                break;
                case 200:
                questions[x*4+1].answered=1;
                return questions[x*4+1].answer;
                break;
                case 300:
                questions[x*4+2].answered=1;
                return questions[x*4+2].answer;
                break;
                case 400: 
                questions[x*4+3].answered=1;
                return questions[x*4+3].answer;
                break;
                default:
                printf("invalid value\n");
            }
        }
    }
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer){
    // Look into string comparison functions
    char* part1=strtok(answer," ");
    char* part2=strtok(NULL," ");
    char* rest=strtok(NULL,"\n");
    char* correct=get_answer(category,value);
    //printf("%s|%s|%s|\n",part1,part2,rest);
    printf("the answer was: {%s}\n",correct);
    if(strcmp(part1,"what")==0 || strcmp(part1,"who")==0){
        if(strcmp(part2,"is")==0){
            //printf("correct format");
            if(strcmp(rest,correct)==0){
                printf("correct\n");
                return true;
            }
        }
    }
    return false;
}
bool done(){
    bool check=0;
    for(int x=0;x<NUM_QUESTIONS;x++){
        check=check||(!questions[x].answered);
    }
    return check;
}
// Returns true if the question has already been answered
bool isQ(char *category, int value){
    for(int x=0;x<3;x++){
        if(strcmp(questions[4*x].category,category)==0 && value%100==0){
            return 1;
        }
    }
    return 0;
}
bool already_answered(char *category, int value){
    for(int x=0;x<3;x++){
        if(strcmp(questions[4*x].category,category)==0){
            //printf("%s\n",questions[x*4+(value/100)-1].question);
            switch(value){
                case 100:
                //printf("%s\n",questions[x*4].question);
                return questions[x*4].answered;
                break;
                case 200:
               // printf("%s\n",questions[x*4+1].question);
                return questions[x*4+1].answered;
                break;
                case 300:
                return questions[x*4+2].answered;
                break;
                case 400: 
                return questions[x*4+3].answered;
                break;
                default:
                printf("invalid value\n");
                return false;
            }
        }
    }
    return false;
}
