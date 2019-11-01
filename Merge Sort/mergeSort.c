#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#define MAX 4294967295
int *arr;


struct params {
  int l;
  int r;
};

int readArray()
{
  FILE *f;
  int i;
  int n;
  arr = malloc(sizeof(int)*n);

  f =fopen("input.txt","r");
  fscanf(f, "%d",&n);
  for(i=0; i<n; i++)
  {
          fscanf(f, "%d",&arr[i]);
  }
  fclose(f);


  return n;
}

void remainingELements(int n1,int n2,int L[],int R[],int i , int j , int k){
  while(i<n1)
  {
    arr[k] =L[i];
    i++;
    k++;
  }

  while(j<n2)
  {
    arr[k]=R[j];
    j++;
    k++;
  }
}

void merge(int l,int mid,int r)
{
int i,j,k;
int n1= mid-l+1;
int n2=r-mid;

int L[n1],R[n2];

for(i=0; i<n1; i++)
  L[i]=arr[l+i];

for(j=0; j<n2; j++)
  R[j]=arr[mid+1+j];

i=0;
j=0;
k=l;
// L[n1]=MAX;
// R[n2]=MAX;

while(i<n1 && j<n2)
{
  if(L[i]<=R[j])
  {
          arr[k]=L[i];
          i++;
  }
  else
  {
          arr[k]=R[j];
          j++;
  }
  k++;
}

while(i<n1)
{
        arr[k] =L[i];
        i++;
        k++;
}

while(j<n2)
{
        arr[k]=R[j];
        j++;
        k++;
}
}

void writeOriginalArray(int n)
{

  FILE *f;
  int i;

  f =fopen("input.txt","w");
  fscanf(f, "%d",&n);
  fprintf(f, "%d\n",n );
  for(i=n; i>0; i--)
  {
      fprintf(f, "%d ",i+10 );
  }
  fclose(f);

}

void* mergeSort(void* item)
{
  struct params *args = (struct params*) item;
  int l=args->l;
  int r=args->r;

  if(l<r)
  {
    int mid = l + (r-l)/2;
    pthread_t thread1,thread2;
    struct params params1,params2;
    params1.l=l;
    params1.r=mid;
    params2.l=mid+1;
    params2.r=r;

    pthread_create(&thread1,NULL,mergeSort, &params1);
    pthread_create(&thread2,NULL,mergeSort, &params2);

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);


    merge(l,mid,r);
    pthread_exit(0);

  }
  pthread_exit(0);
   // return NULL;
}

void printArray(int n){
int i;
for (i=0; i < n; i++)
    printf("%d ", arr[i]);
printf("\n");
}

int main() {
  // writeOriginalArray(100);
  int n=  readArray();
  struct params parameters;
  parameters.l = 0;
  parameters.r = n-1;
  printf("----ARRAY BEFORE SORTING----\n");
  printArray(n);

  pthread_t initialThread;
  pthread_create(&initialThread,NULL,mergeSort,&parameters);
  pthread_join(initialThread,NULL);

  printf("\n----ARRAY AFTER SORTING----\n");
  printArray(n);

  free(arr);

  return 0;
}
