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
/*void tokenize(char *input, char **tokens){
	char *temp_p;
	while( temp_p = strstr( temp_p, substr ) ){
   		int length = strlen( temp_p );
    		memmove( temp_p, temp_p + subStrSize, length - subStrSize + 1 );
	}
	
}*/
char * removeSubStr( char *str, const char *substr )
{
    size_t m1 = strlen(str);
    size_t m2 = strlen(substr);

    if (!(m1 < m2))
    {
        for (char *p = str; (p = strstr(p, substr)) != NULL; )
        {
            size_t n = m1 - ( p + m2 - str );
            memmove(p, p + m2, n + 1);
        }
    }
	printf("this is the return string: %s\n",str);
    return str;
}
int strRemoveAll(char *src,char *key)
{
  while( *src )
  {
    char *k=key,*s=src;
    while( *k && *k==*s ) ++k,++s;
    if( !*k )
    {
      while( *s ) *src++=*s++;
      *src=0;
      return 1;
    }
    ++src;
  }
  return 0;
}
void removeSubstring(char *s,const char *toremove)
{
  while( s=strstr(s,toremove) )
    memmove(s,s+strlen(toremove),1+strlen(s+strlen(toremove)));
}
int words(const char *sentence)
{
    int count=0,i,len;
    char lastC;
    len=strlen(sentence);
    if(len > 0)
    {
        lastC = sentence[0];
    }
    for(i=0; i<=len; i++)
    {
        if((sentence[i]==' ' || sentence[i]=='\0') && lastC != ' ')
        {
            count++;
        }
        lastC = sentence[i];
    }
    return count;
}

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(struct player *players, int num_players){
	int scoreFL[num_players];
	char* nameFL[num_players];
	for(int x=0;x<num_players;x++){
		scoreFL[x] = players[x].score;
		nameFL[x] = players[x].name;
		//strcpy(nameFL[x],players[x].name);
	}
	for (int i = 0; i < num_players; i++)                     //Loop for descending ordering
	{
		for (int j = 0; j < num_players; j++)             //Loop for comparing other values
		{
			if (scoreFL[j] < scoreFL[i])                //Comparing other array elements
			{
				int tmp = scoreFL[i];//Using temporary variable for storing last value	
				char* tmpname = nameFL[i];		
				scoreFL[i] = scoreFL[j];            //replacing value
				nameFL[i] = nameFL[j];
				scoreFL[j] = tmp;             //storing last value
				nameFL[j] = tmpname; 			
			}
		}
	}
		
	for(int x=0;x<num_players;x++){
		printf("%s:%d\n",nameFL[x],scoreFL[x]);
	}
}

int game_state;

//int main(int argc, char *argv[])
int main(){
    // An array of 4 players, may need to be a pointer if you want it set dynamically
    struct player players[NUM_PLAYERS];

    // EXAMPLE: player 1 is named Fred
    for(int x=0;x<4;x++){
        char A[256];
        printf("enter name of player %i: ",x+1);
        scanf("%256s",A);
        strcpy(players[x].name,A);
        players[x].score=0;
    }
    
    printf("%s\n", players[0].name);
    printf("%s\n", players[1].name);
    printf("%s\n", players[2].name);
    printf("%s\n", players[3].name);
    
    // Buffer for user input
    //char buffer[BUFFER_LEN] = { 0 };

    // Display the game introduction and initialize the questions
    initialize_game();

    // Prompt for players names
    
    // initialize each of the players in the array

    // Perform an infinite loop getting command input from users until game ends
    game_state = 1;
    int currentPlayer=0;
    int failCounter=0;
	/*char category[256];
	int value;
	char answer[256];*/
    while (game_state)
    {
        // EXAMPLE: This line gets a line of input from the user
        //printf("[%s]", buffer);
        /*for(int x=0;x<strlen(buffer);x++){
            if(buffer[x]='\n')
            buffer[x]=' ';
        }*/

		//if (strcmp(buffer, "hello\n") == 0) printf(":)\n");
		//if (strcmp(buffer, "world\n") == 0) printf(":)\n");

        display_categories();

        
        //fgets(buffer, BUFFER_LEN, stdin);
	printf("%s, You are Answering\n",players[currentPlayer].name);
	char category[256];
	int value;
	//char answer[256];
	//char temp[256];
        
	do{
		printf("pick category:\n");
        	scanf("%255s",category);
		
		printf("pick value:\n");
		scanf(" %d",&value);
	
	}while(findQ(category,value) == NULL);
	display_question(category,value);
	while(failCounter <NUM_PLAYERS){
		char answer[256];
		//char temp1[256];
		//char temp2[256];
		printf("\n%s,Enter Answer:",players[currentPlayer].name);
		scanf(" %s",answer);
		int x = words(answer);
		/*strcpy(temp1,removeSubStr(answer, "who"));
		strcpy(temp2,removeSubStr(temp1, "is"));		
		strcpy(answer,removeSubStr(temp2, "what"));*/
		removeSubStr(answer, "who");
		removeSubStr(answer, "is");
		removeSubStr(answer, "what");
		for(int i=0;i<=x;i++){
		scanf(" %s",answer);
		}
		/*while( strRemoveAll(answer,"what"));
		while( strRemoveAll(answer,"is") );
		while( strRemoveAll(answer,"who") );*/
		/*removeSubstring(answer,"what");
		removeSubstring(answer,"is");
		removeSubstring(answer,"who");*/

		//printf("You Entered:%s using temp1:%s temp2:%s\n",answer,temp1,temp2);
		printf("You Entered:%s\n",answer);
		if (valid_answer(category,value,answer) == true){
			printf("correct\n");
			update_score(players,NUM_PLAYERS,players[currentPlayer].name,value);
			failCounter =0;
			break;
		}
		else{
			printf("wrong\n");
			failCounter+=1;
			update_score(players,NUM_PLAYERS,players[currentPlayer].name,-value);
			//players.[currentPlayer].score -=value;
			currentPlayer+=1;
			if (currentPlayer==NUM_PLAYERS){
				currentPlayer=0;
			}
			if (failCounter == NUM_PLAYERS){
					continue;
			}
		}
	}
	makeAnswered(category,value);
        
        // Call functions from the questions and players source files

        // Execute the game until all questions are answered

        // Display the final results and exit
	if (checkEnd()==true)
		game_state=0;
	
    }
    return EXIT_SUCCESS;
}
