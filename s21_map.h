#ifndef CPP2_S21_CONTAINERS_1_SRC_MAP_H
#define CPP2_S21_CONTAINERS_1_SRC_MAP_H
#include "s21_avl_tree.h"
#include "s21_vector.h"

namespace s21 {
template <typename Key, typename T>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename MYTree<value_type>::Iterator;
  using const_iterator = typename MYTree<value_type>::ConstIterator;
  using size_type = size_t;
  using tree_node =
      typename MYTree<std::pair<const key_type, mapped_type>>::Node*;

  map();
  map(std::initializer_list<value_type> const& items);
  template <class... Args>
  vector<std::pair<iterator, bool>> insert_many(Args&&... args);
  map(const map& m);
  map(map&& m);
  ~map();
  map& operator=(map&& m);

  mapped_type& at(const key_type& key);
  mapped_type& operator[](const key_type& key);

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();

  reference operator*();
  iterator& operator++();
  iterator operator++(int);
  iterator& operator--();
  iterator operator--(int);
  bool operator!=(const iterator& it);
  bool operator==(const iterator& it);
  const_reference operator*() const;

  void clear();
  std::pair<iterator, bool> insert(const key_type& key, const mapped_type& obj);
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert_or_assign(const key_type& key,
                                             const mapped_type& obj);
  void erase(iterator pos);
  void swap(map& other);
  void merge(map& other);

  bool contains(const key_type& key);
  iterator find(const key_type& key);

 private:
  MYTree<value_type>* tree_;
  void printTree(tree_node node, const std::string& prefix, bool isLeft);

  typename MYTree<key_type>::Node* Copy(
      const typename MYTree<key_type>::Node* s) {
    if (s == nullptr) {
      return nullptr;
    }

    typename MYTree<key_type>::Node* new_node =
        new typename MYTree<key_type>::Node(s->key);

    new_node->left = Copy(s->left);
    new_node->right = Copy(s->right);
    new_node->height = s->height;
    new_node->parent = s->parent;

    return new_node;
  }
};
};  // namespace s21
#include "s21_map.tpp"
#endif  // CPP2_S21_CONTAINERS_1_SRC_MAP_H
