/*
 * gera-matriz.c
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


void initMatriz (int col, int lin, char *fileName1)
{
    lin = (int) lin;
    col = (int) col;
    int i, j;
    FILE *arq;
    int A[col][lin];
    for (i=0;i<col;i++)
        for (j=0;j<lin;j++)
        {
            A[i][j] = rand() % 1000 ;
        }
    arq = fopen(fileName1, "w");
    if (arq == NULL)
    {
        perror("I cannot open output file.\n");
        //exit(EXIT_FAILURE);
    }
    for (i=0;i<col;i++)
        for (j=0;j<lin;j++)
            fprintf(arq, "%d ",A[i][j]);
    fclose(arq);

    }


int main(int argc, char **argv)
{
    int col, lin;
    char *fileName1;
    col = atoi(argv[1]);
    lin = atoi(argv[2]);
    fileName1 = argv[3];
    initMatriz(col,lin,fileName1);
    return 0;
}

