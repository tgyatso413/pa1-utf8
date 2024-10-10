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

//FIXME: adding on letters at the end?
void capitalize_ascii(char str[], char upper[]) {
    for (int i = 0; str[i] != '\n'; i += 1) {
        if (str[i] >= 97 && str[i] <= 122) {
            upper[i] = str[i] - 32;
        } else {
            upper[i] = str[i];
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

//FIXME: Doesn't print special numbers correctly?
void cp_as_decimal(char str[], char result[]) {
    int index = 0;
    for (int i = 0; str[i] != '\n'; i+= 1) {
        if (str[i] > 0 && str[i] <= 0b1111111) {
            printf("%d ", str[i]);
        } else if ((str[i] & 0b11100000) == 0b11000000) {
            result[index]= str[i] & 0b00011111;
            result[index + 1] = str[i + 1] & 0b00111111;
            index += 2;
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

// FIXME: Prints all emoji
char list_animal_emoji(char str[], char result[]) {
    int index = 0;
    for (int i = 0; str[i] != '\n'; i += 1) {
        if ((str[i] & 0b11100000) == 0b11000000) {
            i += 1;
        } else if ((str[i] & 0b11110000) == 0b11100000) {
            i += 2;
        } else if ((str[i] & 0b11111000) == 0b11110000) {
            result[index] = str[i];
            result[index + 1] = str[i + 1];
            result[index + 2] = str[i + 2];
            result[index + 3] = str[i + 3];
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

    puts("Enter a UTF-8 encoded string: ");
    fgets(input, MAX, stdin);
    char upper[MAX];
    char bpc[MAX];
    char emoji[MAX];
    char cpd[MAX];

    printf("Valid ASCII: %s\n", is_ascii(input));
    capitalize_ascii(input, upper);
    printf("Uppercased ASCII: %s\n", upper);
    printf("Length in bytes: %d\n", length_in_bytes(input));
    printf("Number of code points: %d\n", utf8_strlen(input));
    bytes_per_codepoint(input, bpc);
    printf("Bytes per code point: %s\n", bpc);
    printf("Substring of the first 6 code points: \n");
    printf("Code points as decimal numbers: ");
    cp_as_decimal(input, cpd);
    puts("");
    list_animal_emoji(input, emoji);
    printf("Animal emojis: %s\n", emoji);
}

/*Enter a UTF-8 encoded string: My 🐩’s name is Erdős.
Valid ASCII: false
*Uppercased ASCII: "MY 🐩’S NAME IS ERDőS."
Length in bytes: 27
Number of code points: 21
Bytes per code point: 1 1 1 4 3 1 1 1 1 1 1 1 1 1 1 1 1 1 2 1 1
*Substring of the first 6 code points: "My 🐩’s"
*Code points as decimal numbers: 77 121 32 128041 8217 115 32 110 97 109 101 32 105 115 32 69 114 100 337 115 46
*Animal emojis: 🐩


TODO: 
Watch the last lecture to see if I missed something.
Look at Aaron's slides for reference on how to get codepoint from binary
There is something wrong with upper and bpc that makes it think there's more characters.
Code points as decimal numbers is getting the multibyte characters as its UTF-8 values rather than its hexadecimal values.
*/