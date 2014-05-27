#include <iostream>
using namespace std;
const int base = 10000;

struct BigInt{
	int num[1000];
	int sign;
	BigInt()
	{
		sign = 0;
		memset(num,0,sizeof(num));
	}

	BigInt(long long x)
	{
		sign = 1;
		memset(num,0,sizeof(num));

		if (x == 0) {
			sign = 0;
			num[0]=1;
			num[1]=0;
		}

		if (x < 0) {
			sign = -1;
			x*=-1;
		}
		while (x > 0) {
			num[++num[0]] = x%base;
			x/=base;
		}
	}

	void read() 
	{
		char ch = 'a';
		while (!isdigit(ch) && ch!='-') ch = getchar();
		if (ch == '-') sign = -1 , ch = getchar(); else  
		sign = 1;
		while (isdigit(ch)) {
			for (int i = num[0]; i >= 1; i--)
			{
				num[i+1]+=(num[i]*10)/base;
				num[i] = (num[i]*10)%base;
			}
			num[1] = num[1]+ch-48;
			if (num[num[0]+1]) num[0]++;
			ch = getchar();
		}

		if (num[0]==1 && num[1]==0) sign = 0;

	}

	void write()
	{
		if (sign == -1) putchar('-');
		printf("%d",num[num[0]]);
		for (int i = num[0] - 1; i>=1; i--)
		printf("%04d",num[i]);
	}

	void writeln()
	{
		if (sign == -1) putchar('-');
		printf("%d",num[num[0]]);
		for (int i = num[0] - 1; i>=1; i--)
		printf("%04d",num[i]);
		putchar('\n');
	}

	BigInt add(const BigInt &a) {
		BigInt c;
		c.num[0] = max(a.num[0],num[0]);
		for (int i = 1; i <= c.num[0]; i++) {
			c.num[i+1]+=(c.num[i]+a.num[i]+num[i])/base;
			c.num[i]  = (c.num[i]+a.num[i]+num[i])%base;
		}
		if (c.num[c.num[0]+1]) c.num[0]++;
		return c;
	}
	BigInt multiply(const BigInt &a) {
		BigInt c;
		c.num[0] = a.num[0]+num[0];
		for (int i = 1; i <= a.num[0]; i++)
		for (int j = 1; j <= num[0]; j++) {
			c.num[i+j] +=  (c.num[i+j-1]+a.num[i]*num[j])/base;
			c.num[i+j-1] = (c.num[i+j-1]+a.num[i]*num[j])%base;
		}

		while (c.num[0]>1 && !c.num[c.num[0]]) c.num[0]--;
		return c;
	}
	BigInt subtract(const BigInt &a) {
		BigInt c;
		c.num[0] = num[0];
		
		for (int i = 1; i <= num[0]; i++) {
			c.num[i] += num[i] - a.num[i];
			if (c.num[i] < 0) {
				c.num[i+1]--;
				c.num[i]+=base;         
			}
		}
		while (c.num[0] > 1 && !c.num[c.num[0]]) c.num[0]--;
		return c;
	}

	BigInt divide(long long x){
		BigInt c;
		
		long long carry = 0;

		for (int i = num[0]; i >= 1; i--) {
			carry = carry*base+num[i];
			c.num[i] = carry/x;
			carry%=x;
		}
		c.num[0] = num[0];
		while (c.num[0] > 1 && !c.num[c.num[0]]) c.num[0]--;
		return c;
	}

	int comp(const BigInt &a) {
		if (a.num[0] > num[0]) return -1;
		if (a.num[0] < num[0]) return 1;

		for (int i = num[0]; i >= 1; i--)
		if (a.num[i] > num[i]) return -1; else
		if (a.num[i] < num[i]) return 1;

		return 0;
	}
	                             
};

BigInt operator-(BigInt a,BigInt b)
{
	if (a.sign == -1 && b.sign == -1) 
	{	
		b.sign = a.sign = 1;
		return b-a;
	}

	if (b.sign == -1) {
		BigInt c = a.add(b);
		c.sign = 1;
		return c;
	}
	if (a.sign == -1) {
		BigInt c = a.add(b);
		c.sign = -1;
		return c;
	}

	int cmp = a.comp(b);

	if (cmp > 0) {
		BigInt c = a.subtract(b);
		c.sign = 1;
		return c;
	}

	if (!cmp) {
		BigInt c = BigInt(0);
		return c;
	}

	BigInt c = b.subtract(a);
	c.sign = -1;
	return c;
}

BigInt operator+(BigInt a,BigInt b) 
{
	if (a.sign == b.sign) {
		BigInt c = a.add(b);
		c.sign = a.sign;
		return c;		
	}

	if (a.sign == -1) {
		a.sign = 1;
		return b-a;
	}
	if (b.sign == -1) {
		b.sign = 1;
		return a-b;
	}
}



BigInt operator*(BigInt a,BigInt b)
{
	BigInt c;
	c = a.multiply(b);
	c.sign = a.sign*b.sign;
	return c;

}

BigInt operator/(BigInt a,long long b) {
	if (b==0) {
		cerr<<"Division by zero";
		assert(false);
	}
	
	if (b < 0){
		BigInt c = a.divide(-b);
		c.sign = -a.sign;
		if (c.num[0] == 1 && c.num[1]==0) c.sign = 0;
		return c;
	} else
	{
		BigInt c = a.divide(b);
		c.sign = a.sign;
		if (c.num[0] == 1 && c.num[1]==0) c.sign = 0;
		return c;
	}
	
}

bool operator<(BigInt a,BigInt b) {
	if (a.sign==-1 && b.sign==-1) return (a.comp(b)==1);
	if (a.sign==-1) return true;
	if (b.sign==-1) return false;
	return (a.comp(b)==-1);
} 

bool operator>(BigInt a,BigInt b) {
	if (a.sign==-1 && b.sign==-1) return (a.comp(b)==-1);
	if (a.sign==-1) return false;
	if (b.sign==-1) return true;
	return (a.comp(b)==1);
} 

bool operator==(BigInt a,BigInt b) {
	return (a.sign == b.sign && a.comp(b) == 0);
}

bool operator!=(BigInt a,BigInt b) {
	return (a.sign!=b.sign || a.comp(b)!=0);	
}

int main()
{                                            
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	BigInt a,c;
	a.read();
	int b;
	scanf("%d",&b);
	c = a/b;
	c.writeln();
	return 0;
}
