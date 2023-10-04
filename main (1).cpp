//Tigran Sargsyan
#include <iostream>
#include <algorithm>
#include <limits.h>


template <typename T>
class Vector {
private:
  T* Arr;
  size_t size1;
  size_t capacity1;

public:
  Vector() : Arr(new T[1]{}), size1(0), capacity1(1) {}

  Vector(size_t arr_size) : Arr(new T[arr_size]{}), size1(0), capacity1(arr_size) {}

  Vector(size_t arr_size, T elem) : Arr(new T[arr_size]), size1(arr_size), capacity1(arr_size) {
    for (size_t i = 0; i < size1; i++) {
      Arr[i] = elem;
    }
  }

  Vector(const Vector<T>& other) : Arr(new T[other.capacity1]), size1(other.size1), capacity1(other.capacity1) {
    for (size_t i = 0; i < size1; i++) {
      Arr[i] = other.Arr[i];
    }
  }

  Vector(Vector<T>&& other) : Arr(other.Arr), size1(other.size1), capacity1(other.capacity1) {
    other.Arr = nullptr;
    other.size1 = 0;
    other.capacity1 = 0;
  }

  ~Vector() {
    delete[] Arr;
  }

  Vector<T>& operator=(Vector<T> other) {
    std::swap(other.Arr, Arr);
    std::swap(other.size1, size1);
    std::swap(other.capacity1, capacity1);
    return *this;
  };

  size_t size() const {
    return size1;
  }

  size_t capacity() const {
    return capacity1;
  }

  bool empty() const {
    return size1 == 0;
  }

  void resize() {
    T* arr_temp = new T[capacity1 * 2 + 1]{};
    for(size_t i = 0; i < size1; i++) {
      arr_temp[i] = Arr[i];
    }
    delete[] Arr;
    Arr = arr_temp;
    capacity1 = capacity1 * 2 + 1;
  }

  const T& operator[](size_t index) const {
    if (index < size1) {
      return Arr[index];
    }
    else {
      throw std::out_of_range("Index out of range");
    }
  }

  T& operator[](size_t index) {
    if (index < size1) {
      return Arr[index];
    }
    else {
      throw std::out_of_range("Index out of range");
    }
  }

  const T& at(size_t index) const {
    if (index < size1) {
      return Arr[index];
    }
    else {
      throw std::out_of_range("Index out of range");
    }
  }

  T& at(size_t index) {
    if (index < size1) {
      return Arr[index];
    }
    else {
      throw std::out_of_range("Index out of range");
    }
  }

  void push_back(const T& x) {
    if (size1 == capacity1) {
      resize();
    }
    Arr[size1] = x;
    size1++;
  }

  void push_back(T&& x) {
    if (size1 == capacity1) {
      resize();
    }
    Arr[size1] = std::move(x);
    size1++;
  }

  void pop_back() {
    if (size1 > 0) {
      size1--;
    }
  }

  void clear() {
    size1 = 0;
  }
};
//HOMEWORK--------------------------------------------------------------------
Vector<int> mul(Vector<int>& nums) {
    int n = nums.size();
    Vector<int> result(n, 1);
    int left = 1, right = 1;
    for(int i = 0; i < n; i++) {
        result[i] *= left;
        left *= nums[i];
        result[n - i - 1] *= right;
        right *= nums[n - i - 1];
    }
    return result;
}
Vector<int> lucky_number(Vector<Vector<int>>& mat) {
    Vector<int> result;
    int n = mat.size();
    int m = mat[0].size();
    Vector<int> row_min(n, INT_MAX);
    Vector<int> col_max(m, INT_MIN);
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < m; j++) {
        row_min[i] = std::min(row_min[i], mat[i][j]);
        col_max[j] = std::max(col_max[j], mat[i][j]);
      }
    }
    for(int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (mat[i][j] == row_min[i] && mat[i][j] == col_max[j]) {
          result.push_back(mat[i][j]);
        }
      }
    }
    return result;
}
//HOMEWORK--------------------------------------------------------------------

int main() {
  std::size_t m, n;
  std::cin >> m >> n;  
  Vector<Vector<int>> mat(m, Vector<int>(n, 0));
  for (std::size_t i = 0; i < mat.size(); i++){
    for (int j = 0; j < mat[0].size(); j++){
      std::cin >> mat[i][j];
    }
  }
  Vector<int> res = lucky_number(mat);
    for (int i = 0; i< res.size(); i++){
      std::cout << res[i] << ' ';
    }
    return 0;
}