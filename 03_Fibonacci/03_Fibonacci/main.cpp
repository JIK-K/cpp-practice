#include <iostream>
#include <vector>

using namespace std;

static vector<int> arr;

unsigned long fibo(int n) {
    if (n <= 0) return 0;
    if (n == 1 || n == 2) return 1;

    // memoization
    if (n < arr.size() && arr[n] != 0) return arr[n];

    unsigned long result = fibo(n - 1) + fibo(n - 2);

    if (n >= arr.size()) arr.resize(n + 1, 0);

    return arr[n] = result;
}

int main() {
    int n;

    arr.push_back(0); 
    arr.push_back(1); 
    arr.push_back(1); 

    cout << "입력 : ";
    cin >> n;

    cout << "결과 : " << fibo(n) << endl;

    return 0;
}