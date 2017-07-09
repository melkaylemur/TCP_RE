#include "packet.h"
#include <iostream>
#include "LRUcash.h"
#include "PacketDB.h"
#include "AES.h"

//using namepace std;
using std::cout; using std::endl;

LRUcash :: LRUcash (){}

LRUcash :: ~LRUcash (){}



void LRUcash :: Add(packet *pack, int size){
    if (miss == 999)
        int dfg=4567;
    
    std :: list <packet*> :: iterator it_packet;

    for (it_packet = list_packet.begin() ; it_packet != list_packet.end() ; ++it_packet){
        if (pack->hash_data == (*it_packet)->hash_data && pack->data_c == (*it_packet)->data_c){
            it_packet = list_packet.erase(it_packet);
            hit++;
        }
    }
    
    if (list_packet.size() < size)
        list_packet.push_front(pack);
    else {
        list_packet.pop_back();
        list_packet.push_front(pack);
    }
    miss++;
    //cout<< hit << " " << miss << "\n";
}

int LRUcash :: getHit(){
    return hit;
}

int LRUcash :: getMiss(){
    return miss;
}

double LRUcash :: GetHitPoite(){
    double hitPoite = (double)hit / (double)miss;
    return hitPoite;
}

void LRUcash :: AddDB(packet *pack, int size, int k){
    PacketDB *packet_db = new PacketDB();
    AES *aes = new AES();
    aes->KeyIv();
    
    string data = pack->data_c;
    string hash = pack->hash_data;
    string encryptData = aes->Encrypt(data);
    string vr_data;
    string decryptData;
    std :: list <string> :: iterator it_hash;

    for (it_hash = list_hash.begin() ; it_hash != list_hash.end() ; ++it_hash){
        if (hash == (*it_hash)){
            it_hash = list_hash.erase(it_hash);
            vr_data = packet_db->Get(hash);
            //decryptData = aes->Decrypt(vr_data);
            bool flag = packet_db->Compare(encryptData, vr_data);
            if (flag == true)
                hit++;
            //if (vr_data.compare(encryptData))
            //    hit++;
        }
    }
    //str2[i]
    if (list_hash.size() < size){
        list_hash.push_front(hash);
        packet_db->Add(hash, encryptData);
    }
    else {
        list_hash.pop_back();
        packet_db->Delete(hash);
        list_hash.push_front(hash);
        packet_db->Add(hash, encryptData);
    }
    miss++;
}