#include <stdio.h>

#define MAX_LENGTH 1000


void handle_encode();
void handle_decode();
void handle_except();

char* encode(const char* string, char* result);
char* decode(const char* string, char* result);


int main() {
    int mode;
    printf("반복 길이 압축 프로그램입니다\n");
    printf("압축을 원하신다면 1, 압축 해제를 원하신다면 2를 입력해주세요\n");
    printf("(1 / 2) > "); scanf("%d", &mode);

    switch (mode) {
        case 1:
            handle_encode();
            break;
        case 2:
            handle_decode();
            break;
        default:
            handle_except();
    }

    return 0;
}

char* encode(const char* string, char* result) {
    int  index = 1,
         result_index = 0,
         char_count   = 1,
         form_len;
    char selected_char = string[0],
         buff[4];  // 버퍼 선언

    while (string[index] != '\0') {  // 문자열 끝까지 반복
        if (selected_char == string[index]) {  // 선택된 문자와 현재 문자가 같다면
            char_count++;  // 문자열 개수 카운트
        }
        else {  // 다르다면
            form_len = char_count > 1 ?
                sprintf(buff, "%c%d", selected_char, char_count) :  // 문자열 버퍼에 %c%d 형식으로 쓰기
                sprintf(buff, "%c", selected_char);  // 반복되지 않는다면 그대로 씀

            selected_char = string[index];  // 선택된 문자 변경
            char_count = 1;

            for (int i=0;i<form_len;i++) {
                result[result_index++] = buff[i];  // 결과 문자열에 쓰기
            }
        }
        index++;  // 다음 문자열로 넘어감
    }

    form_len = char_count > 1 ?
        sprintf(buff, "%c%d", selected_char, char_count) :  // 문자열 버퍼에 %c%d 형식으로 쓰기
        sprintf(buff, "%c", selected_char);  // 반복되지 않는다면 그대로 씀

    for (int i=0;i<form_len;i++)
        result[result_index++] = buff[i];

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
        selected_char = string[index];

        if ('0' <= string[index+1] && string[index+1] <= '9') {
            for (int i=0;i<2;i++) {
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

void handle_encode() {
    char path_from[100],
         path_to[100];
    printf("읽을 파일의 경로를 입력해주세요\n"); scanf("%s", path_from);
    printf("결과를 쓸 파일의 경로를 입력해주세요\n"); scanf("%s", path_to);
    FILE* from = fopen(path_from, "r+");
    FILE* to   = fopen(path_to, "w");

    if (from == NULL) {
        printf("파일을 읽을 수 없습니다.");
        return;
    }
    if (to   == NULL) {
        printf("파일을 쓸 수 없습니다.");
        return;
    }

    while (!feof(from)) {
        char buff[MAX_LENGTH],
             result[MAX_LENGTH];
        fgets(buff, MAX_LENGTH, from);
        encode(buff, result);
        fputs(result, to);
    }
}

void handle_decode() {
    char path_from[100],
         path_to[100];
    printf("읽을 파일의 경로를 입력해주세요\n"); scanf("%s", path_from);
    printf("결과를 쓸 파일의 경로를 입력해주세요\n"); scanf("%s", path_to);
    FILE* from = fopen(path_from, "r+");
    FILE* to   = fopen(path_to, "w");

    if (from == NULL) {
        printf("파일을 읽을 수 없습니다.");
        return;
    }
    if (to   == NULL) {
        printf("파일을 쓸 수 없습니다.");
        return;
    }

    while (!feof(from)) {
        char buff[MAX_LENGTH],
             result[MAX_LENGTH];
        fgets(buff, MAX_LENGTH, from);
        decode(buff, result);
        fputs(result, to);
    }
}

void handle_except() {
    printf("올바른 숫자를 입력해주세요");
}