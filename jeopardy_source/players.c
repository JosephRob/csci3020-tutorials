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
void initialize_game(void)
{
    // initialize each question struct and assign it to the questions array
	for (int x=0;x<NUM_QUESTIONS;x++){
		int val = 200+(x%(NUM_QUESTIONS/NUM_CATEGORIES))*200;
		strcpy(questions[x].category,categories[x%NUM_CATEGORIES]);
		strcpy(questions[x].question,questionArray[x]);
		questions[x].value = val;
		strcpy(questions[x].answer,answerArray[x]);
		questions[x].answered = false;
		printf("%s  %s  %d %s\n",questions[x].category,questions[x].question,questions[x].value,questions[x].answer);
	}
}


// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    for(int x=0;x<NUM_CATEGORIES;x++){
        printf("%s\t",categories[x]);
    }
    printf("\n");
    for(int x=0;x<5;x++){
        for(int y=0;y<NUM_CATEGORIES;y++){
            printf("%i",200*(x+1));
            for(int z=0;z<(strlen(categories[y])/4);z++)
                printf("\t");
        }
        printf("\n");
    }
    // print categories and dollar values for each unanswered question in questions array
}

// Displays the question for the category and dollar value
bool display_question(char *category, int value)
{
	for (int x=0;x<NUM_QUESTIONS;x++){
		if (strcmp(category,questions[x].category) ==0){
			if(value ==questions[x].value){
				printf("%s",questions[x].question);
				return true;
			}
		}
	}
	return false;
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    for (int x=0;x<NUM_QUESTIONS;x++){
	if (strcmp(category,questions[x].category) ==0){
		if(value ==questions[x].value){
			if(strstr(answer,questions[x].answer)!=NULL){
				questions[x].answered = true;
				return true;
			}
		}
	}
    }	
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
	for (int x=0;x<NUM_QUESTIONS;x++){
		if (strcmp(category,questions[x].category) ==0){
			if(value ==questions[x].value){
				if(questions[x].answered == false){
					return true;
					
				}
			}
		}
	}
    // lookup the question and see if it's already been marked as answered
    return false;
}
void makeAnswered(char *category, int value){
	for (int x=0;x<NUM_QUESTIONS;x++){
		if (strcmp(category,questions[x].category) ==0){
			if(value ==questions[x].value){
				if(questions[x].answered == false){
					questions[x].answered = true;
					
				}
			}
		}
	}
}
bool checkCategory(char *category,int value)
{	printf("entered");
	for (int x=0;x<NUM_QUESTIONS;x++){
		if(strcmp(category,questions[x].category) ==0){
			if(value == questions[x].value){
				printf("true");
				return true;
			}
			
		}
	}
    return false;
}
bool checkEnd(void)
{
	for (int x=0;x<NUM_QUESTIONS;x++){
		if(questions[x].answered == false){
			return false;
		}
	}
    return true;
}
struct question* findQ(char *category, int value){
    for (int x=0;x<NUM_QUESTIONS;x++){
        if (strcmp(questions[x].category,category)==0 && questions[x].value==value)
            return &questions[x];
    }
	return NULL;
}
