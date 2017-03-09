#include <stdio.h>
#include <algorithm>

using namespace std;

struct box{
	int x,y;
};
box b[6];

bool cmp(box a,box b)
{
	if(a.x==b.x)return a.y<b.y;
	return a.x<b.x;
}

int main()
{
	while(~scanf("%d",&b[0].x))
	{
		scanf("%d",&b[0].y);
		if(b[0].x>b[0].y)swap(b[0].x,b[0].y);
		for(int i=1; i<6; i++)
		{
			scanf("%d%d",&b[i].x,&b[i].y);
			if(b[i].x>b[i].y)swap(b[i].x,b[i].y);
		}

		sort(b,b+6,cmp);

		int error = 0;
		for(int i=0; i<3; i++)
		{
			if(b[i*2].x!=b[i*2+1].x || b[i*2].y!=b[i*2+1].y)
			{
				error = 1;
				break;
			}
		}
		if(!error && b[0].x==b[2].x && b[0].y==b[4].x && b[2].y==b[4].y)
			printf("POSSIBLE\n");
		else
			printf("IMPOSSIBLE\n");
	}
	return 0;
}