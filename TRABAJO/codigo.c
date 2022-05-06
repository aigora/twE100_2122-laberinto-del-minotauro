#include<stdio.h>
int main()
{
    char usuario[50];
    printf("Para empezar, elige un nombre de usuario con el que nos referiremos a ti\n");
    scanf("%50[^\n]",usuario);
    printf("Bienvenido,encantado de conocerte %s",usuario);
}
