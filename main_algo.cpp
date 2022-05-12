#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define mk make_pair
typedef pair<int, int> pii;
#define fs first
#define sc second 
#define sp <<" "<<

vector <pii> g[100005];
vector <pii> g1[100005];
int src,dest;
map <pii,int> mp;
int cs[105],cs_wt[105];
int n=100000;
int m;
int dis[100005];
int par[100005];
int currcharge;
int fullcharge;
int dist[52][100005];
vector <int> used_cs;


// dijkstra function to generated shortest path.
vector <int> dij(int st,int en)
{
	priority_queue<pair<int,int>>q;
	
	for(int i=0; i<100005; i++)
	{
		dis[i]=1e8;
		par[i]=-1;
	}

	q.push({0,st});
	dis[st]=0;

	while(!q.empty())
	{
		int u=q.top().sc;
		q.pop();
		for(int i=0; i<(int)g[u].size(); i++)
		{
			if(dis[u]+g[u][i].sc<dis[g[u][i].fs])
			{
				dis[g[u][i].fs]=dis[u]+g[u][i].sc;
				par[g[u][i].fs]=u;
				q.push({-dis[g[u][i].fs],g[u][i].fs});
			}
		}
	}

	vector <int> v;
	if(dis[en]==1e8)
		return v;
	int f=en;
	v.pb(en);
	while(par[f]!=st)
	{
		f=par[f];
		v.pb(f);
	}
	v.pb(st);
	reverse(v.begin(),v.end());
	return v;
}

// First optimal path based on minimus distance.
vector <int> mindist()
{
	// creating an vector in which we will store path.
	vector <int> ans;
	ans.clear();
	int mindist=1e8;
	int cnt=used_cs.size();
	// codition if vehicle do have enough charge to either go to dest.
	if(dist[50][dest]<=currcharge)
	{
		return ans;
	}
	for(int i=0; i<cnt; i++)
	{
		if(dist[50][cs[used_cs[i]]]<=currcharge && dist[used_cs[i]][dest]<=fullcharge)
		{
			if(dist[50][cs[used_cs[i]]]+dist[used_cs[i]][dest]<mindist)
			{
				ans.clear();
				ans.pb(used_cs[i]);
				mindist=dist[50][cs[used_cs[i]]]+dist[used_cs[i]][dest];
			}
		}
	}

	if((int)ans.size())
	{
		return ans;
	}
	// checking if vehicle can go to chaarging station with one charging in the journey.
	for(int i=0; i<cnt; i++)
	{
		if(currcharge>=dist[50][cs[used_cs[i]]])
		{
			for(int j=0; j<cnt; j++)
			{
				if(dist[used_cs[i]][cs[used_cs[j]]]<=fullcharge && dist[used_cs[j]][dest]<=fullcharge)
				{
					// if condition to chech minimum distance.
					if(dist[50][cs[used_cs[i]]]+dist[used_cs[i]][cs[used_cs[j]]]+dist[used_cs[j]][dest]<mindist)
					{
						ans.clear();
						ans.pb(used_cs[i]);
						ans.pb(used_cs[j]);
						mindist=dist[50][cs[used_cs[i]]]+dist[used_cs[i]][cs[used_cs[j]]]+dist[used_cs[j]][dest];
					}
				}
			}
		}
	}

	if((int)ans.size())
	{
		return ans;
	}

	for(int i=0; i<cnt; i++)
	{
		if(currcharge>=dist[50][cs[used_cs[i]]])
		{
			for(int j=0; j<cnt; j++)
			{
				if(dist[used_cs[i]][cs[used_cs[j]]]<=fullcharge)
				{
					for(int k=0; k<cnt; k++)
					{
						if(dist[used_cs[j]][cs[used_cs[k]]]<=fullcharge && dist[used_cs[k]][dest]<=fullcharge)
						{
							if(dist[50][cs[used_cs[i]]]+dist[used_cs[i]][cs[used_cs[j]]]+dist[used_cs[j]][cs[used_cs[k]]]+dist[used_cs[k]][dest]<mindist)
							{
								ans.clear();
								ans.pb(used_cs[i]);
								ans.pb(used_cs[j]);
								ans.pb(used_cs[k]);
								mindist=dist[50][cs[used_cs[i]]]+dist[used_cs[i]][cs[used_cs[j]]]+dist[used_cs[j]][cs[used_cs[k]]]+dist[used_cs[k]][dest];
							}
						}
					}
				}
			}
		}
	}

	if((int)ans.size())
	{
		return ans;
	}
	cout<<"Increse Range\n";
	exit(0);

}

// function to generate path for minimum possible time of journey.
vector <int> mintime()
{
	// creating an vector in which we will store path.
	vector <int> ans;
	ans.clear();
	double mindist=1e8;
	int cnt=used_cs.size();
	// codition if vehicle do have enough charge to either go to dest.
	if(dist[50][dest]<=currcharge)
	{
		return ans;
	}
	for(int i=0; i<cnt; i++)
	{
		if(dist[50][cs[used_cs[i]]]<=currcharge && dist[used_cs[i]][dest]<=fullcharge)
		{
			if((dist[50][cs[used_cs[i]]]+dist[used_cs[i]][dest]+cs_wt[used_cs[i]])/40000.0+
				(dist[50][cs[used_cs[i]]]+dist[used_cs[i]][dest]-currcharge)*2.0/fullcharge<mindist)
			{
				ans.clear();
				ans.pb(used_cs[i]);
				mindist=(dist[50][cs[used_cs[i]]]+dist[used_cs[i]][dest]+cs_wt[used_cs[i]])/40000.0+
				(dist[50][cs[used_cs[i]]]+dist[used_cs[i]][dest]-currcharge)*2.0/fullcharge;
			}
		}
	}

	if((int)ans.size())
	{
		return ans;
	}
	// checking if vehicle can go to chaarging station with one charging in the journey.
	for(int i=0; i<cnt; i++)
	{
		if(currcharge>=dist[50][cs[used_cs[i]]])
		{
			for(int j=0; j<cnt; j++)
			{
				if(dist[used_cs[i]][cs[used_cs[j]]]<=fullcharge && dist[used_cs[j]][dest]<=fullcharge)
				{
					// here considering the wating time of charging at charing station and cheking for minimum time.
					if((dist[50][cs[used_cs[i]]]+dist[used_cs[i]][cs[used_cs[j]]]+dist[used_cs[j]][dest]+cs_wt[used_cs[i]]+cs_wt[used_cs[j]])/40000.0
						+(dist[50][cs[used_cs[i]]]+dist[used_cs[i]][cs[used_cs[j]]]+dist[used_cs[j]][dest]-currcharge)*2.0/fullcharge<mindist)
					{
						ans.clear();
						ans.pb(used_cs[i]);
						ans.pb(used_cs[j]);
						mindist=(dist[50][cs[used_cs[i]]]+dist[used_cs[i]][cs[used_cs[j]]]+dist[used_cs[j]][dest]+cs_wt[used_cs[i]]+cs_wt[used_cs[j]])/40000.0
						+(dist[50][cs[used_cs[i]]]+dist[used_cs[i]][cs[used_cs[j]]]+dist[used_cs[j]][dest]-currcharge)*2.0/fullcharge;
					}
				}
			}
		}
	}

	if((int)ans.size())
	{
		return ans;
	}

	for(int i=0; i<cnt; i++)
	{
		if(currcharge>=dist[50][cs[used_cs[i]]])
		{
			for(int j=0; j<cnt; j++)
			{
				if(dist[used_cs[i]][cs[used_cs[j]]]<=fullcharge)
				{
					for(int k=0; k<cnt; k++)
					{
						if(dist[used_cs[j]][cs[used_cs[k]]]<=fullcharge && dist[used_cs[k]][dest]<=fullcharge)
						{
							if((dist[50][cs[used_cs[i]]]+dist[used_cs[i]][cs[used_cs[j]]]+dist[used_cs[j]][cs[used_cs[k]]]+dist[used_cs[k]][dest]+cs_wt[used_cs[i]]+cs_wt[used_cs[j]]+cs_wt[used_cs[k]])/40000.0
								+(dist[50][cs[used_cs[i]]]+dist[used_cs[i]][cs[used_cs[j]]]+dist[used_cs[j]][cs[used_cs[k]]]+dist[used_cs[k]][dest]-currcharge)*2.0/fullcharge<mindist)
							{
								ans.clear();
								ans.pb(used_cs[i]);
								ans.pb(used_cs[j]);
								ans.pb(used_cs[k]);
								mindist=(dist[50][cs[used_cs[i]]]+dist[used_cs[i]][cs[used_cs[j]]]+dist[used_cs[j]][cs[used_cs[k]]]+dist[used_cs[k]][dest]+cs_wt[used_cs[i]]+cs_wt[used_cs[j]]+cs_wt[used_cs[k]])/40000.0
								+(dist[50][cs[used_cs[i]]]+dist[used_cs[i]][cs[used_cs[j]]]+dist[used_cs[j]][cs[used_cs[k]]]+dist[used_cs[k]][dest]-currcharge)*2.0/fullcharge;
							}
						}
					}
				}
			}
		}
	}

	if((int)ans.size())
	{
		return ans;
	}
	cout<<"Increase Range\n";
	exit(0);

}
int main()
{
	// generating all filestreams to give output to files.
	fstream file,file2,file3;
	file.open("output.txt", ios::out | ios::trunc);
  	file.close();
	file.open ("output.txt", ios::in | ios::out | ios::ate);
	file2.open("output2.txt", ios::out | ios::trunc);
  	file2.close();
	file2.open ("output2.txt", ios::in | ios::out | ios::ate);
	file3.open("output3.txt", ios::out | ios::trunc);
  	file3.close();
	file3.open ("output3.txt", ios::in | ios::out | ios::ate);
	

	// taking all inputs and generating graphs.
	for(int i=0; i<50; i++)
	{
		cin>>cs[i]>>cs_wt[i];
	}
	cin>>m;
	for(int i=0; i<m; i++)
	{
		int u,v,w;
		cin>>u>>v>>w;
		g[u].pb({v,w});
		g1[u].pb({v,w});
		mp[{u,v}]=w;
	}

	cin>>src>>dest;

	int unavaible_nodes;
	cin>>unavaible_nodes;
	int b[unavaible_nodes];
	for(int i=0; i<unavaible_nodes; i++)
	{
		cin>>b[i];
		g[b[i]].clear();
	}

	cin>>currcharge>>fullcharge;
	currcharge=fullcharge*currcharge;
	currcharge/=100;
	
	// running dijkstra for each charging stations and storing the distances in 2D array dist.
	for(int i=0; i<50; i++)
	{
		dij(cs[i],cs[i]);
		for(int j=0; j<100005; j++)
		{
			dist[i][j]=dis[j];
		}
	}

	dij(src,src);
	for(int i=0; i<100005; i++)
	{
		dist[50][i]=dis[i];
	}
	dij(dest,dest);
	for(int i=0; i<100005; i++)
	{
		dist[51][i]=dis[i];
	}

	file<<src<<" "<<dest<<endl;
	
	int totaldist=dist[50][dest];

	int extradist=max(5000,(int)0.5*totaldist);

	totaldist+=extradist;

	for(int i=0; i<50; i++)
	{
		if(dist[i][src]+dist[i][dest]<=totaldist)
		{
			if(cs[i]!=src)
				used_cs.pb(i);
			else 
				currcharge=fullcharge;
		}
	}

	int f=0;
	for(int i=0; i<(int)used_cs.size(); i++)
	{
		if(dist[i][src]<=currcharge)
			f=1;
	}

	// Checking if vehicle have enough range and charge or not.
	if(f==0)
	{
		cout<<"Increase SOC, If SOC is 100 then try increasing range.\n";
		exit(0);
	}

	vector <int> v=mindist();
	// printing of the output file begins and calculationg total travel time and total distance or the journey.
	// this one is minimum distance.
	int tempsrc=src;
	double traveltym=0.0;
	double traveldist=0.0;
	for(int i=0; i<(int)v.size(); i++)
	{
		vector <int> v1=dij(tempsrc,cs[v[i]]);

		// calculation for total distance.
		traveldist+=dis[cs[v[i]]];
		// calculation for total time.
		traveltym+=cs_wt[v[i]]/40000.0;

		if(v1[0]==src)
		{
			file<<src<<" ";
		}
		else 
		{
			file<<-v1[0]<<" ";
		}
		for(int j=1; j<(int)v1.size()-1; j++)
		{
			file<<v1[j]<<" ";
		}
		tempsrc=cs[v[i]];
	}
	
	vector <int> v1=dij(tempsrc,dest);
	// calculation for total distance.
	traveldist+=dis[dest];
	// calculation for total time.
	traveltym+=(traveldist/40000.0+(traveldist - currcharge)*2.0/fullcharge);

	file3<<traveltym<<" ";
	file3<<traveldist<<endl;

	if(v1[0]==src)
	{
		file<<src<<" ";
	}
	else 
	{
		file<<-v1[0]<<" ";
	}
	for(int j=1; j<(int)v1.size()-1; j++)
	{
		file<<v1[j]<<" ";
	}
	file<<dest<<endl;

	for(int i=0; i<(int)v.size()-1; i++)
	{
		file2<<100*dist[v[i]][cs[v[i+1]]]/(double)fullcharge<<" ";
	}
	if((int)v.size())
	{
		file2<<100*dist[v.back()][dest]/(double)fullcharge<<endl;
	}
	v.clear();
	v=mintime();
	// this one is minimum time.
	tempsrc=src;
	traveldist=0.0;
	traveltym=0.0;
	for(int i=0; i<(int)v.size(); i++)
	{
		vector <int> v1=dij(tempsrc,cs[v[i]]);

		//calculation of total distance.
		traveldist+=dis[cs[v[i]]];
		// calculation for total time.
		traveltym+=cs_wt[v[i]]/40000.0;

		if(v1[0]==src)
		{
			file<<src<<" ";
		}
		else 
		{
			file<<-v1[0]<<" ";
		}
		for(int j=1; j<(int)v1.size()-1; j++)
		{
			file<<v1[j]<<" ";
		}
		tempsrc=cs[v[i]];
	}
	v1.clear();
	v1=dij(tempsrc,dest);
	//calculation of total distance.
	traveldist+=dis[dest];
	// calculation for total time.
	traveltym+=(traveldist/40000.0+(traveldist - currcharge)*2.0/fullcharge);

	file3<<traveltym<<" ";
	file3<<traveldist<<endl;

	if(v1[0]==src)
	{
		file<<src<<" ";
	}
	else 
	{
		file<<-v1[0]<<" ";
	}
	for(int j=1; j<(int)v1.size()-1; j++)
	{
		file<<v1[j]<<" ";
	}
	file<<dest<<endl;

	for(int i=0; i<(int)v.size()-1; i++)
	{
		file2<<100*dist[v[i]][cs[v[i+1]]]/(double)fullcharge<<" ";
	}
	if((int)v.size())
	{
		file2<<100*dist[v.back()][dest]/(double)fullcharge<<endl;
	}

	file.close();
    return 0;
}