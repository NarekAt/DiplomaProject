#include <gtest/gtest.h>

int main(int argc, char **argv) {
	// to get rid of the warnings at ASSERT_DEATH().
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
