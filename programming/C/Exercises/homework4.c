#include <stdio.h>
#include <math.h>
#include <float.h>
#include <string.h>

int  main() 
{    
    int indice;

    do
    {
        printf("Inserisci n. esercizio  (da 1 a 2):\n");
        scanf("%d", &indice);
    }while(indice < 1 || indice > 2);

    switch(indice) 
    {
        case 1:
        {
            //homework H12.2 (12. array)

            double p;

            do
            {
               printf("Inserisci un numero qualunque 'p': ");
                scanf("%lf",&p);
                if(p<1)
                {
                    printf("Valori non validi, inserisci un valore qualsiasi 'p' maggiore di 1:\n");
                }
            } while (p<1);

            p = ceil(p); //arrotondo p all'intero più vicino

            int a[(int)p];

            printf("\nInizializza array:\n");
            for(int i=0;i<(int)p;i++)
            {
                printf("Inserisci valore array [%d]: ",i+1);
                scanf("%d", &a[i]);
            }

            printf("\nStampa elementi array:\n");
            for(int i=0;i<(int)p;i++)
            {
                printf("Valore elemento n.%d = %d\n",i+1,a[i]);
            }

            break;
        }
        case 2:
        {
            double N,M;

            //1
            do
            {
                printf("\nInserisci un numero qualsiasi 'N' (N>1): ");
                scanf("%lf",&N);
                printf("\nInserisci un numero qualsiasi 'M' (M>1): ");
                scanf("%lf",&M);

                if(N<1 || M<1)
                {
                    printf("Valori non validi, riprova.\n");
                }
            }while(N<1 || M<1);
            
            N = ceil(N);
            M = ceil(M);
            int array[(int)N][(int)M];
            int c=0;
            //printf("%d\n",(int)N);
            //printf("%d\n",(int)M);
            
            //2
            printf("\nMatrice creata del tipo:\n");
            for(int i=0; i < (int)N; i++)
            {
                for(int j=0; j < (int)M; j++)
                {
                    printf("[%d] ",c);
                    c++;
                }
                printf("\n");
            }
            c=0;

            //3
            printf("\nInizializza array:\n");
            for(int i=0; i < (int)N; i++)
            {
                printf("Riga n.%d: \n",i+1);
                for(int j=0; j < (int)M; j++)
                {
                    printf("Inserisci valore cella [%d]: ",c);
                    scanf("%d", &array[i][j]);
                    c++;
                }
            }
            c=0;
            fflush(stdin);

            //4
            printf("\nStampa array:\n");
            for(int i=0; i < (int)N; i++)
            {
                printf("Riga n.%d: \n",i+1);
                for(int j=0; j < (int)M; j++)
                {
                    printf("%d  ",array[i][j]);
                }
                printf("\n");
            }

            //5
            printf("\nCalcola e stampa il prodotto con il numero '3' con tutti gli elementi della matrice:\n");
            for(int i=0; i < (int)N; i++)
            {
                printf("Riga n.%d: \n",i+1);
                for(int j=0; j < (int)M; j++)
                {
                    printf("%d  ",(array[i][j]*3));
                }
                printf("\n");
            }            
            
            //6
            if(N>M)
            N = M;

            int array2[(int)N][(int)N];

            printf("\nNuova matrice 'array2' creata del tipo:\n");
            for(int i=0; i < (int)N; i++)
            {
                for(int j=0; j < (int)N; j++)
                {
                    printf("[%d] ",c);
                    c++;
                }
                printf("\n");
            }
            c=0;

            //creazione e clonazione dati
            for(int i=0; i < (int)N; i++)
            {
                for(int j=0; j < (int)N; j++)
                {
                    array2[i][j] =  array[i][j];
                }
            }

            //stampa
            printf("\nCreazione di un array quadrato:\n*Nota: alcuni valori potrebbero non entrare nel nuovo array, causando perdita di dati.\n");
            for(int i=0; i < (int)N; i++)
            {
                printf("Riga n.%d: \n",i+1);
                for(int j=0; j < (int)N; j++)
                {
                    printf("%d  ",array2[i][j]);
                }
                printf("\n");
            }


            break;
        }
    }

        
}