#include <stdio.h>
#include <math.h>

#define MAX_LENGTH 10

char* int2str(int num);
int   str2int(char* str);
void  encode(char* string);
char* decode();


int main() {
    char string[MAX_LENGTH];
    scanf("%s", string);

    encode(string);

    return 0;
}

char* int2str(int num) {
    char result[11];
    int loop_limit = log10((double)num);
    for (int i=0;i<loop_limit;i++) {

    }
    result[loop_limit] = '\0';
}

int str2str(char* str) {

}

void encode(char* string) {
    char result[MAX_LENGTH];
    int index = 0,
        result_index = 0,
        prev_char    = 0,
        char_count   = 0;

    while (string[index] != '\0') {
        if (prev_char == string[index]) {
            char_count++;
        }
        else {
            char num[] = int2str(char_count);

            result[result_index++] = prev_char;
            result[result_index++];
        }
        index++;
    }
}

char* decode() {

}