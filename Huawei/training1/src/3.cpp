#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

set<int> ans;

void calc(int w1, int h1, int w2, int h2) {
  if (w2 > w1)
    return;
  if (w2 == w1) {
    if (h1 == h2) {
      ans.insert(0);
      return;
    }
    if (h1 < h2)
      return;
    // h1 > h2
    ans.insert(w1 + (h1 - h2));
    ans.insert(2 * w1 + (h1 - h2));
    return;
  }
  // w2 < w1
  if (h2 > h1)
    return;
  if (h2 == h1) {
    ans.insert(w1 - w2 + h1);
    ans.insert(w1 - w2 + 2 * h1);
    return;
  }
  // h1 > h2
  ans.insert(w1 + h1);
  ans.insert(w1 + h1 + h2);
  ans.insert(w1 + h1 + w2);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout.tie(nullptr);
  int w1, h1, w2, h2;
  cin >> w1 >> h1 >> w2 >> h2;
  calc(w1, h1, w2, h2);
  calc(w1, h1, h2, w2);
  for (int i : ans) {

    cout << 2 * i << ' ';
  }
}