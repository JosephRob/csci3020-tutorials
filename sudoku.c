#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
int bits[9][9];
int lineN=0,colN=0,cellN=0;
void * lines(void * in){
    int check[9],valid=0;
    for (int x=0;x<9;x++){
        check[x]=0;
    }
    for(int y=0;y<9;y++){
        for (int x=0;x<9;x++){
            if(bits[y][x]!=0){
                check[bits[y][x]-1]++;
            }
           // printf("%d ",bits[y][x]);
        }
           // printf("\n");
        valid=1;
        for (int x=0;x<9;x++){
            //printf("%d ",check[x]);
            if(check[x]!=0 && check[x]!=1)
                valid=0;
            check[x]=0;
        }
            //printf("\n");
        if(valid==1){
            lineN++;
            //printf("line %d valid\n",y);
        }
        else{
            printf("line %d invalid\n",y);
        }
    }
}void * cols(void * in){
    int check[9],valid=0;
    for (int x=0;x<9;x++){
        check[x]=0;
    }
    for(int y=0;y<9;y++){
        for (int x=0;x<9;x++){
            if(bits[x][y]!=0){
                check[bits[x][y]-1]++;
            }
            //printf("%d ",bits[x][y]);
        }
            //printf("\n");
        valid=1;
        for (int x=0;x<9;x++){
            //printf("%d ",check[x]);
            if(check[x]!=0 && check[x]!=1)
                valid=0;
            check[x]=0;
        }
        if(valid==1){
            colN++;
            //printf("col %d valid\n",y);
        }
        else{
            printf("col %d invalid\n",y);
        }
    }
}
void * cells(void * arg){
    int shift= (int )arg;
    //printf("%d\n",shift);
    int parts[9];
    for(int x=0;x<3;x++){
        for(int y=0;y<3;y++){
            //printf("%d ",bits[x+3*(shift%3)][y+3*(int)(shift/3)]);
            parts[3*x+y]=bits[x+3*(shift%3)][y+3*(int)(shift/3)];
        }
        //printf("\n");
    }
    int check[9];
    for(int x=0;x<9;x++)check[x]=0;
    for(int x=0;x<9;x++){
        if(parts[x]!=0)check[parts[x]-1]++;
    }
    int valid=0;
    for(int x=0;x<9;x++){
        if(check[x]==0||check[x]==1){
            valid++;
        }
    }
    if (valid==9){
        cellN++;
    }
    else{
        printf("cell %d invalid\n",shift);
    }
}
int main(){
    FILE * f = fopen("puzzle.txt","r");
    for (int x=0;x<9;x++){
        for(int y=0;y<9;y++){
            fscanf(f, "%d",&bits[x][y]);
            if(bits[x][y]!=0)
                printf("%d ",bits[x][y]);
            else printf("  ");
        }
        printf("\n");
    }
    pthread_t line,col,box[9];
    pthread_create(&line,NULL,lines,NULL);
    pthread_create(&col,NULL,cols,NULL);
    for(int x=0;x<9;x++){
        pthread_create(&box[x],NULL,cells,(void *)x);
    }
    pthread_join(col,NULL);
    pthread_join(line,NULL);
    for(int x=0;x<9;x++){
        pthread_join(box[x],NULL);
    }
    if (colN==9){
        printf("columns valid\n");
    }
    else{
        printf("columns invalid\n");
    }
    if (lineN==9){
        printf("rows valid\n");
    }
    else{
        printf("rows invalid\n");
    }
    if (cellN==9){
        printf("cells valid\n");
    }
    else{
        printf("cells invalid\n");
    }
    if (colN==9 && lineN==9 && cellN==9){
        printf("valid\n");
    }
    else{
        printf("invalid\n");
    }
}
