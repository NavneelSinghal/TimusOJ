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

    int m, n;
    cin >> m >> n;
    vector<vector<int>> a(m, vector<int>(n));
    
    for (auto &x : a)
        for (auto &y : x)
            cin >> y;

    auto compress = [&] (int i, int j) {
        return 1 + i * n + j;
    };

    auto decompress = [&] (int ij) {
        if (ij == 0) return make_pair(-1, -1);
        ij--;
        return make_pair(ij / n, ij % n);
    };

    vector<vector<pair<int, long long>>> g(m * n + 1);

    for (int j = 0; j < n; ++j) {
        g[0].emplace_back(compress(m - 1, j), a[m - 1][j]);
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            auto ij = compress(i, j);
            if (i - 1 >= 0)
                g[ij].emplace_back(compress(i - 1, j), a[i - 1][j]);
            if (j - 1 >= 0)
                g[ij].emplace_back(compress(i, j - 1), a[i][j - 1]);
            if (j + 1 < n)
                g[ij].emplace_back(compress(i, j + 1), a[i][j + 1]);
        }
    }

    // dijkstra
    const long long inf = 1e18;
    vector<long long> d(m * n + 1, inf);
    vector<int> p(m * n + 1, -1);
    d[0] = 0;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> q;
    q.emplace(0LL, 0);
    while (!q.empty()) {
        auto [dv, v] = q.top();
        q.pop();
        if (dv != d[v]) {
            continue;
        }
        for (auto &[u, w] : g[v]) {
            if (d[u] > dv + w) {
                d[u] = dv + w;
                p[u] = v;
                q.emplace(d[u], u);
            }
        }
    }

    long long min_d = inf, best_index = -1;
    for (int j = 0; j < n; ++j) {
        int ord = compress(0, j);
        if (min_d > d[ord]) {
            best_index = ord;
            min_d = d[ord];
        }
    }

    vector<pair<int, int>> path;
    while (best_index != -1) {
        path.push_back(decompress(best_index));
        best_index = p[best_index];
    }

    path.pop_back();
    for (auto &[u, v] : path) cout << v + 1 << '\n';

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
