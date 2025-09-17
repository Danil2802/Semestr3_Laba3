#include "Queue.h"
#include <gtest/gtest.h>
#include <sstream>

using namespace std;

TEST(QueueTest, Push_Peek) {
    Queue queue;

    queue.push("first");
    EXPECT_EQ(queue.peek(), "first");

    queue.push("second");
    EXPECT_EQ(queue.peek(), "first");

    queue.pop();

    EXPECT_EQ(queue.peek(), "second");

    queue.pop();

    EXPECT_EQ(queue.peek(), "");
}

TEST(QueueTest, Pop) {
    Queue queue;

    stringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());

    queue.pop();

    string output = buffer.str();
    cout.rdbuf(old);

    EXPECT_EQ(output, "Queue is empty!\n");

    queue.push("first");
    queue.push("second");
    queue.pop();

    EXPECT_EQ(queue.peek(), "second");

    queue.pop();

    EXPECT_EQ(queue.peek(), "");
}

TEST(QueueTest, SaveAndLoad) {
    Queue queue1;
    queue1.push("first");
    queue1.push("second");
    queue1.saveToFile("file3.data/my_queue");

    Queue queue2;
    queue2.loadFromFile("file3.data/my_queue");
    EXPECT_EQ(queue2.peek(), "first");
    queue2.pop();
    EXPECT_EQ(queue2.peek(), "second");
    queue2.pop();
    EXPECT_EQ(queue2.peek(), "");
}

TEST(QueueTest, Print) {
    Queue queue;
    queue.push("first");
    queue.push("second");

    stringstream buffer;
    streambuf* old = cout.rdbuf(buffer.rdbuf());

    queue.print("file3.data/my_queue");

    string output = buffer.str();
    cout.rdbuf(old);

    EXPECT_EQ(output, "my_queue: first second \n");
}

TEST(QueueTest, Overflow) {
    Queue queue(2);
    queue.push("first");
    queue.push("second");
    queue.push("third");

    EXPECT_EQ(queue.peek(), "first");
    queue.pop();
    EXPECT_EQ(queue.peek(), "second");
    queue.pop();
    EXPECT_EQ(queue.peek(), "third");
    queue.pop();
    EXPECT_EQ(queue.peek(), "");
}

TEST(QueueTest, SaveAndLoadBinary) {
    Queue queue1;
    queue1.push("first");
    queue1.push("second");
    queue1.push("third");
    queue1.saveToBinaryFile("file4.data/queue_binary.data");

    Queue queue2;
    queue2.loadFromBinaryFile("file4.data/queue_binary.data");

    EXPECT_EQ(queue2.peek(), "first");
    queue2.pop();
    EXPECT_EQ(queue2.peek(), "second");
    queue2.pop();
    EXPECT_EQ(queue2.peek(), "third");
    queue2.pop();
    EXPECT_EQ(queue2.peek(), "");
}
