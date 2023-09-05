#include <gtest/gtest.h>

#include <queue>
#include <vector>

#include "../s21_queue.h"

class queueTest {
 public:
  s21::queue<int> s21_queue_null;
  std::queue<int> std_queue_null;

  s21::queue<int> s21_queue_swap1{1, 1, 1};
  std::queue<int> std_queue_swap1;

  s21::queue<int> s21_queue_swap2{2, 2, 2, 2};
  std::queue<int> std_queue_swap2;
};

TEST(queue, Constructor_Default) {
  s21::queue<int> our_queue;
  std::queue<int> std_queue;
  EXPECT_EQ(our_queue.empty(), std_queue.empty());
}

TEST(queue, Constructor_List) {
  s21::queue<int> our_queue = {1, 2, 3};
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);
  EXPECT_EQ(our_queue.front(), std_queue.front());
  EXPECT_EQ(our_queue.back(), std_queue.back());
}

TEST(queue, Constructor_Copy) {
  s21::queue<int> our_queue = {1, 2, 3};
  s21::queue<int> our_copy(our_queue);
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);
  std::queue<int> std_copy(std_queue);
  EXPECT_EQ(our_copy.front(), std_copy.front());
  EXPECT_EQ(our_copy.back(), std_copy.back());
}

TEST(queue, Operator_Copy) {
  s21::queue<int> our_queue_int = {1, 2, 3};
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  s21::queue<int> our_queue_empty;
  std::queue<int> std_queue_empty;
  our_queue_empty = our_queue_int;
  std_queue_empty = std_queue_int;
  EXPECT_EQ(our_queue_empty.front(), std_queue_empty.front());
  EXPECT_EQ(our_queue_empty.back(), std_queue_empty.back());
  EXPECT_EQ(our_queue_int.empty(), std_queue_int.empty());
}

TEST(queue, Constructor_Move) {
  s21::queue<int> our_queue = {1, 2, 3};
  s21::queue<int> our_move(std::move(our_queue));
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);
  std::queue<int> std_move(std::move(std_queue));
  EXPECT_EQ(our_move.front(), std_move.front());
  EXPECT_EQ(our_move.back(), std_move.back());
  EXPECT_EQ(our_queue.empty(), std_queue.empty());
}

TEST(queue, Operator_Move) {
  s21::queue<int> our_queue_int = {1, 2, 3};
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  s21::queue<int> our_queue_empty;
  std::queue<int> std_queue_empty;
  our_queue_empty = std::move(our_queue_int);
  std_queue_empty = std::move(std_queue_int);
  EXPECT_EQ(our_queue_empty.front(), std_queue_empty.front());
  EXPECT_EQ(our_queue_empty.back(), std_queue_empty.back());
  EXPECT_EQ(our_queue_int.empty(), std_queue_int.empty());
}

TEST(queue, FrontAndBack) {
  s21::queue<int> our_queue_int = {1, 2, 3};
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  s21::queue<double> our_queue_double = {1.1f, 2.1f, 3.1f};
  std::queue<double> std_queue_double;
  std_queue_double.push(1.1f);
  std_queue_double.push(2.1f);
  std_queue_double.push(3.1f);
  s21::queue<std::string> our_queue_string = {"abc", "def", "ghf"};
  std::queue<std::string> std_queue_string;
  std_queue_string.push("abc");
  std_queue_string.push("def");
  std_queue_string.push("ghf");
  EXPECT_EQ(our_queue_int.front(), std_queue_int.front());
  EXPECT_EQ(our_queue_double.front(), std_queue_double.front());
  EXPECT_EQ(our_queue_string.front(), std_queue_string.front());
  EXPECT_EQ(our_queue_int.back(), std_queue_int.back());
  EXPECT_EQ(our_queue_double.back(), std_queue_double.back());
  EXPECT_EQ(our_queue_string.back(), std_queue_string.back());
}

TEST(queue, Empty) {
  s21::queue<int> our_queue_int = {1, 2, 3};
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  EXPECT_EQ(our_queue_int.empty(), std_queue_int.empty());
  s21::queue<int> our_queue_empty;
  std::queue<int> std_queue_empty;
  EXPECT_EQ(our_queue_empty.empty(), std_queue_empty.empty());
}

TEST(queue, Size) {
  s21::queue<int> our_queue_int = {1, 2, 3};
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  EXPECT_EQ(our_queue_int.size(), std_queue_int.size());
  s21::queue<int> our_queue_empty;
  std::queue<int> std_queue_empty;
  EXPECT_EQ(our_queue_empty.size(), std_queue_empty.size());
}

TEST(queue, Push) {
  s21::queue<int> our_queue_int;
  our_queue_int.push(1);
  our_queue_int.push(2);
  our_queue_int.push(3);
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  EXPECT_EQ(our_queue_int.front(), std_queue_int.front());
  EXPECT_EQ(our_queue_int.back(), std_queue_int.back());
}

TEST(queue, Pop) {
  s21::queue<int> our_queue_int;
  our_queue_int.push(1);
  our_queue_int.push(2);
  our_queue_int.push(3);
  our_queue_int.pop();
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  std_queue_int.pop();
  EXPECT_EQ(our_queue_int.front(), std_queue_int.front());
  EXPECT_EQ(our_queue_int.back(), std_queue_int.back());
  our_queue_int.pop();
  our_queue_int.pop();
  std_queue_int.pop();
  std_queue_int.pop();
  EXPECT_EQ(our_queue_int.empty(), std_queue_int.empty());
}

TEST(queue, Swap) {
  s21::queue<int> our_queue_int = {1, 2, 3};
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  s21::queue<int> our_queue_empty;
  std::queue<int> std_queue_empty;
  our_queue_empty.swap(our_queue_int);
  std_queue_empty.swap(std_queue_int);
  EXPECT_EQ(our_queue_empty.front(), std_queue_empty.front());
  EXPECT_EQ(our_queue_empty.back(), std_queue_empty.back());
  EXPECT_EQ(our_queue_int.empty(), std_queue_int.empty());
}

TEST(queue, InsertManyBack) {
  s21::queue<int> our_queue_int;
  our_queue_int.insert_many_back(1, 2, 3);
  EXPECT_EQ(our_queue_int.front(), 1);
  EXPECT_EQ(our_queue_int.back(), 3);
}

TEST(queue, null_constructor) {
  queueTest data;
  EXPECT_EQ(data.s21_queue_null.size(), data.std_queue_null.size());
  EXPECT_EQ(data.s21_queue_null.empty(), data.std_queue_null.empty());
}

TEST(queue, copy_constructor) {
  queueTest data;
  data.s21_queue_null.push(3);
  data.s21_queue_null.push(4);

  data.std_queue_null.push(3);
  data.std_queue_null.push(4);

  s21::queue<int> a(data.s21_queue_null);
  std::queue<int> b(data.std_queue_null);

  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a.empty(), b.empty());

  while (!a.empty()) {
    EXPECT_EQ(a.front(), b.front());
    a.pop();
    b.pop();
  }

  while (!data.s21_queue_null.empty()) {
    EXPECT_EQ(data.s21_queue_null.front(), data.std_queue_null.front());
    data.s21_queue_null.pop();
    data.std_queue_null.pop();
  }
}

TEST(queue, move_constructor) {
  queueTest data;
  data.s21_queue_null.push(3);
  data.s21_queue_null.push(4);

  data.std_queue_null.push(3);
  data.std_queue_null.push(4);

  s21::queue<int> a(std::move(data.s21_queue_null));
  std::queue<int> b(std::move(data.std_queue_null));

  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a.empty(), b.empty());

  while (!a.empty()) {
    EXPECT_EQ(a.front(), b.front());
    a.pop();
    b.pop();
  }

  while (!data.s21_queue_null.empty()) {
    EXPECT_EQ(data.s21_queue_null.front(), data.std_queue_null.front());
    data.s21_queue_null.pop();
    data.std_queue_null.pop();
  }
}

TEST(queue, copy_operator) {
  queueTest data;
  data.s21_queue_null.push(3);
  data.s21_queue_null.push(4);

  data.std_queue_null.push(3);
  data.std_queue_null.push(4);

  s21::queue<int> a;
  a = data.s21_queue_null;
  std::queue<int> b;
  b = data.std_queue_null;

  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a.empty(), b.empty());

  while (!a.empty()) {
    EXPECT_EQ(a.front(), b.front());
    a.pop();
    b.pop();
  }

  while (!data.s21_queue_null.empty()) {
    EXPECT_EQ(data.s21_queue_null.front(), data.std_queue_null.front());
    data.s21_queue_null.pop();
    data.std_queue_null.pop();
  }
}

TEST(queue, move_operator) {
  queueTest data;
  data.s21_queue_null.push(3);
  data.s21_queue_null.push(4);

  data.std_queue_null.push(3);
  data.std_queue_null.push(4);

  s21::queue<int> a;
  a = std::move(data.s21_queue_null);
  std::queue<int> b;
  b = std::move(data.std_queue_null);

  EXPECT_EQ(a.size(), b.size());
  EXPECT_EQ(a.empty(), b.empty());

  while (!a.empty()) {
    EXPECT_EQ(a.front(), b.front());
    a.pop();
    b.pop();
  }

  while (!data.s21_queue_null.empty()) {
    EXPECT_EQ(data.s21_queue_null.front(), data.std_queue_null.front());
    data.s21_queue_null.pop();
    data.std_queue_null.pop();
  }
}

TEST(queue, swap) {
  queueTest data;

  data.std_queue_swap1.push(1);
  data.std_queue_swap1.push(1);
  data.std_queue_swap1.push(1);

  data.std_queue_swap2.push(2);
  data.std_queue_swap2.push(2);
  data.std_queue_swap2.push(2);
  data.std_queue_swap2.push(2);

  data.std_queue_swap1.swap(data.std_queue_swap2);
  data.s21_queue_swap1.swap(data.s21_queue_swap2);

  EXPECT_EQ(data.std_queue_swap1.front(), data.s21_queue_swap1.front());
  EXPECT_EQ(data.std_queue_swap1.back(), data.s21_queue_swap1.back());

  EXPECT_EQ(data.std_queue_swap2.front(), data.s21_queue_swap2.front());
  EXPECT_EQ(data.std_queue_swap2.back(), data.s21_queue_swap2.back());

  while (!data.s21_queue_swap2.empty()) {
    EXPECT_EQ(data.s21_queue_swap2.front(), data.std_queue_swap2.front());
    EXPECT_EQ(data.s21_queue_swap2.front(), 1);
    EXPECT_EQ(data.s21_queue_swap2.back(), 1);
    data.s21_queue_swap2.pop();
    data.std_queue_swap2.pop();
  }

  while (!data.s21_queue_swap1.empty()) {
    EXPECT_EQ(data.s21_queue_swap1.front(), data.std_queue_swap1.front());
    EXPECT_EQ(data.s21_queue_swap1.front(), 2);
    EXPECT_EQ(data.s21_queue_swap1.back(), 2);

    data.s21_queue_swap1.pop();
    data.std_queue_swap1.pop();
  }
}
