/*
 * mult-serial.c
 *
 * Copyright 2016 bruno <bruno@angus>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include "leMatriz.h"

int main(int argc, char **argv)
{
    int *AA, *AB, *AC, columns, lines, i, j, k; //ponteiro AA AB por que matriz é um endereço de memória
    char *fileName1, *fileName2;
    columns = atoi(argv[1]);
    lines = atoi(argv[2]);
    fileName1 = argv[3];
    fileName2 = argv[4];
    int B[columns][lines];
    int C[columns][lines];
    int D[columns][lines];
    AA = (int *) malloc (sizeof(int) * lines * columns);
    AA = leMatriz(columns,lines,fileName1);
    AB = (int *) malloc (sizeof(int) * lines * columns);
    AB = leMatriz(columns,lines,fileName2);
    AC = (int *) malloc (sizeof(int) * lines * columns);
	
    for (i=0; i<columns; i++)
        for (j=0; j<lines; j++)
            {
            for (k=0; k<lines; k++)
                AC[i*columns + j] = AA[i*columns + k] * AB[k*columns + j] + AC[i*columns + j];
                
            }
     /*for (i=0; i<columns; i++)
        for (j=0; j<lines; j++)
			printf("%d\n", AC[i*columns + j]);
*/

    return 0;
}
