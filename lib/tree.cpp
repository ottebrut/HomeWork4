#include <vector>
#include <iostream>
#include "tree.h"

tree::tree(const vector<pair<uint, char> > &code) {
    for(size_t ind = 0; ind < code.size(); ++ind) {
        insert(code[ind], ind);
    }
}

tree::~tree() {
    for(auto v : vals) {
        delete v;
    }
}

void tree::insert(const pair<uint, char> &point, uchar val) {
    val_ *v = root;
    for(size_t ind = 0; ind < point.second; ++ind) {
        uint c = ((point.first >> ind) & 1u);
        if ((!c && !v->l) || (c && !v->r)) {
            if (!c) {
                v->l = new val_();
                vals.push_back(v->l);
            } else {
                v->r = new val_();
                vals.push_back(v->r);
            }
        }
        v = (!c ? v->l : v->r);
    }
    v->val = val;
}

bool tree::go(const uint &point) {
    cur = (!point ? cur->l : cur->r);
    return (cur != 0);
}

bool tree::end() {
    return (cur->l == 0);
}

uchar tree::get() {
    val_ *tmp = cur;
    cur = root;
    return tmp->val;
}
