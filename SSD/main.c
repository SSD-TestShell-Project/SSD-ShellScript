// 전체적인 LOGIC

// 경우에 따라 2, 3개의 argument를 받아 수행한다.
// read의 경우 1개의 argument를 받는다.
// write의 경우 2개의 argument를 받는다.

// nand.txt 없으면 생성하고 100개의 0x00000000(빈 값으로 가정)을 세팅한다. 이후 c 파일 내부 배열에 값을 저장한다.
// nand.txt 있으면 읽고, NAND[] 배열에 저장한다.
// 배열을 NAND[]로 생각한다.

// read 명령어 구현
// read n이 들어오면, n 범위 검사를 수행한다.
// 범위 검사를 통과하지 못하면, FAULT(Out Of Range/Bound) while reading 출력
// 범위 검사를 통과하면 NAND[n]을 배열 RESULT[]에 차례로 저장한다.

// write 명령어 구현
// write n arg이 들어오면, n 범위 검사를 수행한다.
// 범위 검사를 통과하지 못하면, FAULT(Out Of Range/Bound) while writing 출력
// 범위 검사를 통과하면 NAND[n]에 arg를 저장한다.

// read, write가 실행 될 경우 각각
// RESULT가 차 있으면(bool isReaded), RESULT 배열을 ./result.txt에 쓰고 저장한다(덮어쓰기 x).
// WRITE가 되었으면(bool isWrited), NAND 배열을 ./nand.txt에 쓰고 저장한다(덮어쓰기 x).
#include <stdio.h>
#include <string.h>
#define INVALID1 printf("INVALID : ARGUMENT ERROR")
#define INVALID2 printf("INVALID : COMMAND ERROR")
int main(int argc, char* argv[]) {
	//printf("argc = %d\n", argc);
	/*for (int i = 0; i < argc; i++) {
		printf("argv[%d] = %s\n", i, argv[i]);
	}*/
	if (argc < 2 || argc > 3) {
		INVALID1;
	}
	else {
		if (strcmp(argv[1], "READ") == 0) { // + argument 2인지 확인!
			printf("READING\n");
		}
		else if (strcmp(argv[1], "WRITE") == 0) { // + argument 3인지 확인!
			printf("WRITING\n");
		}
		else {
			INVALID2;
		}
	}
	return 0;
}