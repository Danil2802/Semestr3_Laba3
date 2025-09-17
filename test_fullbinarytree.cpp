#include "FullBinaryTree.h"
#include <gtest/gtest.h>
#include <sstream>

using namespace std;

TEST(FullBinaryTreeTest, Add_Search) {
    FullBinaryTree tree;

    EXPECT_FALSE(tree.search("10"));
    EXPECT_FALSE(tree.search("20"));
    EXPECT_FALSE(tree.search("30"));

    tree.add("10", "L", "20");

    EXPECT_TRUE(tree.search("10"));
    EXPECT_TRUE(tree.search("20"));
    EXPECT_FALSE(tree.search("30"));

    tree.add("10", "R", "30");

    EXPECT_TRUE(tree.search("10"));
    EXPECT_TRUE(tree.search("20"));
    EXPECT_TRUE(tree.search("30"));

    tree.add("20", "R", "40");

    EXPECT_TRUE(tree.search("10"));
    EXPECT_TRUE(tree.search("20"));
    EXPECT_TRUE(tree.search("30"));
    EXPECT_TRUE(tree.search("40"));

    stringstream buffer1;
    streambuf* old1 = cout.rdbuf(buffer1.rdbuf());

    tree.add("50", "L", "60");

    string output1 = buffer1.str();
    cout.rdbuf(old1);

    EXPECT_EQ(output1, "Error: Parent node '50' not found!\n");
    EXPECT_FALSE(tree.search("50"));
    EXPECT_FALSE(tree.search("60"));

    stringstream buffer2;
    streambuf* old2 = cout.rdbuf(buffer2.rdbuf());

    tree.add("20", "L", "30");

    string output2 = buffer2.str();
    cout.rdbuf(old2);

    EXPECT_EQ(output2, "Error: Node with value '30' already exists!\n");
    EXPECT_TRUE(tree.search("20"));
    EXPECT_TRUE(tree.search("30"));

    stringstream buffer3;
    streambuf* old3 = cout.rdbuf(buffer3.rdbuf());

    tree.add("20", "L", "70");

    string output3 = buffer3.str();
    cout.rdbuf(old3);

    EXPECT_EQ(output3, "");
    EXPECT_TRUE(tree.search("10"));
    EXPECT_TRUE(tree.search("20"));
    EXPECT_TRUE(tree.search("30"));
    EXPECT_TRUE(tree.search("40"));
    EXPECT_TRUE(tree.search("70"));

    stringstream buffer4;
    streambuf* old4 = cout.rdbuf(buffer4.rdbuf());

    tree.add("20", "L", "80");

    string output4 = buffer4.str();
    cout.rdbuf(old4);

    EXPECT_EQ(output4, "Error: Left child already exists for node '20'!\n");

    stringstream buffer5;
    streambuf* old5 = cout.rdbuf(buffer5.rdbuf());

    tree.add("10", "R", "90");

    string output5 = buffer5.str();
    cout.rdbuf(old5);

    EXPECT_EQ(output5, "Error: Right child already exists for node '10'!\n");

    stringstream buffer6;
    streambuf* old6 = cout.rdbuf(buffer6.rdbuf());

    tree.add("30", "T", "100");

    string output6 = buffer6.str();
    cout.rdbuf(old6);

    EXPECT_EQ(output6, "Error: Invalid side 'T'. Use 'L' or 'R'.\n");
}

TEST(FullBinaryTreeTest, IsFull) {
    FullBinaryTree tree;
    EXPECT_TRUE(tree.isFullBinaryTree());
    tree.add("10", "L", "20");
    EXPECT_FALSE(tree.isFullBinaryTree());
    tree.add("10", "R", "30");
    EXPECT_TRUE(tree.isFullBinaryTree());
    tree.add("20", "L", "40");
    EXPECT_FALSE(tree.isFullBinaryTree());
    tree.add("40", "L", "50");
    EXPECT_FALSE(tree.isFullBinaryTree());
    tree.add("20", "R", "60");
    EXPECT_FALSE(tree.isFullBinaryTree());
    tree.add("40", "R", "70");
    EXPECT_TRUE(tree.isFullBinaryTree());
}

TEST(FullBinaryTreeTest, SaveAndLoad) {
    FullBinaryTree tree1;
    tree1.add("10", "L", "20");
    tree1.add("20", "L", "30");
    tree1.saveToFile("file3.data/my_tree");

    FullBinaryTree tree2;
    tree2.loadFromFile("file3.data/my_tree");
    EXPECT_TRUE(tree2.search("10"));
    EXPECT_TRUE(tree2.search("20"));
    EXPECT_TRUE(tree2.search("30"));
}

TEST(FullBinaryTreeTest, Print_1) {
    FullBinaryTree tree1;
    tree1.saveToFile("file3.data/my_tree");

    stringstream buffer1;
    streambuf* old1 = cout.rdbuf(buffer1.rdbuf());

    tree1.loadFromFile("file3.data/my_tree");
    tree1.print("file3.data/my_tree", 1);

    string output1 = buffer1.str();
    cout.rdbuf(old1);

    EXPECT_EQ(output1, "Tree is empty\n");

    tree1.add("10", "L", "20");
    tree1.add("10", "R", "30");
    tree1.add("20", "L", "40");
    tree1.saveToFile("file3.data/my_tree");

    FullBinaryTree tree2;
    stringstream buffer2;
    streambuf* old2 = cout.rdbuf(buffer2.rdbuf());

    tree2.loadFromFile("file3.data/my_tree");
    tree2.print("file3.data/my_tree", 3);

    string output2 = buffer2.str();
    cout.rdbuf(old2);

    EXPECT_EQ(output2, "Error: Invalid mode. Use 1 (tree) or 2 (file content)\n");

    FullBinaryTree tree3;
    stringstream buffer3;
    streambuf* old3 = cout.rdbuf(buffer3.rdbuf());

    tree3.loadFromFile("file3.data/my_tree");
    tree3.print("file3.data/my_tree", 1);

    string output3 = buffer3.str();
    cout.rdbuf(old3);

    EXPECT_EQ(output3, "my_tree: \n                        \n       30               \n                        \n10                       \n                        \n       20               \n               40       \n");
}

TEST(FullBinaryTreeTest, Print_2) {
    FullBinaryTree tree1;
    tree1.add("10", "L", "20");
    tree1.add("10", "R", "30");
    tree1.add("20", "L", "40");
    tree1.saveToFile("file3.data/my_tree");

    FullBinaryTree tree2;
    stringstream buffer1;
    streambuf* old1 = cout.rdbuf(buffer1.rdbuf());

    tree2.loadFromFile("file3.data/my_tree");
    tree2.print("file3.data/my_tree", 3);

    string output1 = buffer1.str();
    cout.rdbuf(old1);

    EXPECT_EQ(output1, "Error: Invalid mode. Use 1 (tree) or 2 (file content)\n");

    FullBinaryTree tree3;
    stringstream buffer2;
    streambuf* old2 = cout.rdbuf(buffer2.rdbuf());

    tree3.loadFromFile("file3.data/my_tree");
    tree3.print("file3.data/my_tree", 2);

    string output2 = buffer2.str();
    cout.rdbuf(old2);

    EXPECT_EQ(output2, "my_tree:\n10\n10 L 20\n20 L 40\n10 R 30\n");
}

TEST(FullBinaryTreeTest, SaveAndLoadBinary) {
    FullBinaryTree tree1;
    tree1.add("10", "L", "20");
    tree1.add("10", "R", "30");
    tree1.add("20", "L", "40");
    EXPECT_FALSE(tree1.isFullBinaryTree());
    tree1.saveToBinaryFile("file4.data/tree_binary.data");

    FullBinaryTree tree2;
    tree2.loadFromBinaryFile("file4.data/tree_binary.data");

    EXPECT_TRUE(tree2.search("10"));
    EXPECT_TRUE(tree2.search("20"));
    EXPECT_TRUE(tree2.search("30"));
    EXPECT_TRUE(tree2.search("40"));
    EXPECT_FALSE(tree2.isFullBinaryTree());
}
