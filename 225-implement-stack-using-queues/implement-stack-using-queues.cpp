class MyStack {
public:
    queue<int> q;

    MyStack() {
    }

    void push(int x) {
        int n = q.size();
        q.push(x);

        while (n--) {
            q.push(q.front());
            q.pop();
        }
    }

    int pop() {
        int x = q.front();
        q.pop();
        return x;
    }

    int top() {
        return q.front();
    }

    bool empty() {
        return q.empty();
    }
};