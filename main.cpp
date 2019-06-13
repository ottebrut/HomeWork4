#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include "lib/huffman.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 4 || ((string)argv[1] != "-c" && (string)argv[1] != "-d")) {
        cerr << "Use the next pattern: <./huffman> <-c | -d> <input> <output>\n";
        return 0;
    }
    ifstream in((string)argv[2], ifstream::binary);
    ofstream out((string)argv[3], ofstream::binary);
    if (!in.is_open() || !out.is_open()) {
        cerr << "Invalid files\n";
        return 0;
    }
    if ((string)argv[1] == "-c") {
        compressor(in, out);
    } else {
        if (!decompressor(in, out)) {
            cout << "Invalid file for decompression\n";
            return 0;
        }
    }
    return 0;
}
