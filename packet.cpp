#include "packet.h"
#include "md5.h"
#include <cstdio>
#include <iostream>
#include <cstring>

using std::cout; using std::endl;
//EL: убрать глобальные переменные
std :: vector<u_char>data;

packet :: packet (const u_char *pack , const struct pcap_pkthdr* pkthdr){
	for(int i=0; i < pkthdr->len; i++)
	{
		data.push_back(pack[i]);
               // data[i] = packet[i];
	}
}

packet ::~packet(){
    data.clear();
}

void packet :: parse(){
	int dataPointer = IP_source;
	for (int i = 0 ; i < 4 ; i++){
		iph.ipSource[i] = data[dataPointer+i];
	}

	dataPointer += 4;
	for (int i = 0 ; i < 4 ; i++){
		iph.ipDest[i] = data[dataPointer+i];
	}
        
        dataPointer = TCP_start;
	for (int i = 0 ; i < 2 ; i++)
		tcph.portSource += data[dataPointer+i];

	dataPointer += 2;
	for (int i = 0 ; i < 2 ; i++)
		tcph.portDest += data[dataPointer+i];
        
        dataPointer = TCP_flags;
        if (data[dataPointer] == 24 && data.size() > 68){
            calculate_hash = true;
        }
//        else if (data[dataPointer] == 16 && data.size() > 68){
//            calculate_hash = true;
//        }
        
        if (calculate_hash == true){
            dataPointer = data_start;
            for(int z = dataPointer ; z < data.size() ; z++) { 
                data_c += data[z];
            }
            MD5 md5 = MD5(data_c);
            hash_data = md5.hexdigest(); 
        }
}
