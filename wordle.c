#include "wordle.h"

int main() {

    //VARIABLES
    int cantidadPartidas;
    int cantidadJugadas = 1;
    int cantidadGanadas = 0;
    char respuesta;
    char intento[MAXLETRAS];
    char pistaInicio[MAXLETRAS] = {'_', '_', '_', '_', '_', '\0'};
    char pista[MAXLETRAS];
    char palabraSecreta[MAXLETRAS];
    int intentosRestantes;
    int puntaje;
    char todasSecretas[MAXPARTIDAS][MAXLETRAS];
    int puntajes[MAXPARTIDAS];
    int puntajesVictorias[MAXPARTIDAS];
    int puntajeMayor;
    int puntajeMenor;

    //JUEGO
    Inicio();

    //SE LE PIDE AL JUGADOR QUE SELECCIONE LA CANTIDAD DE PARTIDAS QUE DESEA JUGAR
    printf(">Cuantas partidas deseas jugar? ");
    scanf("%d", &cantidadPartidas);
    cantidadPartidas = CantidadPartidas(cantidadPartidas);

    //SE CREA UN CONJUNTO DE 8 NUMEROS ALEATORIOS QUE NO SE REPITEN
    NrosAleatorios(nrosAleatorios);
    LecturaArchivo();

    //COMIENZAN LAS PARTIDAS
    for(int j=0; j<cantidadPartidas;j++){
        printf("\n>>Partida %d/%d:\nCual es la palabra secreta?\n", j+1, cantidadPartidas);
        printf("%s\n\n", pistaInicio);

        puntaje = 5000;
        intentosRestantes = 5;

        int posicion = nrosAleatorios[j];
        strcpy(palabraSecreta, palabras[posicion-1]);

        printf("%s\n", palabraSecreta);//ESTA ES LA PALABRA A ADIVINAR, COMENTARLA EN CASO DE JUGAR

        //SE GUARDAN TODAS LAS PALABRAS SECRETAS DE LA PARTIDA
        strcpy(todasSecretas[j], palabras[posicion-1]);

        for(int i = 0; i < MAXINTENTOS; i++){
            printf(">Intento %d/%d:\n", i+1, MAXINTENTOS);
            do{
                printf("Ingrese una palabra de 5 letras:\n");
                scanf("%s", intento);
                strupr(intento);//PONE LAS LETRAS EN MAYUSCULA
            }while((strlen(intento))!=5);

            //SE COMIENZAN A COMPARAR LA PALABRA SECRETA CON LA PALABRA QUE INGRESA EL JUGADOR, EN CADA INTENTO
            if(strcasecmp(palabraSecreta, intento) == 0){
                    printf("\nGanaste :D\n");
                    if(intentosRestantes == 5){
                        puntaje = ACIERTOPRIMERO;//SI GANA EN EL PRIMER INTENTO
                    }else{
                        puntaje+=GANO;//SI GANA LUEGO DE ALGUNOS INTENTOS
                    }
                    puntajes[j] = puntaje;
                    puntajesVictorias[cantidadGanadas] = puntajes[j];//ESTO GUARDA LOS PUNTAJES SOLAMENTE DE LAS PARTIDAS QUE SE GANAN
                    cantidadGanadas++;
                    break;
            }else{
                for (int i = 0; i < 5; i++){
                    if(intento[i] == palabraSecreta[i]){
                        pista[i] = 'O'; //LA LETRA ESTA EN LA POSICION CORRECTA.
                        puntaje+=100;
                    }else{
                    pista[i] = 'X'; //LA LETRA NO ESTA EN LA PALABRA.
                    }
                }
                for (int i = 0; i < 5; i++){
                    if(pista[i] == 'X'){
                        for (int j = 0; j < 5; j++){
                            if (intento[i] == palabraSecreta[j] && intento[i] != palabraSecreta[i]){
                                pista[i] = '~'; //LA LETRA ESTA EN LA PALABRA PERO NO EN EL LUGAR CORRECTO.
                                puntaje+=50;
                            }
                        }
                    }
                }
                printf("%s\n", pista);
                intentosRestantes--;
                puntaje-=500;

                //SE EJECUTA SI EL JUGADOR NO LOGRO ADIVINAR LA PALABRA
                if(intentosRestantes == 0 ){
                    printf("\nPerdiste :( \nLa palabra era: %s \n", palabraSecreta);
                    puntaje=0;
                }
            }
        }
        //SE MUESTRA EL PUNTAJE DE LA PARTIDA JUGADA
        printf("El puntaje de esta partida es: %d\n", puntaje);
        //EN PUNTAJES SE GUARDAN LOS PUNTAJES DE TODAS LAS PARTIDAS
        puntajes[j] = puntaje;


        //AL FINALIZAR CADA PARTIDA SE CONSULTA AL JUGADOR SI DESEA SEGUIR JUGANDO
        if((j+1)!=cantidadPartidas){
            do{
                printf("\nDeseas seguir jugando? Respuestas validas:(S/N) >");
                scanf(" %c", &respuesta);
            }while((respuesta!='S')&&(respuesta!='N'));
            if(respuesta=='S'){
                cantidadJugadas++;
                continue;
            }else{
                break;
            }
        }
    }
    //LO SIGUIENTE SE EJECUTA SI TERMINO DE JUGAR LAS PARTIDAS ELEGIDAS O SI INTERRUMPIO EN OTRO MOMENTO
    printf("\nHa terminado la sesion de juego!\n\n");

    //SE MUESTRAN TODAS LAS PALABRAS Y TODOS LOS PUNTAJES DE LAS PARTIDAS JUGADAS
    printf(">Aca podes ver tus puntajes:\n\n");
    for (int i=0 ; i<cantidadJugadas; i++){
      printf(">> %d%c partida:\n", i+1, 167);
      printf(">Palabra: %s. ----- >Puntos: %d.\n\n", todasSecretas[i], puntajes[i]);
    }

    if((cantidadJugadas==1)&&(puntajes[0]!=0)){
        printf("Solo jugaste una partida, y ganaste, por lo que el promedio es igual al puntaje: %d.\n", puntajes[0]);
    }else{
        //SE CALCULA EL PROMEDIO DE LOS PUNTAJES DE LAS PARTIDAS EN QUE EL JUGADOR GANO
        float suma = 0.0;
        float promedio;
        for (int i=0; i<cantidadGanadas; i++){
            suma += puntajesVictorias[i];
        }
        promedio = suma / cantidadGanadas;
        printf(">>El promedio de los puntajes de las %d partidas que ganaste es: %.1f\n", cantidadGanadas, promedio);
    }

    //SI EL JUGADOR JUGO MAS DE 1 PARTIDA CALCULAMOS EL PUNTAJE MAS BAJO Y EL MAS ALTO
    if(cantidadJugadas!=1){

        puntajeMenor = puntajes[0];
        puntajeMayor = puntajes[0];

        for (int i = 0; i < cantidadJugadas; i++) {
            if(puntajes[i]<puntajeMenor){
                puntajeMenor = puntajes[i];
            }
        }
        for (int i = 0; i < cantidadJugadas; i++) {
            if(puntajes[i]>puntajeMayor){
                puntajeMayor = puntajes[i];
            }
        }
        if(puntajeMayor==puntajeMenor){
            printf(">>Todos tus puntajes son iguales: %d\n", puntajeMenor);
        }else{
            printf("\nEl puntaje mas bajo fue: %d\n", puntajeMenor);
            printf(">Partida/s con menor puntaje: ");
            for(int i=0; i<cantidadJugadas; i++){
                if(puntajes[i] == puntajeMenor){
                    printf("%d%c %c ", i+1, 167, 3);
                }
            }

            printf("\nEl puntaje mas alto fue: %d\n", puntajeMayor);
            printf(">Partida/s con mayor puntaje: ");
            for(int i=0; i<cantidadJugadas; i++){
                if(puntajes[i] == puntajeMayor){
                    printf("%d%c %c ", i+1, 167, 3);
                }
            }
        }
    }
    //FIN
    printf("\nChau! :)\n");
    return 0;
}

//FUNCIONES
void Inicio() {
    printf("WORLDE\n\n");
    printf("En este juego tenes que adivinar una palabra secreta de 5 letras.\n");
    printf("Para hacerlo tenes 5 intentos.\n");
    printf("En cada intento veras si cada letra ingresada es correcta o no.\n");
    printf(">Si la letra es correcta, se mostrara una O.\n");
    printf(">Si la letra esta en la palabra pero no el lugar correcto, se mostrara una ~.\n");
    printf(">Si la letra no esta en la palabra, se mostrara una X.\n");
    printf("Podes jugar un maximo de 8 partidas.\n");
    printf("Comencemos!\n\n\n");
}
int CantidadPartidas(int nroIngresado){
    if (nroIngresado > MAXPARTIDAS) {
        printf("Recorda que como maximo podes jugar 8 partidas. ");
        scanf("%d", &nroIngresado);
        CantidadPartidas(nroIngresado);
    }
    else if (nroIngresado < MINPARTIDAS){
        printf("Como minimo debes jugar una partida. ");
        scanf("%d", &nroIngresado);
        CantidadPartidas(nroIngresado);
    }
    else {
        return nroIngresado;
    }
}
void NrosAleatorios(int nrosAleatorios[]){
    srand(time(NULL));
    int i, j;
    for (i = 0; i < MAXPARTIDAS; i++){
        nrosAleatorios[i] = rand() % 30 + 1;
        for (j = i; j >= 0; j--){
            while ((nrosAleatorios[i] == nrosAleatorios[j]) && (i != j)){
                nrosAleatorios[i] = rand() % 30 + 1;
            }
        }
    }
}
void LecturaArchivo(){
    FILE *archivo;
    archivo = fopen(NOMBRE_ARCHIVO, "r");
    if (archivo == NULL){
        printf("Error al abrir el archivo");
        return;
    }

    int c, indice = 0;
    do {
        c = fscanf(archivo, "%s", palabras[indice]);
        indice++;
    } while (c != EOF);
}







