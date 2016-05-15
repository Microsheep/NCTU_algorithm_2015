#include <bits/stdc++.h>
#include <sys/stat.h>
#include <msgpack.hpp>
using namespace std;
typedef long long ll;
unsigned Rand(){
    static unsigned x=20150118;
    return x = x*0xdefaced+1;
}
class Treap{
    public:
        Treap *L, *R;
        ll val, sum, sz;
        unsigned pri;
        ll tmx, lmx, rmx;
        Treap(ll rhs=0): L(NULL), R(NULL), val(rhs), sum(rhs), sz(1), pri(Rand()), tmx(rhs), lmx(rhs), rmx(rhs){}
        void Up(){
            tmx = lmx = rmx = sum = val;
            sz = 1;
            if(L)sum += L->sum, sz += L->sz;
            if(R)sum += R->sum, sz += R->sz;
            if(L){
                lmx = L->lmx;
                lmx = max(lmx, L->sum+val);
                if(R) lmx = max(lmx, L->sum+val+R->lmx);
                tmx = max(tmx, L->tmx);
                tmx = max(tmx, L->rmx+val);
            }else if(R){
                lmx = max(lmx, val+R->lmx);
            }
            if(R){
                rmx = R->rmx;
                rmx = max(rmx, R->sum+val);
                if(L) rmx = max(rmx, R->sum+val+L->rmx);
                tmx = max(tmx, R->tmx);
                tmx = max(tmx, R->lmx+val);
            }else if(L){
                rmx = max(rmx, L->rmx+val);
            }
            if(L && R){
                tmx = max(tmx, L->rmx+val+R->lmx);
            }
        }
};
int size(Treap *rhs){
    return rhs?rhs->sz:0;
}
Treap* Merge(Treap *a,Treap *b)
{
    if(!a || !b) return a?a:b;
    if(a->pri > b->pri){
        a->R = Merge(a->R,b);
        a->Up();
        return a;
    }else{
        b->L = Merge(a,b->L);
        b->Up();
        return b;
    }
}
void Split(Treap *tr,Treap *&a,Treap *&b,int k){
    if(k == 0) a = NULL, b = tr;
    else if(k == size(tr)) a = tr, b = NULL;
    else{
        if(size(tr->L) >= k){
            b = tr;
            Split(tr->L, a, b->L, k);
            b->Up();
        }else{
            a = tr;
            Split(tr->R, a->R, b, k-size(tr->L)-1);
            a->Up();
        }
    }
}
void Free(Treap *tr){
    if(!tr)return;
    if(tr->L)
        Free(tr->L);
    if(tr->R)
        Free(tr->R);
    delete tr;
}
Treap* Build(const vector<ll> &in, int l, int r){
    if(l == r)return new Treap(in[l]);
    int mid=(l+r)>>1;
    return Merge(Build(in, l, mid), Build(in, mid+1, r));

}
int main(){
    int T;
    FILE *fin, *fout;
    struct stat st;
    stat("./input.txt", &st);
    char *buf = new char[st.st_size];
    fin = fopen("input.txt", "rb");
    fread(buf, st.st_size, 1, fin);
    size_t off = 0;
    msgpack::unpacked result;
    msgpack::unpack(result, buf, st.st_size, off);
    result.get().convert(T);
    msgpack::sbuffer sbuf;
    while(T--){
        Treap *root = NULL;
        int N;
        msgpack::unpack(result, buf, st.st_size, off);
        result.get().convert(N);
        vector<ll> in;
        msgpack::unpack(result, buf, st.st_size, off);
        result.get().convert(in);
        root = Build(in, 0, in.size()-1);
        int Q;
        msgpack::unpack(result, buf, st.st_size, off);
        result.get().convert(Q);
        vector<ll> ans;
        while(Q--){
            int l, r;
            pair<int, int> p;
            msgpack::unpack(result, buf, st.st_size, off);
            result.get().convert(p);
            l = p.first, r = p.second;
            Treap *a, *b, *c, *d;
            Split(root, a, b, r);
            Split(a, c, d, l-1);
            ans.push_back(d->tmx);
            a = Merge(c, d);
            root = Merge(a, b);
        }
        Free(root);
        msgpack::pack(&sbuf, ans);
    }
    fout = fopen("./output.txt", "wb");
    fwrite(sbuf.data(), sbuf.size(), 1, fout);
    fclose(fin);
    fclose(fout);
    delete [] buf;
    return 0;
}
