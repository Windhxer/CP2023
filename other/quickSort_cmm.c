// 参考了一些文档，全部实现C语言的特性似乎不太现实，于是我们得修改或者删减一些语言特性
// cmm是C minux minux的意思

// #include不易于实现，于是要求使用的函数均需要用户自行定义
void printf(char* content, ...);

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
