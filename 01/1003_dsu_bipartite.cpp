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
    T ans = 1;
    while (n) {
        if (n & 1) ans *= a;
        if (n > 1) a *= a;
        n >>= 1;
    }
    return ans;
}

void precompute() {}

struct dsu_bipartite {
    
    int n;
    vector<int> rank, bipartite;
    vector<pair<int, int>> parent;

    dsu_bipartite(int n) {
        this->n = n;
        rank.assign(n, 0);
        bipartite.assign(n, 1);
        parent.reserve(n);
        for (int i = 0; i < n; ++i)
            parent.emplace_back(i, 0);
    }

    pair<int, int> find_set(int v) {
        if (v != parent[v].first) {
            int parity = parent[v].second;
            parent[v] = find_set(parent[v].first);
            parent[v].second ^= parity;
        }
        return parent[v];
    }

    void add_edge(int a, int b) {
        int x, y;
        tie(a, x) = find_set(a);
        tie(b, y) = find_set(b);
        if (a == b) {
            if (x == y) bipartite[a] = false;
        } else {
            if (rank[a] < rank[b]) swap(a, b);
            parent[b] = make_pair(a, x ^ y ^ 1);
            bipartite[a] &= bipartite[b];
            if (rank[a] == rank[b]) ++rank[a];
        }
    }

    bool is_bipartite(int v) { return bipartite[find_set(v).first]; }
};

void solve(int) {
    
    int n;
    
    while (true) {

        cin >> n;
        if (n == -1) break;

        int m;
        cin >> m;

        map<int, int> vertices;
        vector<tuple<int, int, int>> queries;
        queries.reserve(m);

        for (int i = 0; i < m; ++i) {
            int u, v;
            string s;
            cin >> u >> v >> s;
            --u;
            vertices[u] = 0;
            vertices[v] = 0;
            queries.emplace_back(u, v, (s[0] == 'o'));
        }

        int dsu_size = 0;

        int id = 0;
        for (auto &[v, v_id] : vertices)
            v_id = id++;
        dsu_size = id + m;

        dsu_bipartite dsu(dsu_size);

        int ans = 0;

        // vertices corresponding to prefix sums and dummy vertices
        // edge between two vertices u, v if prefix sums of u and v
        // have different parities
        // need to check if this is bipartite

        for (auto &[u, v, parity] : queries) {

            int u_id = vertices[u];
            int v_id = vertices[v];

            if (parity == 0) {
                dsu.add_edge(u_id, id);
                dsu.add_edge(v_id, id);
                id++;
            } else {
                dsu.add_edge(u_id, v_id);
            }

            if (!dsu.is_bipartite(u_id)) {
                break;
            }

            ans++;
        }

        cout << ans << '\n';
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
