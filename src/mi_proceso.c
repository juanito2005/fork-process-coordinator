#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {

    printf("=== INICIO DEL PROGRAMA ===\n");
    printf("[PADRE] PID=%d, PPID (el de la consola)=%d\n", getpid(), getppid());
    printf("[PADRE] Voy a crear 3 procesos hijos...\n\n");

    pid_t hijo1 = fork();
    //Ya que en este preciso momento existen dos procesos ejecutandose simultaneamente:
    // Padre e hijo, se necesita aclarar cual debe ejecutar que código
     if (hijo1 == 0) {
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
    }
        
    pid_t hijo2 = fork();
    
    if (hijo2 == 0) {
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
    }

    pid_t hijo3 = fork();
    
    if (hijo3 == 0) {
        printf("=== [HIJO 3] PID=%d, PPID=%d ===\n", getpid(), getppid());
        printf("[HIJO 3] Calcularé el factorial de 5...\n");
        
        int factorial = 1;
        for (int i = 5; i > 0; i--) {
            factorial *= i;
        }
        
        printf("[HIJO 3] 5! = %d\n", factorial);
        printf("[HIJO 3] Terminando con exit(%d)...\n\n", factorial);
        exit(factorial);
    }

    printf("[PADRE] Los 3 hijos fueron creados. Esperando a que terminen...\n\n");
    int suma_total = 0;

    for (int i = 0; i < 3; i++)
    {
        int status;
        pid_t hijo_finalizado = wait(&status);

        // La "ESPOSA SALIDA" es para confirmar que el código del hijo se ejecutó bien mediante 1 o 0
        if (WIFEXITED(status))
        {
            int resultado = WEXITSTATUS(status);
            printf("[PADRE] Hijo con PID=%d terminó con resultado: %d\n", hijo_finalizado, resultado);
            suma_total += resultado;
        }
        
    }

    printf("\n=== RESUMEN FINAL ===\n");
    printf("[PADRE] Suma total de resultados: %d\n", suma_total);
    printf("[PADRE] Todos mis hijos terminaron. Programa finalizado.\n");

    return 0;
}