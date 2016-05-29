#include <iostream>
#include <string>
#include <set>
#include <msgpack.hpp>
#include <sys/types.h>
#include <sys/stat.h>
using namespace std;

int main() {
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
    
    while(num_tests--){
        string in;
        msgpack::unpack(result, buf, st.st_size, off);
        result.get().convert(in);
        cout << "Test: " << in << endl;
        
        vector <int> operand, op;
        /* +1 -2 *3 &4 |5 */
        int tmp=0;
        for(int a=0;a<(int)in.length();a++){
            if(in[a]==' '||in[a]=='\n'){
                continue;
            }
            else if(in[a]=='+'||in[a]=='-'||in[a]=='*'||in[a]=='&'||in[a]=='|'){
                operand.push_back(tmp);
                tmp=0;
                if(in[a]=='+'){
                    op.push_back(1);
                }
                else if(in[a]=='-'){
                    op.push_back(2);
                }
                else if(in[a]=='*'){
                    op.push_back(3);
                }
                else if(in[a]=='&'){
                    op.push_back(4);
                }
                else{
                    op.push_back(5);
                }
            }
            else{
                tmp = 10*tmp + (in[a]-'0');
            }
        }
        operand.push_back(tmp);
        int n=(int)operand.size();

        for(int a=0;a<(int)operand.size();a++){
            cout << operand[a] << " ";
        }
        cout << endl;
        for(int a=0;a<(int)op.size();a++){
            cout << op[a] << " ";
        }
        cout << endl;
        
        set <int> dp[n][n];
        
        for(int a=0;a<n;a++){
            dp[0][a].insert(operand[a]);
        }

        for(int a=1;a<n;a++){
            for(int b=0;b<n-a;b++){
                for(int c=a-1;c>=0;c--){
                    cout << "@ " << a << " " << b << " # " << c << " " << b << " " << a-1-c << " " << b+1+c << endl;
                    if(op[b+c]==1){
                        for(int x : dp[c][b]){
                            for(int y : dp[a-1-c][b+1+c]){
                                dp[a][b].insert(x+y);
                            }
                        }
                    }
                    else if(op[b+c]==2){
                        for(int x : dp[c][b]){
                            for(int y : dp[a-1-c][b+1+c]){
                                dp[a][b].insert(x-y);
                            }
                        }
                    }
                    else if(op[b+c]==3){
                        for(int x : dp[c][b]){
                            for(int y : dp[a-1-c][b+1+c]){
                                dp[a][b].insert(x*y);
                            }
                        }
                    }
                    else if(op[b+c]==4){
                        for(int x : dp[c][b]){
                            for(int y : dp[a-1-c][b+1+c]){
                                dp[a][b].insert(x&y);
                            }
                        }
                    }
                    else{
                        for(int x : dp[c][b]){
                            for(int y : dp[a-1-c][b+1+c]){
                                dp[a][b].insert(x|y);
                            }
                        }
                    }
                }
            }
        }
        
        for(int a=0;a<n;a++){
            for(int b=0;b<n-a;b++){
                cout << a << " " << b << ": ";
                for(int c: dp[a][b]){
                    cout << c << " ";
                }
                cout << endl;
            }
        }
        
        int ans=(int)dp[n-1][0].size();
        msgpack::pack(&sbuf, ans);
    }
    
    delete[] buf;
    
    fout = fopen("output.txt", "wb");
    fwrite(sbuf.data(), sbuf.size(), 1, fout);
    fclose(fout);

}

