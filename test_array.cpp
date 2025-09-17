#include "Array.h"
#include <gtest/gtest.h>
#include <sstream>

using namespace std;

TEST(ArrayTest, AddToEnd_Get) {
    Array arr;

    EXPECT_EQ(arr.get(0), "");
    EXPECT_EQ(arr.get(1), "");
    EXPECT_EQ(arr.get(-1), "");

    arr.addToEnd("first");

    EXPECT_EQ(arr.get(0), "first");
    EXPECT_EQ(arr.get(1), "");
    EXPECT_EQ(arr.get(-1), "");

    arr.addToEnd("second");

    EXPECT_EQ(arr.get(0), "first");
    EXPECT_EQ(arr.get(1), "second");
    EXPECT_EQ(arr.get(2), "");
    EXPECT_EQ(arr.get(-1), "");

    arr.remove(0);

    EXPECT_EQ(arr.get(0), "second");
    EXPECT_EQ(arr.get(1), "");
    EXPECT_EQ(arr.get(-1), "");

    arr.remove(0);

    EXPECT_EQ(arr.get(0), "");
    EXPECT_EQ(arr.get(1), "");
    EXPECT_EQ(arr.get(-1), "");
}

TEST(ArrayTest, Add_Get) {
    Array arr;

    EXPECT_EQ(arr.get(0), "");
    EXPECT_EQ(arr.get(1), "");
    EXPECT_EQ(arr.get(-1), "");

    stringstream buffer1;
    streambuf* old1 = cout.rdbuf(buffer1.rdbuf());

    arr.add(-1, "first");

    string output1 = buffer1.str();
    cout.rdbuf(old1);

    EXPECT_EQ(output1, "Invalid index.\n");

    stringstream buffer2;
    streambuf* old2 = cout.rdbuf(buffer2.rdbuf());

    arr.add(1, "first");

    string output2 = buffer2.str();
    cout.rdbuf(old2);

    EXPECT_EQ(output2, "Invalid index.\n");

    arr.add(0, "first");

    EXPECT_EQ(arr.get(0), "first");
    EXPECT_EQ(arr.get(1), "");
    EXPECT_EQ(arr.get(-1), "");

    stringstream buffer3;
    streambuf* old3 = cout.rdbuf(buffer3.rdbuf());

    arr.add(2, "first");

    string output3 = buffer3.str();
    cout.rdbuf(old3);

    EXPECT_EQ(output3, "Invalid index.\n");

    arr.add(1, "second");

    EXPECT_EQ(arr.get(0), "first");
    EXPECT_EQ(arr.get(1), "second");
    EXPECT_EQ(arr.get(2), "");
    EXPECT_EQ(arr.get(-1), "");

    arr.add(0, "third");

    EXPECT_EQ(arr.get(0), "third");
    EXPECT_EQ(arr.get(1), "first");
    EXPECT_EQ(arr.get(2), "second");
    EXPECT_EQ(arr.get(-1), "");
    EXPECT_EQ(arr.get(3), "");

    arr.add(2, "fourth");

    EXPECT_EQ(arr.get(0), "third");
    EXPECT_EQ(arr.get(1), "first");
    EXPECT_EQ(arr.get(2), "fourth");
    EXPECT_EQ(arr.get(3), "second");
    EXPECT_EQ(arr.get(-1), "");
    EXPECT_EQ(arr.get(4), "");

    arr.remove(0);

    EXPECT_EQ(arr.get(0), "first");
    EXPECT_EQ(arr.get(1), "fourth");
    EXPECT_EQ(arr.get(2), "second");
    EXPECT_EQ(arr.get(-1), "");
    EXPECT_EQ(arr.get(3), "");

    stringstream buffer4;
    streambuf* old4 = cout.rdbuf(buffer4.rdbuf());

    arr.add(4, "first");

    string output4 = buffer4.str();
    cout.rdbuf(old4);

    EXPECT_EQ(output4, "Invalid index.\n");

    arr.remove(0);

    EXPECT_EQ(arr.get(0), "fourth");
    EXPECT_EQ(arr.get(1), "second");
    EXPECT_EQ(arr.get(-1), "");
    EXPECT_EQ(arr.get(2), "");

    stringstream buffer5;
    streambuf* old5 = cout.rdbuf(buffer5.rdbuf());

    arr.add(3, "first");

    string output5 = buffer5.str();
    cout.rdbuf(old5);

    EXPECT_EQ(output5, "Invalid index.\n");

    arr.add(2, "third");

    EXPECT_EQ(arr.get(0), "fourth");
    EXPECT_EQ(arr.get(1), "second");
    EXPECT_EQ(arr.get(2), "third");
    EXPECT_EQ(arr.get(-1), "");
    EXPECT_EQ(arr.get(3), "");
}

TEST(ArrayTest, Remove) {
    Array arr;

    stringstream buffer1;
    streambuf* old1 = cout.rdbuf(buffer1.rdbuf());

    arr.remove(-1);

    string output1 = buffer1.str();
    cout.rdbuf(old1);

    EXPECT_EQ(output1, "Invalid index.\n");

    stringstream buffer2;
    streambuf* old2 = cout.rdbuf(buffer2.rdbuf());

    arr.remove(1);

    string output2 = buffer2.str();
    cout.rdbuf(old2);

    EXPECT_EQ(output2, "Invalid index.\n");

    stringstream buffer3;
    streambuf* old3 = cout.rdbuf(buffer3.rdbuf());

    arr.remove(0);

    string output3 = buffer3.str();
    cout.rdbuf(old3);

    EXPECT_EQ(output3, "Invalid index.\n");

    arr.addToEnd("first");
    arr.addToEnd("second");
    arr.addToEnd("third");

    arr.remove(1);

    EXPECT_EQ(arr.get(0), "first");
    EXPECT_EQ(arr.get(1), "third");
    EXPECT_EQ(arr.get(2), "");

    arr.remove(1);

    EXPECT_EQ(arr.get(0), "first");
    EXPECT_EQ(arr.get(1), "");
    EXPECT_EQ(arr.get(2), "");

    arr.remove(0);

    EXPECT_EQ(arr.get(0), "");
    EXPECT_EQ(arr.get(1), "");
    EXPECT_EQ(arr.get(2), "");

    stringstream buffer4;
    streambuf* old4 = cout.rdbuf(buffer4.rdbuf());

    arr.remove(0);

    string output4 = buffer4.str();
    cout.rdbuf(old4);

    EXPECT_EQ(output4, "Invalid index.\n");
}

TEST(ArrayTest, Set) {
    Array arr;

    stringstream buffer1;
    streambuf* old1 = cout.rdbuf(buffer1.rdbuf());

    arr.set(-1, "value1");

    string output1 = buffer1.str();
    cout.rdbuf(old1);

    EXPECT_EQ(output1, "Invalid index!\n");

    stringstream buffer2;
    streambuf* old2 = cout.rdbuf(buffer2.rdbuf());

    arr.set(1, "value1");

    string output2 = buffer2.str();
    cout.rdbuf(old2);

    EXPECT_EQ(output2, "Invalid index!\n");

    stringstream buffer3;
    streambuf* old3 = cout.rdbuf(buffer3.rdbuf());

    arr.set(0, "value1");

    string output3 = buffer3.str();
    cout.rdbuf(old3);

    EXPECT_EQ(output3, "Invalid index!\n");

    arr.addToEnd("first");
    arr.addToEnd("second");
    arr.addToEnd("third");

    arr.set(1, "new_second");

    EXPECT_EQ(arr.get(0), "first");
    EXPECT_EQ(arr.get(1), "new_second");
    EXPECT_EQ(arr.get(2), "third");

    arr.set(2, "new_third");

    EXPECT_EQ(arr.get(0), "first");
    EXPECT_EQ(arr.get(1), "new_second");
    EXPECT_EQ(arr.get(2), "new_third");

    arr.set(0, "new_first");

    EXPECT_EQ(arr.get(0), "new_first");
    EXPECT_EQ(arr.get(1), "new_second");
    EXPECT_EQ(arr.get(2), "new_third");

    arr.set(1, "new_new_second");

    EXPECT_EQ(arr.get(0), "new_first");
    EXPECT_EQ(arr.get(1), "new_new_second");
    EXPECT_EQ(arr.get(2), "new_third");

    arr.remove(2);

    stringstream buffer4;
    streambuf* old4 = cout.rdbuf(buffer4.rdbuf());

    arr.set(2, "value1");

    string output4 = buffer4.str();
    cout.rdbuf(old4);

    EXPECT_EQ(output4, "Invalid index!\n");

    EXPECT_EQ(arr.get(0), "new_first");
    EXPECT_EQ(arr.get(1), "new_new_second");
    EXPECT_EQ(arr.get(2), "");
}

TEST(ArrayTest, Length) {
    Array arr;
    EXPECT_EQ(arr.length(), 0);
    arr.addToEnd("first");
    EXPECT_EQ(arr.length(), 1);
    arr.addToEnd("second");
    EXPECT_EQ(arr.length(), 2);
    arr.remove(0);
    EXPECT_EQ(arr.length(), 1);
}

TEST(ArrayTest, SaveAndLoad) {
    Array arr1;
    arr1.addToEnd("first");
    arr1.addToEnd("second");
    arr1.saveToFile("file3.data/my_array");

    Array arr2;
    arr2.loadFromFile("file3.data/my_array");
    EXPECT_EQ(arr2.get(0), "first");
    EXPECT_EQ(arr2.get(1), "second");
}

TEST(ArrayTest, Print) {
    Array arr;
    arr.addToEnd("first");
    arr.addToEnd("second");

    stringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());

    arr.print("file3.data/my_array");

    string output = buffer.str();
    cout.rdbuf(old);

    EXPECT_EQ(output, "my_array: first second \n");
}

TEST(ArrayTest, Overflow) {
    Array arr(2);
    arr.addToEnd("first");
    arr.addToEnd("second");
    arr.addToEnd("third");

    EXPECT_EQ(arr.get(0), "first");
    EXPECT_EQ(arr.get(1), "second");
    EXPECT_EQ(arr.get(2), "third");
}

TEST(ArrayTest, SaveAndLoadBinary) {
    Array arr1;
    arr1.addToEnd("first");
    arr1.addToEnd("second");
    arr1.addToEnd("third");
    EXPECT_EQ(arr1.length(), 3);
    arr1.saveToBinaryFile("file4.data/array_binary.data");

    Array arr2;
    arr2.loadFromBinaryFile("file4.data/array_binary.data");

    EXPECT_EQ(arr2.get(0), "first");
    EXPECT_EQ(arr2.get(1), "second");
    EXPECT_EQ(arr2.get(2), "third");
    EXPECT_EQ(arr2.length(), 3);
}
