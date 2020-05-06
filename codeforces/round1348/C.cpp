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



int main() {
    BufferedReader in;
    BufferedWriter out;
    int t = in.readInt();
    while (t--) {
        int n = in.readInt();
        int k = in.readInt();
        string s = in.readString();
        vector<int> arr(26);
        for (int i = 0; i < n; i++) {
            arr[s[i] - 'a']++;
        }
        string answer = "";

        vector<int> a;
        for (int i = 0; i < 26; i++) {
            if (arr[i] > 0) {
                a.push_back(arr[i]);
            }
        }
        sort(all(s));

        int tot = 0;
        if (a[0] < k) {
            answer.push_back(s[k - 1]);
        } else if (a[0] == k) {
            if (k < n) {
                if (a[1] + a[0] == n) {
                    answer.push_back(s[k - 1]);
                    int sz = (a[1] + k - 1) / k;
                    answer += string(sz, s[k]);
                } else {
                    int pos = k - 1;
                    answer = s.substr(pos, n - pos);
                }
            } else {
                answer.push_back(s[k - 1]);
            }
        } else {
            if (n == a[0]) {
                int sz = (a[0] + k - 1) / k;
                answer = string(sz, s[0]);
            } else {
                int pos = k - 1;
                answer = s.substr(pos, n - pos);
            }
        }

        out.println(answer);
    }
}
