#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
double randomDouble() {
    return (double)rand() / (double)RAND_MAX;
}

#define a 6
#define b 1
int main()
{
   
    int indice;

    do
    {
        printf("Inserisci n. esercizio  (da 1 a 3):\n");
        scanf("%d", &indice);
    }while(indice < 1 || indice > 3);

    switch(indice) 
    {
        case 1:
        {
            int N;

            do
            {
                printf("Numero lanci dadi: ");
                scanf("%d",&N);
            }while(N<1);
    
            printf("\nNumero lanci: %d\n\n",N);
            int d1,d2;
    
            srand(time(0)); //inizializzazione numeri casuali

            printf("Tiro dei dadi:\n");
            for(int i=0; i<N;i++)
            {
                //tiro dei dadi
                d1 = (rand() % (a - b + 1) + b); //genera un numero compreso tra  1 e 6
                d2 = (rand() % (a - b + 1) + b); 
        
                printf("%d %d\n",d1,d2);
            }
            
            break;
        }

        case 2:
        {
            //calcolo della probabilità che un punto si trovi all'interno del quarto di cerchio.

            //AreaQuadrato = lato * lato = 1 * 1 = 1
            //AreaQuartoDiCerchio = AreaCerchio / 4 = π * raggio * raggio / 4 = π/4 (in quanto lato e raggio coincidono e quindi = 1)
            
            //NumeroPuntiInterni / NumeroPuntiTotali = AreaQuartoDiCerchio / AreaQuadrato = π/4
            
            
           
            int i, c = 0, campioni;
            double x, y;

            srand(time(0));

            printf("Numero di campionamenti: ");
            scanf("%d", &campioni);

            for (i = 0; i < campioni; i++) {
                x = randomDouble();
                y = randomDouble();

                if (x * x + y * y <= 1) {
                    c++;
                }

                if (i < 5) {
                    printf("Punto %d: (%lf, %lf)\n", i+1, x, y);
                }
            }

            double pi = (double)c / campioni * 4;

            printf("Stima di Pi dopo %d campionamenti: %lf\n", campioni, pi);

            break;
        }
    }
}