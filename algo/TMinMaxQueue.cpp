template <typename T, bool Min = true>
class TMinMaxQueue {
private:
    std::queue<T> Queue_;
    std::deque<std::pair<T, int>> Deque_;
    int Counter_ = 0;
    int CounterDeleted_ = 0;

public:
    void Push(T x) {
        if constexpr (Min) {
            while (!Deque_.empty() && Deque_.back().first >= x) {
                Deque_.pop_back();
            }
        } else {
            while (!Deque_.empty() && Deque_.back().first <= x) {
                Deque_.pop_back();
            }
        }
        Deque_.emplace_back(x, Counter_++);
        Queue_.push(x);
    }

    T Get() const {
        return Deque_.front().first;
    }

    void Pop() {
        if (Deque_.front().second == CounterDeleted_) {
            Deque_.pop_front();
        }
        CounterDeleted_++;
        Queue_.pop();
    }

    T Front() const {
        return Queue_.front();
    }
};

