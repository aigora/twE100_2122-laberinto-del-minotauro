#include<stdio.h>
#include<conio.h> //para la funcion getch, para recibir por teclado caracter sin necesitar intro
#include<stdlib.h> //para la funcion system

#define X 58
#define Y 27

typedef struct
{
    char nombre[50];
    char usuario[50];
    int edad;

}jugador;

void jugador1(int lab[][X], int pos_x_jug, int pos_y_jug);
void jugador2(int laberinto1[Y][X], int pos_x_jug2, int pos_y_jug2);

void juego(int lab[][X], int pos_x_jug, int pos_y_jug);
void juego_multi(int laberinto1[Y][X], int pos_x_jug, int pos_y_jug, int pos_x_jug2, int pos_y_jug2);

void juegosinvision(int lab[][X], int pos_x_jug, int pos_y_jug,jugador j[]);

void imprime_laberinto(int lab[][X],int f,int c);
void imprime_laberintosinvision(int lab[][X],int f,int c,jugador j[],int pos_y_jug, int pos_x_jug);

void entrada(int lab[][X], int *pos_x_jug, int *pos_y_jug, int *salida);
void actualiza(int lab[][X], int pos_x_jug, int pos_y_jug);

void entrada_multi(int laberinto1[Y][X], int *pos_x_jug, int *pos_y_jug, int *salida, int *pos_x_jug2, int *pos_y_jug2, int *pillado);
void actualiza_multi(int laberinto1[Y][X], int pos_x_jug, int pos_y_jug, int pos_x_jug2, int pos_y_jug2);


int main()
{
    int eleccion;
    jugador jugadores[2];
    int i,j;

    printf("Para empezar, me gustaria conocerte jugador. Indica tu nombre y tu edad\n");
    scanf("%s %i",jugadores[0].nombre,&jugadores[0].edad);
    printf("Encantado de conocerte %s, elige ahora tu nombre de usuario para poder iniciar el juego\n",jugadores[0].nombre);
    scanf(" %[^\n]s",jugadores[0].usuario);
    printf("Bienvenido %s... A JUGAR\n",jugadores[0].usuario);

    do
    {
        printf("\n\nBienvenido al menu del LABERINTO DEL MINOTAURO. Selecciona la opcion que desees:\n");
        printf("1-->Reglas del juego y explicacion de juego y modos de juego\n");
        printf("2-->Modo Multijugador\n");
        printf("3-->Inicio del juego\n");
        printf("4-->Juegos relacionados\n");
        printf("Presione la tecla 5 para salir del menu\n"); //comprobar que no salga opcion incorrecta
        scanf("%i",&eleccion);

        switch(eleccion)
        {
            case 1:
            {
                FILE *reg;
                char reglas[500];
                int i=0;
                reg = fopen("Explicacion.txt","r");

                while(fscanf(reg,"%c",&reglas[i])!=EOF)
                {
                    printf("%c",reglas[i]);
                    i++;

                }
                fclose(reg);
                break;

            }

            case 2:
            {
                char seguir;
                int i,j;
                int pos_x_jug, pos_y_jug, pos_x_jug2, pos_y_jug2;
                printf("A %s ya le conocemos pero nos gustaria que te presentaras tu tambien jugador 2. Indicanos tu nombre, edad y usuario\n",jugadores[0].usuario);
                scanf("%s %i %[^\n]s",jugadores[1].nombre,&jugadores[1].edad,jugadores[1].usuario);
                printf("\nDemostrad vuestra habilidad; %s debera atrapar a %s, mientras este intenta llegar a la salida y salir victorioso.Presiona una tecla y ENTER para continuar\n",jugadores[1].usuario,jugadores[0].usuario);
                scanf(" %c",&seguir);

                pos_x_jug = 0;
                pos_y_jug = 1;

                pos_x_jug2 = X-2;
                pos_y_jug2 = Y-3;

                ///laberinto[vertical][horizontal];
                //muros 2, huecos 1
                int laberinto3[Y][X] = {
                        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,'\0'},
                        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,'\0'},
                        {2,2,2,1,2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,2,2,1,2,2,2,2,2,1,2,2,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,'\0'},
                        {2,1,2,1,1,2,2,2,2,2,1,2,2,1,1,1,1,2,2,2,2,2,2,2,1,2,2,2,1,2,2,1,2,1,1,1,2,1,2,2,2,2,1,1,2,1,1,1,1,1,1,1,1,1,2,2,2,'\0'},
                        {2,1,1,1,2,2,2,1,1,1,1,2,2,2,2,2,1,2,2,2,2,2,2,2,1,2,2,2,1,1,1,1,2,2,2,1,2,1,2,2,2,2,2,1,1,1,2,2,2,2,2,2,2,1,2,2,2,'\0'},
                        {2,2,2,1,2,2,2,2,2,2,2,2,2,1,1,1,1,2,2,1,1,1,2,2,1,2,2,2,2,2,2,2,2,2,2,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,'\0'},
                        {2,2,2,1,2,2,2,2,2,2,2,2,2,1,2,2,1,2,2,1,2,1,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,'\0'},
                        {2,2,1,1,1,1,1,1,1,2,2,1,1,1,2,2,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,1,1,1,1,2,2,2,2,2,2,2,1,2,2,2,'\0'},
                        {2,2,1,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,1,1,1,1,1,2,2,1,1,1,1,2,2,2,2,1,2,2,2,'\0'},
                        {2,2,1,2,2,1,2,2,1,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,2,2,2,1,2,2,2,2,2,2,2,2,2,1,2,2,2,2,1,2,2,2,'\0'},
                        {2,1,1,2,2,1,2,2,1,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,1,2,2,1,1,2,2,2,2,2,2,2,2,2,1,1,1,2,2,1,2,2,2,'\0'},
                        {2,2,1,2,2,1,2,2,1,2,2,2,2,2,2,1,2,2,2,1,1,2,2,2,2,1,1,1,1,1,2,2,1,2,1,2,2,1,2,2,2,1,1,1,1,1,1,2,2,2,1,2,2,1,2,2,2,'\0'},
                        {2,2,1,1,1,1,2,2,1,2,2,2,2,2,1,1,1,2,2,2,1,2,2,1,1,1,2,2,2,1,2,2,1,2,1,2,2,1,2,2,2,1,2,2,2,2,1,2,2,2,1,2,2,1,2,2,2,'\0'},
                        {2,2,2,2,2,2,2,2,1,1,1,1,2,2,2,2,1,1,1,2,1,2,2,1,2,2,2,2,2,1,2,2,1,2,1,2,2,1,2,2,2,1,2,2,2,2,1,2,2,2,1,2,2,1,2,2,2,'\0'},
                        {2,1,1,1,2,2,2,2,1,2,2,1,1,1,2,2,2,2,1,1,1,2,2,1,2,2,2,1,1,1,2,2,1,2,1,1,1,1,2,2,2,1,2,2,1,1,1,2,2,2,1,2,2,1,2,2,2,'\0'},
                        {2,1,2,1,1,1,1,1,1,2,2,1,2,1,1,2,2,2,2,2,1,2,2,1,1,2,2,2,2,2,2,2,1,2,1,2,2,2,2,2,2,1,2,2,2,2,1,1,2,2,1,2,2,1,2,2,2,'\0'},
                        {2,1,2,1,2,2,2,2,1,2,2,1,2,2,1,1,2,2,2,2,1,2,2,2,1,1,1,1,1,1,1,1,1,2,1,2,2,2,2,2,2,1,2,2,2,2,2,1,2,2,1,1,1,1,2,2,2,'\0'},
                        {2,2,2,1,1,1,2,2,1,2,2,1,2,2,2,1,2,2,2,2,1,1,1,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,1,1,1,1,2,2,1,2,2,2,2,2,1,2,2,2,'\0'},
                        {2,1,2,2,2,2,2,2,1,2,1,1,2,2,2,1,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,1,2,2,1,1,1,2,2,2,1,2,2,2,'\0'},
                        {2,1,2,2,1,1,1,1,1,2,2,1,1,1,2,1,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,1,2,2,2,'\0'},
                        {2,1,1,2,2,1,2,2,1,2,2,2,2,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,1,2,2,2,'\0'},
                        {2,2,1,2,2,1,2,2,1,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,1,2,2,2,'\0'},
                        {2,2,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,1,2,2,2,'\0'},
                        {2,2,2,1,2,2,2,2,1,2,2,1,2,2,2,2,2,2,2,2,2,2,1,2,2,2,1,1,1,1,2,2,2,2,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,1,2,2,2,1,2,2,2,'\0'},
                        {2,2,2,1,1,2,2,2,1,2,2,1,1,1,2,2,2,2,2,2,2,2,1,2,2,2,1,2,2,1,2,2,2,2,1,2,2,2,1,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,'\0'},
                        {2,2,2,2,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,2,2,1,1,1,1,1,1,2,2,2,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,'\0'},
                        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,'\0'},
                    };


                for(i=0; i<Y; i++){
                    for(j=0; j<X; j++){
                        if(laberinto3[i][j]==1)
                        {
                            laberinto3[i][j]=' ';
                        }

                        if(laberinto3[i][j]==2)
                        {
                            laberinto3[i][j]='*';
                        }

                    printf("%c ",laberinto3[i][j]);


                    }
                    printf("\n");
                }

                jugador1(laberinto3, pos_x_jug, pos_y_jug); //para poner el jugador en su posicion inicial
                jugador2(laberinto3, pos_x_jug2, pos_y_jug2);
                juego_multi(laberinto3, pos_x_jug, pos_y_jug, pos_x_jug2, pos_y_jug2); //para el juego multijugador

                break;
            }

            case 4:
            {
                FILE *jueg;
                char juegos[500];
                int i=0;
                jueg = fopen("Juegos relacionados.txt","r");

                while(fscanf(jueg,"%c",&juegos[i])!=EOF)
                {
                    printf("%c",juegos[i]);
                    i++;

                }
                 fclose(jueg);
                break;
            }

            case 3:
            {
                char sigue;
                int pos_x_jug = 1;
                int pos_y_jug = 2;
                printf("\nEstupendo, empecemos con el laberinto mas facil para entrar en calor. Tu objetivo...llegar a la meta lo antes posible\n\n");
                printf("Presiona una tecla y ENTER para comenzar a jugar\n");
                scanf(" %c",&sigue);

                ///laberinto[vertical][horizontal];
                int laberinto1[Y][X] = {
                        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,'\0'},
                        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,'\0'},
                        {2,1,1,1,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,2,2,2,2,2,2,'\0'},
                        {2,2,2,1,2,2,2,1,2,2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,1,2,2,2,2,2,2,'\0'},
                        {2,2,2,1,2,2,2,1,1,1,1,1,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,1,2,2,2,2,2,2,'\0'},
                        {2,2,2,1,2,2,2,1,2,2,2,1,2,2,2,2,1,1,1,2,2,2,2,2,2,1,1,2,2,2,1,1,1,1,1,1,1,2,2,2,2,2,1,1,1,1,2,2,2,2,1,2,2,2,2,2,2,'\0'},
                        {2,2,1,1,1,1,1,1,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,1,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,2,2,2,'\0'},
                        {2,2,1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,1,1,1,2,1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,1,2,2,2,'\0'},
                        {2,2,1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,2,1,2,1,2,1,1,1,1,1,2,2,2,2,1,2,2,2,2,2,2,2,1,2,2,2,'\0'},
                        {2,2,1,2,2,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,1,2,1,2,1,2,1,2,2,2,1,1,2,2,2,1,1,1,1,1,1,1,1,1,2,2,2,'\0'},
                        {2,2,1,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,1,2,2,2,1,2,1,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,'\0'},
                        {2,2,1,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,1,2,1,2,1,2,1,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,'\0'},
                        {2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,2,2,2,1,1,1,2,1,2,1,2,2,2,2,1,2,2,2,2,2,2,2,1,1,1,1,1,2,2,2,'\0'},
                        {2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,1,2,2,1,1,1,2,2,2,2,1,2,2,2,2,2,2,2,1,2,2,2,1,2,2,2,'\0'},
                        {2,2,2,1,1,1,1,2,2,2,2,2,2,2,1,1,1,1,2,2,2,2,2,1,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,1,2,2,2,1,1,1,1,1,2,2,2,1,2,2,2,'\0'},
                        {2,2,2,1,2,2,2,2,2,2,2,1,1,1,1,2,2,1,2,2,2,2,2,1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,1,2,2,2,1,2,2,2,2,2,2,2,1,2,2,2,'\0'},
                        {2,2,2,1,2,2,2,2,2,2,2,1,2,2,2,2,2,1,2,2,2,2,2,1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,1,2,2,2,1,2,2,2,2,2,2,2,1,2,2,2,'\0'},
                        {2,2,2,1,2,2,2,2,1,1,1,1,2,2,2,2,2,1,2,2,2,2,2,1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,1,1,1,1,1,2,2,2,2,2,2,2,1,2,2,2,'\0'},
                        {2,2,2,1,1,1,1,1,1,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,'\0'},
                        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,'\0'},
                        {2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,2,2,2,2,1,2,2,2,'\0'},
                        {2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,2,2,2,2,2,1,2,2,2,1,1,1,1,1,1,2,2,2,'\0'},
                        {2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,'\0'},
                        {2,2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,1,1,1,1,1,1,1,2,2,2,2,1,2,2,2,2,2,1,2,2,2,2,2,1,1,1,1,1,1,2,'\0'},
                        {2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,2,2,2,2,2,1,1,1,1,1,1,1,2,2,2,2,1,1,'\0'},
                        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,'\0'},
                        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,'\0'},
            };


            for(i=0; i<Y; i++){
                for(j=0; j<X; j++){
                    if(laberinto1[i][j]==1)
                    {
                        laberinto1[i][j]=' ';
                    }

                    if(laberinto1[i][j]==2)
                    {
                        laberinto1[i][j]='*';
                    }

                printf("%c ",laberinto1[i][j]);


                }

                printf("\n");
            }

                jugador1(laberinto1, pos_x_jug, pos_y_jug); //para poner el jugador en su posicion inicial
                juego(laberinto1, pos_x_jug, pos_y_jug);
                 //para el juego del laberinto
                 int laberinto2[Y][X] = {
                        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,'\0'},
                        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,'\0'},
                        {2,1,1,1,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,2,2,2,2,2,2,'\0'},
                        {2,2,2,1,2,2,2,1,2,2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,1,2,2,2,2,2,2,'\0'},
                        {2,2,2,1,2,2,2,1,1,1,1,1,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,1,2,2,2,2,2,2,'\0'},
                        {2,2,2,1,2,2,2,1,2,2,2,1,2,2,2,2,1,1,1,2,2,2,2,2,2,1,1,2,2,2,1,1,1,1,1,1,1,2,2,2,2,2,1,1,1,1,2,2,2,2,1,2,2,2,2,2,2,'\0'},
                        {2,2,1,1,1,1,1,1,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,1,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,2,2,2,'\0'},
                        {2,2,1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,1,1,1,2,1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,1,2,2,2,'\0'},
                        {2,2,1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,2,1,2,1,2,1,1,1,1,1,2,2,2,2,1,2,2,2,2,2,2,2,1,2,2,2,'\0'},
                        {2,2,1,2,2,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,1,2,1,2,1,2,1,2,2,2,1,1,2,2,2,1,1,1,1,1,1,1,1,1,2,2,2,'\0'},
                        {2,2,1,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,1,2,2,2,1,2,1,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,'\0'},
                        {2,2,1,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,1,2,1,2,1,2,1,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,'\0'},
                        {2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,2,2,2,1,1,1,2,1,2,1,2,2,2,2,1,2,2,2,2,2,2,2,1,1,1,1,1,2,2,2,'\0'},
                        {2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,1,2,2,1,1,1,2,2,2,2,1,2,2,2,2,2,2,2,1,2,2,2,1,2,2,2,'\0'},
                        {2,2,2,1,1,1,1,2,2,2,2,2,2,2,1,1,1,1,2,2,2,2,2,1,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,1,2,2,2,1,1,1,1,1,2,2,2,1,2,2,2,'\0'},
                        {2,2,2,1,2,2,2,2,2,2,2,1,1,1,1,2,2,1,2,2,2,2,2,1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,1,2,2,2,1,2,2,2,2,2,2,2,1,2,2,2,'\0'},
                        {2,2,2,1,2,2,2,2,2,2,2,1,2,2,2,2,2,1,2,2,2,2,2,1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,1,2,2,2,1,2,2,2,2,2,2,2,1,2,2,2,'\0'},
                        {2,2,2,1,2,2,2,2,1,1,1,1,2,2,2,2,2,1,2,2,2,2,2,1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,1,1,1,1,1,2,2,2,2,2,2,2,1,2,2,2,'\0'},
                        {2,2,2,1,1,1,1,1,1,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,'\0'},
                        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,'\0'},
                        {2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,2,2,2,2,1,2,2,2,'\0'},
                        {2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,2,2,2,2,2,1,2,2,2,1,1,1,1,1,1,2,2,2,'\0'},
                        {2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,'\0'},
                        {2,2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,1,1,1,1,1,1,1,2,2,2,2,1,2,2,2,2,2,1,2,2,2,2,2,1,1,1,1,1,1,2,'\0'},
                        {2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,2,2,2,2,2,1,1,1,1,1,1,1,2,2,2,2,1,1,'\0'},
                        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,'\0'},
                        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,'\0'},
            };
                for(i=0; i<Y; i++){
                for(j=0; j<X; j++){
                    if(laberinto2[i][j]==1)
                    {
                        laberinto2[i][j]=' ';
                    }

                    if(laberinto2[i][j]==2)
                    {
                        laberinto2[i][j]='*';
                    }
                printf("%c ",laberinto2[i][j]);


                }

                printf("\n");
            }

                jugador1(laberinto2, pos_x_jug, pos_y_jug); //para poner el jugador en su posicion inicial
                juegosinvision(laberinto2, pos_x_jug, pos_y_jug,jugadores);//para el juego del laberinto


                break;
            }
            case 5:
                {
                    printf("FIN DEL JUEGO. Gracias por participar\n");
                    break;
                }

            default:
            {
                printf("Has seleccionado una opcion no valida\n");
                break;
            }
        }

    }
    while(eleccion!=5);


    return 0;
}


//funcion para el jugador
void jugador1(int lab[][X], int pos_x_jug, int pos_y_jug){
    lab[pos_y_jug][pos_x_jug] = 'o'; //le doy la posicion inicial de entrada al laberinto, y le asigno una 'o'
}

//funcion para el bucle del juego
void juego(int lab[][X], int pos_x_jug, int pos_y_jug){
    int salida = 0; //para que cuando encuentre la salida se incremente y termmine el juego

    do{ //este bucle se va a ejecutar durante todo el juego, y es do while porque queremos que se inicie al menos una vez y luego continue
        //dentro del bucle vamos a hacer 3 funciones:

        imprime_laberinto(lab,Y,X); //para dibujar, imprimir, el laberinto en pantalla

        entrada(lab, &pos_x_jug, &pos_y_jug, &salida);
        //para verificar y modificar las posiciones
        //necesitaremos que lo que se modifique dentro de la funcion, se modifique tambien fuera
        //para modificar variables dentro y fuera de la funcion, haremos paso por referencia con punteros

        actualiza(lab, pos_x_jug, pos_y_jug);
        //para ir actualizando el laberinto cada vez que se modifica la posicion del jugador
        //hasta que encuentre la salida

    }while(salida == 0); //se ejecuta el bucle mientras la salida valga 0, es decir, mientras no se haya incrementado y por tanto no haya encontrado la salida

}

//funcion para imprimir el laberinto
void imprime_laberinto(int lab[][X],int f,int c){
    system("cls"); //para que borre el mapa anterior de la pantalla e imprima el actualizado

    int i,j;

    printf("\nEstupendo, empecemos con el laberinto mas facil para entrar en calor. Tu objetivo...llegar a la meta lo antes posible\n\n");

    for(i=0; i<f; i++){
        for(j=0; j<c; j++){
            printf("%c ",lab[i][j]);
        }
        printf("\n");
    }

    printf("\n");

}

//funcion que comrpueba la entrada del usuario por teclado, para cambiar la posición del jugador
void entrada(int lab[][X], int *pos_x_jug, int *pos_y_jug, int *salida){
    char tecla; //para almacenar la orden de movimiento del usuario

    //tendremos que comprobar si ha encontrado la salida
    //tendremos que comprobar la posicion del jugador, para que no ocupe posiciones con pared o muro (*), y que lo introducido por teclado es correcto

    //para mover al jugador:
    if(lab[*pos_y_jug][*pos_x_jug] != '*'){

        if(lab[*pos_y_jug + 1][*pos_x_jug + 1] == '\0'){ //compruebo que no ha encontrado la salida
            //sumo 1 a la posicion de x y de y, para que al encontrar la salida termine, cuando este justo antes del caracter de finalizacion de cadena
            //si quito el +1, en la pos_y y en la pos_x, no termina al encontrar la salida
            *salida = 1;
        }

        else{ //si no ha encontrado la salida, pide orden de movimiento al jugador

            do{ //utilizo un do-while para asegurar que lo que ha introducido el usuario es correcto

                tecla = getch(); //utilizo funcion getch para introducir por teclado sin necesitar pulsar intro despues de introducir la letra

            }while(tecla != 'd' && tecla != 'a' && tecla != 'w' && tecla != 's');

            if(tecla == 'd'){ //movimiento a la derecha, para ello, sumo 1 a las columnas (pos_x_jug)

                if(lab[*pos_y_jug][*pos_x_jug] == 'o'){//para que no ponga el recorrido del jugador, solo la posicion actual
                    lab[*pos_y_jug][*pos_x_jug] = ' ';
                }

                *pos_x_jug = *pos_x_jug + 1;

                if(lab[*pos_y_jug][*pos_x_jug] == '*'){//si tiene muro esa posicion, lo devuelvo a la posicion original
                    *pos_x_jug = *pos_x_jug - 1; //lo muevo a la izquierda porque lo habia movido a la derecha
                }

            }

            if(tecla == 'a'){ //movimiento a la izquierda, para ello resto 1 a las columnas (pos_x_jug)

                if(lab[*pos_y_jug][*pos_x_jug] == 'o'){//para que no ponga el recorrido del jugador, solo la posicion actual
                    lab[*pos_y_jug][*pos_x_jug] = ' ';
                }

                *pos_x_jug = *pos_x_jug - 1;

                if(lab[*pos_y_jug][*pos_x_jug] == '*'){
                    *pos_x_jug = *pos_x_jug + 1;
                }

            }

            if(tecla == 'w'){ //movimiento hacia arriba, para ello resto 1 a las filas (pos_y_jug)

                if(lab[*pos_y_jug][*pos_x_jug] == 'o'){//para que no ponga el recorrido del jugador, solo la posicion actual
                    lab[*pos_y_jug][*pos_x_jug] = ' '; //cambia la posicion anterior del jugador si es un o por un espacio
                }

                *pos_y_jug = *pos_y_jug - 1;

                if(lab[*pos_y_jug][*pos_x_jug] == '*'){ //si tiene muro esa posicion, lo devuelvo a la posicion original
                    *pos_y_jug = *pos_y_jug + 1; //lo muevo hacia abajo porque lo habia movido hacia arriba
                }

            }

            if(tecla == 's'){ //movimiento hacia abajo, para ello sumo 1 a las filas (pos_y_jug)

                if(lab[*pos_y_jug][*pos_x_jug] == 'o'){//para que no ponga el recorrido del jugador, solo la posicion actual
                    lab[*pos_y_jug][*pos_x_jug] = ' ';
                }

                *pos_y_jug = *pos_y_jug + 1;

                if(lab[*pos_y_jug][*pos_x_jug] == '*'){ //si tiene muro esa posicion, lo devuelvo a la posicion original
                    *pos_y_jug = *pos_y_jug - 1; //lo muevo hacia arriba porque lo habia movido hacia abajo
                }

            }
        }
    }
}


//fucnion para actualizar el laberinto
void actualiza(int lab[][X], int pos_x_jug, int pos_y_jug){
    jugador1(lab, pos_x_jug, pos_y_jug); //hace llamada a la funcion jugador, para actualizar su posicion, es decir, la nueva posicion de 'o'
}


void juegosinvision(int lab[][X], int pos_x_jug, int pos_y_jug,jugador j[])
{
    int salida = 0;//para que cuando encuentre la salida se incremente y termmine el juego

    do{ //este bucle se va a ejecutar durante todo el juego, y es do while porque queremos que se inicie al menos una vez y luego continue
        //dentro del bucle vamos a hacer 3 funciones:

        imprime_laberintosinvision(lab,Y,X,j,pos_x_jug,pos_y_jug);
         //para dibujar, imprimir, el laberinto en pantalla

        entrada(lab, &pos_x_jug, &pos_y_jug, &salida);

        //para verificar y modificar las posiciones
        //necesitaremos que lo que se modifique dentro de la funcion, se modifique tambien fuera
        //para modificar variables dentro y fuera de la funcion, haremos paso por referencia con punteros

        actualiza(lab, pos_x_jug, pos_y_jug);
        //para ir actualizando el laberinto cada vez que se modifica la posicion del jugador
        //hasta que encuentre la salida

    }while(salida == 0);
}


void imprime_laberintosinvision(int lab[][58],int f,int c,jugador j[],int pos_x_jug,int pos_y_jug)
{
    system("cls");//para que borre el mapa anterior de la pantalla e imprima el actualizado
   printf("Bien jugado, para tener %i a%cos no esta mal :) Pasemos al siguiente laberinto, ahora con vision reducida...\n",j[0].edad,164);
    int i,l;

    for(i=pos_y_jug-2;i<=pos_y_jug+2; i++){
        for(l=pos_x_jug-2; l<=pos_x_jug+2; l++){
            printf("%c ",lab[i][l]);
        }
        printf("\n");
    }

    printf("\n");
}


void jugador2(int laberinto1[Y][X],int pos_x_jug2, int pos_y_jug2){
    laberinto1[pos_y_jug2][pos_x_jug2] = 'M'; //le doy la posicion final de salida del laberinto, y le asigno una 'M'
}


void juego_multi(int laberinto1[Y][X], int pos_x_jug, int pos_y_jug, int pos_x_jug2, int pos_y_jug2){
    int salida = 0; //para que cuando encuentre la salida se incremente y termmine el juego
    int pillado = 0; //para que cuando le pille se incremente y termine el juego

    do{ //este bucle se va a ejecutar durante todo el juego, y es do while porque queremos que se inicie al menos una vez y luego continue

        imprime_laberinto(laberinto1, Y, X); //para dibujar, imprimir, el laberinto en pantalla

        entrada_multi(laberinto1, &pos_x_jug, &pos_y_jug, &salida, &pos_x_jug2, &pos_y_jug2, &pillado);
        //para verificar y modificar las posiciones

        actualiza_multi(laberinto1, pos_x_jug, pos_y_jug, pos_x_jug2, pos_y_jug2);
        //para ir actualizando el laberinto cada vez que se modifica la posicion de los jugadores

    }while(salida == 0 && pillado == 0); //se ejecuta el bucle mientras la salida valga 0 y pillado tambien
}


void entrada_multi(int laberinto1[Y][X], int *pos_x_jug, int *pos_y_jug, int *salida, int *pos_x_jug2, int *pos_y_jug2, int *pillado){
    char tecla1; //para almacenar la orden de movimiento del usuario

    //para mover al jugador:
    if(laberinto1[*pos_y_jug][*pos_x_jug] != '*'  && laberinto1[*pos_y_jug2][*pos_x_jug2] != '*'){

        if(laberinto1[*pos_y_jug + 1][*pos_x_jug + 1] == '\0'){ //compruebo que no ha encontrado la salida
            *salida = 1;
        }


        //condiciones para pillar??
        else if(laberinto1[*pos_y_jug2][*pos_x_jug2] ==  laberinto1[*pos_y_jug][*pos_x_jug]){ //si lo atraviesa no pilla
                *pillado = 1;
            }


        else{ //si no ha encontrado la salida, pide orden de movimiento al jugador

            do{ //utilizo un do-while para asegurar que lo que ha introducido el usuario es correcto

                tecla1 = getch();

            }while(tecla1 != 'd' && tecla1 != 'a' && tecla1 != 'w' && tecla1 != 's' && tecla1 != 'i' && tecla1 != 'l' && tecla1 != 'j' && tecla1 != 'k');

            if(tecla1 == 'd'){ //movimiento a la derecha, para ello, sumo 1 a las columnas (pos_x_jug)

                if(laberinto1[*pos_y_jug][*pos_x_jug] == 'o'){//para que no ponga el recorrido del jugador, solo la posicion actual
                    laberinto1[*pos_y_jug][*pos_x_jug] = ' ';
                }

                *pos_x_jug = *pos_x_jug + 1;

                if(laberinto1[*pos_y_jug][*pos_x_jug] == '*'){//si tiene muro esa posicion, lo devuelvo a la posicion original
                    *pos_x_jug = *pos_x_jug - 1; //lo muevo a la izquierda porque lo habia movido a la derecha
                }

                if(laberinto1[*pos_y_jug][*pos_x_jug] == 'M'){ //si en al moverse esta en la posicion del monstruo, pillado!!
                    *pillado = 1;
                }

            }

            if(tecla1 == 'a'){ //movimiento a la izquierda, para ello resto 1 a las columnas (pos_x_jug)

                if(laberinto1[*pos_y_jug][*pos_x_jug] == 'o'){//para que no ponga el recorrido del jugador, solo la posicion actual
                    laberinto1[*pos_y_jug][*pos_x_jug] = ' ';
                }

                *pos_x_jug = *pos_x_jug - 1;

                if(laberinto1[*pos_y_jug][*pos_x_jug] == '*'){
                    *pos_x_jug = *pos_x_jug + 1;
                }

                if(laberinto1[*pos_y_jug][*pos_x_jug] == 'M'){ //si en al moverse esta en la posicion del monstruo, pillado!!
                    *pillado = 1;
                }

            }

            if(tecla1 == 'w'){ //movimiento hacia arriba, para ello resto 1 a las filas (pos_y_jug)

                if(laberinto1[*pos_y_jug][*pos_x_jug] == 'o'){//para que no ponga el recorrido del jugador, solo la posicion actual
                    laberinto1[*pos_y_jug][*pos_x_jug] = ' '; //cambia la posicion anterior del jugador si es un o por un espacio
                }

                *pos_y_jug = *pos_y_jug - 1;

                if(laberinto1[*pos_y_jug][*pos_x_jug] == '*'){ //si tiene muro esa posicion, lo devuelvo a la posicion original
                    *pos_y_jug = *pos_y_jug + 1; //lo muevo hacia abajo porque lo habia movido hacia arriba
                }

                if(laberinto1[*pos_y_jug][*pos_x_jug] == 'M'){ //si en al moverse esta en la posicion del monstruo, pillado!!
                    *pillado = 1;
                }

            }

            if(tecla1 == 's'){ //movimiento hacia abajo, para ello sumo 1 a las filas (pos_y_jug)

                if(laberinto1[*pos_y_jug][*pos_x_jug] == 'o'){//para que no ponga el recorrido del jugador, solo la posicion actual
                    laberinto1[*pos_y_jug][*pos_x_jug] = ' ';
                }

                *pos_y_jug = *pos_y_jug + 1;

                if(laberinto1[*pos_y_jug][*pos_x_jug] == '*'){ //si tiene muro esa posicion, lo devuelvo a la posicion original
                    *pos_y_jug = *pos_y_jug - 1; //lo muevo hacia arriba porque lo habia movido hacia abajo
                }

                if(laberinto1[*pos_y_jug][*pos_x_jug] == 'M'){ //si en al moverse esta en la posicion del monstruo, pillado!!
                    *pillado = 1;
                }

            }


             if(tecla1 == 'l'){ //movimiento a la derecha, para ello, sumo 1 a las columnas (pos_x_jug)

                if(laberinto1[*pos_y_jug2][*pos_x_jug2] == 'M'){//para que no ponga el recorrido del jugador, solo la posicion actual
                    laberinto1[*pos_y_jug2][*pos_x_jug2] = ' ';
                }

                *pos_x_jug2 = *pos_x_jug2 + 1;

                if(laberinto1[*pos_y_jug2][*pos_x_jug2] == '*'){//si tiene muro esa posicion, lo devuelvo a la posicion original
                    *pos_x_jug2 = *pos_x_jug2 - 1; //lo muevo a la izquierda porque lo habia movido a la derecha
                }

            }

            if(tecla1 == 'j'){ //movimiento a la izquierda, para ello resto 1 a las columnas (pos_x_jug)

                if(laberinto1[*pos_y_jug2][*pos_x_jug2] == 'M'){//para que no ponga el recorrido del jugador, solo la posicion actual
                    laberinto1[*pos_y_jug2][*pos_x_jug2] = ' ';
                }

                *pos_x_jug2 = *pos_x_jug2 - 1;

                if(laberinto1[*pos_y_jug2][*pos_x_jug2] == '*'){
                    *pos_x_jug2 = *pos_x_jug2 + 1;
                }

            }

            if(tecla1 == 'i'){ //movimiento hacia arriba, para ello resto 1 a las filas (pos_y_jug)

                if(laberinto1[*pos_y_jug2][*pos_x_jug2] == 'M'){//para que no ponga el recorrido del jugador, solo la posicion actual
                    laberinto1[*pos_y_jug2][*pos_x_jug2] = ' '; //cambia la posicion anterior del jugador si es un o por un espacio
                }

                *pos_y_jug2 = *pos_y_jug2 - 1;

                if(laberinto1[*pos_y_jug2][*pos_x_jug2] == '*'){ //si tiene muro esa posicion, lo devuelvo a la posicion original
                    *pos_y_jug2 = *pos_y_jug2 + 1; //lo muevo hacia abajo porque lo habia movido hacia arriba
                }

            }

            if(tecla1 == 'k'){ //movimiento hacia abajo, para ello sumo 1 a las filas (pos_y_jug)

                if(laberinto1[*pos_y_jug2][*pos_x_jug2] == 'M'){//para que no ponga el recorrido del jugador, solo la posicion actual
                    laberinto1[*pos_y_jug2][*pos_x_jug2] = ' ';
                }

                *pos_y_jug2 = *pos_y_jug2 + 1;

                if(laberinto1[*pos_y_jug2][*pos_x_jug2] == '*'){ //si tiene muro esa posicion, lo devuelvo a la posicion original
                    *pos_y_jug2 = *pos_y_jug2 - 1; //lo muevo hacia arriba porque lo habia movido hacia abajo
                }

            }
    }
        }

}


void actualiza_multi(int laberinto1[Y][X], int pos_x_jug, int pos_y_jug, int pos_x_jug2, int pos_y_jug2){
    jugador1(laberinto1, pos_x_jug, pos_y_jug); //hace llamada a la funcion jugador, para actualizar su posicion, es decir, la nueva posicion de 'o'
    jugador2(laberinto1, pos_x_jug2, pos_y_jug2);
}


