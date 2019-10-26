#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#define MAXIMUM 100

int A[MAXIMUM][MAXIMUM], B[MAXIMUM][MAXIMUM], C[MAXIMUM][MAXIMUM];

struct cell {
        int row;
        int col;
        int end;
        int result;
};

void* multiply_cell(void* item)
{
        struct cell *cell_struct =
                (struct cell*) item;

        int sum = 0;
        int i;
        int r = cell_struct->row;
        int c = cell_struct->col;
        int n = cell_struct->end;
        //TODO: we will see how will get the limit of the loop later
        for ( i = 0; i <n; i++) {
                sum += A[r][i]*B[i][c];
        }

        printf("cell= %d\n",sum );
        cell_struct->result = sum;
        // C[r][c] =sum;
        sum=0;

        pthread_exit(0);
}

int main()
{
        int m1, n1, m2, n2, i, j;
        int max=m1*n2;

        // Read the elements of Matrix A from user


        // Read size of Matrix A from user
        printf("\nEnter the number of ms of first Matrix: ");
        scanf("%d", &m1);
        printf("%d", m1);
        printf("\nEnter the number of numns of first Matrix: ");
        scanf("%d", &n1);
        printf("%d", n1);

        // Read size of Matrix B from user
        printf("\nEnter the number of ms of Second Matrix: ");
        scanf("%d", &m2);
        printf("%d", m2);
        printf("\nEnter the number of numns of Second Matrix: ");
        scanf("%d", &n2);
        printf("%d", n2);


// Read the elements of Matrix A from user
        printf("\nEnter the elements of First Matrix: ");
        for (i = 0; i < m1; i++) {
                for (j = 0; j < n1; j++) {
                        printf("\nA[%d][%d]: ", i, j);
                        scanf("%d", &A[i][j]);
                        printf("%d", A[i][j]);
                }
        }
        // Read the elements of Matrix B from user
        printf("\nEnter the elements of Second Matrix: ");
        for (i = 0; i < m2; i++) {
                for (j = 0; j < n2; j++) {
                        printf("\nB[%d][%d]: ", i, j);
                        scanf("%d", &B[i][j]);
                        printf("%d", B[i][j]);
                }
        }


        int thread_num=0;
        int k;
        int l;
        pthread_t threads[max];
        struct cell cells[max];
        for (i = 0; i < m1; i++) {
                for(j=0; j<n2; j++)
                {       cells[thread_num].row=i;
                        cells[thread_num].col=j;
                        cells[thread_num].end=n1;
                        pthread_create(&threads[thread_num], NULL, multiply_cell, &cells[thread_num]);
                        thread_num++;}
        }

        int count=0;
        // for ( k = 0; k < m1; k++)
        //         for(l=0; l<n2; l++) {
        //                 pthread_join(threads[count], NULL);
        //                 C[k][l] = cells[count].result;
        //                 count++;
        //         }
        for ( k = 0; k < max; k++){
                        pthread_join(threads[k], NULL);
                        C[cells[k].row][cells[k].col]=cells[k].result;
                }
                printf("hi\n");

        for ( i = 0; i < m1; i++) {
                for (int j = 0; j < n2; j++)
                        printf("%d ", C[i][j]);

                printf("\n");
        }

        return 0;
}
