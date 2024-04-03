#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h> // Para fork(), sleep()
#include <sys/wait.h>
void animacion() {
    system("clear"); // Limpiar la pantalla
    printf("\033[?25l"); // Ocultar el cursor
    printf("Cargando");
    fflush(stdout); // Forzar la salida del búfer

    for (int i = 0; i < 10; ++i) {
        printf(".");
        fflush(stdout);
        usleep(200000); // Esperar 200ms
    }

    printf("\n\033[?25h"); // Mostrar el cursor
}
