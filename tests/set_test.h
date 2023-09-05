#include <gtest/gtest.h>

#include "../s21_set.h"

TEST(set, ConstructorDefault) {
  s21::set<char> my_set;
  std::set<char> std_set;
  EXPECT_EQ(my_set.empty(), std_set.empty());
}

TEST(set, setConstructors) {
  s21::set<int> my_set{54, 48, 3, 1, -6, 1000000, 4, -10};
  std::set<int> std_set{54, 48, 3, 1, -6, 1000000, 4, -10};

  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();

  while (my_iter != my_set.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
  ASSERT_TRUE(std_iter == std_set.end());

  s21::set<int> my_set2(my_set);
  std::set<int> std_set2(std_set);

  my_iter = my_set2.begin();
  std_iter = std_set2.begin();

  while (std_iter != std_set2.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
  ASSERT_TRUE(my_iter == my_set2.end());

  s21::set<int> my_set3 = std::move(my_set2);
  std::set<int> std_set3 = std::move(std_set2);

  my_iter = my_set3.begin();
  std_iter = std_set3.begin();

  while (std_iter != std_set3.end()) {
    ASSERT_TRUE(*my_iter == *std_iter);
    ASSERT_TRUE(*my_iter == *std_iter);
    ++my_iter;
    ++std_iter;
  }
  ASSERT_TRUE(my_iter == my_set3.end());

  s21::set<int> my_set4 = std::move(my_set2);
  std::set<int> std_set4 = std::move(std_set2);
}

TEST(set, ConstructorInitializer1) {
  s21::set<int> my_set = {54, 48, 3, 1, -6, 1000000, 4, -10};
  std::set<int> std_set = {54, 48, 3, 1, -6, 1000000, 4, -10};
  EXPECT_EQ(my_set.size(), std_set.size());
  auto my_it = my_set.begin();
  auto std_iter = std_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++std_iter) {
    EXPECT_TRUE(*std_iter == *my_it);
  }
}

TEST(set, ConstructorInitializer2) {
  s21::set<int> my_set = {};
  std::set<int> std_set = {};
  EXPECT_EQ(my_set.size(), std_set.size());
  auto my_it = my_set.begin();
  auto std_it = std_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++std_it) {
    EXPECT_TRUE(*std_it == *my_it);
  }
}

TEST(set, ConstructorCopySet) {
  s21::set<int> my_set = {54, 48, 3, 1, -6, 1000000, 4, -10};
  std::set<int> std_set = {54, 48, 3, 1, -6, 1000000, 4, -10};
  s21::set<int> my_set_copy = my_set;
  std::set<int> std_set_copy = std_set;
  EXPECT_EQ(my_set_copy.size(), std_set_copy.size());
  auto my_it = my_set_copy.begin();
  auto std_it = std_set_copy.begin();
  for (; my_it != my_set_copy.end(); ++my_it, ++std_it) {
    EXPECT_TRUE(*std_it == *my_it);
  }
}

TEST(set, ConstructorMove) {
  s21::set<int> my_set = {54, 48, 3, 1, -6, 1000000, 4, -10};
  std::set<int> std_set = {54, 48, 3, 1, -6, 1000000, 4, -10};
  s21::set<int> my_set_copy = std::move(my_set);
  std::set<int> std_set_copy = std::move(std_set);
  EXPECT_EQ(my_set_copy.size(), std_set_copy.size());
  auto my_it = my_set_copy.begin();
  auto std_it = std_set_copy.begin();
  for (; my_it != my_set_copy.end(); ++my_it, ++std_it) {
    EXPECT_TRUE(*std_it == *my_it);
  }
}

TEST(set, SetIterators) {
  s21::set<std::string> my_set = {"Съешь",       "ещё",   "этих", "мягких",
                                  "французских", "булок", "да",   "выпей",
                                  "же",          "чаю"};
  std::set<std::string> std_set = {"Съешь",       "ещё",   "этих", "мягких",
                                   "французских", "булок", "да",   "выпей",
                                   "же",          "чаю"};
  auto my_it = my_set.begin();
  auto std_it = std_set.begin();

  for (; my_it != my_set.end() && std_it != std_set.end(); ++my_it, ++std_it) {
    EXPECT_TRUE(*std_it == *my_it);
  }
}

TEST(set, Capacity) {
  s21::set<char> my_empty_set;
  std::set<char> orig_empty_set;
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.insert('b');
  orig_empty_set.insert('c');
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
}

TEST(set, Clear) {
  s21::set<char> my_empty_set;
  std::set<char> orig_empty_set;
  my_empty_set.clear();
  orig_empty_set.clear();
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.insert('a');
  orig_empty_set.insert('b');
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.clear();
  orig_empty_set.clear();
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
}

TEST(set, Insert) {
  s21::set<int> my_set = {1, 3, 4, 5, 6, 8, 9};
  std::set<int> orig_set = {1, 3, 4, 5, 6, 8, 9};
  auto my_pr = my_set.insert(2);
  auto orig_pr = orig_set.insert(2);
  EXPECT_TRUE(my_pr.second == orig_pr.second);
  EXPECT_TRUE(*my_pr.first == *orig_pr.first);
  my_pr = my_set.insert(2);
  orig_pr = orig_set.insert(2);
  EXPECT_TRUE(my_pr.second == orig_pr.second);
  EXPECT_TRUE(*my_pr.first == *orig_pr.first);
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end() && orig_it != orig_set.end();
       ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(set, setInsert2) {
  s21::set<int> my_set;
  std::set<int> std_set;

  my_set.insert(1);
  std_set.insert(1);
  my_set.insert(2);
  std_set.insert(2);
  my_set.insert(22);
  std_set.insert(22);
  my_set.insert(33);
  std_set.insert(33);
  my_set.insert(7);
  std_set.insert(7);
  my_set.insert(-5);
  std_set.insert(-5);
  my_set.insert(12);
  std_set.insert(12);
  my_set.insert(17);
  std_set.insert(17);
  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();
  while (std_iter != std_set.end()) {
    ASSERT_EQ((*my_iter), (*std_iter));
    ++my_iter;
    ++std_iter;
  }
}

TEST(set, setErace1) {
  s21::set<int> my_set{54, 48, 3, 1, -6, 1000000, 4, -10};
  std::set<int> std_set{54, 48, 3, 1, -6, 1000000, 4, -10};

  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();

  my_set.erase(my_iter);
  std_set.erase(std_iter);

  my_iter = my_set.begin();
  std_iter = std_set.begin();

  while (std_iter != std_set.end()) {
    ASSERT_TRUE((*my_iter) == (*std_iter));
    ASSERT_TRUE((*my_iter) == (*std_iter));
    ++my_iter;
    ++std_iter;
  }
  ASSERT_TRUE(my_iter == my_set.end());
}

TEST(set, Swap) {
  s21::set<int> my_set = {65, 75, 34};
  s21::set<int> my_swap_set = {1, 2, 3, 4, 5, 6, 7, 8};

  my_set.swap(my_swap_set);
  EXPECT_EQ(my_set.size(), 8);
  EXPECT_EQ(my_swap_set.size(), 3);
  EXPECT_EQ(*my_set.begin(), 1);
  EXPECT_EQ(*my_swap_set.begin(), 34);
}

TEST(set, MergeSet1) {
  s21::set<int> my_set = {1, 6};
  s21::set<int> my_merge_set = {3, 4, 5};
  my_set.merge(my_merge_set);

  std::set<int> orig_set = {1, 6};
  std::set<int> orig_merge_set = {3, 4, 5};
  orig_set.merge(orig_merge_set);
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();

  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }

  EXPECT_EQ(orig_set.size(), my_set.size());
}

TEST(set, Find) {
  s21::set<std::string> my_set = {"Съешь",       "ещё",   "этих", "мягких",
                                  "французских", "булок", "да",   "выпей",
                                  "же",          "чаю"};
  s21::set<std::string> orig_set = {"Съешь",       "ещё",   "этих", "мягких",
                                    "французских", "булок", "да",   "выпей",
                                    "же",          "чаю"};
  auto my_it = my_set.find("французских");
  auto orig_it = orig_set.find("французских");
  EXPECT_TRUE(*orig_it == *my_it);
}

TEST(set, Contains) {
  s21::set<std::string> my_set = {"Съешь",       "ещё",   "этих", "мягких",
                                  "французских", "булок", "да",   "выпей",
                                  "же",          "чаю"};
  s21::set<std::string> orig_set = {"Съешь",       "ещё",   "этих", "мягких",
                                    "французских", "булок", "да",   "выпей",
                                    "же",          "чаю"};
  EXPECT_EQ(my_set.contains("да"), orig_set.contains("да"));
  EXPECT_EQ(my_set.contains("Хочу умереть"), orig_set.contains("Хочу умереть"));
}

TEST(set, InsertMany) {
  s21::set<int> my_set;
  auto results = my_set.insert_many(1, 2, 3, 4, 5);
  ASSERT_EQ(results.size(), 5);
  for (const auto& result : results) {
    EXPECT_TRUE(result.second);
  }
  auto duplicate_results = my_set.insert_many(1, 2, 3, 4, 5);
  ASSERT_EQ(duplicate_results.size(), 5);
  for (const auto& result : duplicate_results) {
    EXPECT_FALSE(result.second);
  }
}

TEST(set, EraseEmptySet) {
  s21::set<int> my_set;
  auto my_it = my_set.begin();
  my_set.erase(my_it);
  ASSERT_TRUE(my_set.empty());
}

TEST(set, FindExistingElement) {
  s21::set<int> my_set = {1, 2, 3, 4, 5};
  auto it = my_set.find(3);
  ASSERT_TRUE(it != my_set.end());
  ASSERT_EQ(*it, 3);
}

TEST(set, FindNonExistingElement) {
  s21::set<int> my_set = {1, 2, 3, 4, 5};
  auto it = my_set.find(10);
  ASSERT_TRUE(it == my_set.end());
}
