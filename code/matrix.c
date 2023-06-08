void matrix_multiplication(int A[], int B[], int rows_A, int cols_A, int rows_B, int cols_B) {
    if (cols_A != rows_B) {
        printf("Incompatible Dimensions\n");
        return;
    }
    int result[10000];
    int row = rows_A;
    int column = cols_B;

    for (int i = 0; i < row; i = i + 1) {
        for (int j = 0; j < column; j = j + 1) {
            result[i * column + j] = 0;
            for (int k = 0; k < cols_A; k = k + 1) {
                result[i * column + j] = result[i * column + j] + A[i * cols_A + k] * B[k * cols_B + j];
            }
        }
    }

    // 输出乘积结果
    for (int i = 0; i < row; i = i + 1) {
        for (int j = 0; j < column; j = j + 1) {
            printf("%10d", result[i * column + j]);
        }
        printf("\n");
    }
	return;
}

int main() {
    int rows_A, cols_A, rows_B, cols_B;
    
    int A[10000];
    int B[10000];

    // 读取矩阵 A 的维度
    scanf("%d %d", &rows_A, &cols_A);

    // 读取矩阵 A 的元素
    for (int i = 0; i < rows_A; i = i + 1) {
        for (int j = 0; j < cols_A; j = j + 1) {
            scanf("%d", &A[i * cols_A + j]);
        }
    }
    // 读取矩阵 B 的维度
    scanf("%d %d", &rows_B, &cols_B);

    // 读取矩阵 B 的元素
    for (int i = 0; i < rows_B; i = i + 1) {
        for (int j = 0; j < cols_B; j = j + 1) {
            scanf("%d", &B[i * cols_B + j]);
        }
    }

    // 执行矩阵乘法操作
    matrix_multiplication(A, B, rows_A, cols_A, rows_B, cols_B);

    return 0;
}
