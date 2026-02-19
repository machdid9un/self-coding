# 컴파일러 설정
CXX = g++

# 컴파일 옵션 (C++20 버전 사용, 경고 메시지 활성화, 최적화)
CXXFLAGS = -std=c++20 -Wall -O2

# 최종 출력 파일명 (실행 파일명)
TARGET = mansimulate

# 소스 파일 설정
# mansimulate.cpp에서 gene.cpp를 직접 인클루드하므로 메인 파일만 명시합니다.
SRCS = mansimulate.cpp

# 기본 빌드 규칙
all: $(TARGET)

# 링크 및 빌드 규칙
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

# 생성된 실행 파일 삭제
clean:
	rm -f $(TARGET)

# 프로그램을 빌드하고 즉시 실행
run: all
	./$(TARGET)
