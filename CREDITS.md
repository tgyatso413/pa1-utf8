- Used Professor Schulman's example of getting a codepoint for two bytes
- Austin Kinnear explained << and >> (shifting) to me
- Looked at C library to understand memcpy() function

- Gave ChatGPT the prompt: "Help me finish a function named codepoint_at that gets the codepoint of a character but don't give me the code"
"To complete the codepoint_at function for obtaining the codepoint of a UTF-8 encoded character, you need to handle the remaining cases where the character spans three or four bytes. Here are the steps to follow:

Identify the Starting Byte:
The initial byte (str[cpi]) indicates how many bytes the character uses:
If the starting byte matches 0b11100000, it’s a three-byte character.
If the starting byte matches 0b11110000, it’s a four-byte character.

Extract and Process Each Byte:
For both three-byte and four-byte characters, you’ll need to use the next two or three bytes, respectively. Mask each subsequent byte to extract only the relevant bits (the last six bits of each byte).

Compute the Codepoint for a Three-Byte Character:
Mask the initial byte to keep the last four bits.
Extract and combine bits from the next two bytes, considering their place values.
Use bitwise operations to shift and combine these extracted bits into a single codepoint.

Compute the Codepoint for a Four-Byte Character:
Mask the initial byte to keep the last three bits.
Extract and combine bits from the following three bytes, considering their place values.
Use bitwise operations to shift and combine these extracted bits into a single codepoint.

Return the Calculated Codepoint:
After processing the relevant bytes, return the final computed codepoint.

By handling these cases, you’ll complete the function to properly decode UTF-8 codepoints for one, two, three, and four-byte characters."

- Gave ChatGPT the prompt: "write a utf-8 encoding function"
"Certainly! Below is a simple C function that encodes a Unicode code point into its corresponding UTF-8 representation. This function handles code points ranging from U+0000 to U+10FFFF.
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
}"

-Gave ChatGPT the prompt: "explain the function to me"
"Sure! Let’s break down the `encode_utf8` function step by step:

### Function Purpose
The `encode_utf8` function takes a Unicode code point and encodes it into its UTF-8 representation, storing the result in the provided character array (`result`).

### Function Parameters
- `int32_t codepoint`: This is the Unicode code point that you want to encode. It can range from 0 to 0x10FFFF (the maximum valid code point).
- `char result[]`: This is an array where the resulting UTF-8 encoded bytes will be stored.

### Encoding Logic

1. **Single-byte (1-byte) Encoding**: 
   ```c
   if (codepoint <= 0x7F) {
       result[0] = (char)codepoint;
       result[1] = '\0';
   }
   ```
   - If the code point is less than or equal to `0x7F`, it fits within a single byte (the ASCII range).
   - The byte is directly assigned to `result[0]`.
   - The string is null-terminated with `result[1] = '\0'`.

2. **Two-byte Encoding**:
   ```c
   else if (codepoint <= 0x7FF) {
       result[0] = (char)(0xC0 | (codepoint >> 6));
       result[1] = (char)(0x80 | (codepoint & 0x3F));
       result[2] = '\0';
   }
   ```
   - For code points between `0x80` and `0x7FF`, UTF-8 uses two bytes.
   - The first byte is created by:
     - Shifting the code point right by 6 bits.
     - Using a bitwise OR with `0xC0` (binary `110xxxxx`).
   - The second byte is created by:
     - Masking the code point with `0x3F` (which captures the last 6 bits).
     - Using a bitwise OR with `0x80` (binary `10xxxxxx`).
   - The result is null-terminated.

3. **Three-byte Encoding**:
   ```c
   else if (codepoint <= 0xFFFF) {
       result[0] = (char)(0xE0 | (codepoint >> 12));
       result[1] = (char)(0x80 | ((codepoint >> 6) & 0x3F));
       result[2] = (char)(0x80 | (codepoint & 0x3F));
       result[3] = '\0';
   }
   ```
   - For code points from `0x800` to `0xFFFF`, three bytes are used.
   - The first byte is created similarly as before but with `0xE0` (binary `1110xxxx`).
   - The second and third bytes are created using the same method as for two-byte encoding.

4. **Four-byte Encoding**:
   ```c
   else if (codepoint <= 0x10FFFF) {
       result[0] = (char)(0xF0 | (codepoint >> 18));
       result[1] = (char)(0x80 | ((codepoint >> 12) & 0x3F));
       result[2] = (char)(0x80 | ((codepoint >> 6) & 0x3F));
       result[3] = (char)(0x80 | (codepoint & 0x3F));
       result[4] = '\0';
   }
   ```
   - For code points from `0x10000` to `0x10FFFF`, four bytes are used.
   - The first byte is generated with `0xF0` (binary `11110xxx`), and the subsequent bytes are created similarly to the previous cases.

5. **Invalid Code Point Handling**:
   ```c
   else {
       // Invalid codepoint
       result[0] = '\0'; // Set result to empty
   }
   ```
   - If the code point is greater than `0x10FFFF` or negative, it is invalid.
   - The function sets the first element of `result` to `'\0'` to indicate an empty string.

### Summary
The function systematically checks the range of the provided code point and encodes it into the appropriate number of bytes according to the UTF-8 standard. The final UTF-8 byte sequence is stored in the `result` array, which is always null-terminated for safe string handling."