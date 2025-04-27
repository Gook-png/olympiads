#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <math.h>
#include <unordered_set>
using namespace std;
using ll = long long;
using ull = unsigned long long;
int p1 = 179, p2 = 269;
int mod = 1e9 + 7;
const int MAXN = 1e5 + 10;
int pow1[MAXN];
ull pow2[MAXN];
int mul(int a, int b) {
    return (1ll * a * b) % mod;
}
int sum(int a, int b) {
    if (a + b >= mod) {
        return a + b - mod;
    }
    else {
        return a + b;
    }
}
int sub(int a, int b) {
    if (a - b < 0) {
        return a - b + mod;
    }
    else {
        return a - b;
    }
}
pair<int, ull> hash_s[MAXN];
void hash_v(const string& s) {
    int n = (int)s.size();
    for (int i = 0; i < n; i++) {
        hash_s[i + 1].first = sum(mul(hash_s[i].first, p1), s[i]);
        hash_s[i + 1].second = hash_s[i].second * p2 + s[i];
    }
}
pair<int, ull> hash_i(const string& s) {
    int n = (int)s.size();
    pair<int, ull> hash = { 0, 0 };
    for (int i = 0; i < n; i++) {
        hash.first = sum(mul(hash.first, p1), s[i]);
        hash.second = hash.second * p2 + s[i];
    }
    return hash;
}
// [l, r]
pair<int, ull> sub_hash(int l, int r) {
    return { sub(hash_s[r + 1].first, mul(hash_s[l].first, pow1[r - l + 1])),
             hash_s[r + 1].second - hash_s[l].second * pow2[r - l + 1]};
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    pow1[0] = 1; pow2[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        pow1[i] = mul(pow1[i - 1], p1);
        pow2[i] = pow2[i - 1] * p2;
    }
    string s;
    cin >> s;
    hash_v(s);
    unordered_set<int>str1;
    unordered_set<ull>str2;
    int n;
    cin >> n;
    vector<int>sizes;
    string m;
    for (int i = 0; i < n; i++) {
        cin >> m;
        sizes.push_back((int)m.size());
        pair<int, ull> cur_h = hash_i(m);
        str1.insert(cur_h.first);
        str2.insert(cur_h.second);
    }
    sort(sizes.begin(), sizes.end());
    sizes.erase(unique(sizes.begin(), sizes.end()), sizes.end());
    const int kol = (int)sizes.size();
    const int sz = (int)s.size();
    vector<vector<int>> pref(kol, vector<int>(sz + 1));
    for (int j = 0; j < kol; j++) {
        int size = sizes[j];
        for (int i = 0; i <= (int)s.size(); i++) {
            if(i < (int)s.size() - size + 1) {
                pair<int, ull> cur_hash = sub_hash(i, i + size - 1);
                if(str1.find(cur_hash.first) != str1.end() && str2.find(cur_hash.second) != str2.end()) {
                    pref[j][i + 1] = 1;
                }
            }
            if(i != 0)pref[j][i] += pref[j][i-1];
        }
    }
    int q;
    cin >> q;
    vector<int>answer(q);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        int ans = 0;
        for (int j = 0; j < kol; j++) {
            int size = sizes[j];
            int ql = l, qr = r - (size - 1);
            if (ql <= qr) {
                ans += pref[j][qr + 1] - pref[j][ql];
            }
        }
        answer[i] = ans;
    }
    for (int i = 0; i < q; i++) {
        cout << answer[i] << ' ';
    }
    return 0;
}
