#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#include <msgpack.hpp>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#define MAX_node 1000000
#define NEGINF -999999999ll
using namespace std;

bool test=false;

struct node{
    long long my_sum=0;
    long long my_max=0;
    long long l_max=0;
    long long r_max=0; 
};

void nprint(node in){
    cout << "Node: " << in.my_sum << " " << in.my_max << " " << in.l_max << " " << in.r_max << endl; 
}

node seg_tree[MAX_node*4];
vector<long long> items;

void build_tree(int x, int start, int end){
    if(start==end){
        //cout << "# " << x << " " << start << " " << items[x-1] << endl;
        seg_tree[x].my_sum=items[start-1];
        seg_tree[x].my_max=items[start-1];
        seg_tree[x].l_max=items[start-1];
        seg_tree[x].r_max=items[start-1];
    }
    else{
        //cout << "GG " << x << " " << start << " " << end << endl; 
        int mid=(start+end)/2;
        build_tree(2*x, start, mid);
        build_tree(2*x+1, mid+1, end);
        seg_tree[x].my_sum=seg_tree[2*x].my_sum+seg_tree[2*x+1].my_sum;
        seg_tree[x].l_max=max(seg_tree[2*x].my_sum+seg_tree[2*x+1].l_max,seg_tree[2*x].l_max);
        seg_tree[x].r_max=max(seg_tree[2*x].r_max+seg_tree[2*x+1].my_sum,seg_tree[2*x+1].r_max);
        seg_tree[x].my_max=max(seg_tree[x].my_sum,max(seg_tree[2*x].r_max+seg_tree[2*x+1].l_max,max(seg_tree[2*x].my_max,seg_tree[2*x+1].my_max)));
    }
    return;
}

node seg_q(int x, int start, int end, int a, int b){
    node tmp;
    //cout << "# " << x << " " << start << " " << end << " " << a << " " << b << endl;
    if(b<start||end<a){
        tmp.my_sum=0;
        tmp.my_max=NEGINF;
        tmp.l_max=NEGINF;
        tmp.r_max=NEGINF;
        //nprint(tmp);
        return tmp;
    }
    if(a<=start&&end<=b){
        tmp.my_sum=seg_tree[x].my_sum;
        tmp.my_max=seg_tree[x].my_max;
        tmp.l_max=seg_tree[x].l_max;
        tmp.r_max=seg_tree[x].r_max;
        //nprint(tmp);
        return tmp;
    } 
    int mid=(start+end)/2;
    node n1=seg_q(2*x,start,mid,a,b);
    node n2=seg_q(2*x+1,mid+1,end,a,b);
    tmp.my_sum=n1.my_sum+n2.my_sum;
    tmp.l_max=max(n1.l_max,n1.my_sum+n2.l_max);
    tmp.r_max=max(n2.r_max,n2.my_sum+n1.r_max);
    tmp.my_max=max(n1.my_sum+n2.my_sum,max(n1.r_max+n2.l_max,max(n1.my_max,n2.my_max)));
    //nprint(tmp);
    return tmp;
}

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
    if(test){
        cin >> num_tests;
    }
    else{
        result.get().convert(num_tests);
    }

    msgpack::sbuffer sbuf;
    
    while(num_tests--){
        int item_num;
        items.clear();
        if(test){
            cin >> item_num;
            for(int a=0;a<item_num;a++){
                long long tmp;
                cin >> tmp;
                items.push_back(tmp);
            }
        }
        else{
            msgpack::unpack(result, buf, st.st_size, off);
            result.get().convert(item_num);
            msgpack::unpack(result, buf, st.st_size, off);
            result.get().convert(items);
        }
        
        /*
        cout << "Items:";
        for(int a=0;a<item_num;a++){
            cout << " " << items[a];
        }
        cout << endl;
        */

        // Pre init
        
        memset(seg_tree,0,sizeof(seg_tree));
        
        build_tree(1,1,item_num);
        /*
        for(int a=1;a<=30;a++){
            cout << a << " " << seg_tree[a].my_sum << " " << seg_tree[a].my_max << " " << seg_tree[a].l_max << " " << seg_tree[a].r_max << endl;
        }
        */
        vector<int> ans;
        int query_num;
        if(test){
            cin >> query_num;
        }
        else{
            msgpack::unpack(result, buf, st.st_size, off);
            result.get().convert(query_num);
        }
        for(int q=0;q<query_num;q++){
            vector<int> query;
            if(test){
                int tmp1,tmp2;
                cin >> tmp1 >> tmp2;
                query.push_back(tmp1);
                query.push_back(tmp2); 
            }
            else{
                msgpack::unpack(result, buf, st.st_size, off);
                result.get().convert(query);
            }

            //cout << "Q #" << q << " " << query[0] << " " << query[1] << endl;

            // Calculate query  
            node tmp_ans=seg_q(1, 1, item_num, query[0], query[1]);
            if(test){
                cout << tmp_ans.my_max << endl;
            }
            ans.push_back(tmp_ans.my_max);
        } 
        msgpack::pack(&sbuf, ans);
    }
    
    delete[] buf;
    
    fout = fopen("output.txt", "wb");
    fwrite(sbuf.data(), sbuf.size(), 1, fout);
    fclose(fout);

}


