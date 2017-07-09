/* 
 * File:   main.cpp
 * Author: tanya
 *
 * Created on 19 Февраль 2015 г., 14:40
 */

#include <cstdlib>

using namespace std;

/*
 * 
 */
#include <pcap.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <errno.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <netinet/if_ether.h>
#include "packet.h"
#include "LRUcash.h"
#include <iostream>
#include <time.h>
#include "PacketDB.h"

void my_callback(u_char *args, const struct pcap_pkthdr* pkthdr, const u_char *pack) 
{ 
    //static int pa = 1;
    //cout << pa << " ";
    LRUcash *cash = (LRUcash *)args;
    static int count = 1;
    if (count == 159)
        int fg=3456;
    
    packet *p_p = new packet(pack, pkthdr);
    p_p -> parse();

    if (p_p->calculate_hash == true){
        cash -> Add(p_p, 10000);
        count++;
    }
    //delete p_p;
    //pa++;
}
int compare (char *mode){
	if (mode[0] == 'o' && mode[1] == 'n' && mode[2] == 'l' && mode[3] == 'i' && mode[4] == 'n' && mode[5] == 'e')
		return 1;
	else if (mode[0] == 'o' && mode[1] == 'f' && mode[2] == 'f' && mode[3] == 'l' && mode[4] == 'i' && mode[5] == 'n' && mode[6] == 'e')
		return 2;
	else return 3;
}

void connection_lpcap(char *mode, char *file, u_char *ucash, char *protocol){
    int i;
    char *dev; 
    char errbuf[PCAP_ERRBUF_SIZE]; 
    pcap_t* descr; 
    const u_char *packet; 
    struct pcap_pkthdr hdr;
    struct ether_header *eptr; /* net/ethernet.h */ 
    struct bpf_program fp;     /*выражение фильтрации в составленном виде */ 
    bpf_u_int32 maskp;         /*маска подсети */ 
    bpf_u_int32 netp;          /* ip */
        
    dev = pcap_lookupdev(errbuf); 

    if(dev == NULL) {
            fprintf(stderr, "%s\n", errbuf);
            exit(1);
    } 
    /* Получение сетевого адреса и маски сети для устройства */ 
    pcap_lookupnet(dev, &netp, &maskp, errbuf); 

    int modeInt = compare(mode);

    if (modeInt == 1){
            descr = pcap_open_live(dev, BUFSIZ, 1,-1, errbuf);
            if(descr == NULL) {
                    printf("pcap_open_live(): %s\n", errbuf);
                    exit(1);
            }
    }
    if (modeInt == 2){
            descr = pcap_open_offline(file,errbuf);
            if(descr == NULL) {
                    printf("pcap_open_offline(): %s\n", errbuf);
                    exit(1);
            }
    }

    /* теперь составляется выражение фильтрации*/ 
    if(pcap_compile(descr, &fp, protocol, 0, netp) == -1) {
            fprintf(stderr, "Error calling pcap_compile\n");
            exit(1);
    } 
    /* применение фильтра*/ 
    if(pcap_setfilter(descr, &fp) == -1) {
            fprintf(stderr, "Error setting filter\n");
            exit(1);
    } 
    /* функция обратного вызова используется в цикле */ 
    pcap_loop(descr, -1, my_callback, ucash);
}

int main(int argc,char **argv){

    char *mode = argv[1];
    char *mode2 = argv[0];
    char *mode3 = argv[2];

    LRUcash *cash = new LRUcash();
    u_char *ucash = (u_char *) cash;
    
    PacketDB *pdb = new PacketDB();
    pdb->Create();
    double hhh=0;
    int modeInt = compare(argv[1]);
    if (modeInt == 2){
        if (argc > 2){
            int k = 3;
            for (int i = k ; i < argc ; i++){
                srand(time(0));
                int start_time = clock();
                cout << argv[i] << '\n';
                connection_lpcap(argv[1], argv[i], ucash, argv[2]);
                int hit = cash -> getHit();
                int miss = cash -> getMiss();
                double hitPoite = cash -> GetHitPoite();
		hhh += hitPoite;
                cout << "hit = " << hit << " miss = " << miss << " hitPoite = " << hitPoite << '\n';
                int end_time = clock();
                double time = (double)(end_time - start_time)/CLOCKS_PER_SEC;
                cout << "time = " << time << '\n';
            }
		double ttt = hhh/(double)(argc-k);
	cout<< ttt << '\n';
        }
    }
    //pdb->CloseDB();
    
    if (modeInt == 1){
        connection_lpcap(argv[1], NULL, ucash, argv[2]);
        int hit = cash -> getHit();
        int miss = cash -> getMiss();
        double hitPoite = cash -> GetHitPoite();
        cout << "hit = " << hit << " miss = " << miss << " hitPoite = " << hitPoite << '\n';
            
    }
    return 0;
}


