namespace s21 {

template <typename key_type>
set<key_type>::set() : tree_(new MYTree<key_type>()) {}
template <typename key_type>
set<key_type>::set(const set& s) {
  tree_ = new MYTree<value_type>();
  tree_->root_ = tree_->Copy(s.tree_->get_root());
}

template <typename key_type>
set<key_type>::set(set&& s) : tree_(new MYTree<value_type>()) {
  std::swap(this->tree_, s.tree_);
}

template <typename key_type>
set<key_type>::~set() {
  this->tree_->~MYTree();
  delete tree_;
}

template <typename key_type>
set<key_type>& set<key_type>::operator=(set&& s) {
  if (this != &s) {
    tree_ = std::move(s.tree_);
  }

  return *this;
}

template <typename key_type>
std::pair<typename set<key_type>::iterator, bool> set<key_type>::insert(
    typename set<key_type>::const_reference value) {
  std::pair<iterator, bool> result;

  if (this->tree_->Empty() || !this->tree_->Contains(value)) {
    result = this->tree_->Insert(value);
  } else {
    iterator it = find(value);
    result = std::pair<iterator, bool>(it.get_iterator_node(), false);
  }

  return result;
}

template <typename key_type>
set<key_type>::set(std::initializer_list<key_type> const& items)
    : tree_(new MYTree<key_type>()) {
  for (auto i = items.begin(); i != items.end(); ++i) {
    this->insert(*i);
  }
}

template <typename key_type>
void set<key_type>::merge(set& other) {
  iterator first_iter = other.tree_->Begin();

  for (; first_iter != other.tree_->End(); first_iter++) {
    std::pair<iterator, bool> result = insert(*first_iter);
  }
}

template <typename key_type>
typename set<key_type>::iterator set<key_type>::begin() {
  return tree_->Begin();
}

template <typename key_type>
typename set<key_type>::iterator set<key_type>::end() {
  return tree_->End();
}

template <typename key_type>
bool set<key_type>::empty() {
  return tree_->Empty();
}

template <typename key_type>
typename set<key_type>::size_type set<key_type>::size() {
  return tree_->Size();
}

template <typename key_type>
typename set<key_type>::size_type set<key_type>::max_size() {
  return tree_->max_size();
}

template <typename key_type>
void set<key_type>::clear() {
  return tree_->Clear();
}

template <typename key_type>
void set<key_type>::erase(iterator pos) {
  return tree_->Erase(pos);
}

template <typename key_type>
void set<key_type>::swap(set& other) {
  return tree_->Swap(*other.tree_);
}

template <typename key_type>
typename set<key_type>::iterator set<key_type>::find(
    typename set<key_type>::const_reference value) {
  return tree_->Find(value);
}

template <typename Key>
bool set<Key>::contains(typename set<key_type>::const_reference value) {
  return tree_->Contains(value);
}

template <typename key_type>
typename set<key_type>::const_reference set<key_type>::operator*() const {
  return (*tree_);
}

template <typename key_type>
typename set<key_type>::iterator& set<key_type>::operator++() {
  return ++tree_;
}

template <typename key_type>
typename set<key_type>::iterator set<key_type>::operator++(int) {
  return tree_++;
}

template <typename key_type>
typename set<key_type>::iterator& set<key_type>::operator--() {
  return --tree_;
}

template <typename key_type>
typename set<key_type>::iterator set<key_type>::operator--(int) {
  return tree_--;
}

template <typename key_type>
typename set<key_type>::key_type set<key_type>::operator*() {
  return *tree_;
}

template <typename key_type>
bool set<key_type>::operator!=(const iterator& it) {
  return tree_ != it;
}

template <typename key_type>
bool set<key_type>::operator==(const iterator& it) {
  return tree_ == it;
}

template <typename key_type>
template <typename... Args>
vector<std::pair<typename set<key_type>::iterator, bool>>
set<key_type>::insert_many(Args&&... args) {
  vector<std::pair<typename set<key_type>::iterator, bool>> results;
  (results.insert_many_back(insert(std::forward<Args>(args))), ...);
  return results;
}

}  // namespace s21
