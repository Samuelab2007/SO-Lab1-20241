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
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int files_hardlinked(const char *file1, const char *file2)
{
    struct stat stat1, stat2;

    stat(file1, &stat1);
    stat(file2, &stat2);

    if (stat1.st_ino == stat2.st_ino)
    {
        return 1; // Files hardlinked
    }
    else
    {
        return 0; // Files are not hardlinked
    }
}

int main(int argc, char *argv[])
{
    // validacion de la cantidad de argumentos pasados al programa
    if (argc >= 4)
    {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    // Variable declarations
    FILE *rptr; // Pointers to files
    FILE *wptr;

    char *stream; // Buffers, lines, line_list
    char line[100];
    int linec = 0;

    rptr = fopen(argv[1], "r");

    // Error al intentar abrir el archivo de entrada
    const char *nombre_archv = argv[1];
    if (rptr == NULL)
    {
        fprintf(stderr, "reverse: cannot open file '%s'\n", nombre_archv);
        exit(1);
    }
    // TODO LO QUE SEA COMPARAR DIRECTAMENTE ARGV[] ES PROPENSO A SEGFAULTS, PORQUE ESOS VALORES
    // PUEDEN ESTAR O NO ESTAR DEFINIDOS

    if (argc > 2)
    {
        if (strcmp(argv[1], argv[2]) == 0)
        {
            fprintf(stderr, "reverse: input and output file must differ\n");
            exit(1);
        }

        int hardlink_verify = files_hardlinked(argv[1], argv[2]);
        if (hardlink_verify == 1)
        {
            fprintf(stderr, "reverse: input and output file must differ\n");
            exit(1);
        }
    }

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

    if (argc > 2)
    {
        // Escribe en el archivo de salida.

        wptr = fopen(argv[2], "w");

        // Error al intentar abrir el achivo de salida
        const char *name_file = argv[2];
        if (wptr == NULL)
        {
            fprintf(stderr, "Error: cannot open file\n", name_file);
            exit(1);
        }
    }

    // Compara si los archivos de entrada y salida son iguales
    // while (!feof(rptr) && !feof(wptr))
    //{
    //    line2 = (char*)malloc(sizeof(int));
    // Fallo en asignacion de memoria dinamica (malloc falla)
    //    if (line2 == NULL)
    //    {
    //        fprintf(stderr, "Malloc failed"\n);
    //        exit(1);
    //    }
    //    linearptr = fgets(line, 100, rptr);
    //    lineawptr = fgets(line2, 100, wptr);
    //    if (strcmp(linearptr, lineawptr) == 0)
    //    {
    //        fprintf(stderr, "Los archivos de entrada y de salida deben diferir\n");
    //        exit(0);
    //    }

    //}

    for (int i = linec - 1; i >= 0; i--)
    {
        // De momento es para cuando se utiliza solo la entrada
        if (argc < 3)
        {
            fputs(line_list[i], stdout);
        }
        else
        {
            fputs(line_list[i], wptr);
        }
    }
    if (argc > 2)
    {
        fclose(wptr);
    }

    // Usar la variable argc para determinar cuantos argumentos se utilizaron llamando la función.
    // Si es uno sólo, se hace uso de stdout. Si no son ninguno se lee también stdin.
    // Si son más de tres. Se manda un error y listo.
}
