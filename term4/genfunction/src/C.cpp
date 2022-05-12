#include <iostream>
#include <vector>

using namespace std;

template <class T>
class FormalSeries
{
    vector<T> coefficients;

public:
    explicit FormalSeries(size_t degree)
        : coefficients(degree + 1)
    {}

    [[nodiscard]] size_t size() const
    {
        return coefficients.size();
    }

    [[nodiscard]] size_t deg() const
    {
        return size() - 1;
    }

    T & operator[](size_t i)
    {
        return coefficients[i];
    }

    T operator[](size_t i) const
    {
        return i >= size() ? 0 : coefficients[i];
    }

    friend FormalSeries operator*(FormalSeries const & p, FormalSeries const & q)
    {
        FormalSeries res(q.deg() - 1);

        size_t size = 0;

        for (size_t i = 0; i < res.size(); ++i) {
            for (size_t j = 0; j <= i; ++j) {
                res[i] += p[j] * q[i - j];
            }
            if (res[i]) {
                size = i + 1;
            }
        }

        res.coefficients.resize(size);
        return res;
    }

    friend istream & operator>>(istream & in, FormalSeries & series)
    {
        for (size_t i = 0; i < series.size(); ++i) {
            in >> series[i];
        }
        return in;
    }

    friend ostream & operator<<(ostream & out, FormalSeries const & series)
    {
        out << series.deg() << '\n';
        for (size_t i = 0; i < series.size(); ++i) {
            out << series[i] << ' ';
        }
        return out << '\n';
    }
};

int main()
{
    size_t k;
    cin >> k;

    FormalSeries<int> a(k - 1), q(k);
    cin >> a;

    q[0] = 1;
    for (size_t i = 1; i <= k; ++i) {
        cin >> q[i];
        q[i] = -q[i];
    }

    cout << a * q << q;

    return 0;
}
