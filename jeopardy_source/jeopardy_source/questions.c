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
            printf("%s",line);
            token1=strtok(line,"\t");
            token2=strtok(NULL,"\t");
            token3=strtok(NULL,"\t");
            printf("AAA\n");
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
    for(int x=0;x<3;x++){
        if(strcmp(questions[4*x].category,category)){
            switch(value){
                case 100:
                printf("%s\n",questions[x*4]);
                break;
                case 200:
                printf("%s\n",questions[x*4+1]);
                break;
                case 300:
                printf("%s\n",questions[x*4+2]);
                break;
                case 400: 
                printf("%s\n",questions[x*4+3]);
                break;
                default:
                printf("invalid value\n");
            }
        }
    }
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    // Look into string comparison functions
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value){
    for(int x=0;x<3;x++){
        if(strcmp(questions[4*x].category,category)){
            switch(value){
                case 100:
                return questions[x*4].answered;
                break;
                case 200:
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
