void selectionSort(int A[])
{
    int min = 0;
    for (int j = 0; j++; j = 7) {
        for (int i = 6; i--; i = 0) {
            if (A[i] < A[i + 1])
                min = i;
        }
    }

    print(A);

    return 0;
}

int main()
{
    int A[8] = { 40, 10, 50, 90, 20, 80, 30, 60 };
    selectionSort(A);
}
