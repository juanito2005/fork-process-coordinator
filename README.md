# 🔄 Coordinador de Procesos con `fork()`

Este proyecto implementa una simulación de carga de trabajo distribuida utilizando llamadas al sistema UNIX en C (`fork`, `wait`, `exit`).

El programa consiste en un **proceso padre** que coordina la creación y gestión de **4 procesos hijos**, cada uno realizando tareas computacionales independientes de forma concurrente.

## 📋 Descripción de la Práctica

El objetivo principal es comprender experimentalmente:
* La creación de procesos mediante `fork()`.
* La ejecución paralela e independiente.
* La sincronización del padre esperando a los hijos mediante `wait()`.
* El intercambio de códigos de salida (exit status).

### 🚀 Funcionalidades Implementadas

El proyecto cumple con los requisitos básicos y añade varias **ampliaciones opcionales**:

1.  **Proceso Padre**:
    * Inicia la ejecución y lanza los procesos hijos.
    * Espera a que todos terminen y recoge sus resultados.
    * Calcula estadísticas globales (Suma total, Media).
    * **Ampliación:** Mide el tiempo total de ejecución con precisión de microsegundos (`gettimeofday`).
    * **Ampliación:** Muestra una tabla comparativa del orden de creación vs. orden de finalización.

2.  **Procesos Hijos**:
    * **Hijo 1:** Calcula la suma de los números del 1 al 10.
    * **Hijo 2:** Cuenta la cantidad de números primos entre el 1 y el 30.
    * **Hijo 3:** Calcula el factorial de 5 (5!).
    * **Hijo 4 (Ampliación):** Calcula la suma de los números pares del 1 al 20.

## 🛠️ Requisitos

* GCC (GNU Compiler Collection) o Clang.
* Sistema operativo tipo UNIX (Linux o macOS).
* Make (opcional, para usar el Makefile incluido).

## ⚙️ Compilación e Instalación

El proyecto incluye un `Makefile` para facilitar la compilación y limpieza de binarios.

1.  **Clonar el repositorio:**
    ```bash
    git clone <URL_DEL_REPO>
    cd fork-process-coordinator
    ```

2.  **Compilar el proyecto:**
    ```bash
    make mi-proceso
    ```
    *Esto generará el ejecutable en la carpeta `bin/`.*

3.  **Compilar las respuestas teóricas (Opcional):**
    ```bash
    make respuestas
    ```

4.  **Limpiar binarios antiguos (Recomendado antes de compilar):**
    ```bash
    make clean
    ```

## ▶️ Ejecución

Para ejecutar el coordinador de procesos principal:

```bash
./bin/mi_proceso
# O usando el atajo del Makefile:
make run-mi-proceso

=== INICIO DEL PROGRAMA ===
[PADRE] PID=12345, PPID=6789
[PADRE] Voy a crear 3 procesos hijos...

=== [HIJO 1] PID=12346... Calcularé la suma de 1 a 10...
=== [HIJO 2] PID=12347... Contaré primos del 1 al 30...
...
[PADRE] Hijo con PID=12346 terminó con resultado: 55
...
=== RESUMEN FINAL ===
[PADRE] Suma total de resultados: 247
[PADRE] Media total de resultados: 61.750
[PADRE] Tiempo total: 4005123 us (4005.123 ms)

.
├── Makefile                 # Script de automatización de compilación
├── README.md                # Documentación del proyecto
├── src/
│   ├── mi_proceso.c         # Código fuente principal (Lógica de fork/wait)
│   └── respuestas_preguntas.c # Código con respuestas a cuestiones teóricas
└── bin/                     # Directorio donde se generan los ejecutables