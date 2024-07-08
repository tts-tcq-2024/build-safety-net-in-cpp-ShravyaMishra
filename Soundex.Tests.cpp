#include "Soundex.h"
#include <gtest/gtest.h>

// Test fixture for Soundex functions
class SoundexTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Tests for getSoundexCode function
TEST_F(SoundexTest, GetSoundexCode) {
    EXPECT_EQ(Soundex::getSoundexCode('b'), '1');
    EXPECT_EQ(Soundex::getSoundexCode('F'), '1');
    EXPECT_EQ(Soundex::getSoundexCode('P'), '1');
    EXPECT_EQ(Soundex::getSoundexCode('V'), '1');
    EXPECT_EQ(Soundex::getSoundexCode('g'), '2');
    EXPECT_EQ(Soundex::getSoundexCode('L'), '4');
    EXPECT_EQ(Soundex::getSoundexCode('m'), '5');
    EXPECT_EQ(Soundex::getSoundexCode('R'), '6');
    EXPECT_EQ(Soundex::getSoundexCode('z'), '2');
    EXPECT_EQ(Soundex::getSoundexCode('y'), '0'); // Should return '0' for unknown characters
    EXPECT_EQ(Soundex::getSoundexCode('1'), '0'); // Numeric character should map to '0'
    EXPECT_EQ(Soundex::getSoundexCode('@'), '0'); // Special character should map to '0'
}

// Tests for IsHW function
TEST_F(SoundexTest, IsHW) {
    EXPECT_TRUE(Soundex::isHW('h'));
    EXPECT_FALSE(Soundex::isHW('H'));
    EXPECT_TRUE(Soundex::isHW('w'));
    EXPECT_FALSE(Soundex::isHW('a'));
    EXPECT_FALSE(Soundex::isHW(' '));
    EXPECT_FALSE(Soundex::isHW('z'));
}

// Tests for ShouldAppend function
TEST_F(SoundexTest, ShouldAppend) {
    EXPECT_TRUE(Soundex::shouldAppend('1', '0', 'B')); // First occurrence of 'B'
    EXPECT_FALSE(Soundex::shouldAppend('1', '1', 'B')); // Already appended '1'
    EXPECT_TRUE(Soundex::shouldAppend('2', '1', 'C')); // Different code '2' after 'B'
    EXPECT_TRUE(Soundex::shouldAppend('3', '2', 'D')); // Different code '3' after 'C'
    EXPECT_FALSE(Soundex::shouldAppend('3', '3', 'T')); // Already appended '3'
    EXPECT_TRUE(Soundex::shouldAppend('5', '3', 'M')); // Different code '5' after 'T'
    EXPECT_FALSE(Soundex::shouldAppend('5', '5', 'N')); // Already appended '5'
    EXPECT_TRUE(Soundex::shouldAppend('4', '5', 'L')); // Different code '4' after 'N'
    EXPECT_FALSE(Soundex::shouldAppend('4', '4', 'L')); // Already appended '4'
}

// Tests for accumulateSoundexCodes function
TEST(SoundexFunctionsTest, AccumulateSoundexCodes) {
    EXPECT_EQ(Soundex::accumulateSoundexCodes("Rubin"), "R150");
    EXPECT_EQ(Soundex::accumulateSoundexCodes("Tymczak"), "T520");
    EXPECT_EQ(Soundex::accumulateSoundexCodes("Pfister"), "P236");
    EXPECT_EQ(Soundex::accumulateSoundexCodes("Honeyman"), "H500");
    EXPECT_EQ(Soundex::accumulateSoundexCodes(""), "0000");
}

// Tests for padSoundex function
TEST(SoundexFunctionsTest, PadSoundex) {
    EXPECT_EQ(Soundex::padSoundex("R163"), "R163");
    EXPECT_EQ(Soundex::padSoundex("T52"), "T520");
    EXPECT_EQ(Soundex::padSoundex("P236"), "P236");
    EXPECT_EQ(Soundex::padSoundex(""), "0000");
}

// Tests for generateSoundex function
TEST_F(SoundexTest, GenerateSoundex) {
    EXPECT_EQ(Soundex::generateSoundex("Robert"), "R163");
    EXPECT_EQ(Soundex::generateSoundex("Rupert"), "R163");
    EXPECT_EQ(Soundex::generateSoundex("Rubin"), "R150");
    EXPECT_EQ(Soundex::generateSoundex("Ashcraft"), "A226");
    EXPECT_EQ(Soundex::generateSoundex("Tymczak"), "T520");
    EXPECT_EQ(Soundex::generateSoundex("Pfister"), "P236");
    EXPECT_EQ(Soundex::generateSoundex(""), "0000"); // Empty string case
}

// Run the tests
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
