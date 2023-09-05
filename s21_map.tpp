namespace s21 {

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map() : tree_(new MYTree<value_type>()) {}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(const map& s) {
  tree_ = new MYTree<value_type>();
  tree_->root_ = tree_->Copy(s.tree_->get_root());
}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(map&& s) : tree_(new MYTree<value_type>()) {
  std::swap(this->tree_, s.tree_);
}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::~map() {
  tree_->~MYTree();
  delete tree_;
}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>& map<key_type, mapped_type>::operator=(map&& s) {
  if (this != &s) {
    tree_ = std::move(s.tree_);
  }
  return *this;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::iterator
map<key_type, mapped_type>::begin() {
  return tree_->Begin();
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::iterator
map<key_type, mapped_type>::end() {
  return tree_->End();
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::iterator map<key_type, mapped_type>::find(
    const key_type& key) {
  typename map<key_type, mapped_type>::tree_node search_node =
      tree_->get_root();

  while (search_node != nullptr) {
    if (key < search_node->key.first) {
      search_node = search_node->left;
    } else if (search_node->key.first < key) {
      search_node = search_node->right;
    } else {
      return iterator(search_node);
    }
  }

  return end();
}

template <typename key_type, typename mapped_type>
bool map<key_type, mapped_type>::contains(const key_type& key) {
  iterator it = find(key);

  return it.get_iterator_node() != nullptr;
}

template <typename key_type, typename mapped_type>
std::pair<typename map<key_type, mapped_type>::iterator, bool>
map<key_type, mapped_type>::insert(const value_type& value) {
  std::pair<iterator, bool> result;
  bool check = contains(value.first);

  if (this->tree_->get_root() == nullptr || !check) {
    result = this->tree_->Insert(value);
  } else {
    result.first = find(value.first);
    result.second = false;
  }

  return result;
}

template <typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(const std::initializer_list<value_type>& items)
    : tree_(new MYTree<value_type>()) {
  for (auto i = items.begin(); i != items.end(); ++i) {
    insert(*i);
  }
}

template <typename key_type, typename mapped_type>
std::pair<typename map<key_type, mapped_type>::iterator, bool>
map<key_type, mapped_type>::insert(const key_type& key,
                                   const mapped_type& obj) {
  std::pair<iterator, bool> result;
  bool check = contains(key);

  if (this->tree_->Empty() || !check) {
    result = this->tree_->Insert(std::make_pair(key, obj));
  } else {
    result.first = find(key);
    result.second = false;
  }

  return result;
}

template <typename key_type, typename mapped_type>
std::pair<typename map<key_type, mapped_type>::iterator, bool>
map<key_type, mapped_type>::insert_or_assign(const key_type& key,
                                             const mapped_type& obj) {
  std::pair<iterator, bool> result;
  bool check = contains(key);

  if (this->tree_->get_root() == nullptr || !check) {
    result = this->tree_->Insert(std::make_pair(key, obj));
  } else {
    iterator it = find(key);
    (*it).second = obj;
    result.first = it;
    result.second = false;
  }

  return result;
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::merge(map& other) {
  iterator first_iter = other.tree_->Begin();

  for (; first_iter != other.tree_->End(); first_iter++) {
    if (!contains(first_iter.get_iterator_node()->key.first)) {
      this->insert(*first_iter);
    }
  }
}

template <typename key_type, typename mapped_type>
mapped_type& map<key_type, mapped_type>::operator[](const key_type& key) {
  iterator it = find(key);

  if (it.get_iterator_node() == nullptr) {
    std::pair<iterator, bool> result =
        insert(std::make_pair(key, mapped_type{}));
    it = result.first;
  }

  return it.get_iterator_node()->key.second;
}

template <typename key_type, typename mapped_type>
mapped_type& map<key_type, mapped_type>::at(const key_type& key) {
  iterator it = find(key);

  if (it.get_iterator_node() == nullptr) {
    throw std::out_of_range("Key not found in map");
  }

  return it.get_iterator_node()->key.second;
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::erase(iterator pos) {
  tree_->Erase(pos);
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::swap(map& other) {
  return tree_->Swap(*other.tree_);
}

template <typename key_type, typename mapped_type>
bool map<key_type, mapped_type>::empty() {
  return tree_->Empty();
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::size_type
map<key_type, mapped_type>::size() {
  return tree_->Size();
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::size_type
map<key_type, mapped_type>::max_size() {
  return tree_->max_size();
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::clear() {
  tree_->Clear();
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::value_type&
map<key_type, mapped_type>::operator*() {
  return (*tree_);
}
template <typename key_type, typename mapped_type>
const typename map<key_type, mapped_type>::value_type&
map<key_type, mapped_type>::operator*() const {
  return (*tree_);
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::iterator&
map<key_type, mapped_type>::operator++() {
  return ++tree_;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::iterator
map<key_type, mapped_type>::operator++(int) {
  return tree_++;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::iterator&
map<key_type, mapped_type>::operator--() {
  return --tree_;
}

template <typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::iterator
map<key_type, mapped_type>::operator--(int) {
  return tree_--;
}

template <typename key_type, typename mapped_type>
bool map<key_type, mapped_type>::operator!=(const iterator& it) {
  return tree_ != it;
}

template <typename key_type, typename mapped_type>
bool map<key_type, mapped_type>::operator==(const iterator& it) {
  return tree_ == it;
}

template <typename key_type, typename mapped_type>
void map<key_type, mapped_type>::printTree(tree_node node,
                                           const std::string& prefix,
                                           bool isLeft) {
  if (node == nullptr) {
    return;
  }

  std::cout << prefix;
  std::cout << (isLeft ? "L├──" : "R└──");
  std::cout << node->key_.first << ", " << node->key_.second << " "
            << std::endl;

  std::string childPrefix = prefix + (isLeft ? "│   " : "    ");
  printTree(node->left, childPrefix, true);
  printTree(node->right, childPrefix, false);
}

template <typename key_type, typename mapped_type>
template <typename... Args>
vector<std::pair<typename map<key_type, mapped_type>::iterator, bool>>
map<key_type, mapped_type>::insert_many(Args&&... args) {
  vector<std::pair<typename map<key_type, mapped_type>::iterator, bool>>
      results;

  (results.insert_many_back(insert(std::forward<Args>(args))), ...);

  return results;
}

};  // namespace s21
