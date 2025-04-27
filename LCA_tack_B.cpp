#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <queue>
#include <map>
using namespace std;
using ll = long long;
vector<vector<ll>>g1, g2;
vector<ll>tin, tout;
vector<ll>el2;
ll time_ = 0;
void dfs_el(ll v, ll p) {
	tin[v] = time_++;
	el2.push_back(v);
	for (ll u : g2[v]) {
		if (u != p) {
			dfs_el(u, v);
		}
	}
	el2.push_back(v);
	tout[v] = time_++;
}
vector<ll>tree;
void update(ll v, ll vl, ll vr, ll ql, ll qr, ll x) {
	if (vl == ql && vr == qr) {
		tree[v] += x;
		return;
	}
	ll vm = (vl + vr) / 2;
	if (qr <= vm) {
		update(v * 2, vl, vm, ql, qr, x);
	}
	else if (ql >= vm) {
		update(v * 2 + 1, vm, vr, ql, qr, x);
	}
	else {
		update(v * 2, vl, vm, ql, vm, x);
		update(v * 2 + 1, vm, vr, vm, qr, x);
	}
}
ll get(ll v, ll vl, ll vr, ll pos) {
	if (vl == vr - 1) {
		return tree[v];
	}
	ll vm = (vl + vr) / 2;
	if (pos < vm) {
		return get(v * 2, vl, vm, pos) + tree[v];
	}
	else {
		return get(v * 2 + 1, vm, vr, pos) + tree[v];
	}
}
ll ans = 0;
void dfs(ll v, ll p) {
	ans += get(1, 0, time_, tin[v]);
	update(1, 0, time_, tin[v], tout[v] + 1, 1);
	for (ll u : g1[v]) {
		if (u != p) {
			dfs(u, v);
		}
	}
	update(1, 0, time_, tin[v], tout[v] + 1, -1);
}
int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	ll n;
	cin >> n;
	g1.resize(n), g2.resize(n);
	tin.resize(n), tout.resize(n);
	ll a;
	ll s1, s2;
	for (ll i = 0; i < n; i++) {
		cin >> a;
		a--;
		if (a != -1) {
			g1[a].push_back(i);
		}
		else {
			s1 = i;
		}
	}
	for (ll i = 0; i < n; i++) {
		cin >> a;
		a--;
		if (a != -1) {
			g2[a].push_back(i);
		}
		else {
			s2 = i;
		}
	}
	dfs_el(s2, s2);
	tree.resize(4 * time_);
	dfs(s1, s1);
	cout << ans << '\n';
}
