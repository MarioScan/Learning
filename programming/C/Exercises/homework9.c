#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h> //esercizio 6 --> funzione di islower()

#define max_char 100

//PROPOTIPO DELLE FUNZIONI
int alf_min_ASCII();
char char_e_num();

//DEFINIZIONE DELLE FUNZIONI
int alf_min_ASCII()
{
    //prendendo dalla tabella ASCII i valori [a-z] otteniamo il range in valore numerico corrispondente: [97-122]
    //voglio restituire il valore numerico con questa funzione in maniera tale da assegnare i valori direttamente alla singola casella char
    int ris = rand() % (122 - 97 + 1) + 97;
    return ris;
}
//////////////////////
char char_e_num()
{
    int ris = rand() % 36; //26 lettere alfabeto minuscolo [a-z] e numeri da [0-9]
    if(ris < 26)
        return 'a' + ris; //valori tra (ris = 0 e 25) quindi [a-z]
    else 
        return '0' + (ris - 26); //0 + (max di 35 - 26 (minimo), quindi 9) range [0-9]
}
/////////////////////
int main()
{
    int n_menu,cc=-1 ;
    do
    {
        char indice_menu[] = "1) 17.1\n2) 17.2\n3) 17.3\n4) 17.4\n5) 17.5\n6) 17.6\n";
        int n_esercizi = 6;
        n_menu = menu(indice_menu,n_esercizi); //Benvenuto nel menu'
        
        switch(n_menu)
        {
            case 1:
            {
                printf("\nHomework 17.1:\n");
                /////////
                printf("\nPunto 1) Definire un array di caratteri di lunghezza 15. Riempire tale array con caratteri random nel'intervallo [a-z].\n");
                int n = 15;
                char c[n];
                for(int i=0;i<n;i++)
                {
                    //printf("%d\n",alf_min_ASCII()); //debug
                    c[i] = alf_min_ASCII();
                }
                printf("Array di caratteri generato: ");
                for(int i=0;i<n;i++)
                    printf("%c ",c[i]);
                printf("\n");
                ////////
                printf("\nPunto 2) Definire un array di caratteri mediante una lista di inizializzazione, che abbia almeno 5 caratteri. Stampare la stringa con una istruzione printf.\n");
                char array[] = {'a','b','c','d','X','Y','*','\0'};
                printf("Array di caratteri con lista di inizializzazione: %s\n",array);
                ///////
                printf("\nPunto 3) Definire un array mediante un inizializzatore che sia un letterale stringa. Stampare quindi la lunghezza della stringa, e la stringa stessa mediante una istruzione printf.\n");
                char a[] = "Ciao mondo!";
                printf("Stringa: %s ; lunghezza: %d\n",a,(strlen(a)));
                //////
                printf("\nPunto 4) Definire un array di caratteri di sola lettura, mediante la definizione di un puntatore a carattere. Stampare quindi la stringa e la lunghezza della stringa stessa, mediante una istruzione printf.\n");
                //Se è sola lettura, ovviamente si tratta di una costante, quindi non variabile,
                const char *s = "Sono una variabile di sola lettura...";
                printf("Stringa: \"%s\" ; lunghezza: %d\n",s,strlen(s));
                break;
            }
            case 2:
            {
                printf("\nHomework 17.2:\n");
                ///////
                printf("Punto 1) Definire tre stringhe di lunghezza random che sia compresa tra 10 e 20.\n");
                int n;
                n = rand() % (20 - 10 + 1) + 10;
                printf("Lunghezza prima stringa = %d\n",n);
                char *v1 = (char*)malloc((n) * sizeof(char)); 
                //potrei anche considerare n+1 per lasciare uno spazio per la chiusura dell'array ma lo considero per scelta personale, dalla consegna come compresa tra i 20 numeri possibili...
                for(int i=0;i<n;i++)
                    v1[i] = char_e_num();
                v1[n]='\0';
                n = rand() % (20 - 10 + 1) + 10;
                printf("Lunghezza seconda stringa = %d\n",n);
                char *v2 = (char*)malloc(n * sizeof(char));
                for(int i=0;i<n;i++)
                    v2[i] = char_e_num();
                v2[n]='\0';
                n = rand() % (20 - 10 + 1) + 10;
                printf("Lunghezza terza stringa = %d\n",n);
                char *v3 = (char*)malloc(n * sizeof(char));
                for(int i=0;i<n;i++)
                    v3[i] = char_e_num();
                v3[n]='\0';
                
                printf("\nPunto 2) Riempire le tre stringhe con caratteri pseudocasuali che appartengano agli intervalli [a-z, 0-9].\n");

                printf("Stringa n.1: \"%s\" ; Lunghezza: %d\n",v1,strlen(v1));
                printf("Stringa n.2: \"%s\" ; Lunghezza: %d\n",v2,strlen(v2));
                printf("Stringa n.3: \"%s\" ; Lunghezza: %d\n",v3,strlen(v3));

                printf("\nPunto 3) Eseguire un confronto lessicografico delle tre stringhe mediante la funzione strcmp.\n");

                printf("Risultato confronto v1 (\"%s\") e v2 (\"%s\"): %d\n",v1,v2,strcmp(v1,v2));
                printf("Risultato confronto v2 (\"%s\") e v3 (\"%s\"): %d\n",v2,v3,strcmp(v2,v3));
                printf("Risultato confronto v1 (\"%s\") e v3 (\"%s\"): %d\n",v1,v3,strcmp(v1,v3));

                printf("\nNota: 0 se uguali, valore > 0 se la prima e\' maggiore, valore < 0 se minore...\n");

                printf("\nPunto 4) Infine stampare le tre stringhe, una riga dopo l'altra dalla stringa minore alla stringa maggiore.\n");
                
                printf("Array in ordine originale:\n1) %s\n2) %s\n3) %s\n\n",v1,v2,v3);
                printf("Array ordinati in ordine crescente...\n");
                char *order[] = {v1,v2,v3};
                for(int i=0;i<3;i++)
                {
                    //confronto tutti i valori per il primo array, e così via...
                    for(int j=0;j<3;j++)
                    {
                        if(strcmp(order[i],order[j])<0) //riordino per ordine crescente
                        {
                            char *temp = order[i];
                            order[i] = order[j];
                            order[j] = temp;
                        }
                    }
                    printf("%d) %s\n",i,order[i]);
                }
                printf("\n");
                //liberazione memoria assegnata...
                free(v1);
                free(v2);
                free(v3);
                break;
            }
            case 3:
            {
                printf("\nHomework 17.3:\n");
                printf("Punto 1) Scrivere un programma che chieda in input all'utente nome e cognome, da memorizzare in due array di caratteri distinti.\n");

                //char nome[20], cognome[20]; //Posso utilizzare un altro modo, per ridurre al minimo lo spazio usato da ogni variabile:
                //fgets è più sofisticato rispetto a scanf, in quanto permette di scrivere il numero massimo che può ricevere in input, e crea una newline per ogni spazio, quindi se l'utente ha più di un nome non genera errore
                /*
                printf("\nInserisci nome: ");
                scanf("%s",&nome);
                printf("\nInserisci cognome: ");
                scanf("%s",&cognome);
                */
                fflush(stdin); //Necessario pulire il buffer per usare fgets dopo scanf del menu...
                char*input=(char*)malloc(max_char*sizeof(char));
                printf("\nInserisci nome completo: ");
                fgets(input, max_char, stdin);
                //adesso voglio che venga utilizzato il minor spazio possibile:
                int len = strlen(input);
                //fgets porta a capo in automatico quando premi tasto invio per inviare l'input, quindi vado a cercare se è stato inserito un \n alla fine del testo e lo vado a sostituire con carattere di fine stringa \0 
                if (input[len - 1] == '\n') 
                { 
                    input[len - 1] = '\0'; 
                    len--; 
                }
                printf("\nNome: %s ; lunghezza: %d\n", input,len);
                char*nome = (char*)malloc(len * sizeof(char));
                strcpy(nome,input);
                
                //voglio resettare input: porto quindi tutti i caratteri usati a nulli con \0, posso farlo manualmente o con la funzione memset:
                
                for(int i=len-1;i>=0;i--)
                {
                    input[i] = '\0';
                }
                //printf("\ninput: %s ; lunghezza: %d\n", input,strlen(input));
                
               //oppure:
                /*
                memset(input, '\0', sizeof(input));
                printf("\ninput: %s ; lunghezza: %d\n", input,strlen(input));
                */
                printf("\nInserisci cognome:\n");
                fgets(input, max_char, stdin);
                len = strlen(input);
                if (input[len - 1] == '\n') 
                { 
                    input[len - 1] = '\0'; 
                    len--; 
                }
                printf("\nCognome: %s ; lunghezza: %d\n", input,len);
                char*cognome = (char*)malloc(len * sizeof(char));
                strcpy(cognome,input);
                memset(input, '\0', sizeof(input));
                printf("Nome e cognome inseriti: %s %s\n",nome,cognome);

                printf("\nPunto 2) Definire quindi un array di caratteri che possoa contenere sia nome che cognome separati da un carattere ';', senza spazi.\n");
                len = strlen(nome) + strlen(cognome);
                char*utente = (char*)malloc((len+1) * sizeof(char)); //+1 per ; 
                strcpy(utente,nome);
                strcat(utente,";");
                strcat(utente,cognome);
                printf("Utente: %s",utente);
                free(input);
                free(nome);
                free(cognome);
                free(utente);
                break;
            }
            case 4:
            {
                printf("Homework 17.4:\n"); 
                printf("Programma che indica quanti verbi finiscono con \'-are\', \'-ere\' e \'-ire\'.\n");
                
                /* Controllo dell'input... */
                short num=-1;
                char input[3];
                fflush(stdin);
                do
                {
                    num=-1;
                    printf("Inserisci numero di verbi massimo da prendere in input:\n");
                    scanf("%s",&input);
                    num=atoi(input);
                    //printf("%hu\n",num); //Debug
                    if(num>10 || num<1)
                        printf("Valore non valido: il numero da inserire dev\'essere compreso tra 1 e 10. Riprova.\n");
                    printf("\n#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#\n\n");
                }while(num>10 || num<1);
                /* Fine controllo dell'input... */

                //Allocazione dinamica dell'array di stringhe...
                char**verbi=(char**)malloc(num*sizeof(char*));
                for(int i=0;i<num;i++)
                    verbi[i]=(char*)malloc(30 * sizeof(char));
                
                //Inserimento input...
                printf("Inserisci verbi:\n");
                for(int i=0;i<num;i++)
                    scanf("%s",verbi[i]);

                //Verifica se tutti gli input sono stati inseriti correttamente...
                printf("Stampa array:\n");
                for(int i=0;i<num;i++)
                    printf("%d) %s\n",i,verbi[i]);

                //ricerca delle parole che terminano per i criteri richiesti...
                //Due approcci possibili: ricerca manuale calcolando le ultime tre caselle di ogni cella dell'array con strlen e prendendo strlen-1,strlen-2,strlen-3... 
                //oppure, con ricerca strstr che si occupa della ricerca di sottostringhe.
                printf("\nPunto 2) Elementi che terminano con \'-are\', \'-ere\' e \'-ire\'.\n");
                int c1=0,c2=0,c3=0;
                for(int i=0;i<num;i++)
                {   
                    char *ricerca1=strstr(verbi[i],"are");
                    if(ricerca1/*se ricerca ha un valore, quindi se ricerca==true:*/)
                    {
                        printf("%s \'-%s\'\n",verbi[i],ricerca1);
                        c1++;
                        continue;
                    }
                    char *ricerca2=strstr(verbi[i],"ere");
                    if(ricerca2)
                    {
                        printf("%s \'-%s\'\n",verbi[i],ricerca2);
                        c2++;
                        continue;
                    }
                    char *ricerca3=strstr(verbi[i],"ire");
                    if(ricerca3)
                    {
                        printf("%s \'-%s\'\n",verbi[i],ricerca3);
                        c3++;
                        continue;
                    }
                }
                printf("\nVerbi che terminano con le seguenti desinenze:\n\'-are\' --> %d\n\'-ere\' --> %d\n\'-ire\' --> %d\n\n",c1,c2,c3);
                //libero memoria allocata precedentemente...
                for(int i=0;i<num;i++)
                    free(verbi[i]);
                free(verbi);
                printf("Liberazione memoria assegnata in precedenza...\n\nFine esecuzione.\n");
                printf("\n#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#\n\n");
                break;
            }
            case 5:
            {
                printf("Homework 17.5:\n");
                printf("Esercizio di conversione da stringa a double con tre funzioni di conversione differenti:\n1) atof;\n2) sscanf;\n3) strtof.\nDopodiche\' calcola la media dei tre valori e restituisci il risultato.\n");

                char**str=(char**)malloc(3 * sizeof(char*));
                for(int i=0;i<3;i++)
                    str[i]=(char*)malloc(10*sizeof(char));
                
                strcpy(str[0],"primo");
                strcpy(str[1],"secondo");
                strcpy(str[2],"terzo");
                
                fflush(stdin);
                
                /* Input controllato */
                for(int i=0;i<3;i++)
                {
                    bool check=false;
                    char input[10];
                    do
                    {
                        printf("Inserisci %s valore:\n",str[i]);
                        //memset(str[i], '\0', sizeof(str[i])); //non è necessario cancellare la stringa, viene sovrascritta ugualmente...
                        scanf("%s",input);
                        if(( strlen(input)<1) || (atof(input) == 0))
                        {
                            printf("Valore non valido. Riprova.\n");
                            check=true;
                        }
                        else
                        {
                            strcpy(str[i],input);
                            check=false;
                        }
                    }while(check!=false);
                }
                printf("\n#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#\n\n");

                /* Stampa valori */
                for(int i=0;i<3;i++)
                    printf("%d) %s\n",i,str[i]);

                printf("Conversione con atof: stringa: %s (%%s) --> ",str[0]);
                float n1 = atof(str[0]);
                printf("%.5f (%%.5f)\n",n1);

                printf("Conversione con sscanf: stringa: %s (%%s) --> ",str[1]);
                float n2;
                sscanf(str[1],"%f",&n2);
                printf("%.5f (%%.5f)\n",n2);

                printf("Conversione con strtof: stringa: %s (%%s) --> ",str[2]);
                float n3;
                char *endptr; //la funzione strtof richiede un secondo parametro che punta alla fine della stringa da convertire, se va a buon fine il suo valore sarà di tipo NULL
                //ho già controllato che la stringa sia puramente numerica, quindi:
                n3 = strtof(str[2],&endptr);
                printf("%.5f (%%.5f)\n",n3);

                printf("\nPunto 3) Calcolo media dei tre valori:\nMedia = (n1 + n2 + n3) / 3 = (%.3f + %.3f + %.3f) / 3 = %.5f\n",n1,n2,n3,(n1+n2+n3)/3);
                
                for(int i=0;i<3;i++)
                    free(str[i]);
                free(str);
                printf("\nLiberazione della memoria allocata dinamicamente...\nFine esecuzione.\n");
                printf("\n#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#\n\n");
                break;
            }
            case 6:
            {
                printf("Homework 17.6:\n");
                /*
                Homework H17.6 Scrivere un programma che chieda all’utente di
                inserire alcune stringhe, una alla volta, entro un limite massimo (es 30).
                Il programma memorizza le stringhe in appositi array di caratteri.
                Ogni stringa in input potr`a anche contenere spazi, ed il programma
                leggera' al massimo 20 caratteri per ogni stringa in input.
                Il programma dovra' stampare, per ogni stringa memorizzata:
                • la stringa stessa ;
                • il numero di lettere minuscole presenti nella stringa;
                • il numero di caratteri che rappresentano numeri, presenti nella
                stringa;
                • il numero di spazi presenti nella stringa;
                */
               
                /* Input controllato... */
                int n;
                do
                {
                    printf("Quante stringhe vorresti inserire? ");
                    scanf("%d",&n);
                    if(n<1 || n>10)
                        printf("Valore non valido. Inserisci un valore compreso tra 1 e 10. Riprova.\n");
                }while(n<1 || n>10);

                /* Creazione array di stringhe... */
                char **str = (char**)malloc(n * sizeof(char*));
                for(int i=0;i<n;i++)
                    *(str+i)=(char*)malloc(30 * sizeof(char));

                /* Inserimento dei dati nell'array... */
                fflush(stdin);
                printf("Inserisci dei valori per ogni stringa:\n");
                for(int i=0;i<n;i++)
                {
                    printf("%d) ",i);
                    //scanf("%s",str[i]);
                    fgets(str[i],20,stdin); //al contrario di scanf, fgets tollera gli spazi e mi permette di gestire meglio la memoria da assegnare
                    //str[i][strlen(str[i])] = '\0';
                }
                /* Rimuovo gli eventuali \n aggiunti automaticamente dalla funziona fgets...*/
                printf("Stampa dati inseriti:\n");
                for(int i=0;i<n;i++)
                {
                    int len=strlen(str[i]);
                //fgets porta a capo in automatico quando premi tasto invio per inviare l'input, 
                //quindi vado a cercare se è stato inserito un \n alla fine del testo e lo vado a sostituire con carattere di fine stringa \0 
                    if (str[i][len - 1] == '\n') 
                    { 
                        str[i][len - 1] = '\0'; 
                        len--; 
                    }
                    printf("%d) %s ; lunghezza: %d\n",i,str[i],len);
                }

                /* Punto 2 ...*/
                printf("\nPunto 2)\n- Trova il numero di lettere minuscole in ogni stringa:\nIl numero di caratteri di tipo numerico in ogni stringa\nIl numero di spazi all\'interno di ogni stringa.\n\n");
                for(int i=0;i<n;i++)
                {
                    int c=0,c1=0,c2=0,c4=0;
                    printf("Stringa: %s\n",str[i]);
                    for(int j=0;j<strlen(str[i]);j++)
                    {
                        if(str[i][j] == ' ' && j!=0)
                        {
                            printf(" + ");
                            c2++;
                            c4=j;
                        }
                        if(islower(str[i][j]))
                        {
                            printf(" %c ",str[i][j]);
                            c++;
                        }
                        if(isdigit(str[i][j]))
                        {
                            printf(" %c ", str[i][j]);
                            c1++;
                        }
                    }
                    //Per punto 2...
                    printf("\nNumero di lettere minuscole: %d\n",c);
                    //Per punto 3...
                    printf("Numero di caratteri che rappresentano valori di tipo numerico: %d\n",c1);
                    //Per punto 4...
                    printf("Numero di spazi: %d ; Posizione del primo spazio: %d\n\n",c2,c4);
                }


                /* Libera memoria utilizzata... */
                for(int i=0;i<n;i++)
                    free(str[i]);
                free(str);

                printf("\nLiberazione della memoria allocata dinamicamente...\nFine esecuzione.\n");
                printf("\n#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#\n\n");
                break;
            }
        } //Fine switch (!!!)
        if(n_menu==0)
        {
            cc=0;
        }
        else cc=menu1(); //tornare al menu si/no
        
        n_menu=-1; //reset variabile menu di sicurezza
    }while(cc==1);
} //Fine programma
