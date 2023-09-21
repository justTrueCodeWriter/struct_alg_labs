#include <stdio.h>

int degree(int number, int degree) {

	int result = 1;

	for (int i = 0; i < degree; i++) {
		result *= number;
	}

	return result;

}

void fill_array(int *arr, int sizeArr) {
	
	int val = 0;
	for (int i = 0; i < sizeArr; i++) {
		printf("arr[%d]>>", i); scanf("%d", &val);
		arr[i] = val;
	}
	

}

void print_array(int *arr, int sizeArr) {

	for (int i = 0; i < sizeArr; i++) 
		printf("%d ", arr[i]);
	printf("\n");

}

void alg_1() {

	int sizeArr;
	printf("sizeArr>>"); scanf("%d", &sizeArr);

	int arr[sizeArr];
	fill_array(arr, sizeArr);	
	print_array(arr, sizeArr);

	for (int i = 0; i < sizeArr; i++) {
		int tmp = 0;
		for (int j = 0; j < sizeArr-1; j++) {
			if (arr[j] >= 0) {
				tmp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tmp;
			}

		}
	}
	print_array(arr, sizeArr);

}

void alg_2() {
	int sizeArr;
	printf("sizeArr>>"); scanf("%d", &sizeArr);

	int arr[sizeArr];
	fill_array(arr, sizeArr);	
	print_array(arr, sizeArr);

	for (int i = 0; i < sizeArr; i++) {
		int tmp = 0;
		for (int j = 0; j < sizeArr-i-1; j++) {
			if (arr[j] >= 0) {
				tmp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tmp;
			}

		}
	}
	print_array(arr, sizeArr);
}

int get_positive_amount(int *arr, int sizeArr) {
	int sizePositive = 0;

	for (int i = 0; i < sizeArr; i++) {
		if (arr[i] >= 0) {
			sizePositive++;	
		}
	}

	return sizePositive;
}

void get_positive(int *arr, int *positiveElements, int *positivePositions, int sizeArr, int sizePositive){

	int k = 0;
	for (int i = 0; i < sizeArr; i++) {
		if (arr[i] >= 0){
			positiveElements[k] = arr[i];
			positivePositions[k] = i;
			k++;
		}
	}
}

/*
void alg_3() {
	int sizeArr;
	printf("sizeArr>>"); scanf("%d", &sizeArr);

	int arr[sizeArr];
	fill_array(arr, sizeArr);	
	print_array(arr, sizeArr);

	int sizePositive = get_positive_amount(arr, sizeArr);	
	int positiveElements[sizePositive];
	int positivePositions[sizeArr];

	int k = 0;
	for (int i = 0; i < sizeArr; i++) {
		int tmp = 0;
		if (arr[i] >= 0) {
			positivePositions[k] = i;
			k++;
		}

		if (arr[i] < 0 && i != 0) {
			tmp = arr[i];
			arr[i] = arr[positivePositions[i-k]];
			arr[positivePositions[i-k]] = tmp;
			positivePositions[i] = i;
		}
		print_array(arr, sizeArr);
	}

}
*/

// -456 298 4324 -8456 37298 -80024 
// 

int main() {

	int userChoice = 0;
	do{
		printf(">>"); scanf("%d", &userChoice);
		switch(userChoice) {
			case 1: alg_1(); break;
			case 2:	alg_2(); break;
			case 3: return 0; break;
			default: printf("incorrect choice!\n");
		}
	}while(true);

}
