#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>


#define NUMBEL 16

void QuickSort(int *a,int a2,int b);
void quick_sort(int *a, int n);
void createBest(int *arr, int start_index, int count, int start_value);
int partition(int *arr, int low, int high);

int temp,i,j,k;

int main()
{
  j = 0;
  int n = NUMBEL;
  int arr[n];
  int arr2[n];
  for(i=0;i<NUMBEL;i++)
  {
    arr2[i] = 1;
    printf("%2d ", arr2[i]);
  }
  arr2[4] = 3;
  arr2[7] = 2;
  arr2[1] = 2;

  createBest(arr, 0, n, 1);
  printf("\n");
  for(i=0;i<NUMBEL;i++)
  {
    printf("%2d ", arr[i]);
  }
  printf("\n");
  quick_sort(arr2, n);
  for(i=0;i<NUMBEL;i++)
  {
    printf("%2d ", arr2[i]);
  }


  return 0;
}

void createBest(int *arr, int start_index, int count, int start_value) {
   if (count == 0)
       return;

   if (count == 1)
   {
       arr[start_index] = start_value;

   }

   int partition1_count = count / 2;
   int partition2_count = count - partition1_count - 1; // need to save a spot for the pivot so -1...
   int pivot_value_index = start_index + partition1_count;
   int pivot_value = start_value + partition1_count;

   createBest(arr, start_index, partition1_count, start_value);
   createBest(arr, pivot_value_index, partition2_count, pivot_value+1);
   arr[start_index + count - 1] = pivot_value;
}

void quick_sort(int *arr, int n) //Nesseled funktions due to real algorithm funktion needing diferent parameters.
{
	QuickSort(arr, 0, n-1);

}

void QuickSort(int *arr,int low,int high)
{
  int piv;
  if(low < high)
  {
    piv = partition(arr, low, high);
    QuickSort(arr, low, piv - 1);
    QuickSort(arr, piv + 1, high);
  }
}
int partition(int *arr, int low, int high)
{
  int i, j, temp, pivot;
  pivot = arr[high];
  i=(low-1);
  for(j=low; j<=high-1; j++)
  {
    if(arr[j]<=pivot)
    {
      i++;
      temp = arr[j];
      arr[j] = arr[i];
      arr[i] = temp;
    }
  }
  temp = arr[high];
  arr[high] = arr[i+1];
  arr[i+1] = temp;

  return i;
}
