#include<iostream>
#include <cassert>

template <typename T>
class Grid final
{
private:
    using S = unsigned;
    T* data;
    S y_size, x_size;
    void swap(Grid<T>& src)
    {
        std::swap(data, src.data);
        std::swap(y_size, src.y_size);
        std::swap(x_size, src.x_size);
    }
public:
    // constructor with 1 parameters
    Grid(T const& t) :
        data(new T[1]), y_size(1), x_size(1)
    {
        data[0] = t;
    }
    // constructor with 2 parameters
    Grid(S y_size, S x_size) :
        data(new T[y_size * x_size]),
        y_size(y_size), x_size(x_size) {}

    // constructor with 3 parameters
    Grid(T const& t, S y_size, S x_size) :
        data(new T[y_size * x_size]),
        y_size(y_size), x_size(x_size)
    {
        for (S pos = 0; pos < y_size * x_size; pos++)
        {
            data[pos] = t;
        }
    }
    Grid(T* new_data, S y_size, S x_size) :
        data(new T[y_size * x_size]),
        y_size(y_size), x_size(x_size)
    {
        for (S pos; pos < y_size * x_size; pos++)
        {
            data[pos] = new_data[pos];
        }
    }
    // copy constructor
    Grid(Grid<T> const& src) :
        data(new T[src.x_size * src.y_size]),
        y_size(src.y_size), x_size(src.x_size)
    {
        for (S pos = 0; pos < src.x_size * src.y_size; pos++)
        {
            data[pos] = src.data[pos];
        }
    }
    // move constructor
    Grid(Grid<T>&& src) noexcept :
        data(nullptr),
        y_size(0), x_size(0)
    {
        swap(src);
    }
    // copy assignment operator  
    Grid<T>& operator=(Grid<T>& src)
    {
        Grid tmp = src;
        swap(tmp);
        return *this;
    }
    // move assignment operator
    Grid<T>& operator=(Grid<T>&& src) noexcept
    {
        Grid tmp = src;
        swap(tmp);
        src.data = nullptr;
        src.y_size = 0;
        src.x_size = 0;
        return *this;
    }
    // destructor
    ~Grid() { delete[] data; }
    T operator()(S y_idx, S x_idx) const
    {
        return data[y_idx * x_size + x_idx];
    }
    T& operator()(S y_idx, S x_idx)
    {
        return data[y_idx * x_size + x_idx];
    }

    // index operator
    T* operator[](S idx) const { return &(data[idx * x_size]); }

    // y_size getter
    S get_y_size() const { return y_size; }

    // x_size getter
    S get_x_size() const { return x_size; }

    bool is_empty() const { return y_size * x_size == 0; }
};

void test_1()
{
    Grid<float> g(3, 2, 0.0f);
    assert(3 == g.get_y_size());
    assert(2 == g.get_x_size());

    using gsize_t = Grid<int>::size_type;

    for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            assert(0.0f == g[y_idx][x_idx]);

    for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            g[y_idx][x_idx] = 1.0f;

    for (gsize_t y_idx = 0; y_idx != g.get_y_size(); ++y_idx)
        for (gsize_t x_idx = 0; x_idx != g.get_x_size(); ++x_idx)
            assert(1.0f == g[y_idx][x_idx]);
}

void test_2()
{
    Grid<float, 3> const g3(2, 3, 4, 1.0f);
    assert(1.0f == g3(1, 1, 1));
    Grid<float, 2> const g2(2, 5, 2.0f);
    assert(2.0f == g2(1, 1));
    g2 = g3[1];
    assert(1.0f == g2(1, 1));
}

int main()
{
    //  Test for index operator
    test(1);

    // Test for multidimensional Grid
    // test(2)
    return 0;
}
