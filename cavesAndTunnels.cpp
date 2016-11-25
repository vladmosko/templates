#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cassert>
#include <cstdio>
#include <queue>
#include <set>
#include <map>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <algorithm>
#include <numeric>
 
#define mt make_tuple
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)(x).size())
#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define range(i, x, y) for (int i = x; i < y; i++)
#define rrange(i, x, y) for (int i = y - 1; i >= x; i--)
 
using namespace std;
 
typedef double db;
typedef long long i64;
typedef long double ld;
 
typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<i64> vi64;
typedef vector<vi64> vvi64;
 
template<typename T, typename S> inline bool upmin(T &a, const S &b) {
    return a > b ? a = b, true : false;
}
template<typename T, typename S> inline bool upmax(T &a, const S &b) {
    return a < b ? a = b, true : false;
}
 
const int maxn = 1e5 + 5;
 
int timer;
int up[maxn][18];
int tin[maxn];
int tout[maxn];
int depth[maxn];
int subtree[maxn];
bool heavy[maxn];
int whichChain[maxn];
int whichPosition[maxn];
int val[maxn];
bool assigned[maxn];
vpii h;
vi g[maxn];
 
void dfs(int v, int pr) {
    tin[v] = ++timer;
    depth[v] = depth[pr] + 1;
    subtree[v] = 1;
    h.pb(mp(depth[v], v));
    up[v][0] = pr;
    for (int i = 1; i < 17; i++) up[v][i] = up[up[v][i - 1]][i - 1];
    for (auto child: g[v]) {
        if (child == pr) continue;
        dfs(child, v);
        subtree[v] += subtree[child];
    }
    for (auto child: g[v]) {
        if (child == pr) continue;
        if (subtree[child] * 2 > subtree[v]) heavy[child] = true;
    }
    tout[v] = ++timer;
}
 
struct SegmentTree {
    vector<int> data;
 
    void initialize(int n) {
        data.assign(8 * n, 0);
    }
 
    void modify(int x, int l, int r, int p, int v) {
        if (l == r) data[x] += v;
        else {
            int mid = (l + r) / 2;
            if (p <= mid) modify(x + x, l, mid, p, v);
            else modify(x + x + 1, mid + 1, r, p, v);
            data[x] = max(data[x + x], data[x + x + 1]);
        }
    }
 
    int query(int x, int l, int r, int ql, int qr) {
        if (l == ql && r == qr) return data[x];
        else {
            int mid = (l + r) / 2;
            if (qr <= mid) return query(x + x, l, mid, ql, qr);
            else if (ql > mid) return query(x + x + 1, mid + 1, r, ql, qr);
            else {
                int s1 = query(x + x, l, mid, ql, mid);
                int s2 = query(x + x + 1, mid + 1, r, mid + 1, qr);
                return max(s1, s2);
            }
        }
    }
};
 
vvi chains;
vector<SegmentTree> hld;
 
void createChains() {
    sort(all(h));
    while (!h.empty()) {
        int v = h.back().se;
        h.pop_back();
        if (assigned[v]) continue;
        vi newChain;
        while (true) {
            assigned[v] = true;
            newChain.pb(v);
            if (!heavy[v]) break;
            if (v == 0) break;
            v = up[v][0];
        }
        reverse(all(newChain));
        chains.emplace_back(newChain);
    }
    forn(i, sz(chains)) {
        forn(j, sz(chains[i])) {
            whichChain[chains[i][j]] = i;
            whichPosition[chains[i][j]] = j;
        }
        SegmentTree newSegmentTree;
        newSegmentTree.initialize(sz(chains[i]));
        hld.emplace_back(newSegmentTree);
    }
}
 
inline bool upper(int x, int y) {
    return tin[x] <= tin[y] && tout[x] >= tout[y];
}
 
int lca(int x, int y) {
    if (upper(x, y)) return x;
    if (upper(y, x)) return y;
    for (int i = 16; i >= 0; i--) {
        if (!upper(up[x][i], y)) x = up[x][i];
    }
    return up[x][0];
}
 
int sumUp(int u, int v) {
    assert(upper(v, u));
    int s = val[u];
    while (true) {
        if (u == v) break;
        int ch = whichChain[u], ps = whichPosition[u];
        if (!heavy[u] || (heavy[u] && ps == 0)) {
            u = up[u][0];
            s = max(s, val[u]);
            continue;
        }
        int jumpV = depth[u] - depth[v];
        int heavyJump = ps;
        int gonnaJump = min(jumpV, heavyJump);
        s = max(s, hld[ch].query(1, 0, sz(chains[ch]) - 1, ps - gonnaJump, ps - 1));
        u = chains[ch][ps - gonnaJump];
    }
    return s;
}
 
int main() {
    int n;
    scanf("%d", &n);
    forn(i, n - 1) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        g[u].pb(v);
        g[v].pb(u);
    }
    forn(i, n) whichChain[i] = -1;
    dfs(0, 0);
    createChains();
    int queries;
    scanf("%d", &queries);
    while (queries--) {
        char tp;
        int foo, bar;
        scanf(" %c%d%d", &tp, &foo, &bar);
        foo--;
        if (tp == 'I') {
            val[foo] += bar;
            int q = whichChain[foo];
            if (~q) hld[q].modify(1, 0, sz(chains[q]) - 1, whichPosition[foo], bar);
        } else {
            bar--;
            int l = lca(foo, bar);
            printf("%d\n", max(sumUp(foo, l), sumUp(bar, l)));
        }
    }
    return 0;
}
