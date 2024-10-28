11100000 10000000 10100001 is equivalent to 0000000000100001, which has a decimal value of 33. The correlating character is !.

'!' can also be encoded as:
1. One byte: 00100001
2. Two bytes: 11000001 10100001
3. Four bytes: 11110000 10000000 10000000 10000001

An example of a character with exactly three encodings could be any character that requires at least two bytes of memory, such as 'â'. These characters can be encoded in two, three, or four bytes, but never in only one.

One problem with multiple encodings, especially overlong ones, is that it wastes memory. Using four bytes of memory to type a character that can be written with one byte, such as '!', wastes three bytes. Furthermore, there is history of security issues being caused by overlong encoding. Malicious actors can exploit input filters that didn't account for overlong encoding and access private materials.