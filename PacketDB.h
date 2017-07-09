/* 
 * File:   PacketDB.h
 * Author: tanya
 *
 * Created on 24 Май 2015 г., 15:15
 */

#ifndef PACKETDB_H
#define	PACKETDB_H

#include <cstdlib>
#include <stdlib.h>
#include <string.h>
 
#include <iostream>
#include <iomanip>
#include <string>
 
#include <db_cxx.h>

using namespace std;

class PacketDB{
    private :
        Db* pdb;
    public :
        PacketDB();
        ~PacketDB();
        
    public :
        void Create();
        void Open();
        void Add(string hash, string data);
        string Get(string hash);
        void Delete(string hash);
        void CloseDB();
        bool Compare(string str1, string str2);
};

#endif	/* PACKETDB_H */

