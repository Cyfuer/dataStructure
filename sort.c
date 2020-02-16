#include <stdio.h>

void printArr( char *str, int arr[], int len);
void bubble(int arr[], int len);// 冒泡排序
void selection(int arr[], int len);// 选择排序
void insertion(int arr[], int len);// 插入排序

int main(int argc, char const *argv[])
{

	int arr[] = {1,3,4,7,3,1,9,20};
	int len = (int)sizeof(arr) / sizeof(*arr);
	bubble(arr, len);
	selection(arr, len);
	insertion(arr, len);
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
	for (int i = 0; i < len; ++i) {
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