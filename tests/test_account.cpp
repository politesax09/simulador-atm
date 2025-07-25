#include <gtest/gtest.h>
#include "Account.hpp"

TEST(AccountTest, DepositoPositivo) {
    Account cuenta("123", 100.0);
    cuenta.deposit(50.0);
    EXPECT_EQ(cuenta.getBalance(), 150.0);
}

TEST(AccountTest, RetiroValido) {
    Account cuenta("123", 100.0);
    bool ok = cuenta.withdraw(40.0);
    EXPECT_TRUE(ok);
    EXPECT_EQ(cuenta.getBalance(), 60.0);
}

TEST(AccountTest, RetiroInvalido) {
    Account cuenta("123", 50.0);
    bool ok = cuenta.withdraw(100.0);
    EXPECT_FALSE(ok);
    EXPECT_EQ(cuenta.getBalance(), 50.0);
}