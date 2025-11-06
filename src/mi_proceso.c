#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/time.h>

int main() {

    // Tomar el tiempo de inicio
    struct timeval t0, t1;
    gettimeofday(&t0, NULL);

    printf("=== INICIO DEL PROGRAMA ===\n");
    printf("[PADRE] PID=%d, PPID (el de la consola)=%d\n", getpid(), getppid());
    printf("[PADRE] Voy a crear 3 procesos hijos...\n\n");

    struct info_procesos {
    pid_t pid;
    char nombre[50];
    int orden_creacion;
    int orden_finalizacion;
    };

    struct info_procesos procesos[4];
    
    pid_t hijo1 = fork();
    //Ya que en este preciso momento existen dos procesos ejecutandose simultaneamente:
    // Padre e hijo, se necesita aclarar cual debe ejecutar que código
    if (hijo1 == 0) {
        sleep(4);
        printf("=== [HIJO 1] PID=%d, PPID=%d ===\n", getpid(), getppid());
        printf("[HIJO 1] Calcularé la suma de 1 a 10...\n");

        int suma = 0;
        for (int i = 1; i <= 10; i++) {
            suma += i;
        }
        
        printf("[HIJO 1] Suma = %d\n", suma);
        printf("[HIJO 1] Terminando con exit(%d)...\n\n", suma);
        // Este exit() garantiza que el hijo termine y no siga ejecutando más código
        exit(suma);

    } else if (hijo1 > 0) {
        procesos[0].pid = hijo1;
        strcpy(procesos[0].nombre, "Suma 1-10");
        procesos[0].orden_creacion = 1;
        procesos[0].orden_finalizacion = 0;
    }
        
    pid_t hijo2 = fork();

    if (hijo2 == 0) {
        sleep(3);
        printf("=== [HIJO 2] PID=%d, PPID=%d ===\n", getpid(), getppid());
        printf("[HIJO 2] Contaré primos del 1 al 30...\n");
        
        int contador_primos = 0;
        
        for (int num = 2; num <= 30; num++) {
            int es_primo = 1;  // Lo mismo que decir "true"
            
            for (int i = 2; i * i <= num; i++) {
                if (num % i == 0) {
                    es_primo = 0;  // Lo mismo que decir "false"
                    break;
                }
            }

            if (es_primo) {
                contador_primos++;
            }
        }
        printf("[HIJO 2] Primos encontrados = %d\n", contador_primos);
        printf("[HIJO 2] Terminando con exit(%d)...\n\n", contador_primos);
        exit(contador_primos);
    } else if (hijo2 > 0) {
        procesos[1].pid = hijo2;
        strcpy(procesos[1].nombre, "Contar Primos");
        procesos[1].orden_creacion = 2;
        procesos[1].orden_finalizacion = 0;
    }

    pid_t hijo3 = fork();    
    if (hijo3 == 0) {
        sleep(2);
        printf("=== [HIJO 3] PID=%d, PPID=%d ===\n", getpid(), getppid());
        printf("[HIJO 3] Calcularé el factorial de 5...\n");
        
        int factorial = 1;
        for (int i = 5; i > 0; i--) {
            factorial *= i;
        }
        
        printf("[HIJO 3] 5! = %d\n", factorial);
        printf("[HIJO 3] Terminando con exit(%d)...\n\n", factorial);
        exit(factorial);
    } else if (hijo3 > 0) {
        procesos[2].pid = hijo3;
        strcpy(procesos[2].nombre, "Factorial de 5");
        procesos[2].orden_creacion = 3;
        procesos[2].orden_finalizacion = 0;
    }

    // Ampliación 1: añadir un cuarto hijo que calcule la suma de los números pares del 1 al 20.
    // El padre recibe el pid del hijo y el hijo siempre recibirá un 0 aplica para "nietos"
    pid_t hijo4 = fork();
    if (hijo4 == 0) {
        sleep(1);
        printf("===[HIJO 4] PID=%d, PPID=%d ===\n", getpid(), getppid());
        printf("[HIJO 4] Calcularé la suma de los números pares del 1 al 20\n");
        
        int suma = 0;
        for (int i = 0; i <= 20; i++)
        {
            if (i%2 == 0)
            {
                // Bucle de prints para ver como se suma
                // printf("suma: %i + i: %i\n", suma, i);
                // fflush(stdout);
                suma += i;
            }
        }

        printf("[HIJO 4] Sumando los pares...\n");
        printf("[HIJO 4] Terminando con exit(%d)...\n\n", suma);
        exit(suma);
    } else if (hijo4 > 0) {
        procesos[3].pid = hijo4;
        strcpy(procesos[3].nombre, "Suma de pares 1-20");
        procesos[3].orden_creacion = 4;
        procesos[3].orden_finalizacion = 0;
    }
    

    printf("[PADRE] Los 4 hijos fueron creados. Esperando a que terminen...\n\n");
    int suma_total = 0;
    int contador_hijos = 0;
    int orden_finalizacion = 1;
    
    for (int i = 0; i < 4; i++)
    {
        int status;
        pid_t hijo_finalizado = wait(&status);

        // La "ESPOSA SALIDA" es para confirmar que el código del hijo se ejecutó bien mediante 1 o 0
        if (WIFEXITED(status))
        {
            int resultado = WEXITSTATUS(status);
            for (int j = 0; j < 4; j++)
            {
                if (procesos[j].pid == hijo_finalizado)
                {
                    procesos[j].orden_finalizacion = orden_finalizacion;
                    orden_finalizacion++;
                    break;
                }
                
            }

            printf("[PADRE] Hijo con PID=%d terminó con resultado: %d\n", hijo_finalizado, resultado);
            // Cuenta los hijos que terminaron
            contador_hijos ++;
            suma_total += resultado;
        }
        
    }
    
    // Tomar tiempo de fin y calcular diferencia
    gettimeofday(&t1, NULL);
    long long start_us = (long long)t0.tv_sec * 1000000LL + (long long)t0.tv_usec;
    long long end_us   = (long long)t1.tv_sec * 1000000LL + (long long)t1.tv_usec;
    long long elapsed_us = end_us - start_us;
    double elapsed_ms = elapsed_us / 1000.0;
    double elapsed_s  = elapsed_us / 1000000.0;

    double media = (double)suma_total / (double)contador_hijos;

    printf("\n=== RESUMEN FINAL ===\n");
    printf("[PADRE] Suma total de resultados: %d\n", suma_total);
    printf("[PADRE] Media total de resultados: %.3f\n", media);
    printf("[PADRE] Tiempo total: %lld us (%.3f ms, %.6f s)\n",
           elapsed_us, elapsed_ms, elapsed_s);

    printf("\n=== ORDEN CREACIÓN VS FINALIZACIÓN ===\n");
    printf("Creación | %-18s | PID    | Finalización\n", "Nombre");
    printf("────────────────────────────────────────────────────────────\n");
    for (int i = 0; i < 4; i++) {
        printf("   %d     | %-18s | %-6d |    %d\n",
               procesos[i].orden_creacion,
               procesos[i].nombre,
               procesos[i].pid,
               procesos[i].orden_finalizacion);
    }

    printf("[PADRE] Todos mis %d hijos terminaron. Programa finalizado.\n",
           contador_hijos);
    
    return 0;
}