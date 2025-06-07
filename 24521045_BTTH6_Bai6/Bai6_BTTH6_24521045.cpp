#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
class cKhachHang{
	protected:
		string Name;
		ll number;
		double money;
	public:
		virtual void doc(){
			cin.ignore();
			cout<<"Nhap ten: "<<flush;
			getline(cin,Name);
			
			cout<<"Number_Product: "<<flush;
			cin>>number;
			
			cout<<"Price: "<<flush;
			cin>>money;
		}
		virtual double bill()=0;
		
		virtual void xuat()=0;
};
class cA : public cKhachHang{
	private:
	protected:
	public:
		double bill() override{
			double sum=number*money;
			return (double)sum+sum*0.1;
		}
		void xuat() override{
			cout<<Name<<endl;
			cout<<bill()<<endl;
		}
};
class cB : public cKhachHang{
	private:
		ll year_friend;
	public:
		void doc() override{
			cKhachHang::doc();
			cout<<"Year_friend: "<<flush;
			cin>>year_friend;
		}
		double bill() override{
			double sum=(number*money)*(1-max(year_friend*0.05,0.5));
			return sum+(double)sum*0.1;
		}
		void xuat() override{
			cout<<Name<<endl;
			cout<<bill()<<endl;
		}
};
class cC : public cKhachHang{
	public:
		double bill() override{
			double sum=number*money*0.5;
			return (double)sum+sum*0.1;
		}
		void xuat() override{
			cout<<Name<<endl;
			cout<<bill()<<endl;
		}
};
class Manager{
	private:
		ll x;
		ll y;
		ll z;
		vector<cKhachHang*> Admin;
	public:
		void In(){
			cin>>x>>y>>z;
			for(int i=0;i<x+y+z;i++){
				cKhachHang* temp;
				temp=nullptr;
				if(i<x) temp=new cA();
					else if(i<x+y) temp=new cB();
						else temp=new cC();
				temp->doc();
				Admin.push_back(temp);
			}
		}
		double Total(){
			double sum=0;
			for(int i=0;i<x+y+z;i++){
				sum+=Admin[i]->bill();
			}
			return sum;
		}
		void out(){
			for(int i=0;i<x+y+z;i++){
				Admin[i]->xuat();
			}
			cout<<Total()<<endl;
		}
};
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	Manager A;
	A.In();
	A.out();
	return 0;
}
