// ��ü���� LOGIC

// ��쿡 ���� 2, 3���� argument�� �޾� �����Ѵ�.
// read�� ��� 1���� argument�� �޴´�.
// write�� ��� 2���� argument�� �޴´�.

// nand.txt ������ �����ϰ� 100���� 0x00000000(�� ������ ����)�� �����Ѵ�. ���� c ���� ���� �迭�� ���� �����Ѵ�.
// nand.txt ������ �а�, NAND[] �迭�� �����Ѵ�.
// �迭�� NAND[]�� �����Ѵ�.

// read ��ɾ� ����
// read n�� ������, n ���� �˻縦 �����Ѵ�.
// ���� �˻縦 ������� ���ϸ�, FAULT(Out Of Range/Bound) while reading ���
// ���� �˻縦 ����ϸ� NAND[n]�� �迭 RESULT[]�� ���ʷ� �����Ѵ�.

// write ��ɾ� ����
// write n arg�� ������, n ���� �˻縦 �����Ѵ�.
// ���� �˻縦 ������� ���ϸ�, FAULT(Out Of Range/Bound) while writing ���
// ���� �˻縦 ����ϸ� NAND[n]�� arg�� �����Ѵ�.

// read, write�� ���� �� ��� ����
// RESULT�� �� ������(bool isReaded), RESULT �迭�� ./result.txt�� ���� �����Ѵ�(����� x).
// WRITE�� �Ǿ�����(bool isWrited), NAND �迭�� ./nand.txt�� ���� �����Ѵ�(����� x).
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

	if (errno != 0 || *endptr != '\0') return 0; // ��ȯ ���� , ���� ���ڰ� ������ invalid

	if (val < 0 || val > 99) return 0; // ���� �˻�

	return 1;
}

int main(int argc, char* argv[]) {
	//printf("argc = %d\n", argc);
	/*for (int i = 0; i < argc; i++) {
		printf("argv[%d] = %s\n", i, argv[i]);
	}*/
	unsigned int NAND[100] = { 0 }; // NAND �迭
	FILE* fp;
	if (argc < 3 || argc > 4) { // argument�� 0
		INVALID1;
	}
	else {
		if (strcmp(argv[1], "READ") == 0 && argc == 3) { // READ MODE : argument �� 3���� Ȯ��!
			if (is_valid_number(argv[2]) == 1) {
				printf("READING .. %d\n", atoi(argv[2]));
				// NAND.TXT ���� ��� �迭�� ���� - NAND.TXT�� �ִٰ� ����
				// �迭���� argv[2] index�� ����
				// RESULT.TXT ���� ��� ����(���� �̾��! ����� X) - RESULT.TXT�� �ִٰ� ����
				fp = fopen("./nand.txt", "r");
				if (!fp) {
					perror("NAND.TXT open failed");
					exit(1);
				}

				for (int i = 0; i < 100; i++) { // ���Ͽ��� �迭 �б�
					fscanf(fp, "%x", &NAND[i]);
				}
				fclose(fp);
				
				fp = fopen("./result.txt", "a"); // RESULT.TXT - �̾� ����
				if (!fp) {
					perror("RESULT.TXT open failed");
					exit(1);
				}

				// ���� �ε��� ���� ����
				fprintf(fp, "%08X\n", NAND[atoi(argv[2])]);
				fclose(fp);
			}
			else { // ������ ��߳��ų� ���ڰ� �ƴ� ���
				INVALID3;
			}
		}
		else if (strcmp(argv[1], "WRITE") == 0 && argc == 4) { // WRITE MODE : argument �� 4���� Ȯ��!
			if (is_valid_number(argv[2]) == 1) {
				// NAND.TXT ���� ������ ���� - �迭�� �� 0X00000000���� ��� ����
				// NAND.TXT ������ ���� ��� �迭�� �����ϱ� - �迭�� �� ������ ������ ��� ����
				// �迭���� argv[2] index�� ���� argv[3]���� ����
				// �迭�� �ٽ� NAND.TXT�� ����(���� �����! �̾�� X)
				unsigned int value = (unsigned int)strtoul(argv[3], NULL, 16); // 16���� �Է� ó��
				fp = fopen("./nand.txt", "r");
				if (fp) {
					for (int i = 0; i < 100; i++) {
						fscanf(fp, "%x", &NAND[i]);
					}
					fclose(fp);
				}
				else {
					// ���� ������ 0x00000000���� �ʱ�ȭ
					for (int i = 0; i < 100; i++) {
						NAND[i] = 0x00000000;
					}
				}

				// �迭�� �� ����
				NAND[atoi(argv[2])] = value;

				// NAND.TXT�� �ٽ� ���� (�����)
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
			else { // ������ ��߳��ų� ���ڰ� �ƴ� ���
				INVALID3;
			}
		}
		else {
			INVALID2;
		}
	}
	return 0;
}