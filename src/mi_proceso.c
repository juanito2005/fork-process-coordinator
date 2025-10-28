#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pro_pid = getpid();
    pid_t padre_ppid = getppid();

    char nombre[] = "Juan Camilo";
    int horas_estudio = 12;

    int dif_pid = pro_pid - padre_ppid;

    printf("Hola soy: %s y estudio %i horas al día :)\n", nombre, horas_estudio);
    printf("Diferencia entre mi proceso %i y el proceso padre %i: = %i\n", pro_pid, padre_ppid, dif_pid);

    if (pro_pid > 1000)
    {
        printf("Proceso moderno :)\n");
    } else
    {
        printf("Proceso del sistema\n");
    }
    return 0;
}
