#include <stdio.h>
#include <stdlib.h>
#include "leMatriz.h"

int main(int argc, char **argv)
{
    int nthreads, tid;
    int *AA, *AB, *AC, *AD, inter = 0, columns, lines, i, j, k, chunk = 8; //ponteiro AA AB por que matriz é um endereço de memória
    char *fileName1, *fileName2, *fileName3;
    columns = atoi(argv[1]);
    lines = atoi(argv[2]);
    fileName1 = argv[3];
    fileName2 = argv[4];
    fileName3 = argv[5];
    int B[columns][lines];
    int C[columns][lines];
    int D[columns][lines];
    AA = (int *) malloc (sizeof(int) * lines * columns);
    AA = leMatriz(columns,lines,fileName1);
    AB = (int *) malloc (sizeof(int) * lines * columns);
    AB = leMatriz(columns,lines,fileName2);
    AC = (int *) malloc (sizeof(int) * lines * columns);
    AC = leMatriz(columns,lines,fileName3);
    AD = (int *) malloc (sizeof(int) * lines * columns);
    
    #pragma omp parallel private(i , j , k , tid, inter) shared(AA , AB , AC , nthreads , chunk , columns, lines)
  	{
		tid = omp_get_thread_num();
		if(tid == 0)
			nthreads = omp_get_num_threads();
    #pragma omp for schedule(static , chunk)
    for (i=0; i<columns; i++)
        for (j=0; j<lines; j++)
            {
            	for (k=0; k<lines; k++)
                	inter = AA[i*columns + k] * AB[k*columns + j] + inter;
		AD[i*columns + j] = inter + AC[i*columns + j];
		inter = 0;
		

            }
	}
/*    for (i=0; i<columns; i++)
        for (j=0; j<lines; j++)
            printf("%d\n", AD[i*columns + j]);
*/
    return 0;
}
