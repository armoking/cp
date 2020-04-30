template<int BUFFER_SIZE>
class BufferedInput {
private:
    char buffer[BUFFER_SIZE];
    size_t itr = 0;
public:
    BufferedInput() {
        fread(buffer, 1, BUFFER_SIZE, stdin);
    }
    string readString() {
        while (isspace(buffer[itr])) itr++;
        string result = "";
        for (size_t i = itr;; i++) {
            if (isspace(buffer[i])) {
                buffer[i] = 0;
                result = string(&buffer[itr]);
                itr = i + 1;
                break;
            }
        }
        if (result.size() == 0) return readString();
        return result;
    }
    int32_t readInt() {
        while (isspace(buffer[itr])) itr++;
        for (size_t i = itr;; i++) {
            if (isspace(buffer[i])) {
                buffer[i] = 0;
                int ans = atoi(&buffer[itr]);
                itr = i + 1;
                return ans;
            }
        }
        return readInt();
    }
    int64_t readLong() {
        while (isspace(buffer[itr])) itr++;
        for (size_t i = itr;; i++) {
            if (isspace(buffer[i])) {
                buffer[i] = 0;
                int64_t ans = atoll(&buffer[itr], i);
                itr = i + 1;
                return ans;
            }
        }
        return readLong();
    }
};

template<int BUFFER_SIZE>
class BufferedOutput {
private:
    char buffer[BUFFER_SIZE];
    size_t len = 0;
public:
    ~BufferedOutput() {
        flush();
    }
    void flush() {
        fwrite(buffer, 1, len, stdout);
        len = 0;
    }
    void print(const string& s) {
        memcpy(&buffer[len], &s[0], s.size());
        len += s.size();
    }
    void print(const char& ch) {
        buffer[len++] = ch;
    }
    void println(const string& s) {
        print(s), print('\n');
    }
    template<typename T> void print(const T& x) {
        print(to_string(x));
    }
    template<typename T> void println(const T& x) {
        println(to_string(x));
    }
};
