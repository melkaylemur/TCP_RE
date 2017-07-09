/* 
 * File:   LRUcash.h
 * Author: tanya
 *
 * Created on 20 Апрель 2015 г., 17:51
 */

#ifndef LRUCASH_H
#define	LRUCASH_H

#include "packet.h"
#include <iostream>
#include <list>
#include <string>

using namespace std;

//static int hit = 0;
//static int miss = 0;

class LRUcash{
    private :
        std :: list <packet *> list_packet;
        int hit = 0;
        int miss = 0;
        std :: list <string> list_hash;
 
    public : 
	LRUcash();
	~LRUcash();
    
    public :
        //EL: имена классов должны называться с большой буквы
        void Add(packet *pack, int size);
        int getHit();
        int getMiss();
        double GetHitPoite();
        void AddDB(packet *pack, int size, int k);
};


#endif	/* LRUCASH_H */

