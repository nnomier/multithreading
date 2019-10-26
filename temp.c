#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int arr[500];

int readArray()
{
        FILE *f;
        int i;
        int n;
        f =fopen("merge.txt","r");
        printf("before reading ..\n");
        fscanf(f, "%d",&n);
        printf("n is %d\n",n );
        for(i=0; i<n; i++)
        {
                fscanf(f, "%d",&arr[i]);
        }
        fclose(f);

printf("after reading..\n");
for (i=0; i < n; i++)
        printf("%d ", arr[i]);

        return n;
}



void merge(int arr[],int l,int mid,int r)
{
        int i,j,k;
        int n1= mid-l+1;
        int n2=r-mid;

        int L[n1],R[n2];

        for(i=0; i<n1; i++)
                L[i]=arr[l+i];

        for(j=0;j<n2; j++)
                R[j]=arr[mid+l+j];

        i=0;
        j=0;
        k=l;

        while(j<n2 && i<n1)
        {
                if(L[i]<=R[j])
                {
                        arr[k]=L[i];
                        i++;
                }
                else
                {
                        arr[k]=R[j];
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

void mergeSort(int arr[],int l, int r)
{                printf("vefore merge..");

        if(l<r)
        {
                int mid = l + (r-l)/2;

                mergeSort(arr,l,mid);
                mergeSort(arr,mid+1,r);
                merge(arr,l,mid,r);
        }
}

int main(int argc, char const *argv[]) {
      // int n=  readArray();
      int n=5;
      arr = malloc(sizeof(int)*n);
      arr[0]=1;
      arr[1]=10;
      arr[2]=20;
      arr[3]=5;
      arr[4]=2;
      int i;
        mergeSort(arr,0,n-1);
        // printf("after sorting ..\n");
        // int i;
        for (i=0; i < n; i++)
                printf("%d ", arr[i]);
        printf("\n");
        // // free(arr);

        return 0;
}
