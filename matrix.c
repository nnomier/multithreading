#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXIMUM 100

// int A[MAXIMUM][MAXIMUM], B[MAXIMUM][MAXIMUM], C1[MAXIMUM][MAXIMUM],C2[MAXIMUM][MAXIMUM];
int *A, *B, *C1,*C2;
int m1,m2,n1,n2;

struct cell {
								int row;
								int col;
								int end;
								int result;
};

struct row {
								int row_num;
								int m;
								int n;
};

void readMatrix()
{
								FILE *f;
								f =fopen("input.txt","r");
								int i,j;
								fscanf(f, "%d%d",&m1,&n1);
								for(i=0; i<m1; i++)
								{
																for(j=0; j<n1; j++)
																{
																								fscanf(f, "%d",&*(A+i*n1+j));
																								// fscanf(f, "%d",&A[i][j]);

																}
								}

								fscanf(f, "%d%d",&m2,&n2);

								for(i=0; i<m2; i++)
								{
																for(j=0; j<n2; j++)
																{
																								// fscanf(f, "%d",&A[i][j]);
																								fscanf(f, "%d",&*(B+i*n2+j));
																}
								}
								fclose(f);
}

void writeFile(){
								FILE *f;
								int i;
								int j;
								f =fopen("input.txt","w");
								fprintf(f, "ELEMENT BY ELEMENT RESULT \n");
								for ( i = 0; i < m1; i++) {
																for ( j = 0; j < n2; j++)
																								fprintf(f, "%d", *(C1+i*n2+j));

																// fprintf(f, "%d",C1[i][j] );
																fprintf(f,"\n");
								}
								// fprintf(f, "ROW THREADING RESULT \n");
								// for ( i = 0; i < m1; i++) {
								//         for (int j = 0; j < n2; j++)
								//                 fprintf(f, "%d", *(C2+i*n2+j));
								//         fprintf(f,"\n");
								// }
								fclose(f);
}

void* multiply_cell(void* item)
{
								struct cell *cell_struct =
																(struct cell*) item;
								int sum = 0;
								int i;
								int r = cell_struct->row;
								int c = cell_struct->col;
								int n = cell_struct->end;
								for ( i = 0; i <n; i++) {
																// sum += A[r][i]*B[i][c];
																int temp = *(A+r*n+i)  * *(B+i*n+c);
																sum+=temp;
								}
								printf("cell= %d\n",sum );
								cell_struct->result = sum;
								// C[r][c] =sum;
								sum=0;
								pthread_exit(0);
}

// void* multiply_row(void* item)
// {
//         struct row *row_struct =
//                 (struct row*) item;
//         int r = row_struct->row_num;
//         int m =row_struct->m;
//         int n = row_struct->n;
//         int sum = 0;
//         int i;
//         int j;
//         for ( i = 0; i < n; i++)
//                 for ( j = 0; j < m; j++)
//                         C2[r][i] += A[r][j] * B[j][i];
//         // C[r][c] =sum;
//         pthread_exit(0);
// }
//
void cellThreading()
{
								printf("----- A) CREATE A THREAD FOR EACH ELEMENT ----- \n" );

								int i, j;

								int thread_num=0;
								int k;
								int l;
								pthread_t threads[m1][n2];
								struct cell cells[m1][n2];
								for (i = 0; i < m1; i++) {
																for(j=0; j<n2; j++)
																{       cells[i][j].row=i;
																								cells[i][j].col=j;
																								cells[i][j].end=n1;
																								pthread_create(&threads[i][j], NULL, multiply_cell, &cells[i][j]);}
								}

								int count=0;
								for ( k = 0; k < m1; k++) {
																for(l=0; l<n2; l++) {
																								pthread_join(threads[k][l], NULL);
																								*(C1+k*n2+l)= cells[k][l].result;
																}
								}



}
//
// void rowThreading()
// {
//         printf("----- B) CREATE A THREAD FOR EACH ROW ----- \n" );
//         int i, j;
//
//         int thread_num=0;
//         int k;
//         int l;
//         pthread_t threads[m1];
//         struct row rows[m1];
//         for (i = 0; i < m1; i++) {
//                 rows[i].row_num=i;
//                 rows[i].n=n2;
//                 rows[i].m=n1;
//                 pthread_create(&threads[i], NULL, multiply_row, &rows[i]);
//         }
//
//         int count=0;
//         for ( k = 0; k < m1; k++) {
//
//                 pthread_join(threads[k], NULL);
//
//         }
//
// }

int main()
{
								readMatrix();
								A= (int*) malloc(m1*n1*sizeof(int));
								B= (int*) malloc(m2*n2*sizeof(int));
								C1= (int*) malloc(m1*n2*sizeof(int));
								C2= (int*) malloc(m1*n2*sizeof(int));

								// A = (int **)malloc(m1 * sizeof(int *));
								// for (i=0; i<m1; i++)
								//         A[i] = (int *)malloc(n1 * sizeof(int));
								//
								// B = (int **)malloc(m2 * sizeof(int *));
								// for (i=0; i<m2; i++)
								//         B[i] = (int *)malloc(n2 * sizeof(int));
								//
								//
								// C1 = (int **)malloc(m1 * sizeof(int *));
								// for (i=0; i<m1; i++)
								//         B[i] = (int *)malloc(n2 * sizeof(int));
								//
								// C2 = (int **)malloc(m1 * sizeof(int *));
								// for (i=0; i<m1; i++)
								//         B[i] = (int *)malloc(n2 * sizeof(int));



								clock_t time;
								cellThreading();
								//	rowThreading();
								writeFile();
								return 0;
}
