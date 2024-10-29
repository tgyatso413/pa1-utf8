#include <stdint.h>
#include <stdio.h>
#include <string.h>

char* is_ascii(unsigned char str[]) {
    for (int i = 0; str[i] != '\0'; i += 1) {
        if (str[i] > 128) {
            return "false";
        }
    }
    return "true";
}

int32_t capitalize_ascii(char str[]) {
    for (int i = 0; str[i] != '\0'; i += 1) {
        if (str[i] >= 97 && str[i] <= 122) {
            str[i] -= 32;
        }
    }
}

int width_from_start_byte(char start) {
    if ((start & 0b11110000) == 0b11110000) {
    return 4;
    } else if ((start & 0b11100000) == 0b11100000) {
    return 3;
    } else if ((start & 0b11000000) == 0b11000000) {
    return 2;
    } else if (start > 0) { return 1; }
    else { return -1; }
}

int codepoint_to_byte_index(char str[], int cpi) {
    int result = 0;
    int index = 0;
    for (int i = 0; i < strlen(str); i++) { result += width_from_start_byte(str[cpi]); index += width_from_start_byte(str[cpi]); }
    return result;
}

int length_in_bytes(char str[]) {
    int index = 0;
    for (int i = 0; str[i] != '\0'; i+= 1) {
        if (width_from_start_byte(str[i]) == 1) {
            index += 1;
        } else if (width_from_start_byte(str[i]) == 2) {
            index += 2;
            i += 1;
        } else if (width_from_start_byte(str[i]) == 3) {
            index += 3;
            i += 2;
        } else if (width_from_start_byte(str[i]) == 4) {
            index += 4;
            i += 3;
        }
    }
    return index;
}

int32_t utf8_strlen(char str[]) {
    int len = 0;
    for (int i = 0; str[i] != '\0'; i += 1) {
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
    for (int i = 0; str[i] != '\0'; i+= 1) {
        if (str[width_from_start_byte(str[i]) + i - 1] != '\0') {
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
        if (str[i] != '\0') {
            result[index + 1] = ' ';
            index += 2;
        } else {
            return;
        }
        }
        
    }
}

int32_t codepoint_index_to_byte_index(unsigned char str[], int32_t cpi) {
    int index = 0;
    int cp = 0;
    for (int i = 0; cp != cpi; i += 1) {
        if ((str[i] > 0 && str[i] <= 0b1111111)) {
           index += 1;
           cp += 1;
        } else if ((str[i] & 0b11100000) == 0b11000000) {
            index += 2;
            cp += 1;
        } else if ((str[i] & 0b11110000) == 0b11100000) {
            index += 3;
            cp += 1;
        } else if ((str[i] & 0b11111000) == 0b11110000) {
            index += 4;
            cp += 1;
        }
    }
    return index;
}

void utf8_substring(char str[], int32_t cpi_start, int32_t cpi_end, char result[]) {
    int byte_start = codepoint_index_to_byte_index(str, cpi_start);
    int byte_end = codepoint_index_to_byte_index(str, cpi_end);
    int index = 0;

    for (int i = byte_start; i < byte_end; i++){
        if (str[i] != '\0') {
            result[index] = str[i];
            index += 1;
        }
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

void cp_as_decimal(char str[], char result[]) {
    for (int i = 0; str[i] != '\0'; i+= 1) {
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

char list_animal_emoji(char str[], char result[]) {
    int index = 0;
    int width;
    for (int i = 0; str[i] != '\0'; i += 1) {
        if (str[width_from_start_byte(str[i]) + i - 1] != '\0') {
            width = width_from_start_byte(str[i]);
        if (width == 2) {
            i += 1;
        } else if (width == 3) {
            i += 2;
        } else if (width == 4) {
            int cp = codepoint_at(str, i);
            if (((cp >= 128000) && (cp <= 128063)) || (cp >= 129408) && (cp <= 129454)) {
                result[index] = str[i];
                result[index + 1] = str[i + 1];
                result[index + 2] = str[i + 2];
                result[index + 3] = str[i + 3];
                index += 4;
            }
            i += 3;
        }
        }
    }
    if (index != 0) {
        result[index] = 0;
        result[index + 1] = 0;
    }
}

void encode_utf8(int32_t codepoint, char result[]) {
    if (codepoint <= 0x7F) {
        result[0] = (char)codepoint;
        result[1] = '\0';
    } else if (codepoint <= 0x7FF) {
        result[0] = (char)(0xC0 | (codepoint >> 6));
        result[1] = (char)(0x80 | (codepoint & 0x3F));
        result[2] = '\0';
    } else if (codepoint <= 0xFFFF) {
        result[0] = (char)(0xE0 | (codepoint >> 12));
        result[1] = (char)(0x80 | ((codepoint >> 6) & 0x3F));
        result[2] = (char)(0x80 | (codepoint & 0x3F));
        result[3] = '\0';
    } else if (codepoint <= 0x10FFFF) {
        result[0] = (char)(0xF0 | (codepoint >> 18));
        result[1] = (char)(0x80 | ((codepoint >> 12) & 0x3F));
        result[2] = (char)(0x80 | ((codepoint >> 6) & 0x3F));
        result[3] = (char)(0x80 | (codepoint & 0x3F));
        result[4] = '\0';
    } else {
        // Invalid codepoint
        result[0] = '\0'; // Set result to empty
    }
}

void next_utf8_char(char str[], int32_t cpi, char result[]) {
    int codepoint = codepoint_at(str, cpi);
    encode_utf8(codepoint + 1, result);
}


int main() {
    int MAX = 256;
    char input[MAX];
    char upper[MAX];
    
    printf("Enter a UTF-8 encoded string: ");
    fgets(input, MAX, stdin);
    input[strcspn(input, "\n")] = 0;
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
    char nxt[MAX];

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
    
    next_utf8_char(input, 3, nxt);
    printf("Next Character of Codepoint at Index 3: %s\n", nxt);
}
