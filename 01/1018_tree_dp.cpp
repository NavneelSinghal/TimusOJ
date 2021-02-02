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
    
    int n, q;
    cin >> n >> q;
    
    // dp[v][k] = max possible apples preserved when we remove k branches from the subtree of v
    // sz[v] = size of subtree of v (= number of edges in subtree of v + 1)
    
    vector<vector<pair<int, int>>> g(n);
    for (int i = 1; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    vector<int> sz(n);
    vector<vector<int>> dp(n, vector<int>(n + 1));

    function<void(int, int)> dfs = [&] (int v, int p) {

        sz[v] = 1;
        for (auto &[u, w] : g[v]) {
            if (u == p) continue;
            dfs(u, v);
            sz[v] += sz[u];
        }

        if (sz[v] == 1) {
            dp[v][0] = 0;
            return;
        }

        vector<int> children;
        vector<int> weights;
        for (auto &[u, w] : g[v]) {
            if (u != p) {
                children.push_back(u);
                weights.push_back(w);
            }
        }

        assert(children.size() == 2);
        int u1 = children[0], u2 = children[1];
        int w1 = weights[0], w2 = weights[1];

        // u1 and u2 are children (!= p)
        // w1 and w2 are weights corresponding to them
        for (int i = 0; i < sz[v]; ++i) {
            
            for (int j1 = 0, j2 = i; j1 <= i; ++j1, --j2) {

                // remove j1 from the left, j2 from the right
                // remove connecting branch - left
                if (j1 == sz[u1] && j2 < sz[u2]) {
                    remax(dp[v][i], dp[u2][j2] + w2);
                }

                // remove connecting branch - right
                if (j2 == sz[u2] && j1 < sz[u1]) {
                    remax(dp[v][i], dp[u1][j1] + w1);
                }

                // remove connecting branch - both
                if (j2 == sz[u2] && j1 == sz[u1]) {
                    remax(dp[v][i], 0);
                }

                // remove connecting branch - none
                if (j1 < sz[u1] && j2 < sz[u2]) {
                    remax(dp[v][i], dp[u1][j1] + dp[u2][j2] + w1 + w2);
                }
            }
            
        }
    };

    dfs(0, -1);
    cout << dp[0][n - q - 1] << '\n';
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
