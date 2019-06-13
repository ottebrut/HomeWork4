#include "sstream"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include "huffman.h"
#include "tree.h"

using namespace std;

const int BUFF_SIZE = 4096;
const int A_SIZE = 256;

uchar buffer[BUFF_SIZE];
uchar buffer_out[BUFF_SIZE];
uint buff_ind = 0;
ull length = 0;
ull stream = 0;

void compressor(istream &in, ostream &out) {

    vector<uint> cnt(A_SIZE);

    in.seekg(0);
    size_t size;
    while((size = in.readsome((char *)buffer, BUFF_SIZE)) > 0) {
        for(size_t ind = 0; ind < size; ++ind) {
            cnt[buffer[ind]]++;
        }
    }

    out.write((char *)&stream, sizeof(stream));
    buff_ind = 0;
    for(size_t ind = 0; ind < A_SIZE; ++ind) {
        write((uchar)ind, out);
        write(cnt[ind], out);
    }

    vector<pair<uint, char>> code = get_codes(cnt);
    uint line = 0;
    uint line_size = 0;
    stream = 0;
    in.seekg(0);
    while((size = in.readsome((char *)buffer, BUFF_SIZE)) > 0) {
        for(size_t ind = 0; ind < size; ++ind) {
            line += code[buffer[ind]].first << line_size;
            line_size += code[buffer[ind]].second;
            if (line_size >= 32) {
                write(line, out);
                line_size -= 32;
                line = code[buffer[ind]].first >> (code[buffer[ind]].second - line_size);
            }
        }
    }
    if (line_size) {
        write(line, out);
        stream -= 32 - line_size;
    }

    if (buff_ind) {
        out.write((char *)buffer_out, buff_ind);
    }
    out.seekp(0);
    out.write((char *)&stream, sizeof(stream));
}

bool decompressor(istream &in, ostream &out) {

    vector<uint> cnt(A_SIZE);

    in.seekg(0);
    in.read((char *)&length, sizeof(length));
    for(size_t ind = 0; ind < A_SIZE; ++ind) {
        uchar i;
        in.read((char *)&i, sizeof(i));
        if (i != ind) {
            return false;
        }
        in.read((char *)&cnt[ind], sizeof(cnt[ind]));
    }

    tree Tree(get_codes(cnt));
    buff_ind = 0;
    size_t size;
    while((size = in.readsome((char *)buffer, BUFF_SIZE)) > 0) {
        for(size_t ind = 0; ind < size; ++ind) {
            for(size_t b = 0; b < min((ull)8, length); ++b) {
                if (Tree.go((buffer[ind] >> b) & 1u)) {
                    if (Tree.end()) {
                        write(Tree.get(), out);
                    }
                } else {
                    return false;
                }
            }
            length = (length > 8 ? length - 8 : 0);
        }
    }

    if (buff_ind) {
        out.write((char *)buffer_out, buff_ind);
    }
    return true;
}

template<typename T>
void write(T symb, ostream &out) {
    if (buff_ind + sizeof(symb) >= BUFF_SIZE) {
        out.write((char *)buffer_out, buff_ind);
        buff_ind = 0;
    }
    memcpy(buffer_out + buff_ind, &symb, sizeof(symb));
    buff_ind += sizeof(symb);
    stream += 8 * sizeof(symb);
}

vector<pair<uint, char>> get_codes(const vector<uint> &cnt) {

    vector<pair<uint, uint>> pr(2 * A_SIZE, { 0, 0 });
    vector<pair<uint, char>> res(A_SIZE);
    priority_queue<pair<uint, uint>, vector<pair<uint, uint>>, greater<>> q;
    for(size_t ind = 0; ind < A_SIZE; ++ind) {
        q.push({ cnt[ind], ind });
    }
    uint cur_ind = A_SIZE;
    while(q.size() > 1) {
        auto fst = q.top();
        q.pop();
        auto scd = q.top();
        q.pop();
        pr[fst.second] = { cur_ind, 0 };
        pr[scd.second] = { cur_ind, 1 };
        q.push({ fst.first + scd.first, cur_ind++ });
    }

    vector<uint> code;
    for(size_t ind = 0; ind < A_SIZE; ++ind) {
        code.clear();
        for(size_t j = ind; pr[j].first; j = pr[j].first) {
            code.push_back(pr[j].second);
        }
        reverse(code.begin(), code.end());
        uint line = 0;
        for(size_t j = 0; j < code.size(); ++j)
            line += (code[j] << j);
        res[ind] = { line, (char)code.size() };
    }

    return res;
}
