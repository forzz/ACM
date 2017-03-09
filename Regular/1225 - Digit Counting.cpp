#include<cstdio>  
int a[10000][10];  
int main()  
{  
    for(int i=1;i<10000;i++)  
    {  
        for(int j=0;j<10;j++)  
            a[i][j]=a[i-1][j];  
        for(int k=i;k;k/=10)  
            a[i][k%10]++;  
    }  
    int n;  
    scanf("%d",&n);  
    for(int i=0;i<n;i++)  
    {  
        int num;  
        scanf("%d",&num);  
        for(int j=0;j<9;j++)  
            printf("%d ",a[num][j]);  
        printf("%d\n",a[i][9]);  
    }  
    return 0;  
}  