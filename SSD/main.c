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
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define INVALID1 printf("INVALID : ARGUMENT ERROR")
#define INVALID2 printf("INVALID : COMMAND ERROR")
#define INVALID3 printf("INVALID : FAULT(OUT OF BOUND)")

int is_valid_number(const char* str) {
	char* endptr;
	errno = 0;
	long val = strtol(str, &endptr, 10);

	if (errno != 0 || *endptr != '\0') return 0; // 변환 실패 , 남은 문자가 있으면 invalid

	if (val < 0 || val > 99) return 0; // 범위 검사

	return 1;
}

int main(int argc, char* argv[]) {
	//printf("argc = %d\n", argc);
	/*for (int i = 0; i < argc; i++) {
		printf("argv[%d] = %s\n", i, argv[i]);
	}*/
	unsigned int NAND[100] = { 0 }; // NAND 배열
	FILE* fp;
	if (argc < 3 || argc > 4) { // argument가 0
		INVALID1;
	}
	else {
		if (strcmp(argv[1], "READ") == 0 && argc == 3) { // READ MODE : argument 수 3인지 확인!
			if (is_valid_number(argv[2]) == 1) {
				printf("READING .. %d\n", atoi(argv[2]));
				// NAND.TXT 파일 열어서 배열에 저장 - NAND.TXT는 있다고 가정
				// 배열에서 argv[2] index의 값을
				// RESULT.TXT 파일 열어서 쓰기(내용 이어쓰기! 덮어쓰기 X) - RESULT.TXT는 있다고 가정
				fp = fopen("./nand.txt", "r");
				if (!fp) {
					perror("NAND.TXT open failed");
					exit(1);
				}

				for (int i = 0; i < 100; i++) { // 파일에서 배열 읽기
					fscanf(fp, "%x", &NAND[i]);
				}
				fclose(fp);
				
				fp = fopen("./result.txt", "a"); // RESULT.TXT - 이어 쓰기
				if (!fp) {
					perror("RESULT.TXT open failed");
					exit(1);
				}

				// 지정 인덱스 값만 저장
				fprintf(fp, "%08X\n", NAND[atoi(argv[2])]);
				fclose(fp);
			}
			else { // 범위에 어긋나거나 숫자가 아닌 경우
				INVALID3;
			}
		}
		else if (strcmp(argv[1], "WRITE") == 0 && argc == 4) { // WRITE MODE : argument 수 4인지 확인!
			if (is_valid_number(argv[2]) == 1) {
				// NAND.TXT 파일 없으면 생성 - 배열의 값 0X00000000으로 모두 셋팅
				// NAND.TXT 있으면 파일 열어서 배열에 저장하기 - 배열의 값 파일의 값으로 모두 셋팅
				// 배열에서 argv[2] index의 값을 argv[3]으로 설정
				// 배열을 다시 NAND.TXT에 쓰기(내용 덮어쓰기! 이어쓰기 X)
				unsigned int value = (unsigned int)strtoul(argv[3], NULL, 16); // 16진수 입력 처리
				fp = fopen("./nand.txt", "r");
				if (fp) {
					for (int i = 0; i < 100; i++) {
						fscanf(fp, "%x", &NAND[i]);
					}
					fclose(fp);
				}
				else {
					// 파일 없으면 0x00000000으로 초기화
					for (int i = 0; i < 100; i++) {
						NAND[i] = 0x00000000;
					}
				}

				// 배열에 값 설정
				NAND[atoi(argv[2])] = value;

				// NAND.TXT에 다시 저장 (덮어쓰기)
				fp = fopen("./nand.txt", "w");
				if (!fp) {
					perror("NAND.TXT open failed");
					exit(1);
				}

				for (int i = 0; i < 100; i++) {
					fprintf(fp, "%08X\n", NAND[i]);
				}
				fclose(fp);
				printf("WRITING .. %d\n", atoi(argv[2]));
			}
			else { // 범위에 어긋나거나 숫자가 아닌 경우
				INVALID3;
			}
		}
		else {
			INVALID2;
		}
	}
	return 0;
}