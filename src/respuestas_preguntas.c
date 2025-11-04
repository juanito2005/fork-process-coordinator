#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    // Cuestiones complementarias.


    // 1. ¿Qué valor devuelve fork() en el padre y en el hijo?
    /*  
        Devuelve dos valores: 
        - A el padre le asigna el pid del hijo
        - Y al hijo le asigna el número "0" a modo de identificación, es por eso que se hace el:
            if (pid == 0) {
                Esto diferencia que ejecuta el padre y que el hijo
            }
    */


    // 2. ¿Por qué el orden de ejecución de los hijos no es siempre el mismo?
    /*  
        Por que es el scheduler del kernel el que decide que proceso ejecutar sin importar el orden
        en el que se escribió.
        Para garantizar un orden, se deben hacer semáforos, sleep(), etc
    */


    // 3. ¿Qué ocurre si el padre no llama a wait()?
    /*
        Los procesos hijos se convierten en zombies ocupando "entradas" en la tabla de
        procesos que es limitada 
    */

    // 4. ¿Qué limitación tiene devolver resultados con exit()?
    /*
        El exit() status es de 8 bits y por cosas que no entiendo pero relacionadas a esto, el int a
        devolver solo pueden ser valores entre 0 y 255
    */

    // 5. ¿Cómo podríamos transmitir resultados más grandes o estructuras completas?
    /*
        Según lo que investigué  existen métodos específicos pensados para esto, such as:
                | Método         | Uso                              | Ejemplo           |
        | -------------- | -------------------------------- | ----------------- |
        | Pipes          | Comunicación unidireccional      | pipe(),popen()    |
        | Shared Memory  | Memoria compartida (más rápido)  | shmget(),shmat()  |
        | Message Queues | Colas de mensajes                | msgget(),msgsnd() |
        | Sockets        | Comunicación red/local           | socket(),bind()   |
        | Archivos       | Tu idea - escribir/leer archivos | fopen(),fwrite()  |
        | Signals        | Notificaciones simples           | kill(),signal()   |    
    */

    // 6. ¿Qué ocurriría si un hijo se queda bloqueado? ¿Cómo podría el padre gestionarlo?
    /*
        Pasaría que incluso si el padre tiene wait() se quedaría esperando infinitamente
        Para evitar esto se usan metodos que ponen tiempo límite como:
            - WNOHANG
            - SIGALRM
    */

}
