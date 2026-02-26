#include <gtest/gtest.h>
#include "set1/set1.h"

// Challenge 4: Detect single-character XOR
// One of the 60-character strings in this file has been encrypted by single-character XOR.
// Find it.

TEST(Set1Challenge4, DetectSingleCharXOR) {
    std::string filename = "../src/set1/utils/ch4.txt";
    std::string plaintext = detect_single_char_xor(filename);

    // The expected plaintext is "Now that the party is jumping\n"
    std::string expected_text = "Now that the party is jumping\n";
    EXPECT_EQ(plaintext, expected_text);
}