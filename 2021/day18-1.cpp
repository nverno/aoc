// -*- compile-command: "make d18" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
#include "../lib/tree.hpp"
using namespace std;
using Tree = Node<int>;

// [[[a,b]].[d,e]...]
Tree *treeFromList(std::string& line) {
    Tree *prev = nullptr, *res = nullptr;
    std::stack<Tree*> st;
    for (size_t i = 0; i < line.size(); ++i) {
        if (line[i] == ',') continue;
        if (line[i] == '[') {
            if (st.empty()) st.push(new Tree());
            else st.push(st.top()->append());
        }
        else if (line[i] == ']') res = st.top(), st.pop();
        else {
            assert(isdigit(line[i]));
            Tree *nxt = st.top()->append(line[i]-'0');
            nxt->left = prev;
            if (prev) prev->right = nxt;
            prev = nxt;
        }
    }
    return res;
}

Tree *explode(Tree *t) {
    assert(t->leaf && t->depth >= 4);
    auto [l, r] = t->getPair();
    assert(l->leaf && r->leaf);
    if (l->left) l->left->val += l->val;
    if (r->right) r->right->val += r->val;
    Tree *res = l->parent;
    res->left = l->left;
    res->right = r->right;
    res->val = 0;
    res->leaf = true;
    if (l->left) l->left->right = res;
    if (r->right) r->right->left = res;
    free(l); free(r);
    return res;
}

Tree *split(Tree *t) {
    assert(t->leaf && t->val >= 10);
    Tree *l = t->left, *r = t->right;
    t->left = new Tree(t->val/2, t, l);
    t->right = new Tree((1+t->val)/2, t, t->left, r);
    t->left->right = t->right;
    if (l) l->right = t->left;
    if (r) r->left = t->right;
    t->leaf = false;
    return t->left;
}

Tree *reduce(Tree *hd) {
    Tree *ptr = hd;
    while (ptr) {
        if (ptr->depth > 4) {
            Tree *nxt = explode(ptr);
            assert(nxt);
            if (ptr == hd) hd = nxt;
            ptr = nxt;
        } else ptr = ptr->right;
    }
    ptr = hd;
    while (ptr) {
        if (ptr->val >= 10) {
            Tree *nxt = split(ptr);
            if (ptr == hd) hd = nxt;
            return reduce(hd);
        } else ptr = ptr->right;
    }
    return hd;
}

Tree *join(Tree *l, Tree *hd, Tree *r) {
    Tree *res = new Tree(nullptr, l, r);
    l->parent = r->parent = res;
    res->updateDepth();
    while (hd && hd->right) hd = hd->right;
    Tree *rhd = r;
    while (rhd && rhd->left) rhd = rhd->left;
    rhd->left = hd;
    hd->right = rhd;
    return res;
}

void printList(Tree *hd) {
    cout << "list: ";
    while (hd && hd->right) {
        cout << hd->val << ",";
        hd = hd->right;
    }
    cout << hd->val << endl;
}

int magnitude(Tree *t) {
    if (!t) return 0;
    if (t->leaf) return t->val;
    return 3*magnitude(t->left) + 2*magnitude(t->right);
}

int main(int argc, char *argv[]) {
    string line;
    getline(cin, line);
    Tree *tree = treeFromList(line), *hd = tree;
    while (hd && hd->left) hd = hd->left;

    while (getline(cin, line)) {
        Tree *nxt = treeFromList(line);
        cout << tree << endl;
        cout << "+ " << nxt << "\n= ";
        tree = join(tree, hd, nxt);
        hd = reduce(hd);
        cout << tree << endl;
    }

    cout << tree << endl;
    cout << magnitude(tree) << endl;
    return 0;
}
