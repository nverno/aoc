// -*- compile-command: "make d23" -*-
#include <bits/stdc++.h>
#include "../lib/aoc.hpp"
using namespace std;

const int dirs[8][2] = {
    {-1,-1},{-1,0},{-1,1},
    {0,-1}, /*  */ {0,1},
    {1,-1}, {1,0}, {1,1}
};
// N,S,W,E
int dinds[4][3] = {{0,1,2}, {5,6,7}, {0,3,5}, {2,4,7}};

int main(int argc, char *argv[]) {
    set<pair<int,int>> elves;
    string line;
    int row = 0;
    while (getline(cin, line)) {
        for (int j = 0; j < (int)line.size(); ++j) 
            if (line[j] == '#') elves.insert({row, j});
        ++row;
    }

    auto should_move = [&](pair<int,int> e) {
        auto [i, j] = e;
        for (auto& d : dirs) {
            int x = i + d[0], y = j + d[1];
            if (elves.count({x, y})) return true;
        }
        return false;
    };

    auto is_open = [&](pair<int,int> e, int dir) -> pair<bool,pair<int,int>> {
        auto [i,j] = e;
        for (auto& idx : dinds[dir]) {
            auto& d = dirs[idx];
            int x = i + d[0], y = j + d[1];
            if (elves.count({x, y})) return {false, {}};
        }
        auto [x, y] = dirs[dinds[dir][1]];
        return {true, {i+x, j+y}};
    };

    int idx = 0, nround = 10, sz = elves.size();
    while (nround--) {
        set<pair<int,int>> nxt;
        map<pair<int,int>,vector<pair<int,int>>> proposed;
        for (auto& e : elves) {
            if (!should_move(e)) {
                nxt.insert(e);
                continue;
            }
            int d = idx, done = 0;
            do {
                auto [ok, pos] = is_open(e, d);
                if (ok) {
                    proposed[pos].push_back(e);
                    done = 1;
                }
                d = (d + 1) % 4;
            } while (!done && d != idx);
            if (!done) 
                nxt.insert(e);
        }
        for (auto& [k,v] : proposed) {
            if (v.size() == 1)
                nxt.insert(k);
            else for (auto& e : v) nxt.insert(e);
        }
        idx = (idx + 1) % 4;
        swap(nxt, elves);
        assert((int)elves.size() == sz);

        // cout << "== End of Round " << 10 - nround << " ==\n";
        // vector<string> grid(15, string(15, '.'));
        // for (auto& [x,y] : elves) 
        //     grid[x+3][y+3] = '#';
        // for (auto& r : grid) {
        //     cout << r << '\n';
        // }
        // cout << '\n';
    }

    int mx[2] = {INT_MAX,INT_MIN}, my[2] = {INT_MAX,INT_MIN};
    for (auto& e : elves) {
        mx[0] = min(mx[0], e.first);
        mx[1] = max(mx[1], e.first);
        my[0] = min(my[0], e.second);
        my[1] = max(my[1], e.second);
    }

    cout << (1 + mx[1] - mx[0]) * (1 + my[1] - my[0]) - elves.size() << '\n';
    return 0;
}
