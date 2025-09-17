#include "Stack.h"
#include <gtest/gtest.h>
#include <sstream>

using namespace std;

TEST(StackTest, Push_Peek) {
    Stack stack;

    stack.push("first");
    EXPECT_EQ(stack.peek(), "first");

    stack.push("second");
    EXPECT_EQ(stack.peek(), "second");

    stack.pop();
    EXPECT_EQ(stack.peek(), "first");

    stack.pop();
    EXPECT_EQ(stack.peek(), "");
}

TEST(StackTest, Pop) {
    Stack stack;

    stringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());

    stack.pop();

    string output = buffer.str();
    cout.rdbuf(old);

    EXPECT_EQ(output, "Stack is empty!\n");

    stack.push("first");
    stack.push("second");
    stack.pop();

    EXPECT_EQ(stack.peek(), "first");

    stack.pop();

    EXPECT_EQ(stack.peek(), "");
}

TEST(StackTest, SaveAndLoad) {
    Stack stack1;
    stack1.push("first");
    stack1.push("second");
    stack1.saveToFile("file3.data/my_stack");

    Stack stack2;
    stack2.loadFromFile("file3.data/my_stack");
    EXPECT_EQ(stack2.peek(), "second");
    stack2.pop();
    EXPECT_EQ(stack2.peek(), "first");
    stack2.pop();
    EXPECT_EQ(stack2.peek(), "");
}

TEST(StackTest, Print) {
    Stack stack;
    stack.push("first");
    stack.push("second");

    stringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());

    stack.print();

    string output = buffer.str();
    cout.rdbuf(old);

    EXPECT_EQ(output, "first second \n");
}

TEST(StackTest, Overflow) {
    Stack stack(2);
    stack.push("first");
    stack.push("second");
    stack.push("third");

    EXPECT_EQ(stack.peek(), "third");
    stack.pop();
    EXPECT_EQ(stack.peek(), "second");
    stack.pop();
    EXPECT_EQ(stack.peek(), "first");
    stack.pop();
    EXPECT_EQ(stack.peek(), "");
}

TEST(StackTest, SaveAndLoadBinary) {
    Stack stack1;
    stack1.push("first");
    stack1.push("second");
    stack1.push("third");
    stack1.saveToBinaryFile("file4.data/stack_binary.data");

    Stack stack2;
    stack2.loadFromBinaryFile("file4.data/stack_binary.data");

    EXPECT_EQ(stack2.peek(), "third");
    stack2.pop();
    EXPECT_EQ(stack2.peek(), "second");
    stack2.pop();
    EXPECT_EQ(stack2.peek(), "first");
    stack2.pop();
    EXPECT_EQ(stack2.peek(), "");
}
