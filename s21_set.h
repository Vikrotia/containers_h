#ifndef CPP2_S21_CONTAINERS_1_SRC_SET_H
#define CPP2_S21_CONTAINERS_1_SRC_SET_H
#include "s21_avl_tree.h"
#include "s21_vector.h"

namespace s21 {
template <typename Key>
class set {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = Key&;
  using const_reference = const Key&;
  using iterator = typename MYTree<Key>::Iterator;
  using const_iterator = typename MYTree<Key>::ConstIterator;
  using size_type = size_t;

  set();
  set(const set& s);
  set(set&& s);
  ~set();
  set& operator=(set&& s);

  set(std::initializer_list<key_type> const& items);
  template <class... Args>
  vector<std::pair<iterator, bool>> insert_many(Args&&... args);

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  std::pair<iterator, bool> insert(const_reference value);
  void erase(iterator pos);
  void swap(set& other);
  void merge(set& other);

  iterator find(const_reference key);
  bool contains(const_reference key);

  iterator& operator++();
  iterator operator++(int);
  iterator& operator--();
  iterator operator--(int);
  key_type operator*();
  bool operator!=(const iterator& it);
  bool operator==(const iterator& it);
  const_reference operator*() const;

 private:
  MYTree<key_type>* tree_;
};
};  // namespace s21
#include "s21_set.tpp"

#endif  // CPP2_S21_CONTAINERS_1_SRC_SET_H
