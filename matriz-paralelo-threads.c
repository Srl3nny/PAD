/*
 * mult-parallel.c
 *
 * Copyright 2016 bruno <bruno@adm123>
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
#include <pthread.h>
#include "leMatriz.h"
#define NUM_THREADS 8 

struct thread_data
{
    int id;
    int *AA;
    int *AB;
    int *AC;
    int columns;
    int lines;
    };

struct thread_data thread_data_array[NUM_THREADS];

int *multiplica(void *threadarg)
    {
        struct thread_data *my_data;
        my_data = (struct thread_data *) threadarg;
        int tid = my_data->id;
        int *AA = my_data->AA;
        int *AB = my_data->AB;
        int *AC = my_data->AC;
        int columns = my_data->columns;
        int lines = my_data->lines;
        int i, j, k;
        int slice = lines /  NUM_THREADS;
        int start = slice * tid;
        int stop = start + slice;

        for (i=start; i<stop; i++)
            for (j=0; j<lines; j++)
            {
                for (k=0; k<lines; k++)
                    AC[i*columns + j] = AA[i*columns + k] * AB[k*columns + j] + AC[i*columns + j];
            }


    }

int main(int argc, char **argv)
{
    pthread_t thread[NUM_THREADS];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);


    int *AA, *AB, *AC, columns, lines, k, i, j, t; //ponteiro AA AB por que matriz é um endereço de memória
    char *fileName1, *fileName2;
    int rc;
    void *status;
    columns = atoi(argv[1]);
    lines = atoi(argv[2]);
    fileName1 = argv[3];
    fileName2 = argv[4];


    AA = (int *) malloc (sizeof(int) * lines * columns);
    AA = leMatriz(columns,lines,fileName1);
    AB = (int *) malloc (sizeof(int) * lines * columns);
    AB = leMatriz(columns,lines,fileName2);
    AC = (int *) malloc (sizeof(int) * lines * columns);
        for (t=0; t<NUM_THREADS; t++)
    {
        printf("criando thread %ld\n", t);
        thread_data_array[t].id = t;
        thread_data_array[t].AA = AA;
        thread_data_array[t].AB = AB;
        thread_data_array[t].AC = AC;
        thread_data_array[t].columns = columns;
        thread_data_array[t].lines = lines;
        rc = pthread_create(&thread[t], &attr, multiplica, (void *) &thread_data_array[t]);
        if (rc){
            printf("Error ao criar thread e %d\n", rc);
            exit(-1);
        }
    }

    pthread_attr_destroy(&attr);
    for (t=0; t<NUM_THREADS; t++)
    {
        rc = pthread_join(thread[t], &status);
        if (rc){
            printf("Erro join e %d\n", rc);
            exit(-1);
        }
        printf("Completo o Join com thread %d com status %ld\n",t,(long)status);
    }
    printf("Main: program completed. Exiting.\n");
   /* for (i=0; i<columns; i++)
        for (j=0; j<lines; j++)
            printf("matriz %d\n", AC[i*columns + j]);*/
    pthread_exit(NULL);



    return 0;
}

