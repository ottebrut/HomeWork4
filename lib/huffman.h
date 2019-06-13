#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <vector>

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned long long ull;

using namespace std;

void compressor(istream &in, ostream &out);
bool decompressor(istream &in, ostream &out);

template<typename T>
void write(T symb, ostream &out);
vector<pair<uint, char>> get_codes(const vector<uint> &cnt);

#endif
