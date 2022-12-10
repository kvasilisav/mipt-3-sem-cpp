#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
struct comparator
{
    virtual bool operator()(T const&, T const&) const = 0;
};

struct IntComparator final : comparator<int>
{
    bool operator ( ) (int const& lha, int const& rha) const override
    {
        return lha > rha;
    }
};

struct DoubleComparator final : comparator<double>
{
    bool operator ( ) (double const& lha, double const& rha) const override
    {
        return lha > rha;
    }
};

struct StringComparator final : comparator<std::string>
{
    bool operator ( ) (string const& lha, string const& rha) const override
    {
        int i = 0;
        if (lha.length() != rha.length())
            return (lha.length() > rha.length());
        else
        {
            while ((lha[i] == rha[i]) && i < lha.length() - 1 && i < rha.length() - 1)
                i++;
            return (lha[i] > rha[i]);
        }
    }
};

template <typename T>
void Qsort(T* arr, int left, int right, comparator <T>& comp)
{
    T base = arr[right];
    int i = left;

    for (int j = left; j <= right; j++)
    {
        if (comp(arr[j], base) == 0)
        {
            swap(arr[j], arr[i]);
            i = i + 1;
        }
    }

    if (i - 2 > left)
        Qsort(arr, left, i - 2, comp);
    if (right > i)
        Qsort(arr, i, right, comp);

}

template<typename T>
class PriorityQueue
{
private:
    comparator<T>& Comparator;

public:

    PriorityQueue(comparator<T>& Comparator) : Comparator(Comparator) {}

    vector <T> arr;

    //новое значение в очередь (как в куче)
    void push(T element)
    {
        arr.push_back(element);
        int idx = arr.size() - 1;
        int i = (idx - 1) / 2;

        while (Comparator(arr[i], element) == 0 && arr[i] != element)
        {
            if (i == 0)
            {
                swap(arr[i], arr[idx]);
                break;
            }

            swap(arr[i], arr[idx]);
            idx = i;
            i = (idx - 1) / 2;
        }
    }

    //чтение верхнего элемента очереди
    T peek()
    {
        if (arr.size() == 0)
        {
            cout << "there is no elements in queue";
        }
        else return arr[0];
    }

    //удаление верхнего элемента 
    void poll()
    {
        arr.erase(arr.begin());
        vector <T> tmp = arr;
        arr.clear();
        for (int i = 0; i < tmp.size(); i++)
        {
            this->push(tmp[i]);
        }

    }

    //проверка пустоты очереди
    bool is_empty()
    {
        return arr.size() == 0;
    }

};



int main()
{
    int arr1[15] = { 1471, 6074, 19, 544, 862, 3396, 5070, 83, 144, 5693, 437, 9873, 91051, 62, 94 };
    //int arr2[10] = { -3, 0, 7, 2, -7, 0, 4, -9, 2, 9 };
    //double arr3[8] = { -7.4, 0, 9.3, 1.0, -2.6, 3.8, 10.0, 9 };
    //string arr4[8] = { "unicorn", "juice", "underground", "peak", "bear", "pepper", "abricot", "boo" };
    //string arr5[10] = { "ab", "bc", "bd", "b", "a", "d", "c", "abc", "adc", "cd" };

    IntComparator intComp;
    //DoubleComparator doubleComp;
    //StringComparator stringComp;

    //изначальный 
    cout << "Original array: ";
    for (int i = 0; i < 15; i++)
    {
        cout << arr1[i] << "  ";
    }
    cout << "\n\n";
    
    //отсортированный
    Qsort(arr1, 0, 15 - 1, intComp);
    cout << "Sorted array: ";
    for (int i = 0; i < 15; i++)
    {
        cout << arr1[i] << "  ";
    }
    cout << "\n\n";

    //очередь с приоритетом
    PriorityQueue<int> q(intComp);
    for (int i = 0; i < 15; i++)
    {
        q.push(arr1[i]);
    }
    cout << "Priority queue: ";
    for (int i = 0; i < q.arr.size(); i++)
    {
        cout << q.arr[i] << "  ";
    }
    cout << "\n\n";

    //без верхнего элемента
    q.poll();
    cout << "Queue(poll root): ";
    for (int i = 0; i < q.arr.size(); i++)
    {
        cout << q.arr[i] << "  ";
    }
    cout << "\n\n";


    return 0;
}