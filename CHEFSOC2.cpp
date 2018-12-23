
// question :- https://www.codechef.com/problems/CHEFSOC2

#include <iostream>
#include <string.h>
using namespace std;
#define mod 1000000007

int main()
{
	int t;
	cin >> t;
	while(t--)
	{
		int n,m,s;
		cin>>n>>m>>s;
		int A[m+1];
		for(int i=1;i<=m;i++)
			cin>>A[i];
		int dp[n+1][m+1];
		memset(dp,0,sizeof(dp[0][0])*(n+1)*(m+1));
		if(s-A[1] > 0)
			dp[s-A[1]][1] = 1;
		if(s+A[1] <= n)
			dp[s+A[1]][1] = 1;
		for(int j = 2;j<=m;j++)
		{
			for(int i=1;i<=n;i++)
			{
				if(i-A[j] > 0 & i+A[j] <=n)
					dp[i][j] = (dp[i-A[j]][j-1] + dp[i+A[j]][j-1]) % mod;
				else if(i-A[j] > 0)
					dp[i][j] = dp[i-A[j]][j-1];
				else if(i+A[j] <=n)
					dp[i][j] = dp[i+A[j]][j-1];
			}
		}

		for(int i=1;i<=n;i++)
			cout << dp[i][m] << " ";
		cout << endl;
	}
	return 0;
}

// DP