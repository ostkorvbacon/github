#include "algorithm.h"
#include <stdio.h>

//
// Private
//

int temp,i,j,k;

//
// Public
//
void bubble_sort(int *a, int n) //Bubble sort algorithm.
{
	k=0;
	while (k==0)
	{
		k=1;
		for (i=0;i<n-1;i++)
		{
			if (a[i]>a[i+1])
			{
				temp=a[i];
				a[i]=a[i+1];
				a[i+1]=temp;
				k=0;
			}
		}
	}
}

void insertion_sort(int *a, int n) //Insertion sort algorithm.
{
	for (i=1;i<n;i++)
	{
		j=i;
		while (j>0 && a[j-1]>a[j])
		{
			temp=a[j];
			a[j]=a[j-1];
			a[j-1]=temp;
			j--;
		}
	}
}

//Funktion that calls for quicksort algorithm.
void quick_sort(int *a, int n) //Nesseled funktions due to real algorithm funktion needing diferent parameters.
{
	QuickSort(a,0,n-1);
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
  int l, p, temp, pivot;
  pivot = arr[high];
  l=(low-1);
  for(p=low; p<=high-1; p++)
  {
    if(arr[p]<=pivot)
    {
      l++;
      temp = arr[p];
      arr[p] = arr[l];
      arr[l] = temp;
    }
  }
  temp = arr[high];
  arr[high] = arr[l+1];
  arr[l+1] = temp;

  return l;
}

bool linear_search(const int *a, int n, int v)
{
	for (i=0;i<n;i++){

		if (a[i]==v) return true;

		}

	return false;

}

bool binary_search(const int *a, int n, int v)
{
	int low=0;
	int i=0;
	int high=n-1;
	while (low<=high){
		i++;

		k=(low+high)/2;
		if (a[k]<v) low=k+1;

		else if (a[k]>v) high=k-1;

		else {


			return true;}
	}

	return false;
}
