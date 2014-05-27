#include <cstdio>
#include <cstring>

int n,i,l,r,z[400006];
char s[400006];
int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	gets(s);
	l=-1; r=-1;
	n=strlen(s);
	for (i=1;i<n;i++){
		if (i>r){
			z[i]=0;
			while (s[z[i]]==s[z[i]+i]&&z[i]<2*n) z[i]++;
			if (z[i]) l=i,r=z[l]+l-1;
		} else
		if (z[i-l]<r-i+1) z[i]=z[i-l]; else
		{
			z[i]=r-i+1;
			while (s[z[i]]==s[z[i]+i]&&z[i]<2*n) z[i]++;
			if (z[i]+i-1>r) l=i,r=z[l]+l-1;
		}
	}
	for (i=0;i<n;i++) printf("%d ",z[i]);

}
