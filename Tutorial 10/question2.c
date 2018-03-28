/*
 * Tutorial 10 MPI Demo for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Author: Jonathan Gillett
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>

// Define process 0 as MASTER
#define MASTER 0

#define DATA_SIZE 10000000
#define CHUNK_SIZE 100

void master(int n_proc)
{
    //double data[DATA_SIZE] = { 0 };    // The data to send
    //double chunk[CHUNK_SIZE] = { 0 };  // The chunk to store results
    //double results[DATA_SIZE] = { 0 }; // The final calculations
    double total_chunks = 100;
    double total = 0;
    int n_sent = 0, n_recv = 0;        // The number of the data chunks sent/recv
    int proc = 0;                      // The process that returned data
    MPI_Status status;                 // MPI status struct
	double *data = malloc( DATA_SIZE * sizeof(* data) );
	//double *chunk = malloc( DATA_SIZE * sizeof(* chunk) );
	//double *results = malloc( DATA_SIZE * sizeof(* results) );
    // Populate the data to send to slaves
    for (int i = 0; i < 10; ++i)
    {
        data[i] = i;
		printf("%d\n",i);
    }
	printf("done\n");
    // "Map" the data to slave processes
    // i MUST start from 1, since MASTER is process 0!
    for (int i = 1; i < n_proc; ++i)
    {
        // Send CHUNK_SIZE of data to each process initially
        // Sends data, of type double to process 'i'
        MPI_Send(&data[DATA_SIZE], DATA_SIZE, MPI_DOUBLE, i, 
                 n_sent, MPI_COMM_WORLD);
        n_sent++;
    }

    // Receive EACH of the chunks from the slave processes
    for (int i = 0; i < total_chunks; ++i)
    {
        // Receive the computed chunk back from the slave
        MPI_Recv(data, DATA_SIZE, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG,
                 MPI_COMM_WORLD, &status);
        // Get the process that sent the data and send it the next chunk
        proc = status.MPI_SOURCE;
        n_recv = status.MPI_TAG;
        
        // Copy the results from the slave into the results array
        /*for (int i = 0; i < CHUNK_SIZE; ++i)
        {
            results[n_recv*CHUNK_SIZE + i] = chunk[i];
        }*/

        if (n_sent < total_chunks)
        {
            MPI_Send(&data[DATA_SIZE], DATA_SIZE, MPI_DOUBLE, proc, 
                     n_sent, MPI_COMM_WORLD);
            n_sent++;
        }
    }
	printf("master here\n");
    // Send all the slave processes STOP signal, (TAG of CHUNK_SIZE)
    for (int i = 1; i < n_proc; ++i)
    {
        MPI_Send(data, DATA_SIZE, MPI_DOUBLE, i, 
                 DATA_SIZE, MPI_COMM_WORLD);
    }

   /* for (int i = 1; i < DATA_SIZE; ++i)
    {
        if (data[i] < 1)
        {
            printf("ERROR, DATA ZERO AT INDEX %d\n", i);
        }
    }*/
    /*// "Reduce" and calculate the final summation
    for (int i = 0; i < DATA_SIZE; ++i)
    {
        total += results[i];
    }

    printf("The final sum of the calculation: %f\n", total);*/
}


void slave(int proc_id)
{
    double *chunk= malloc( DATA_SIZE * sizeof(* chunk) );;  // The chunk to receive for calculations
    //double result[DATA_SIZE] = { 0 }; // The results
    int n_recv = 0;                    // The number of the data chunk received
    MPI_Status status;                 // MPI status struct

    // Receive the chunk to calculate from MASTER
    MPI_Recv(chunk, DATA_SIZE, MPI_DOUBLE, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
    n_recv = status.MPI_TAG;
	//printf("slave here");
    // Calculate all results provided until "STOP" signal recieved (CHUNK_SIZE)
    while (n_recv < CHUNK_SIZE)
    {
        /*// Perform our "calculation" to return back to MASTER
        for (int i = 0; i < CHUNK_SIZE; ++i)
        {
            result[i] = chunk[i] * chunk[i];
        }*/

        // Send the results back to MASTER, include in TAG the chunk that was calculated
        MPI_Send(chunk, DATA_SIZE, MPI_DOUBLE, MASTER, n_recv, MPI_COMM_WORLD);
        
        // Wait for the next chunk of data to be received
        MPI_Recv(chunk, DATA_SIZE, MPI_DOUBLE, MASTER, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        n_recv = status.MPI_TAG;
		//printf("slave here");
    }
}


int main (int argc, char* argv[])
{
    int proc_id;            // Process rank
    int n_proc;             // Number of processes
	double t1,t2;
    // Initialize MPI
    MPI_Init(&argc, &argv);
    
    // Get the current number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &n_proc);

    // Get the current process id
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
    
	    t1=MPI_Wtime();
    if (proc_id == MASTER)
    {
        master(n_proc);
    }
    else
    {
        slave(proc_id);
    }
	t2=MPI_Wtime();
	printf("elapsed time = %f seconds\n",t2-t1);
    // Required to terminate all MPI processes
    MPI_Finalize();
}
