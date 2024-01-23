#include<stdio.h>
#include<string.h>
#define MSG_SIZE 10
int main()
{
	int n , b;
	printf("Enter the number of messages\n:");
	scanf("%d",&n);
	printf("Enter message size\n:");
	scanf("%d",&b);
	char msg[n][MSG_SIZE];
	for(int i=0;i<n;i++)
	{
		scanf("%s",msg[i]);
	}
	printf("Enter 0 for Even and 1 for Odd\n:");
	int flag;
	scanf("%d",&flag);
	for(int i=0;i<n;i++)
	{
		int r_count = 0;
		for(int j=0;j<b;j++)
		{
			if(msg[i][j] == '1')
			{
				r_count++;
			}
		}
		if(r_count%2 == flag)
		{
			printf("%s0\n",msg[i]);
		}
		else
		{
			printf("%s1\n",msg[i]);
		}
	}
}

