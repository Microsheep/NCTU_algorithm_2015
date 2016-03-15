#include <stdio.h>
#include <algorithm>
#define INF -123456789
char c;
int res = 0;
int a[20000];
int cnt, T;
int tmp, i;
int print_cnt;
char t[20];
inline int getint(){
    for(c=getchar();!('0'<=c&&c<='9')&&c!='\n';c=getchar());
    if(c == '\n')return INF;
    res = 0;
    for(;('0'<=c&&c<='9');res = (res*10+c-'0'), c=getchar());
    ungetc(c, stdin);
    return res;
}
inline void clean(){
    for(c=getchar();c!='\n'&&!('0'<=c&&c<='9');c=getchar());
    if('0'<=c&&c<='9')ungetc(c, stdin);
}
inline void print(int x){
    if(x == 0){
        putchar('0');
        return ;
    }
    print_cnt = 0;
    while(x){
        t[print_cnt++] = x%10 + '0';
        x /= 10;
    }
    for(int i=print_cnt-1;i>=0;i--)
        putchar(t[i]);
}
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    T = getint();
    clean();
    while(T--){
        cnt = 0;
        while((tmp=getint()) != INF)
            a[cnt++] = tmp;
        std::sort(a, a+cnt);
        print(a[0]);
        for(i=1;i<cnt;i++)
            putchar(' '), print(a[i]);
        putchar('\n');
    }
    return 0;
}
