#include<stdio.h>
typedef struct
{
    char nombre[50];
    char usuario[50];
    int edad;

}jugador;

int main()
{
    int eleccion;
    jugador j1;

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
