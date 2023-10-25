#include <iostream>

template<typename T>
class List {
  struct Node {
    T data;
    Node *next;
    Node *prev;
    Node(const T& data) : data(data), next(nullptr), prev(nullptr) {}
  };

  Node *head;
  Node *tail;
  size_t size_;

public:
  class iterator {
    Node *current;
  public:
    using value_type = T;
    using reference = T&;
    using pointer = T*;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;

    iterator() : current(nullptr) {}
    iterator(Node *node) : current(node) {}
    reference operator*() const { return current->data; }
    pointer operator->() const { return &(current->data); }
    iterator &operator++() { current = current->next; return *this; }
    iterator &operator++(int) { iterator old = *this; ++(*this); return old; }
    iterator &operator--() { current = current->prev; return *this; }
    iterator &operator--(int) { iterator old = *this; --(*this); return old; }
    friend bool operator==(iterator lhs, iterator rhs) { return lhs.current == rhs.current; }
    friend bool operator!=(iterator lhs, iterator rhs) { return lhs.current != rhs.current; }
  };

  List() : head(nullptr), tail(nullptr), size_(0) {}
  List(size_t count, const T &value = T()) : head(nullptr), tail(nullptr), size_(0) {
    for (size_t i = 0;i < count;i++) {
      push_back(value);
    }
  }

  List(const List &other) : head(nullptr), tail(nullptr), size_(0) {
    for (const T& item : other) {
      push_back(item);
    }
  }

  List(List &&other) : head(other.head), tail(other.tail), size_(other.size_) {
    other.head = nullptr;
    other.tail = nullptr;
    other.size_ = 0;
  }

  List(std::initializer_list<T> ilist) : head(nullptr), tail(nullptr), size_(0) {
    for (const T& item : ilist) {
      push_back(item);
    }
  }

  ~List() {
    while (!empty()) {
      pop_front();
    }
  }

  List &operator=(const List &other) {
    if (this != &other) {
      clear();
      for (const T& item : other) {
        push_back(item);
      }
    }
    return *this;
  }

  List &operator=(List &&other) {
    if (this != &other) {
      clear();
      head = other.head;
      tail = other.tail;
      size_ = other.size_;
      other.head = nullptr;
      other.tail = nullptr;
      other.size_ = 0;
    }
    return *this;
  }

  List &operator=(std::initializer_list<T> ilist) {
    clear();
    for (const T& item : ilist) {
      push_back(item);
    }
    return *this;
  }

  T &front() { return head->data; }
  const T &front() const { return head->data; }
  T &back() { return tail->data; }
  const T &back() const { return tail->data; }

  bool empty() const { return size_ == 0; }
  size_t size() const { return size_; }

  iterator insert(iterator pos, const T &value) {
    if (pos.current == nullptr) {
      push_back(value);
      return iterator(tail);
    }
    Node *newNode = new Node(value);
    Node *before = pos.current->prev;
    newNode->next = pos.current;
    newNode->prev = before;
    pos.current->prev = newNode;
    if (before) {
      before->next = newNode;
    } 
    else {
      head = newNode;
    }
    size_++;
    return iterator(newNode);
  }

  iterator insert(iterator pos, T &&value) {
    if (pos.current == nullptr) {
      push_back(std::move(value));
      return iterator(tail);
    }
    Node *newNode = new Node(std::move(value));
    Node *before = pos.current->prev;
    newNode->next = pos.current;
    newNode->prev = before;
    pos.current->prev = newNode;
    if (before) {
      before->next = newNode;
    }
    else {
      head = newNode;
    }
    size_++;
    return iterator(newNode);
  }

  iterator insert(iterator pos, std::initializer_list<T> ilist) {
    for (const T& item : ilist) {
      pos = insert(pos, item);
      pos++;
    }
    return pos;
  }

  iterator erase(iterator pos) {
    if (pos.current) {
      Node *prevNode = pos.current->prev;
      Node *nextNode = pos.current->next;
      if (prevNode) {
        prevNode->next = nextNode;
      } 
      else {
        head = nextNode;
      }
      if (nextNode) {
        nextNode->prev = prevNode;
      }
      else {
        tail = prevNode;
      }
      delete pos.current;
      size_--;
    }
    return iterator(pos.current ? pos.current->next : nullptr);
  }

  iterator erase(iterator first, iterator last) {
    while (first != last) {
      first = erase(first);
    }
    return last;
  }

  void push_front(const T &value) {
    Node *newNode = new Node(value);
    newNode->next = head;
    if (head) {
      head->prev = newNode;
    }
    else {
      tail = newNode;
    }
    head = newNode;
    size_++;
  }

  void push_front(T &&value) {
    Node *newNode = new Node(std::move(value));
    newNode->next = head;
    if (head) {
      head->prev = newNode;
    }
    else {
      tail = newNode;
    }
    head = newNode;
    size_++;
  }

  void push_back(const T &value) {
    Node *newNode = new Node(value);
    newNode->prev = tail;
    if (tail) {
      tail->next = newNode;
    }
    else {
      head = newNode;
    }
    tail = newNode;
    size_++;
  }

  void push_back(T &&value) {
    Node *newNode = new Node(std::move(value));
    newNode->prev = tail;
    if (tail) {
      tail->next = newNode;
    }
    else {
      head = newNode;
    }
    tail = newNode;
    size_++;
  }

  void pop_front() {
    if (head) {
      Node *newHead = head->next;
      delete head;
      head = newHead;
      if (head) {
        head->prev = nullptr;
      }
      else {
        tail = nullptr;
      }
      size_--;
    }
  }

  void pop_back() {
    if (tail) {
      Node *newTail = tail->prev;
      delete tail;
      tail = newTail;
      if (tail) {
        tail->next = nullptr;
      }
      else {
        head = nullptr;
      }
      size_--;
    }
  }

  iterator begin() { return iterator(head); }
  iterator end() { return iterator(nullptr); }

  void clear() {
    while (!empty()) {
      pop_front();
    }
  }

  friend bool operator==(const List<T> &lhs, const List<T> &rhs) {
    if (lhs.size_ != rhs.size_) {
      return false;
    }
    auto lit = lhs.begin();
    auto rit = rhs.begin();
    while (lit != lhs.end()) {
      if (*lit != *rit) {
        return false;
      }
      lit++;
      rit++;
    }
    return true;
  }

  bool operator!=(const List<T> &other) {
    return !(*this == other);
  }
};

int main() {

  
  return 0;
}
