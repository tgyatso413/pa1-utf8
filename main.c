#include <stdint.h>
#include <stdio.h>

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

int main() {
    printf("Is 🔥 ASCII? %d\n", is_ascii("🔥"));

    int32_t ret = 0;
    char str[] = "abcd";
    ret = capitalize_ascii(str);
    printf("Capitalized String: %s\nCharacters updated: %d\n", str, ret);
}