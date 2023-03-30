#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
#include <string>


// Funzione per la crittografia dei dati
std::string createToken(const std::string& data, const std::string& secretKey) {
    EVP_MD_CTX* mdctx;
    const EVP_MD* md;
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len;

    // Imposto l'algoritmo di crittografia
    md = EVP_sha256();

    // Creo un contesto di crittografia
    mdctx = EVP_MD_CTX_create(); 
    EVP_DigestInit_ex(mdctx, md, NULL);

    // Aggiungo i dati da crittografare 
    EVP_DigestUpdate(mdctx, data.c_str(), data.length());

    // Aggiungo la chiave segreta per la crittografia
    EVP_DigestUpdate(mdctx, secretKey.c_str(), secretKey.length());

    // Creo il token crittografando i dati con la chiave segreta
    EVP_DigestFinal_ex(mdctx, md_value, &md_len);
    EVP_MD_CTX_destroy(mdctx);
    std::string token = std::string(reinterpret_cast<char*>(md_value), md_len);

    // Codifico il token in Base64 per renderlo leggibile
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    bio = BIO_new(BIO_s_mem());
    b64 = BIO_new(BIO_f_base64());
    bio = BIO_push(b64, bio);

    BIO_write(bio, token.c_str(), token.length());
    BIO_flush(bio);
    BIO_get_mem_ptr(bio, &bufferPtr);
    BIO_set_close(bio, BIO_NOCLOSE);

    std::string encodedToken(bufferPtr->data, bufferPtr->length - 1);
    BIO_free_all(bio);

    return encodedToken;
}

int main() {
    std::string data = "user123"; // Dati da crittografare
    std::string secretKey = "mySecretKey"; // Chiave segreta per la crittografia

    std::string token = createToken(data, secretKey);
    std::cout << token << std::endl;

    return 0;
}
