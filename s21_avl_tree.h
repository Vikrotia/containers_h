#ifndef CPP2_S21_CONTAINERS_1_SRC_TREE_H
#define CPP2_S21_CONTAINERS_1_SRC_TREE_H

#include <iostream>
#include <limits>
#include <map>
#include <queue>

namespace s21 {
template <typename Key>
class MYTree {
  using size_type = size_t;

 public:
  class Node {
   public:
    Key key;
    int height;
    Node* left;
    Node* right;
    Node* parent;

    Node(Key key, Node* parent)
        : key(key), height(0), left(nullptr), right(nullptr), parent(parent) {}
    Node()
        : key(Key()),
          height(0),
          left(nullptr),
          right(nullptr),
          parent(nullptr) {}
    Node(Key new_key) : key(new_key) {
      // key = new_key;
      left = right = parent = nullptr;
      height = 0;
    }
  };
  Node* get_root() const;

 public:
  Node* root_;
  class Iterator;
  class ConstIterator;

  MYTree();
  MYTree(const MYTree& other);
  MYTree(MYTree&& other) noexcept;
  MYTree& operator=(MYTree&& other) noexcept;
  MYTree& operator=(const MYTree& other);
  ~MYTree();

  std::pair<Iterator, bool> Insert(const Key& key);
  void Clear();
  void Erase(Iterator pos);
  void Swap(MYTree& other);
  bool Empty();
  bool Contains(const Key& key);
  void merge(MYTree& other);
  Iterator Find(const Key& key);
  size_type Size();
  size_type RecursSize(Node* node);
  size_type max_size();
  Iterator Begin();
  Iterator End();

  class Iterator {
   public:
    Iterator();
    Iterator(Node* node, Node* last_node)
        : iterator_node_(node), iterator_last_node_(last_node){};
    explicit Iterator(Node* node);
    Iterator(const Iterator& other);
    Iterator(Iterator&& other) noexcept;
    Iterator& operator=(Iterator&& other) noexcept;
    Iterator& operator=(const Iterator& other);
    ~Iterator();

    Iterator& operator++();
    Iterator operator++(int);
    Iterator& operator--();
    Iterator operator--(int);
    Key& operator*();
    bool operator!=(const Iterator& it);
    bool operator==(const Iterator& it);

    MYTree::Node* NextNode();
    MYTree::Node* PreviousNode();
    MYTree::Node* get_iterator_node() const;
    MYTree::Node* get_iterator_last_node() const;

   private:
    Node* iterator_node_;
    Node* iterator_last_node_;
  };

  class ConstIterator : public Iterator {
   public:
    ConstIterator() : Iterator(){};
    explicit ConstIterator(Node* node) : Iterator(node) {}
    ConstIterator(Node* node, Node* last_node) : Iterator(node, last_node) {}
    ConstIterator(const Iterator& other) : Iterator(other) {}
    ~ConstIterator() override {}

    const Key& operator*() const { return Iterator::operator*(); }
  };
  Node* Copy(const Node* node);

 private:
  Node* GetMax(Node* node);
  Node* GetMin(Node* node);
  int GetHeight(const Node* node);
  int GetBalance(Node* node);

  void UpdateHeight(Node* node);
  void Balance(Node* node);
  void RotateLeft(Node* root);
  void RotateRight(Node* root);
  void UpdateParent(Node* node, Node* parent);
  void SwapNodesKey(Node* a, Node* b);
  void Swap_Nodes(Node* node1, Node* node2);
  void DestroyTree(Node* node);
  void Delete(Key key);
  Node* DeleteNode(Node* root, const Key& key);
  std::pair<Iterator, bool> InsertNode(MYTree::Node* node, const Key& key);
  Node* MergeTrees(Node* left, Node* right);
  void PrintTree(Node* node, const std::string& prefix, bool isLeft);
};

};  // namespace s21

#include "s21_avl_tree.tpp"
#endif /* CPP2_S21_CONTAINERS_1_SRC_TREE_H*/
