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

long long merge_inversions(vector<int>& a, int l, int m, int r, vector<int>& b) {
    int i = l, j = m, k = l;
    long long cnt = 0;
    while (i < m && j <= r) {
        if (a[i] <= a[j]) {
            b[k++] = a[i++];
        } else {
            b[k++] = a[j++];
            cnt += m - i;
        }
    }
    while (i < m)
        b[k++] = a[i++];
    while (j <= r)
        b[k++] = a[j++];
    copy(b.begin() + l, b.begin() + r + 1, a.begin() + l);
    return cnt;
}

long long count_inversions(vector<int>& a, int l, int r, vector<int>& b) {
    
    if (l == r) return 0LL;
    int m = l + (r - l) / 2;
    
    long long ans = count_inversions(a, l, m, b);
    ans += count_inversions(a, m + 1, r, b);
    ans += merge_inversions(a, l, m + 1, r, b);

    return ans;
}

void solve(int) {
    
    int n, k;
    cin >> n >> k;
    
    vector<long long> ans(k);
    for (int kk = 0; kk < k; ++kk) {
        vector<int> a(n);
        for (auto &x : a) cin >> x;
        vector<int> b = a;
        ans[kk] = count_inversions(a, 0, n - 1, b);
    }

    long long max_ans = *max_element(begin(ans), end(ans));
    for (int i = 0; i < k; ++i) {
        if (max_ans == ans[i]) {
            cout << i + 1 << '\n';
            return;
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
