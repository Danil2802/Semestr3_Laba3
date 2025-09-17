#include "DoublyLinkedList.h"
#include <gtest/gtest.h>
#include <sstream>

using namespace std;

TEST(DoublyLinkedListTest, AddToHead_Search) {
    DoublyLinkedList list;
    list.addToHead("first");
    list.addToHead("second");

    EXPECT_TRUE(list.search("first"));
    EXPECT_TRUE(list.search("second"));
    EXPECT_FALSE(list.search("third"));

    list.removeFromHead();

    EXPECT_TRUE(list.search("first"));
    EXPECT_FALSE(list.search("second"));
    EXPECT_FALSE(list.search("third"));
}

TEST(DoublyLinkedListTest, AddToTail_Search) {
    DoublyLinkedList list;
    list.addToTail("first");
    list.addToTail("second");

    EXPECT_TRUE(list.search("first"));
    EXPECT_TRUE(list.search("second"));
    EXPECT_FALSE(list.search("third"));

    list.removeFromHead();

    EXPECT_FALSE(list.search("first"));
    EXPECT_TRUE(list.search("second"));
    EXPECT_FALSE(list.search("third"));
}

TEST(DoublyLinkedListTest, RemoveFromHead) {
    DoublyLinkedList list;

    stringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());

    list.removeFromHead();

    string output = buffer.str();
    cout.rdbuf(old);

    EXPECT_EQ(output, "List is empty!\n");

    list.addToHead("value1");
    list.addToHead("value2");
    
    list.removeFromHead();

    EXPECT_FALSE(list.search("value2"));
    EXPECT_TRUE(list.search("value1"));

    list.removeFromHead();

    EXPECT_FALSE(list.search("value1"));
    EXPECT_FALSE(list.search("value2"));
}

TEST(DoublyLinkedListTest, RemoveFromTail) {
    DoublyLinkedList list;

    stringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());

    list.removeFromTail();

    string output = buffer.str();
    cout.rdbuf(old);

    EXPECT_EQ(output, "List is empty!\n");

    list.addToHead("value1");
    list.addToHead("value2");
    
    list.removeFromTail();

    EXPECT_FALSE(list.search("value1"));
    EXPECT_TRUE(list.search("value2"));

    list.removeFromTail();

    EXPECT_FALSE(list.search("value1"));
    EXPECT_FALSE(list.search("value2"));
}

TEST(DoublyLinkedListTest, RemoveByValue) {
    DoublyLinkedList list;

    stringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());

    list.addToTail("first");
    list.addToTail("second");
    list.addToTail("third");
    list.removeByValue("second");
    list.removeByValue("fourth");

    string output = buffer.str();
    cout.rdbuf(old);

    EXPECT_EQ(output, "Value not found!\n");
    EXPECT_FALSE(list.search("second"));
    EXPECT_TRUE(list.search("first"));
    EXPECT_TRUE(list.search("third"));

    list.removeByValue("third");

    EXPECT_FALSE(list.search("second"));
    EXPECT_TRUE(list.search("first"));
    EXPECT_FALSE(list.search("third"));

    list.removeByValue("first");

    EXPECT_FALSE(list.search("second"));
    EXPECT_FALSE(list.search("first"));
    EXPECT_FALSE(list.search("third"));
}

TEST(DoublyLinkedListTest, SaveAndLoad) {
    DoublyLinkedList list1;
    list1.addToHead("first");
    list1.addToTail("second");
    list1.saveToFile("file3.data/my_doublylinkedlist");

    DoublyLinkedList list2;
    list2.loadFromFile("file3.data/my_doublylinkedlist");
    EXPECT_TRUE(list2.search("first"));
    EXPECT_TRUE(list2.search("second"));
}

TEST(DoublyLinkedListTest, Print) {
    DoublyLinkedList list;
    list.addToHead("first");
    list.addToTail("second");

    stringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());

    list.print("file3.data/my_doublylinkedlist");

    string output = buffer.str();
    cout.rdbuf(old);

    EXPECT_EQ(output, "my_doublylinkedlist: first second \n");
}

TEST(DoublyLinkedListTest, SaveAndLoadBinary) {
    DoublyLinkedList list1;
    list1.addToHead("first");
    list1.addToTail("second");
    list1.addToTail("third");
    list1.saveToBinaryFile("file4.data/doublylinkedlist_binary.data");

    DoublyLinkedList list2;
    list2.loadFromBinaryFile("file4.data/doublylinkedlist_binary.data");

    EXPECT_TRUE(list2.search("first"));
    EXPECT_TRUE(list2.search("second"));
    EXPECT_TRUE(list2.search("third"));
}
