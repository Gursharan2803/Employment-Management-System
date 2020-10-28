#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

int emp_id_width=8;
int name_width=20;
int Numerical_width=10;
int email_width=25;
int total_width=100;

struct employee{
    int emp_id;
    string name;
    double basicsalary;
    double pf;
    double healthInsAmt;
    string email;
    };
    // fuction prototype//
void readingfile(vector <employee>& a);
void printmenu();
void dotask(vector <employee>& a, int option);
void addemployee(vector <employee>& a);
int search_employee_id(vector <employee> a, int targetemploy_id);
void printemploees(vector <employee> a);
void printemployee(employee e);
double getnetsalary(employee e);
void savetofile(vector <employee> a);
bool deleteemployee(vector <employee>& a,int index);

void readingfile(vector <employee>& a){
ifstream fin;
fin.open("emp.txt");
if(!fin){
    cout<<"error in reading file";
    exit(1);
}
int recordno=0;
string line;
while (!fin.eof()){
    recordno++;
    getline(fin,line);
        /*cout<<recordno<<"-"<<line<<endl;
since its successfully read the file , now we have tp parse it to get our result.*/
    string stremp_id;
    string strname;
    string strbasicsalary;
    string strpf;
    string strhealthInsAmt;
    string stremail;
    istringstream iss(line);
    getline(iss,stremp_id,',');
    getline(iss,strname,',');
    getline(iss,stremail,',');
    getline(iss,strbasicsalary,',');
    getline(iss,strpf,',');
    getline(iss,strhealthInsAmt,',');

    employee t;
    t.emp_id=atoi(stremp_id.c_str());
    t.name=strname;
    t.basicsalary=atof(strbasicsalary.c_str());
    t.pf=atof(strpf.c_str());
    t.healthInsAmt=atof(strhealthInsAmt.c_str());
    t.email=stremail;

    a.push_back(t);}
    }

void printmenu(){
cout<<"1. ADD EMPLOYEE "<<endl;
cout<<"2. PRINT EMPLOYEE REPORT "<<endl;
cout<<"3. SEARCH EMPLOYEE"<<endl;
cout<<"4. DELETE EMPLOYEE"<<endl;
cout<<"5. SAVE "<<endl;
cout<<"6. EXIT"<<endl;
}
void addemployee(vector <employee>& a){
employee temp;
bool duplicate=false;
do{
        duplicate=false;
        cout<<"employee.id"<<endl;
      cin>>temp.emp_id;
        if(search_employee_id(a,temp.emp_id) != -1){
        duplicate=true;
            cout<<"employee id"<<temp.emp_id<<" "<<"is already there, pls input unique employee id  "<<endl;

        }else{

        }


}while(duplicate);
cout<<"name"<<endl;
cin.clear();
cin.ignore(INT_MAX, '\n');
getline(cin,temp.name);
cout<<"BASIC SALARY ($) "<<endl;
cin>>temp.basicsalary;
cout<<"pf"<<endl;
cin>>temp.pf;
cout<<"healthInsAmt"<<endl;
cin>>temp.healthInsAmt;
cin.clear();
cin.ignore(INT_MAX, '\n');
cout<<"email"<<endl;
getline(cin,temp.email);

a.push_back(temp);
cout<<"record with employee id "<<temp.emp_id<<"has been successfully added into record "<<endl;
cout<<" Total employees "<<a.size()<<endl;

}
int search_employee_id(vector <employee> a, int targetemploy_id){

for(int i=0; i<a.size();++i){
    if(a[i].emp_id== targetemploy_id)
        return i;
    }
    return -1;
}

    void printemployees(vector <employee> a){
cout<<setw(emp_id_width)<<left<<"EMPid";
cout<<setw(name_width)<<left<<"Name";
cout<<setw(email_width)<<left<<"Email";
cout<<setw(Numerical_width)<<right<<"salary ($)";
cout<<setw(Numerical_width)<<right<<"pf ($)";
cout<<setw(Numerical_width)<<right<<" hltINS ($)";
cout<<setw(Numerical_width)<<right<<"NET ($)"<<endl;
cout<<setw(total_width)<<setfill('-')<<" "<<endl;
cout<<setfill(' ');
double totalbasic =0.0;
     double totalpfdeduction=0.0;
     double totalhealthinss=0.0;
     double netsalary=0.0;

for(vector <employee>::iterator it= a.begin();it!=a.end();++it){
    printemployee(*it);
      totalbasic+=it->basicsalary;
      totalpfdeduction+=it->pf;
     totalhealthinss+=it->healthInsAmt;
     netsalary+=getnetsalary(*it);}
    cout<<setw(total_width)<<setfill('-')<<" "<<endl;
    cout<<setfill(' ');
cout<<setw(emp_id_width)<<left<<"Total";
cout<<setw(name_width)<<left<<"IN ($)";
cout<<setw(email_width)<<right<<" ";
cout<<setw(Numerical_width)<<right<<setprecision(2)<<fixed<<totalbasic;
cout<<setw(Numerical_width)<<right<<setprecision(2)<<fixed<<totalpfdeduction;
cout<<setw(Numerical_width)<<right<<setprecision(2)<<fixed<<totalhealthinss;
cout<<setw(Numerical_width)<<right<<setprecision(2)<<fixed<<netsalary<<endl;
}

void printemployee(employee e){
    cout<<setw(emp_id_width)<<left<<e.emp_id;
    cout<<setw(name_width)<<left<<e.name;
cout<<setw(email_width)<<left<<e.email;
cout<<setw(Numerical_width)<<right<<setprecision(2)<<fixed<<e.basicsalary;
cout<<setw(Numerical_width)<<right<<setprecision(2)<<fixed<<e.pf;
cout<<setw(Numerical_width)<<right<<setprecision(2)<<fixed<<e.healthInsAmt;
cout<<setw(Numerical_width)<<right<<setprecision(2)<<fixed<<getnetsalary(e)<<endl;

}
double getnetsalary(employee e){
return e.basicsalary -(e.pf+e.healthInsAmt);
}

void savetofile(vector <employee> a)
{
    ofstream fout;
    fout.open("emp.txt");
if(!fout){
    cout<<"error in reading file";
    exit(1);}
    else{
            int record=0;
        for(vector <employee>::iterator it=a.begin(); it!=a.end();++it){
            fout<<it->emp_id<<","<<it->name<<","<<it->email<<","<<it->basicsalary<<","<<it->pf<<","<<it->healthInsAmt;
            ++record;
            if(record!=a.size()){
                fout<<endl;
            }

        }
        fout.close();
    }

cout<<"total "<<a.size()<<" employees successfully saved to the file"<<endl;

}

void dotask(vector <employee>& a, int option){
    int index=0;
    int targetemployee_id;
switch(option){
case 1:addemployee(a);
    break;
case 2:printemployees(a);
    break;
case 3:cout<<"Enter employee id to search";
    cin>>targetemployee_id;
    index= search_employee_id(a,targetemployee_id);
    if(index==-1){
        cout<<"Employee with id  "<<targetemployee_id<<"does'nt exists"<<endl;

    }else{
        cout<<"Employee exists with the following details "<<endl;
    printemployee(a[index]);
    }
break;
case 4:cout<<"enter the employee id to delete from the file"<<endl;
cin>>targetemployee_id;
    if(deleteemployee(a,targetemployee_id)){
        cout<<"this employee has successfully deleted from the file"<<endl;
        cout<<"press 5 to save changes"<<endl;
    }else{
    cout<<"employee with id "<<targetemployee_id<<" could not be deleted"<<endl;}
    break;
case 5:savetofile(a);
    break;
default:cout<<"Invalid option choosen, valid options are from 1-6 "<<endl;


}

}
bool deleteemployee(vector <employee>& a,int targetemployee_id){
    int index=search_employee_id(a,targetemployee_id);
    if(index==-1){
            return false;}
        cout<<"employee with id "<<targetemployee_id<<" found"<<endl;
        printemployee(a[index]);
        cout<<"are you sure to delete? press 1 to delete or 0 to exit"<<endl;
        int option;
        cin>>option;
        if(option ==1){
                a.erase(a.begin()+index);
        return true;


        }else{
        return false;}

    }


int main()
{
vector <employee> a;
readingfile(a);
cout<<" Total"<<a.size()<<"record read from the data file"<<endl;
printmenu();
bool quit = false;
while(!quit){
    int option;
    cout<<"enter your option"<<endl;
    cin>>option;
    if(option==6){
        quit=true;

    }else{
    dotask(a,option);
    }

}

}
