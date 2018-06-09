#include<iostream>
#include<fstream>
#include<algorithm>
#include<set>
#include<stack>
#include<queue>
#include<map>

using namespace std;
string word[5757];
int check1[5757]={0};
int check2[5757]={0};
map<int,set<int> > A1; // Ánh xạ từ đỉnh i sang tập đỉnh kề với nó
map<int,set<int> > A2;
map<int,set<int> > B;
map<int,string> W;  // Ánh xạ tư 1 đỉnh sang 1 từ
map<string,int> X;  // Ánh xạ từ 1 từ sang 1 đỉnh
map<int,int> p; // Đỉnh thăm trước khi thăm x
map<int,string> pv;  // Ánh xạ từ postvisit sang 1 từ
set<int> timepv;  // Danh sách time của postvisit
stack <int> S;
map<int,set<int> > LTM; // Ánh xạ từ 1 số nguyên sang tập các thành phần liên thông mạnh
map<int,int> L; // Ánh xạ từ 1 đỉnh sang nhóm thành phần liên thông mạnh
int time=0;
int countLTM=0;
// Lấy dữ liệu từ file
void readWord(char *fileName)
{
    int i=0;
    ifstream f (fileName);
    while(!f.eof())
    {
        f >> word[i];
        X[word[i]]=i;
        W[i]=word[i];
        i++;
    }
}
//BÀI 1------------------------------------------------------
// Lập danh sách các cạnh kề
void adjacentBT1()
{
	for(int i=0;i<5757;i++)
	{
		for(int j=0;j<5757;j++)
		{
			if(i != j)
			{
				int count=5;
				for(int k=0;k<5;k++)
				{
					if(word[i][k] != word[j][k])
						count--;
                    if(count <= 3)
                        break;
				}
				if(count >=4 )
				{
					A1[i].insert(j);
				}
			}
		}
	}
}
// Thăm các đỉnh kề
void DFSVisit(int u)
{
	check1[u]=1;
	for(set <int> :: iterator q= A1[u].begin();q!=A1[u].end();q++)
	{
        if(check1[*q] == 0)
        {
            DFSVisit(*q);
        }
	}
}
// Đếm số thành phần liên thông
int CountConnect()
{
	int count=0;
	for(int u=0;u<5757;u++)
	{
		if(check1[u]==0)
		{
			count++;
			DFSVisit(u);
		}
	}
	return count;
}
// Tìm đường đi ngắn nhất trên đồ thi vô hướng bằng BFS
void findPath(int s,int t)
{
    queue <int> Q;
    int v;
    Q.push(s);
    check1[s]=0;
    while(!Q.empty())
    {
        v = Q.front(); Q.pop();
        for(set <int> :: iterator q = A1[v].begin();q!=A1[v].end();q++)
        {
            if(check1[*q]==1)
            {
                p[*q]=v;
                check1[*q]=0;
                Q.push(*q);
            }
        }
    }
    if(check1[t]==1) cout << "    Khong co duong di";
    else
    {
        int x=t;
        while(x!=s)
        {
            S.push(x);
            x=p[x];
        }
        cout << "    Duong di tu "<<W[s]<< "->" << W[t]<<":"<<endl;
        cout << "       "<<W[s];
        while(!S.empty())
        {
            x=S.top(); S.pop();
            cout<< "->" << W[x];
        }
        cout<<endl<<endl<<endl;
    }
}

// BÀI 2 --------------------------------------------------------------------------------
// Lập danh sách các cung
void adjacentBT2()
{
    for(int i=0;i<5757;i++)
	{
		for(int j=0;j<5757;j++)
		{
			if(i != j)
			{
			    string tmp=word[j];
			    int count =0;
				for(int m=1;m<5;m++)
				{
				    for(int n=0;n<5;n++)
                    {
                        if(word[i][m] == tmp[n])
                        {
                            count ++;
                            tmp[n]=',';
                            break;
                        }
                    }
                    if(m==1 && count<1)
                    	break;
                    if(m==2 && count<2)
                    	break;
                    if(m==3 && count<3)
                    	break;
                    if(m==4 && count<4)
                    	break;
				}
				if(count == 4)
                    A2[i].insert(j);
			}
		}
	}
}
// Đảo ngược các cung
void DaoNguocCung()
{
    for(int i=0;i<5757;i++)
    {
        for(set<int> :: iterator q=A2[i].begin();q!=A2[i].end();q++)
        {
            B[*q].insert(i);
        }
    }
}
// Thăm các đỉnh kề của danh sách đảo ngược cung
void DFSVisitBT2(int u)
{
    S.push(u);
    check2[u]=1;
    ++time;
	for(set <int> :: iterator q= B[u].begin();q!=B[u].end();q++)
	{
        if(check2[*q] == 0)
        {
            DFSVisitBT2(*q);
        }
	}
    ++time;
    pv[time]=W[S.top()];
    timepv.insert(time);
    S.pop();
}
// Tạo postvisit
void getPostVisit()
{
    for(int i=0;i<5757;i++)
    {
        if(check2[i]==0)
        {
            DFSVisitBT2(i);
        }
    }
}
// Thăm các đỉnh kề theo chiều giảm của postvisit
void DFSVisitBack(int u)
{
    check2[u]=0;
    LTM[countLTM].insert(u);
    L[u]=countLTM;
	for(set <int> :: iterator q= A2[u].begin();q!=A2[u].end();q++)
	{
        if(check2[*q] == 1)
        {
            DFSVisitBack(*q);
        }
	}
}
// Đếm số thành phần liên thông mạnh
int superConnect()
{
	for(set <int> :: reverse_iterator q=timepv.rbegin();q!=timepv.rend();q++) // theo chiều giảm dần của Post
	{
		if(check2[X[pv[*q]]]==1)
		{
			DFSVisitBack(X[pv[*q]]);
			countLTM++;
		}
	}
	return countLTM;
}
// Tìm đường đi ngắn nhất trên đồ thị có hướng bằng BFS
void findPathBT2(int s,int t)
{
    queue <int> Q;
    int v;
    Q.push(s);
    check2[s]=1;
    while(!Q.empty())
    {
        v = Q.front(); Q.pop();
        for(set <int> :: iterator q = A2[v].begin();q!=A2[v].end();q++)
        {
            if(check2[*q]==0)
            {
                p[*q]=v;
                check2[*q]=1;
                Q.push(*q);
            }
        }
    }
    if(check2[t]==0) cout << "    Khong co duong di";
    else
    {
        int x=t;
        while(x!=s)
        {
            S.push(x);
            x=p[x];
        }
        cout << "    Duong di tu "<<W[s]<< "->" << W[t]<<":"<<endl;
        cout << "       "<<W[s];
        while(!S.empty())
        {
            x=S.top(); S.pop();
            cout<< "->" << W[x];
        }
        cout<<endl<<endl<<endl;
    }
}
int main()
{
    int test;
	readWord("sgb-words.txt");
	do
    {
        cout<<endl;
        cout<< "--------------------------------------------------TOAN ROI RAC--------------------------------------------------";
        cout<<endl;
        cout<<"1. Nhap 1 de test bai 1" <<endl;
        cout<<"2. Nhap 2 de test bai 2" <<endl;
        cout<<"0. Nhap 0 de ket thuc" <<endl;
        cin>> test;
        system("cls");
        switch(test)
        {
        case 1:
            {
                for(int i=0;i<5757;i++)
                {
                    check1[i]=0;
                }
                int count,u1,v1;
                string u,v;
                cout << "\t\t--------------------BAI 1--------------------"<<endl;
                adjacentBT1();
                count = CountConnect();
                cout << "1.1 So thanh phan lien thong la: " << count<<endl;
                do
                {
                    cout << "1.2 Tim duong di ngan nhat tu u -> v"<<endl;
                    cout<<"    Nhap tu u:";
                    cin >> u;
                    u1=X[u];
                    if(u != word[0] && u1 == 0)
                    {
                        cout << "    Khong co tu \"" << u << "\""<<" trong file."<<endl;
                        cout << "    Xin hay nhap lai!!!"<<endl;
                        continue;
                    }
                    cout<<"    Nhap tu v:";
                    cin >> v;
                    v1=X[v];
                    if(v != word[0] && v1 == 0)
                    {
                        cout << "    Khong co tu \"" << v << "\""<<" trong file."<<endl;
                        cout << "    Xin hay nhap lai!!!"<<endl;
                        continue;
                    }
                    findPath(u1,v1);
                }while((u != word[0] && u1 == 0) || v != word[0] && v1 == 0 );
            }
            break;
        case 2:
            {
                for(int i=0;i<5757;i++)
                {
                    check2[i]=0;
                }
                countLTM=0;
                int count =0,Lu,u1,v1;
                string u,v;
                cout << "\t\t--------------------BAI 2--------------------"<<endl;
                adjacentBT2();
                DaoNguocCung();
                getPostVisit();
                count=superConnect();
                cout << "2.1 So thanh phan lien thong manh: " << count<<endl;
                do
                {
                    cout<<"2.2 Xuat cac phan tu cung thanh phan lien thong manh"<<endl;
                    cout << "    Nhap tu u :";
                    cin >> u;
                    Lu=L[X[u]]; // Lu1 sẽ là nhóm thành phần liên thông mạnh chứa u
                    u1=X[u];
                    if(u != word[0] && u1 == 0)
                {
                    cout << "    Khong co tu \"" << u << "\""<<" trong file."<<endl;
                    cout << "    Xin hay nhap lai!!!"<<endl;
                    continue;
                }
                cout << "    Thanh phan cung voi tu "<< u << " la : ";
                for(set<int> :: iterator q=LTM[Lu].begin();q!=LTM[Lu].end();q++)
                {
                    cout<<"-"<< W[*q];
                }
                }while(u != word[0] && u1 == 0);
                do
                {
                    cout<<endl;
                    cout<<"2.3 Tim duong di ngan nhat tu u -> v"<<endl;
                    cout<<"    Nhap tu u:";
                    cin >> u;
                    u1=X[u];
                    if(u != word[0] && u1 == 0)
                    {
                        cout << "    Khong co tu \"" << u << "\""<<" trong file."<<endl;
                        cout << "    Xin hay nhap lai!!!"<<endl;
                        continue;
                    }
                    cout<<"    Nhap tu v:";
                    cin >> v;
                    v1=X[v];
                    if(v != word[0] && v1 == 0)
                    {
                        cout << "    Khong co tu \"" << v << "\""<<" trong file."<<endl;
                        cout << "    Xin hay nhap lai!!!"<<endl;
                        continue;
                    }
                    findPathBT2(u1,v1);
                }while((u != word[0] && u1 == 0) || v != word[0] && v1 == 0 );
            }
            break;
        }
    }while(test != 0 );
    return 0;
}
