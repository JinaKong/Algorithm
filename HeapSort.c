#include <stdio.h>

// 배열 원소 교환 함수
void exchange(int* a, int* b) {

	int temp = *a;
	*a = *b;
	*b = temp;
}

// HEAPIFY 함수
void HEAPIFY(int arr[], int i, int n) {

	int largest;
	int left_child = 2 * i  ; //왼쪽 자식노드
	int right_child = 2 * i + 1; //오른쪽 자식노드

	// 왼쪽 자식노드 값이 루트보다 큰 경우
	if (left_child <= n && arr[left_child] > arr[i])
		largest = left_child;
	else largest = i;

	// 오른쪽 자식노드 값이 루트보다 큰 경우
	if (right_child <= n && arr[right_child] > arr[largest])
		largest = right_child;

	// 현재 노드가 루트가 아니면 교환 
	if (largest != i) {
		exchange(&arr[i], &arr[largest]);
		
		//다시 HEAPIFY() 호출
		HEAPIFY(arr, largest, n);
	}
	else return;
}

// max heap 생성 함수
void BUILD_HEAP(int arr[], int n) {
	for (int i = n / 2; i > 0; i--) {
		HEAPIFY(arr, i, n);
	}
}


// heap sort 함수
void HEAPSORT(int arr[], int n) {

	//max heap 생성
	BUILD_HEAP(arr, n);

	//정렬
	for (int i = n; i > 1; i--) {
		exchange(&arr[1], &arr[i]); 

		//heap size를 1 줄여서 HEAPIFY() 호출
		HEAPIFY(arr, 1, i - 1);
	}
}

//배열 출력 함수
void print_array(int arr[], int n) {
	for (int i = 1; i <= n; i++) {
		printf("%d ", arr[i]);			// A[1]부터 시작하는 배열로, A[0]은 출력하지 않음
	}
	printf("\n");
}

int main() {

	int A[] = { 0, 4, 1, 3, 2, 16, 9, 10, 14, 8, 7}; //임의의 배열(인덱스 1부터 시작)
	int B[] = { 0, 3, 15, 3, 5, 2, 10, 11, 1, 7};

	int num_a = sizeof(A) / sizeof(A[1]) - 1; // 배열 크기
	int num_b = sizeof(B) / sizeof(B[1]) - 1; // 배열 크기


	// 배열 A 정렬 
	printf("정렬 전 배열 A: ");
	print_array(A, num_a);

	HEAPSORT(A, num_a);

	printf("정렬 후 배열 A: ");
	print_array(A, num_b);

	// 배열 B 정렬 
	printf("\n정렬 전 배열 B: ");
	print_array(B, num_b);

	HEAPSORT(B, num_b);

	printf("정렬 후 배열 B: ");
	print_array(B, num_b);

	return 0;
}