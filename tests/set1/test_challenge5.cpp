#include <gtest/gtest.h>
#include "set1/set1.h"

// Challenge 5: Repeating-key XOR
// Implement repeating-key XOR encryption

TEST(Set1Challenge5, RepeatingKeyXOR) {
    std::string plaintext = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
    std::string key = "ICE";
    
    std::string result = repeating_key_xor(plaintext, key);
    
    // La salida esperada
    std::string expected = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";
    
    EXPECT_EQ(result, expected);
}
