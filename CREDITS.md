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