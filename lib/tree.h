#ifndef TREE_HPP
#define TREE_HPP

#include <vector>

typedef unsigned int uint;
typedef unsigned char uchar;

using namespace std;

class tree {
public:
    tree(const vector<pair<uint, char>> &code);
    ~tree();

    void insert(const pair<uint, char> &point, uchar val);
    bool go(const uint &point);
    bool end();
    uchar get();

private:
    struct val_ {
        uchar val = 0;
        val_ *l = 0, *r = 0;
    };
    val_ *root = new val_();
    val_ *cur = root;
    vector<val_ *> vals = { root };

};

#endif
