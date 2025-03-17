#include <stdio.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Choose the rightmost element as pivot
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


int quickselect(int arr[], int low, int high, int k) {
    if (k >= 0 && k <= high - low) {
        int pivot = partition(arr, low, high);
        
        if (pivot - low == k)
            return arr[pivot];
            
        if (pivot - low > k)
            return quickselect(arr, low, pivot - 1, k);
            
        return quickselect(arr, pivot + 1, high, k - pivot + low - 1);
    }
    
    return -1;
}

// Function to find the ith order statistic
int ithOrderStatistic(int arr[], int n, int i) {
    if (i <= 0 || i > n) {
        printf("Invalid order statistic requested\n");
        return -1;
    }
    
    // Convert to 0-based index for quickselect
    return quickselect(arr, 0, n - 1, i - 1);
}

int main() {
    int arr[] = {12, 3, 5, 7, 4, 19, 26};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("Array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    
    for (int i = 1; i <= n; i++) {
        printf("The %d-th smallest element is: %d\n", 
               i, ithOrderStatistic(arr, n, i));
    }
    
    return 0;
}