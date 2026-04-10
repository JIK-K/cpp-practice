//#include<iostream>
//#include<cstddef>
//
//struct Normal {
//	char a;
//	int b;
//	char c;
//};
//
//struct alignas(16) Aligned16 {
//	char a;
//	int b;
//	char c;
//};
//
//int main() {
//    // alignof — 정렬 요구사항 확인
//    std::cout << "[alignof]" << std::endl;
//    std::cout << "alignof(char)   : " << alignof(char) << "\n";
//    std::cout << "alignof(int)    : " << alignof(int) << "\n";
//    std::cout << "alignof(double) : " << alignof(double) << "\n";
//
//    // sizeof — 패딩 확인
//    std::cout << "\n[sizeof]" << std::endl;
//    std::cout << "sizeof(Normal)    : " << sizeof(Normal) << "\n";
//    std::cout << "sizeof(Aligned16) : " << sizeof(Aligned16) << "\n";
//
//    // alignas — 정렬된 버퍼
//    alignas(16) char buf[64];
//    std::cout << "\n[alignas]" << std::endl;
//    std::cout << "buf address    : " << (void*)buf << "\n";
//    std::cout << "16 aligned?    : " << ((reinterpret_cast<uintptr_t>(buf) % 16 == 0) ? "YES" : "NO") << "\n";
//
//    // SIMD 연산 -> 16 또는 32바이트 정렬 필수
//    // DMA 전송 -> 특정 정렬 안 맞으면 하드웨어 에러
//    // 캐시라인 -> 64바이트 정렬하면 캐시 효율 극대화
//    return 0;
//}