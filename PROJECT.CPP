        //Header Files required
#include <iostream.h>
#include <conio.h>
#include <fstream.h>
#include <string.h>
#include <stdio.h>

using namespace std;

fstream file1, file2;
        //Defining Structures
struct Id //Accepts name and password
{
  char name[30], password[20];
  int employee;
};

struct traindetails //For Train Details
{
  char from[10], to[10], date[10];
  int  trainNo, coach;
} set;

       //Function Declaration
int askPassword(int); //asks for user/employee id by calling struct id
void setupEmployee();//creates first employee at the start if required
void createLogin(int);//Creates Id of User/Employee

typedef traindetails td;

       //Class Declaration
class employee //For employee depatment
{
  td train;
 public:
  employee()
  {
    strcpy(train.from,"DELHI");
    strcpy(train.to,"MUMBAI");
    train.trainNo=10000;
    train.date[0]='\0';
    train.coach=0;
  }
  void addTrains(); //adds the trains to the file
};

class user
{
  td location,tan;
  int i,tno;
 public:
  user()
  {
    i=0;
  }
  void searchTrain();   //Searches for the trains from user inputs
  void showFare();   //Displays the Fare
};

class PassDetails
{
  char gender;
  int age,trnNo;
 public:
  char name[20];
  void enter();//inputs passenger details
  void disp();//displays passenger details
  int tno(); //returns train number
};

class setPayment: public user  //For the details of the train opted by user
{
  int cvv, i,tNo,j;
  char card_type[10], card_no[20], pname[30];
  PassDetails det;
  td trnd;
 public:
  void EnterPass();  //Enters Passenger Details through PassDetails
  void inputDetails(); //Inputs Payment mode
  void cancelTicket();  //For cancelling the ticket
};

void main()     //Declaring the main function
{
  clrscr();
  employee emp;
  setPayment usr;
  int choice, ch;
  setupEmployee();
  do
  {
    cout<<"Welcome to Railway Reservation Service\nLog In as\n1.Employee\t2.User\t3.Exit\n";
    cin>>choice;
    switch(choice)
    {
      case 1:
        if(askPassword(1)==1)
        {
          clrscr();
          cout<<"Logged In\n";
          int a;
          do
          {
            cout<<"1.Add Trains\t2.Add Employee\t3.Log Out\n";
            cin>>a;
            if(a==1)
              emp.addTrains();
            else if(a==2)
              createLogin(1);
            else if(a==3)
              break;
            else
              cout<<"Invalid Response\n";
          }
          while(a!=3);
        }
        break;
      case 2:
        int b;
        do
        {
          cout<<"1.New user\t2.Existing User\t3.Back\n";
          cin>>b;
          if(b==1)
            createLogin(0);
          else if(b==2)
          {
            if(askPassword(0)==1)
            {
              clrscr();
              cout<<"Logged In\nTrain Search Area\n";
              usr.searchTrain();
              do
              {
                cout<<"1.See Fare\t2.Book Train\t3.Cancel Ticket\t4.Back\n";
                cin>>ch;
                if(ch==1)
                {
                  usr.showFare();
                }
                else if(ch==2)
                {
                  usr.EnterPass();
                  usr.inputDetails();
                }
                else if(ch==3)
                  usr.cancelTicket();
                else if(ch==4)
                  break;
                else
                  cout<<"Invalid\n";
              }
              while(ch!=4);
            }
            else if(b==3)
              break;
            else
              cout<<"Invalid Response\n";
          }
        }
        while(b!=3);
        break;
      case 3:
        break;
      default:
        cout<<"Invalid Response\n";
    }
  }
  while(choice!=3);
  getch();
}
	  //Function Definition
int askPassword(int flag)
{
  clrscr();
  Id pd;
  int i=0;
  file1.open("Password.dat",ios::in|ios::binary);
  char name[30], pass[20];
  cout<<"Enter your username\n";
  cin>>name;
  cout<<"Enter your password\n";
  cin>>pass;
  while(file1.read((char*)&pd,sizeof(pd)))
  {
    if(strcmp(name,pd.name)==0 && strcmp(pass,pd.password)==0 && pd.employee==flag)
    {
      i+=1;
      break;
    }
  }
  file1.close();
  if(i==0)
  {
    cout<<"Invalid Username/Password\n";
  }
  return i;
}

void createLogin(int flag1)
{
  Id pwd;
  file1.open("Password.dat", ios::binary| ios::app);
  cout<<"Enter Username\n";
  cin>>pwd.name;
  cout<<"Enter Password\n";
  cin>>pwd.password;
  pwd.employee=flag1;
  file1.write((char*)&pwd,sizeof(pwd));
  cout<<"Record Updated\n";
  file1.close();
}

void setupEmployee()
{
  Id empy, emp;
  int empty = 1, a;
  file1.open("Password.dat",ios::binary | ios::in | ios::app);
  a=file1.tellg();
  if(a!=0)
  {
    while(file1.read((char*)&empy,sizeof(empy)))
    {
      if(empy.employee==1)
      {
	empty = 0;
	break;
      }
    }
  }
  if(empty==1)
  {
    strcpy(emp.name,"irctc.com");
    strcpy(emp.password,"trains");
    emp.employee=1;
    file1.write((char*)&emp,sizeof(emp));
  }
  file1.close();
}

       //Class Definition
//Employee class functions
void employee::addTrains()
{
  cout<<"Enter train number\n";
  cin>>train.trainNo;
  cout<<"Enter Journey Station\n";
  cin>>train.from;
  cout<<"Enter Destination\n";
  cin>>train.to;
  cout<<"Enter date of Journey\n";
  cin>>train.date;
  file1.open("Train.dat", ios::app| ios::binary);
  file1.write((char*)&train, sizeof(train));
  cout<<"Success\n";
  file1.close();
}

void user::searchTrain()
{
  c:
  cout<<"Enter Journey Station\n";
  cin>>location.from;
  cout<<"Enter Destination\n";
  cin>>location.to;
  cout<<"Enter date of Journey\n";
  cin>>location.date;
  file1.open("Train.dat",ios::in|ios::binary);
  while(file1.read((char*)&tan,sizeof(tan)))
  {
    if(strcmpi(location.from,tan.from)==0 && strcmpi(location.to,tan.to)==0 && strcmpi(location.date,tan.date)==0)
    {
      cout<<"Train number "<<tan.trainNo;
      cout<<"\nFrom "<<tan.from;
      cout<<"\nTo "<<tan.to;
      cout<<"\nDate "<<tan.date<<endl;
      i++;
    }
  }
  if(i==0)
  {
    cout<<"Not available\n";
    goto c;
  }
  do
  {
    cout<<"1.Reset\t2.Continue\n";
    cin>>tno;
    if(tno==1)
    {
      clrscr();
      goto c;
    }
    else if(tno==2)
    {}
    else
    {
      cout<<"Invalid\n";
    }
  }
  while(tno!=2);
}

void user::showFare()
{
  cout<<"Fare:\nBase Fare: 800\nTax: 144\nDynamic Fare: 500\nTotal Fare(per person)=1444\n";
}

void PassDetails::enter()
{
  file1.open("Train.dat",ios::app|ios::binary);
  g:
  cout<<"Enter the train number\n";
  cin>>trnNo;
  cout<<"Enter the name\n";
  cin>>name;
  cout<<"Enter the Gender(M/F)\n";
  cin>>gender;
  cout<<"Enter the age\n";
  cin>>age;
  while(file1.read((char*)&set,sizeof(set)))
  {
    if(trnNo==set.trainNo)
    {
      if(set.coach<65)
	set.coach+=1;
      else
      {
	cout<<"Seats full\nPlease select another train\n";
	goto g;
      }
    }
  }
  file1.close();
}

void PassDetails::disp()
{
  cout<<"Train number "<<trnNo;
  cout<<"\nName "<<name;
  cout<<"\nAge "<<age;
  cout<<"\nGender "<<gender<<endl;
}

int PassDetails::tno()
{
  return trnNo;
}

void setPayment::EnterPass()
{
  file2.open("passenger.dat",ios::app|ios::binary);
  cout<<"Enter the number of passengers\n";
  cin>>i;
  j=i;
  while(i>0)
  {
    det.enter();
    file2.write((char*)&det,sizeof(det));
    i--;
    det.disp();
  }
  file2.close();
}

void setPayment::inputDetails()
{
  cout<<"Enter of your card number\n";
  gets(card_no);
  cout<<"Enter your card type(Credit/Debit)\n";
  gets(card_type);
  cout<<"Enter your cvv\n";
  cin>>cvv;
  clrscr();
  cout<<"Payment Successful\n";
  cout<<"Total Amount paid "<<j*1444<<endl;
  showFare();
}

void setPayment::cancelTicket()
{
  file1.open("passenger.dat",ios::in|ios::binary);
  file2.open("temp.dat",ios::out|ios::binary);
  fstream f3("Train.dat",ios::in|ios::app|ios::binary);
  i=0;
  do
  {
    cout<<"Enter your name\n";
    cin>>pname;
    cout<<"Enter the train number\n";
    cin>>tNo;
    while(file1.read((char*)&det,sizeof(det)))
    {
      if(strcmp(det.name,pname)!=0 || det.tno()!=tNo)
      {
	file2.write((char*)&det,sizeof(det));
      }
      else
	i=1;
    }
    if(i==0)
    {
      cout<<"Invalid Name\n";
    }
  }
  while(i==0);
  file1.close();
  file2.close();
  remove("passenger.dat");
  rename("temp.dat","passenger.dat");
  while(f3.read((char*)&trnd,sizeof(trnd)))
  {
    if(trnd.trainNo==tNo)
    {
      trnd.coach-=1;
      f3.write((char*)&trnd,sizeof(trnd));
    }
  }
  cout<<"Ticket cancelled\n";
  f3.close();
}