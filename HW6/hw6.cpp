#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <math.h>
using namespace std;

struct circle{
    int pos,rad;
    double lpos,rpos;
};

bool cmp(circle a, circle b){
    if(a.lpos==b.lpos){
        return a.rpos<b.rpos;
    }
    else{
        return a.lpos<b.lpos; 
    }
}

int main(){
    int n,l,w;
    while(~scanf("%d %d %d",&n,&l,&w)){
        circle cir[n];
        double sqrtrw,rw,ww=w/2.0,w2=ww*ww;
        for(int a=0;a<n;a++){
            scanf("%d %d",&cir[a].pos,&cir[a].rad);
            if(cir[a].rad<ww){
                cir[a].lpos=0;
                cir[a].rpos=0;
            }
            else{
                rw=cir[a].rad*cir[a].rad-w2;
                sqrtrw=sqrt(rw);
                cir[a].lpos=cir[a].pos-sqrtrw;
                cir[a].rpos=cir[a].pos+sqrtrw;
            }
        }
        sort(cir,cir+n,cmp);

        int ans=0;
        double now=0,maxx=0;
        for(int a=0;a<n;a++){
            if(cir[a].lpos<=now){
                maxx=max(maxx,cir[a].rpos);
                continue;
            }
            else{
                if(maxx>now){
                    if(maxx>l){
                        break;
                    }
                    now=maxx;
                    ans++; 
                }
                if(a!=n-1){
                    a--;
                }
            }
        }
        
        maxx=max(maxx,cir[n-1].rpos);
        if(maxx>now){
            now=maxx;
            ans++;
        }

        if(now<l){
            ans = -1;
        }

        cout << ans << endl;
    }
    return 0;
}

