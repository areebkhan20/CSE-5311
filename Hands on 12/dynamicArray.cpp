#include <iostream>
#include <stdexcept>

class DynamicArray {
private:
    int* array;
    size_t size;
    size_t capacity;

    void resize(size_t newCapacity) {
        int* newArray = new int[newCapacity];
        for (size_t i = 0; i < size; ++i) {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
        capacity = newCapacity;
    }

public:
    DynamicArray(size_t initCapacity = 8) : size(0), capacity(initCapacity) {
        array = new int[capacity];
    }

    ~DynamicArray() {
        delete[] array;
    }

    void push_back(int value) {
        if (size == capacity) {
            resize(capacity * 2);
        }
        array[size++] = value;
    }

    void pop_back() {
        if (size > 0) size--;
    }

    void insert(size_t index, int value) {
        if (index > size) throw std::out_of_range("Insert index out of range");
        if (size == capacity) resize(capacity * 2);
        for (size_t i = size; i > index; --i) {
            array[i] = array[i - 1];
        }
        array[index] = value;
        size++;
    }

    void erase(size_t index) {
        if (index >= size) throw std::out_of_range("Erase index out of range");
        for (size_t i = index; i < size - 1; ++i) {
            array[i] = array[i + 1];
        }
        size--;
    }

    int& at(size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        return array[index];
    }

    int& operator[](size_t index) {
        return array[index]; 
    }

    size_t getSize() const {
        return size;
    }

    size_t getCapacity() const {
        return capacity;
    }
};

int main() {
    DynamicArray arr;

    for (int i = 0; i < 10; i++) {
        arr.push_back(i);
    }

    std::cout << "Initial array: ";
    for (size_t i = 0; i < arr.getSize(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";

    arr.insert(5, 99);
    std::cout << "After inserting 99 at index 5: ";
    for (size_t i = 0; i < arr.getSize(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";

    arr.erase(5);
    std::cout << "After erasing index 5: ";
    for (size_t i = 0; i < arr.getSize(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";

    return 0;
}
