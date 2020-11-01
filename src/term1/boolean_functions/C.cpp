#include <bits/stdc++.h>

using namespace std;

class Circuit
{
    struct Node
    {
        vector<Node*> children;
        vector<bool> table;
        bool value = false;

        [[nodiscard]] uint32_t getDepth() const
        {
            if (children.empty()) {
                return 0;
            }

            uint32_t d = 0;

            for (const auto &c : children) {
                d = max(d, c->getDepth());
            }

            return 1 + d;
        }

        [[nodiscard]] bool calculate() const
        {
            if (children.empty()) {
                return value;
            }

            size_t index = 0;
            for (const auto &c : children) {
                index <<= 1u;
                index |= c->calculate();
            }

            return table[index];
        }
    };

    vector<Node> nodes;

public:
    explicit Circuit(const size_t &n) : nodes(n) {}

    [[nodiscard]] uint32_t getDepth() const
    {
        return nodes.back().getDepth();
    }

    vector<bool> getTruthTable()
    {
        vector<Node*> leaves;
        for (auto &&n : nodes) {
            if (n.children.empty()) {
                leaves.push_back(&n);
            }
        }

        const auto size = 1u << leaves.size();

        vector<bool> res(size);

        for (uint32_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < leaves.size(); ++j) {
                leaves[j]->value = i & (1u << (leaves.size() - j - 1));
            }
            res[i] = nodes.back().calculate();
        }

        return res;
    }

    friend istream &operator>>(istream &in, Circuit &bf)
    {
        for (auto &n : bf.nodes) {
            size_t m;
            cin >> m;

            if (0 == m) {
                continue;
            }

            for (size_t i = 0; i < m; ++i) {
                size_t a;
                cin >> a;
                n.children.push_back(&bf.nodes[a - 1]);
            }

            n.table.resize(1u << m);
            for (auto &&b : n.table) {
                bool t;
                cin >> t;
                b = t;
            }
        }
        return cin;
    }
};

int main()
{
    size_t n;
    cin >> n;

    Circuit c(n);
    cin >> c;

    cout << c.getDepth() << '\n';

    for (const auto &&b : c.getTruthTable()) {
        cout << b;
    }

    return 0;
}