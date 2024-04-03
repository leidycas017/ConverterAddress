#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h> // Para fork(), sleep()
#include <sys/wait.h>

void animacion()
{
    system("clear");     // Limpiar la pantalla
    printf("\033[?25l"); // Ocultar el cursor
    printf("Cargando");
    fflush(stdout); // Forzar la salida del búfer

    for (int i = 0; i < 10; ++i)
    {
        printf(".");
        fflush(stdout);
        usleep(200000); // Esperar 200ms
    }

    printf("\n\033[?25h"); // Mostrar el cursor
}

void print_cabecera()
{
    printf("\033[1;36m"); // Cambiar el color del texto a cian brillante
    printf("*********************************************\n");
    printf("*      Conversión de direcciones VA / PA    *\n");
    printf("*            Autores: Yuly Alvear           *\n");
    printf("*                     Leidy Castaño          *\n");
    printf("*                    Omar Torres            *\n");
    printf("*********************************************\n");
    printf("\033[0m"); // Restaurar el color del texto a su valor predeterminado
}

void convertirDirecciones() {
    int opcion, VA, BASE, BOUNDS, PA;
    bool en_kilobytes_va, en_kilobytes_pa, en_kilobytes_base, en_kilobytes_bounds;

    printf("Seleccione la opción:\n1. Calcular dirección física (PA)\n2. Calcular dirección virtual (VA)\n");
    scanf("%d", &opcion);
    pid_t pid;
    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        if (opcion == 1) {
            // Calcular PA
            printf("Ingrese el valor de la memoria virtual (VA): ");
            scanf("%d", &VA);
            printf("¿Está VA en kilobytes? (si/no): ");
            char va_en_kb[3];
            scanf("%s", va_en_kb);
            en_kilobytes_va = (va_en_kb[0] == 's' || va_en_kb[0] == 'S');
            if (en_kilobytes_va) {
                VA *= 1024;
            }
            printf("Ingrese el valor de BASE: ");
            scanf("%d", &BASE);
            printf("¿Está BASE en kilobytes? (si/no): ");
            char base_en_kb[3];
            scanf("%s", base_en_kb);
            en_kilobytes_base = (base_en_kb[0] == 's' || base_en_kb[0] == 'S');
            if (en_kilobytes_base) {
                BASE *= 1024;
            }
            printf("Ingrese el valor de BOUNDS: ");
            scanf("%d", &BOUNDS);
            printf("¿Está BOUNDS en kilobytes? (si/no): ");
            char bounds_en_kb[3];
            scanf("%s", bounds_en_kb);
            en_kilobytes_bounds = (bounds_en_kb[0] == 's' || bounds_en_kb[0] == 'S');
            if (en_kilobytes_bounds) {
                BOUNDS *= 1024;
            }

            // Validar la dirección
            if (0 <= VA && VA <= BOUNDS) {
                // Calcular la dirección física
                PA = VA + BASE;
                printf("La dirección virtual es válida.\n");
                printf("Dirección física (PA): %d bytes\n", PA);
            } else {
                printf("La dirección virtual está fuera de los límites (BOUNDS).\n");
            }
        } else if (opcion == 2) {
            // Calcular VA
            printf("Ingrese el valor de la memoria física (PA): ");
            scanf("%d", &PA);
            printf("¿Está PA en kilobytes? (si/no): ");
            char pa_en_kb[3];
            scanf("%s", pa_en_kb);
            en_kilobytes_pa = (pa_en_kb[0] == 's' || pa_en_kb[0] == 'S');
            if (en_kilobytes_pa) {
                PA *= 1024;
            }
            printf("Ingrese el valor de BASE: ");
            scanf("%d", &BASE);
            printf("¿Está BASE en kilobytes? (si/no): ");
            char base_en_kb[3];
            scanf("%s", base_en_kb);
            en_kilobytes_base = (base_en_kb[0] == 's' || base_en_kb[0] == 'S');
            if (en_kilobytes_base) {
                BASE *= 1024;
            }
            printf("Ingrese el valor de BOUNDS: ");
            scanf("%d", &BOUNDS);
            printf("¿Está BOUNDS en kilobytes? (si/no): ");
            char bounds_en_kb[3];
            scanf("%s", bounds_en_kb);
            en_kilobytes_bounds = (bounds_en_kb[0] == 's' || bounds_en_kb[0] == 'S');
            if (en_kilobytes_bounds) {
                BOUNDS *= 1024;
            }

            // Validar la dirección
            VA = PA - BASE;
            if (0 <= VA && VA <= BOUNDS) {
                // Calcular la dirección virtual
                printf("La dirección física es válida.\n");
                printf("Dirección virtual (VA): %d bytes\n", VA);
            } else {
                printf("La dirección física está fuera de los límites (BOUNDS).\n");
            }
        } else {
            printf("Opción no válida. Por favor, seleccione 1 o 2.\n");
        }
        exit(EXIT_SUCCESS); // Salir del proceso hijo
    } else {
        // Proceso padre
        wait(NULL); // Esperar a que el proceso hijo termine
    }
}
