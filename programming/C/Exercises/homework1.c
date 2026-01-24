/*
 Un falegname realizza scaffali in legno per ambienti interni o
 esterni. I clienti si recano presso il suo laboratorio con alcune
 richieste (input) in base alle quali il falegname opera alcune
 scelte:
 1. ambiente: esterno o interno
 2. carico massimo (in kg) che il singolo ripiano deve essere
 in grado di sopportare;
 3. lunghezza in metri di ogni ripiano;

 Il falegname dovrà operare nel modo seguente:
 1. Se lo scaffale va sistemato all’esterno allora va impiegato
 legno di castagno, altrimenti legno di pino;

 2. lo spessore di ogni ripiano va calcolato in base alla
 formula S = [B + max(0,L−1)×P]×Q, dove:
    (*) L è la lunghezza (in metri) di ogni ripiano fornita dal
    cliente;

    (*) B = 0.018 metri se si usa il castagno, B = 0.02 metri
    se si usa il pino;

    (*) P = 0.02 per il castagno, P = 0.022 per il pino

    (*) Q = 1.1 se il legno scelto è il castagno e se il
    massimo carico che il singolo ripiano deve supportare
    è maggiore di 100 kg, altrimenti Q = 1.0;

    (*) Q = 1.2 se il legno scelto è il pino e se il carico
    massimo che il singolo ripiano deve supportare è
    maggiore di 80kg, altrimenti Q = 1.0

 Descrivere una soluzione del problema tale che, dati in input i
 parametri ambiente, lunghezza L e carico massimo del singolo
 ripiano dello scaffale, produca in output:
    (*) essenza da usare (pino o castagno)
    (*) spessore ripiani.
 In particolare:
 1. Realizzare un diagramma di flusso (o a blocchi) per la
 risoluzione del problema del falegname;
 2. Codificare in C un programma che si base sul diagramma
 di flusso realizzato per il punto precedente;

 3. Impiegare la tecnica di hand tracing per verificare il
 funzionamento del programma per i seguenti input:
    a) Carico max 80kg, scaffale non destinato all’esterno,
     lunghezza ripiani 150cm;
    b) Carico max 100kg, scaffale destinato all’esterno,
    lunghezza ripiani 100cm;
    c) Carico max 120kg, scaffale non destinato all’esterno,
    lunghezza ripiani 100cm;
*/


#include <stdio.h>
#include <math.h>
#include <string.h>
int main()
{
    float L = 0; //lunghezza max ripiano
    float carico_max = 0; //carico max ripiano
    int ambiente; //0 interno, 1 esterno
    char scaffale[20] = ""; // pino o castano, inizializzata poi nel ciclo if (fase 2)
    float S = 0; //spessore ripiano
    float B = 0;
    float P = 0;
    double Q = 0;

    //1) Fase input -->

    printf("Inserisci lunghezza massima del ripiano: ");
    scanf("%f", &L);

    printf("Inserisci carico massimo del ripiano: ");
    scanf("%f", &carico_max);

    do
    {
        printf("Digita il numero 0 o 1 per indicare l'ambiente in cui usare gli scaffali:\n0) Interno;\n1) Esterno.\nInserisci uno dei valori indicati: ");
        scanf("%d", &ambiente);
        if(ambiente  != 0 && ambiente != 1)
        {
            printf("Valore non valido!\nUtilizza uno dei due valori indicati:\n0) Interno;\n1) Esterno.\n");
        }
    }while(ambiente  != 0 && ambiente != 1);

    //2) elaborazione dei dati presi in input -->

    if(ambiente == 0) //interno
    {
        strcpy(scaffale, "legno_pino");
        B = 0.02;
        P = 0.022;
        if(carico_max > 80)
        {    
            Q = 1.1;
        }
        else Q = 1.0; //minore di 80
    }
    else
    {
        strcpy(scaffale, "legno_castagno");
        B = 0.018;
        P = 0.02;
        if(carico_max > 100)
        {
            Q = 1.1;
        }
        else Q = 1.0; //minore di 100
    }

    S = (B + fmax(0, L - 1) * P) * Q; 

    //3) Fine elaborazione, output dei risultati -->

    printf("\nIl materiale usato e': %s\n",scaffale);
    printf("Lo spessore del ripiano e' di: %f\n\n", S); 

}