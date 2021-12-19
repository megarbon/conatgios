/*
 * Práctica 9
 * SIMULADOR DE EPIDEMIA
 *
 */

#include <stdio.h>
#include <stdlib.h> //Para rand() y RAND_MAX
#define N 50
#define M 20

/* Inicializa la matriz: cada persona se va a empezar a reir (valor 3)
 * con probabilidad prob_p y, si no, está seria (valor 0)
 */
void inicializar_matriz (int patio[N][M], float prob_p);


/* Devuelve 1 cuando algún vecino de i,j está riéndose (valores 1 o 2) */
int tiene_vecino_riendose (int patio[N][M], int i, int j);

/* Calcula el proximo estado de le matriz:
 * 1) Actualiza el estado de cada persona al pasar de un minuto
 * 2) Contagia (estado 3) con probabilidad R las personas que tienen 
 *    un vecino riéndose
 */
void actualizar_matriz (int patio[N][M], float prob_r);

/* Imprime la matriz usando los siguientes simbolos
 * Serio: " "
 * Riéndose: "."
 * Va a empezar a reír: "*"
 */
void print (int patio[N][M]);

/* void dimensionMatriz(int *filas, int *columnas){
    printf("Introduce la dimension del patio (filas, columnas): \n");
    scanf("%d, %d", filas, columnas);
}

int mayoriaContagiada(int matriz[N][M], int contagiados){
    return (contagiados >= (0.9*N*M) );
}
*/

/*** Función main. No modificar. ***/

int main (int argc, char const *argv[]) {

    float patio[N][M], i=0;
    float prob_p, prob_r;
    char salida;

    printf("EPIDEMIA DE RISA\n");

    // Entradas
    do {
        printf("Probabilidad P de empezar a reir? (Entre 0 y 1): ");
        scanf("%f",&prob_p);
        getchar();
    } while(prob_p>1 || prob_p <0);

    do {
        printf("Probabilidad R de contagio? (Entre 0 y 1): ");
        scanf("%f",&prob_r);
        getchar();
    } while(prob_r>1 || prob_r <0);


    //Inicialización
    printf("Situacion inicial: \n");
	    inicializar_matriz (patio, prob_p);
    print(patio);

    printf("Presionar ENTER para empezar la simulacion.");
    getchar();

    //Iteraciones
	    do {
        actualizar_matriz (patio, prob_r);

		  printf("\nMinuto %d: \n\n",++i);
		  print(patio);

		  printf("Presionar ENTER para continuar la simulacion. (q para salir)\n");
		  salida = getchar();
	    } while (salida!='q');

}


/* Función que se proporciona: devuelve 1 con probabilidad p */
int lanza_moneda (float p) {
    return rand() <= p*RAND_MAX;
}

/* Las siguientes funciones son STUBS, funciones vacías 
 * para que el programa compile.
 * Deben ser modificadas para resolver el ejercicio.
 */

void inicializar_matriz (int patio[N][M], float prob_p) {
    int i, j;
    int prob = 1/prob_p;  //la inversa de la probabilidad de contagiado inicial ej: 1/3 ---> 3
    for ( i = 0; i < N; i++){
        for(j = 0; j < M; j++){
            if( ( rand()%prob ) == (prob - 1) ){    // la probabilidad  de que salga cualquier valor con rand es 1/prob por lo que calculo la de cualquiera
                                                    // de los valores que pueden salir,  en este caso el del valor mas alto que es prob-1.
                patio[i][j] = 3;                    //si sale el valor mayo --> contagiado
            }
            else{
                patio[i][j] = 0;
            }
        }
    }
    
}

void print (int patio[N][M]) {
	//printf("Funcionalidad no disponible.\n");
      int i, j;
    for ( i = 0; i < N; i++){
        for(j = 0; j < M; j++){
            if(patio[i][j]){
                printf("*");
            }
            else{
                printf(" ");
                }           
            }
            
        }
        printf("\n");
    }

//para aplicar a los vecions de las esquinas y que la funcion tenga estructura toroidal utilizaremos el modulo para calcular vecinos (i-1)%filas , (j-1)%columnas
// asi en caso de llegar al borde empezaremos de nuevo. O al menos en python con pygame funciona así.

int tiene_vecino_riendose (int patio[N][M], int i, int j) {
    int fil, col, found = 0;
    for(fil = i-1; fil <= i+1 && !found; fil++){
        for(col = j-1; col <= j+1 && !found; col++){
            if((patio[fil][col] == '*') && !(fil==i && col==j)){
                found++;
            }
        }
    }
    return found;
}


void actualizar_matriz (int patio[N][M], float prob_r) {
    int i, j, prob = 1/prob_r;
    for(i = 0; i <N; i++){
        for(j = M; j <M; j++){
            if(patio[i][j] != 0){
                patio[i][j]--;
            }
            else if ((patio[i][j] == 0) && tiene_vecino_riendose(patio, i, j)){
                if( ( rand()%prob ) == (prob - 1) ){   
                patio[i][j] = 3;            
                    }
                else{
                patio[i][j] = 0;
                    }
            }
        }
    }
}
