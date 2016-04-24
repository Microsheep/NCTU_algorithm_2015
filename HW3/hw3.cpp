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
    vector<string> items;
    while(num_tests--){
        msgpack::unpack(result, buf, st.st_size, off);
        result.get().convert(pattern);
        msgpack::unpack(result, buf, st.st_size, off);
        result.get().convert(items); 

        bool flag=false;
        string words[26];
        
        if(pattern.length()==items.size()){
            for(int a=0;a<(int)pattern.length();a++){
                int now=pattern[a]-'a';
                if(words[now]==""){
                    words[now]=items[a];
                    continue;
                }
                else if(words[now]==items[a]){
                    continue;
                }
                else{
                    flag=true;
                    break;
                } 
            }
            sort(words,words+26);
            for(int a=0;a<25;a++){
                if(words[a]==words[a+1]&&words[a]!=""){
                    flag=true;
                    break;
                }
            }
        }
        else{
            flag=true;
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


