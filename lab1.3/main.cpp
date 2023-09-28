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

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
 
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
 
    int i = (low - 1);
 
    for (int j = low; j <= high - 1; j++) {
 
        if (arr[j] < pivot) {
 
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
 
void alg_3(int arr[], int low, int high)
{
    if (low < high) {
 
        int pi = partition(arr, low, high);
 
        alg_3(arr, low, pi - 1);
        alg_3(arr, pi + 1, high);
    }
}


int main() {

	int userChoice = 0;
	do{
		printf(">>"); scanf("%d", &userChoice);
		switch(userChoice) {
			case 1: alg_1(); break;
			case 2:	alg_2(); break;
			case 3: {
						int sizeArr; 
						printf("sizeArr>>"); scanf("%d", &sizeArr);
						int arr[sizeArr];
						fill_array(arr, sizeArr);	
						print_array(arr, sizeArr);
						alg_3(arr, 0, sizeArr-1); 
						print_array(arr, sizeArr);
					}
					break;
			case 4: return 0; break;
			default: printf("incorrect choice!\n");
		}
	}while(true);

}
