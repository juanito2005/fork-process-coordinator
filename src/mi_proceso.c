#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {

    printf("=== INICIO DEL PROGRAMA ===\n");
    printf("[PADRE] PID=%d, PPID (el de la consola)=%d\n", getpid(), getppid());
    printf("[PADRE] Voy a crear 3 procesos hijos...\n\n");

    struct info_procesos
    {
        pid_t pid;
        char nombre[50];
        int orden_creacion;
    };
    
    pid_t hijo1 = fork();
    struct info_procesos proceso1 = {hijo1, "Proceso 1", 1};
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
    struct info_procesos proceso2 = {hijo2, "Proceso 2", 2};
    
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
    struct info_procesos proceso2 = {hijo3, "Proceso 3", 3};
    
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

    // Ampliación 1: añadir un cuarto hijo que calcule la suma de los números pares del 1 al 20.
    // El padre recibe el pid del hijo y el hijo siempre recibirá un 0 aplica para "nietos"
    pid_t hijo4 = fork();
    struct info_procesos proceso2 = {hijo4, "Proceso 4", 4};
    
    if (hijo4 == 0) {
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
    }
    

    printf("[PADRE] Los 4 hijos fueron creados. Esperando a que terminen...\n\n");
    int suma_total = 0;
    int contador_hijos = 0;
    int orden_finalizacion = 1;
    
    for (int i = 0; i < 4; i++)
    {
        int status;
        pid_t hijo_finalizado = wait(&status);

        if (hijo_finalizado == proceso1.pid)
        {
            
            orden_finalizacion++;
        }
        

        if (hijo_finalizado == -1)
        {
            break;
        }
        
        // La "ESPOSA SALIDA" es para confirmar que el código del hijo se ejecutó bien mediante 1 o 0
        if (WIFEXITED(status))
        {
            int resultado = WEXITSTATUS(status);
            printf("[PADRE] Hijo con PID=%d terminó con resultado: %d\n", hijo_finalizado, resultado);
            // Cuenta los hijos que terminaron
            contador_hijos ++;
            suma_total += resultado;
        }
        
    }
    
    float media = (float)suma_total/contador_hijos;

    printf("\n=== RESUMEN FINAL ===\n");
    printf("[PADRE] Suma total de resultados: %d\n", suma_total);
    //Ampliación 2: hacer que el padre calcule la media de los tres resultados en lugar de la suma.
    printf("[PADRE] Media del total de resultados: %.3f\n", media);
    printf("[PADRE] Todos mis %i hijos terminaron. Programa finalizado.\n", contador_hijos);

    return 0;
}