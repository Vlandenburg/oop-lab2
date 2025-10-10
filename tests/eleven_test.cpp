#include <gtest/gtest.h>
#include "../include/lab2.h"

TEST(ElevenConstructorTests, HandlesAllCases) {
    Eleven zero;
    ASSERT_EQ(zero.toString(), "0");

    Eleven fives(3, 5);
    ASSERT_EQ(fives.toString(), "555");
    
    Eleven all_zeros(5, static_cast<unsigned char>(0));
    ASSERT_EQ(all_zeros.toString(), "0");

    Eleven from_str("A1A");
    ASSERT_EQ(from_str.toString(), "A1A");
    
    Eleven leading_zeros_str("007A");
    ASSERT_EQ(leading_zeros_str.toString(), "7A");

    Eleven from_list{10, 2, 0};
    ASSERT_EQ(from_list.toString(), "A20");
    
    Eleven leading_zeros_list{0, 0, 1, 2, 3};
    ASSERT_EQ(leading_zeros_list.toString(), "123");
}

TEST(ElevenLifecycleTests, CopyAndMove) {
    Eleven original("A23");
    Eleven copy(original);
    ASSERT_EQ(original.toString(), "A23");
    ASSERT_EQ(copy.toString(), "A23");

    Eleven moved_from("456");
    Eleven moved_to(std::move(moved_from));
    ASSERT_EQ(moved_to.toString(), "456");
}

TEST(ElevenArithmeticTests, AdditionAndSubtraction) {
    Eleven a("A9");
    Eleven b("12");

    Eleven sum = a.add(b);
    ASSERT_EQ(sum.toString(), "110"); 

    Eleven big_a("AAAA");
    Eleven big_b("1");
    ASSERT_EQ(big_a.add(big_b).toString(), "10000");

    Eleven diff = a.subtract(b);
    ASSERT_EQ(diff.toString(), "97");
    
    Eleven c("123");
    Eleven d("123");
    ASSERT_EQ(c.subtract(d).toString(), "0");
}

TEST(ElevenComparisonTests, AllRelations) {
    Eleven a("100");
    Eleven b("A5");
    Eleven c("100");

    ASSERT_TRUE(a.equals(c));
    ASSERT_FALSE(a.equals(b));
    ASSERT_TRUE(a.greater(b));
    ASSERT_FALSE(b.greater(a));
    ASSERT_FALSE(a.greater(c));
    ASSERT_TRUE(b.less(a));
    ASSERT_FALSE(a.less(b));
    ASSERT_FALSE(a.less(c));
}

TEST(ElevenErrorHandlingTests, ExceptionsAndEdgeCases) {
    ASSERT_THROW(Eleven(5, 11), std::invalid_argument);
    ASSERT_THROW(Eleven("12G5"), std::invalid_argument);
    ASSERT_THROW(Eleven({1, 12, 3}), std::invalid_argument);

    Eleven smaller("10");
    Eleven larger("20");
    ASSERT_THROW(smaller.subtract(larger), std::logic_error);

    Eleven empty_str("");
    ASSERT_EQ(empty_str.toString(), "0");
    
    Eleven zero_str("0");
    ASSERT_EQ(zero_str.toString(), "0");
}