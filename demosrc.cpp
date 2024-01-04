#include<iostream>
class Stack{
    int top=-1,stack[100],choice;
    int math[100],dsa[100],os[100],ddco[100],oops[100];
    void insert(int sub[]){
        
    }


    void markattendance(){
        int sub;
        printf("1.Math\n2.DSA\n3.OOPS\n4.DDCO\n5.OS\n");
        scanf("%d",&sub);
        switch(sub){
            case 1:insert(math);
        }
    }

    void displayattendance(){
        
    }


    void choice(){
        for(;;){
            printf("Enter your choice: \n1.Mark Attendance\n2.Display Attendance\n3.Exit");
            scanf("%d",&choice);
            switch(choice){
                case 1:markattendance();
                        break;
                case 2:displayattendance();
                        break;
                case 3:exit(0);
                default:printf("\nEnter a valid choice\n");
            }
        }
    }
};

