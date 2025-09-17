#include "HashTable.h"
#include <gtest/gtest.h>
#include <sstream>

using namespace std;

TEST(HashTableTest, Insert_Get) {
    HashTable table;

    EXPECT_EQ(table.get("key1"), "");
    EXPECT_EQ(table.get("key2"), "");
    EXPECT_EQ(table.get("key3"), "");

    table.insert("key1", "value1");
    table.insert("key2", "value2");

    EXPECT_EQ(table.get("key1"), "value1");
    EXPECT_EQ(table.get("key2"), "value2");
    EXPECT_EQ(table.get("key3"), "");

    table.insert("key1", "value3");
    table.insert("key2", "value4");

    EXPECT_EQ(table.get("key1"), "value3");
    EXPECT_EQ(table.get("key2"), "value4");
    EXPECT_EQ(table.get("key3"), "");
    EXPECT_EQ(table.get("key4"), "");
}

TEST(HashTableTest, Remove) {
    HashTable table;

    stringstream buffer1;
    streambuf* old1 = cout.rdbuf(buffer1.rdbuf());

    table.remove("key1");

    string output1 = buffer1.str();
    cout.rdbuf(old1);

    EXPECT_EQ(output1, "Not found!\n");

    table.insert("key1", "value1");

    table.remove("key1");
    EXPECT_EQ(table.get("key1"), "");
}

TEST(HashTableTest, Hasher) {
    HashTable table;
    EXPECT_EQ(table.hasher("K1", 2, 31), 0);
}

TEST(HashTableTest, Count) {
    HashTable table;
    EXPECT_EQ(table.count(), 0);
    table.insert("key1", "value1");
    EXPECT_EQ(table.count(), 1);
    table.insert("key2", "value2");
    EXPECT_EQ(table.count(), 2);
    table.remove("key1");
    EXPECT_EQ(table.count(), 1);
}

TEST(HashTableTest, SaveAndLoad) {
    HashTable table1;
    table1.insert("key1", "value1");
    table1.insert("key2", "value2");
    table1.saveToFile("file3.data/my_hash");

    HashTable table2;
    table2.loadFromFile("file3.data/my_hash");
    EXPECT_EQ(table2.get("key1"), "value1");
    EXPECT_EQ(table2.get("key2"), "value2");
}


TEST(HashTableTest, Print) {
    HashTable table;
    table.insert("key1", "value1");
    table.insert("key2", "value2");

    stringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());

    table.print("file3.data/my_hash");

    string output = buffer.str();
    cout.rdbuf(old);

    EXPECT_EQ(output, "my_hash:\nKey: key1, Value: value1\nKey: key2, Value: value2\n");
}

TEST(HashTableTest, Overflow_rehash) {
    HashTable table(2);
    table.insert("key1", "value1");
    table.insert("key2", "value2");
    table.insert("key3", "value3");
    table.insert("key4", "value4");
    table.insert("key5", "value5");

    EXPECT_EQ(table.get("key1"), "value1");
    EXPECT_EQ(table.get("key2"), "value2");
    EXPECT_EQ(table.get("key3"), "value3");
    EXPECT_EQ(table.get("key4"), "value4");
    EXPECT_EQ(table.get("key5"), "value5");
}

TEST(HashTableTest, SaveAndLoadBinary) {
    HashTable table1;
    table1.insert("key1", "value1");
    table1.insert("key2", "value2");
    table1.insert("key3", "value3");
    table1.saveToBinaryFile("file4.data/hash_binary.data");

    HashTable table2;
    table2.loadFromBinaryFile("file4.data/hash_binary.data");
    EXPECT_EQ(table2.get("key1"), "value1");
    EXPECT_EQ(table2.get("key2"), "value2");
    EXPECT_EQ(table2.get("key3"), "value3");
}
