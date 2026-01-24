#include "menu.h" //menu
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//dichiarazione propotipo funzioni
short case1(short a,short b);
void case2(short a,short b, short unsigned *ris);
int case3(char a1[], char a2[]);
int case4(const char *stringa1, const char *stringa2);
int case5(char *a, int n);
int case6(int *a,int *b,int n);
void case7(int r,int c,int **a,double y);
void case8(int n,double **a, const double delta);
void case9(int n,int **a);
int case10(int n, int m, unsigned int **mat,unsigned short a, unsigned short b, double d);
//definizione delle funzioni
short case1(short a, short b)
{
    short prod = a*b; //long long può esprimere il valore massimo possibile di prodotto tra due short (-32768 e 32768) che equivale a |1073741824| superando i 32 bit di una variabile int
    return abs(prod); // la funzione "abs" (o "llabs" nel caso di long long) restituisce il valore assoluto di una variabile (dalla libreria stdlib.h)
}
//__________________________________________
void case2(short a,short b, short unsigned *ris) //viene creata una variabile puntatore short unsigned con con l'indirizzo alla variabile del case2 
{
    *ris = abs(a*b); //salva il risultato del prodotto nella variabile puntatore 
}
//__________________________________________
int case3(char a1[], char a2[])
{
    int n = strlen(a1);
    a1[n] = ' '; //aggiunge uno spazio tra i campi Nome e Cognome
    a1[n+1] = '\0'; //aggiungo terminatore di stringa
    
    char a3[n];
    strcpy(a3,a1); //copia a1 in a3
    strcat(a3,a2); //aggiunge a2 in a3 (incolla a2)
    printf("Unione delle due stringhe:\nNome: %s (%d caratteri)\nCognome: %s (%d caratteri)\nStringa unita in nuovo array: %s\n",a1,(strlen(a1)-1),a2,strlen(a2),a3);
    
    //n = strlen(a3);
    n=0; //reset contatore 
    //contatore lunghezza stringa
    while (a3[n] != '\0') 
    {
        n++;
    }
    return n;
}
//__________________________________________
int case4(const char *stringa1, const char *stringa2)
{
    int i=0,n=-2;
    //esercizio confronto in base ai valori ASCII, per il confronto alfabetico basta invertire i segni maggiore e minore.
    //funzioni per le stringhe:
    //strcmp --> case sensitive, oppure  strcasecmp --> case insensitive
    printf("Confronto tra due stringhe:\n1) %s\n2) %s\n\nMostra le lettere e il loro relativo valore ASCII.\n",stringa1,stringa2);
    for (i = 0; stringa1[i] != '\0' && stringa2[i] != '\0'; i++)
    {
        if(stringa1[i] < stringa2[i])
        {
            printf("%c < %c  (%d < %d)\n%s e' piu' grande.\n\n",stringa1[i],stringa2[i],stringa1[i],stringa2[i],stringa2);
            n = -1;
            return n;
        }
        else if(stringa1[i] > stringa2[i])
        {
            printf("%c > %c  (%d > %d)\n%s e' piu' grande.\n\n",stringa1[i],stringa2[i],stringa1[i],stringa2[i],stringa1);
            n = 1;
            return n;
        }
        else if(stringa1[i] == stringa2[i])
        {
            printf("%c == %c  (%d == %d)\n",stringa1[i],stringa2[i],stringa1[i],stringa2[i]);
        }
    }
    if (stringa1[i] == '\0' && stringa2[i] == '\0')
    {
        printf("Le stringhe sono uguali.\n\n");
        n = 0; //Le stringhe sono uguali.
    } 
    return n;
}
//__________________________________________
int case5(char *a, int n)
{
    srand(time(NULL));  // Inizializza il seme con il tempo corrente --> necessaria per ottenere risultati randomici differenti (il primo valore ottenuto era 'random' ma ad ogni esecuzione restituiva sempre lo stesso valore, nel mio caso: 'phqghumeay')
    int k=0;
    for(int i=0;i<n;i++)
    {
        *(a+i) = rand() % ('z'-'a'+1) + 'a';
        printf("%c\n",*(a+i));
        if(*(a+i) == 'a'  || *(a+i)=='e' || *(a+i)=='i' || *(a+i)=='o'||*(a+i)=='u')
        {
            k++;
        } //*(a+i) equivale a dire a[i]...
    }
    *(a+n) = '\0';
    printf("\nNuova stringa: %s\n",a);
    return k;
}
//__________________________________________
int case6(int *a,int *b,int n)
{
    srand(time(NULL));
    int cont=0;
    for(int i=0;i<n;i++)
    {
        *(a+i) = rand() % (100-1+1) + 1;
        *(b+i) = rand() % (100-1+1) + 1;
    }
    for(int i=0;i<n;i++)
    {
        printf("\n%d) Valore degli array (i = %d):\nA[%d] = %d\nB[%d] = %d\n",i,i,i,a[i],i,b[i]);
        if(b[i] != 0)
        {
            printf("B[%d] != 0, quindi:\n",i,b[i]);
            if(a[i]/b[i] < 1)
            {
                b[i] = a[i];
                a[i] = rand() % (200-100+1) + 100;
                printf("   A[i]/B[i] < 1:\n   B[%d] = A[%d] --> B[%d] = %d\n   A[%d] = %d (random [100-200])\n",i,i,i,b[i],i,a[i]);
            }
            else if(a[i]/b[i] > 1)
            {
                a[i] = b[i];
                b[i] = rand() % (100-0+1) + 0;
                printf("   A[i]/B[i] > 1:\n   A[%d] = B[%d] --> A[%d] = %d\n   B[%d] = %d (random [0-100])\n",i,i,i,a[i],i,b[i]);
            }
            else if(a[i]/b[i] == 1)
            {
                b[i] = a[i];
                a[i] = 0;
                printf("   A[i]/B[i] = 1:\n   B[%d] = A[%d] --> B[%d] = %d\n   A[%d] = 0\n",i,i,i,b[i],i,a[i]);
                cont++;
            }
        }
        printf("_______________\n");
    }
    return cont;
}
//__________________________________________
void case7(int r,int c,int **a,double y)
{
    double s=0;
    int count=0;
    srand(time(NULL));
    printf("\nValore della variabile da comparare 'y' = %.2f\nMatrice creata del tipo:\n",y);
    //creazione matrice con numeri compresi tra 1 a 100
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            a[i][j] = rand() % (100-1+1) + 1; // Valori casuali da 1 a 100
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    printf("\nColonne della matrice 'a' < = %.2f (y):\n__________________",y);
    printf("\n\n");
    for(int i=0;i<c;i++)
    {
        printf("Colonna n.%d)\n",i+1);
        for(int j=0;j<r;j++)
        {
            s += a[j][i];
            printf("%d --> " ,a[j][i]);
            printf("somma = %.2f\n",s);
        }

        printf("\nSomma elementi colonna n.%d: %.2f ",i+1,s);
        s=s/c;
        printf("--> media elementi: %.2f\n",s);
        if(s<=y)
        {
            count++;
            printf("Colonne: %d\n",i+1);
        }
        s=0;
        printf("\n");
    }
    printf("Le colonne con media aritmetica minore o uguale a y sono: %d\n__________________\n",count);
}
//__________________________________________
void case8(int n,double **a, const double delta)
{
    //Inizializzazione degli elementi della matrice (a(i_k)):
    srand(time(NULL));
    printf("Creazione e inizializzazione matrice con valori double compresi tra 1 e 20.\n");
    for(int i=0;i<n;i++)
    {
        printf("| ");
        for(int j=0;j<n;j++)
        {
            a[i][j] = (double)rand() / (double)RAND_MAX * (20.0 - 1.0) + 1.0; //[1.0 - 20] double
            printf("%.2f | ",a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    int count=0;
    for(int k=0;k<=n-1;k++) //k<n o k<=n-1 se volessimo seguire alla lettere l'esercizio...
    {
        double dk = a[n-k-1][k]; //partendo dall'angolo inferiore sinistro della matrice
        printf("%d) Diagonale secondaria: %.2f\n",k+1,dk);
        /* k=0 n=5,
        allora dk:
        k=0 --> [5-0-1][0] = [4][0] ; 
        k=1 --> [5-1-1][1] = [3][1] ; 
        k=2 --> [5-2-1][2] = [2][2] ; 
        k=3 --> [5-3-1][3] = [1][3] ;
        k=4 --> [5-4-1][4] = [0][4] . 
        */
       double somma=0;
       for(int i=0;i<n;i++)
       {
            printf("somma+=a[i][k] --> %.2f\n",a[i][k]);
            somma+=a[i][k];
       }
       somma /= n; //media
       double differenza = fabs(dk-somma);
       printf("Differenza --> media (%.2f) - dk (%.2f) = %.2f\n",somma,dk,differenza);
       if(differenza < delta)
       {
            printf("Espressione < delta trovata: colonna n.%d, differenza (%.2f) < delta (%.2f).\n",k+1,differenza,delta);
            count++;
       }
       else printf("Espressione > delta.\n");
       printf("\n");
    }
    printf("Numero di elementi la cui differenza assoluta sia minore di delta: %d\n",count);
}
//__________________________________________
void case9(int n,int **a)
{
    int dp[n], ds[n];
    double s1=0,s2=0;
    //Inizializzazione degli elementi della matrice: (preso da case8...)
    srand(time(NULL));
    printf("Creazione e inizializzazione matrice con valori int compresi tra 1 e 50.\n");
    for(int i=0;i<n;i++)
    {
        printf("| ");
        for(int j=0;j<n;j++)
        {
            a[i][j] = rand() % (50-1+1) + 1; //[1 - 50] int
            printf("%d | ",a[i][j]);
            //printf("[%d][%d] | ",i,j); //visualizza tabella
        }
        printf("\n");
    }
    printf("\n");

    //Calcolo differenza tra la media della diagonale principale e la diagonale secondaria:
    printf("Diagonale principale:\n");
    for(int i=0;i<=n-1;i++)
    {
        dp[i] = a[n-i-1][n-i-1]; //partendo dall'angolo inferiore destro della matrice
        s1+=dp[i];
        printf("%d\n",dp[i]);
    }
    printf("Diagonale secondaria:\n");
    for(int i=0;i<=n-1;i++)
    {
        ds[i] = a[n-i-1][i]; //partendo dall'angolo inferiore sinistro della matrice
        s2+=ds[i];
        printf("%d\n",ds[i]);
    }
    printf("Somma dei valori della diagonale principale: %.0f\n",s1);
    printf("Somma dei valori della diagonale secondaria: %.0f\n",s2);    
    printf("Media calcolata con: somma delle rispettive diagonali / n (%d).\n",n);
    s1/=n;
    s2/=n;
    double differenza = fabs(s1-s2);
    printf("Differenza: s1(%.2f) - s2(%.2f) = %.2f\n",s1,s2,differenza);
}
//__________________________________________
int case10(int n, int m, unsigned int **mat,unsigned short a, unsigned short b, double d)
{
    int count=0;
    double s=0;
    srand(time(NULL));
    printf("Creazione e inizializzazione matrice con valori interi senza segno compresi tra 1 e 10.\n");
    for(int i=0;i<n;i++)
    {
        printf("| ");
        for(int k=0;k<m;k++)
        {
            mat[i][k] = rand() % (10-1+1) + 1; //[1 - 10] int
            printf("%d | ",mat[i][k]);
        }
        printf("\n");
    }
    printf("\n");
    
    printf("Calcolo media degli elementi della matrice tra a e b...\n");
    printf("Elementi compresi tra a e b:\n");
    for(int i=0;i<n;i++)
    {
        printf("Colonna n.%d:\n",i+1);
        s=0;
        for(int k=0;k<=b;k++)
        {
            printf("%d | ",mat[i][k]);
            s+=mat[i][k];
        }
        s/=b;
        if(s<d)
        {
            count++;
            printf("Media < delta, numero incrementato: media (%.2f) < delta (%.2f).\n",s,d);
        }
        else printf("Media > delta, numero invariato: media (%.2f) > delta (%.2f).\n",s,d);
    }

    return count;

}
//__________________________________________
int main()
{
    int n,cc=-1 ;
    do
    {
        char indice_menu[] = "1) 15.1\n2) 15.2\n3) 15.3\n4) 15.4\n5) 15.5\n6) 15.6\n7) 15.7\n8) 15.8\n9) 15.9\n10) 15.10\n";
        int n_esercizi = 10;
        n = menu(indice_menu,n_esercizi); //Benvenuto nel menu'
        switch(n)
        {
            case 0:
            {
                printf("Terminazione del programma... A presto!\n\n><-><-><-><-><-><-><-><-><-><-><-><\n\n");
                break;
            }
            case 1:
            {
                short a = -12;
                short b = 2;
                printf("Esercizio 1:\nSeguendo la traccia:\n'Funzione in C che prende in input una coppia di interi short con segno e restituisca il valore assoluto del prodotto di tali interi.'\n");
                printf("\nRisultato del prodotto assoluto delle due variabili short a e b, in cui:\na = %d\nb = %d\nProdotto assoluto = %lld\n",a,b,case1(a,b));
                break;
            }
            case 2:
            {
                short a = -40;
                short b = 3;
                short unsigned x; //variabile short unsigned
                case2(a,b,&x); //viene mandato l'indirizzo della variabile short unsigned
                printf("Esercizio 2:\nSeguendo la traccia:\nFunzione in C che prende, oltre a una coppia di interi short, anche un puntatore ad un numero short unsigned.\nLa funzione dovra' scrivere il risultato della computazione nella locazione di memoria rappresentata dal puntatore in input. La funzione non avra' alcun tipo di ritorno.\n");
                printf("\nRisultato del prodotto assoluto delle due variabili short a e b, in cui:\na = %d\nb = %d\nRisultato del prodotto assoluto puntato dalla variabile short unsigned x = %d\nVerifica prodotto con esercizio precedente: |a*b| = %d",a,b,x,case1(a,b));
                break;
            }
            case 3:
            {
                char nome[] = "Albano";
                char cognome[] = "Celentano";
                printf("Esercizio 3:\nSeguendo la traccia:\nFunzione in C che prenda in input un array Nome e un array Cognome e li unisca nell'array Persona.\nTale funzione dovra' restituire la lunghezza della stringa.\n\n");
                printf("Lunghezza stringa di %d caratteri.\nNota: la lunghezza stringa comprende lo spazio tra nome e cognome (somma delle due stringhe + 1 carattere spazio).\n",case3(nome,cognome));
                break;
            }
            case 4:
            {
                /* Il simbolo “&” per ottenere l’indirizzo di una variabile, che è utile quando vogliamo passare l’indirizzo di una variabile a una funzione
                (ad esempio, quando vogliamo che la funzione modifichi il valore della variabile originale). 
                Tuttavia, nel caso degli array, non abbiamo bisogno di farlo perché il nome dell’array è già un puntatore al primo elemento dell’array.
                */
                char s1[] = "Pippo";
                char s2[] = "Pippo";
                printf("Esercizio 4:\nSeguendo la traccia:\nFunzione in C che prenda in input due array di caratteri.\nLa funzione restituisca un risultato intero che rappresenta il confronto lessicografico tra le due stringhe.\n\n");
                printf("Comparazione delle due stringhe:\n-1 se s1 < s2;\n1 se s1 > s2;\n0 se s1 = s2.\nRisultato: %d\n",case4(s1,s2));
                break;
            }
            case 5:
            {
                printf("Esercizio 5:\nSeguendo la traccia:\nFunzione C che prenda in input un array di caratteri ed un parametro che indica la sua lunghezza.\nLa funzione dovra' riempire l'array di caratteri con caratteri pseudo-casuali nell'intervallo [a-z].\nLa funzione dovra' restituire il numero di vocali all'interno della stringa.\n\n");
                printf("Stringa di default per questo esempio composta da dieci '-' simboli.\n");
                char array[] = {'-','-','-','-','-','-','-','-','-','-','\0'};
                printf("Stringa di default: %s\n",array);
                printf("Numero vocali all'interno della stringa generata: %d\n",case5(array,strlen(array)));
                break;
            }
            case 6: 
            {
                printf("Esercizio 6:\nSeguendo la traccia:\nCodificare una funzione che prenda in input due array di interi A e B di eguale lunghezza, ed un parametro formale che indichi la lunghezza stessa degli array.\nTale funzione dovra' operare nel seguente modo (solo se bi != 0):\n1) Se ai/bi < 1, allora:\n     i) pone bi = ai;\n       ii) scrive nella cella ai un numero pseudo-casuale nel range [100,200];\n2) Se ai/bi > 1, allora pone:\n     i) ai = bi;\n       ii) scrive nella cella bi un numero pseudo-casuale nel range [0,100];\n3) Se ai/bi = 1, allora:\n     i) pone bi = ai;\n       ii) scrive nella cella ai il numero 0.\nLa funzione restituisca il numero di volte in cui ai/bi = 1\n\n");
                int n = 6;
                int A[n] /*= {1,2,3,4,5,6}*/,B[n] /*= {7,8,9,10,11,12}*/;
                printf("\nRisultato: %d", case6(A,B,n));
                break;
            }
            case 7:
            {
                printf("Esercizio 7:\nSeguendo la traccia:\nCodificare una funzione in C che prenda in input un array bidimensionale di dimensioni N x M di interi, ovvero una matrice, ed un numero double y.\nLa funzione restituisca il numero di colonne della matrice che soddisfano il seguente requisito:\n - La media aritmetica degli elementi della colonna stessa sia minore o uguale ad y.\n--> Testare la funzione mediante la codifica di una funzione main() nella quale si dichiari (allocazione automatica) un un array bidimensionale di dimensioni a piacimento. Riempire tale matrice con elementi pseudo-casuali in un range a piacere.\n");
                int N = 5, M = 4;
                double y = 65.14;
                
                //allocazione dinamica
                int **a = (int **)malloc(N * sizeof(int *));
                for (int i = 0; i < N; i++) 
                {
                    a[i] = (int *)malloc(M * sizeof(int));
                }
                case7(N,M,a,y);
                
                //deallocazione dinamica
                for (int i = 0; i < N; i++) 
                {
                    free(a[i]);
                }
                free(a);

                break;
            }
            case 8:
            {
                printf("Esercizio 8:\nSeguendo la traccia:\nCodificare una funzione in C che prenda in input un array bidimensionale A di dimensioni n x n di double, ovvero una matrice quadrata, ed un parametro formale in virgola mobile (delta).\nLa funzione restituisca il numero di elementi della diagonale secondaria tali che (vedi espressione pdf n.15, H15.8):\nDove per dk si intende l'elemento della diagonale secondaria appartenente alla colonna di indice k, e aik rappresenta il generico elemento della matrice stessa.\n");
                const double delta = 2.23;
                int n = 5;

                //allocazione dinamica della matrice
                double **A = (double **)malloc(n*sizeof(double *));
                for(int i=0;i<n;i++) 
                {
                    A[i] = (double *)malloc(n*sizeof(double));
                }

                /* Note sull'allocazione dinamica:
                1. double **A = (double **)malloc(n * sizeof(double *)); 
                  In questa riga viene allocata la memoria per un array di puntatori a double.
                  Ogni puntatore in questo array punterà ad un altro array di double, creando così una matrice. 
                  La funzione malloc() alloca un numero n di blocchi di memoria, ognuno dalla dimensione di un puntatore a double, uso di sizeof(double *). 
                  Il risultato è un puntatore a un puntatore a double (double **), che viene assegnato alla variabile A. 

                2. for(int i=0;i<N;i++) 
                  Serve a iterare il passaggio 1 su ogni elemento dell’array di puntatori a double.

                3. A[i] = (double *)malloc(n * sizeof(double));  
                  Alloca un numero n di blocchi di memoria, ognuno della dimensione di un double (sizeof(double)), 
                  e assegna il puntatore al primo blocco al puntatore corrente nell’array A.
                  In pratica, ciò crea un array di double per ogni puntatore nell’array A, risultando in una matrice bidimensionale.

                In pratica, viene creata una matrice bidimensionale di double con n righe e n colonne.
                Importante: 
                Liberare la memoria allocata con malloc quando non più utile, utilizzando la funzione free(), per evitare perdite di memoria.
                In questo caso, per esempio, bisognerebbe liberare prima ogni A[i], poi A stesso.
                */

                case8(n,A,delta);

                //deallocazione della matrice / liberazione della memoria
                for(int i=0; i<n; i++)
                {
                    free(A[i]);
                }
                free(A);
                //importante liberare prima il contenuto della matrice (es. A[i]) e poi il puntatore alla matrice stesso (es. A).
                break;
            }
            case 9:
            {
                printf("Esercizio 9:\nSeguendo la traccia:\nCodificare una funzione in C che prenda in input un array bidimensionale di dimensioni n x n di interi, ovvero una matrice quadrata.\nLa funzione restituisca la differenza, in valore assoluto, tra la media aritmetica degli elementi della diagonale principale, e la media aritmetica degli elementi della diagonale secondaria.\n");
                int n = 5;
                //allocazione dinamica
                int **m = (int **)malloc(n * sizeof(int *));
                for (int i = 0; i < n; i++) 
                {
                    m[i] = (int *)malloc(n * sizeof(int));
                }
                case9(n,m);
                //deallocazione memoria                
                for(int i=0; i<n; i++)
                {
                    free(m[i]);
                }
                free(m);
                
                break;
            }
            case 10:
            {
                printf("Esercizio 10:\nSeguendo la traccia:\nCodificare una funzione in C che prenda in input un array bidimensionale di dimensioni n x m di interi senza segno, due short unsigned mobile a e b (si assuma 0 ≤ a < b ≤ n), ed un terzo parametro in virgola mobile delta.\nLa funzione restituisca il numero di righe della matrice per cui vale la seguente proprieta': la media aritmetica degli elementi aik (i rappresenta l'indice della generica riga) tali che a ≤ k ≤ b e' un numero minore di delta.\n");
                //si assuma che 0 <= a < b <= n 
                int n = 3, m = 4;
                unsigned short a = 1, b = 3;
                double delta = 6.71;

                unsigned int **matrice = (unsigned int **)malloc(n * sizeof(unsigned int *));
                for (int i = 0; i < n; i++) 
                {
                    matrice[i] = (unsigned int *)malloc(m * sizeof(unsigned int));
                }

                printf("Righe la cui media e' minore di delta: %d\n",case10(n,m,matrice,a,b,delta));

                for(int i=0; i<n; i++)
                {
                    free(matrice[i]);
                }
                free(matrice);
            }
        }
        if(n==0)
        {
            cc=0;
        }
        else cc=menu1(); //tornare al menu si/no
        
        n=-1; //reset var menu di sicurezza
    }while(cc==1);
    //prova();
    
}