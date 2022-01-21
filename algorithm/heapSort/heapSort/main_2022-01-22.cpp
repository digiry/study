#include <iostream>
#include <queue>

using namespace std;

priority_queue<int> pq;

typedef struct _node {
    int mId;
    int mValue;

    _node(int id, int value);
} Node;

struct CompNode {
    bool operator()(Node& lhs, Node& rhs) {
        if (lhs.mValue == rhs.mValue) {
            return lhs.mId > rhs.mId;
        }

        return (lhs.mValue > rhs.mValue);
    }
};

priority_queue<Node, vector<Node>, CompNode> pq2;

int main() {
	const int inputs[] = { 20,15,19,4,13,13,23 };
	const int inputs_length = sizeof(inputs) / sizeof(inputs[0]);

	for (int i = 0; i < inputs_length; ++i) {
        pq.push(inputs[i]);
        pq2.push(Node(i, inputs[i]));
	}

	int value = 0;

    while (pq.empty() == false) {
        value = pq.top();
        cout << "pop: value=" << value << endl;
        pq.pop();
    }

    while (pq2.empty() == false) {
        auto node = pq2.top();
        cout << "pop: value=" << node.mId << ":" << node.mValue << endl;
        pq2.pop();
    }
    return 0;
}

_node::_node(int id, int value) {
    this->mId = id;
    this->mValue = value;
}