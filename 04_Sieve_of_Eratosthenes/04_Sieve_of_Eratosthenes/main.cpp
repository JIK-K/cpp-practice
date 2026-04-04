#include<iostream>
#include<vector>

using namespace std;

void getPrimes(int n) {
	vector<bool> isPrime(n + 1, true);
	isPrime[0] = isPrime[1] = false;

	/* * [증명: i를 prime * 2가 아닌 prime * prime부터 시작해도 되는 이유]
	* 소수 prime의 배수 중 prime * prime보다 작은 값들은 (prime * 2, prime * 3, ..., prime * (prime-1))
	* 이 숫자들은 prime보다 작은 인수(2, 3, ..., prime-1)를 반드시 포함
	* prime * 2는 이미 소수 2를 처리할 때 지워졌고 prime * 3은 이미 소수 3을 처리할 때 지워짐
	* prime의 배수 중 최초로 지워지지 않은 숫자는 항상 prime * prime
	*/
	for (int prime = 2; prime * prime <= n; prime++) {
		if (isPrime[prime]) {
			// prime이 소수면 prime의 배수들을 모두 지운다
			for (int i = prime * prime; i <= n; i += prime) {
				isPrime[i] = false;
			}
		}
	}

	for (int prime = 2; prime <= n; prime++) {
		if (isPrime[prime]) {
			cout << prime << " ";
		}
	}
	
	/*
	* 단순 반복
	*/
	//for (int num = 2; num <= n; num++) {
	//	bool isPrime = true;

	//	for (int i = 2; i <= sqrt(num); i++) {
	//		if (num % i == 0) {
	//			isPrime = false;
	//			break;
	//		}
	//	}
	//	if (isPrime) {
	//		cout << num << " ";
	//	}
	//}
}

int main() {
	int n;
	cout << "수를 입력하세요 ";
	cin >> n;

	if (n < 2) {
		cout << "잘못된 입력입니다 \n 2 이상의 수를 입력하세요." << endl;
		return 0;
	}

	getPrimes(n);
}