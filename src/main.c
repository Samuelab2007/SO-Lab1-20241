#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*void read_file(FILE *fd){    
    int linec = 0;    
    char line[100];
    char *stream;

    while(!feof(fd)){
        stream = fgets(line, 100, fd);
        linec++;
    }

    char *line_list[linec];
    linec = 0;
    fseek(fd, 0, SEEK_SET);
    while(!feof(fd) || !ferror(fd)){  
        stream = fgets(line, 100, fd); 
       if (feof(fd) || ferror(fd))  //Amaño para evitar el segmentation fault.
       {
        break;
       }

        line_list[linec] = strdup(line);
        linec++;
    }

    for (int i = linec-1; i >= 0; i--)
    {
        FILE *wptr;
        wptr = fopen("output.txt","a");
        fputs(line_list[i] , wptr);
        fclose(wptr);
        // Esta joda me está retornando mero archivo binario ahí. Seguramente estoy almacenando mal los strings o algo
    }
    
    
}*/


int main(int argc, char *argv[]){

    //Variable declarations
    FILE *rptr; //Pointers to files
    FILE *wptr;

    char *stream;   //Buffers, lines, line_list
    char line[100];
    int linec = 0;
    


    rptr = fopen(argv[1], "r");
    

    //////////////////

    // Contar las líneas del archivo
    while(!feof(rptr)){
        stream = fgets(line, 100, rptr);
        linec++;
    }

    char *line_list[linec]; //Crea un array para guardar las líneas
    
    // Reinicia el contador de líneas y vuelve al inicio del stream.
    linec = 0;
    fseek(rptr, 0, SEEK_SET);

    // Lee el archivo nuevamente, deteniendose en caso de EOF(End of file) o si se presenta algún error. 
    while(!feof(rptr) || !ferror(rptr)){  
        stream = fgets(line, 100, rptr); 
        /*Theres a seg fault because if checks the condition of feof and ferror before it 
        reads the next stream line and thus it executes strlen(stream) and it fails
        */
       if (feof(rptr) || ferror(rptr))  //Amaño para evitar el segmentation fault.
       {
        if(ferror(rptr)){
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
    for (int i = linec-1; i >= 0; i--)
    {
        wptr = fopen("output.txt", "a");
        fputs(line_list[i] , wptr);
        fclose(wptr);
        // Esta joda me está retornando mero archivo binario ahí. Seguramente estoy almacenando mal los strings o algo
    }
    
    
 
}

