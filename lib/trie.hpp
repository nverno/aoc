#pragma once

#include <array>
#include <algorithm>
#include <string>

template<typename T>
struct Trie {
    bool leaf;
    char offset;
    T val;
    std::array<Trie*,26> ch;

    Trie(char off = 'A'): leaf(false), offset(off) {
        std::fill(ch.begin(), ch.end(), nullptr);
    }

    void add(std::string& s, T v) {
        Trie *ptr = this;
        for (char const &c: s) {
            if (!ptr->ch[c-offset])
                ptr->ch[c-offset] = new Trie<T>(offset);
            ptr = ptr->ch[c-offset];
        }
        ptr->leaf = true;
        ptr->val = v;
    }

    Trie *lookup(std::string s) {
        Trie *ptr = this;
        for (char const &c: s) {
            if (!ptr->ch[c-offset]) break;
            ptr = ptr->ch[c-offset];
        }
        return ptr->leaf ? ptr : nullptr;
    }
};
