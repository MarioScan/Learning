#include "menu.h" //menu
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h> //usata per la funzione tolower (stringhe tutte minuscole) utile nella funzione palindrome dell'esercizio 1, in modo tale da mettere diversi elementi maius e non per gli esercizi successivi con la stessa funzione di generazione stringhe...

#define n 3
#define m 5
#define max_caratteri 20
#define delta 25.2
#define kk 2
#define zz 2
//!!!
void deallocazione_matrice_char(char ***A, int n1, int n2);
void gen_stringhe_nm(char *a[n][m]);
void gen_stringhe_nn(char *a[n][n]);
void gen_alfabeto_char_n(char c[n]);
void gen_alfabeto_char_kz(char matrice[kk][zz]);
void gen_alfabeto_char_nm(char matrice[n][m]);
char***gen_matrice_stringhe(char***a,int n1,int n2);
bool case1(char *M[n][m]);
bool palindrome(char *str);
void deallocazione_char(char *a[n][m]);
void deallocazione_int(int **matrice, int n1, int n2);
bool case2(char *s[n][m],char c[m],float w);
int** allocazione_int(int n1, int n2);
double** allocazione_double(int n1, int n2);
char*** allocazione_matrice_char(int n1,int n2);
void gen_numeri_int(int **matrice, int n1, int n2);
void gen_numeri_double(double **matrice, int n1, int n2);
double* case3(int k, int **a,int **b);
int* case4(int k, int **a, double **b);
bool case5(char *s[n][m],short w,short k);
bool case6(int **a, short w, short k);
char* confronto_stringhe(char* stringa);
bool case7(char *a[n][m], char s[]);
bool case8(char*A[n][m],char C[kk][zz],short w);
bool case9(char C[n][m],int a);
char** case10(char***A, short k, char* s);
double* case11(int**A,int**B);
char caratteri_random();
void gen_stringhe_casuali(char**S, int n1);
char**case12(char**S,char**C,int n3,int n2,int n1,short k);
char**case13(char***A,short**B,int n1,int n2);
short case14(char ***S,short*B,int n1, int n2);
short*case15(char ***A,char*B,char*C,int n1, int n2);
int case16(double**A,int*B, int n1, int n2);
//int case16_alt(double**A,int*B,int n1, int n2);
//---------------------------------------------------
void deallocazione_matrice_char(char ***A, int n1, int n2)
{
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < n2; j++)
        {
            free(A[i][j]); // Libera ogni stringa
        }
        free(A[i]); // Libera ogni riga
    }
    free(A); // Libera la matrice
    printf("\nDeallocazione della matrice di stringhe completata con successo...\n");
}
//---------------------------------------------------
void gen_stringhe_nm(char *a[n][m])
{                   //n parole e max caratteri
    char vet_stringhe[][20] = {"Radar", "Cane", "Gatto", "Madam", "Civic", "Auto", "Deed", "level","LEVEL","Level","rotor", "kayak", "mela", "casa", "pala", "tavolo", "sedia", "finestra", "porta", "libro", "penna", "quaderno", "zaino", "orologio","abc","Pippo","pino","fiore","albero","Albero","Internet","Ingegni","Wow","ottetto","Ala","SMS","Orso"};
    //char vet_stringhe[][20] = {"Albero", "albero", "ALbero", "aLbero", "alBero", "AlBero", "aLBero", "ALBero", "albEro", "AlbEro", "aLbEro", "ALbEro", "alBEro", "AlBEro", "aLBEro", "ALBEro", "albeRo", "AlbeRo", "aLbeRo", "ALbeRo", "alBeRo", "AlBeRo", "aLBeRo", "ALBeRo", "albeRO", "AlbeRO", "aLbeRO", "ALbeRO", "alBeRO", "AlBeRO", "aLBeRO", "ALBeRO", "albERo", "AlbERo", "aLbERo", "ALbERo","ALBERO"};

    srand(time(NULL));
    printf("\nCreazione e inserimento di parole estratte tra 36 combinazioni differenti, palindrome e non palindrome:\n\n");
    
    for(int i=0;i<n;i++)
    {
        int r=0;
        printf("| ");
        for(int j=0;j<m;j++)
        {
            r = rand() % (36-0+1) + 0; 
            a[i][j] = (char*)malloc((strlen(vet_stringhe[r]) + 1) * sizeof(char));  // Allocazione memoria
            strcpy(a[i][j], vet_stringhe[r]);  // Copia stringa
            printf("%s | ", a[i][j]);
        }
        printf("\n");
    }
    fflush(stdin);
}
//---------------------------------------------------
void gen_stringhe_nn(char *a[n][n])
{                   //n parole e max caratteri
    char vet_stringhe[][20] = {"Radar", "Cane", "Gatto", "Madam", "Civic", "Auto", "Deed", "level","LEVEL","Level","rotor", "kayak", "mela", "casa", "pala", "tavolo", "sedia", "finestra", "porta", "libro", "penna", "quaderno", "zaino", "orologio","abc","Pippo","pino","fiore","albero","Albero","Internet","Ingegni","Wow","ottetto","Ala","SMS","Orso"};
    //char vet_stringhe[][20] = {"Albero", "albero", "ALbero", "aLbero", "alBero", "AlBero", "aLBero", "ALBero", "albEro", "AlbEro", "aLbEro", "ALbEro", "alBEro", "AlBEro", "aLBEro", "ALBEro", "albeRo", "AlbeRo", "aLbeRo", "ALbeRo", "alBeRo", "AlBeRo", "aLBeRo", "ALBeRo", "albeRO", "AlbeRO", "aLbeRO", "ALbeRO", "alBeRO", "AlBeRO", "aLBeRO", "ALBeRO", "albERo", "AlbERo", "aLbERo", "ALbERo","ALBERO"};

    srand(time(NULL));
    printf("\nCreazione e inserimento di parole estratte tra 36 combinazioni differenti, palindrome e non palindrome:\n\n");
    
    for(int i=0;i<n;i++)
    {
        int r=0;
        printf("| ");
        for(int j=0;j<n;j++)
        {
            r = rand() % (36-0+1) + 0; 
            a[i][j] = (char*)malloc((strlen(vet_stringhe[r]) + 1) * sizeof(char));  // Allocazione memoria
            strcpy(a[i][j], vet_stringhe[r]);  // Copia stringa
            printf("%s | ", a[i][j]);
        }
        printf("\n");
    }
    fflush(stdin);
}
//---------------------------------------------------
char***gen_matrice_stringhe(char***a,int n1,int n2)
{
    srand(time(NULL));
    printf("\nCreazione e inserimento di parole estratte tra 36 combinazioni differenti, palindrome e non palindrome:\n\n");
    //char vet_stringhe[][20] = {"Radar", "Cane", "Gatto", "Madam", "Civic", "Auto", "Deed", "level","LEVEL","Level","rotor", "kayak", "mela", "casa", "pala", "tavolo", "sedia", "finestra", "porta", "libro", "penna", "quaderno", "zaino", "orologio","abc","Pippo","pino","fiore","albero","Albero","Internet","Ingegni","Wow","ottetto","Ala","SMS","Orso"};
    char vet_stringhe[30][20] = {"Albero", "Casa", "Libro", "Amore", "Gatto", "Cane", "Barca", "Natura", "Musica", "Arte", "Scienza", "Sport", "Viaggio", "Cucina", "Famiglia", "Amicizia", "Lavoro", "Storia", "Cultura", "Speranza", "Salute", "Pranzo", "Tristezza", "Rabbia", "Paura", "Sorpresa", "Disgusto", "Coraggio", "Pazienza", "Gentilezza"};
    for(int i=0;i<n1;i++) 
    {
        int r=0;
        printf("| ");
        for(int j=0;j<n2;j++) 
        {
            r = rand() % (29-0+1) + 0; //36 vet1 - 29 vet2  
            a[i][j] = (char*)malloc((strlen(vet_stringhe[r]) + 1) * sizeof(char));
            strcpy(a[i][j], vet_stringhe[r]);  // Copia stringa
            printf("%s | ", a[i][j]);
        }
        printf("\n");
    }
    return a;
}
//---------------------------------------------------
void gen_alfabeto_char_n(char c[n])
{
    char vet_char[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char vet_char1[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z','a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    srand(time(NULL));
    int r=0,ans;
    do
    {
        printf("Selezione se utilizzare solo alfabeto minuscolo o alfabeto minuscolo e maiuscolo mescolati insieme:\n1) Solo alfabeto minuscolo;\n2) Alfabeto minuscolo e maiuscolo.\n");
        scanf("%d",&ans);
        if(ans <= 0 || ans >2)
            printf("Seleziona dei valori adeguati! Riprova.\n");
    }while(ans <= 0 || ans >2);
    
    switch(ans)
    {
        case 1:
        {
            printf("Hai selezionato solo valori alfabeto minuscolo.\n");
            printf("\nCreazione e inserimento di caratteri estratti tra 26 combinazioni differenti:\n");
            printf("Array di caratteri: ");
            for(int i=0;i<n;i++)
            {
                r = rand() % (25 - 0 + 1) + 0;
                c[i] = vet_char[r];
                if(i!=n-1)
                    printf("%c, ", c[i]);
                else printf("%c. ", c[i]);
            }
            break;
        }
        case 2:
        {
            printf("Hai selezionato valori alfabeto minuscolo e maiuscolo.\n");
            printf("\nCreazione e inserimento di caratteri estratti tra 52 combinazioni differenti:\n");
            printf("Array di caratteri: ");
            for(int i=0;i<n;i++)
            {
                r = rand() % (51 - 0 + 1) + 0;
                c[i] = vet_char1[r];
                if(i!=n-1)
                    printf("%c, ", c[i]);
                else printf("%c. ", c[i]);
            }
            break;
        }
    }
    printf("\n\n");
}
//---------------------------------------------------
void gen_alfabeto_char_kz(char matrice[kk][zz])
{
    srand(time(NULL));
    int n1=kk,n2=zz;
    char vet_char[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char vet_char1[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z','a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    int r=0,ans;
    
    do
    {
        printf("Selezione se utilizzare solo alfabeto minuscolo o alfabeto minuscolo e maiuscolo mescolati insieme:\n1) Solo alfabeto minuscolo;\n2) Alfabeto minuscolo e maiuscolo.\n");
        scanf("%d",&ans);
        if(ans <= 0 || ans >2)
            printf("Seleziona dei valori adeguati! Riprova.\n");
    }while(ans <= 0 || ans >2);

    printf("\nGenerazione matrice di caratteri con 26 combinazioni di lettere minuscole differenti (tutto l\'alfabeto italiano)...\n");
    for(int i=0;i<n1;i++)
    {
        printf("{ ");
        for(int j=0;j<n2;j++)
        {
            r = rand() % (25 - 0 + 1) + 0;
            matrice[i][j] = vet_char[r];
            if(j!=n2-1)
                printf("%c | ",matrice[i][j]);
            else if(j==n2-1)
                printf("%c }",matrice[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
//---------------------------------------------------
void gen_alfabeto_char_nm(char matrice[n][m])
{
    srand(time(NULL));
    int n1=n,n2=m;
    char vet_char[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char vet_char1[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z','a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    int r=0,ans;
    
    do
    {
        printf("Selezione se utilizzare solo alfabeto minuscolo o alfabeto minuscolo e maiuscolo mescolati insieme:\n1) Solo alfabeto minuscolo;\n2) Alfabeto minuscolo e maiuscolo.\n");
        scanf("%d",&ans);
        if(ans <= 0 || ans >2)
            printf("Seleziona dei valori adeguati! Riprova.\n");
    }while(ans <= 0 || ans >2);

    switch(ans)
    {
        case 1:
        {
            printf("\nGenerazione matrice di caratteri con 26 combinazioni di lettere minuscole (tutto l\'alfabeto italiano)...\n");
            for(int i=0;i<n1;i++)
            {
                printf("{ ");
                for(int j=0;j<n2;j++)
                {
                    r = rand() % (25 - 0 + 1) + 0;
                    matrice[i][j] = vet_char[r];
                    if(j!=n2-1)
                        printf("%c | ",matrice[i][j]);
                    else if(j==n2-1)
                        printf("%c }",matrice[i][j]);
                }
                printf("\n");
            }
            printf("\n");
            break;
        }
        case 2:
        {
            printf("\nGenerazione matrice di caratteri con 51 combinazioni di lettere minuscole e maiuscole (tutto l\'alfabeto italiano)...\n");
            for(int i=0;i<n1;i++)
            {
                printf("{ ");
                for(int j=0;j<n2;j++)
                {
                    r = rand() % (51 - 0 + 1) + 0;
                    matrice[i][j] = vet_char1[r];
                    if(j!=n2-1)
                        printf("%c | ",matrice[i][j]);
                    else if(j==n2-1)
                        printf("%c }",matrice[i][j]);
                }
                printf("\n");
            }
            printf("\n");
            break;
        }
    }
}
//---------------------------------------------------
bool palindrome(char *str)
{
    fflush(stdin);
    printf("Stringa da analizzare: \'%s\' --> Risultato: ",str);
    int len = strlen(str); //assegno la lunghezza della stringa da analizzare alla variabile len
    char str1[len];
    strcpy(str1,str);
    for(int i = 0; i < len; i++) //tutto minuscolo
    {
        str1[i] = tolower(str1[i]);
    }
    for (int i = 0; i < len / 2; i++) 
    {
        if (str1[i]!= str1[len - i - 1]) //confronta la prima metà della stringa con l'altra meta, partendo rispettivamente dal primo e ultimo carattere, es. casa --> c è uguale ad a?
        {  
            printf("stringa non palindroma.\n\n");
            return false;
        }
    }
    printf("stringa palindroma!\n\n");
    return true;
}
//---------------------------------------------------
void deallocazione_char(char *a[n][m])
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            free(a[i][j]);
        }
        free(a[i]);
    }
    free(a);    
}
void deallocazione_int(int **matrice,int n1, int n2)
{
    for(int i=0; i<n; i++)
    {
        free(matrice[i]);
    }
    free(matrice);
}
//---------------------------------------------------
bool case1(char *M[n][m])
{
    fflush(stdin);
    int countRow[n]; //creazione di un array contatore per le righe della matrice di caratteri in cui vengono trovate stringhe palindrome 
    printf("\nNota: Le stringhe vengono lette tutte in minuscolo durante il controllo dei palindromi con la funzione tolower.\n");
    for (int i = 0; i < n; i++) 
    {
        printf("\nRiga n.%d:\n\n",i+1);
        //Righe
        countRow[i] = 0; // Conta palindromi nelle righe della matrice
        for (int j = 0; j < m; j++) 
        {
            printf("Colonna n.%d\nVerifica se la stringa \'%s\' sia o meno palindroma:\n",j+1,M[i][j]);
            bool ris = palindrome(M[i][j]);
            if (ris == true) 
            {
                //printf nella funzione palindrome
                countRow[i]++; //stringa palindroma trovata, aggiunto all'array 
            }
        }
    } //fine ciclo for principale (int i = 0; i < n; i++)
    
    for(int i=0;i<n;i++)
    {
        if(countRow[i] > 0)
        {
            return true;
        }
    }
    return false;
}
//---------------------------------------------------
bool case2(char *s[n][m],char c[m],float w)
{
    printf("\nCalcolo se sia presente almeno una riga o una colonna della matrice tale che la percentuale di caratteri di C sia maggiore di w:\n");
    float n_caratteri = 0;
    float n_car_C = 0;
    int len_S;
    float ris=0;

    gen_alfabeto_char_n(c);

    //Controllo tutte le righe:
    for(int i=0;i<n;i++) //righe di S
    {
        printf("Riga n.%d\n",i+1);
        for(int j=0;j<m;j++) //colonne di S
        {
            len_S = strlen(s[i][j]);
            n_caratteri += len_S;
            printf("Stringa: \'%s\' ; Lunghezza stringa: %d ; Numero caratteri totali: %.0f\n",s[i][j],len_S,n_caratteri);
            for(int k=0;k<len_S;k++) //stringhe di S
            {
                for(int l=0;l<n;l++) //caratteri di S
                {
                    printf("%c == %c ...? ",s[i][j][k] ,c[l]);
                    if(s[i][j][k] == c[l])
                    {
                        n_car_C += 1;
                        printf("--> \'%c\' == \'%c\' ; contatore = %.0f",s[i][j][k],c[l],n_car_C);
                    }
                    printf("\n");
                }
                printf("\n");
            }
        }
        //calcolo percentuale:
        // (numero caratteri corrispondenti / numero caratteri totali) * 100 > w
        ris = ((n_car_C/n_caratteri)*100);
        printf("\nCalcolo:\n(numero caratteri corrispondenti (%.0f) / numero caratteri totali(%.0f)) * 100 > w (%.2f) -----> ris (%.2f) > w (%.2f)\n",n_car_C,n_caratteri,w,ris,w);
        printf("Percentuale di caratteri C: %.2f\n", ris);
        if(ris>w)
        {
            printf("Percentuale di caratteri C presenti > w: %.2f > %.2f\n",ris,w);
            return true;
        }
    }
    printf("\n");

    printf("Nessuna riga ha ottenuto una percentuale di caratteri C maggiore di w.\n");
    return false;
}
//---------------------------------------------------
int** allocazione_int(int n1, int n2)
{
    //allocazione righe
    int ** matrice = (int **)malloc(n1 * sizeof(int *));
    if(matrice == NULL) //controllo gestione errore allocazione di memoria
    {
        return NULL;
    }
    //allocazione colonne
    for (int i = 0; i < n1; i++) 
    {
        matrice[i] = (int *)malloc(n2 * sizeof(int));
        if(matrice[i] == NULL) {
            // Gestione errore di allocazione della memoria
            for(int j = 0; j < i; j++) 
            {
                free(matrice[j]);
            }
            free(matrice);
            return NULL;
        }
    }
    printf("Allocazione dinamica completata con successo...\n");
    return matrice;
}
//---------------------------------------------------
double** allocazione_double(int n1, int n2)
{
    //allocazione righe
    double ** matrice = (double **)malloc(n1 * sizeof(double *));
    if(matrice == NULL) //controllo gestione errore allocazione di memoria
    {
        return NULL;
    }
    //allocazione colonne
    for (int i = 0; i < n1; i++) 
    {
        matrice[i] = (double *)malloc(n2 * sizeof(double));
        if(matrice[i] == NULL) {
            // Gestione errore di allocazione della memoria
            for(int j = 0; j < i; j++) 
            {
                free(matrice[j]);
            }
            free(matrice);
            return NULL;
        }
    }
    printf("Allocazione dinamica completata con successo...\n");
    return matrice;
}
//---------------------------------------------------
char*** allocazione_matrice_char(int n1,int n2)
{
    char ***A = (char***)malloc(n1* sizeof(char**));
    for (int i = 0; i < n1; i++)
    {
        A[i] = malloc(n2 * sizeof(char*));
        for (int j = 0; j < n2; j++)
        {
            A[i][j] = malloc(15 * sizeof(char));
        }    
    }
    printf("\nAllocazione dinamica della matrice di stringhe completata con successo...\n");
    return A;
}
//---------------------------------------------------
void gen_numeri_int(int **matrice, int n1, int n2)
{
    srand(time(NULL));
    int sel = 0;
    do
    {
        printf("Scegli un range di numeri da generare:\n0) Piccolissimo [1-5]\n1) Piccolo [1 - 10];\n2) Medio [1 - 25];\n3) Grande [1 - 50];\n4) Grandissimo [1 - 99].\nRisposta: ");
        scanf("%d",&sel);
        if(sel < 0 || sel > 4)
        {
            printf("Errore: valore inserito non valido.\nRiprova.\n");
        }
    }while(sel < 0 || sel > 4);

    switch(sel)
    {
        case 0:
        {
            printf("\nCreazione matrice con numeri di tipo interi compresi tra 1 a 5:\n");
            for(int i=0;i<n1;i++)
            {
                for(int j=0;j<n2;j++)
                {
                    matrice[i][j] = rand() % (5-1+1) + 1;
                    printf("%d ",matrice[i][j]);
                }
                printf("\n");
            }
            break;    
        }
        case 1:
        {
            printf("\nCreazione matrice con numeri di tipo interi compresi tra 1 a 10:\n");
            for(int i=0;i<n1;i++)
            {
                for(int j=0;j<n2;j++)
                {
                    matrice[i][j] = rand() % (10-1+1) + 1;
                    printf("%d ",matrice[i][j]);
                }
                printf("\n");
            }
            break;            
        }
        case 2:
        {
            printf("\nCreazione matrice con numeri di tipo interi compresi tra 1 a 25:\n");
            for(int i=0;i<n1;i++)
            {
                for(int j=0;j<n2;j++)
                {
                    matrice[i][j] = rand() % (25-1+1) + 1;
                    printf("%d ",matrice[i][j]);
                }
                printf("\n");
            }
            break;
        }
        case 3:
        {
            printf("\nCreazione matrice con numeri di tipo interi compresi tra 1 a 50:\n");
            for(int i=0;i<n1;i++)
            {
                for(int j=0;j<n2;j++)
                {
                    matrice[i][j] = rand() % (50-1+1) + 1;
                    printf("%d ",matrice[i][j]);
                }
                printf("\n");
            }
            break;            
        }
        case 4:
        {
            printf("\nCreazione matrice con numeri di tipo interi compresi tra 1 a 99:\n");
            for(int i=0;i<n1;i++)
            {
                for(int j=0;j<n2;j++)
                {
                    matrice[i][j] = rand() % (99-1+1) + 1;
                    printf("%d ",matrice[i][j]);
                }
                printf("\n");
            }
            break;
        }
    }
    printf("\n><-><-><-><-><-><-><-><-><-><-><-><\n\n");
}
//---------------------------------------------------
void gen_numeri_double(double **matrice, int n1, int n2)
{
    srand(time(NULL));
    int sel = 0;
    do
    {
        printf("Scegli un range di numeri da generare:\n1) Piccolo [1 - 10];\n2) Medio [1 - 25];\n3) Grande [1 - 50];\n4) Grandissimo [1 - 99].\nRisposta: ");
        scanf("%d",&sel);
        if(sel < 0 || sel > 4)
        {
            printf("Errore: valore inserito non valido.\nRiprova.\n");
        }
    }while(sel < 0 || sel > 4);

    switch(sel)
    {
        case 1:
        {
            printf("\nCreazione matrice con numeri di tipo double compresi tra 1 a 10:\n");
            for(int i=0;i<n1;i++)
            {
                for(int j=0;j<n2;j++)
                {
                    matrice[i][j] = (double)rand() / (double)RAND_MAX * (10.0 - 1.0) + 1.0;
                    printf("%.4f ",matrice[i][j]);
                }
                printf("\n");
            }
            break;            
        }
        case 2:
        {
            printf("\nCreazione matrice con numeri di tipo double compresi tra 1 a 25:\n");
            for(int i=0;i<n1;i++)
            {
                for(int j=0;j<n2;j++)
                {
                    matrice[i][j] = (double)rand() / (double)RAND_MAX * (25.0 - 1.0) + 1.0;
                    printf("%.4f ",matrice[i][j]);
                }
                printf("\n");
            }
            break;
        }
        case 3:
        {
            printf("\nCreazione matrice con numeri di tipo double compresi tra 1 a 50:\n");
            for(int i=0;i<n1;i++)
            {
                for(int j=0;j<n2;j++)
                {
                    matrice[i][j] = (double)rand() / (double)RAND_MAX * (50.0 - 1.0) + 1.0;
                    printf("%.4f ",matrice[i][j]);
                }
                printf("\n");
            }
            break;            
        }
        case 4:
        {
            printf("\nCreazione matrice con numeri di tipo double compresi tra 1 a 99:\n");
            for(int i=0;i<n1;i++)
            {
                for(int j=0;j<n2;j++)
                {
                    matrice[i][j] = (double)rand() / (double)RAND_MAX * (99.0 - 1.0) + 1.0;
                    printf("%.4f ",matrice[i][j]);
                }
                printf("\n");
            }
            break;
        }
    }
    printf("\n><-><-><-><-><-><-><-><-><-><-><-><\n\n");
}
//---------------------------------------------------
double* case3(int k, int **a,int **b)
{   
        //A[n][m], B[k][n]
    //int nn = n;
    //double C[n]; // C[i] = somma righe A[i] / prodotto colonne B[i]
    double *C = (double*)malloc(10*sizeof(double));
    int s=0;
    //somma righe A[i]
    for(int i=0;i<n;i++)
    {
        printf("Riga n.%d\n",i+1);
        s=0;
        for(int j=0;j<m;j++)
        {
            s+=a[i][j];
            printf("Somma = %d ; valore riga = %d\n",s,a[i][j]);
        }
        C[i] = (double)s; 
        printf("---> C[%d] = %.1f\n\n",i,C[i]);
    }
    //prodotto colonne B[i]
    for(int i=0;i<k;i++)
    {
        printf("Colonna n.%d\n",i+1);
        s=0; 
        for(int j=0;j<n;j++)
        {
            if(j==0)
            {
                s=b[j][i];
            }
            else s*=b[j][i];
            printf("Prodotto = %d ; valore colonna = %d\n",s,b[j][i]);
        }
        C[i] /= (double)s;
        printf("--> Rapporto tra somma righe A[i] / prodotto colonne B[i] = %.6f\n",C[i]);
    }
    return C;
}

/*
double (*myFunction2())[10]{
    double (*p)[10];
    p = malloc(sizeof(double[10]));
    return p;
}
*/

int* case4(int k, int **a, double **b)
{
    int* array = (int*)malloc(10*sizeof(int));
    for(int i=0;i<n;i++)
    {
        *(array+i) = i;
    }
    double sum=0;
    double somma[n];
    int calc=0;
    int count[n];
    for(int i=0;i<n;i++)
    { //righe
        printf("Riga di A n.%d\n",i+1);
        calc=0, sum=0;
        for(int j=0;j<m;j++)
        { //colonne
            sum+=a[i][j]; //righe di A 
            printf("A[%d][%d] --> %d\n",i,j,a[i][j]);
            calc++;
        }
        count[i] = calc;
        somma[i] = sum;
        *(array+i) = sum; //array[i] = somma righe di A[i]
        printf("\n");
    }
    for(int i=0;i<n;i++)
    {
        printf("Colonna di B n.%d\n",i+1);
        calc=0, sum=0;
        for(int j=0;j<k;j++)
        {
            sum+=round(b[j][i]); //NB: approssima all'intero piu' vicino (round), ceil() approssima all'intero maggiore più vicino
            printf("B[%d][%d] --> %.4f\n",j,i,b[j][i]);
            calc++;
        }
        somma[i]+=sum;
        count[i]+=calc; //contatore elementi per calcolo media
        printf("\n");
    }
    for(int i=0;i<n;i++)
    {
        array[i] = round(somma[i] / count[i]);
    }

    return array;
}
//---------------------------------------------------
bool case5(char *s[n][m],short w,short k)
{
    bool result = false;
    int count=0,c1=0;
    printf("\n");
    for(int i=0;i<n;i++)
    {
        c1=0;
        printf("Riga n.%d --> Stringhe minori di k (%hu): ",i+1,k);
        for(int j=0;j<m;j++)
        { //righe 
            if(strlen(s[i][j]) < k)
            {
                printf("%s ",s[i][j]);
                count++;
                c1++;
            }
        }
        if(c1==0)
            printf("Nessuna");
            
        printf("\n");
    }
    if(count >= w)
        result = true;

    count=0;
    printf("\n");
    for(int i=0;i<m;i++)
    {
        c1=0;
        printf("Colonna n.%d --> Stringhe minori di k (%hu): ",i+1,k);
        for(int j=0;j<n;j++)
        { //colonne
            if(strlen(s[j][i]) < k)
            {
                count++;
                printf("%s ",s[j][i]);
                c1++;
            }
        }
        if(c1==0)
            printf("Nessuna");
        printf("\n");
    }
    if(count >= w && result == true)
        return true;
    
    return false;
}
//---------------------------------------------------
bool case6(int **a, short w, short k)
{
    /*
    int count=0,c1=0;
    for(int i=0;i<m;i++)
    {
        count=0;
        printf("Colonna n.%d\n",i+1);
        for(int j=0;j<n-1;j++)
        {
            //if(a[j][i] < a[j+1][i])
            {
                count ++;
                printf("%d < %d\n",a[j][i],a[j+1][i]);
            }
            if(count>=k)
                c1++;
        }
    }
    if(c1>=w)
        return true;
    
    return false;
    */

    int count=0,c1=0;
    int min=0;
    int temp=0;
    for(int i=0;i<m;i++)
    {
        count=0;
        min=0;
        printf("Colonna n.%d\n",i+1);
        for(int j=0;j<n-1;j++)
        {
            temp = a[j+1][i];
            /////////////////////////////////
            if(min==0)
            {          
                if(a[j][i] < temp && (a[j][i]+1) == temp)
                {
                    min=a[j+1][i];
                    count ++;
                    printf("%d < %d",a[j][i],temp);
                }
            } ///////////////////////////////  
            else if(min < temp && (min+1) == temp)
            {
                count++;
                printf(" < %d",temp);
            }
            else if(min == temp || min+1 != temp)
            {       
                min=0;
                printf("\n");
            }
            if(count>=k)
                c1++;
        }
        printf("\n");
    }
    if(c1>=w)
        return true;
    
    return false;
}
//---------------------------------------------------
char* confronto_stringhe(char* stringa)
{
    int l = strlen(stringa);
    char* s1 = (char*)malloc((l + 1) * sizeof(char)); // Allocazione dinamica della memoria
    strcpy(s1,stringa);
    for(int i=0;i<l;i++)
        s1[i] = tolower(s1[i]);
    
    return s1;
}
//---------------------------------------------------
bool case7(char *a[n][m], char s[])
{
    bool check=true,check2=false;
    int ans=-1,count=0,indici[n],k=0;
    for(int i=0;i<n;i++)
        indici[i]=-1;
    do
    {
        printf("\nVuoi effettuare il confronto di stringhe in maniera case sensitive?\nSI --> 1\nNO --> 0\nInserisci un opzione: ");
        scanf("%d",&ans);
        if(ans != 1 && ans != 0)
            printf("\nInserisci un valore appropriato...Riprova:\n");
        else if(ans == 0)
            printf("\nHai scelto un tipo di confronto a base case INSensitive, nessun controllo tra maiuscole e minuscole...\n");
        else if(ans == 1)
            printf("\nHai scelto un tipo di confronto a base case Sensitive, controllo tra maiuscole e minuscole...\n");
    }while(ans != 1 && ans != 0);

    if(ans==0)
    {
        for(int i=0;i<n;i++)
        {
            printf("Riga n.%d\n",i);
            check=true; //reset check
            check2=false;
            for(int j=0;j<m;j++)
            { //////
                printf("- Colonna n.%d\n",j);
                if(strcmp(confronto_stringhe(a[i][j]),confronto_stringhe(s))==0)
                {
                    for(int l=0;l<m;l++)
                    {
                        if(indici[k]==j)
                        {
                            check=false; //check falso, indice già usato
                            printf("Numero colonna gia\' usata.\n");
                        }
                    }
                    if(check==true) //indice non usato, check invariato
                    {
                        indici[k]=j;
                        count++;
                        k++;
                        printf("--> Elemento trovato i[%d] j[%d]: %s == %s\n",i,j,a[i][j],s);
                        check2=true;
                    }
                }
                if(check2==true)
                    break;
            } //////
        }
    }
    else if(ans == 1)
    {
        for(int i=0;i<n;i++)
        {
            printf("Riga n.%d\n",i);
            check=true; //reset check
            check2=false;
            for(int j=0;j<m;j++)
            { //////
                printf("- Colonna n.%d\n",j);
                if(strcmp(a[i][j],s)==0)
                {
                    for(int l=0;l<m;l++)
                    {
                        if(indici[k]==j)
                        {
                            check=false; //check falso, indice già usato
                            printf("Numero colonna gia\' usata.\n");
                        }
                    }
                    if(check==true) //indice non usato, check invariato
                    {
                        indici[k]=j;
                        count++;
                        k++;
                        printf("--> Elemento trovato i[%d] j[%d]: %s == %s\n",i,j,a[i][j],s);
                        check2=true;
                    }
                }
                if(check2==true)
                    break;
            } //////
        }
    }
    printf("\nTrovati %d elementi.\n",count);
    if(count>=2)
        return true;
    return false;
}
//---------------------------------------------------
bool case8(char*A[n][m],char C[kk][zz],short w)
{
    bool result=false;
    int count=0, len;
//////////////////////// Blocco iterativo per A
    for(int i = 0; i < n; i++) 
    {
        printf("\nRiga n.%d:\n", i);
        for(int j = 0; j < m; j++) 
        {
            printf("- Colonna n.%d --> Stringa da analizzare: %s\n", j,A[i][j]);
            len = strlen(A[i][j]);
            count = 0; // reset count alla fine del blocco iterativo principale
            for(int l = 0; l < len; l++) 
            {
                //singoli caratteri di A[i][j]
                //////////////////// Blocco iterativo per C
                for(int b = 0; b < kk; b++) 
                {
                    for(int d = 0; d < zz; d++) 
                    {
                        // controllo per righe di C
                        if(A[i][j][l] == C[b][d]) 
                        {
                            count++;
                            printf("++ Trovata corrispondenza in : %c (%s) == %c\n", A[i][j][l], A[i][j], C[b][d]);
                        } 
                    }
                }
            }
            if(count >= w) 
            {
                printf("--> Trovato sequenza di %d elementi (richiesti in w: %hu).\n",count,w);
                result=true;
            }
            else if(count>0 && count<w)
                printf("--> Sequenza di %d elementi non sufficiente, richiesti: %hu.\n",count,w);
            else if(count==0)
                printf("--> Nessuna sequenza trovata %d elementi, richiesti: %hu.\n",count,w);
            count=0;
            printf("\n");
        }
    }
    return result;
}
//---------------------------------------------------
/*
To find out if the input is a letter or a digit:

int isalpha ( int c ); function to verify whether c is an alphabetic letter.
int isalnum ( int c ); function to verify whether c is either a decimal digit or an uppercase or lowercase letter.
int isdigit ( int c ); function to verify whether c is a decimal digit character.
To find out if the letter is uppercase or lowercase:

int islower ( int c ); to checks whether c is a lowercase letter: a-z
int isupper ( int c ); to checks whether c is a uppercase letter: A-Z
Fonte: StackOverflow*/

bool case9(char C[n][m],int a)
{
    int cmin=0,cmaiusc=0,count=0;
    for(int i=0;i<n;i++)
    {
        printf("Riga n.%d:\n",i);
        cmin=0;
        cmaiusc=0;
        for(int j=0;j<m;j++)
        {
            if(islower(C[i][j])) //se minuscolo
            { 
                cmin++;
                if(cmaiusc>=a)
                {
                    printf("Trovata sequenza di caratteri maiuscoli maggiori o uguali alla variabile intera a: %d (seq) >= %d (a)\n",cmaiusc,a);
                    count++;
                }
                cmaiusc=0;
            }
            else //allora maiuscolo
            {
                cmaiusc++;
                if(cmin>=a)
                {
                    printf("Trovata sequenza di caratteri minuscoli maggiori o uguali alla variabile intera a: %d (seq) >= %d (a)\n",cmin,a);
                    count++;
                }
                cmin=0;
            }
            //Nel caso in cui si tratti dell'ultima cella della matrice, allora esegui la stampa (altrimenti non possibile):
            if(j==m-1)
            {
                if(cmaiusc>=a)
                {
                    printf("Trovata sequenza di caratteri maiuscoli maggiori o uguali alla variabile intera a: %d (seq) >= %d (a)\n",cmaiusc,a);
                    count++;
                }
                else if(cmin>=a)
                {
                    printf("Trovata sequenza di caratteri minuscoli maggiori o uguali alla variabile intera a: %d (seq) >= %d (a)\n",cmin,a);
                    count++;
                }
            }
        }
    }
    if(count>0) //Controllo e stampa finale
    {
        printf("\nNumero di sequenze di minuscole o maiuscole trovate: %d\n",count);
        return true;
    }
    return false;
}
//---------------------------------------------------
char** case10(char***A, short k, char* s)
{
    char **ris = (char**)malloc(((n+1)*sizeof(char*)));
    for(int i=0;i<n;i++)
    {
        ris[i] = (char*)malloc(15*sizeof(char));
    }
    /*Per non andare a scorrere tutta la matrice, posso solo scorrere il primo indice i, e calcolare j per la diagonale secondaria
    Con la formula n-i-1, se per esempio: n = 3
    allora: 
    1. 3-0-1 = 2 --> a[0][2]           
    2. 3-1-1 = 1 --> a[1][1]     
    3. 3-2-1 = 0 --> a[2][0]
    */ 
    int cont=0,c1=0;
    int len=strlen(s);
    printf("Corrispondenza tra stringa e matrice nella sola diagonale secondaria:\n");
    for(int i=0;i<n;i++) //scorrimento matrice A
    {
        printf("\nParola da analizzare: %s\n",A[i][n-i-1]);
        if(strlen(A[i][n-i-1])>=k)
        {
            cont=0; //reset contatore
            for(int j=0;j<len;j++) //scorrimento caratteri per confronto matrice A - stringa s
            {
                if(s[j] == A[i][n-i-1][j])
                {
                    cont++;
                    printf("%c == %c\n",s[j],A[i][n-i-1][j]);
                }
            }
            if(cont==len)
            {
                printf("Stringa trovata: %s --> Inizia con: %s; contatore %d\n",A[i][n-i-1],s,c1);
                strcpy(ris[c1],A[i][n-i-1]);
                c1++;
            }
            else printf("Corrispondenza con \'%s\' non trovata.\n",s);
        }
    }
    if(c1!=0)
        ris[c1+1] = NULL;
    else ris[c1] = NULL;
    return ris;
}
//---------------------------------------------------
double* case11(int**A,int**B)
{
    //A = k x n
    //B = n x k
    int min=0;
    double s=0;
    double* C = (double*)malloc(kk*sizeof(double));
    printf("Righe di A:\n");
    for(int i=0;i<kk;i++)
    { 
        s=0; //reset somma
        printf("Riga n.%d:\n",i);
        for(int j=0;j<n;j++)
        {
            if(j==0)
            {
                s=A[i][j];
                printf("A[%d][%d] --> Valore = %d --> Somma = %.0f\n",i,j,A[i][j],s);
            }
            else
            {
                s+=A[i][j];
                printf("A[%d][%d] --> Valore = %d --> Somma = %.0f\n",i,j,A[i][j],s);
            }
        }
        C[i]=(double)(s/kk); //media righe di A
        printf("Media righe di A[%d]: %.2f\n",i,C[i]);
    }
    printf("\nColonne di B:\n");
    for(int i=0;i<kk;i++)
    {
        printf("Colonna n.%d:\n",i);
        for(int j=0;j<n;j++)
        { 
            printf("B[%d][%d] --> Valore = %d\n",j,i,B[j][i]);
            if(j==0)
                min=B[j][i];
            else
            {
                if(B[j][i]<min)
                    min=B[j][i];
            }
        }
        printf("Media righe A[%d] = %.2f ; Valore minimo: %d ; ",i,C[i],min);
        C[i] -= (double)(min);
        printf("Differenza media-min: %.2f.\n",C[i]);
    }
    printf("\n");
    /*printf("Valori di C:\n");
    for(int i=0;i<kk;i++)
    {
        printf("%.2f\n",C[i]);
    }*/

    return C;
}
//---------------------------------------------------
char caratteri_random()
{
    //srand da mettere nel singolo case (case12)
    //26 caratteri minuscoli dell'alfabeto
    //char v_char[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char v_char[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z','a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    int r = rand() % (51-0+1) + 0; //26-1 solo min, 52-1 maiusc e min
    char ris=v_char[r];   
    return ris;
}
//---------------------------------------------------
void gen_stringhe_casuali(char**S, int n1)
{
    srand(time(NULL));
    char v_stringhe[30][20] = {"Albero", "Casa", "Libro", "Amore", "Gatto", "Cane", "Barca", "Natura", "Musica", "Arte", "Scienza", "Sport", "Viaggio", "Cucina", "Famiglia", "Amicizia", "Lavoro", "Storia", "Cultura", "Speranza", "Salute", "Pranzo", "Tristezza", "Rabbia", "Paura", "Sorpresa", "Disgusto", "Coraggio", "Pazienza", "Gentilezza"};
    for(int i=0;i<n1;i++)
    {
        int r = rand() % (29-0+1) + 0;
        strcpy(S[i],v_stringhe[r]);
    }

    printf("Array di %d elementi, creato con i seguenti elementi:\n{ ",n1);
    for(int i=0;i<n1;i++)
    {
        if(i==n1-1)
            printf("%s. ",S[i]);
        else printf("%s, ",S[i]);
    }
    printf("}\n\n");
}
//---------------------------------------------------
char**case12(char**S,char**C,int n3,int n2,int n1,short k)
{
    char**ris = (char**)malloc(n3 * sizeof(char));
    for(int i=0;i<n3;i++)
        ris[i] = malloc(20 * sizeof(char));
    
    int count=0,c1=0;
    for(int i=0;i<n3;i++) //scorrimento array S
    { //es. prima stringa
        count=0;
        printf("Parola da analizzare: %s\n",S[i]);
        for(int j=0;j<(strlen(S[i]));j++) // caratteri di S
        {
            //entra nello scorrimento
            for(int l=0;l<n1;l++) //scorrimento tutto array C per confronto con S[i] -->
            {
                for(int p=0;p<n2;p++)
                {
                    if(S[i][j] == C[l][p]) //es. S[0][0] (riga n.0, carattere n.0) == ?  C[0][0] (riga n.0, colonna n.0)
                    {
                        printf("%c == %c\n",S[i][j],C[l][p]);
                        count++;
                    }
                }
            }
        } 
        if(count>=k)
        {
            c1++;
            printf("Trovato: Stringa con %d elementi corrispondenti alla ricerca.\n\n",count);
            strcpy(ris[i],S[i]);
        }
        else
        {
            printf("Elementi non sufficenti.\n");
            ris[i] = NULL;
        }
    }
    if(c1==0)
        printf("\nNessuna stringa con elementi corrispondenti alla ricerca sufficienti.\n");
    else printf("\nTrovati %d elementi corrispondenti alla ricerca.\n",c1);
    return ris;
}
//---------------------------------------------------
char**case13(char***A,short**B,int n1,int n2)
{
    char**ris = (char**)malloc((n1*n2) * sizeof(char));
    int l=0;
    for(int i=0;i<(n1*n2);i++)
    {
        ris[i] = malloc(20 * sizeof(char));
    }
    for(int i=0;i<n1;i++)
    {
        printf("Riga n.%d\n",i);
        for(int j=0;j<n2;j++)
        {
            printf("Parola da analizzare: %s\n",A[i][j]);
            printf("A[%d][%d] --> %s (%d caratteri) >= B (%hu)\n",i,j,A[i][j],strlen(A[i][j]),B[i][j]);
            if(strlen(A[i][j])>=B[i][j])
            {
                printf("Stringa valida.\n");
                strcpy(ris[l],A[i][j]);
                l++;
            }
            else printf("Lunghezza non sufficiente.\n");
            printf("\n");
        }
    }
    /* Debug
    printf("Stringhe valide:\n");
    for(int i=0;i<l;i++)
    {
        printf("%s\n",ris[i]);
    }*/
    ris[l]=NULL;
    return ris;
}
//---------------------------------------------------
short case14(char ***S,short*B,int n1, int n2)
{
    short res = 1;
    for(int i=0;i<n1;i++)
    {
        printf("Riga n.%d\n",i);
        for(int j=0;j<n2;j++)
        {
            printf("Parola da analizzare: %s ; lunghezza = %d ; B[%d] = %hu\n",S[i][j],strlen(S[i][j]),j,B[j]);
            if(strlen(S[i][j]) >= B[j])
                printf("Stringa maggiore o uguale a B.\n");
            else printf("Stringa non sufficientemente lunga.\n");
            if(strlen(S[i][j]) > res)
                res=strlen(S[i][j]);
            printf("\n");
        }
        printf("\n");
    }
    return res;
}
//---------------------------------------------------
short*case15(char ***A,char*B,char*C,int n1, int n2)
{
    short *ris = (short*)malloc(n1* sizeof(short));
    
    for(int i=0;i<n1;i++)
    {
        printf("Riga n.%d:\n",i);
        ris[i]=0;
        for(int j=0;j<n2;j++)
        {
            int len=strlen(A[i][j]);
            if(A[i][j][0] == B[i] && A[i][j][len-1] == C[i])
            {
                ris[i]++;
                printf("Stringa A[%d][%d] inizia con B[%d] e finisce con C[%d] --> %s (inizia: %c) (finisce: %c).\n",i,j,i,i,A[i][j],B[i],C[i]);
            }
            else
            {
                printf("Stringa non corrispondente ai criteri di ricerca.\n");
            }
        }
    }
    return ris;
}
//---------------------------------------------------
int case16(double**A,int*B, int n1, int n2)
{
    int result=-1;
    int cont=0,c1=0;
    for(int j=0;j<n2;j++)
    {
        cont=0; //fine colonna, reset
        printf("Colonna n.%d",j);
        printf(" -- Valori confrontati con B[%d] = %d:\n",j,B[j]);
        for(int i=0;i<n1;i++)
        {
            if(round(A[i][j]) == B[j])
            {
                cont++;
                printf("- Trovato in A[%d][%d] = %d (%.2f) e B[%d] = %d\n",i,j,(int)(round(A[i][j])),A[i][j],j,B[j]);
            }
        }
        if(cont>0 && c1==0) //solo per la prima condizione positiva
        {
            c1=cont;
            result=j;
            printf("--> Elementi trovati: %d\n",cont);
        }
        else if(cont>0 && cont>c1) //per le altre condizioni positive...
        {
            c1=cont;
            result=j;
            printf("--> Elementi trovati: %d\n",cont);
        }
        else printf("--> Elementi trovati: %d\n",cont);
        printf("\n");
    }
    return result;
}
//---------------------------------------------------
/*int case16_alt(double**A,int*B,int n1, int n2)
{
    int result=-1;
    int cont=0,c1=0;
    for(int j=0;j<n2;j++)
    {
        printf("Colonna n.%d --> Confrontati con tutto l'array di B:\n",j);
        cont=0;
        for(int i=0;i<n1;i++)
        {
            for(int l=0;l<n1;l++)
            {
                if(round(A[i][j]) == B[l])
                {
                    cont++;
                }
            }
        }
        if(cont>0 && c1==0) //solo per la prima condizione positiva
        {
            c1=cont;
            result=j;
            printf("--> Elementi trovati: %d\n",cont);
        }
        else if(cont>0 && cont>c1) //per le altre condizioni positive...
        {
            c1=cont;
            result=j;
            printf("--> Elementi trovati: %d\n",cont);
        }
        else printf("--> Elementi trovati: %d\n",cont); //nessun elemento trovato o condizione non sufficiente...
    }
    return result;
}*/
//---------------------------------------------------
int main()
{
    int n_menu,cc=-1 ;
    do
    {
        char indice_menu[] = "1) 16.1\n2) 16.2\n3) 16.3\n4) 16.4\n5) 16.5\n6) 16.6\n7) 16.7\n8) 16.8\n9) 16.9\n10) 16.10\n11) 16.11\n12) 16.12\n13) 16.13\n14) 16.14\n15) 16.15\n16) 16.16\n";
        int n_esercizi = 16;
        n_menu = menu(indice_menu,n_esercizi); //Benvenuto nel menu'
        
        switch(n_menu)
        {
            case 0:
            {
                printf("Terminazione del programma... A presto!\n\n><-><-><-><-><-><-><-><-><-><-><-><\n\n");
                break;
            }
            case 1:
            {
                printf("Esercizio n.1:\nSeguendo la traccia:\nCodificare una funzione C che prenda in input un parametro formale matrice M di dimensioni n x m di stringhe (puntatori a caratteri),\nche restituisca il valore true (1) se esiste almeno una colonna in M che abbia un egual numero di stringhe palindrome di una delle righe di M.\n");
                char *M[n][m];
                gen_stringhe_nm(M);
                bool r = case1(M);
                if(r == true)
                {
                    printf("Vero: ");
                }
                else printf("Falso: ");
                printf("%d\n",r);

                deallocazione_char(M);
                break;
            }
            case 2:
            {
                printf("Esercizio n.2:\nSeguendo la traccia:\nCodificare una funzione in C che prenda in input tre parametri formali:\nUna matrice di stringhe S di dimensioni n x m, un array di caratteri C che contiene per ipotesi elementi distinti, ed un float w.\nIl metodo restituisca true se esiste almeno una riga o una colonna della matrice tale che la percentuale di caratteri di C presenti in essa e\' maggiore di w.\n");
                char *S[n][m];
                gen_stringhe_nm(S);
                char C[m];
                float w = delta;
                bool r = case2(S,C,w);
                if(r == true)
                {
                    printf("Vero: ");
                }
                else printf("Falso: ");
                printf("%d\n",r);
                deallocazione_char(S);
                break;
            }
            case 3:
            {
                printf("Esercizio n.3:\nSeguendo la traccia:\nCodificare una funzione in C che prenda in input due parametri formali:\nUna matrice A di dimensioni n x m ed una matrice B di dimensioni k x n entrambe di interi positivi.\nIl metodo restituisca un array C di double di dimensione n nel quale lo i-esimo elemento dello array C sia uguale\nal rapporto tra la somma degli elementi della riga i-esima di A e il prodotto degli elementi della colonna i-esima di B.\n\n");
                int k=3;
                //int A[n][m], B[k][n];

                int **A = allocazione_int(n,m);
                if(A == NULL)
                    printf("Errore di allocazione della memoria.\n");
                int **B = allocazione_int(k,n);
                if(B == NULL)
                    printf("Errore di allocazione della memoria.\n");

                gen_numeri_int(A,n,m);
                gen_numeri_int(B,k,n);
                
                double* C = case3(k,A,B);
                printf("Valori di C:\n");
                for(int i=0;i<n;i++)
                {
                    printf("%.2f\n",*(C+i));
                }

                deallocazione_int(A,n,m);
                deallocazione_int(B,k,n);
                break;
            }
            case 4:
            {
                printf("Esercizio n.4:\nSeguendo la traccia:\nCodificare una funzione in C che prenda in input un parametro formale array A di interi di dimensioni n x m di elementi distinti ed un array B di double di dimensioni k x n,\ne restituisca un array di n interi nel quale lo i-esimo elemento sia uguale alla media aritmetica degli elementi presenti sia nella riga i-esima di A\nche nella colonna i-esima di B.\nNB: per decidere se un elemento int della matrice A e' uguale ad un elemento double della matrice B si calcoli l'approssimazione all'intero piu' vicino di quest'ultimo.\n");
                int k=3;
                int **A = allocazione_int(n,m); //A[n][m]
                double **B = allocazione_double(k,n); //B[k][n]

                gen_numeri_int(A,n,m);
                gen_numeri_double(B,k,n);

                
                int *array = case4(k,A,B);
                for(int i=0;i<n;i++)
                {
                    printf("Media righe A - colonne B indice [%d] --> %d\n",i,*(array+i)); 
                }        
                break;
            }
            case 5:
            {
                printf("Esercizio n.5:\nSeguendo la traccia:\nCodificare una funzione in C che prenda in input un parametro formale matrice S di puntatori a carattere di dimensione n x m\n S quindi contiene stringhe), uno short w ed uno short k.\nSi deve restituire il valore booleano true (1)\nse in S sono presenti almeno una riga ed almeno una colonna che presentano ciascuna almeno w stringhe di lunghezza minore di k.\n");
                
                char *S[n][m];
                gen_stringhe_nm(S);
                short w = 2, k = 5; //w stringhe ; k lunghezza
                
                bool ris = case5(S,w,k);
                printf("\nRisultato: %s\n", ris ? "Vero" : "Falso");
                break;
            }
            case 6:
            {
                printf("Esercizio n.6:\nSeguendo la traccia:\nCodificare una funzione in C che prenda in input un parametro formale:\nUna matrice A di interi di dimensioni n x m, uno short k ed uno short w,\ne restituisca il valore booleano true (1) se la matrice contiene almeno w colonne\n che contengono almeno una sequenza di interi monotona crescente di lunghezza maggiore o uguale a k.\n");
                int **A = allocazione_int(n,m);
                short k = 3, w = 2;
                gen_numeri_int(A,n,m);

                bool ris = case6(A,w,k);
                printf("\nRisultato: %s\n", ris ? "Vero" : "Falso");

                deallocazione_int(A,n,m);
                break;
            }
            case 7:
            {
                printf("Esercizio n.7:\nSeguendo la traccia:\nCodificare una funzione in C che prenda in input un parametro formale A matrice di stringhe di dimensione n x m, ed una stringa s.\nIl metodo restituisca true (1) se esistono almeno due stringhe in A che contengono la stringa s e che abbiano differenti indici di riga e di colonna.\n");
                char*A[n][m];
                gen_stringhe_nm(A);
                char s[10] = "Albero";
                bool ris = case7(A,s);
                printf("\nRisultato: %s\n", ris ? "Vero" : "Falso");
                deallocazione_char(A);
                break;
            }
            case 8:
            {
                printf("Esercizio n.8:\nSeguendo la traccia:\nCodificare una funzione C che prenda in input dei parametri formali:\n- Matrice di stringhe A di dimensioni n x m, una matrice di caratteri C di dimensioni k x z, uno short w e,\nrestituisca true se esiste almeno una riga o una colonna di A che contiene almeno una sequenza contigua di w\noppure, piu\' caratteri che si trovano in una riga o in una colonna di C.\n");
                printf("\nProcedimento:\n");
                char*A[n][m];
                gen_stringhe_nm(A);
                char C[kk][zz];
                short w=3;
                gen_alfabeto_char_kz(C);

                bool ris = case8(A,C,w);
                printf("\nRisultato: %s\n", ris ? "Vero" : "Falso");
                
                deallocazione_char(A);
                break;
            }
            case 9:
            {
                printf("Esercizio n.9:\nSeguendo la traccia:\nCodificare una funzione C che prenda in input:\nUna matrice di caratteri di dimensione n x m ed un ulteriore parametro intero a, e,\nrestituisca il valore booleano \'true\' (1) se esiste almeno una riga o una colonna che contiene almeno a caratteri che siano:\ntutti minuscoli o tutti maiuscoli e che abbiano posizioni adiacenti.\nNota: Si assuma che la matrice contenga solo caratteri corrispondenti alle lettere dell'alfabeto.\n");
                printf("\nProcedimento:\n");
                char C[n][m];
                gen_alfabeto_char_nm(C);
                int a=2;
                bool ris = case9(C,a);
                printf("\nRisultato: %s\n", ris==true ? "Vero" : "Falso");
                break;
            }
            case 10:
            {
                printf("Esercizio n.10:\nSeguendo la traccia:\nCodificare una funzione C che prenda un parametro formale:\nUna matrice quadrata di stringhe (puntatori a caratteri) di dimensioni n x n, uno short k ed una ulteriore stringa s,\ne restituisca un array di n stringhe (puntatori a caratteri) il cui generico elemento di indice i contenga la i-esima stringa della diagonale secondaria.\nSe questa stringa ha lunghezza maggiore o uguale a k e inizia con la stringa s,\naltrimenti la corrispondente stringa (i-esima) della diagonale principale.\n");
                printf("\nProcedimento:\n");
                //n già dichiarata in quanto definita come costante...
                int n1=n,n2=n;
                char ***A = allocazione_matrice_char(n1,n2);
                gen_matrice_stringhe(A,n,n);
                short k=3;
                char s[10] = "Alb";
                char **ris = case10(A,k,s);
                printf("\nRisultato:\n");
                if(ris[0] == NULL)
                    printf("Nessun elemento corrispondente.\n");
                else
                {
                    for(int i=0;ris[i]!=NULL;i++)
                        printf("%s\n",ris[i]);
                }
                /* //Si potrebbe anche fare:
                int i=0;
                do
                {
                    if(ris[0] == NULL)
                    {
                        printf("Nessun elemento corrispondente.\n");
                        break;
                    }
                    printf("%s\n",ris[i]);
                    i++;
                }while(ris[i]!=NULL)
                */
                deallocazione_matrice_char(A,n1,n2);
               //deallocazione della memoria
               /*
                for (int i = 0; i < n1; i++)
                {
                    for (int j = 0; j < n2; j++)
                    {
                        free(A[i][j]); // Libera ogni stringa
                    }
                    free(A[i]); // Libera ogni riga
                }
                free(A); // Libera la matrice
                printf("\nDeallocazione della matrice di stringhe completata con successo...\n");
                */
                break;
            }
            case 11:
            {
                printf("Esercizio n.11:\nSeguendo la traccia:\nCodificare una funzione in C che prenda in input:\ndue matrici di interi, A e B di dimensioni k x n ed n x k rispettivamente,\nrestituisca uno array monodimensionale di k elementi double in cui lo i-esimo elemento sia uguale\nalla differenza tra la media aritmetica degli elementi della riga i-esima di A\ned il minimo valore degli elementi della colonna i-esima di B.\n");
                printf("\nProcedimento:\n");
                int **A = allocazione_int(kk,n);
                int **B = allocazione_int(n,kk);
                gen_numeri_int(A,kk,n);
                gen_numeri_int(B,n,kk);

                printf("\nRisultato:\n");
                double*C = case11(A,B);
                for(int i=0;i<kk;i++)
                    printf("%.2f\n",C[i]); 
                
               deallocazione_int(A,kk,n);
               deallocazione_int(B,n,kk);
                break;
            }
            case 12:
            {
                srand(time(NULL));
                printf("Esercizio n.12:\nSeguendo la traccia:\nCodificare una funzione C che prenda in input:\nun array monodimensionale S di n puntatori a caratteri (stringhe), una matrice C di caratteri distinti (char) ed uno short k,\nrestituisca un array di n puntatori a caratteri (strighe) in cui il generico elemento di indice i punta alla i-esima stringa in S\nsolo se questa contiene almeno k caratteri in C, altrimenti NULL\n");
                printf("\nProcedimento:\n\n");
                
                int n1 = 4, n2 = 3, n3 = 10;
                short k=3;

                //allocazione dinamica  
                char**s = (char**)malloc(n3 * sizeof(char*));
                for(int i=0;i<n3;i++)
                {
                    s[i] = (char*)malloc(20 * sizeof(char));
                }
                gen_stringhe_casuali(s,n3);

                //allocazione dinamica per la matrice di caratteri
                char**C = (char**)malloc(n1 * sizeof(char*));
                for(int i=0;i<n1;i++)
                {
                    C[i] = (char*)malloc(n2 * sizeof(char));
                }

                printf("Stampa caratteri casuali generati:\n");
                for(int i=0;i<n1;i++)
                {
                    printf("\n");
                    for(int j=0;j<n2;j++)
                    {
                        C[i][j] = caratteri_random();
                        printf("%c ",C[i][j]);
                    }
                }
                printf("\n\n");
                printf("Funzione di ricerca caratteri in comune della matrice C con l'array di stringhe S:\n\n");
                char**ris = case12(s,C,n3,n2,n1,k);
                printf("\nRisultato:\n");
                for(int i=0;i<n3;i++)
                {
                    printf("%s\n",ris[i]);
                }
                break;
            }
            case 13:
            {
                printf("Esercizio n.13:\nSeguendo la traccia:\nCodificare una funzione in C che prenda in input due parametri formali:\nuna matrice A di stringhe (puntatori a caratteri) ed una matrice B di short, entrambe di dimensioni n x m.\nIl metodo restituisca un array di n stringhe, nel quale,\nil generico elemento di indice i sarà uguale alla concatenazione delle sole stringhe della riga i-esima di A\nche hanno lunghezza pari o maggiore del corrispondente numero in B\n(cioè bisogna confrontare la lunghezza della stringa aij con il numero bij.\n");
                printf("\nProcedimento:\n");

                srand(time(NULL));
                int n1=n,n2=m;
                ///////////////////////////
                //allocazione dinamica della matrice di stringhe A
                char***A = (char***)malloc(n1*sizeof(char**));
                for(int i=0;i<n1;i++)
                {
                    A[i] = (char**)malloc(n2*sizeof(char*));
                    for(int j=0;j<n2;j++)
                    {
                        A[i][j] = (char*)malloc(20*sizeof(char));
                    }
                }
                printf("Creazione matrice di stringhe A:\n");
                gen_matrice_stringhe(A,n1,n2);
                ///////////////////////////
                //allocazione dinamica della matrice di short B
                short**B = (short**)malloc(n1*sizeof(short*));
                for(int i=0;i<n1;i++)
                {
                    B[i] = (short*)malloc(n2*sizeof(short));
                }
                for(int i=0;i<n1;i++)
                {
                    for(int j=0;j<n2;j++)
                    {
                        int r = rand() % (10-1+1) + 1;
                        B[i][j]=r;
                    }
                }
                printf("\nMatrice B di variabili short (valori tra 1-10):\n");
                for(int i=0;i<n1;i++)
                {
                    printf("\n");
                    for(int j=0;j<n2;j++)
                    {
                        printf("%hu ",B[i][j]);
                    }
                }
                printf("\n");
                char**ris = case13(A,B,n1,n2);
                printf("\nRisultato:\n");
                for(int i=0;ris[i]!=NULL;i++)
                {
                    printf("%s\n",ris[i]);
                }
                ///////////////////////////
                //Deallocazione di A
                for(int i = 0; i < n1; i++)
                {
                    for(int j = 0; j < n2; j++)
                    {
                        free(A[i][j]);
                    }
                    free(A[i]);
                }
                free(A);

                //Deallocazione di B
                for(int i = 0; i < n1; i++)
                {
                    free(B[i]);
                }
                free(B);
                break;
            }
            case 14:
            {
                srand(time(NULL)); 
                printf("Esercizio n.14:\nSeguendo la traccia:\nCodificare una funzione in C che prenda in input una matrice S di stringhe\n(puntattori a caratteri) di dimensioni n x m ed un array B di short di dimensione m\ne che restituisca uno short che rappresenti l'indice della riga in S\ncon il maggior numero di stringhe aventi lunghezza minore o uguale del corrispondente numero nello array B.\n");
                printf("\nProcedimento:\n");
                
                int n1 = n, n2 = m; 
                char***S = allocazione_matrice_char(n1,n2);
                gen_matrice_stringhe(S,n1,n2);

                short*B = (short*)malloc(n2 * sizeof(short));
                printf("[ ");
                for(int i=0;i<n2;i++)
                {
                    B[i] = rand() % (10 - 3 + 1) + 3;
                    if(i==n2-1)
                        printf("%hu. ]",B[i]);
                    else printf("%hu, ",B[i]);
                }
                printf("\n\n");

                
                short ris = case14(S,B,n1,n2);
                printf("\nRisultato: %hu\n",ris);
                
                //deallocazione S:
                for(int i = 0; i < n1; i++)
                {
                    for(int j = 0; j < n2; j++)
                    {
                        free(S[i][j]);
                    }
                    free(S[i]);
                }
                free(S);
                printf("Deallocazione di S effettuata con successo...\n");
                //deallocazione B:
                free(B);
                printf("Deallocazione di B effettuata con successo...\n");
                break;
            }
            case 15:
            {
                srand(time(NULL));
                printf("Esercizio n.15:\nSeguendo la traccia:\nCodificare una funzione in C che prenda in input una matrice di stringhe S (puntatori a caratteri) di dimensione n x m\ne due array di caratteri C e D di dimensione n,\nrestituire un array di short nel quale il generico elemento di posto i contiene\nil numero di stringhe che iniziano con il carattere di C\ndi indice i e finiscono con il carattere in D di indice i.\n");
                printf("\nProcedimento:\n");
                int n1=6,n2=3; //n1 = n, n2= m;

                char***S = (char***)malloc(n1*sizeof(char**));
                for(int i=0;i<n1;i++)
                {
                    S[i] = (char**)malloc(n2*sizeof(char*));
                    for(int j=0;j<n2;j++)
                        S[i][j] = (char*)malloc(max_caratteri * sizeof(char));
                }
                printf("Creazione matrice di stringhe:\n");
                gen_matrice_stringhe(S,n1,n2);
                ////////////////////////////////////////
                char*C = (char*)malloc(n1 * sizeof(char));
                char*D = (char*)malloc(n1 * sizeof(char));
                
                printf("Creazione array di caratteri C:\n");
                printf("{ ");
                for(int i=0;i<n1;i++)
                {
                    //C[i] = caratteri_random();
                    //oppure: Array con le lettere iniziali più frequenti nella matrice di stringhe...
                    char v[] = {'A','S','C','P','N','M','F'};
                    int r = rand() % (6 - 0 + 1) + 0;
                    C[i] = v[r];

                    if(i==n1-1)
                        printf("%c. }\n\n",C[i]);
                    else printf("%c, ",C[i]);
                }
                ////////////////////////////////////////
                printf("Creazione array di caratteri D:\n");
                printf("{ ");
                for(int i=0;i<n1;i++)
                {
                    //D[i] = caratteri_random();
                    //oppure: Array con le lettere finali più frequenti nella matrice di stringhe...
                    char v[] = {'a','e','i','o','u'}; //tutte le vocali...
                    int r = rand() % (4 - 0 + 1) + 0;
                    D[i] = v[r];

                    if(i==n1-1)
                        printf("%c. }\n\n",D[i]);
                    else printf("%c, ",D[i]);
                }
                ////////////////////////////////////////
                short*risult = case15(S,C,D,n1,n2);
                printf("\nRisultato:\n");
                for(int i=0;i<n1;i++)
                {
                    printf("%hu\n",risult[i]);
                }

                ////////////////////////////////////////
                printf("Deallocazione delle variabili:\n");
                for(int i=0;i<n1;i++)
                {
                    for(int j=0;j<n2;j++)
                    {
                        free(S[i][j]);
                    }
                    free(S[i]);
                }
                free(S);
                printf("Matrice di stringhe S deallocata con successo...\n");
                free(C);
                printf("Array di caratteri C deallocato con successo...\n");
                free(D);
                printf("Array di caratteri D deallocato con successo...\n");
                printf("\n\n");
                ////////////////////////////////////////
                break;
            }
            case 16:
            {
                printf("Esercizio n.16:\nSeguendo la traccia:\nCodificare una funzione in C che prenda un parametro formale:\n matrice A di double di dimensioni n x k ed un array B di interi di dimensione n,\nrestituisca l'indice della colonna in A che contiene il maggior numero di elementi tali che\nl\'approssimazione dell\'elemento stesso al numero intero piu\' vicino\nsia uguale al corrispondente elemento intero in B.\n(NB: in pratica il generico elemento di indice (i,j) va confrontato con l\'elemento in B di indice i).\n");
                printf("\nProcedimento:\n\n");

                srand(time(NULL));
                int n1=5, n2= 4; //n1 = n, n2 = kk; 
                //////////////////////////////////////////
                double**A = (double**)malloc(n1*sizeof(double*));
                for(int i=0;i<n1;i++)
                {
                    A[i]=(double*)malloc(n2*sizeof(double));
                }
                //Creazione valori di A...
                for(int i=0;i<n1;i++)
                {
                    for(int j=0;j<n2;j++)
                    {
                        A[i][j] = (double)rand() / (double)RAND_MAX * (9.99 - 0.7) + 0.7;
                    }
                }
                //////////////////////////////////////////
                int *B = (int*)malloc(n1*sizeof(int));
                //creazione valori di B...
                for(int i=0;i<n1;i++)
                {
                    B[i] = rand() % (10 - 1 + 1) + 1;
                }
                //////////////////////////////////////////
                printf("                Matrice di double A:        Array di interi B:\n");
                for(int i=0;i<n1;i++)
                {
                    printf("Riga n.%d  || ",i);
                    for(int j=0;j<n2;j++)
                    {
                        if(j==n2-1)
                            printf("%.2f ||  ", A[i][j]);
                        else printf("%.2f | ", A[i][j]);
                    }
                    if(B[i] >= 10)
                        printf("          %d           ||\n",B[i]);
                    else printf("          %d            ||\n",B[i]);
                }
                /////////
                //int ris1 = case16_alt(A,B,n1,n2);
                //printf("Ris alternativo = %d\n",ris1);
                /////////
                printf("\nRisultato:\n");
                int ris = case16(A,B,n1,n2);
                printf("Indice con piu\' elementi = %d\nNota: in questo esercizio se n > k allora ci saranno alcuni elementi che non verranno confrontati:\nEsempio n=5, k=4, l'ultima cella di B non verra\' controllata...\n",ris);
                break;
            }
        }
        //!!!
        if(n_menu==0)
        {
            cc=0;
        }
        else cc=menu1(); //tornare al menu si/no
        
        n_menu=-1; //reset var menu di sicurezza
    }while(cc==1);
} 

//gcc homework8.c menu.c -o homework8.exe
//.\homework8.exe