#pragma once
#include <cstddef>
using namespace std;

// Основа Vector<T> из semak3/prak.cpp.
template <typename T>
class Vector {
 private:
  T* data;
  size_t sz;
  size_t capacity;
  void Reserve(size_t new_capacity);

 public:
  Vector();
  Vector(const Vector& other);
  Vector& operator=(const Vector& other);
  ~Vector();
  size_t Size() const;
  void PushBack(const T& value);
  const T& operator[](size_t index) const;
};
