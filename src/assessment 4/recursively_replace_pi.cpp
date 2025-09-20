#include <bits/stdc++.h>

using namespace std;


void answer(string s, int index, string& ans) {
    if (index >= s.length()) return;
    if (index + 1 < s.length() && s[index] == 'p' && s[index + 1] == 'i') {
        ans += "3.14";
        index++;
    }
    else {
        ans.push_back(s[index]);
    }
    answer(s, index + 1, ans);
}


int main() {
    string s;
    getline(cin, s);
    string ans;
    answer(s, 0, ans);
    cout << ans << endl;;
    return 0;
}
