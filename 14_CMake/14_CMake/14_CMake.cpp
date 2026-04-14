// 14_CMake.cpp : 애플리케이션의 진입점을 정의합니다.
//

#include "14_CMake.h"
#include "math/math.hpp"

using namespace std;

int main()
{
	// 일부러 누수 만들기
	int* leak = new int[10];
	leak[20] = 42;

	std::cout << add(2, 3) << std::endl;
	std::cout << multiply(2, 3) << std::endl;
	return 0;
}
