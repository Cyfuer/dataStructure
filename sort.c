#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printArr( char *str, int arr[], int len);
void bubble(int arr[], int len);// 冒泡排序
void selection(int arr[], int len);// 选择排序
void insertion(int arr[], int len);// 插入排序
void shell(int arr[], int len);// 希尔排序

void merge(int arr[], int len);// 归并排序
void mergeSort(int arr[], int left, int right, int temp[]);
void mergeAdd(int arr[], int left, int right, int temp[]);

void quick(int arr[], int len);// 快速排序
void quickSort(int arr[], int left, int right);
int quickExchange(int arr[], int left, int right);

int main(int argc, char const *argv[])
{

	int arr[] = {1,3,4,7,3,1,9,20};
	int len = (int)sizeof(arr) / sizeof(*arr);
	// bubble(arr, len);
	// selection(arr, len);
	// insertion(arr, len);
	// merge(arr, len);
	quick(arr, len);
	return 0;
}

void printArr( char *str, int arr[], int len) {
	for (int i = 0; i < len; ++i)
	{
		printf("%4d ", arr[i]);
	}
	printf("\n");
}

void bubble(int arr[], int len) {
	for (int i = 0; i < len - 1; ++i) {
		for (int j = 0; j < len - 1 - i; ++j) {
			if (arr[j] > arr[j+1]) {
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
	printArr("冒泡排序", arr, len);
}

void selection(int arr[], int len) {
	int temp, minIndex;
	for (int i = 0; i < len; ++i) {
		minIndex = i;
		for (int j = i + 1; j < len; ++j) {
			if (arr[j] < arr[minIndex]) {
				minIndex = j;
			}
		}
		temp = arr[i];
		arr[i] = arr[minIndex];
		arr[minIndex] = temp;
	}
	printArr("选择排序", arr, len);
}

void insertion(int arr[], int len) {
	if (len > 1)
	{
		int preIndex, cur;
		for (int i = 1; i < len; ++i)
		{
			preIndex = i - 1;
			cur = arr[i];
			while(preIndex >= 0 && arr[preIndex] > cur) {
				arr[preIndex + 1] = arr[preIndex];
				preIndex--;
			}
			arr[preIndex + 1] = cur;
		}
	}
	printArr("插入排序", arr, len);
}

void shell(int arr[], int len) {
	for (int gap = len/2; gap > 0; gap = gap/2) {
		for (int i = gap; i < len; ++i) {
			int j = i;
			int cur = arr[i];
			while(j - gap >= 0 && cur < arr[j - gap]) {
				arr[j] = arr[j - gap];
				j = j - gap;
			}
			arr[j] = cur;
		}
	}
	printArr("希尔排序", arr, len);
}

void merge(int arr[], int len) {
	int *temp = (int*) malloc(len * sizeof(int));
	mergeSort(arr, 0, len - 1, temp);
	printArr("归并排序", arr, len);

}

void mergeSort(int arr[], int left, int right, int temp[]) {
	if (left < right) {
		int mid = left + (right - left) / 2;
		mergeSort(arr, left, mid, temp);
		mergeSort(arr, mid + 1, right, temp);
		mergeAdd(arr, left, right, temp);
	}
}

void mergeAdd(int arr[], int left, int right, int temp[]) {
	int mid = left + (right - left) / 2;
	int i = left, j = mid + 1;
	int k = left;
	while(i <= mid && j <= right) {
		if (arr[i] < arr[j]) {
			temp[k++] = arr[i++];
		} else {
			temp[k++] = arr[j++];
		}
	}
	while(i <= mid) {
		temp[k++] = arr[i++];
	}
	while(j<= right) {
		temp[k++] = arr[j++];
	}


	memcpy(arr + left, temp + left, sizeof(int) * (right - left + 1));
}

void quick(int arr[], int len) {
	quickSort(arr, 0, len - 1);
	printArr("快速排序", arr, len);
}

void quickSort(int arr[], int left, int right) {
	if (left < right) {
		int partition = quickExchange(arr, left, right);
		quickSort(arr, left, partition - 1);
		quickSort(arr, partition + 1, right);
	}
}
int quickExchange(int arr[], int left, int right) {
	int partition = left;
	int index = left + 1;
	int temp;
	for (int i = index; i <= right; ++i) {
		if (arr[i] < arr[partition]) {
			temp = arr[index];
			arr[index] = arr[i];
			arr[i] = temp;
			index++;
		}
	}
	temp = arr[index - 1];
	arr[index - 1] = arr[partition];
	arr[partition] = temp;
	return index - 1;
}