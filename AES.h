/* 
 * File:   AES.h
 * Author: tanya
 *
 * Created on 24 Май 2015 г., 22:51
 */

#ifndef AES_H
#define	AES_H

#include <iostream>
#include <iomanip>

#include "cryptopp/modes.h"
#include "cryptopp/aes.h"
#include "cryptopp/filters.h"
#include <string>

using namespace std;

class AES{
    private :
        byte key[ CryptoPP::AES::DEFAULT_KEYLENGTH ];
        byte iv[ CryptoPP::AES::BLOCKSIZE ];
    
    public :
        AES();
        ~AES();

    public :
        void KeyIv();
        string Encrypt(string data);
        string Decrypt(string data_encrypt);
};

#endif	/* AES_H */

