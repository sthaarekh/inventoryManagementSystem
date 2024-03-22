//Inventory Management System by Arekh Shrestha
//sthaarekh

#include<stdio.h>
#include<string.h>
#include"admin.h"
#include"customer.h"
int main(){
    main:
    printf("\e[1;1H\e[2J");
    printf("Welcome to Inventory Management System");
    printf("\n@sthaarekh");
    printf("\n\n1. Admin Section");
    printf("\n2. Customer Section");
    printf("\n3. Exit the program.\n");
    printf("\nEnter your choice: ");
    choice:
    scanf("%d",&c);
    switch (c){
        case 1:
        getchar();
        printf("Enter password to acess admin section: ");
        pass:
        scanf("%[^\n]%*c",password);
        fpr = fopen("password.txt", "r");
        fscanf(fpr, "%[^\n]%*c",storedPassword);
            if(strcmp(password,storedPassword)==0){
                adminSection();
            }
            else{
                printf("\nYou entered worng password \nPlease enter the password again: ");
                goto pass;
            }
        printf("\nGo back to main menu: (Y/N)");
        scanf("%s", &choice);
            if (choice == 'Y' || choice == 'y')
                goto main;
            else
                printf("Exiting the program....");
        break;
        case 2:
            customerSection();
            break;
        case 3:
            printf("Exiting the program....");
            break;
        default:
        printf("\nInvalid Choice!! Please Enter a valid choice: ");
        goto choice;
    }
}