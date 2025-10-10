#include<iostream>

using namespace std;
typedef unsigned long long ull;

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ull n, a = 0, b = 0;
    bool flag = false;
    cin >> n;
    if (n == 0) {
        cout << "0 0\n";
        return 0;
    }

    int i = 0;
    while(n > 1) {
        ull last_bit = (n & 1);
        n >>= 1;
        
        if (last_bit) {
            if (flag) {
                a |= (1ull << i);
                b |= (1ull << i);
            } else {
                b |= (1ull << i);
            }
        } else {
            if (flag) {
                b |= (1ull << i);
            } else {
                a |= (1ull << i);
                b |= (1ull << i);
                flag = true;
            }
        }

        i++;
    } 

    if (!flag) {
        b |= (1ull << i);
    }

    cout << a << " " << b << '\n';

    return 0;
}