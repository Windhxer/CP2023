#include <stdio.h>
#include <string.h>
int main() {

    // 获取输入
    char line[500];
	char *courses[40];
	int score[40];
	char *pre[40];
	char grade[40];
	int i = 0, j = 0;
	int flag = 0;
    while (1) {
		char c;
		scanf("%c", &c);
		if (c == '\n')
		{
			if (flag == 1)
			{
				break;
			}
			else
			{
				flag = 1;
				char line1[10];
				char line2[1000];
				sscanf(line, "%[^|]|%d|%[^|]|%c", line1, &score[j], line2, &grade[j]);
				courses[j] = strdup(line1);
				pre[j] = strdup(line2);
				j++;
				i = 0;
			}
		}
		else
		{
			flag = 0;
			line[i++] = c;
		}
    }
	for (int i = 0; i < j; i++)
	{
		printf("(%s, %d, %s, %c)\n", courses[i], score[i], pre[i], grade[i]);
	}

	// for (int j = 0; j < iii; j++)
	// {
	// 	printf("(%s, %d, %s, %c)\n", courses[j], score[j], pre[j], grade[j]);
	// }

    // 在这里可以使用获取到的输入进行后续处理

    return 0;
}
