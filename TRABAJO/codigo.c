#include<stdio.h>
#include<conio.h> //para la funcion getch, para recibir por teclado caracter sin necesitar intro
#include<stdlib.h> //para la funcion system

#define X 58
#define Y 30

typedef struct
{
    char nombre[50];
    char usuario[50];
    int edad;

}jugador;

void jugador1(int laberinto1[Y][X],int pos_x_jug, int pos_y_jug);
void juego(int laberinto1[Y][X], int pos_x_jug, int pos_y_jug); //int mod_x, int mod_y);
void imprime_laberinto(int laberinto1[Y][X]);
void entrada(int laberinto1[Y][X], int *pos_x_jug, int *pos_y_jug, int *salida); // int *mod_x, int *mod_y, int *salida);
void actualiza(int laberinto1[Y][X], int pos_x_jug, int pos_y_jug);


int main()
{
    int eleccion;
    jugador j1;
    int i,j;

    printf("Para empezar, me gustaria conocerte jugador. Indica tu nombre y tu edad\n");
    scanf("%s %i",j1.nombre,&j1.edad);
    printf("Encantado de conocerte %s, elige ahora tu nombre de usuario para poder iniciar el juego\n",j1.nombre);
    scanf(" %[^\n]s",j1.usuario);
    printf("Bienvenido %s... A JUGAR\n",j1.usuario);

    do
    {
        printf("\n\nBienvenido al menu del LABERINTO DEL MINOTAURO. Selecciona la opcion que desees:\n");
        printf("1-->Reglas del juego\n");
        printf("2-->Explicacion del juego\n");
        printf("3-->Inicio del juego\n");
        printf("4-->Juegos relacionados\n");
        printf("Presione la tecla 5 para salir del menu\n");
        scanf("%i",&eleccion);

        switch(eleccion)
        {
            case 1:
            {
                FILE *reg;
                char reglas[500];
                int i=0;
                reg = fopen("Reglas.txt","r");

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
                FILE *exp;
                char explicacion[500];
                int i=0;
                exp = fopen("Explicacion.txt","r");

                while(fscanf(exp,"%c",&explicacion[i])!=EOF)
                {
                    printf("%c",explicacion[i]);
                    i++;

                }
                 fclose(exp);
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

                int pos_x_jug = 0;
                int pos_y_jug = 3;

                ///laberinto[vertical][horizontal];
                int laberinto1[Y][X] = {
                        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,'\0'},
                        {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,'\0'},
                        {1,1,1,1,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,2,2,2,2,2,2,'\0'},
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
                juego(laberinto1, pos_x_jug, pos_y_jug); //para el juego del laberinto


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
void jugador1(int laberinto1[Y][X],int pos_x_jug, int pos_y_jug){
    laberinto1[pos_y_jug][pos_x_jug] = 'o'; //le doy la posicion inicial de entrada al laberinto, y le asigno una 'o'
}

//funcion para el bucle del juego
void juego(int laberinto1[Y][X], int pos_x_jug, int pos_y_jug){
    int salida = 0; //para que cuando encuentre la salida se incremente y termmine el juego

    do{ //este bucle se va a ejecutar durante todo el juego, y es do while porque queremos que se inicie al menos una vez y luego continue
        //dentro del bucle vamos a hacer 3 funciones:

        imprime_laberinto(laberinto1); //para dibujar, imprimir, el laberinto en pantalla

        entrada(laberinto1, &pos_x_jug, &pos_y_jug, &salida);
        //para verificar y modificar las posiciones
        //necesitaremos que lo que se modifique dentro de la funcion, se modifique tambien fuera
        //para modificar variables dentro y fuera de la funcion, haremos paso por referencia con punteros

        actualiza(laberinto1, pos_x_jug, pos_y_jug);
        //para ir actualizando el laberinto cada vez que se modifica la posicion del jugador
        //hasta que encuentre la salida

    }while(salida == 0); //se ejecuta el bucle mientras la salida valga 0, es decir, mientras no se haya incrementado y por tanto no haya encontrado la salida

}

//funcion para imprimir el laberinto
void imprime_laberinto(int laberinto1[Y][X]){
    system("cls"); //para que borre el mapa anterior de la pantalla e imprima el actualizado

    int i,j;

    for(i=0; i<Y; i++){
        for(j=0; j<X; j++){
            printf("%c ",laberinto1[i][j]);
        }
        printf("\n");
    }

    printf("\n\n");

}

//funcion que comrpueba la entrada del usuario por teclado, para cambiar la posición del jugador
void entrada(int laberinto1[Y][X], int *pos_x_jug, int *pos_y_jug, int *salida){
    char tecla; //para almacenar la orden de movimiento del usuario

    //tendremos que comprobar si ha encontrado la salida
    //tendremos que comprobar la posicion del jugador, para que no ocupe posiciones con pared o muro (*), y que lo introducido por teclado es correcto

    //para mover al jugador:
    if(laberinto1[*pos_y_jug][*pos_x_jug] != '*'){

        if(laberinto1[*pos_y_jug + 1][*pos_x_jug + 1] == '\0'){ //compruebo que no ha encontrado la salida
            //sumo 1 a la posicion de x y de y, para que al encontrar la salida termine, cuando este justo antes del caracter de finalizacion de cadena
            //si quito el +1, en la pos_y y en la pos_x, no termina al encontrar la salida
            *salida = 1;
        }

        else{ //si no ha encontrado la salida, pide orden de movimiento al jugador

            do{ //utilizo un do-while para asegurar que lo que ha introducido el usuario es correcto

                tecla = getch(); //utilizo funcion getch para introducir por teclado sin necesitar pulsar intro despues de introducir la letra

            }while(tecla != 'd' && tecla != 'a' && tecla != 'w' && tecla != 's');

            if(tecla == 'd'){ //movimiento a la derecha, para ello, sumo 1 a las columnas (pos_x_jug)

                if(laberinto1[*pos_y_jug][*pos_x_jug] == 'o'){//para que no ponga el recorrido del jugador, solo la posicion actual
                    laberinto1[*pos_y_jug][*pos_x_jug] = ' ';
                }

                *pos_x_jug = *pos_x_jug + 1;

                if(laberinto1[*pos_y_jug][*pos_x_jug] == '*'){//si tiene muro esa posicion, lo devuelvo a la posicion original
                    *pos_x_jug = *pos_x_jug - 1; //lo muevo a la izquierda porque lo habia movido a la derecha
                }

            }

            if(tecla == 'a'){ //movimiento a la izquierda, para ello resto 1 a las columnas (pos_x_jug)

                if(laberinto1[*pos_y_jug][*pos_x_jug] == 'o'){//para que no ponga el recorrido del jugador, solo la posicion actual
                    laberinto1[*pos_y_jug][*pos_x_jug] = ' ';
                }

                *pos_x_jug = *pos_x_jug - 1;

                if(laberinto1[*pos_y_jug][*pos_x_jug] == '*'){
                    *pos_x_jug = *pos_x_jug + 1;
                }

            }

            if(tecla == 'w'){ //movimiento hacia arriba, para ello resto 1 a las filas (pos_y_jug)

                if(laberinto1[*pos_y_jug][*pos_x_jug] == 'o'){//para que no ponga el recorrido del jugador, solo la posicion actual
                    laberinto1[*pos_y_jug][*pos_x_jug] = ' '; //cambia la posicion anterior del jugador si es un o por un espacio
                }

                *pos_y_jug = *pos_y_jug - 1;

                if(laberinto1[*pos_y_jug][*pos_x_jug] == '*'){ //si tiene muro esa posicion, lo devuelvo a la posicion original
                    *pos_y_jug = *pos_y_jug + 1; //lo muevo hacia abajo porque lo habia movido hacia arriba
                }

            }

            if(tecla == 's'){ //movimiento hacia abajo, para ello sumo 1 a las filas (pos_y_jug)

                if(laberinto1[*pos_y_jug][*pos_x_jug] == 'o'){//para que no ponga el recorrido del jugador, solo la posicion actual
                    laberinto1[*pos_y_jug][*pos_x_jug] = ' ';
                }

                *pos_y_jug = *pos_y_jug + 1;

                if(laberinto1[*pos_y_jug][*pos_x_jug] == '*'){ //si tiene muro esa posicion, lo devuelvo a la posicion original
                    *pos_y_jug = *pos_y_jug - 1; //lo muevo hacia arriba porque lo habia movido hacia abajo
                }

            }
        }
    }
}


//fucnion para actualizar el laberinto
void actualiza(int laberinto1[Y][X], int pos_x_jug, int pos_y_jug){
    jugador1(laberinto1, pos_x_jug, pos_y_jug); //hace llamada a la funcion jugador, para actualizar su posicion, es decir, la nueva posicion de 'o'
    //imprime_laberinto(laberinto1); //no es necesario!!
}

