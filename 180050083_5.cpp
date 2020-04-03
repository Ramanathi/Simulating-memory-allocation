	
#include<iostream>
#include<vector>
#include<map>
#include<vector>
#include<iterator>
#include<utility>
using namespace std;
typedef long long int ll;
typedef map<int,pair<int, int > > :: iterator mapit;
typedef map<int,vector<int> > :: iterator vmapit;

struct req{
 int num;
 char c;
 int pid;
 int m;
req(int n,char a,int b,int d){num=n;c=a;pid=b;m=d;}
};

typedef vector<req>::iterator vecit;

vector<req> pend;
map<int,pair<int, int > > all;


int check(int M,int size,mapit beg,mapit end)
{
	int pos=-1,start=beg->first,i;
	bool got = false;
	for(i=0;i<M;i++)
	{
		if(i<start)
		{
			i = start;
			if(start >= size) {pos = 0;got = true;break;}
		}
		else
		{
			bool tf = true;
			for(mapit it = beg;it != end;it++)
			{
				mapit temp = it;temp++;
                pair<int, int> p= it->second;
				if(temp == end)
				{
                    i = (it->first)+(p.second); tf = false;
				}
				else
				{
					int s = (it->first)+(p.second);
					int len = (temp->first)-s;
					if(len >= size) {pos = s;got=true;break;}
				}
			}
			break;
		}
	}
	if(got) return pos;
    if(M-i >= size) return i;
    else return -1;
}

void printinfo()
{
	for(mapit it = all.begin();it!=all.end();it++)
	{
		cout<<it->second.first<<" "<<it->first<<" "<<it->first + it->second.second<<endl;
	}
}

void go_on(int ans[],int M)
{
	if(pend.size()!=0)
    for(vecit it=pend.begin();it!=pend.end();)
   {
   	int count=it->num,pid = it->pid,size = it->m;
   	if(all.size() == 0)
   	{
       all[0]=make_pair(pid,size);ans[count] = 0;
       it = pend.erase(it);
   	}
   	else 
   	{
   		int pos = check(M,size,all.begin(),all.end());
				if(pos != -1) 
				{
                    all[pos]=make_pair(pid,size);
					ans[count] = pos;
					it = pend.erase(it);
				}
				else it++;
   	}
   	
   }
}

void go_on1(int size,int at,int ans[])
{
	if(pend.size() != 0)
	{
		for(vecit it=pend.begin();it!=pend.end();)
		{
			int count=it->num,pid = it->pid,mem = it->m;
			if(size >= mem)
			{
				all[at] = make_pair(pid,mem);
				ans[count] = at;
				it = pend.erase(it);
				size = size - mem; at = at + mem;
			}
			else it++;
		}
	}
}

int main()
{
	int n,M;
	cin>>n>>M;
	int ans[1000000],count=0;
	char c; int pid,size,add;
	while(true)
	{
		cin>>c;
		if(c != 'H')
		{
			if(c == 'A')
			{
				cin>>pid>>size;
				if(size > M) ans[count]= -1;
                else if(all.size() == 0) 
                {
                   all[0]=make_pair(pid,size);ans[count] = 0;
                }
				else
				{
				int pos = check(/*a,*/M,size,all.begin(),all.end());
				if(pos == -1) pend.push_back(req(count,'A',pid,size));
				else
				{
                    all[pos]=make_pair(pid,size);
					ans[count] = pos;
				}
			    }
			}
			else if(c == 'D')
			{
               cin>>pid>>add;
               if(all.size() == 0) {ans[count] = 1;}
               else
               {
               	mapit t = all.find(add);
               	if(t!=all.end())
               	{
                   if((t->second).first != pid) ans[count] = 1;
                   else
                   {
                   	   ans[count] = 0;
                   	   mapit it1 = t;mapit it2 = t;it2++;
                   	   if(t == all.begin())
                   	   {
                   	   	 if(all.size() != 1) {int ulfa = it2->first;all.erase(t);go_on1(ulfa,0,ans);}
                   	   	 else {all.erase(t);go_on1(M,0,ans);}
                   	   }
                   	   else if(it2 == all.end())
                   	   {
                   	   	it1--; int ulfa = it1->first+it1->second.second;all.erase(t);go_on1(M-ulfa,ulfa,ans);
                   	   }
                   	   else
                   	   {
                   	   	it1--;int ulfa2 = it1->first+it1->second.second;int ulfa1 = it2->first-ulfa2;all.erase(t);go_on1(ulfa1,ulfa2,ans);
                   	   }
                   }
               	}
               	else ans[count] = 1;
               }
			}
			else if(c == 'T')
			{
               cin>>pid;
               if(all.size() == 0) {ans[count] = 1;}
               else
               {    
               	   bool got = false;
                   for(mapit it=all.begin();it!=all.end();) 
                   	{
                   		if(it->second.first == pid)
                   		{
                   		   got = true;
                           
                           it = all.erase(it); 
                           
                   		}
                   		else it++;
                   	}
                   
                   	if(pend.size() != 0)
                   	{
                   	for(vecit it = pend.begin();it!=pend.end();)
                   	{
                   		if(it->pid == pid)
                   		{
                   			
                   			ans[it->num] = -1;
                   			it = pend.erase(it); 
                   		}
                   		else it++;
                   	}
                   }
                   go_on(ans,M);
                   	if(got) ans[count] = 0;
                   	else ans[count] = 1;
                   	
               }
			}
		}
		else
		{
			for(int i=0;i<pend.size();i++)
			{
				ans[pend[i].num] = -1;
			}
			for(int i=0;i<count;i++) cout<<ans[i]<<endl;
			break;
		}
		count++;
	}
	cout<<endl;
}
