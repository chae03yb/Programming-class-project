#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 10
#define ESCAPE '`';

void handle_encode();
void handle_decode();
void handle_except();

char* encode(const char* string, char* result);
char* decode(const char* string, char* result);

int main() {
    char string[MAX_LENGTH];
    char e_result[MAX_LENGTH];
    char d_result[MAX_LENGTH];

    int mode;
    printf("�ݺ� ���� ���� ���α׷��Դϴ�\n");
    printf("������ ���ϽŴٸ� 1, ���� ������ ���ϽŴٸ� 2�� �Է����ּ���\n");
    printf("(1 / 2) > "); scanf("%d", &mode);

    switch (mode) {
        case 1:
            handle_encode();
//            FILE* file = fopen("", "");
//            encode()
            break;
        case 2:
            handle_decode();
            break;
        default:
            handle_except();
            printf("�ùٸ� ���ڸ� �Է����ּ���");
            return 0;
    }

    scanf("%s", string);

    encode(string, e_result);
    decode(e_result, d_result);

    return 0;
}

char* encode(const char* string, char* result) {
    int  index = 1,
         result_index = 0,
         char_count   = 1;
    char selected_char = string[0];

    while (string[index] != '\0') {  // ���ڿ� ������ �ݺ�
        if (selected_char == string[index]) {  // ���õ� ���ڿ� ���� ���ڰ� ���ٸ�
            char_count++;  // ���ڿ� ���� ī��Ʈ
        }
        else {  // �ٸ��ٸ�
            char buff[4];  // ���� ����
            int form_len = char_count > 1 ?
                sprintf(buff, "%c%d", selected_char, char_count) :  // ���ڿ� ���ۿ� %c%d �������� ����
                sprintf(buff, "%c", selected_char);  // �ݺ����� �ʴ´ٸ� �״�� ��
            
            selected_char = string[index];  // ���õ� ���� ����
            char_count = 1;

            for (int i=0;i<form_len;i++) {
                result[result_index++] = buff[i];  // ��� ���ڿ��� ����
            }
        }
        index++;  // ���� ���ڿ��� �Ѿ
    }

    result[result_index++] = selected_char;
    result[result_index] = '\0';

    return result;
}

char* decode(const char* string, char* result) {
    int  index = 0,
         result_index = 0,
         repeat_count;
    char selected_char,
         buff[4];

    while (string[index] != '\0') {
        // a3bc
        selected_char = string[index];

        if ('0' <= string[index+1] && string[index+1] <= '9') {
            for (int i=0;i<2;i++) {
                int _ = string[index+1+i];
                if (string[index+1+i] < '0' || string[index+1+i] > '9') {
                    index += i+1;
                    break;
                }
                buff[i] = string[index+1+i];
            }
            buff[index] = '\0';
            sscanf(buff, "%d", &repeat_count);

            for (int i=0;i<repeat_count;i++)
                result[result_index++] = selected_char;

        } else {
            result[result_index++] = string[index++];
        }
    }
    result[result_index] = '\0';

    return result;
}
