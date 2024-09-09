/*
Integrantes:
- Samuel Acevedo Bustamante(1001016099)
- Manuela GUtiérrez Cano (1037657256)


TODO: Permitir recibir archivos por la stdinput.
Permitir escoger el nombre del archivo de salida, y también permitir escribir el resultado en
la salida estándar.

Pa eso capaz tengo que compartimentar el código.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{

    if (argc >= 3)
    {
        fprintf(stderr, "Error: Cantidad de argumentos invalida. El máximo de argumentos es 2");
    }

    // Variable declarations
    FILE *rptr; // Pointers to files
    FILE *wptr;

    char *stream; // Buffers, lines, line_list
    char line[100];
    int linec = 0;

    rptr = fopen(argv[1], "r");

    //////////////////

    // Contar las líneas del archivo
    while (!feof(rptr))
    {
        stream = fgets(line, 100, rptr);
        linec++;
    }

    char *line_list[linec]; // Crea un array para guardar las líneas

    // Reinicia el contador de líneas y vuelve al inicio del stream.
    linec = 0;
    fseek(rptr, 0, SEEK_SET);

    // Lee el archivo nuevamente, deteniendose en caso de EOF(End of file) o si se presenta algún error.
    while (!feof(rptr) || !ferror(rptr))
    {
        stream = fgets(line, 100, rptr);
        /*Theres a seg fault because if checks the condition of feof and ferror before it
        reads the next stream line and thus it executes strlen(stream) and it fails
        */
        if (feof(rptr) || ferror(rptr)) // Amaño para evitar el segmentation fault.
        {
            if (ferror(rptr))
            {
                fprintf(stderr, "Se presentó un error leyendo el archivo");
                exit(1);
            }
            break;
        }
        // Clona la línea y almacena el puntero a esta a la tabla line_list
        line_list[linec] = strdup(line);
        linec++;
    }

    // Escribe en el archivo de salida.

    for (int i = linec - 1; i >= 0; i--)
    {
        wptr = fopen(argv[2], "a");
        fputs(line_list[i], wptr);
        fclose(wptr);
        // Esta joda me está retornando mero archivo binario ahí. Seguramente estoy almacenando mal los strings o algo
    }

    // stdin = 0
    // stdout = 1

    // Usar la variable argc para determinar cuantos argumentos se utilizaron llamando la función.
    // Si es uno sólo, se hace uso de stdout. Si no son ninguno se lee también stdin.
    // Si son más de tres. Se manda un error y listo.

    int descriptor = fileno(stdout);
    printf("Descriptor de la salida estándar: %i", descriptor);
}
