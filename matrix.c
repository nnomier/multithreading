#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define MAXIMUM 100

// int A[MAXIMUM][MAXIMUM], B[MAXIMUM][MAXIMUM], C1[MAXIMUM][MAXIMUM],C2[MAXIMUM][MAXIMUM];
int *A, *B, *C1,*C2;
int m1,m2,n1,n2;

struct cell {
								int row;
								int col;
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
								A= (int*) malloc(m1*n1*sizeof(int));

								for(i=0; i<m1; i++)
								{
																for(j=0; j<n1; j++)
																{
																								fscanf(f, "%d",&*(A+i*n1+j));
																								// fscanf(f, "%d",&A[i][j]);

																}
								}

								fscanf(f, "%d%d",&m2,&n2);
								B= (int*) malloc(m2*n2*sizeof(int));

								for(i=0; i<m2; i++)
								{
																for(j=0; j<n2; j++)
																{
																								// fscanf(f, "%d",&A[i][j]);
																								fscanf(f, "%d",&*(B+i*n2+j));
																}
								}
								C1= (int*) malloc(m1*n2*sizeof(int));
								C2= (int*) malloc(m1*n2*sizeof(int));
								fclose(f);
}

void writeFile(double t1,double t2){
								FILE *f;
								int i;
								int j;
								f =fopen("output.txt","w");
								fprintf(f, "----- A) CREATE A THREAD FOR EACH ELEMENT ----- \n\n");
								for ( i = 0; i < m1; i++) {
																for ( j = 0; j < n2; j++)
																								fprintf(f, "%d ", *(C1+i*n2+j));
																fprintf(f,"\n");
								}
								fprintf(f, "\nTIME TAKEN FOR METHOD A : %lf\n\n",t1 );
								fprintf(f, "----- B) CREATE A THREAD FOR EACH ROW ----- \n\n");
								for ( i = 0; i < m1; i++) {
																for (int j = 0; j < n2; j++)
																								fprintf(f, "%d ", *(C2+i*n2+j));
																fprintf(f,"\n");
								}
								fprintf(f, "\nTIME TAKEN FOR METHOD B : %lf\n",t2 );

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
								for ( i = 0; i <n1; i++) {
																// sum += A[r][i]*B[i][c];
																int temp = A[r*n1+i]   * B[i*n2+c];
																// int temp = *(A+r*n1+i)  * *(B+i*n1+c);
																sum+=temp;
								}
								printf("cell= %d\n",sum );
								cell_struct->result = sum;
								// C[r][c] =sum;
								sum=0;
								pthread_exit(0);
}

void* multiply_row(void* item)
{
								struct row *row_struct =
																(struct row*) item;
								int r = row_struct->row_num;
								int m =row_struct->m;
								int n = row_struct->n;
								int sum = 0;
								int i;
								int j;
								for ( i = 0; i < n; i++)
																for ( j = 0; j < m; j++)
																								*(C2+r*n+i) += *(A+r*m+j) * *(B+j*n+i);

// C2[r][i] += A[r][j] * B[j][i];
								// C[r][c] =sum;
								pthread_exit(0);
}


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
void rowThreading()
{
								printf("----- B) CREATE A THREAD FOR EACH ROW ----- \n" );
								int i, j;

								int thread_num=0;
								int k;
								int l;
								pthread_t threads[m1];
								struct row rows[m1];
								for (i = 0; i < m1; i++) {
																rows[i].row_num=i;
																rows[i].n=n2;
																rows[i].m=n1;
																pthread_create(&threads[i], NULL, multiply_row, &rows[i]);
								}

								int count=0;
								for ( k = 0; k < m1; k++) {

																pthread_join(threads[k], NULL);

								}

}

int main()
{

			clock_t t;


			readMatrix();
			t = clock();
			cellThreading();

			t = clock() - t;
			double time_taken1 = ((double)t)/CLOCKS_PER_SEC; // calculate the elapsed time
			t = clock();

			rowThreading();
			t = clock() - t;
			double time_taken2 = ((double)t)/CLOCKS_PER_SEC;  // calculate the elapsed time

			writeFile(time_taken1,time_taken2);
			return 0;
}
