#include<sodium.h>
#include<spdlog/spdlog.h>

int main(int argc, char ** argv )
{
    std::string plain_text = "Hello Bob!";

    #define CIPHERTEXT_LEN (crypto_box_MACBYTES + MESSAGE_LEN)

    unsigned char alice_publickey[crypto_box_PUBLICKEYBYTES];
    unsigned char alice_secretkey[crypto_box_SECRETKEYBYTES];
    crypto_box_keypair(alice_publickey, alice_secretkey);
    spdlog::info("Alice Private key: {:x}", fmt::join(std::begin(alice_secretkey),std::end(alice_secretkey), ","));
    spdlog::info("Alice Public  key: {:x}", fmt::join(std::begin(alice_publickey),std::end(alice_publickey), ","));

    unsigned char bob_publickey[crypto_box_PUBLICKEYBYTES];
    unsigned char bob_secretkey[crypto_box_SECRETKEYBYTES];
    crypto_box_keypair(bob_publickey, bob_secretkey);

    spdlog::info("Bob Private key: {:x}", fmt::join(std::begin(bob_secretkey),std::end(bob_secretkey), ","));
    spdlog::info("Bob Public  key: {:x}", fmt::join(std::begin(bob_publickey),std::end(bob_publickey), ","));

    unsigned char nonce[crypto_box_NONCEBYTES];
    std::vector<uint8_t> ciphertext(crypto_box_MACBYTES + plain_text.size());
    //unsigned char ciphertext[CIPHERTEXT_LEN];
    randombytes_buf(nonce, sizeof nonce);
    spdlog::info("Plain  Text: {}", plain_text);
    spdlog::info("Encrypting Plain Text using Alice private key and Bob public key");
    if (crypto_box_easy(reinterpret_cast<unsigned char*>(&ciphertext[0]),
                        reinterpret_cast<unsigned char*>(plain_text.data()), plain_text.size(),
                        nonce,
                        bob_publickey, alice_secretkey) != 0) {
        /* error */
    }
    spdlog::info("Cypher Text: {:x}", fmt::join(std::begin(ciphertext),std::end(ciphertext), ","));

    spdlog::info("Decrypting cypher Text using Alice public key and Bob private key");
    std::string decrypted(100, ' ');
    if (crypto_box_open_easy(reinterpret_cast<unsigned char*>(decrypted.data()),
                             reinterpret_cast<unsigned char*>(ciphertext.data()),  ciphertext.size(),
                             nonce,
                             alice_publickey, bob_secretkey) != 0) {
        /* message for Bob pretending to be from Alice has been forged! */
    }
    else
    {
        spdlog::info("Decrypted text: {}", decrypted);
    }
    return 0;
}
