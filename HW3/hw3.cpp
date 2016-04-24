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

        int ans=1;
        string words[26];
        
        int n=0;
        int tests[26];
        
        if(pattern.length()==items.size()){
            for(int a=0;a<(int)pattern.length();a++){
                int now=pattern[a]-'a';
                if((int)words[now].length()==0){
                    for(int b=0;b<n;b++){
                        if(items[a]==words[tests[b]]){
                            ans=0;
                            goto OUT;
                        }
                    }
                    words[now]=items[a];
                    tests[n++]=a;
                    continue;
                }
                else if(words[now]==items[a]){
                    continue;
                }
                else{
                    ans=0;
                    break;
                } 
            }
        }
        else{
            ans=0;
        }
        
        OUT:
        msgpack::pack(&sbuf, ans);
    
    }
    
    delete[] buf;
    
    fout = fopen("output.txt", "wb");
    fwrite(sbuf.data(), sbuf.size(), 1, fout);
    fclose(fout);

}


