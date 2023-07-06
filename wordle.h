//LIBRERIAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//MACROS
#define MAXPARTIDAS 8
#define MINPARTIDAS 1
#define CANTIDAD_LINEAS 30
#define MAXLETRAS 6
#define NOMBRE_ARCHIVO "palabras.txt"
#define MAXINTENTOS 5
#define PUNTOS_INICIO 5000
#define ACIERTOPRIMERO 10000
#define PERDIO 0
#define GANO 2000

//PROTOTIPOS DE FUNCIONES
void Inicio();
int CantidadPartidas(int);
void NrosAleatorios(int[]);
void LecturaArchivo();

//VARIABLES GLOBALES
char palabras[CANTIDAD_LINEAS][MAXLETRAS];
int nrosAleatorios[MAXPARTIDAS];
char palabraSecreta[MAXLETRAS];
char todasSecretas[MAXPARTIDAS][MAXLETRAS];





