
#include "vector.h"

#include <stdexcept>
#include <utility>
using namespace std;

template <typename T>
void Vector<T>::Reserve(size_t new_capacity) {
  T* new_data = new T[new_capacity]{};
  try {
    for (size_t i = 0; i < sz; ++i) {
      new_data[i] = data[i];
    }
  } catch (...) {
    delete[] new_data;
    throw;
  }
  delete[] data;
  data = new_data;
  capacity = new_capacity;
}

template <typename T>
Vector<T>::Vector() : data(nullptr), sz(0), capacity(0) {}

template <typename T>
Vector<T>::Vector(const Vector& other)
    : data(nullptr), sz(other.sz), capacity(other.sz) {
  if (sz > 0) {
    data = new T[sz]{};
  }
  try {
    for (size_t i = 0; i < sz; ++i) {
      data[i] = other.data[i];
    }
  } catch (...) {
    delete[] data;
    throw;
  }
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
  if (this != &other) {
    Vector copy(other);
    swap(data, copy.data);
    swap(sz, copy.sz);
    swap(capacity, copy.capacity);
  }
  return *this;
}

template <typename T>
Vector<T>::~Vector() {
  delete[] data;
}

template <typename T>
size_t Vector<T>::Size() const {
  return sz;
}

template <typename T>
void Vector<T>::PushBack(const T& value) {
  if (sz == capacity) {
    size_t newCapacity = 2;
    if (capacity > 0) {
      newCapacity = capacity * 2;
    }
    T copy = value;
    Reserve(newCapacity);
    data[sz] = copy;
  } else {
    data[sz] = value;
  }
  ++sz;
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const {
  if (index >= sz) {
    throw out_of_range("Индекс за пределами массива");
  }
  return data[index];
}
