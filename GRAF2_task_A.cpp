#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")


#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <queue>
#include <math.h>
#include <set>
#include <fstream>
using namespace std;
using ll = long long;
using ull = unsigned long long;
vector<vector<pair<ll, ll>>> g;
vector<ll>mt;
vector<ll>last_used;
ll version = 1;
bool try_(ll v, ll mid) {
    if (last_used[v] == version) return 0;
    last_used[v] = version;
    for (pair<ll, ll> u : g[v]) {
        if (u.first < mid) break;
        if (mt[u.second] == -1) {
            mt[u.second] = v;
            return 1;
        }
        if (try_(mt[u.second], mid)) {
            mt[u.second] = v;
            return 1;
        }
    }
    return 0;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll n, m;
    cin >> n >> m;
    last_used.resize(max(n, m));
    mt.resize(m);
    g.resize(n);
    ll k;
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            cin >> k;
            g[i].push_back({k, j});
        }
        sort(g[i].rbegin(), g[i].rend());
    }
    last_used.assign(n, 0);
    mt.assign(m, -1);
    version = 1;
    for (ll i = 0; i < n; i++) {
        if (try_(i, 0)) {
            version++;
        }
    }
    ll MAX = 0;
    for (ll i = 0; i < m; i++) {
        if (mt[i] != -1)MAX++;
    }
    ll l = 0, r = 1e10;
    while (r - l > 1) {
        ll mid = (l + r) / 2;
        last_used.assign(n, 0);
        mt.assign(m, -1);
        version = 1;
        for (ll i = 0; i < n; i++) {
            if (try_(i, mid)) {
                version++;
            }
        }
        ll p = 0;
        for (ll i = 0; i < m; i++) {
            if (mt[i] != -1)p++;
        }
        if (p == MAX) {
            l = mid;
        } else {
            r = mid;
        }
    }
    cout << l << '\n';
}
