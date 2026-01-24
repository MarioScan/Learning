#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Arguments readInput(int num_args, char* argv[])
{
    if(num_args != 3)
    {
        fprintf(stderr,"Invalid number of arguments.\n");
        exit(EXIT_FAILURE);
    }

    Arguments args;
    args.IN = argv[1];
    args.k = atoi(argv[2]);

    if(args.k < 7 || args.k > 13)
    {
        fprintf(stderr,"Invalid value for the variable \"k\". Expected: [7-13] ; provided %s\n",argv[2]);
        exit(EXIT_FAILURE);
    } 

    return args;
}

void insertWord(Stack* stack, char* word)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(!newNode)
    {
        fprintf(stderr,"Impossible to allocate memory for a new node.\n");
        exit(EXIT_FAILURE);
    }

    newNode->key = strdup(word);
    newNode->prev = NULL;    
    newNode->next = NULL;

    //Case 1 --> Stack is empty
    if(stack->top == NULL)
    {
        stack->top = newNode;    
        return;
    }
    //Case 2 --> new node goes on top of the stack (stringa lessicamente minore):
    if(strcmp(newNode->key,stack->top->key) < 0)
    {
        newNode->next = stack->top;
        stack->top->prev = newNode;
        stack->top = newNode;
        return;
    }

    //Case 3 --> trova posizione corretta per nuovo nodo (stringa lessicamente maggiore):
    Node* current = stack->top; //scorrimento 
    while(current->next != NULL && strcmp(newNode->key,current->next->key) > 0) //meccanismo di scorrimento: 
    { //current->next != NULL assicura che non si esca dallo Stack, e si fermi all'ultimo valore possibile che sia maggiore di newNode, altrimenti si posiziona come ultimo nodo
        current = current->next;
        //quindi scorre tutto lo stack a partire dal next della cima dello Stack 
    }
    //inserisci nodo nella posizione corretta
    newNode->next = current->next; //il successivo di newNode è il successivo del nodo corrente (nodo in cui si è fermato il ciclo while di sopra)
    newNode->prev = current; //il precedente di newNode è quindi il nodo corrente 
    //quindi --> current node --> newNode --> current->next (newNode si posizione in mezzo) o nel caso in cui non ci siano elementi più grandi di newNode: currentNode --> newNode --> NULL
    
    if(current->next != NULL) 
    {
        current->next->prev = newNode; //indica al nodo successivo (se non NULL) che prima di esso adesso c'è il nuovo nodo
    }

    current->next = newNode; //nuovo nodo diventa il valore 
}

void buildList(Stack* stack, const char* file_name)
{
    FILE* file = fopen(file_name, "r");
    if(!file)
    {
        fprintf(stderr,"Impossible to open the input file for the reading.\n");
        exit(EXIT_FAILURE);
    }

    char buffer[maxLength];
    while(fscanf(file,"%29s",buffer) == 1)
    {   
        insertWord(stack,buffer);
    }

    fclose(file);
}

void printList(Stack* stack)
{
    printf("\nOutput:\n");
    Node* current = stack->top;
    while(current != NULL)
    {
        printf("%s\n",current->key);
        current = current->next;
    }
}

void elab(Stack* stack, int k)
{
    int c=0;
    Node* current = stack->top;
    while(current != NULL)
    {
        if(strlen(current->key) >= k)
        {
            c++;
        }
        current = current->next;
    }
    printf("Numero di stringhe aventi lunghezza pari o maggiore di %d: %d\n",k,c);
}




/* Inserimento senza controllo lessicografico:

void insertWord(Stack* stack, char* word)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(!newNode)
    {
        fprintf(stderr,"Impossible to allocate memory for a new node.\n");
        exit(EXIT_FAILURE);
    }

    newNode->key = strdup(word);
    newNode->prev = NULL;    
    newNode->next = stack->top;

    if(stack->top != NULL)
    {
        stack->top->prev = newNode;
    }
    stack->top = newNode;
}

*/