#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <msgpack.hpp>
#include <sys/types.h>
#include <sys/stat.h>
#define MAX_node 100000
#define NEGINF -999999999ll
using namespace std;

struct node{
    long long my_sum=0;
    long long my_max=0;
    long long l_max=0;
    long long r_max=0; 
};

node seg_tree[MAX_node*2];
vector<long long> items;

void build_tree(int x, int start, int end){
    if(start==end){
        seg_tree[x].my_sum=items[start-1];
        seg_tree[x].my_max=items[start-1];
        seg_tree[x].l_max=items[start-1];
        seg_tree[x].r_max=items[start-1];
    }
    else{
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
    int mid=(start+end)/2;
    if(a==start&&end==b){
        return seg_tree[x];
    }
    else if(b<=mid){
        node n=seg_q(2*x,start,mid,a,b);
        return n;
    }
    else if(a>mid){
        node n=seg_q(2*x+1,mid+1,end,a,b);
        return n;
    }
    else{
        node tmp;
        node n1=seg_q(2*x,start,mid,a,mid);
        node n2=seg_q(2*x+1,mid+1,end,mid+1,b);
        tmp.my_sum=n1.my_sum+n2.my_sum;
        tmp.l_max=max(n1.l_max,n1.my_sum+n2.l_max);
        tmp.r_max=max(n2.r_max,n2.my_sum+n1.r_max);
        tmp.my_max=max(n1.my_sum+n2.my_sum,max(n1.r_max+n2.l_max,max(n1.my_max,n2.my_max)));
        return tmp;
    }
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
    result.get().convert(num_tests);

    msgpack::sbuffer sbuf;
    
    while(num_tests--){
        int item_num;
        items.clear();
        msgpack::unpack(result, buf, st.st_size, off);
        result.get().convert(item_num);
        msgpack::unpack(result, buf, st.st_size, off);
        result.get().convert(items);
        
        memset(seg_tree,0,sizeof(seg_tree)); 
        build_tree(1,1,item_num);

        vector<long long> ans;
        int query_num;
        msgpack::unpack(result, buf, st.st_size, off);
        result.get().convert(query_num);
        
        for(int q=0;q<query_num;q++){
            vector<int> query;
            msgpack::unpack(result, buf, st.st_size, off);
            result.get().convert(query);

            node tmp_ans=seg_q(1, 1, item_num, query[0], query[1]);
            ans.push_back(tmp_ans.my_max);
        } 
        msgpack::pack(&sbuf, ans);
    }
    
    delete[] buf;
    
    fout = fopen("output.txt", "wb");
    fwrite(sbuf.data(), sbuf.size(), 1, fout);
    fclose(fout);

}

