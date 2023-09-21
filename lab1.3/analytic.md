# Algorithm 1
```cpp
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
```
# Algorithm 2
```cpp
void alg_2() {
	int amountElements;
	printf("amountElements>>"); scanf("%d", &amountElements);

	int arr[amountElements];
	fill_array(arr, amountElements);	
	print_array(arr, amountElements);

	for (int i = 0; i < amountElements; i++) {
		int tmp = 0;
		for (int j = 0; j < amountElements-i-1; j++) {
			if (arr[j] >= 0) {
				tmp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tmp;
			}

		}
	}
	print_array(arr, amountElements);
}
```

# Analytic
| **Alg number** | Baddest    | Average    | Best       |
| ---            | ---        | ---        | ---        |
| 1              | O(n^2)     | Θ(n^2)     | Ω(n^2)     |
| 2              | O(nlog(n)) | Θ(nlog(n)) | Ω(nlog(n)) |
