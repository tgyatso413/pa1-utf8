#include <stdint.h>
#include <stdio.h>
#include <string.h>

int32_t is_ascii(unsigned char str[]) {
    for (int i = 0; i < strlen(str); i += 1) {
        if (str[i] > 128) {
            return 0;
        }
    }
    return 1;
}

int32_t capitalize_ascii(char str[]) {
    int x = 0;
    for (int i = 0; i < strlen(str); i += 1) {
        if (str[i] >= 97 && str[i] <= 122) {
            str[i] -= 32;
            x += 1;
        }
    }
    return x;
}

int32_t width_from_start_byte(char start_byte) {
    if (start_byte > 0 && start_byte <= 256) {
        return 1;
    } else if ((start_byte & 0b11000000) != (start_byte & 0b10000000)) {
        return 2;
    } else {
        return -1;
    }
}

int32_t utf8_strlen(char str[]) {
    int len = 0;
    for (int i = 0; i < strlen(str); i += 1) {
        if ((str[i] > 0 && str[i] <= 256) || (str[i] & 0b11000000) != (str[i] & 0b10000000)) {
            len += 1;
        }
    }
    return len;
}

int32_t codepoint_index_to_byte_index(char str[], int32_t cpi) {
    int index = 0;
    for (int i = 0; i < cpi; i += 1) {
        if (str[i] > 0 && str[i] <= 256) {
            index += 1;
        } else if ((str[i] & 0b11000000) != (str[i] & 0b10000000)) {
            index += 2;
        }
    }
    return index;
    // "Returns -1 if there are any errors encountered in processing the UTF-8 string."
}

//FIXME - #4 Milestone 2
void utf8_substring(char str[], int32_t cpi_start, int32_t cpi_end, char result[]) {
    int len = cpi_end - cpi_start;
    char temp[len];
    for (int i = 0; i < len; i++) {
        temp[i] = str[i + cpi_start];
    }
    str = temp;
}

int32_t codepoint_at(char str[], int32_t cpi) {
    return str[cpi + 1];
}

//FIXME: #2 Milestone 3
char is_animal_emoji_at(char str[], int32_t cpi) {

}

int main() {
    char str[] = "Joséph";
    printf("Length of string %s is %d\n", str, utf8_strlen(str));  // 6 codepoints, (even though 7 bytes)

    int32_t idx = 4;
    printf("Codepoint index %d is byte index %d\n", idx, codepoint_index_to_byte_index("Joséph", idx));

//FIXME - #4 Milestone 2
    char result[17];
    utf8_substring("🦀🦮🦮🦀🦀🦮🦮", 3, 7, result);
    printf("String: %s\nSubstring: %s", result); // these emoji are 4 bytes long

    printf("Codepoint at %d in %s is %d\n", idx, str, codepoint_at(str, idx)); // 'p' is the 4th codepoint
}