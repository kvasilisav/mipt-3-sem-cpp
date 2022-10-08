#include <iostream>
#include <cstdlib>

using namespace std;

struct Complex {
    double r;
    double i;
};

//compare abs values
bool compare(void* lha, void* rha) {
    Complex* left = (Complex*)lha;
    Complex* right = (Complex*)rha;

    return left->r * left->r + left->i * left->i > right->r * right->r + right->i * right->i;

}

//swap elements
void swp(void* lha, void* rha, size_t element_size) {

    void* tmp = malloc(element_size);
    memcpy(tmp, lha, element_size);
    memcpy(lha, rha, element_size);
    memcpy(rha, tmp, element_size);
    free(tmp);

}
void* shift_reference(void* start, int delta, size_t element_size) {
    char* tmp = (char*)start;
    tmp += delta * element_size;
    start = (void*)tmp;
    return start;
}

void* partition(void* array, size_t element_size, void* left, void* right, void* g_pivot) {
    void* pivot = operator new(element_size);
    memcpy(pivot, g_pivot, element_size);
    while (true) {
        while (compare(left, pivot) && left <= right) left = shift_reference(left, 1, element_size);
        while (compare(pivot, right)) right = shift_reference(right, -1, element_size);

        if (right <= left) return right;
        swp(left, right, element_size);
        left = shift_reference(left, 1, element_size);
        right = shift_reference(right, -1, element_size);

    }
    operator delete (pivot);
    return right;
}

void generic_qsort(void* array, size_t element_size, bool (*compare)(void* lha, void* rha), void* start, void* end) {
    if (start >= end) {
        return;
    }

    void* split = start;

    char* tmp1 = (char*)start;
    char* tmp2 = (char*)end;
    int cnt = 0;
    while (tmp1 != tmp2) {
        cnt++;
        tmp1 += element_size;
    }

    split = shift_reference(split, cnt / 2, element_size);
    split = partition(array, element_size, start, end, split);

    generic_qsort(array, element_size, compare, start, split);
    generic_qsort(array, element_size, compare, shift_reference(split, 1, element_size), end);

}

int main() {
    Complex data[10];
    for (int i = 0; i < 10; ++i) {

        int a, b;
        cin >> a >> b;
        data[i].r = a;
        data[i].i = b;

    }

    generic_qsort(data, sizeof(Complex), compare, data, data + 10 - 1);

    for (int i = 0; i < 10; ++i) {
        cout << data[i].r << ' ' << data[i].i << endl;
    }
    return 0;

}