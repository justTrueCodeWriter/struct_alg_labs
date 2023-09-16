#include <stdio.h>

int degree(int number, int degree) {

	int result = 1;

	for (int i = 0; i < degree; i++) {
		result *= number;
	}

	return result;

}

void fill_array(int *arr, int amountElements) {
	
	int val = 0;
	for (int i = 0; i < amountElements; i++) {
		printf("arr[%d]>>", i); scanf("%d", &val);
		arr[i] = val;
	}
	

}

void print_array(int *arr, int amountElements) {

	for (int i = 0; i < amountElements; i++) 
		printf("%d ", arr[i]);
	printf("\n");

}

void alg_1() {

	int amountElements;
	printf("amountElements>>"); scanf("%d", &amountElements);

	int arr[amountElements];
	fill_array(arr, amountElements);	
	print_array(arr, amountElements);

	for (int i = 0; i < amountElements; i++) {
		int tmp = 0;
		for (int j = 0; j < amountElements-1; j++) {
			if (arr[j] >= 0) {
				tmp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tmp;
			}

		}
	}
	print_array(arr, amountElements);

}

int main() {

	alg_1();

}
