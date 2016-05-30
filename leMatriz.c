/*
 * leMatriz.c
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


int *leMatriz(int columns, int lines, char *fileName1)
{
    int *A;
    A = (int *) malloc (sizeof(int) * lines * columns);
    int i, j;
    FILE *arq;
    arq = fopen(fileName1, "r");
    if (arq == NULL)
    {
        perror("I cannot open output file.\n");
        //exit(EXIT_FAILURE);
    }
    for (i=0;i<columns;i++)
        for (j=0;j<lines;j++)
            fscanf(arq, "%d ", &A[i * columns + j]);
    fclose(arq);
    return A;

}

