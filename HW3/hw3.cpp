#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#include <msgpack.hpp>
#include <sys/types.h>
#include <sys/stat.h>
using namespace std;

int main(void) {
    FILE *fin, *fout;

    struct stat st;
    stat("./input.txt", &st);
    char* buf = new char[st.st_size];

    fin = fopen("input.txt", "rb");
    fread(buf, st.st_size, 1, fin);
    fclose(fin);
    
    size_t off=0;
    msgpack::unpacked result;
    msgpack::unpack(result, buf, st.st_size, off);
    
    int num_tests;
    result.get().convert(num_tests);

    msgpack::sbuffer sbuf;
    
    string pattern;
    string words[30];
    vector<string> items;
    while(num_tests--){
        msgpack::unpack(result, buf, st.st_size, off);
        result.get().convert(pattern);
        msgpack::unpack(result, buf, st.st_size, off);
        result.get().convert(items);
        for(int a=0;a<26;a++){
            words[a]="";
        }

        bool flag=false;
        for(int a=0;a<(int)pattern.length();a++){
            int now=pattern[a]-'a';
            if(words[now]==""){
                words[now]=items[a];
                continue;
            }
            else{
                if(words[now]==items[a]){
                    continue;
                }
                else{
                    flag=true;
                    break;
                }
            }
        }
        
        if(flag){
            msgpack::pack(&sbuf, 0);
        }
        else{
            msgpack::pack(&sbuf, 1);
        }
    
    }
    
    delete[] buf;
    
    fout = fopen("output.txt", "wb");
    fwrite(sbuf.data(), sbuf.size(), 1, fout);
    fclose(fout);

}


