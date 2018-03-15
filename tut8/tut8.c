#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


struct proc{
    char name[256];
    char parent[256];
    int priority;
    int memory;
};
struct procTree{
    struct proc * process;
    struct procTree * parent;
    struct procTree * right;
    struct procTree * left;
};
char * printTree(struct procTree * tree, int I){
    struct proc * process = tree->process;
    if(tree->left!=NULL)
        printTree((*tree).left,I+1);
    for(int x=0;x<I;x++){
        printf("\t");
    }
    printf("|%s|\t|%s|\n\n",process->name,process->parent);
    if(tree->right!=NULL)
        printTree((*tree).right,I+1);
}
void add(struct proc * process, struct procTree * tree){
    if(tree->process==NULL){
        tree->process=process;
    }
    else{
        struct proc * asdf = tree->process;
        if(strcmp(asdf->name,process->parent)==0){
    printf("%s\t%s\n",process->name,process->parent);
            if (tree->left==NULL){
    printf("%s\t%s\n",process->name,process->parent);
                tree->left=malloc(sizeof(struct procTree));
                tree->left->left=NULL;
                tree->left->right=NULL;
                tree->left->parent=tree;
                tree->left->process=process;
    printf("%s\t%s\n",tree->left->process->name,tree->left->process->parent);
            }
            else{
    printf("%s\t%s\n",process->name,process->parent);
                tree->right=malloc(sizeof(struct procTree));
                tree->right->left=NULL;
                tree->right->right=NULL;
                tree->right->parent=tree;
                tree->right->process=process;
    printf("%s\t%s\n",tree->right->process->name,tree->right->process->parent);
            }
    printf("%s\t%s\n",process->name,process->parent);
        }
        else{
            //printf("\t%s\n",tree->process->name);
            if(tree->left!=NULL)
                add(process,tree->left);
            if(tree->right!=NULL)
                add(process,tree->right);
        }
    }
}
int main(void){
    struct proc * p1;
    struct procTree* base;
    base=malloc(sizeof(struct procTree));
    base->process=NULL;
    base->left=NULL;
    base->right=NULL;
    base->parent=NULL;

    stdin=freopen("process_tree.txt","r",stdin);
    char name[256];
    char parent[256];
    int priority=0;
    int memory=0;
    for(int x=0;x<8;x++){
        scanf("%s, ",parent);
        scanf("%s, ",name);
        scanf("%i, ",&priority);
        scanf("%i", &memory);
        p1=malloc(sizeof(struct procTree));
        strcpy(p1->name,strtok(name,","));
        strcpy(p1->parent,strtok(parent,","));
        p1->priority=priority;
        p1->memory=memory;
        printf("%s\t%s\t%i\t%i\n",p1->name,p1->parent,p1->priority,p1->memory);
        add(p1,base);
    }
    printf("%s\n",base->left.parent);
    printTree(base,0);
}