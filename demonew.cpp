//Simulation of a mailing system

#include<bits/stdc++.h>
using namespace std;

pair<int,string> users[10];
int usercount=0;
string username1,username2;

struct emailnode{
    string message;
    emailnode *next;
}emailnode;

void finduser(string username1){

}

void createnewuser(){
    string username;
    cout<<"\nEnter user name ";
    cin>>username;
    users=username;
    cout<<"\nCreated a User with the UserName: \n"<<users[usercount];
    usercount++;
    return;
}

void sendmail(){
    string username1;
    cout<<"Enter your UserName: ";
    cin>>username1;
    //finduser(username1); write this function later
    cout<<"Enter the User you want to send a mail to: ";
    cin>>username2;
    //finduser(username2);
    

}

int main(){
    int choice;
    for(;;){
        cout<<"\nEnter your Choice:\n1.Create New User\n2.Send Mail\n3.Check Mail\n4.View Users\n5.Delete User\n6.Exit ";
        cin>>choice;
        switch(choice){
            case 1: createnewuser();
                    break;
            /* case 2: sendmail();
                    break;
            case 3: checkmail();
                    break;
            case 4: viewuser();
                    break;
            case 5: deluser();
                    break; */
            case 6: exit(0);
            default:cout<<"Enter a valid choice!!";
        }
    }
}
