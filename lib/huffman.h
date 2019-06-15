#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned long long ull;

void compress(std::istream &in, std::ostream &out);
bool decompress(std::istream &in, std::ostream &out);

#endif
