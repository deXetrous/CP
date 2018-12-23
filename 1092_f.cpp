
// question link :- https://codeforces.com/problemset/problem/1092/F

#include <bits/stdc++.h>
using namespace std;

struct node
{
	long long int index;
	vector <long long int> neighbours;
	long long int value; // denotes the sum of its value(given in ques) and the sum of value(given in ques) of its children nodes.
};

// recursive function to fill the parameter value for all the nodes.
void fillvalues(struct node tree[], long long int pos, long long int a[], long long int ch[])
{
	ch[pos] = 1;
	long long int val = a[pos];
	for (long long int i = 0; i < tree[pos].neighbours.size(); ++i)
	{
		long long int x = tree[pos].neighbours[i];
		if(ch[x] == 0)
		{
			fillvalues(tree, x, a, ch);
			val += tree[x].value;
		}
	}
	tree[pos].value = val;
	return;

}

// I have assumed that node 1 is the root node of our tree.
int main()
{
	long long int n;
	cin >> n;
	long long int a[n+1];
	long long int ch[n+1];
	struct node tree[n+1];
	for (long long int i = 1; i <= n; ++i)
	{
		tree[i].index = i;
		tree[i].value = 0;
		ch[i] = 0;
		cin >> a[i];
	}
	for (long long int i = 0; i < n-1; ++i)
	{
		long long int t1,t2;
		cin>>t1>>t2;
		tree[t1].neighbours.push_back(t2);
		tree[t2].neighbours.push_back(t1);
	}
	fillvalues(tree, 1, a, ch);
	// for(long long int i =1;i<=n; i++)
	// {
	// 	cout << i << "   " << tree[i].value << endl; 
	// }
	long long int maxi = 0;
	long long int ans[n+1]; // ans[i] is the cost if node i is chosen. final ans will be the max of the array values.
	ans[1] = 0;
	bool visited[n+1]; 
    long long int depth[n+1];
    for(long long int i = 1; i <= n; i++) 
    {
    	depth[i] = 0;
        visited[i] = false; 
    }

    queue <long long int> q; // for bfs
    visited[1] = true; 
    q.push(1); 
    // calculating answer for node 1 i.e. choosing the node 1.
    while(!q.empty()) 
    {
        long long int s = q.front();
        q.pop(); 
        
        for (long long int i = 0; i < tree[s].neighbours.size(); ++i) 
        {
          	long long int pos = tree[s].neighbours[i];
          	depth[pos] = depth[s] + 1;
            if (!visited[pos])
            { 
        		ans[1] += a[pos] * depth[pos];
                visited[pos] = true; 
                q.push(pos); 
            } 
        }
    }
    
    maxi = max(maxi, ans[1]);

    // calculating for rest of the nodes, using the calculation done for 1st node and the nodes parent.
    // Concept - DP. 
    long long int count = 1;
    queue <long long int> q1; //for bfs
    for(long long int i = 1; i <= n; i++) 
        visited[i] = false;
   
    visited[1] = true; 
    q1.push(1);
    while(!q1.empty())
    {
    	long long int s = q1.front();
        q1.pop();
    	for (long long int i = 0; i < tree[s].neighbours.size(); ++i)
    	{
    		long long int pos = tree[s].neighbours[i];
    		
			if (!visited[pos])
            { 
            	// most important line
            	ans[pos] = ans[s] + tree[1].value - 2*tree[pos].value;
    			maxi = max(maxi, ans[pos]);
                visited[pos] = true; 
                q1.push(pos); 
            }
    	}
    }
    
    cout << maxi << endl;

}