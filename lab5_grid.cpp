#include<iostream>

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
    // ����������� 1
    Grid(T const& t) :
        data(new T[1]), y_size(1), x_size(1)
    {
        data[0] = t;
    }

    // ����������� 2
    Grid(S y_size, S x_size) :
        data(new T[y_size * x_size]),
        y_size(y_size), x_size(x_size) {}

    // ����������� 3
    Grid(T const& t, S y_size, S x_size) :
        data(new T[y_size * x_size]),
        y_size(y_size), x_size(x_size)
    {
        for (S pos = 0; pos < y_size * x_size; pos++)
        {
            data[pos] = t;
        }
    }

    // ����������� �����������
    Grid(Grid<T> const& src) :
        data(new T[src.x_size * src.y_size]),
        y_size(src.y_size), x_size(src.x_size)
    {
        for (S pos = 0; pos < src.x_size * src.y_size; pos++)
        {
            data[pos] = src.data[pos];
        }
    }

    // ����������� �����������
    Grid(Grid<T>&& src) noexcept :
        data(nullptr),
        y_size(0), x_size(0)
    {
        swap(src);
    }

    // �������� ����������� ������������
    Grid<T>& operator=(Grid<T>& src)
    {
        Grid tmp = src;
        swap(tmp);
        return *this;
    }

    // �������� ������������� ������������
    Grid<T>& operator=(Grid<T>&& src) noexcept
    {
        Grid tmp = src;
        swap(tmp);
        src.data = nullptr;
        src.y_size = 0;
        src.x_size = 0;
        return *this;
    }

    // ����������
    ~Grid() { delete[] data; }

    T operator()(S y_idx, S x_idx) const
    {
        return data[y_idx * x_size + x_idx];
    }
    T& operator()(S y_idx, S x_idx)
    {
        return data[y_idx * x_size + x_idx];
    }
    T* operator[](S idx) const { return &(data[idx * x_size]); }

    S get_y_size() const { return y_size; }
    S get_x_size() const { return x_size; }
    bool is_empty() const { return y_size * x_size == 0; }
};

int main()
{
    int* data = new int[6];
    for (int idx = 0; idx < 6; idx++)
    {
        data[idx] = idx + 1;
    }
    Grid<int> A(4, 4, 4);
    Grid<int> B(A);
    Grid<int> C = A;
    /*
    ����:
        � = 4 ... 4
        B = � = 4 ... 4
        C = A = 4 ... 4
    */
    std::cout
        << A[1][3] << "\n"
        << A.is_empty() << "\n"
        << B[3][3] << "\n"
        << C[2][2] << "\n";
    /*
    ������ �������:
        4
        0
        4
        4
    */
}
