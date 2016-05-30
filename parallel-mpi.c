/*
 * mpi_exercicio2.c
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


#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#define size 1000



int a[size][size];
int b[size][size];
int c[size][size];

void mult(int ini, int fim)
{
    int temp;
    for (int i = ini; i <= fim; ++i) {
        for (int j = 0; j < size; ++j) {
            for (int k = 0; k < size; ++k) {
                temp += a[i][k] * b[k][j];
            }
	  c[i][j] += temp,
	  temp = 0;
        }
    }
}

void preenche(void)
{
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            a[i][j] = 1;
            b[i][j] = 2;
            c[i][j] = 30;
            }
        }

}

int main(int argc, char* argv[])
{
    int rank, nproc;
    int ini, fim, rc;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   /* verifica se execução será paralela*/ 
    if (nproc<2)
    {
        printf("\n\nParando programa necessiario no minimo 2 processos \n");
        MPI_Abort(MPI_COMM_WORLD, rc);
        exit(0);
    }

/* verifica se divisão do tamanho total matris por num processos deixa resto, caso deixe não faz pois o progema não está preparado para isso*/
    if (size % nproc > 0) {
        printf("\n\n Parando programa necessario ser um num divisivel por %d \n", size*size);
        MPI_Abort(MPI_COMM_WORLD, rc);
        exit(0);
     }


    if (rank == 0) {
        preenche(); 
    }

   /* Envia as matrizes em broadcast para todos os processos*/    
    MPI_Bcast(a, size*size, MPI_FLOAT, 0,MPI_COMM_WORLD);
    MPI_Bcast(b, size*size, MPI_FLOAT, 0,MPI_COMM_WORLD);
    MPI_Bcast(c, size*size, MPI_FLOAT, 0,MPI_COMM_WORLD);

   /*setar inicio e fim do for para cada processo*/ 
    ini = (size / nproc) * rank;
    fim = (size / nproc) * (rank + 1) - 1;

    
    mult(ini, fim);

   /*Obtem as mensagens de todos os processos*/ 
    MPI_Gather(c + (size/nproc*rank),
               size*size/nproc,
               MPI_FLOAT,
               c + (size/nproc*rank),
               size*size/nproc,
               MPI_FLOAT,
               0,
               MPI_COMM_WORLD);

/*    if (rank == 0) {
    	for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
	printf("%d\n", c[i][j]);
	}}   
    }*/

    MPI_Finalize();
    return 0;
}
