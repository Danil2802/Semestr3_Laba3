#include "SinglyLinkedList.h"
#include <gtest/gtest.h>
#include <sstream>

using namespace std;

TEST(SinglyLinkedListTest, AddToHead_Search)
{
    SinglyLinkedList list;
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

TEST(SinglyLinkedListTest, AddToTail_Search)
{
    SinglyLinkedList list;
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

TEST(SinglyLinkedListTest, RemoveFromHead)
{
    SinglyLinkedList list;

    stringstream buffer;
    streambuf *old = cout.rdbuf(buffer.rdbuf());

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

TEST(SinglyLinkedListTest, RemoveFromTail)
{
    SinglyLinkedList list;

    stringstream buffer;
    streambuf *old = cout.rdbuf(buffer.rdbuf());

    list.removeFromTail();

    string output = buffer.str();
    cout.rdbuf(old);

    EXPECT_EQ(output, "List is empty!\n");

    list.addToHead("value1");
    list.addToHead("value2");
    list.addToHead("value3");

    list.removeFromTail();

    EXPECT_FALSE(list.search("value1"));
    EXPECT_TRUE(list.search("value2"));
    EXPECT_TRUE(list.search("value3"));

    list.removeFromTail();

    EXPECT_FALSE(list.search("value1"));
    EXPECT_FALSE(list.search("value2"));
    EXPECT_TRUE(list.search("value3"));

    list.removeFromTail();

    EXPECT_FALSE(list.search("value1"));
    EXPECT_FALSE(list.search("value2"));
    EXPECT_FALSE(list.search("value3"));
}

TEST(SinglyLinkedListTest, RemoveByValue)
{
    SinglyLinkedList list;

    stringstream buffer;
    streambuf *old = cout.rdbuf(buffer.rdbuf());

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

TEST(SinglyLinkedListTest, SaveAndLoad)
{
    SinglyLinkedList list1;
    list1.addToHead("first");
    list1.addToTail("second");
    list1.saveToFile("file3.data/my_singlylinkedlist");

    SinglyLinkedList list2;
    list2.loadFromFile("file3.data/my_singlylinkedlist");
    EXPECT_TRUE(list2.search("first"));
    EXPECT_TRUE(list2.search("second"));
}

TEST(SinglyLinkedListTest, Print)
{
    SinglyLinkedList list;
    list.addToHead("first");
    list.addToTail("second");

    stringstream buffer;
    streambuf *old = cout.rdbuf(buffer.rdbuf());

    list.print("file3.data/my_singlylinkedlist");

    string output = buffer.str();
    cout.rdbuf(old);

    EXPECT_EQ(output, "my_singlylinkedlist: first second \n");
}

TEST(SinglyLinkedListTest, SaveAndLoadBinary)
{
    SinglyLinkedList list1;
    list1.addToHead("first");
    list1.addToTail("second");
    list1.addToTail("third");
    list1.saveToBinaryFile("file4.data/singlylinkedlist_binary.data");

    SinglyLinkedList list2;
    list2.loadFromBinaryFile("file4.data/singlylinkedlist_binary.data");

    EXPECT_TRUE(list2.search("first"));
    EXPECT_TRUE(list2.search("second"));
    EXPECT_TRUE(list2.search("third"));
}
