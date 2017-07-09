#include "PacketDB.h"

PacketDB :: PacketDB (){}

PacketDB :: ~PacketDB (){}

void PacketDB :: Create (){
    DbEnv env(0);
 
    env.set_error_stream(&cerr);
    env.open(".", DB_CREATE | DB_INIT_MPOOL, 0);
    
    pdb = new Db(&env, 0);
    pdb->open(NULL, "access.db", NULL, DB_BTREE, DB_CREATE | DB_TRUNCATE, 0);
}

void PacketDB :: Open (){
    DbEnv env(0);
    
    env.set_error_stream(&cerr);
    env.open(".", 0, 0);
    
    pdb = new Db(&env, 0);
    pdb->open(NULL, "access.db", NULL, DB_BTREE, 0, 0);
}

void PacketDB :: Add (string hash, string data_packet){
    int df=567;
    DbEnv env(0);
    Db* p;
 
    env.set_error_stream(&cerr);
    env.open(".", 0, 0);
    
    pdb = new Db(&env, 0);
    pdb->open(NULL, "access.db", NULL, DB_BTREE, 0, 0);
    
    Dbt key(const_cast<char*>(hash.data()), hash.size());
    Dbt value(const_cast<char*>(data_packet.data()), data_packet.size()+1);
    pdb->put(NULL, &key, &value, 0);
}

string PacketDB :: Get (string hash){
    DbEnv env(0);
    Db* p;
 
    env.set_error_stream(&cerr);
    env.open(".", 0, 0);
    
    pdb = new Db(&env, 0);
    pdb->open(NULL, "access.db", NULL, DB_BTREE, 0, 0);
    
    char buffer[2000];
    Dbt key(const_cast<char*>(hash.data()), hash.size());
    Dbt data;
    data.set_data(buffer);
    data.set_ulen(2000);
    data.set_flags(DB_DBT_USERMEM);
    if (pdb->get(NULL, &key, &data, 0) == DB_NOTFOUND) {
      cerr << "Not found" << endl;
    }
    string buf = buffer;
    return buf;
}

void PacketDB :: Delete (string hash){
    DbEnv env(0);
    Db* p;
 
    env.set_error_stream(&cerr);
    env.open(".", 0, 0);
    
    pdb = new Db(&env, 0);
    pdb->open(NULL, "access.db", NULL, DB_BTREE, 0, 0);
    
    Dbt key(const_cast<char*>(hash.data()), hash.size());
    pdb->del(NULL, &key, 0);
}

void PacketDB :: CloseDB(){
    DbEnv env(0);
    Db* p;
 
    env.set_error_stream(&cerr);
    env.open(".", 0, 0);
    
    pdb = new Db(&env, 0);
    pdb->open(NULL, "access.db", NULL, DB_BTREE, 0, 0);
    
    pdb->close(0);
    delete pdb;
//    
//    pdb = new Db(NULL, 0);
//    pdb->remove("access.db", NULL, 0);
//    delete pdb;
    env.close(0);
}

bool PacketDB :: Compare(string str1, string str2){
    bool flag=false;
    for (int i = 0 ; i < str2.size()+1 ; i++){
        if (i == 84)
            int dfg=456;
        if (str1[i] == str2[i]){
            flag = true;
        }
        else {
            flag = false;
            break;
        }
    }
    return flag;
}


