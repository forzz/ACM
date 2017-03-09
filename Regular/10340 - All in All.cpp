#include <cstdio>  
#include <cstdlib>  
#include <cstring>  
char s[10010],t[1000010];  
int main()  
{  
    while(scanf("%s%s",s,t)!=EOF) //t是子序列 
    {  
        int len_s=strlen(s),len_t=strlen(t),count=0;  
        for(int i=0; i<len_t; i++)  
            if(count<len_s)  //遍历每一个t
            {  
                if(t[i]==s[count]) count++;//  
            }  
            else break;  
        if(count==len_s) printf("Yes\n");  
        else printf("No\n");  
    }  
    return 0;  
}  