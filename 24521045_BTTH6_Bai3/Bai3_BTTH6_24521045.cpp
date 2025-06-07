#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
class cSinhVien{
	private:
		string ID;
		string Name;
		string street;
	protected:
		ll credit;
		double average;
	public:
		double getAverage(){
			return this->average;
		}
		virtual void doc(){
			cin.ignore();
			cout<<"In ID_Student: "<<flush;
			getline(cin,ID);
			
			cout<<"In Name_Student: "<<flush;
			getline(cin,Name);
			
			cout<<"In Home_Student: "<<flush;
			getline(cin,street);
			
			cout<<"In Credit_Student: "<<flush;
			cin>>credit;
			
			cout<<"In Scores_Average: "<<flush;
			cin>>average;
		}
		
		virtual bool Pass()=0;
		
		virtual void xuat(){
			cout<<Name<<" "<<ID<<" "<<street<<endl;
		}
};
class cCollege : public cSinhVien{
	private:
		double scores;
	public:
		void doc() override{
			cSinhVien::doc();
			cout<<"In Scores: "<<flush;
			cin>>scores;
		}
		bool Pass() override{
			if(credit>=120 && average>=5.0 && scores>=5) return true;
			return false;
		}
		void xuat() override{
			cout<<"I'm College_Student"<<endl;
			cSinhVien::xuat();
			if(Pass()) cout<<"Congratulation, You passed graduation"<<endl;
				else cout<<"You didn't pass graduation"<<endl;
		}
};
class cUniversity : public cSinhVien{
	private:
		string Name_Title;
		double scores;
	public:
		void doc() override{
			cSinhVien::doc();
			cin.ignore();
			cout<<"In Name_Title: "<<flush;
			getline(cin,Name_Title);
			
			cout<<"In Scores: "<<flush;
			cin>>scores;
		}
		bool Pass() override{
			if(credit>=170 && average>=5.0 && scores>=5) return true;
			return false;
		}
		void xuat() override{
			cout<<"I'm University_Student"<<endl;
			cSinhVien::xuat();
			if(Pass()) cout<<"Congratulation, You passed graduation"<<endl;
				else cout<<"You didn't pass graduation"<<endl;
		}
}; 
struct bg{
	cSinhVien *mem;
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
		void Out_graduation();
		void Out_ungraduation();
		void Max_Average();
		void Max_Average_College();
		void countIneligibleByType();
};
void Manager::Menu(){
	int choice;
    do {
        cout<<"\n========== MENU =========="<<endl;
        cout<<"1. Nhap danh sach"<<endl;
        cout<<"2. Xuat danh sach"<<endl;
        cout<<"3. Xuat danh sach sinh vien du dieu kien tot nghiep"<<endl;
        cout<<"4. Xuat danh sach sinh vien KHONG du dieu kien tot nghiep"<<endl;
        cout<<"5. Sinh vien co diem trung binh cao nhat"<<endl;
        cout<<"6. Sinh vien co diem trung binh cao nhat o sinh vien cao dang"<<endl;
        cout<<"7. Thong ke so luong sinh vien khong du dieu kien tot nghiep theo loai"<<endl;
        cout<<"0. Thoat"<<endl;
        cout<<"=========================="<<endl;
        cout<<"Nhap lua chon cua ban: "<<flush;
        cin>>choice;
        switch (choice) {
            case 1:
                In();
                break;
            case 2:
                Out();
                break;
            case 3:
                Out_graduation();
                break;
            case 4:
                Out_ungraduation();
                break;
            case 5:
                Max_Average();
                break;
            case 6:
            	Max_Average_College();
            	break;
            case 7:
                countIneligibleByType();
                break;
            case 0:
                cout<<"Thoat chuong trinh."<<endl;
                break;
            default:
                cout<<"Lua chon khong hop le. Vui long chon lai."<<endl;
        }
    }
	while (choice!=0);
}
void Manager::In(){
	cout<<"Nhap so luong sinh vien: "<<flush;
	cin>>Member;
	for(int i=0;i<Member;i++){
		cout<<"1.College"<<endl;
		cout<<"2.University"<<endl;
		ll choice;
		cin>>choice;
		bg temp;
		temp.mem=nullptr;
		if(choice==1){
			temp.mem=new cCollege();
			temp.x=choice;
		}
		if(choice==2){
			temp.mem=new cUniversity();
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
void Manager::Out_graduation(){
	for(int i=0;i<Member;i++){
		if(Admin[i].mem->Pass()) Admin[i].mem->xuat();
	}
}
void Manager::Out_ungraduation(){
	for(int i=0;i<Member;i++){
		if(Admin[i].mem->Pass()!=1) Admin[i].mem->xuat();
	}
}
void Manager::Max_Average(){
	double compare=0;
	ll check=0;
	for(int i=0;i<Member;i++){
		if(compare<Admin[i].mem->getAverage()){
			compare=Admin[i].mem->getAverage();
			check=i;
		}
	}
	Admin[check].mem->xuat();
}
void Manager::Max_Average_College(){
	double compare=0;
	ll check=0;
	for(int i=0;i<Member;i++){
		if(compare<Admin[i].mem->getAverage() && Admin[i].x==1){
			compare=Admin[i].mem->getAverage();
			check=i;
		}
	}
	Admin[check].mem->xuat();
}
void Manager::countIneligibleByType(){
	ll dem1=0,dem2=0;
	for(int i=0;i<Member;i++){
		if(Admin[i].mem->Pass()!=1){
			if(Admin[i].x==1) dem1++;
				else dem2++;
		}
	}
	cout<<"College: "<<flush<<dem1<<endl;
	cout<<"University: "<<flush<<dem2<<endl;
}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	Manager A;
	A.Menu();
	return 0;
}
