/*
░█████╗░███╗░░░███╗░█████╗░███╗░░██╗██╗░░██╗░██████╗██╗░░██╗░█████╗░
██╔══██╗████╗░████║██╔══██╗████╗░██║██║░██╔╝██╔════╝██║░░██║██╔══██╗
███████║██╔████╔██║███████║██╔██╗██║█████═╝░╚█████╗░███████║███████║
██╔══██║██║╚██╔╝██║██╔══██║██║╚████║██╔═██╗░░╚═══██╗██╔══██║██╔══██║
██║░░██║██║░╚═╝░██║██║░░██║██║░╚███║██║░╚██╗██████╔╝██║░░██║██║░░██║
╚═╝░░╚═╝╚═╝░░░░░╚═╝╚═╝░░╚═╝╚═╝░░╚══╝╚═╝░░╚═╝╚═════╝░╚═╝░░╚═╝╚═╝░░╚═╝
*/


#include <bits/stdc++.h>
using namespace std;

#define AAKANKSHA ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define ll long long

const int MAX_DIGITS = 20;

ll dp[MAX_DIGITS][3][2][2];

ll solve(int index, int currentCount, int tight, int x, bool leading_zeroes, string &originalString, string num) {
    if (index == x) {
        if (currentCount <= 3 && (count(num.begin(), num.end(), '0') != num.size())) {
            
            return 1;
        } else {
            return 0;
        }
    }

    if (dp[index][currentCount][tight][leading_zeroes] != -1) {
        return dp[index][currentCount][tight][leading_zeroes];
    }

    int minLimit = 0;
    int maxLimit = tight ? originalString[index] - '0' : 9;
    ll ans = 0;

    for (int digit = minLimit; digit <= maxLimit; digit++) {
        string dig = to_string(digit);
        if (currentCount == 3 && digit != 0) {
            continue;
        }

        if (leading_zeroes && digit == 0) {
            ans += solve(index + 1, currentCount, false, x, leading_zeroes, originalString, num + dig);
        } else  {
            int newIndex = index + 1;
            int newTight = tight && (digit == maxLimit);
            int currNewCount=currentCount+((digit>0)?1:0);
            ans += solve(newIndex, currNewCount, newTight, x, leading_zeroes && (digit == 0), originalString, num + dig);
        }
    }

    return dp[index][currentCount][tight][leading_zeroes] = ans;
}


bool check(string &a) {
    int n = a.size();
    int count=0;
    for (int i =0; i < n; i++) {
        if (a[i ] !='0') {
            count++;
        }
    }
    return count<=3;
}

int main() {
    AAKANKSHA;

    int t = 1;
    cin>>t;
    while (t--) {
        ll a, b;
        cin >> a >> b;

        string a_string = to_string(a); // Count for numbers less than a
        string b_string = to_string(b);

        memset(dp, -1, sizeof(dp));
        ll count_b = solve(0, 0, 1, b_string.size(), 1, b_string,"");
        memset(dp, -1, sizeof(dp));
        ll count_a = solve(0, 0, 1, a_string.size(), 1, a_string,"");
        ll result = (count_b - count_a);
        result += check(a_string);

        cout << result << endl;
    }
    return 0;
}
