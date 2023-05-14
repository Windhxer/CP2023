// 这是矩阵乘法的代码，还在debug中，能通过验收细则中给出的两个例子，
// 未能通过测试程序的测试点，卡在了size=0和size=1，感觉是没有考虑矩阵行数=0或者列数=0的情况
#include <stdio.h>
#include <stdlib.h>

void matrix_multiplication(int** A, int** B, int rows_A, int cols_A, int rows_B, int cols_B) {
    if (rows_A == 0 || cols_A == 0 || rows_B == 0 || cols_B == 0) {
        // printf("Incompatible Dimensions\n\n");
        return;
    }
    if (cols_A != rows_B) {
        printf("Incompatible Dimensions\n\n");
        return;
    }

    int** result = (int**)malloc(rows_A * sizeof(int*));
    for (int i = 0; i < rows_A; i++) {
        result[i] = (int*)malloc(cols_B * sizeof(int));
    }

    for (int i = 0; i < rows_A; i++) {
        for (int j = 0; j < cols_B; j++) {
            result[i][j] = 0;
            for (int k = 0; k < cols_A; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    // 输出乘积结果
    for (int i = 0; i < rows_A; i++) {
        for (int j = 0; j < cols_B; j++) {
            printf("%10d ", result[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    // 释放内存
    for (int i = 0; i < rows_A; i++) {
        free(result[i]);
    }
    free(result);
}

int main() {
    int rows_A, cols_A, rows_B, cols_B;

    // 读取矩阵 A 的维度
    scanf("%d %d", &rows_A, &cols_A);

    // 动态分配矩阵 A 的内存
    int** A = (int**)malloc(rows_A * sizeof(int*));
    for (int i = 0; i < rows_A; i++) {
        A[i] = (int*)malloc(cols_A * sizeof(int));
    }

    // 读取矩阵 A 的元素
    for (int i = 0; i < rows_A; i++) {
        for (int j = 0; j < cols_A; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    // 读取矩阵 B 的维度
    scanf("%d %d", &rows_B, &cols_B);

    // 动态分配矩阵 B 的内存
    int** B = (int**)malloc(rows_B * sizeof(int*));
    for (int i = 0; i < rows_B; i++) {
        B[i] = (int*)malloc(cols_B * sizeof(int));
    }

    // 读取矩阵 B 的元素
    for (int i = 0; i < rows_B; i++) {
        for (int j = 0; j < cols_B; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    // 执行矩阵乘法操作
    matrix_multiplication(A, B, rows_A, cols_A, rows_B, cols_B);

    // 释放内存
    for (int i = 0; i < rows_A; i++) {
        free(A[i]);
    }
    free(A);

    for (int i = 0; i < rows_B; i++) {
        free(B[i]);
    }
    free(B);

    return 0;
}
