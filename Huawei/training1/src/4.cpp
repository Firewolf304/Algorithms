#include<bits/stdc++.h>

using namespace std;

int main() {

    int n, k;
    cin >> n >> k;

    string arr[n];

    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int to = 1;
    for(int i = 0; i < k; i++) {
        to *= n;
    }

    map<string, int> mp;
    for(int i = 0; i < to; i++) {
        string cur = "";
        int x = i;
        for(int j = 0; j < k; j++) {
            int curch = x % n;
            x /= n;
            cur += arr[curch];
        }
        mp[cur]++;
    }

    int ans = 0;
    for(auto it = mp.begin(); it != mp.end(); it++) {
        if (it->second == 1) {
            ans++;
        }
    }
    cout << ans << endl;

    return 0;
}