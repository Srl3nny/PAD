#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
    int *AA, *AB, *AC, columns, lines, i, j, k, temp; //ponteiro AA AB por que matriz é um endereço de memória
    char *fileName1, *fileName2;
    columns = atoi(argv[1]);
    lines = atoi(argv[2]);
    AA = (int *) malloc (sizeof(int) * lines * columns);
    AB = (int *) malloc (sizeof(int) * lines * columns);
    AC = (int *) malloc (sizeof(int) * lines * columns);
	
    for (i=0; i<columns; i++){ /*inicializando matriz*/
        for (j=0; j<lines; j++){
		AA[i*columns + j] = 1;
		AB[i*columns + j] = 2;
		AC[i*columns + j] = 30;
	}}
		
    for (i=0; i<columns; i++)
        for (j=0; j<lines; j++)
            {
            for (k=0; k<lines; k++)
                temp += AA[i*columns + k] * AB[k*columns + j];
	AC[i*columns + j] += temp;
	temp = 0; 
                
            }
/*    for (i=0; i<columns; i++){
        for (j=0; j<lines; j++){
	printf ("%d\n", AC[i*columns + j]);
	} }*/
    return 0;
}

