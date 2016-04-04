#include <stdlib.h>
#include <string.h>
#include <algorithm>
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
    
    vector<int> NUMBERS;
    while(num_tests--){
        msgpack::unpack(result, buf, st.st_size, off);
        result.get().convert(NUMBERS);
        sort(NUMBERS.begin(), NUMBERS.end());
        msgpack::pack(&sbuf, NUMBERS);
    }
    
    delete[] buf;

    fout = fopen("output.txt", "wb");
    fwrite(sbuf.data(), sbuf.size(), 1, fout);
    fclose(fout);
}


