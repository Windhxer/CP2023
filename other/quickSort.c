// 这是一个在windows下已经通过了所有测试点的快速排序代码（用gcc编译）
#include <stdio.h>

// 交换两个元素的值
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 将数组分区并返回分区点的索引
int partition(int* arr, int low, int high) {
    int pivot = arr[high];  // 选择最后一个元素作为基准点
    int i = (low - 1);      // 小于基准的子数组的最后一个元素的索引

    for (int j = low; j <= high - 1; j++) {
        // 如果当前元素小于或等于基准
        if (arr[j] <= pivot) {
            i++;  // 将较小元素放到小于基准的子数组的末尾
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);  // 将基准放到正确的位置
    return (i + 1);                 // 返回分区点的索引
}

// 快速排序算法
void quickSort(int* arr, int low, int high) {
    if (low < high) {
        // 将数组分区并获取分区点的索引
        int pi = partition(arr, low, high);

        // 递归地对分区点左侧和右侧的子数组进行排序
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int N;
    scanf("%d", &N);

    int arr[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }


    // 对整数数组进行快速排序
    quickSort(arr, 0, N - 1);

    for (int i = 0; i < N; i++) {
        printf("%d\n", arr[i]);
    }

    return 0;
}
