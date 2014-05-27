#include <cstdio>
struct Gr{
	int to;		
	int W;
	Gr *next;
	Gr(int tt,int ww){
		to=tt;
		W=ww;
		next=0;
	}
}*a[110001],*tmp;
int n,m,s,f,d[110001],l,r,w,min,pos;
bool used[110001];

int main()
{
	freopen("path.in","r",stdin);
	freopen("path.out","w",stdout);	
		scanf("%d %d",&n,&m);
		int i;
		for (i=1;i<=m;i++){
			scanf("%d %d %d",&l,&r,&w);
			tmp=new Gr(r,w);
			tmp->next=a[l];
			a[l]=tmp;
			tmp=new Gr(l,w);
			tmp->next=a[r];
			a[r]=tmp;
		}
	scanf("%d %d",&s,&f);
	for (i=1;i<=n;i++)d[i]=2147483647;
	tmp=a[s];
	while (tmp){
		if (d[tmp->to]>tmp->W)d[tmp->to]=tmp->W;
		tmp=tmp->next;
	}
	used[s]=1;
	while (!used[f]){
		min=2147483647;
		for (i=1;i<=n;i++)
		if (!used[i]&&min>d[i]){min=d[i];pos=i;}
		if (min==2147483647)break;
		used[pos]=true;
		tmp=a[pos];
		while (tmp){
			if (d[tmp->to]>d[pos]+tmp->W)d[tmp->to]=d[pos]+tmp->W;
			tmp=tmp->next;
		}
	}
	printf("%d",d[f]);
	fclose(stdin);
	fclose(stdout);
}