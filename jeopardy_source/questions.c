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
	for(int i=0;i<NUM_CATEGORIES;i++){
		for(int j=0;j<(NUM_CATEGORIES/NUM_QUESTIONS);j++){
			int num = (i*NUM_CATEGORIES/NUM_QUESTIONS)+j;
			int val = 200+j*200;
			strcpy(questions[num].category,categories[i]);
			strcpy(questions[num].question,questionArray[j]);
			questions[num].value = val;
			strcpy(questions[num].answer,answerArray[j]);
			questions[num].answered = false;
		}
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
            if(already_answered(categories[y],200*(x+1))==0)
                printf("%i",200*(x+1));
            for(int z=0;z<(strlen(categories[y])/4);z++)
                printf("\t");
        }
        printf("\n");
    }
    // print categories and dollar values for each unanswered question in questions array
}

// Displays the question for the category and dollar value
extern bool display_question(char *category, int value)
{
	for(int i=0;i<NUM_CATEGORIES;i++){
		for(int j=0;j<(NUM_CATEGORIES/NUM_QUESTIONS);j++){
			int num = (i*NUM_CATEGORIES/NUM_QUESTIONS)+j; 
			if (strcmp(category,questions[num].category) ==0){
				if(value ==questions[num].value){
					printf("%s",questions[num].question);
					}
			}
			else{
				break;
			}
		}
	}
	return true;

}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    for(int i=0;i<NUM_CATEGORIES;i++){
		for(int j=0;j<(NUM_CATEGORIES/NUM_QUESTIONS);j++){
			int num = (i*NUM_CATEGORIES/NUM_QUESTIONS)+j; 
			if (strcmp(category,questions[num].category) ==0){
				if(value ==questions[num].value){
					if(strstr(answer,questions[num].answer)!=NULL){
						return true;
					}
				}
			}
			else{
				break;
			}
		}
	}
    return false;
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
	for(int i=0;i<NUM_CATEGORIES;i++){
		for(int j=0;j<(NUM_CATEGORIES/NUM_QUESTIONS);j++){
			int num = (i*NUM_CATEGORIES/NUM_QUESTIONS)+j; 
			if (strcmp(category,questions[num].category) ==0){
				if(value ==questions[num].value){
					if(questions[num].answered == false){
						return true;
					}
				}
			}
			else{
				break;
			}
		}
	}
    // lookup the question and see if it's already been marked as answered
    return false;
}

/*struct question * findQ(char *category, int value){
    for (int x=0;x<NUM_QUESTIONS;x++){
        if (strcmp(questions[x].category,category)==0 && questions[x].value==value)
            return &questions[x];
    }
}
*/