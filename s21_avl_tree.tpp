namespace s21 {

template <typename Key>
MYTree<Key>::MYTree() {
  root_ = nullptr;
}

template <typename Key>
MYTree<Key>::~MYTree() {
  DestroyTree(root_);
}

template <typename Key>
MYTree<Key>::MYTree(const MYTree<Key>& other) {
  root_ = Copy(other.root_);
}

template <typename Key>
MYTree<Key>& MYTree<Key>::operator=(const MYTree<Key>& other) {
  if (this == &other) {
    return *this;
  }

  root_ = Copy(other.root_);
  return *this;
}

template <typename Key>
MYTree<Key>& MYTree<Key>::operator=(MYTree<Key>&& other) noexcept {
  if (this == &other) {
    return *this;
  }

  DestroyTree(root_);
  root_ = other.root_;
  other.root_ = nullptr;
  return *this;
}

template <typename Key>
MYTree<Key>::MYTree(MYTree<Key>&& other) noexcept : root_(other.root_) {
  other.root_ = nullptr;
}

template <typename Key>
typename MYTree<Key>::Node* MYTree<Key>::get_root() const {
  return root_;
}

template <typename Key>
int MYTree<Key>::GetHeight(const Node* node) {
  return node == nullptr ? -1 : node->height;
}

template <typename Key>
void MYTree<Key>::UpdateHeight(Node* node) {
  node->height = std::max(GetHeight(node->left), GetHeight(node->right)) + 1;
}

template <typename Key>
void MYTree<Key>::Erase(MYTree<Key>::Iterator pos) {
  if (root_ == nullptr || pos.get_iterator_node() == nullptr) return;
  root_ = DeleteNode(root_, *pos);
}

template <typename Key>
std::pair<typename MYTree<Key>::Iterator, bool> MYTree<Key>::Insert(
    const Key& key) {
  std::pair<Iterator, bool> result;

  if (root_ == nullptr) {
    root_ = new Node(key, nullptr);
    result.first = Iterator(root_);
    result.second = true;
  } else {
    result = InsertNode(root_, key);
  }

  return result;
}

template <typename Key>
std::pair<typename MYTree<Key>::Iterator, bool> MYTree<Key>::InsertNode(
    MYTree::Node* node, const Key& key) {
  std::pair<Iterator, bool> result;

  if (key < node->key) {
    if (node->left == nullptr) {
      node->left = new Node(key, node);
      result.first = Iterator(node->left);
      result.second = true;
    } else {
      result = InsertNode(node->left, key);
    }
  } else if (key > node->key) {
    if (node->right == nullptr) {
      node->right = new Node(key, node);
      result.first = Iterator(node->right);
      result.second = true;
    } else {
      result = InsertNode(node->right, key);
    }
  } else {
    result.first = Iterator(node);
    result.second = false;
  }

  UpdateHeight(node);
  Balance(node);

  return result;
}

template <typename Key>
int MYTree<Key>::GetBalance(Node* node) {
  return (node == nullptr) ? 0 : GetHeight(node->right) - GetHeight(node->left);
}

template <typename Key>
void MYTree<Key>::UpdateParent(Node* node, Node* parent) {
  if (node != nullptr) node->parent = parent;
}

template <typename Key>
typename MYTree<Key>::Node* MYTree<Key>::DeleteNode(Node* node,
                                                    const Key& key) {
  if (node == nullptr) {
    return node;
  } else if (key < node->key) {
    node->left = DeleteNode(node->left, key);
    UpdateParent(node->left, node);
  } else if (key > node->key) {
    node->right = DeleteNode(node->right, key);
    UpdateParent(node->right, node);
  } else {
    if (node->left == nullptr || node->right == nullptr) {
      Node* temp = node->left ? node->left : node->right;

      if (temp != nullptr) {
        UpdateParent(temp, node->parent);
      }

      delete node;
      node = temp;
    } else {
      Node* temp = GetMin(node->right);
      Swap_Nodes(node, temp);
      Iterator it = Find(key);
      DeleteNode(it.get_iterator_node(), key);
      UpdateParent(node->right, node);
    }
  }

  if (node != nullptr) {
    UpdateHeight(node);
    Balance(node);
  }

  return node;
}

template <typename Key>
void MYTree<Key>::Delete(Key key) {
  if (root_ != nullptr) {
    DeleteNode(root_, key);
  }
}

template <typename Key>
void MYTree<Key>::Clear() {
  DestroyTree(root_);
}

template <typename Key>
void MYTree<Key>::SwapNodesKey(MYTree::Node* node_1, MYTree::Node* node_2) {
  std::swap(node_1->key, node_2->key);
}

template <typename Key>
void MYTree<Key>::RotateRight(MYTree::Node* node) {
  if (node == nullptr || node->left == nullptr) {
    return;
  }

  MYTree::Node* newRoot = node->left;
  node->left = newRoot->right;

  if (newRoot->right != nullptr) {
    newRoot->right->parent = node;
  }

  newRoot->right = node;

  newRoot->parent = node->parent;
  node->parent = newRoot;

  if (newRoot->parent != nullptr) {
    if (newRoot->parent->right == node) {
      newRoot->parent->right = newRoot;
    } else {
      newRoot->parent->left = newRoot;
    }
  } else {
    root_ = newRoot;
  }

  UpdateHeight(node);
  UpdateHeight(newRoot);
}

template <typename Key>
void MYTree<Key>::RotateLeft(MYTree::Node* node) {
  if (node == nullptr || node->right == nullptr) {
    return;
  }

  MYTree::Node* newRoot = node->right;

  node->right = newRoot->left;

  if (newRoot->left != nullptr) {
    newRoot->left->parent = node;
  }

  newRoot->left = node;

  newRoot->parent = node->parent;
  node->parent = newRoot;

  if (newRoot->parent != nullptr) {
    if (newRoot->parent->left == node) {
      newRoot->parent->left = newRoot;
    } else {
      newRoot->parent->right = newRoot;
    }
  } else {
    root_ = newRoot;
  }

  UpdateHeight(node);
  UpdateHeight(newRoot);
}

template <typename Key>
void MYTree<Key>::Balance(MYTree::Node* node) {
  int balance = GetBalance(node);

  if (balance == -2) {
    if (GetBalance(node->left) == 1) {
      RotateLeft(node->left);
    }

    RotateRight(node);
  } else if (balance == 2) {
    if (GetBalance(node->right) == -1) {
      RotateRight(node->right);
    }

    RotateLeft(node);
  }
}

template <typename Key>
typename MYTree<Key>::Iterator MYTree<Key>::Find(const Key& key) {
  Node* search_node = root_;

  while (search_node != nullptr) {
    if (key < search_node->key) {
      search_node = search_node->left;
    } else if (search_node->key < key) {
      search_node = search_node->right;
    } else {
      return Iterator(search_node);
    }
  }

  return End();
}

template <typename Key>
bool MYTree<Key>::Contains(const Key& key) {
  Iterator it = Find(key);

  return it.get_iterator_node() != nullptr;
}

template <typename Key>
void MYTree<Key>::Swap_Nodes(MYTree::Node* node1, MYTree::Node* node2) {
  if (node1->parent != nullptr) {
    if (node1->parent->left == node1) {
      node1->parent->left = node2;
    } else
      node1->parent->right = node2;
  } else {
    root_ = node2;
  }

  if (node2->parent != nullptr) {
    if (node2->parent->right == node2) {
      node2->parent->right = node1;
    } else {
      node2->parent->left = node1;
    }
  } else {
    root_ = node1;
  }

  std::swap(node1->parent, node2->parent);
  std::swap(node1->left, node2->left);
  std::swap(node1->right, node2->right);
}

template <typename Key>
void MYTree<Key>::Swap(MYTree& other) {
  std::swap(root_, other.root_);
}

template <typename Key>

typename MYTree<Key>::size_type MYTree<Key>::max_size() {
  return (std::numeric_limits<size_t>::max() / 2) / sizeof(Key) / 10;
}

template <typename Key>
typename MYTree<Key>::Node* MYTree<Key>::Copy(const Node* node) {
  if (node == nullptr) {
    return nullptr;
  }

  Node* copy_node = new Node(node->key);
  copy_node->left = Copy(node->left);
  copy_node->right = Copy(node->right);
  copy_node->height = node->height;
  copy_node->parent = node->parent;

  return copy_node;
}

template <typename Key>
void MYTree<Key>::DestroyTree(Node* node) {
  if (node != nullptr) {
    if (node->left != nullptr) {
      DestroyTree(node->left);
    }

    if (node->right != nullptr) {
      DestroyTree(node->right);
    }
    delete node;
  }

  root_ = nullptr;
}

template <typename Key>
typename MYTree<Key>::Node* MYTree<Key>::GetMax(Node* node) {
  if (node == nullptr) {
    return nullptr;
  }

  if (node->right == nullptr) {
    return node;
  }

  return GetMax(node->right);
}

template <typename Key>
typename MYTree<Key>::Node* MYTree<Key>::GetMin(Node* node) {
  if (node == nullptr) {
    return nullptr;
  }

  if (node->left == nullptr) {
    return node;
  }

  return GetMin(node->left);
}

template <typename Key>
void MYTree<Key>::PrintTree(Node* node, const std::string& prefix,
                            bool isLeft) {
  if (node == nullptr) {
    return;
  }
  std::cout << prefix;
  std::cout << (isLeft ? "L├──" : "R└──");
  std::cout << node->key << " " << std::endl;
  std::string childPrefix = prefix + (isLeft ? "│   " : "    ");

  PrintTree(node->left, childPrefix, true);
  PrintTree(node->right, childPrefix, false);
}

template <typename Key>
MYTree<Key>::Iterator::Iterator()
    : iterator_node_(nullptr), iterator_last_node_(nullptr){};

template <typename Key>
MYTree<Key>::Iterator::Iterator(const Iterator& other)
    : iterator_node_(other.iterator_node_) {}

template <typename Key>
MYTree<Key>::Iterator::Iterator(Iterator&& other) noexcept
    : iterator_node_(std::exchange(other.iterator_node_, nullptr)) {}

template <typename Key>
typename MYTree<Key>::Node* MYTree<Key>::Iterator::get_iterator_node() const {
  return iterator_node_;
}

template <typename Key>
typename MYTree<Key>::Node* MYTree<Key>::Iterator::get_iterator_last_node()
    const {
  return iterator_last_node_;
}

template <typename Key>
typename MYTree<Key>::Iterator& MYTree<Key>::Iterator::operator=(
    Iterator&& other) noexcept {
  if (this == &other) {
    return *this;
  }

  iterator_node_ = std::exchange(other.iterator_node_, nullptr);

  return *this;
}

template <typename Key>
typename MYTree<Key>::Iterator& MYTree<Key>::Iterator::operator=(
    const Iterator& other) {
  if (this == &other) {
    return *this;
  }

  iterator_node_ = other.iterator_node_;

  return *this;
}

template <typename Key>
MYTree<Key>::Iterator::~Iterator() {
  iterator_node_ = nullptr;
  iterator_last_node_ = nullptr;
};

template <typename Key>
MYTree<Key>::Iterator::Iterator(Node* node)
    : iterator_node_(node), iterator_last_node_(nullptr){};

template <typename Key>
typename MYTree<Key>::Node* MYTree<Key>::Iterator::NextNode() {
  iterator_last_node_ = iterator_node_;
  if (iterator_node_ != nullptr) {
    if (iterator_node_->right != nullptr) {
      iterator_node_ = iterator_node_->right;

      while (iterator_node_->left) {
        iterator_node_ = iterator_node_->left;
      }
    } else {
      while (iterator_node_->parent != nullptr &&
             iterator_node_ == iterator_node_->parent->right) {
        iterator_node_ = iterator_node_->parent;
      }

      iterator_node_ = iterator_node_->parent;
    }
  }

  return iterator_node_;
}

template <typename Key>
typename MYTree<Key>::Node* MYTree<Key>::Iterator::PreviousNode() {
  if (iterator_node_ == nullptr) {
    iterator_node_ = iterator_last_node_;

    if (iterator_last_node_ != nullptr) {
      iterator_last_node_ = iterator_last_node_->parent;
    }
  } else if (iterator_node_->left != nullptr) {
    iterator_node_ = iterator_node_->left;

    while (iterator_node_->right != nullptr) {
      iterator_node_ = iterator_node_->right;
    }
  } else {
    while (iterator_node_->parent != nullptr &&
           iterator_node_ == iterator_node_->parent->left) {
      iterator_node_ = iterator_node_->parent;
    }

    iterator_node_ = iterator_node_->parent;
  }

  return iterator_node_;
}

template <typename Key>
typename MYTree<Key>::Iterator MYTree<Key>::Iterator::operator++(int) {
  Iterator tmp = *this;
  operator++();

  return tmp;
}
template <typename Key>
typename MYTree<Key>::Iterator& MYTree<Key>::Iterator::operator++() {
  iterator_node_ = NextNode();

  return *this;
}

template <typename Key>
bool MYTree<Key>::Iterator::operator!=(const Iterator& it) {
  return (iterator_node_ != it.iterator_node_);
}

template <typename Key>
bool MYTree<Key>::Iterator::operator==(const Iterator& it) {
  return (iterator_node_ == it.iterator_node_);
}

template <typename Key>
typename MYTree<Key>::Iterator MYTree<Key>::Iterator::operator--(int) {
  Iterator tmp = *this;
  operator--();

  return tmp;
}
template <typename Key>
typename MYTree<Key>::Iterator& MYTree<Key>::Iterator::operator--() {
  iterator_node_ = PreviousNode();

  return *this;
}

template <typename Key>
Key& MYTree<Key>::Iterator::operator*() {
  if (iterator_node_ == nullptr) {
    Key key;
    Key& ref = key;
    return ref;
  }

  return iterator_node_->key;
}

template <typename Key>
typename MYTree<Key>::Iterator MYTree<Key>::Begin() {
  return Iterator(GetMin(root_));
}

template <typename Key>
typename MYTree<Key>::Iterator MYTree<Key>::End() {
  Node* last_node = root_;

  if (last_node) {
    while (last_node->right) {
      last_node = last_node->right;
    }
  }

  return Iterator(nullptr, last_node);
}

template <typename Key>
size_t MYTree<Key>::Size() {
  return RecursSize(root_);
}

template <typename Key>
size_t MYTree<Key>::RecursSize(Node* node) {
  if (node == nullptr) {
    return 0;
  }

  size_t leftSize = RecursSize(node->left);
  size_t rightSize = RecursSize(node->right);

  return leftSize + rightSize + 1;
}

template <typename Key>
bool MYTree<Key>::Empty() {
  return Size() == 0;
}
};  // namespace s21
