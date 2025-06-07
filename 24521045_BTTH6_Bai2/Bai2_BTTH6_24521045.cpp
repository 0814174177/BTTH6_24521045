#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
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
		bool operator<=(const cTime b){
			if(year>b.year) return true;
				else if(month>b.month) return true;
					else if(day>=b.day) return true;
			return false;
		}
};
class cVAKALAND{
	private:
		string ID;
		cTime t;
	protected:
		double money;
		string type;
		double S;
	public:
		cTime getTime(){ return this->t;}
		virtual void doc(){
			cout<<"In ID land: "<<flush;
			cin>>ID;
			cout<<"In Time to buy land: "<<flush;
			cin>>t;
			cout<<"IN_money: "<<flush;
			cin>>money;
			cout<<"In_Area: "<<flush;
			cin>>S;
		}
		virtual void xuat(){
			cout<<ID<<endl;
			cout<<t<<endl;
		}
		virtual double Total()=0;
};
class cLand : public cVAKALAND{
	private:
	protected:
	public:
		void doc() override{
			cVAKALAND::doc();
			cout<<"IN_type(A/B/C): "<<flush;
			cin>>type;
		}
		double Total() override{
			if(type=="B" || type=="C") return (double)S*money;
			if(type=="A") return (double)S*money*1.5;
		}
		void xuat() override{
			cout<<"This is Land"<<endl;
			cVAKALAND::xuat();
			cout<<type<<" "<<Total()<<endl;
		}
};
class cCity : public cVAKALAND{
	private:
		string street;
	protected:
	public:
		void doc() override{
			cVAKALAND::doc();
			cout<<"IN_type(high/normal): "<<flush;
			cin>>type;
			cin.ignore();
			cout<<"IN_Street: "<<flush;
			getline(cin,street);
		}
		inline double Total() override{
			if(type=="high") return (double)S*money;
				else return (double)S*money*0.9;
		}
		void xuat() override{
			cout<<"This is Land_City"<<endl;
			cout<<type<<endl;
			cout<<street<<endl;
			cout<<Total();
		}
};
class cApartment : public cVAKALAND{
	private:
		string ID_home;
		ll floor;
	protected:
	public:
		void doc() override{
			cVAKALAND::doc();
			cout<<"IN_ID_home: "<<flush;
			cin>>ID_home;
			cout<<"IN_floor: "<<flush;
			cin>>floor;
		}
		inline double Total() override{
			if(floor==1) return (double)S*money*2.0;
				else if(floor>15) return (double)S*money*1.2;
					else return (double)S*money;
		}
		void xuat() override{
			cout<<"this is Apartment"<<endl;
			cout<<ID_home<<" "<<floor<<Total()<<endl;
		}
};
struct bg{
	cVAKALAND *mem;
	ll x;
};
class Manager{
	private:
		ll dem1,dem2,dem3;
		ll Member;
		vector <bg> Admin;
	public:
		void setDem3(ll dem3){ this->dem3=dem3; }
		void Menu();
		void In();
		void Type_Land();
		double Average_Apartment();
		void Max_Total_City();
		void Check_Time();
};
void Manager::Menu(){
    int opt;
    do {
        cout << "========== MENU =========="<<endl;
        cout << "1. Nhap danh sach"<<endl;
        cout << "2. Thong ke loai dat"<<endl;
        cout << "3. Tinh trung binh tong tien cua can ho"<<endl;
        cout << "4. Tim dat city co tong tien cao nhat"<<endl;
        cout << "5. Xuat lo dat mua trong thang 12/2024"<<endl;
        cout << "0. Thoat"<<endl;
        cout << "Nhap lua chon: "<<endl;
        cin >> opt;
        switch(opt) {
            case 1: In(); break;
            case 2: Type_Land(); break;
            case 3: cout << "Trung binh can ho: " << Average_Apartment() << endl; break;
            case 4: Max_Total_City(); break;
            case 5: Check_Time(); break;
            case 0: cout << "Tam biet!\n"; break;
            default: cout << "Lua chon khong hop le!\n";
        }
    } while(opt != 0);
}
void Manager::In(){
	cin>>Member;
	for(int i=0;i<Member;i++){
		cout<<"Land/City/Apartment(1/2/3)"<<endl;
		int x;
		cin>>x;
        bg temp;
		temp.mem=nullptr;
        if (x==1) temp.mem=new cLand();
        else if(x==2) temp.mem=new cCity();
        else if (x==3) temp.mem=new cApartment();
        else{
            cout<<"Invalid choice. Skipped.\n";
            continue;
        }
        temp.x=x;
        temp.mem->doc();
        Admin.push_back(temp);
	}	
}
void Manager::Type_Land(){
	ll dem1=0;dem2=0;dem3=0;
	for(int i=0;i<Member;i++){
		if(Admin[i].x==1) dem1++;
			else if(Admin[i].x==2) dem2++;
				else if(Admin[i].x==3) dem3++;
	}
	cout<<"Normal Land: "<<dem1<<endl;
	cout<<"City: "<<dem2<<endl;
	cout<<"Apartment: "<<dem3<<endl;
}
double Manager::Average_Apartment(){
	ll dem3=0;
	double sum=0;
	for(int i=0;i<Member;i++){
		if(Admin[i].x==3){
			sum+=Admin[i].mem->Total();
			dem3++;
		}
	}
	return (double)sum/dem3;
}
void Manager::Max_Total_City(){
	ll sum=0;
	ll check=0;
	for(int i=0;i<Member;i++){
		if(Admin[i].x==2 && sum<=Admin[i].mem->Total()){
			sum=Admin[i].mem->Total();
			check=i;
		}
	}
	Admin[check].mem->xuat();
} 
void Manager::Check_Time(){
	cTime first(1,12,2024),second(31,12,2024);
	for(int i=0;i<Member;i++){
		if(Admin[i].mem->getTime()>=first && Admin[i].mem->getTime()<=second) Admin[i].mem->xuat();
	}
}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	Manager A;
	A.Menu();
	return 0;
}
