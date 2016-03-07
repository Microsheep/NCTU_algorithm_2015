#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    FILE *f_in, *f_out;
    f_in = fopen("./input.txt", "r");
    f_out = fopen("./output.txt", "w");
    char line[100000];
    vector<int> numbers;
    fgets(line,100,f_in);
    while(fgets(line,100000,f_in)){
        numbers.clear();
        char* split;
        split = strtok (line," ");
        while (split!=NULL){
            int tmp=atoi(split);
            numbers.push_back(tmp);
            split = strtok(NULL, " ");
        }
        sort(numbers.begin(), numbers.end());
        vector<int>::iterator it;
        for(it=numbers.begin();it!=numbers.end();++it){
            fprintf(f_out, "%d ", *it);
        }
        fprintf(f_out, "\n");
    }
    fclose(f_in);
    fclose(f_out);
    return 0;
}

