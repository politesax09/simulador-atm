#include <gtest/gtest.h>
#include "User.hpp"
#include "Hashing.hpp"  // Simulado si fuera necesario

TEST(UserTest, AutenticacionCorrecta) {
    std::string pin = "1234";
    User u("juan", Hashing::hashPin(pin), Account("001", 100.0));
    EXPECT_TRUE(u.authenticate("1234"));
}

TEST(UserTest, CambioDePin) {
    User u("ana", Hashing::hashPin("1111"), Account("002", 80.0));
    u.changePin("2222");
    EXPECT_TRUE(u.authenticate("2222"));
    EXPECT_FALSE(u.authenticate("1111"));
}