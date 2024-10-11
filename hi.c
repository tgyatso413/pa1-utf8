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
    for (int i = 0; str[i] != '\n'; i += 1) {
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
    for (int i = 0; str[i] != '\n'; i += 1) {
        len += 1;
        if ((str[i] & 0b11100000) == 0b11000000) {
            i += 1;
        } else if ((str[i] & 0b11110000) == 0b11100000) {
            i += 2;
        } else if ((str[i] & 0b11111000) == 0b11110000) {
            i += 3;
        }
    }
    return len;
}

int32_t codepoint_index_to_byte_index(char str[], int32_t cpi) {
    int index = 0;
    for (int i = 0; i < cpi; i += 1) {
        if (str[i] > 0 && str[i] <= 127) {
            index += 1;
        } else if ((str[i] & 0b11000000) == 0b10000000) {
            index += 2;
        } else if ((str[i] & 0b11100000) == 0b11000000) {
            index += 3;
        } else if ((str[i] & 0b11110000) == 0b11100000) {
            index += 4;
        }
    }
    return index - 1;
    // "Returns -1 if there are any errors encountered in processing the UTF-8 string."
}

//FIXME - #4 Milestone 2
void utf8_substring(char str[], int32_t cpi_start, int32_t cpi_end, char result[]) {
    int byte_start = codepoint_index_to_byte_index(str, cpi_start);
    int byte_end = codepoint_index_to_byte_index(str, cpi_end);
    int index = 0;

    for (int i = byte_start; i < byte_end; i++){
        result [index] = str[i];
        index += 1;
    }
    result[index] = '\0';
}

//FIXME: this dont seem right
int32_t codepoint_at(char str[], int32_t cpi) {
    return str[cpi + 1];
}

//FIXME: #2 Milestone 3
char is_animal_emoji_at(unsigned char str[], int32_t cpi) {
    int temp[4];
    if ((str[cpi] & 0b11110000) == 0b11100000) {
        for (int i = 0; i < 4; i += 1) {
            temp[i] = str[cpi + i];
        }
    }
    if (((str[cpi] >= 128000) && (str[cpi] <= 128063)) || (str[cpi] >= 129408) && (str[cpi] <= 129454)){
        return 't';
    } else {
        return 'f';
    }
}

int .() {
    char input[300];
    fgets(input, 300, stdin);


    int32_t ret = 0;
    char str[] = "My 🐩’s name is Erdős.";
    ret = capitalize_ascii(str);
    printf("Capitalized String: %s\nCharacters updated: %d\n", str, ret);

    char s[] = "Héy"; // same as { 'H', 0xC3, 0xA9, 'y', 0 },   é is start byte + 1 cont. byte
    printf("Width: %d bytes\n", width_from_start_byte(s[1])); // start byte 0xC3 indicates 2-byte sequence


    /*char str[] = "Joséph";
    printf("Length of string %s is %d\n", str, utf8_strlen(str));  // 6 codepoints, (even though 7 bytes)*/

    int32_t idx = 4;
    printf("Codepoint index %d is byte index %d\n", idx, codepoint_index_to_byte_index("Joséph", idx));

//FIXME - #4 Milestone 2
    char result[17];
    utf8_substring("🦀🦮🦮🦀🦀🦮🦮", 3, 7, result);
    printf("String: %s\nSubstring: %s\n", "🦀🦮🦮🦀🦀🦮🦮", result); // these emoji are 4 bytes long

    printf("Codepoint at %d in %s is %d\n", idx, str, codepoint_at(str, idx)); // 'p' is the 4th codepoint
    printf("Is there an animal at 5: %c\n", is_animal_emoji_at("🦀🦮🦮🦀🦀🦮🦮", 5));
}