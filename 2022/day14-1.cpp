// -*- compile-command: "make d14" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

const int maxN = 700;
const int startX = 500;

vector<array<int,2>> to_points(string line) {
    vector<string> parts;
    split(line, parts, " -> ");
    vector<array<int,2>> res;
    for (auto& p : parts) {
        array<int,2> point = {0, 0};
        int j = 0;
        for (char const &c: p) {
            if (c == ',') ++j;
            else point[j] = 10*point[j] + (c-'0');
        }
        res.push_back(point);
    }
    return res;
}

int sign(int v) {
    return (0 < v) - (v < 0);
}

int main(int argc, char *argv[]) {
    vector<vector<char>> g(maxN, vector<char>(maxN, '.'));
    string line;
    int idx = 0;
    while (getline(cin, line)) {
        auto ps = to_points(line);
        int n = ps.size();
        for (int i = 1; i < n; ++i) {
            auto [x, y] = ps[i-1];
            auto [ex, ey] = ps[i];
            int dx = sign(ex - x),
                dy = sign(ey - y);
            while (!(x == ex && y == ey)) {
                g[y][x] = '#';
                x += dx;
                y += dy;
            }
            g[y][x] = '#';
        }
        ++idx;
    }

    int res = 0;
    bool done = false;
    while (!done) {
        array<int,2> p = {0, startX};
        while (true) {
            auto& [y, x] = p;
            if (y+1 >= maxN || g[y][x] == 'o') {
                done = true;
                break;
            }
            if (g[y+1][x] == '.') ++y;
            else if (x > 0 && g[y+1][x-1] == '.') ++y, --x;
            else if (x < maxN-1 && g[y+1][x+1] == '.') ++y, ++x;
            else {
                g[y][x] = 'o';
                ++res;
                break;
            }
        }
    }

    // cout << endl;
    // for (int i = 0; i < 20; ++i) {
    //     for (int j = 470; j < 510; ++j) {
    //         cout << g[i][j];
    //     }
    //     cout << endl;
    // }

    cout << res << '\n';
    return 0;
}
