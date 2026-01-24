#include <stdio.h>
#include <stdlib.h>

//Propotipo
void Fibo(int n1);

//Definizione
void Fibo(int n1)
{
    int a=0,b=1,r;

    for(int i=0;i<n1;i++)
    {
        if(i < 1)
            printf("Fibo(%d)\n", a);
        else if(i==1)
            printf("Fibo(%d)\n", b);
        else
        {
            printf("Fibo(%d) (%d + %d)\n", a + b, a, b);
            int temp = a; //salvo a in variabile temporanea
            a = b; //salvataggio secondo valore
            b = temp + b; //passo somma a b
        }
    }
}

int main(int argc, char *argv[])
{
    /*Nota: argc conta il numero di argomenti al momento della compilazione:
    argc = 0 --> non si avvia nemmeno il programma
    argc = 1 --> solo il nome del programma inserito come argomento (es: PS C:\Users\Mario\OneDrive\Desktop\Università\Programmazione 1\Programmi> ./homework8.exe )
    argc > 1 --> altri argomenti insieme al programma inseriti: (es. PS C:\Users\Mario\OneDrive\Desktop\Università\Programmazione 1\Programmi> ./homework8.exe 3)
        --> nome_programma + argomento ...
    argv[] contiene gli effettivi valori, argc è solo il contatore che distingue quanti arg sono stati inseriti in input...
    argv[0] --> nome del programma
    argv[1]...[2]...[3]...etc. --> valori, se presenti, degli eventuali argomenti dati in input  
    */
    int n;
    if(argc < 2)
    {
        printf("Nessun argomento inserito...\n");
        return -1;
    }
    else
    {
        n = atoi(argv[1]); //conversione da stringa a int...
        printf("Mostra la successione di Fibonacci per %d elementi:\n",n);
    }
    Fibo(n);
    
}