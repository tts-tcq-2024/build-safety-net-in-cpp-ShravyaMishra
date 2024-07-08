#include "Soundex.h"
#include <gtest/gtest.h>

using namespace std;

// Test fixture for Soundex functions
class SoundexTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Tests for getSoundexCode function
TEST_F(SoundexTest, GetSoundexCode) {
    EXPECT_EQ(getSoundexCode('b'), '1');
    EXPECT_EQ(getSoundexCode('F'), '1');
    EXPECT_EQ(getSoundexCode('P'), '1');
    EXPECT_EQ(getSoundexCode('V'), '1');
    EXPECT_EQ(getSoundexCode('g'), '2');
    EXPECT_EQ(getSoundexCode('L'), '4');
    EXPECT_EQ(getSoundexCode('m'), '5');
    EXPECT_EQ(getSoundexCode('R'), '6');
    EXPECT_EQ(getSoundexCode('z'), '2');
    EXPECT_EQ(getSoundexCode('y'), '0'); // Should return '0' for unknown characters
	EXPECT_EQ(getSoundexCode('1'), '0'); // Numeric character should map to '0'
    EXPECT_EQ(getSoundexCode('@'), '0'); // Special character should map to '0'
}

// Tests for IsHW function
TEST_F(SoundexTest, IsHW) {
    EXPECT_TRUE(isHW('h'));
    EXPECT_FALSE(isHW('H'));
    EXPECT_TRUE(isHW('w'));
    EXPECT_FALSE(isHW('a'));
    EXPECT_FALSE(isHW(' '));
    EXPECT_FALSE(isHW('z'));
}

// Tests for ShouldAppend function
TEST_F(SoundexTest, ShouldAppend) {
    EXPECT_TRUE(shouldAppend('1', '0', 'B')); // First occurrence of 'B'
    EXPECT_FALSE(shouldAppend('1', '1', 'B')); // Already appended '1'
    EXPECT_TRUE(shouldAppend('2', '1', 'C')); // Different code '2' after 'B'
    EXPECT_TRUE(shouldAppend('3', '2', 'D')); // Different code '3' after 'C'
    EXPECT_FALSE(shouldAppend('3', '3', 'T')); // Already appended '3'
    EXPECT_TRUE(shouldAppend('5', '3', 'M')); // Different code '5' after 'T'
    EXPECT_FALSE(shouldAppend('5', '5', 'N')); // Already appended '5'
    EXPECT_TRUE(shouldAppend('4', '5', 'L')); // Different code '4' after 'N'
    EXPECT_FALSE(shouldAppend('4', '4', 'L')); // Already appended '4'
}

// Tests for accumulateSoundexCodes function
TEST(AccumulateSoundexCodesTest, BasicName) {
    EXPECT_EQ(accumulateSoundexCodes("Rubin"), "R15");
}

TEST(AccumulateSoundexCodesTest, NameWithHAndW) {
    EXPECT_EQ(accumulateSoundexCodes("Tymczak"), "T52");
}

TEST(AccumulateSoundexCodesTest, NameWithAdjacentSameCodes) {
    EXPECT_EQ(accumulateSoundexCodes("Pfister"), "P236");
}

TEST(AccumulateSoundexCodesTest, NameWithExcludedCharacters) {
    EXPECT_EQ(accumulateSoundexCodes("Honeyman"), "H5");
}

TEST(AccumulateSoundexCodesTest, EmptyName) {
    EXPECT_EQ(accumulateSoundexCodes(""), "0000");
}

// Tests for padSoundex function
TEST(PadSoundexTest, NormalSoundex) {
    EXPECT_EQ(padSoundex("R163"), "R163");
}

TEST(PadSoundexTest, ShortSoundex) {
    EXPECT_EQ(padSoundex("T52"), "T520");
}

TEST(PadSoundexTest, FullSoundex) {
    EXPECT_EQ(padSoundex("P236"), "P236");
}

TEST(PadSoundexTest, EmptySoundex) {
    EXPECT_EQ(padSoundex(""), "0000");
}

// Tests for generateSoundex function
TEST_F(SoundexTest, GenerateSoundex) {
    EXPECT_EQ(generateSoundex("Robert"), "R163");
    EXPECT_EQ(generateSoundex("Rupert"), "R163");
    EXPECT_EQ(generateSoundex("Rubin"), "R150");
    EXPECT_EQ(generateSoundex("Ashcraft"), "A202");
    EXPECT_EQ(generateSoundex("Tymczak"), "T520");
    EXPECT_EQ(generateSoundex("Pfister"), "P236");
    EXPECT_EQ(generateSoundex(""), ""); // Empty string case
}
// Run the tests
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
