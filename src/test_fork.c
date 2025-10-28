#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    printf("Hola! Estoy aprendiendo procesos en C\n");
    printf("Mi primer programa compilado\n");

    // la anotación "\n" es para hacer saltos de linea
    char nombre[] = "Juan Camilo";
    int edad = 20;
    int horas_estudio = 12;
    float nota_esperada = 10;

    printf("Mi nombre es: %s\n", nombre);
    printf("Tengo %d años de edad\n", edad);
    printf("Estudio %d al dia, así que espero obtener un %.2f \n", horas_estudio, nota_esperada);

    if (horas_estudio < 10)
    {
        printf("⚠️ Necesitas más tiempo");
        return 1;
    } else
    {
        printf("¡Perfecto!");
        return 0;
    }


    // 1: verdader
    // 0: falso
    // if(return == 0) ? programa Exitoso! : programa con Error;
    //return 0;
}