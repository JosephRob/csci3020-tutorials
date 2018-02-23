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
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4

// Put global environment variables here

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens);

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(struct player *players, int num_players);

int game_state;


int main(int argc, char *argv[])
{
    // An array of 4 players, may need to be a pointer if you want it set dynamically
    struct player players[NUM_PLAYERS];

    // EXAMPLE: player 1 is named Fred
    //strcpy(players[0].name, "Fred");
    //printf("%s\n", players[0].name);
    for(int x=0;x<NUM_PLAYERS;x++){
        printf("player name %d:\t",x);
        char temp[BUFFER_LEN];
        fgets(temp, BUFFER_LEN,stdin);
        //printf("|%s|\n",temp);
        strcpy(players[x].name, strtok(temp,"\n"));
        //printf("|%s|\n",players[x].name);
        players[x].score=0;
    }
    
    // Buffer for user input
    char buffer[BUFFER_LEN] = { 0 };

    // Display the game introduction and initialize the questions
    initialize_game();

    // Prompt for players names
    
    // initialize each of the players in the array

    // Perform an infinite loop getting command input from users until game ends
    game_state = 1;
    while (game_state){
        for(int x=0;x<NUM_PLAYERS;x++){printf("%s\t%d\n",players[x].name,players[x].score);}//scoreboard
        // EXAMPLE: This line gets a line of input from the user
        while (true){
            printf("name of player to choose question: ");
            fgets(buffer, BUFFER_LEN, stdin);
            char *name=strtok(buffer,"\n");
            if(player_exists(&players, NUM_PLAYERS,name)){
                break;
            }
        }
        char question[BUFFER_LEN];
        int amount;
        //while(1){
            display_categories();
            printf("category: ");
            fgets(question,BUFFER_LEN,stdin);
            strcpy(question,strtok(question,"\n"));
            printf("amount: ");
            scanf("%d",&amount);
            printf("%s\t%d\n",question,amount);
            //if(isQ(question,amount)){
                //break;
            //}
        //}
        display_question(question,amount);
        // Call functions from the questions and players source files

        // Execute the game until all questions are answered

        // Display the final results and exit
        break;
    }
    return EXIT_SUCCESS;
}
