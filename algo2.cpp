#include <stdio.h>
#include <algorithm>
#include <time.h>
#include <cmath>
#include <cstring>
#include <vector>
using namespace std;
double before, after;
void insertion_sort(vector<int>& arr, int s, int e) {
	int n = e - s + 1;
	int tmp, j;
	for (int i = s + 1; i <= e; i++) {
		tmp = arr[i];
		j = i;
		while (j > s&&tmp < arr[j - 1]) {
			arr[j] = arr[j - 1];
			j--;
		}
		arr[j] = tmp;
	}
}
int partition(vector<int> &arr, int s, int e, int piv) {
	swap(arr[piv], arr[e]);//pivot  위치로 이동
	int x = s;
	for (int i = s; i < e; i++) {
		if (arr[i] < arr[e]) {
			swap(arr[i], arr[x]);
			x++;
		}
	}
	swap(arr[x], arr[e]);//pivot 위치 바꿔줌
	return x;
}
void quick_sort(vector<int>& arr, int s, int e) {
	if (e - s > 0) {
		int pivot = partition(arr, s, e, e);
		quick_sort(arr, s, pivot - 1);
		quick_sort(arr, pivot+1, e);
	}
}
void merge(vector<int> &arr, int left, int mid, int right) {
	int len = arr.size();
	vector<int> sorted(len);
	int i, j, k, l;//i : left idx for left, j : right idx for right
	i = left;
	j = mid + 1;
	k = left;
	while (i <= mid && j <= right) {//merge lists
		if (arr[i] <= arr[j]) {
			sorted[k++] = arr[i++];
		}
		else {
			sorted[k++] = arr[j++];
		}
	}
	if (i > mid) {
		for (l = j; l <= right; l++) {
			sorted[k++] = arr[l];
		}
	}
	else {
		for (l = i; l <= mid; l++) {
			sorted[k++] = arr[l];
		}
	}
	for (l = left; l <= right; l++) {
		arr[l] = sorted[l];
	}
}
void merge_sort(vector<int>& arr, int left, int right) {
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		merge_sort(arr, left, mid);
		merge_sort(arr, mid+1, right);
		merge(arr, left, mid, right);
	}
}
void heap_adjust(vector<int>& arr, int root, int e) {
	int child = 2 * root;
	int tmp = arr[root];
	while (child <= e) {
		if (child < e&&arr[child] > arr[child + 1]) child++;
		if (tmp < arr[child]) break;
		else {
			arr[child / 2] = arr[child];
			child *= 2;
		}
	}
	arr[child / 2] = tmp;
}

void my_sort(vector<int>& arr, int s, int e) {//heap sort
	int n = e - s + 1;
	vector<int> v(n+1);
	int kk = s;
	for (int i = 1; i <= n; i++) {
		v[i] = arr[kk++];
	}
	int k = n / 2;
	for (int i = k; i >= 1; i--) {
		heap_adjust(v, i, n);
	}
	int t = n;
	kk = s;
	for (int i = 1; i <= n; i++) {
		arr[kk++] = v[1];
		swap(v[1], v[t]);
		heap_adjust(v, 1, --t);
	}
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	FILE* fp = fopen(argv[1], "r");//open inut file
	int n; 
	fscanf(fp,"%d", &n);
	vector<int> v(n);
	for (int i = 0; i < n; i++) {
		fscanf(fp, "%d", &v[i]);
	}
	before = clock();
	if (argv[2][0] == '1') insertion_sort(v, 0, n - 1);
	else if (argv[2][0] == '2') quick_sort(v, 0, n - 1);
	else if (argv[2][0] == '3')	merge_sort(v, 0, n - 1);
	else if (argv[2][0] == '4') my_sort(v, 0, n - 1);
	after = clock();
	char outputfilename[100] = "result_";
	if (argv[2][0] == '1')outputfilename[7] = '1';
	if (argv[2][0] == '2')outputfilename[7] = '2';
	if (argv[2][0] == '3')outputfilename[7] = '3';
	if (argv[2][0] == '4')outputfilename[7] = '4';
	outputfilename[8] = '_';
	outputfilename[9] = '\0';
	strcat(outputfilename, argv[1]);
	FILE* output = fopen(outputfilename, "w");
	fprintf(output, "%s\n%c\n%d\n", argv[1], argv[2][0], n);
	fprintf(output, "%lf\n", (after - before) / CLOCKS_PER_SEC);
	for (int i = 0; i < n; i++) {
		fprintf(output, "%d ", v[i]);
	}
	return 0;
}