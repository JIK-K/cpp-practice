#include<iostream>
#include<vector>

using namespace std;

static vector<int> arr;

int partition(int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void sort(int low, int high)
{
    if (low < high)
    {
        int pi = partition(low, high);
        sort(low, pi - 1);
        sort(pi + 1, high);
    }
}

void printArray()
{
    int n = arr.size();

    cout << "정렬된 배열 : ";

    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
	int n;
	cout << "배열 크기 : " ;
	cin >> n;

	cout << "배열 요소 : ";;
	for (int i = 0; i < n; i++) {
		int temp;
		cin >> temp;

		arr.push_back(temp);
	}

    sort(0, n - 1);
    
    printArray();
}