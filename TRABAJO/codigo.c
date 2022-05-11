#include<stdio.h>

int main()
{
    int eleccion;
    char usuario[50];

    printf("Para empezar, elige un nombre de usuario con el que nos referiremos a ti\n");
    scanf("%50[^\n]",usuario);
    printf("Bienvenido,encantado de conocerte %s",usuario);

    do
    {
        printf("\n\nBienvenido al menu del LABERINTO DEL MINOTAURO. Selecciona la opcion que desees:\n");
        printf("1-->Reglas del juego\n");
        printf("2-->Explicacion del juego\n");
        printf("3-->Inicio del juego\n");
        printf("4-->Juegos relacionados\n");
        scanf("%i",&eleccion);
    }
    while(eleccion!=1 || eleccion!=2 || eleccion!=3 || eleccion!=4);


    return 0;
}
