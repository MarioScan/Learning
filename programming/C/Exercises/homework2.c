/*
1)
H10.4
Codificare in linguaggio C un programma che produca la somma
dei numeri interi dispari da 1 a 99, facendo uso del co
strutto for. Dalla somma vanno esclusi i numeri divisibili per tre.

2)
H10.5
Codificare in linguaggio C un programma che stampi a ritroso
i numeri positivi pari minori o uguali a mille; inoltre le
iterazioni finiscono se la somma dei numeri precedentemente
stampati è maggiore o uguale a centomila.

3)
H10.6
Codificare in linguaggio C un programma che stampi a ritroso
la sequenza di caratteri da ’a’ a ’z’, ma non le vocali. Codifi
care due versioni differenti nelle quali si fa uso del costrutto
for e del costrutto while rispettivamente.

4)
H10.7
Estendere l’esercizio precedente in modo da conservare tutti i
caratteri in un array di caratteri. Infine, stampare la lunghez
za della stringa contenuta in esso con la funzione di libreria
strlen.

5)
H10.8
Codificare un programma che stampi le prime N potenze di 2,
dove N è un parametro scelto dall’utente (input da tastiera).

6)
Codificare un programma che chiede all’utente di inserire due
numeri decimali maggiori di zero e diversi tra loro (ES: 10.2
e 24.7), ed un numero intero N > 1. Quindi:

1) il programma calcola l’arrotondamento di entrambi i
numeri all’intero pi`u vicino, Siano a e b i due numeri
ottenuti, con a < b.
2) per ogni numero a ≤ p ≤ b, calcola e stampa la
somma degli N-1 numeri minori di p e la somma dei
2N numeri maggiori di p;

___________________________________________________________________
*/


/*
Esercizio n.1 )

H10.4
Codificare in linguaggio C un programma che produca la somma
dei numeri interi dispari da 1 a 99, facendo uso del costrutto
for. Dalla somma vanno esclusi i numeri divisibili per tre.

#include <stdio.h>
int main()
{
    int s=0;
    for(int i=1; i<100;i++)
    {
        if((i%2!=0) && (i%3!=0))
        {
            //printf("%d\n",i); eventuale controllo numerico 
            s+=i;
        }
    }
    printf("Somma: %d",s);
}

*/

/*
Esercizio n.2 )

H10.5
Codificare in linguaggio C un programma che stampi a ritroso
i numeri positivi pari minori o uguali a mille; inoltre le
iterazioni finiscono se la somma dei numeri precedentemente
stampati è maggiore o uguale a centomila.

#include <stdio.h>
int main()
{
    int s=0;
    for(int i=1000; i<=1000;i--)
    {
        if((i%2==0))
        {
            printf("%d\n",i);
            s+=i;

            if(s>=100000)
                break;
        }
    }
    printf("Somma: %d",s);
}

*/

/*

Esercizio n.3 )

H10.6
Codificare in linguaggio C un programma che stampi a ritroso
la sequenza di caratteri da ’a’ a ’z’, ma non le vocali. Codificare
due versioni differenti nelle quali si fa uso del costrutto
for e del costrutto while rispettivamente.

#include <stdio.h>
int main()
{
    // Versione con il costrutto FOR
    printf("Versione con for:\n");
    for (char c='z';c>='a';c--)
    {
        if(c!='a' && c!='e' && c!='i' && c!='o' && c!='u')
        {
            printf("%c\n",c);
        }
    }

    printf("Versione con while:\n");
    char c='z';
    while(c>='a')
    {
        if(c!='a' && c!='e' && c!='i' && c!='o' && c!='u')
        {
            printf("%c\n",c);
        }
        c--;
    }
}

*/

/*

Esercizio n.4 )

H10.7
Estendere l’esercizio precedente in modo da conservare tutti i
caratteri in un array di caratteri. Infine, stampare la lunghezza
della stringa contenuta in esso con la funzione di libreria
strlen.

#include <stdio.h>
#include <string.h>
int main()
{
    int i=0;
    char vet[30];
    // Versione con il costrutto FOR
    printf("Versione con for:\n");
    for (char c='z';c>='a';c--)
    {
        if(c!='a' && c!='e' && c!='i' && c!='o' && c!='u')
        {
            vet[i] = c;
            printf("%c\n",vet[i]);
            i++;
        }
    }
    vet[i]= '\0'; //termina stringa
    printf("vet: %s\nLunghezza stringa: %d",vet,strlen(vet));

}

*/

/*

Esercizio n.5 )

H10.8
Codificare un programma che stampi le prime N potenze di 2,
dove N è un parametro scelto dall’utente (input da tastiera).

#include <stdio.h>
#include <math.h>
int main()
{
    int n=0;
    int k=0;
    printf("Inserisci valore N: ");
    scanf( "%d" , &n);

    k=pow(2,n);
    printf("Risultato potenza di 2^%d: %d",n,k);

    return 0;
}

*/

/*

Esercizio n.6 )

Codificare un programma che chiede all’utente di inserire due
numeri decimali maggiori di zero e diversi tra loro (ES: 10.2
e 24.7), ed un numero intero N > 1. Quindi:

1) il programma calcola l’arrotondamento di entrambi i
numeri all’intero più vicino, Siano a e b i due numeri
ottenuti, con a < b.
2) per ogni numero a ≤ p ≤ b, calcola e stampa la
somma degli N-1 numeri minori di p e la somma dei
2N numeri maggiori di p;

*/

#include <stdio.h>
#include <math.h>
int main()
{
    double a,b;
    int n;

    //input
    do
    {
        printf("Inserisci primo numero decimale: ");
        scanf("%lf" ,&a);
        printf("Inserisci secondo numero decimale: ");
        scanf("%lf",&b);
        printf("Inserisci numero intero N:");
        scanf("%d",&n);

        if(a==b || a<0 || b<0 || n<1)
        {
            printf("________________________________\nValori non validi!\nI due numeri decimali devono essere maggiori di zero e non possono essere uguali.\nIl numero intero n deve essere maggiore di 1.\n________________________________\n\n"); 
        }
    }while(a==b || a<0 || b<0 || n<1);

    //arrotondamento al primo intero vicino
    a = round(a);
    b = round(b);

    //"Siano a e b i due numeri ottenuti, con a < b", verifica che a sia minore di b 
    if(a>b)
    {
        int temp;
        temp=a;
        a=b;
        b=temp;
    }

    //per ogni numero a ≤ p ≤ b, calcola e stampa la somma degli N-1 numeri minori di p

    for(int p=a;p<=b;p++)
    {
        //calcola somma N-1 numeri minori di p  
        int smin=0;
        if(p-n+1>0)
        {
            for(int i=p-n+1;i<p;i++)
            {
                smin+=i;
            }
        }
        int smag=0;
        for (int i=p+1;i<=p+2*n;i++)
        {
            smag+=i;
        }
        printf("Per p = %d, la somma dei numeri minori (%d) di p e': %d e la somma dei numeri maggiori (%d) di p e': %d\n",p,n-1,smin,2*n,smag);
    }
}


