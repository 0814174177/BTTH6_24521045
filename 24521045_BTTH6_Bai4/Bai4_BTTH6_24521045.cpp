#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
class cNhanVien{
	private:
		string ID;
		string Name;
		ll Old;
		string Number_Phone;
		string Email;
	protected:
		double basic_salary;
	public:
		virtual void doc(){
			cin.ignore();
			cout<<"In ID: "<<flush;
			getline(cin,ID);
			
			cout<<"In Name: "<<flush;
			getline(cin,Name);
			
			cout<<"In Old: "<<flush;
			cin>>Old;
			cin.ignore();
			
			cout<<"In Number_Phone: "<<flush;
			cin>>Number_Phone;
			
			cout<<"In Email: "<<flush;
			cin>>Email;
		}
		
		virtual double Salary()=0;
		
		virtual void xuat(){
			cout<<Name<<" "<<ID<<" "<<Old<<endl;
			cout<<"Phone: "<<Number_Phone<<" Email: "<<Email<<endl;
		}
};
class cIT : public cNhanVien{
	private:
		ll overtime;
	public:
		void doc() override{
			cNhanVien::doc();
			cout<<"In Basic_Salary: "<<flush;
			cin>>basic_salary;
			cout<<"In Over_time: "<<flush;
			cin>>overtime;
		}
		double Salary() override{
			return (double)basic_salary+overtime*200.000;
		}
		void xuat() override{
			cout<<"I'm IT"<<endl;
			cNhanVien::xuat();
		}
};
class cVerify : public cNhanVien{
	private:
		ll Fix_bug;
	public:
		void doc() override{
			cNhanVien::doc();
			cout<<"In Basic_Salary: "<<flush;
			cin>>basic_salary;
			cout<<"In The_number_of_Fix_Bug: "<<flush;
			cin>>Fix_bug;
		}
		double Salary() override{
			return (double)basic_salary+Fix_bug*50.000;
		}
		void xuat() override{
			cout<<"I'm Verify"<<endl;
			cNhanVien::xuat();
		}
}; 
struct bg{
	cNhanVien *mem;
	ll x;
};
class Manager{
	private:
		ll Member;
		vector <bg> Admin;
	public:
		void Menu();
		void In();
		void Out();
		double Average_Salary();
		void printEmployeesBelowAverageSalary();
		void Max_Salary();
		void Min_Salary();
		void Max_Salary_IT();
		void Min_Salary_Verify();
};
void Manager::Menu() { 
    int choice;
    do {
    	cout<<endl;
        cout << "========== MENU =========="<<endl;
        cout << "1. Nhap danh sach nhan vien"<<endl;
        cout << "2. Xuat danh sach nhan vien"<<endl;
        cout << "3. Tinh va xuat muc luong trung binh"<<endl;
        cout << "4. Xuat nhan vien co luong thap hon trung binh"<<endl;
        cout << "5. Xuat nhan vien co luong cao nhat"<<endl;
        cout << "6. Xuat nhan vien co luong thap nhat"<<endl;
        cout << "7. Xuat nhan vien IT co luong cao nhat"<<endl;
        cout << "8. Xuat nhan vien Verify co luong thap nhat"<<endl;
        cout << "0. Thoat"<<endl;
        cout << "=========================="<<endl;
        cout << "Nhap lua chon cua ban: "<<flush;
        cin >> choice;

        switch (choice) {
            case 1:
                In();
                break;
            case 2:
                Out();
                break;
            case 3:
                cout << "Luong trung binh cua nhan vien: " << Average_Salary() << endl;
                break;
            case 4:
                printEmployeesBelowAverageSalary();
                break;
            case 5:
                Max_Salary();
                break;
            case 6:
                Min_Salary();
                break;
            case 7:
                Max_Salary_IT();
                break;
            case 8:
                Min_Salary_Verify();
                break;
            case 0:
                cout << "Thoat chuong trinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le. Vui long chon lai.\n";
        }
    } while (choice != 0);
}
void Manager::In(){
	cout<<"Nhap so luong nhan vien: "<<flush;
	cin>>Member;
	for(int i=0;i<Member;i++){
		cout<<"1.IT"<<endl;
		cout<<"2.Verify"<<endl;
		ll choice;
		cin>>choice;
		bg temp;
		temp.mem=nullptr;
		if(choice==1){
			temp.mem=new cIT();
			temp.x=choice;
		}
		if(choice==2){
			temp.mem=new cVerify();
			temp.x=choice;
		}
		temp.mem->doc();
		Admin.push_back(temp);	
	}
}
void Manager::Out(){
	for(int i=0;i<Member;i++){
		Admin[i].mem->xuat();
	}
}
double Manager::Average_Salary(){
	double average=0;
	for(int i=0;i<Member;i++){
		average+=Admin[i].mem->Salary();
	}
	return average/=Member;
}
void Manager::printEmployeesBelowAverageSalary(){
	double S=Average_Salary();
	for(int i=0;i<Member;i++){
		if(Admin[i].mem->Salary()<S) Admin[i].mem->xuat();
	}
}
void Manager::Max_Salary(){
	double compare=0;
	ll check=0;
	for(int i=0;i<Member;i++){
		if(compare<Admin[i].mem->Salary()){
			compare=Admin[i].mem->Salary();
			check=i;
		}
	}
	Admin[check].mem->xuat();
}
void Manager::Min_Salary(){
	double compare=1e18;
	ll check=0;
	for(int i=0;i<Member;i++){
		if(compare>Admin[i].mem->Salary()){
			compare=Admin[i].mem->Salary();
			check=i;
		}
	}
	Admin[check].mem->xuat();
}
void Manager::Max_Salary_IT(){
	double compare=0;
	ll check=0;
	for(int i=0;i<Member;i++){
		if(compare<Admin[i].mem->Salary() && Admin[i].x==1){
			compare=Admin[i].mem->Salary();
			check=i;
		}
	}
	Admin[check].mem->xuat();
}
void Manager::Min_Salary_Verify(){
	double compare=1e18;
	ll check=0;
	for(int i=0;i<Member;i++){
		if(compare>Admin[i].mem->Salary() && Admin[i].x==2){
			compare=Admin[i].mem->Salary();
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
