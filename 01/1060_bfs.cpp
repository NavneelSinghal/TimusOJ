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

    vector<string> a(4);
    for (auto &x : a) cin >> x;
    
    vector<pair<int, int>> dirs = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

    auto check = [&] (int i, int j) {
        return 0 <= i && i < 4 && 0 <= j && j < 4;
    };

    auto compute_mask = [&] (int i, int j) {
        return 1 << (i * 4 + j);
    };

    vector<int> masks;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int m = compute_mask(i, j);
            for (auto &[dx, dy] : dirs) {
                if (check(i + dx, j + dy)) {
                    m |= (compute_mask(i + dx, j + dy));
                }
            }
            masks.push_back(m);
        }
    }

    int x = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            x |= (1 << (i * 4 + j)) * (a[i][j] == 'b');
        }
    }

    const int t1 = 0, t2 = (1 << 16) - 1;

    const int inf = INT_MAX; 
    
    queue<int> q;
    vector<int> d(1 << 16, inf);
    
    q.push(x);
    d[x] = 0;
    
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        if (v == t1 || v == t2) {
            cout << d[v] << '\n';
            return;
        }
        for (auto nxt : masks) {
            if (d[v ^ nxt] == inf) {
                q.push(v ^ nxt);
                d[v ^ nxt] = d[v] + 1;
            }
        }
    }

    cout << "Impossible\n";

    return;
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
