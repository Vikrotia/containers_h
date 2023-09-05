#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_QUEUE_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_QUEUE_H_

#include <iostream>
#include <list>

#include "s21_list.h"

namespace s21 {
template <class T, class Container = list<T>>
class queue {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;

  queue() : deque_() {}
  queue(std::initializer_list<value_type> const &items) : deque_(items) {}
  queue(const queue &other) : deque_(other.deque_) {}
  queue(queue &&other) : deque_(std::move(other.deque_)) {}
  ~queue() { ; }

  queue &operator=(queue &&other) noexcept {
    if (this != &other) {
      deque_ = std::move(other.deque_);
    }

    return *this;
  }
  queue &operator=(const queue &other) {
    if (this != &other) {
      deque_ = other.deque_;
    }

    return *this;
  }

  bool empty() { return deque_.empty(); }
  size_type size() { return deque_.size(); }
  const_reference front() const { return deque_.front(); }
  const_reference back() const { return deque_.back(); }
  void swap(queue &other) { std::swap(deque_, other.deque_); }

  void pop() { deque_.pop_front(); }
  void push(const_reference value) { deque_.push_back(value); }

  template <class... Args>
  void insert_many_back(Args &&...args) {
    for (const auto &arg : {args...}) {
      deque_.push_back(arg);
    }
  }

 private:
  Container deque_;
};

};  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_QUEUE_H_
