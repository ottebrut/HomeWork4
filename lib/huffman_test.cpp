#include <iostream>
#include <random>
#include "huffman.h"
#include "gtest/gtest.h"

using namespace std;

TEST(correctness, empty) {
    stringstream in(""), code, out;
    compressor(in, code);
    decompressor(code, out);
    EXPECT_EQ(in.str(), out.str());
}

TEST(correctness, one_char) {
    stringstream in("a"), code, out;
    compressor(in, code);
    decompressor(code, out);
    EXPECT_EQ(in.str(), out.str());
}


TEST(correctness, alphabet) {
    stringstream in("abcdefghijklmnopqrstuvwxyz"), code, out;
    compressor(in, code);
    decompressor(code, out);
    EXPECT_EQ(in.str(), out.str());
}

TEST(correctness, all_chars) {
    stringstream in, code, out;
    for (int i = -128; i < 128; i++) {
        in << (char)i;
    }
    compressor(in, code);
    decompressor(code, out);
    EXPECT_EQ(in.str(), out.str());
}

static const int MAXLEN = 10 * 1024 * 1024;

TEST(correctness, big_text) {
    stringstream in, code, out;
    mt19937 rnd(1);
    for (int i = 0; i < MAXLEN; i++) {
        in << (char)rnd() % 256;
    }
    compressor(in, code);
    decompressor(code, out);
    EXPECT_EQ(in.str(), out.str());
}

TEST(corectness, invalid_file) {
    stringstream code("dafhk41 41"), out;
    EXPECT_FALSE(decompressor(code, out));
}


TEST(correctness, one_char_text) {
    stringstream in, code, out;
    mt19937 rnd(1);
    for (int i = 0; i < MAXLEN; i++) {
        in << 'a';
    }
    compressor(in, code);
    decompressor(code, out);
    EXPECT_EQ(in.str(), out.str());
}


TEST(correctness, two_chars_text) {
    stringstream in, code, out;
    mt19937 rnd(1);
    for (int i = 0; i < MAXLEN; i++) {
        in << (char)('a' + rnd() % 2);
    }
    compressor(in, code);
    decompressor(code, out);
    EXPECT_EQ(in.str(), out.str());
}


TEST(correctness, compressor_compressored) {
    stringstream in, code1, code2, out2, out;
    mt19937 rnd(1);
    for (int i = 0; i < MAXLEN; i++) {
        in << (char)(rnd() % 256);
    }
    compressor(in, code1);
    compressor(code1, code2);
    decompressor(code2, out2);
    decompressor(out2, out);
    EXPECT_EQ(in.str(), out.str());
}
