// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx")
// #pragma GCC optimize("unroll-loops")

#include "bits/stdc++.h"
#include "ext/pb_ds/assoc_container.hpp"
#include "ext/pb_ds/tree_policy.hpp"

using namespace __gnu_pbds;
using namespace std;

template <typename X, typename Y>
X &remin(X &x, const Y &y) {
    return x = (y < x) ? y : x;
}

template <typename X, typename Y>
X &remax(X &x, const Y &y) {
    return x = (x < y) ? y : x;
}

template <typename X, typename Y>
[[nodiscard]] bool ckmin(X &x, const Y &y) {
    return (y < x) ? (x = y, 1) : 0;
}

template <typename X, typename Y>
[[nodiscard]] bool ckmax(X &x, const Y &y) {
    return (x < y) ? (x = y, 1) : 0;
}

template <typename T>
void ignore_unused(const T &) {}

void setIO(string name = "") {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout << setprecision(10) << fixed;
    if (name.size() == 0) return;
    FILE *fin = freopen((name + ".in").c_str(), "r", stdin);
    FILE *fout = freopen((name + ".out").c_str(), "w", stdout);
    ignore_unused(fin);
    ignore_unused(fout);
}

// constexpr int mod = 998244353;
constexpr int mod = 1e9 + 7;
constexpr int64_t linf = 3e18;
constexpr long double pi = acosl(-1.0);

[[nodiscard]] int64_t pwr_mod(int64_t a, int64_t n) {
    int64_t ans = 1;
    while (n) {
        if (n & 1) ans = (ans * a) % mod;
        a = (a * a) % mod;
        n >>= 1;
    }
    return ans;
}

// when using integers, keep overflow in mind
template <typename T>
T pwr(T a, int64_t n) {
    T ans(1);
    while (n) {
        if (n & 1) ans *= a;
        if (n > 1) a *= a;
        n >>= 1;
    }
    return ans;
}

template <typename T>
inline T sq(T a) {
    return a * a;
}

template <typename T>
inline T sq_dist(pair<T, T>& a, pair<T, T>& b) {
    return sq(a.first - b.first) + sq(a.second - b.second);
}

template <typename T>
inline long double dist(pair<T, T>& a, pair<T, T>& b) {
    return sqrtl(sq_dist(a, b));
}

inline long long isqrt(long long n) {
    long long sq = (long long)sqrtl((long double)n) - 2;
    sq = max(sq, 0LL);
    while (sq * sq < n) sq++;
    if ((sq * sq) == n) return sq;
    return sq - 1;
}

inline bool is_sq(int n) {
    int w = isqrt(n);
    return w * w == n;
}

void precompute() {
}

void solve(int) {

    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;

    map<pair<int, int>, char> mp;
    mp[make_pair(1, 0)] = 'R';
    mp[make_pair(0, 1)] = 'T';
    mp[make_pair(-1, 0)] = 'L';
    mp[make_pair(0, -1)] = 'B';

    map<char, pair<int, int>> pm;
    pm['R'] = {1, 0};
    pm['T'] = {0, 1};
    pm['L'] = {-1, 0};
    pm['B'] = {0, -1};

    string dirs = "RTLB";

    vector<vector<int>> grid(12, vector<int>(12));
    if (s.find(",") == string::npos && s.find(".") == string::npos) {
    
        int x, y;
        x = m;
        y = stoi(s);
        int startx = x, starty = y;
        grid[x][y] = 1;
        for (int i = 1; i < n; ++i) {
            cin >> x >> y;
            grid[x][y] = 1;
        }
        
        queue<pair<int, int>> q;
        vector<vector<int>> visited(12, vector<int>(12));
        
        q.emplace(startx, starty);
        visited[startx][starty] = 1;
        
        cout << startx << ' ' << starty << '\n';

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            for (char c : dirs) {
                auto [dx, dy] = pm[c];
                if (!visited[x + dx][y + dy] && grid[x + dx][y + dy]) {
                    visited[x + dx][y + dy] = 1;
                    q.emplace(x + dx, y + dy);
                    cout << mp[make_pair(dx, dy)];
                }
            }
            if (!q.empty()) cout << ",\n";
            else cout << ".\n";
        }

    } else {
        int x = n, y = m;
        queue<pair<int, int>> q;
        grid[x][y] = 1;
        bool ended = false;
        for (auto c : s) {
            if (c != '.' && c != ',') {
                auto [xx, yy] = make_pair(x + pm[c].first, y + pm[c].second);
                q.emplace(xx, yy);
                grid[xx][yy] = 1;
            } else if (c == '.') {
                ended = true;
            }
        }
        
        auto print_grid = [&]() {
            int ans = 0;
            for (int i = 0; i < 12; ++i) {
                for (int j = 0; j < 12; ++j) {
                    ans += grid[i][j];
                }
            }
            cout << ans << '\n';
            for (int i = 0; i < 12; ++i) {
                for (int j = 0; j < 12; ++j) {
                    if (grid[i][j]) {
                        cout << i << ' ' << j << '\n';
                    }
                }
            }
        };

        if (ended) {
            print_grid();
        } else {
            while (!ended && !q.empty()) {
                cin >> s;
                tie(x, y) = q.front();
                q.pop();
                for (auto c : s) {
                    if (c != '.' && c != ',') {
                        auto [xx, yy] = make_pair(x + pm[c].first, y + pm[c].second);
                        q.emplace(xx, yy);
                        grid[xx][yy] = 1;
                    } else if (c == '.') {
                        ended = true;
                    }
                }
            }
            print_grid();
        }
    }
}

void brute(int) {}

signed main() {
    setIO();
    precompute();
    int t = 1;
    // cin >> t;
    for (int _t = 1; _t <= t; _t++) {
        // cout << "Case #" << _t << ": ";
        solve(_t);
        // brute(_t);
    }
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n = 1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
