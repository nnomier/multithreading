#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
    int r = 3, c = 4;
    int *arr;
    arr = (int *)malloc(r * c * sizeof(int));

    int i, j, count = 0;
    for (i = 0; i <  r; i++)
      for (j = 0; j < c; j++)
      scanf("%d\n",& *(arr + i*c + j));


    for (i = 0; i <  r; i++)
      for (j = 0; j < c; j++)
         printf("%d ", *(arr + i*c + j));

   /* Code for further processing and free the
      dynamically allocated memory */

   return 0;
}
