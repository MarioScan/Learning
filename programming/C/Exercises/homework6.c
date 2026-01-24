#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//dichiarazione propotipo funzioni
int menu();
int menu1();
void case1(double *x, short unsigned *y, char *z);
void case2_1(double a[10], int b[10]);
void case2_2(int a[10], double b[10], double *x,int *y);
void case3(double a[200],const double *x, double *const y);
//____________________________________________________

//definizione delle funzioni
int menu()
{
    int x;
    srand(time(NULL));

    printf("\n><-><-><-><-><-><-><-><-><-><-><-><\n\n         --------\n           Menu' \n         --------\nEsercizi sui puntatori di array:\n1) Introduzione ai puntatori di array (H14.1);\n2) Numeri casuali e puntatori di array (H14.2);\n3) Numeri casuali e puntatori costanti (H14.3).\n\nAltre azioni:\n0) EXIT\n\n");
    printf("Seleziona un comando: ");
    scanf("%d",&x);
    do
    {
        if(x < 0 || x > 3)
        {
            printf("Errore: valore non ammesso. Riprova.\n");
        }
        else if(x==0)
        {
            printf("Chiusura del programma in corso...\n\n");
        }
        else
        {
            printf("Esercizio %d selezionato correttamente.\nAvvio in corso...\n\n><-><-><-><-><-><-><-><-><-><-><-><\n\n", x);
        }
    }while(x < 0 || x > 3);
    
    return x;
}
//____________________________________________________

void case1(double *x, short unsigned *y, char *z)
{
    printf("Esecuzione esercizio numero 1...\n\n1) Valori delle tre variabili puntate:\na = %lf\nb = %hu\nc = %c\n2) Valore dei puntatori alle rispettive variabili:\nx = %p\ny = %p\nz = %p\n",*x,*y,*z,x,y,z);
}

//____________________________________________________

int menu1()
{
    int x;
    do
    {
        printf("\nTornare al menu'?\nDigita un valore numerico per rispondere:\n[SI] == [1]\n[NO] == [0]\nRisposta: ");
        scanf("%d",&x);
        if(x<0 || x>1)
        {
            printf("Errore: valore non valido. Riprova.\n\n><-><-><-><-><-><-><-><-><-><-><-><\n");
        }
        else{
            if(x==0)
            {
                printf("Fine del programma. A presto!\n\n><-><-><-><-><-><-><-><-><-><-><-><\n");
            }
            else if(x==1)
            {
                printf("Ritorno al menu' in corso...\n");
            }
        }
    }while(x<0 || x>1);
    
    return x;
}

//____________________________________________________

void case2_1(double a[10], int b[10])
{
    printf("Caricamento e stampa degli array...\n\n");
    //inizializzazione array double D
    for(int i=0;i<10;i++)
    { //a[i] o come in un altro array qualunque è possibile esprimerlo come: *(a+i)
        *(a+i) = (double)rand() / (double)RAND_MAX * (90.0 - 1.25) + 1.25;
    }
    //inizializzazione array int A
    for(int i=0;i<10;i++)
    {
        //*(b+i) = (int)rand() / (int)RAND_MAX * (50 - 10) + 10;        
        b[i] = rand() % (50-10+1) + 10;
    }
    //Stampa array
    for(int i=0;i<10;i++)
    {
        printf("D[%d] = %.2f\nA[%d] = %d\n\n",i,*(a+i),i,b[i]);
    }
}

//____________________________________________________

void case2_2(int a[10], double b[10], double *x, int *y)
{
    //x --> Array D | y --> Array A
    int cont1=0,cont2=0;
    printf("1) Stampa dei valori pari dell'array A:\n\n");
    for(int i=0;i<10;i++)
    {
        if(i%2==0) //pari --> celle pari Array A
        {
            printf("Cella array A[%d] (variabile): %d, indirizzo = %p\n",i,a[i],&a[i]);
            printf("Cella array A[%d] (puntatore): %d, indirizzo = %p\n\n",i,*(y+i),y+i);
        }
        //else //dispari --> celle dispari Array D
    }
    printf("____________________________________________________\n\n2) Stampa dei valori dispari dell'array D:\n\n");
    for(int i=0;i<10;i++)
    {
        if(i%2!=0)
        {
            printf("Cella array D[%d] (puntatore): %.2f, indirizzo = %p\n",i,b[i],&b[i]);
            printf("Cella array D[%d] (puntatore): %.2f, indirizzo = %p\n\n",i,*(x+i),x+i);
        }
    }
    printf("\n><-><-><-><-><-><-><-><-><-><-><-><\n");
}

//____________________________________________________

void case3(double a[200],const double *x, double *const y)
{
    //punto 2...
    printf("Caricamento e stampa degli array...\n\n");
    //inizializzazione array double D
    for(int i=0;i<200;i++)
    { //a[i] o come in un altro array qualunque è possibile esprimerlo come: *(a+i)
        *(a+i) = (double)rand() / (double)RAND_MAX * (50 - 10) + 10;
    }
    //Stampa array V
    for(int i=0;i<200;i++)
    {
        if(i%10!=0)
        {
            printf("[%.2f] ",a[i]);
        }
        else printf("\n");
    }
    //punto 3...
    printf("\n\n____________________________________________________\n\nStampa elementi con indice non divisibile per 2 e per 3:\n\n");
    int cont=0;
    for(int i=0;i<200;i++)
    {
        if(i%2!=0 && i%3!=0)
        {
            printf("[%.2f] ",*(x+i));
            cont++;
            if(cont%9==0)
            {
                printf("\n");
            }
            //elementi per il punto 4...
            *(y+i)= (double)rand() / (double)RAND_MAX * (200 - 100) + 100;
        }
    }
    //stampa punto 4
    printf("\n\n____________________________________________________\n\nStampa elementi con valori alterati in numeri random tra 100 e 200:\n\n");
    cont=0;
    for(int i=0;i<200;i++)
    {
        if(i%2!=0 && i%3!=0)
        {
            printf("[%.2f] ",*(y+i));
            cont++;
            if(cont%9==0)
            {
                printf("\n");
            }
        }
    }
    
    printf("\n\n><-><-><-><-><-><-><-><-><-><-><-><\n");
}

//><-><-><-><-><-><-><-><-><-><-><-><

int main()
{
    int n,cc=-1;
    do
    {
        n = menu(); //Benvenuto nel menu'
        switch(n)
        {
            case 0:
            {
                printf("Terminazione del programma... A presto!\n\n><-><-><-><-><-><-><-><-><-><-><-><\n\n");
                break;
            }
            case 1:
            {
                double a=12.5;
                short unsigned b=2.3;
                char c='*';
                case1(&a,&b,&c);
                printf("3) Valori delle variabili senza puntatori:\na = %lf\nb = %hu\nc = %c\n\n><-><-><-><-><-><-><-><-><-><-><-><\n\n",a,b,c);
                break;
            }
            case 2:
            {
                double D[10];
                int A[10];
                case2_1(D,A);
                double *ptr_D=D;
                int *ptr_A=A;
                case2_2(A,D,ptr_D,ptr_A);
                break;
            }
            case 3:
            {
                int N=200;
                double V[N];
                //puntatore costante double: non modifica il valore della variabile puntata, può cambiare la variabile da puntare
                const double *ptr=V;
                //puntatore costante al tipo double: possibile cambiare il valore della variabile puntata ma non è possibile cambiare variabile da puntare  
                double *const ptr2=V;
                case3(V,ptr,ptr2);
                break;
            }
        }
        if(n==0)
        {
            cc=0;
        }
        else cc=menu1(); //tornare al menu si/no
        
        n=-1; //reset var menu di sicurezza
    }while(cc==1);
}