#include <cstdio>
#include <cstring>

int main()
{
#ifdef LOCAL 
    freopen("in", "r", stdin);
#endif
    int n;
    scanf("%d", &n);
    char s[100];
    while(n--)
    {
        scanf("%s", s);
        int len = strlen(s);
        for(int i = 1; i <= len; i++)
            if(len % i == 0)
            {
                int k;
                for(k = i; k < len; k++)
                    if(s[k] != s[k%i])   break;
                if(k == len)
                {
                    printf("%d\n", i);
                    if(n)   printf("\n");
                    break;
                }
            }
    }
    return 0;
}