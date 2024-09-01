#include<stdio.h>
#include<stdlib.h>

void read_file(FILE *fd){    
    int linec = 0;    
    char line[100];
    char *stream;
    do
    {  
        stream = fgets(line, 100, fd);   
        printf("%s", stream);
        linec++;
    } while (stream != NULL);

}

int main(int argc, char *argv[]){

    FILE *rptr; // Define pointers

    //rptr = fopen(argv[1], "r");
    rptr = fopen("example.txt", "r");
    printf("El argumento es: %s\n", argv[1]);
    read_file(rptr);
}

