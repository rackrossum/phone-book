#include "test_runner.h"
#include "phone_book.h"

void TestLookup()
{
    Contact c1, c2, c3, c4, c5;
    c1.name = "aaa";
    c2.name = "aaaa";
    c3.name = "aaa";
    c4.name = "bbb";
    c5.name = "aab";

    PhoneBook pb({c1, c2, c3, c4, c5});

    ASSERT_EQUAL(pb.FindByNamePrefix("").size(), 5);
    ASSERT_EQUAL(pb.FindByNamePrefix("aaa").size(), 3);
    ASSERT_EQUAL(pb.FindByNamePrefix("aaaa").size(), 1);
    ASSERT_EQUAL(pb.FindByNamePrefix("aa").size(), 4);
    ASSERT_EQUAL(pb.FindByNamePrefix("aab").size(), 1);
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestLookup);

    return 0;
}
