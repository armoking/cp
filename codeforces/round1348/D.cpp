#include <bits/stdc++.h>
#define all(x) begin(x), end(x)

using namespace std;
using ll = long long;

class BufferedReader {
private:
    const static int BUFFER_SIZE = 25e5;
    int index = 0;
    char buffer[BUFFER_SIZE];
    void getBuffer() {
        fread(buffer, 1, BUFFER_SIZE, stdin);
        index = 0;
    }
public:
    BufferedReader() {
        memset(buffer, 0, sizeof buffer);
        getBuffer();
    }
    inline char getChar() {
        if (index == BUFFER_SIZE) {
            getBuffer();
        }
        return buffer[index++];
    }
    inline string readString() {
        string ans = "";
        static char ch;
        ch = getChar();
        while (isspace(ch) || ch == 0) ch = getChar();
        while (!isspace(ch)) {
            ans.push_back(ch), ch = getChar();
        }
        return ans;
    }
    inline long long readLong() {
        long long ans = 0;
        char neg = false, ch = getChar();
        while (isspace(ch)) ch = getChar();
        if (ch == '-') {
            neg = true, ch = getChar();
        }
        while (!isspace(ch)) {
            ans = (ans * 10) + (ch - '0');
            ch = getChar();
        }
        return neg ? -ans : ans;
    }
    inline int readInt() {
        int ans = 0;
        char neg = false, ch = getChar();
        while (isspace(ch)) ch = getChar();
        if (ch == '-') {
            neg = true, ch = getChar();
        }
        while (!isspace(ch)) {
            ans = (ans * 10) + (ch - '0');
            ch = getChar();
        }
        return neg ? -ans : ans;
    }
    inline double readDouble() {
        double ans = 0;
        static char neg, ch, sep;
        neg = sep = 0;
        while (isspace(ch)) ch = getChar();
        if (ch == '-') {
            neg = true, ch = getChar();
        }
        while (!isspace(ch)) {
            if (ch == '.') {
                sep++;
            } else {
                ans = (ans * 10) + ch - '0';
                sep += sep > 0;
            }
            ch = getChar();
        }
        ans /= pow(10, sep - 1);
        return neg ? -ans : ans;
    }
};

class BufferedWriter {
private:
    static const int BUFFER_SIZE = 25e5;
    char buffer[BUFFER_SIZE];
    int index = 0;

public:
    BufferedWriter() {
        memset(buffer, 0, sizeof buffer);
    }
    ~BufferedWriter() {
        flush();
    }
    inline void flush() {
        fwrite(buffer, 1, index, stdout), index = 0;
    }
    inline void putChar(char x) {
        if (index == BUFFER_SIZE) {
            flush();
        }
        buffer[index++] = x;
    }
    inline void print(const string& s) {
        for (char ch : s) putChar(ch);
    }
    template<typename T> void print(const T& x) {
        print(to_string(x));
    }
    template<typename T> void println(const T& x) {
        print(x), putChar('\n');
    }
};

pair<bool, vector<int>> IsPossible(int n, int day) {
    ll w = 1;
    ll cnt = 1;
    vector<int> ans = {};
    ll past = day + 1;
    for (int d = 0; d < day; d++) {
        ll rem = day - d;
        ll left = 0;
        ll right = cnt;
        ll mid;
        ll dlt = 0;
        while (left <= right) {
            mid = (left + right) / 2;
            ll cur = 1ll * rem * mid;
            if (cur + past <= n) {
                dlt = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        ans.push_back(dlt);
        cnt += dlt;
        past += 1ll * dlt * rem;
        w += cnt;
    }
    return {w == n, ans};
}

int main() {
    BufferedReader in;
    BufferedWriter out;
    int t = in.readInt();
    while (t--) {
        int n = in.readInt();
        vector<int> ans;
        for (int day = 1; day <= 35; day++) {
            auto [res, cur] = IsPossible(n, day);
            if (res) {
                ans = cur;
                break;
            }
        }
        out.println(ans.size());
        for (int val : ans) {
            out.print(val);
            out.putChar(' ');
        }
        out.putChar('\n');
    }
}
