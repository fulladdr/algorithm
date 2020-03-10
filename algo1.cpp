#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <time.h>
using namespace std;
FILE* fp, *sp;
int r, c;
int arr[10001][10001];
int tmp[1000001];
double beforetime, aftertime;

int sol_n6(void) {
	beforetime = clock();//�ð�����
	int maxSum1 = -987654321;//�ִ밪�� ������ �� �ִ� ���� ���� ������ ����
	for (int i = 0; i < c; i++) {//���ư��鼭 col ���ۺκа� ���κ��� ������
		for (int j = i; j < c; j++) {
			for (int w = 0; w < r; w++) {//���ư��鼭 row ���ۺκа� ���κ��� ������
				for (int k = w; k < r; k++) {
					int result = 0;//row�� col�������� ���� ����
					for (int a = i; a <= j; a++) {
						for (int b = w; b <= k; b++) {
							result += arr[a][b];
						}
					}
					maxSum1 = max(maxSum1, result);//result�� max�϶��� ã��
				}
			}
		}
	}
	return maxSum1;//max return
}

int sol_n4(void) {
	beforetime = clock();//�ð�����
	int maxSum2 = -987654321;
	for (int i = 0; i < r; i++) {
		memset(tmp, 0, sizeof(tmp));//ū ���������� tmp�迭�� ���� column �� ����
		for (int j = i; j < r; j++) {//j���������� ���������� tmp�� ����
			for (int q = 0; q < c; q++) {//column��ŭ ���� tmp�� ����
				tmp[q] += arr[q][j];
			}
			for (int a = 0; a < r; a++) {//���� column tmp������ �ִ����� ����
				int thisSum = 0;
				for (int b = a; b < c; b++) {
					thisSum += tmp[b];
					if (thisSum > maxSum2)maxSum2 = thisSum;
				}
			}
		}
	}
	return maxSum2;
}
//n^3�˰������� n^4�˰����򿡼� inner loop�� �����ϰ� ǥ���� ����
int sol_n3(void) {
	beforetime = clock();//�ð�����
	int maxSum3 = -987654321;
	for (int i = 0; i < r; i++) {
		memset(tmp, 0, sizeof(tmp));
		for (int j = i; j < r; j++) {
			for (int q = 0; q < c; q++) {
				tmp[q] += arr[q][j];
			}//��������� n^3 �˰������ ������
			int thisSum = 0;
			for (int a = 0; a < c; a++) {
				thisSum += tmp[a];
				if (thisSum < 0) thisSum = 0;//0���� ������ �ƿ� �� �������� ó�� �����ִ� ������ 0���� �ʱ�ȭ��
				else if (thisSum > maxSum3) {
					maxSum3 = thisSum;
				}
			}
		}
	}//�׷��� n^3 �˰������� input�� ��� �����϶� ����ε� ���� ���� ����
	int flag = 0;
	for (int i = 0; i < c; i++) {
		for (int j = 0; j < r; j++) {
			if (arr[i][j] > 0) flag = 1;//���� ��� input�� �����̸� flag���� ������ �ʰ� �״�� 0��
		}
	}
	if (flag == 0) {
		int maxN = -987654321;
		for (int i = 0; i < c; i++) {
			for (int j = 0; j < r; j++) {
				maxN = max(maxN, arr[i][j]);
			}
		}
		return maxN;
	}
	return maxSum3;
}

int main(int argc, char* argv[]) {
	fp = fopen(argv[1], "r");//input file �Է¹���
    fscanf(fp, "%d %d", &c, &r);//row, column �� 
	for (int i = 0; i < c; i++) {
		for (int j = 0; j < r; j++) {
			fscanf(fp, "%d", &arr[i][j]);//matrix ���·� ����
		}
	}
	int ans;
	if (argv[2][0] == '1') ans = sol_n6();//1�� �ԷµǸ� n^6�˰�����
	if (argv[2][0] == '2') ans = sol_n4();//2�� �ԷµǸ� n^4�˰�����
	if (argv[2][0] == '3') ans = sol_n3();//3�� �ԷµǸ� n^3�˰�����
	aftertime = clock();//�Լ�ȣ�� �� �ð�����
	char output[30] = "result_";
	strcat(output,argv[1]);
	sp = fopen(output, "w");//output�� ���
	fprintf(sp, "%s\n", argv[1]);
	fprintf(sp, "%c\n", argv[2][0]);
	fprintf(sp, "%d\n", c);
	fprintf(sp, "%d\n", r);
	fprintf(sp, "%d\n", ans);
	fprintf(sp, "%lf\n", 1000 * (aftertime - beforetime) / (CLOCKS_PER_SEC));
	fclose(sp);
	fclose(fp);//close of file
	return 0;
}
