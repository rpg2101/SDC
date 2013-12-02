#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#define ipc_key IPC_PRIVATE
#define rows 10
#define columns 30

int main (){
	int id_shmem ;
	int row,column;
	int *matrix;

// -----------------Escritura del buffer--------------------------------
// Create the shared memory segment
	id_shmem = shmget(ipc_key, sizeof(int)*(rows)*(columns), IPC_CREAT|0666);
// Attach the shared memory to our matrix
	matrix = (int *)shmat(id_shmem, 0, 0);
	printf ("shared memory attached at address %p\n", matrix);
// Loop through all elements in the array
	for (row = 0; row < rows; row++)
	{
		for (column = 0; column < columns; column++)
		{
        matrix[row*columns + column] = 1; // Equivalent to matrix[column][row]
		}
	}
	shmdt (matrix);
// -----------------Lectura del buffer--------------------------------
	matrix = (int *)shmat(id_shmem, (const void *)0x5000000, 0);
	printf ("shared memory reattached at address %p\n", matrix);
	/* Print out the string from shared memory. */
	for (row = 0; row < rows; row++)
	{
		for (column = 0; column < columns; column++)
		{
			printf (" %i " , matrix[row*columns + column] ); // Equivalent to matrix[column][row]
		}
		printf ("\n");
	}
	/* Detach the shared memory segment. */
	shmdt (matrix);
	/* Deallocate the shared memory segment. */
	shmctl (id_shmem, IPC_RMID, 0);
	
	return 0;
}


