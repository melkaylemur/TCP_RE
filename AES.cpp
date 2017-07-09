#include "AES.h"

AES :: AES (){}

AES :: ~AES (){}

void AES :: KeyIv (){
    memset( key, 0x00, CryptoPP::AES::DEFAULT_KEYLENGTH );
    memset( iv, 0x00, CryptoPP::AES::BLOCKSIZE );
}

string AES :: Encrypt (string data){
    string data_encrypt;
    
    CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption( aesEncryption, iv );

    CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink( data_encrypt ) );
    stfEncryptor.Put( reinterpret_cast<const unsigned char*>( data.c_str() ), data.length() + 1 );
    stfEncryptor.MessageEnd();
    
    return data_encrypt;
}

//string AES :: Decrypt (string data_encrypt){
//    int fg=56;
//    string data_decrypt;
//    
//    CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
//    CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption( aesDecryption, iv );
//
//    CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink( data_decrypt ) );
//    stfDecryptor.Put( reinterpret_cast<const unsigned char*>( data_encrypt.c_str() ), data_encrypt.size() );
//    stfDecryptor.MessageEnd();
//    
//    return data_decrypt;
//}