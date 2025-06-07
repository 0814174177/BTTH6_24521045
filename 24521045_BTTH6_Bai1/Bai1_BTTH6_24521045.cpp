#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
class cTime{
	private:
		ll day;
		ll month;
		ll year;
		ll a[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	public:
		cTime(ll day=0, ll month=0, ll year=0){
			this->day=day;	
			this->month=month;
			this->year=year;
		}
		bool check_LeapYear(){
			if((year%100!=0 && year%4==0) || (year%400==0)) return true;
			return false;
		}
		bool check_Time(){
			if(check_LeapYear()) a[2]=29;
			if(month<1 || month>12) return false;
			if(day<1 || day>a[month]) return false;
			if(year<0) return false;
			return true;
		}
		friend istream& operator>>(istream &in, cTime &a){
			do{
				in>>a.day>>a.month>>a.year;
				if(a.check_Time()) break;
					else cout<<"Wrong form in Birth"<<endl;
			}
			while (1);
			return in;
		}
		friend ostream& operator<<(ostream &out, cTime &a){
			out<<a.day<<" "<<a.month<<" "<<a.year;
			return out;
		}
		bool operator>=(const cTime b){
			if(year<b.year) return true;
				else if(month<b.month) return true;
					else if(day<b.day) return true;
						else if(day==b.day) return true;
			return false;
		}
};
class cNhanvien{
	private:
		string Name;
		cTime Birth;
	public:
		cTime getBirth(){
			return this->Birth;
		}
		virtual void doc(){
			cout<<"IN_name: "<<flush;
			cin.ignore();
			getline(cin,Name);
			cout<<"IN_Birth: "<<flush;
			cin>>Birth;
		}
		virtual void xuat(){
			cout<<Name<<" "<<Birth<<" ";
		}
		virtual double luong()=0;
};
class cOffical : public cNhanvien{
	private:
		double luongcoban;
		ll sosanpham;
	protected:
	public:
		void doc() override{
			cNhanvien::doc();
			cout<<"In_base_salary: "<<flush;
			cin>>luongcoban;
			cout<<"In_number_of_product: "<<flush;
			cin>>sosanpham;
		}
		double luong() override{
			return (double)(luongcoban+sosanpham*5.000);
		}
		void xuat() override{
			cNhanvien::xuat();
			cout<<luong()<<endl;
		}
};
class cProduct : public cNhanvien{
	private:
		ll songaylamviec;
	protected:
	public:
		void doc() override{
			cNhanvien::doc();
			cout<<"In_number_of_working: "<<flush;
			cin>>songaylamviec;
		}
		double luong() override{
			return (double)songaylamviec*100.000;
		}
		void xuat() override{
			cNhanvien::xuat();
			cout<<luong()<<endl;
		}
};
struct bg{
	cNhanvien *mem;
	ll x;
};
class Manager{
	private:
		ll Member;
		vector <bg> Admin;
	public:
		void Menu(){
			ll x;
			do{
				cout << "1. Nhap danh sach nhan vien\n";
	        	cout << "2. Tong luong\n";
	        	cout << "3. Tim nguoi co luong thap nhat\n";
	        	cout << "4. Nhan vien lon tuoi nhat\n";
	        	cout << "0. Thoat\n";
	        	cout << "Lua chon: "<<flush;
				cin>>x;
				switch(x){
					case 1: in_program();
					case 2: Total();
					case 3: FindMin();
					case 4: HighBirth();
				}
			}
			while(x!=0);
		}
		void in_program();
		double Total();
		void FindMin();
		void HighBirth();
};
void Manager :: in_program(){
	cout<<"The_number_of_member: "<<flush;
	cin>>Member;
	for(int i=0;i<Member;i++){
		int x;
		bg temp;
		temp.mem = nullptr;
		cout<<"Offical/Product(1/2)"<<endl;
		cin>>x;
		if(x==1){
			temp.mem=new cOffical();
			temp.x=1;
		}
		if(x==2){
			temp.mem=new cProduct();
			temp.x=2;
		}
		temp.mem->doc();
		Admin.push_back(temp);
	}
}
double Manager :: Total(){
	double sum=0;
	for(int i=0;i<Member;i++){
		sum+=Admin[i].mem->luong();
	}
	return sum;
}
void Manager :: FindMin(){
	ll sum=1e18;
	ll check=0;
	for(int i=0;i<Member;i++){
		if(sum>Admin[i].mem->luong()){
			sum=Admin[i].mem->luong();
			check=i;
		}
	}
	Admin[check].mem->xuat();
}
void Manager :: HighBirth(){
	cTime sum(0,0,1e18);
	ll check=0;
	for(int i=0;i<Member;i++){
		if(sum>=Admin[i].mem->getBirth()){
			sum=Admin[i].mem->getBirth();
			check=i;
		}
	}
	Admin[check].mem->xuat();
}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	Manager A;
	A.Menu();
	return 0;
}
