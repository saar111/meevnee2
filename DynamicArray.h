#ifndef DYNAMIC_ARRAY_H_
#define DYNAMIC_ARRAY_H_

const int INITIAL = 10;

template<class T>
class DynamicArray {
public:
    T **pointers;
    int array_size;
    int elements_count;

    DynamicArray(int length = INITIAL);
    ~DynamicArray();
    void Push(T *data);
};


template<class T>
DynamicArray<T>::DynamicArray(int length):
        array_size(length), elements_count(0) {
    pointers = new T *[length];
}

template<class T>
DynamicArray<T>::~DynamicArray() {
    delete[] pointers;
}

template<class T>
void DynamicArray<T>::Push(T *pointer) {
    if (elements_count == array_size) {
        T **new_arr = new T *[array_size * 2];
        for (int i = 0; i < elements_count; i++) {
            new_arr[i] = pointers[i];
        }
        delete[] pointers;
        pointers = new_arr;
        array_size = array_size * 2;
    }
    pointers[elements_count] = pointer;
    elements_count++;
}

#endif