# CMakeList.txt: 14_CMake에 대한 CMake 프로젝트, 여기에 소스를 포함하고
# 프로젝트 특정 논리를 정의합니다.


# add_library로 분리하는 방법
# 규모가 커지만 기능 단위로 라이브러리로 묶어서 링크하는 방식.
# 모듈 단위 빌드 할때 이 구조 사용한다고 카더라

# math.obj를 라이브러로 묶는 것
add_library(math_lib math/math.cpp)

# 이 프로젝트의 실행 파일에 소스를 추가합니다.
add_executable (14_CMake "14_CMake.cpp" "14_CMake.h")

target_link_libraries(14_CMake PRIVATE math_lib)

# 링크 단계에서 연결하는 것
target_include_directories(14_CMake PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(math_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/math)


# 컴파일 옵션
if(MSVC)
    target_compile_options(14_CMake PRIVATE
        # Debug : 최적화 끄고 디버그 정보 포함
        $<$<CONFIG:Debug>:/Od /Zi /fsanitize=address>
        # Release : 최대 최적화
        $<$<CONFIG:Release>:/O2>
    )
else()
    target_compile_options(14_CMake PRIVATE
        # Debug
        $<$<CONFIG:Debug>:-O0 -g -fsanitize=address>
        # Release
        $<$<CONFIG:Release>:-O2>
    )
    target_link_options(14_CMake PRIVATE
        $<$<CONFIG:Debug>:-fsanitize=address>
    )
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 14_CMake PROPERTY CXX_STANDARD 20)
endif()