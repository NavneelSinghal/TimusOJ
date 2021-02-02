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
   
    // wlog assume s < t
    // claim: shortest paths always completely lie to the left of a point
    // proof: induction -
    //        for first element done
    //        suppose we are at the ith element
    //        consider the previous point on the path
    //        if on the left, done
    //        if on the right, then there is a portion of the path
    //        which is on the right, and the remaining portion has a nonempty
    //        intersection with the left part, since it starts from the first element
    //        hence, we can replace the whole portion by a single jump since
    //        l and c are both increasing, so we have a contradiction to minimality
    //        thus we are done
    // using this by noting that travel is bidirectional, we can see that
    // the path is always completely between s and t
    
    int l1, l2, l3;
    cin >> l1 >> l2 >> l3;
    int c1, c2, c3;
    cin >> c1 >> c2 >> c3;

    int n;
    cin >> n;

    int s, t;
    cin >> s >> t;
    if (s > t) swap(s, t);
    --s, --t;

    vector<int> d(n);
    for (int i = 1; i < n; ++i)
        cin >> d[i];

    const int inf = (int)1e9 + 1;
    
    vector<int> cost(n, inf);
    cost[s] = 0;
    
    // O(n^2)
    // for (int i = s; i <= t; ++i) {
    //     for (int j = i - 1; j >= s; --j) {
    //         if (d[i] - d[j] <= l1) {
    //             remin(cost[i], cost[j] + c1);
    //         } else if (d[i] - d[j] <= l2) {
    //             remin(cost[i], cost[j] + c2);
    //         } else if (d[i] - d[j] <= l3) {
    //             remin(cost[i], cost[j] + c3);
    //         } else {
    //             break;
    //         }
    //     }
    // }

    // claim: cost is monotonically increasing
    // proof: suppose not
    //        then we have for some a that cost[a + 1] < cost[a]
    //        the previous point on the path for a + 1 can't be a
    //        as otherwise we have a better path for a anyway
    //        hence if the last point is something before a
    //        then we have a better path to a by simply replacing
    //        the last path in the path to a + 1 with the path to a
    
    int ptr1 = s, ptr2 = s, ptr3 = s;
    for (int i = s + 1; i <= t; ++i) {
        while (d[ptr1] + l1 < d[i]) ++ptr1;
        while (d[ptr2] + l2 < d[i]) ++ptr2;
        while (d[ptr3] + l3 < d[i]) ++ptr3;
        remin(cost[i], cost[ptr1] + c1);
        remin(cost[i], cost[ptr2] + c2);
        remin(cost[i], cost[ptr3] + c3);
    }
    
    cout << cost[t] << '\n';
    
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
