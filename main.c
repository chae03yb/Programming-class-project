#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#define MAX_LENGTH 10

char* encode(const char* string, char* result);
char* decode(const char* string, char* result);

int main() {
    char string[MAX_LENGTH];
    char e_result[MAX_LENGTH];
    char d_result[MAX_LENGTH];
    scanf("%s", string);

    encode(string, e_result);
    decode(e_result, d_result);

    printf("%s\n", e_result);
    printf("%s\n", d_result);

    return 0;
}

char* encode(const char* string, char* result) {
    int  index = 1,
         result_index = 0,
         char_count   = 1;
    char selected_char = string[0];

    while (string[index] != '\0') {  // 문자열 끝까지 반복
        if (selected_char == string[index]) {  // 선택된 문자와 현재 문자가 같다면
            char_count++;  // 문자열 개수 카운트
        }
        else {  // 다르다면
            char buff[4];  // 버퍼 선언
            int form_len = char_count > 1 ?
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

    result[result_index++] = selected_char;
    result[result_index] = '\0';

    return result;
}

char* decode(const char* string, char* result) {
    int index = 0,
        result_index = 0;
    char selected_char;

    while (string[index] != '\0') {  // 문자열 반복
        bool is_repeated = '1' <= string[index+1] && string[index+1] <= '9';  // 다음 문자가 숫자면 반복됨
        int repeat_count = 0;  // 반복 횟수 저장용
        selected_char = string[index];  // 현재 문자

        result[result_index++] = selected_char;  // 인덱스 증가하며 결과 문자열에 현재 문자 추가

        if (is_repeated) {  // 반복되는 문자열이라면
            char buff[3];
            for (int i=2;i>=0;i--) {  // 반복 횟수 셈
                // FIXME: 연산으로 반복 횟수 세어야 함
                if ('0' <= string[index+i] && string[index+i] <= '9')
                    buff[i] = string[index+i];
                else
                    continue;
            }
            sscanf(buff, "%d", &repeat_count);

            for (int i=0;i<repeat_count;i++)  // 반복 횟수만큼 문자 추가
                result[result_index++] = selected_char;
        }
        index++;
    }
    result[result_index] = '\0';

    return result;
}
