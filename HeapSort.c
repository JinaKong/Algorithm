#include <stdio.h>

// �迭 ���� ��ȯ �Լ�
void exchange(int* a, int* b) {

	int temp = *a;
	*a = *b;
	*b = temp;
}

// HEAPIFY �Լ�
void HEAPIFY(int arr[], int i, int n) {

	int largest;
	int left_child = 2 * i  ; //���� �ڽĳ��
	int right_child = 2 * i + 1; //������ �ڽĳ��

	// ���� �ڽĳ�� ���� ��Ʈ���� ū ���
	if (left_child <= n && arr[left_child] > arr[i])
		largest = left_child;
	else largest = i;

	// ������ �ڽĳ�� ���� ��Ʈ���� ū ���
	if (right_child <= n && arr[right_child] > arr[largest])
		largest = right_child;

	// ���� ��尡 ��Ʈ�� �ƴϸ� ��ȯ 
	if (largest != i) {
		exchange(&arr[i], &arr[largest]);
		
		//�ٽ� HEAPIFY() ȣ��
		HEAPIFY(arr, largest, n);
	}
	else return;
}

// max heap ���� �Լ�
void BUILD_HEAP(int arr[], int n) {
	for (int i = n / 2; i > 0; i--) {
		HEAPIFY(arr, i, n);
	}
}


// heap sort �Լ�
void HEAPSORT(int arr[], int n) {

	//max heap ����
	BUILD_HEAP(arr, n);

	//����
	for (int i = n; i > 1; i--) {
		exchange(&arr[1], &arr[i]); 

		//heap size�� 1 �ٿ��� HEAPIFY() ȣ��
		HEAPIFY(arr, 1, i - 1);
	}
}

//�迭 ��� �Լ�
void print_array(int arr[], int n) {
	for (int i = 1; i <= n; i++) {
		printf("%d ", arr[i]);			// A[1]���� �����ϴ� �迭��, A[0]�� ������� ����
	}
	printf("\n");
}

int main() {

	int A[] = { 0, 4, 1, 3, 2, 16, 9, 10, 14, 8, 7}; //������ �迭(�ε��� 1���� ����)
	int B[] = { 0, 3, 15, 3, 5, 2, 10, 11, 1, 7};

	int num_a = sizeof(A) / sizeof(A[1]) - 1; // �迭 ũ��
	int num_b = sizeof(B) / sizeof(B[1]) - 1; // �迭 ũ��


	// �迭 A ���� 
	printf("���� �� �迭 A: ");
	print_array(A, num_a);

	HEAPSORT(A, num_a);

	printf("���� �� �迭 A: ");
	print_array(A, num_b);

	// �迭 B ���� 
	printf("\n���� �� �迭 B: ");
	print_array(B, num_b);

	HEAPSORT(B, num_b);

	printf("���� �� �迭 B: ");
	print_array(B, num_b);

	return 0;
}