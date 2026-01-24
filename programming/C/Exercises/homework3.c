/*

Esercizio n.1)

Codificare un programma in linguaggio C nel quale si iteri un numero
indefinito di volte la moltiplicazione di un numero in virgola mobile y > 0
per un altro numero in virgola mobile x < 1: y ← y ∗x.
Ad ogni iterazione si stampi il risultato della moltiplicazione.
L’algoritmo deve terminare quando si verifica la condizione di underflow,
ovvero il risultato viene approssimato con lo zero.
Codificare l’algoritmo anche con un numero di partenza y < 0, stampare
il risultato finale (lo 0 “negativo”).
Stampare i risultati in notazione scientifica.

__________________________________________________________________________________

Esercizio n.2)


Codificare un programma in linguaggio C nel quale si iteri un
numero indefinito di volte la divisione di di un numero in virgola
mobile y > 1 per un altro numero in virgola mobile x < 1:
y ←y/x.
Ad ogni iterazione si stampi il risultato della moltiplicazione.
L’algoritmo deve terminare quando si verifica la condizione di
overflow, ovvero il risultato viene approssimato con il simbolo INF.

__________________________________________________________________________________

Esercizio n.3)

Codificare un programma che provi a stampare il risultato delle
seguenti operazioni:
1) 2.0/0;
2) 2/0;
Qual è la differenza tra la prima e la seconda operazione? Spiegare
il perchè del comportamento differente del programma nei due casi.

__________________________________________________________________________________

Esercizio n.4)

Codificare un programma in linguaggio C nel quale si chieda
all’utente di inserire due interi (a e b) da tastiera.
Il programma dovr` a poi stampare la somma, la media, ed il max
tra i due numeri.
Tutti gli output del programma dovranno essere in notazione
scientifica, con una precisione di 4 cifre dopo la virgola

*/


#include <stdio.h>
#include <math.h>
#include <float.h>
#include <string.h>
int  main() 
{   
    int numero_esercizio=-1;
    do
    {
    printf("Inserisci numero esercizio da eseguire (1-10): ");
    scanf("%d", &numero_esercizio);
    }while(numero_esercizio < 1 || numero_esercizio > 10);
    fflush(stdin);

    switch(numero_esercizio)
    {
        case 1:
            {
                //Esercizio n.1)

                float y = 0.80; //y > 0
                float x = 0.93; //x < 1

                //stampa valore iniziale di y in notazione scientifica
                printf("Valore iniziale di y: %.2e\n",y); 

                 while (1) 
                // notazione scientifica di 0.0000000001, numero così piccolo che permette a y
                // di essere approssimato a 0 (fenomeno di "Underflow"), 
                // il loop sarebbe sbagliato se ci fosse stato y>=0
                // poiché sarebbe divenuto un loop infinito, in quanto la moltiplicazione
                // di un numero positivo per un numero minore di uno renderà il numero
                // sempre più piccolo ma mai un numero pari a 0 o negativo
                {
                    y *= x;
                    printf("y = %.2e || Risultato in valore decimale: %f\n",y,y);  //stampa valore di y in notazione scientifica
                
                    if(y < 1e-10) //altro metodo, ma prende molti più numeri dopo che il valore è stato già arrotondato per 0... (fpclassify(y) == FP_SUBNORMAL)
                    {
                        printf("\n_______________\nRisultato finale di y in notazione scientifica: %.2e\nRisultato in valore decimale: %f\n",y,y);
                        fflush(stdin);
                        break;       
                    }    
                }
                break;                    
            }

        case 2:
            {
                //Esercizio n.2)

                float y = 10.02; //y > 1
                float x = 0.97; //x < 1

                
                while(1)
                {
                    y /= x; //y←y/x
                    printf("y = %.2e || Risultato in valore decimale: %f\n",y,y);  //stampa valore di y in notazione scientifica

                    if(isinf(y))
                    {
                        printf("\n_______________\nRisultato finale di y in notazione scientifica: %.2e\nRisultato in valore decimale: %f\n",y,y);
                        fflush(stdin);
                        break;                        
                    }
                }
                break;    
            }
        
        case 3:
        {
        /*
        Codificare un programma che provi a stampare il risultato delle
        seguenti operazioni:
        1) 2.0/0;
        2) 2/0;
        Qual è la differenza tra la prima e la seconda operazione? Spiegare
        il perchè del comportamento differente del programma nei due casi.
        
        
        double x = 2.0/0;
        int y = 2/0;
        printf("\n1) Prima operazione: 2.0/0 = %f\n",x/0);
        printf("2)Seconda operazione: 2/0 = %f\n",y/0);
        
        
        In linguaggio C, la differenza tra la divisione di 2.0 / 0 e 2 / 0 riguarda 
        il tipo di dati utilizzato per la divisione e il comportamento risultante:

        Primo caso:
        2.0 / 0:
        In questa espressione, 2.0 è un valore letterale in virgola mobile (di tipo double).
        Quando si divide 2.0 per 0, il risultato è “infinito positivo” (rappresentato come “inf”).
        Questo è definito comportamento in virgola mobile.

        Secondo caso:
        2 / 0:
        In questa espressione, 2 è un valore letterale intero (di tipo int).
        Quando si divide 2 per 0, si verifica un comportamento indefinito.
        Questo significa che il risultato non è definito e potrebbe comportarsi in modi imprevedibili.
        */
        break;
        }

        case 4:
        {
            /*
            Codificare un programma in linguaggio C nel quale si chieda
            all’utente di inserire due interi (a e b) da tastiera.
            Il programma dovrà poi stampare la somma, la media, ed il max
            tra i due numeri.
            Tutti gli output del programma dovranno essere in notazione
            scientifica, con una precisione di 4 cifre dopo la virgola
            */
            
            int a,b;
            printf("Inserisci il primo numero (a):\n");
            scanf("%d",&a);
            printf("Inserisci  il secondo numero (b):\n");
            scanf("%d",&b);
            fflush(stdin);
            
            int max = ((a > b) ? a : b); 
            double media = ((a+b)/2);
            printf("Somma dei due numeri: %.4e\nMedia dei due numeri: %.4e\nMax tra i due numeri: %.4e\n\n",a+b,media,max);
            printf("Somma dei due numeri: %d\nMedia dei due numeri: %f\nMax tra i due numeri: %d\n\n",a+b,media,max);
            break;
        }
       
       case 5:
        {
            /*
            Codificare un programma in linguaggio C che chieda all’utente di
            inserire tre numeri da tastiera. L’utente può inserire numeri interi o
            decimali.
            Il programma dovrà stampare, per ogni numero in input,
            l’arrotondamento al valore intero più vicino

                Nota:
                Dall'esercizio della lezione scorsa, 
                per l'arrotondamento al primo intero vicino:
                a = round(a);
                b = round(b);
                */

            double x,y,z;
            printf("Inserisci primo numero (x):\n");
            scanf("%lf", &x);
            printf("Inserisci primo numero (y):\n");
            scanf("%lf", &y);
            printf("Inserisci primo numero (z):\n");
            scanf("%lf", &z);
            fflush(stdin);
            
            x = round(x);
            y = round(y);
            z = round(z);

            printf("Numeri arrotondati al valore intero piu' vicino:\nx: %.1f;\ny: %.1f;\nz: %.1f;\n\n", x, y, z);

        break;
        }

        case 6:
        {
            /*
            Codificare un programma in linguaggio C che chieda all’utente
            di inserire da tastiera il proprio nome e cognome.
            Successivamente il programma dovrà stampare le seguenti
            informazioni:

            1. il primo e l’ultimo carattere del nome, il secondo ed il
            terzo carattere del cognome.

            2. una stringa formata da tutti i caratteri che sono presenti
            sia nel nome che nel cognome. 
            Esempio: se nome=”Mario”, cognome= ”Rossi” l'output sarà ”io”

            3. le seguenti ulteriori informazioni:

            a) un messaggio che comunica all’utente se la prima
            lettera del nome è uguale all’ultima lettera del
            cognome.
            b) un messaggio che comunica all’utente se il numero di
            caratteri del nome è uguale al numero di caratteri del
            cognome.
            c) il numero di consonanti del nome e del cognome.
            */

            char  nome[20], cognome[20], charcomuni[20] = "", var='A';
            printf("_______________________________________________________________\n");
            printf("\nInserisci nome utente:\n");
            scanf("%s",nome);
            printf("Inserisci cognome utente:\n");
            scanf("%s",cognome);
            printf("_______________________________________________________________\n");
            int lnome = strlen(nome);
            int lcog = strlen(cognome);
            int cons_nome=0, cons_cog=0;

            //punto 1 --------------------------------------------------------------------
            printf("\nPunto 1)\nPrimo e ultimo carattere del nome: %s\n1) %c\n2) %c\n",nome,nome[0],nome[lnome-1]);
            printf("Secondo e terzo carattere del cognome: %s\n1) %c\n2) %c\n",cognome,cognome[1] ,cognome[2]);
            fflush(stdin);
            printf("_______________________________________________________________\n");
            //punto 2 --------------------------------------------------------------------
            for (int i = 0; i < lnome; i++) 
            {
                for (int j = 0; j < lcog; j++) 
                {
                    if (nome[i] == cognome[j]) 
                    {
                        strncat(charcomuni, &nome[i], 1);
                        break;
                    }
                }
            }

            if(strlen(charcomuni)>=1)
            {
                printf("\nPunto 2)\nCaratteri in comune:\n%s\n\n",charcomuni);
            }else printf("\nPunto 2)\nNon ci sono caratteri in comune.");
            fflush(stdin);
            printf("_______________________________________________________________\n");
            //punto 3-A --------------------------------------------------------------------
            if(nome[0] == cognome[lcog-1])
            {
            printf("\nPunto 3-A)\nLa prima lettera del nome e' uguale all'ultima lettera  del cognome.\nNome: %s\nCognome: %s\nLettere comuni: '%c' e '%c'\n\n",nome,cognome,nome[0],cognome[lcog-1]);
            }else printf("\nPunto 3-A)\nLa prima lettera del nome NON coincide con l'ultima lettera  del cognome.\nNome: %s\nCognome: %s\n\n",nome,cognome);
            printf("_______________________________________________________________\n");

            //punto 3-B --------------------------------------------------------------------
            if(lnome == lcog)
            {
                printf("\nPunto 3-B)\nNome e cognome hanno lo stesso numero di lettere:\nNome: %s --> %d\nCognome: %s --> %d\n\n",nome,lnome,cognome,lcog);
            }
            else printf("\nPunto 3-B)\nNome e cognome NON hanno lo stesso numero di lettere:\nNome: %s --> %d\nCognome: %s --> %d\n\n",nome,lnome,cognome,lcog);
            fflush(stdin);
            printf("_______________________________________________________________\n");

            //punto 3-C --------------------------------------------------------------------
            //n consonanti nome
            for(int i = 0;i<lnome;i++)
            {
                var = 'A';
                while(var <= 'z')
                {
                    if (var != 'A' && var != 'E' && var != 'I' && var != 'O' && var != 'U' && var != 'a' && var != 'e' && var != 'i' && var != 'o' && var != 'u')
                    {
                        if(nome[i] == var)
                        {
                            cons_nome++;
                        }
                    }
                    var++;            
                }
            }
            fflush(stdin);
            //n consonanti cognome
            for(int i = 0;i<lcog;i++)
            {
                var = 'A';
                while(var <= 'z')
                {
                    if (var != 'A' && var != 'E' && var != 'I' && var != 'O' && var != 'U' && var != 'a' && var != 'e' && var != 'i' && var != 'o' && var != 'u')                    
                    {
                        if(cognome[i] == var)
                        {
                            cons_cog++;
                        }
                    }
                    var++;                  
                }
            }
            printf("\nNumero consonanti:\nNome: %d\nCognome: %d\n\n",cons_nome,cons_cog);
            fflush(stdin);
            printf("_______________________________________________________________\n");
            //--------------------------------------------------------------------
    
            break;
        }
        
        case 7:
        {
            /*
            Codificare un programma in linguaggio C che calcoli e stampi
            l’ipotenusa di un triangolo rettangolo.
            L’utente dovrà inserire i due cateti a e b da tastiera.
            Il programma dovrà controllare che i valori inseriti siano positivi.
            */

           double i,a,b;
            printf("\n_______________________________________________________________\n");

            do
            {
                printf("Inserisci primo cateto (a):\n");
                scanf("%lf",&a);
                printf("Inserisci secondo cateto (b):\n");
                scanf("%lf",&b);
                //controllo se i valori sono positivi 
            }while(a<=0 || b<=0);

            i=sqrt(pow(a,2) + pow(b,2));
            
            printf("Ipotenusa = %lf\n",i);
            fflush(stdin);
            printf("_______________________________________________________________\n");
            break;
        }

        case  8:
        {
            /*
            Codificare un programma in linguaggio C che chieda all’utente di
            inserire il raggio di un cerchio.
            Il programma dovrà calcolare e stampare l’area e la circonferenza
            del cerchio.
            */
            printf("\n_______________________________________________________________\n");
            
            double r,a,c;
            const double Pi = 3.14159265358979323846;
            /*
            Il Pi greco si puo' inserire come costante tramite define o variabile "const"
            altrimenti, si puo' usare la funzione della libreria <math.h> "acos(-1)"
            */
            printf("Inserisci il raggio del cerchio:\n");
            scanf("%lf",&r);
            //formula area = A = Pi * (raggio^2)
            a = Pi * (pow(r,2));
            //formula circonferenza = C = 2 * Pi * raggio
            c = 2 * Pi * r;

            printf("Risultato:\nDal raggio del cerchio: %lf, si e' ricavato:\nArea del cerchio: %lf\nCirconferenza: %lf\n",r,a,c);
            break;
        }

        case 9:
        {
            /*
            Parte 1)
                Scrivere un programma in C finalizzato al calcolo dei valori di dosaggio
                per la ricetta di un dolce.
                Il programma chiede all’utente di inserire un numero compreso tra 2 e 16
                che rappresenta il numero di persone che mangeranno il dolce.
                Il programma chiede all’utente di inserire un valore che indica se tra i
                commensali ci sono diabetici.
            Parte 2)
                Il programma calcola il dosaggio nel seguente modo:
                
                A) dosaggio “base”, per un numero di persone compreso tra 2 e 4
                (estremi inclusi): 0.3kg di farina, 4 uova, 0.1kg di zucchero.

                B) dosaggio “medio”, per un numero di persone compreso tra 5 e 8
                (estremi inclusi). 2 volte e mezzo il dosaggio base per la farina e le
                uova, 1 volta e mezzo il dosaggio base di zucchero.
                
                C) dosaggio “grande”, per un numero di persone compreso tra 9 e 16
                (estremi inclusi): in questo caso il dosaggio andrà calcolato come la
                somma dei dosaggi dei due casi precedenti (medio e base).
            Parte 3) 
                Inoltre:
                • se ci sono diabetici tra i commensali, usare il fruttosio al posto dello
                zucchero, e la dose sarà la seguente:
                dosaggio Fruttosio = 2/3 × dosaggio Zucchero.
                • il numero di uova va arrotondato sempre per eccesso (es: 2.1 → 3,
                2.9 → 3, 9.45 → 10).
            */

            int  n_persone = 0;
            int control = -1;
            bool diabetici = false;
            char risposta[5];
            
            //parte 1:
            printf("\n_______________________________________________________________\n");
            do
            {
                printf("\nInserisci numero persone da 2 a 16:\n");
                scanf("%d", &n_persone);
                if(n_persone <2  || n_persone > 16)
                {
                    printf("Inserisci un valore valido!");
                }
            }while(n_persone <2  || n_persone > 16);
           printf("Numero persone inserito: %d\n",n_persone); //controllo

           do
           {
                printf("Sono presenti persone diabetiche?\nSi / No : ");
                scanf("%s",risposta);
                if(strcmp(risposta,"si")==0 || strcmp(risposta,"SI")==0  || strcmp(risposta,"Si")==0 || strcmp(risposta,"sI")==0)
                {
                    diabetici=true;
                    control = 1;
                    printf("Sono presenti persone diabetiche.\n");
                }
                else if(strcmp(risposta,"no")==0 || strcmp(risposta,"NO")==0  || strcmp(risposta,"No")==0 || strcmp(risposta,"nO")==0)
                {
                    diabetici=false;
                    control = 1;
                    printf("Non sono presenti persone diabetiche.\n");
                }
                else control = -1;

                if(control == -1)
                {
                    printf("Inserisci un valore valido!\n");
                }
           }while(control == -1);

            
            printf("\n_______________________________________________________________\n");
            
//parte 2:

            int dosaggio;
            double farina = 0.3, uova = 4.0, zucchero = diabetici ? 0.1 * 2 / 3 : 0.1;
            
            /*A) dosaggio “base”, per un numero di persone compreso tra 2 e 4
            (estremi inclusi): 0.3kg di farina, 4 uova, 0.1kg di zucchero.*/
            if(n_persone >=2 &&  n_persone <=4)
            {
                dosaggio = 0;

            }
            /*B) dosaggio “medio”, per un numero di persone compreso tra 5 e 8
            (estremi inclusi). 2 volte e mezzo il dosaggio base per la farina e le
            uova, 1 volta e mezzo il dosaggio base di zucchero.*/
            else if(n_persone >=5 && n_persone <=8)
            {
                dosaggio = 1;
            }
            /*C) dosaggio “grande”, per un numero di persone compreso tra 9 e 16
            (estremi inclusi): in questo caso il dosaggio andrà calcolato come la
            somma dei dosaggi dei due casi precedenti (medio e base).*/
            else if(n_persone >=9 && n_persone <=16)
            {
                dosaggio = 2;

            }
            
            //valori in base al dosaggio:
            if(dosaggio == 0)
            {
                //valori invariati
            }
            if(dosaggio == 1)
            {
                farina *= 2.5;
                uova = ceil(uova * 2.5);
                zucchero *= 1.5;
            }
            else if(dosaggio == 2)
            {
                farina += (farina*2.5);
                uova += ceil(uova * 2.5);
                zucchero += (zucchero*1.5);
            }


            //stampa ricetta con il dosaggio selezionato
            printf("\nRicetta per %d persone, dosaggio ", n_persone);
            if(dosaggio == 0)
            {
                printf("base");
            }
            else if(dosaggio == 1)
            {
                printf("medio");
            }
            else if(dosaggio == 2)
            { 
                printf("grande");
            }
            printf("\n");
            if(diabetici == true)
            {
                printf("Tra i partecipanti sono presenti persone diabetiche, quindi e' stato utilizzato il fruttosio al posto del normale zucchero.\n");
            }
            printf("\nFarina: %.2f kg\nUova: %d\nZucchero: %.2f kg\n\n",farina,(int)uova,zucchero);

            break;
        }

        case 10:
        {
            /*
            Tre vasche A, B e C raccolgono acqua da 15 tubi differenti.
            • La vasca A riceve l’acqua convogliata nei tubi 1,5,6,10.
            • La vasca B riceve l’acqua convogliata nei tubi da 2 a 4 e da 7 a 9.
            • La vasca C riceve l’acqua convogliata nei rimanenti tubi.
            Inoltre, i tubi con numero dispari hanno una portata di 60 litri al
            minuto, mentre quelli con numero pari hanno una portata di 120
            litri al minuto.

            Codificare un programma in linguaggio C che esegua le seguenti
            operazioni:
            • il programma chiede in input all’utente 5 numeri distinti, compresi
            tra 1 e 15. Tali numeri rappresentano 5 differenti tubi. 
            NB: il programma deve operare un controllo sulla validità dell’input 
            (ad esempio che i numeri siano tutti differenti tra loro);
            
            • il programma chiede all’utente il numero totale di minuti (M)
            durante i quali i tubi specificati forniranno acqua alla rispettiva vasca. 
            Nota: il programma deve operare un controllo sulla validità
            dello input, ad esempio che il numero immesso sia positivo.
            
            • il programma calcola e stampa la quantità d’acqua raccolta in ogni
            vasca dopo gli M minuti specificati dall’utente.
            */

            int tubi[15], input[5] = {0,0,0,0,0};
            int min, acqua_raccolta=0,control = -1;

                //popolamento array tubi
                for(int i=0;i<15;i++)
                {
                    if(i%2==0)
                        tubi[i] = 120;
                    else 
                        tubi[i]=60;
                }
                
                
                //input utente
                printf("Inserisci i distinti tubi interessati:\n");
                for(int i=0; i<5;i++)
                {
                    do
                    {
                        printf("%d) ",i+1);
                        scanf("%d",&input[i]);

                        //controllo input
                        if(input[i] < 1 || input[i] > 15)
                        {
                            printf("Input non valido. Inserire un valore tra 1 e 15.\n");
                            control = 1;
                        }
                        else //controllo numeri duplicati
                        {
                            control = -1;
                            for(int j=0;j<i;j++)
                            {
                                if(input[i] == input[j])
                                {
                                    printf("Errore: Numero duplicato, inserisci un altro valore.\n");
                                    control = 1;
                                    break;
                                }
                                else 
                                    control = -1;
                            }
                        }
                    }while(control != -1);
                }

                do
                {
                    printf("Inserisci numero totale di minuti da calcolare:\n");
                    scanf("%d",&min);
                }while(min <= 0);

                //calcolo quanti litri sono passati nell'intervallo di tempo richiesto

                for(int i=0;i<5;i++)
                {
                    acqua_raccolta += tubi[input[i]] * min; 
                }

                printf("Acqua raccolta nell'intervallo richiesto nei tubi selezionati:\n1) %d => %d l/min\n2) %d => %d l/min\n3) %d => %d l/min\n4) %d => %d l/min\n5) %d => %d l/min\n\nLitri totali nell'intervallo di tempo richiesto (%d min)= %d\n",input[0],tubi[input[0]],input[1],tubi[input[1]],input[2],tubi[input[2]],input[3],tubi[input[3]],input[4],tubi[input[4]],min,acqua_raccolta);

            
            break;
        }
    }
}



