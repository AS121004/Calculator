#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Function that returns the largest magical string by recursively processing the input.
string largestMagical(string s) {
    int n = s.size();
    if(n == 0) return "";
    vector<string> subs;
    int count = 0, start = 0;
    // Partition the string into balanced parts
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') count++;
        else count--;
        if (count == 0) {
            // Recursively process the inner part
            string inner = largestMagical(s.substr(start + 1, i - start - 1));
            // Encapsulate it as a magical segment
            subs.push_back("1" + inner + "0");
            start = i + 1;
        }
    }
    // Sort in descending order to obtain the maximum numeric value
    sort(subs.begin(), subs.end(), greater<string>());
    string result;
    for (const auto &sub : subs) {
        result += sub;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    cout << largestMagical(s) << "\n";
    return 0;
}