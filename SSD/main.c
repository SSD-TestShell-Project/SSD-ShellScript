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
		if (strcmp(argv[1], "READ") == 0) { // + argument 2���� Ȯ��!
			printf("READING\n");
		}
		else if (strcmp(argv[1], "WRITE") == 0) { // + argument 3���� Ȯ��!
			printf("WRITING\n");
		}
		else {
			INVALID2;
		}
	}
	return 0;
}