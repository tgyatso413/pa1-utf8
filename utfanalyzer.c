#include <stdint.h>
#include <stdio.h>
#include <string.h>

char* is_ascii(unsigned char str[]) {
    for (int i = 0; str[i] != '\n'; i += 1) {
        if (str[i] > 128) {
            return "false";
        }
    }
    return "true";
}

int32_t capitalize_ascii(char str[]) {
    int x = 0;
    for (int i = 0; str[i] != '\n'; i += 1) {
        if (str[i] >= 97 && str[i] <= 122) {
            str[i] -= 32;
        }
    }
}

int length_in_bytes(char str[]) {
    int index = 0;
    for (int i = 0; str[i] != '\n'; i+= 1) {
        if (str[i] > 0 && str[i] <= 0b1111111) {
            index += 1;
        } else if ((str[i] & 0b11100000) == 0b11000000) {
            index += 2;
            i += 1;
        } else if ((str[i] & 0b11110000) == 0b11100000) {
            index += 3;
            i += 2;
        } else if ((str[i] & 0b11111000) == 0b11110000) {
            index += 4;
            i += 3;
        }
    }
    return index;
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

void bytes_per_codepoint(char str[], char result[]) {
    int index = 0;
    for (int i = 0; str[i] != '\n'; i+= 1) {
        if (str[i] > 0 && str[i] <= 0b1111111) {
            result[index] = '1';
        } else if ((str[i] & 0b11100000) == 0b11000000) {
            result[index] = '2';
            i += 1;
        } else if ((str[i] & 0b11110000) == 0b11100000) {
            result[index] = '3';
            i += 2;
        } else if ((str[i] & 0b11111000) == 0b11110000) {
            result[index] = '4';
            i += 3;
        }
        if (str[i + 1] != '\n') {
            result[index + 1] = ' ';
            index += 2;
        }
    }
}

int32_t codepoint_index_to_byte_index(unsigned char str[], int32_t cpi) {
    int index = 0;
    for (int i = 0; i < cpi; i += 1) {
        if ((str[i] > 0 && str[i] <= 0b1111111)) {
           index += 1;
        } else if ((str[i] & 0b11100000) == 0b11000000) {
            index += 2;
        } else if ((str[i] & 0b11110000) == 0b11100000) {
            index += 3;
        } else if ((str[i] & 0b11111000) == 0b11110000) {
            index += 4;
        }
    }
    return index;
}

void utf8_substring(char str[], int32_t cpi_start, int32_t cpi_end, char result[]) {
    int byte_start = codepoint_index_to_byte_index(str, cpi_start);
    int byte_end = codepoint_index_to_byte_index(str, cpi_end);
    int index = 0;

    for (int i = byte_start; i < byte_end; i++){
        result[index] = str[i];
        index += 1;
    }
    result[index] = '\0';
}

int32_t codepoint_at(char str[], int32_t cpi) {
        if (str[cpi] > 0 && str[cpi] <= 0b1111111) {
            return str[cpi];
        } else if ((str[cpi] & 0b11100000) == 0b11000000) {
            char part1 = str[cpi] & 0b00011111;
            char part2 = str[cpi + 1] & 0b00111111;
            return (part1 * 64) + part2;
        } else if ((str[cpi] & 0b11110000) == 0b11100000) {
            return ((str[cpi] & 0x0F) << 12) | ((str[cpi + 1] & 0x3F) << 6) | (str[cpi + 2] & 0x3F);
        } else if ((str[cpi] & 0b11111000) == 0b11110000) {
            return ((str[cpi] & 0x07) << 18 | (str[cpi + 1] & 0x3F) << 12) | ((str[cpi + 2] & 0x3F) << 6) | (str[cpi + 3] & 0x3F);
        }
}

//FIXME: Doesn't print special numbers correctly?
void cp_as_decimal(char str[], char result[]) {
    for (int i = 0; str[i] != '\n'; i+= 1) {
        printf("%d ", codepoint_at(str, i));
        if ((str[i] & 0b11100000) == 0b11000000) {
            i += 1;
        } else if ((str[i] & 0b11110000) == 0b11100000) {
            i += 2;
        } else if ((str[i] & 0b11111000) == 0b11110000) {
            i += 3;
        }
    }
}

// FIXME: Prints all emoji
char list_animal_emoji(char str[], char result[]) {
    int index = 0;
    for (int i = 0; str[i] != '\n'; i += 1) {
        if ((str[i] & 0b11100000) == 0b11000000) {
            i += 1;
        } else if ((str[i] & 0b11110000) == 0b11100000) {
            i += 2;
        } else if ((str[i] & 0b11111000) == 0b11110000) {
            int cp = codepoint_at(str, i);
            if (((cp >= 128000) && (cp <= 128063)) || (cp >= 129408) && (cp <= 129454)) {
            result[index] = str[i];
            result[index + 1] = str[i + 1];
            result[index + 2] = str[i + 2];
            result[index + 3] = str[i + 3];
            }
            if (str[i + 1] != '\n') {
                index += 4;
            }
            i += 3;
        }
    }
    if (index != 0) {
        result[index] = ' ';
    }
}

int main() {
    int MAX = 300;
    char input[MAX];
    char upper[MAX];
    
    puts("Enter a UTF-8 encoded string: ");
    fgets(input, MAX, stdin);
    memcpy(upper, input, strlen(input) + 1);
    char bpc[MAX];
    int i = 0;
    while (i < 50) {
        bpc[i] = 0;
        i += 1;
    }
    char emoji[MAX];
    char cpd[MAX];
    char sub[MAX];

    printf("Valid ASCII: %s\n", is_ascii(input));

    capitalize_ascii(upper);
    printf("Uppercased ASCII: %s\n", upper);

    printf("Length in bytes: %d\n", length_in_bytes(input));

    printf("Number of code points: %d\n", utf8_strlen(input));

    bytes_per_codepoint(input, bpc);
    printf("Bytes per code point: %s\n", bpc);

    utf8_substring(input, 0, 6, sub);
    printf("Substring of the first 6 code points: %s\n", sub);

    printf("Code points as decimal numbers: ");
    cp_as_decimal(input, cpd);
    puts("");

    list_animal_emoji(input, emoji);
    printf("Animal emojis: %s\n", emoji);
}

/*Enter a UTF-8 encoded string: My 🐩’s name is Erdős.
Valid ASCII: false
Uppercased ASCII: "MY 🐩’S NAME IS ERDőS."
Length in bytes: 27
Number of code points: 21
Bytes per code point: 1 1 1 4 3 1 1 1 1 1 1 1 1 1 1 1 1 1 2 1 1
*Substring of the first 6 code points: "My 🐩’s"
Code points as decimal numbers: 77 121 32 128041 8217 115 32 110 97 109 101 32 105 115 32 69 114 100 337 115 46
Animal emojis: 🐩
*/