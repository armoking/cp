class BufferedReader {
private:
    const static int BUFFER_SIZE = 1 << 18;
    int index = BUFFER_SIZE;
    char buffer[BUFFER_SIZE];
    void getBuffer() {
        index = 0;
        fread(buffer, 1, BUFFER_SIZE, stdin);
    }
public:
    BufferedReader() {
        getBuffer();
    }
    inline char getChar() {
        if (index == BUFFER_SIZE) {
            getBuffer();
        }
        return buffer[index++];
    }
    inline string readString() {
        string ans;
        static char ch;
        while (isspace(ch = getChar()));
        while (!isspace(ch)) {
            ans.push_back(ch), ch = getChar();
        }
        return ans;
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
    inline long long readLong() {
        long long ans = 0;
        static char neg, ch;
        neg = false;
        while (isspace(ch = getChar()));
        if (ch == '-') {
            neg = true, ch = getChar();
        }
        while (!isspace(ch)) {
            ans = (ans * 10) + (ch - '0'), ch = getChar();
        }
        return neg ? -ans : ans;
    }
    inline double readDouble() {
        double ans = 0;
        static char neg, ch, sep;
        neg = sep = 0;
        while (isspace(ch = getChar()));
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
    static const int BUFFER_SIZE = 1 << 18;
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
