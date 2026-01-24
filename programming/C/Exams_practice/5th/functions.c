#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

Arguments readInput(int num_args, char* arg_values[])
{
    if(num_args != 4)
    {
        fprintf(stderr,"Invalid number of arguments.\n");
        exit(EXIT_FAILURE);
    }

    Arguments args;
    args.N = atoi(arg_values[1]);
    args.a = arg_values[2][0];
    args.b = arg_values[3][0];

    if(args.N < 5 || args.N > 10)
    {
        fprintf(stderr,"Invalid value of variable \"N\". Expected: [5-10] ; provided: %d", args.N);
        exit(EXIT_FAILURE);
    }

    if(args.a < 'a' || args.a > 'z')
    {
        fprintf(stderr,"Invalid value of variable \"a\". Expected: [\'a\' - \'z\'] ; provided: %c", args.a);
        exit(EXIT_FAILURE);
    }

    if(args.b < 'a' || args.b > 'z')
    {
        fprintf(stderr,"Invalid value of variable \"b\". Expected: [\'a\' - \'z\'] ; provided: %c", args.b);
        exit(EXIT_FAILURE);
    }

    return args;
}

unsigned int get_random() 
{
    static unsigned int m_w = 123456;
    static unsigned int m_z = 789123;

    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    
    return (m_z << 16) + m_w;
}

char genVowel()
{
    char vowels[] = {'a','e','i','o','u'};
    int randVowel = (int)((get_random() / (UINT_MAX + 1.0)) * 5);
    return vowels[randVowel];
}

char genConsonant()
{
    char consonants[] = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'};
    size_t numConsonants = sizeof(consonants) /sizeof(consonants[0]);
    int randCons = (int)((get_random() / (UINT_MAX + 1.0)) * numConsonants);
    return consonants[randCons];
}

void push(Stack *stack, char value)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if(!newNode)
    {
        fprintf(stderr,"Error: impossible to allocate memory for a new node.\n");
        exit(EXIT_FAILURE);
    } 

    newNode->c = value;
    newNode->next = stack->top;
    stack->top = newNode;
}

void fillStack(Stack* stack, unsigned int n, char a, char b)
{
    for(int i=0;i<n;i++)
    {
        char x = '1' + (int)((get_random() / (UINT_MAX + 1.0)) * 9);
        if(x >= '1' && x <= '4')
        {
            for(int j=0;j< (int)(x - '0');j++)
            {
                char cc = genVowel();
                push(stack, (cc==a ? '?' : (cc==b ? '?' : cc)));
            }
            push(stack,x);
        }
        if(x >= '5' && x <= '9')
        {
            for(int j=0;j< (int)(x - '0');j++)
            {
                char cc = genConsonant();
                push(stack, (cc==a ? '?' : (cc==b ? '?' : cc)));
            }
            push(stack,x);
        }
    }
}

void printStack(Stack* stack)
{
    printf("\n** TOP -> ");
    while(stack->top != NULL)
    {
        printf("%c ",stack->top->c);
        stack->top = stack->top->next;
    }
    printf(" <- BOTTOM **\n");
}