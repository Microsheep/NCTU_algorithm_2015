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
    return a.lpos<b.lpos; 
}

int main(){
    FILE *f_in, *f_out;
    f_in = fopen("./input.txt", "r");
    f_out = fopen("./output.txt", "w");

    int n,l,w;
    while(~fscanf(f_in,"%d %d %d",&n,&l,&w)){
        circle cir[n];
        double sqrtrw,rw,ww=w/2.0,w2=ww*ww;
        for(int a=0;a<n;a++){
            fscanf(f_in,"%d %d",&cir[a].pos,&cir[a].rad);
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
                if(a!=n-1){
                    continue;
                }
                else{
                    if(maxx>now){
                        now=maxx;
                        ans++;
                    }
                }
            }
            else{
                if(maxx>now){
                    now=maxx;
                    maxx=0;
                    ans++;
                    if(now>=l){
                        break;
                    }
                    if(a!=n-1){
                        a--;
                    }
                    else{
                        if(cir[n-1].lpos<=now){
                            maxx=max(maxx,cir[n-1].rpos);
                            if(maxx>now){
                                now=maxx;
                                ans++;
                            }
                        }
                    }
                }
                else{
                    break;
                }
            }
        }
        
        if(now<l){
            ans = -1;
        }

        fprintf(f_out,"%d\n",ans);
    }
    fclose(f_in);
    fclose(f_out);
    return 0;
}

