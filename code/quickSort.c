// 将数组分区并返回分区点的索引
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  // 选择最后一个元素作为基准点
    int i = (low - 1);      // 小于基准的子数组的最后一个元素的索引

    for (int j = low; j <= high - 1; j = j + 1) {
        // 如果当前元素小于或等于基准
        if (arr[j] <= pivot) {
            i = i + 1;  // 将较小元素放到小于基准的子数组的末尾
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
        }
    }
	int temp = arr[i + 1];
	arr[i + 1] = arr[high];
	arr[high] = temp;
    return (i + 1);                 // 返回分区点的索引
}

// 快速排序算法
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // 将数组分区并获取分区点的索引
        int pi = partition(arr, low, high);

        // 递归地对分区点左侧和右侧的子数组进行排序
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
        return;
    }
    return;
}

int main() {
    int N;
    scanf("%d", &N);

    int arr[10000];
    for (int i = 0; i < N; i = i + 1) {
        scanf("%d", &arr[i]);
    }

    // 对整数数组进行快速排序
    quickSort(arr, 0, N - 1);

    for (int i = 0; i < N; i = i + 1) {
        printf("%d\n", arr[i]);
    }

    return 0;
}
