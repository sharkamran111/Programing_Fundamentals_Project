#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct BankAccount{
 int accountNumber;
 char name[50];
 char accountType[20];
 float balance;
 char phoneNumber[15];
 char address[100];
} ;

void displayMenu() {
 printf(" \n\nMAIN MENU\n   ");
 printf("1. Create New Account\n");
 printf("2. Display All Accounts\n");
 printf("3. Search Account\n");
 printf("4. Deposit Money\n");
 printf("5. Withdraw Money\n");
 printf("6. Update Account Information\n");
 printf("7. Delete Account\n");
 printf("8. Save Data to File\n");
 printf("9. Exit\n\n");
 
}



void saveFile(struct BankAccount *accounts, int count) {
 FILE *file;
 
 file = fopen("bank_accounts.dat", "wb"); 
 
 if(file == NULL) {
 printf("\nError \n");
 return;
 }
 fwrite(&count, sizeof(int), 1, file);
 fwrite(accounts, sizeof(struct BankAccount), count, file);
 fclose(file);
}



void loadfile(struct BankAccount *accounts, int *count) {
 FILE *file;

 file = fopen("bank_accounts.dat", "rb");
 
 if(file == NULL) {
 *count = 0;
 return;
 }
 fread(count, sizeof(int), 1, file);
 fread(accounts, sizeof(struct BankAccount), *count, file);
 fclose(file);
 
 printf("\nLoaded existing accounts from database\n");
}



int searchacc(struct BankAccount *accounts, int count, int accNum) {
 int i;
 
 for(i = 0; i < count; i++) {
 if(accounts[i].accountNumber == accNum) {
 return i;
 }
 }  
 return -1;
}


void createAccount(struct BankAccount *accounts, int *count) {
 int currentIndex;

 if(*count>=100) {
 printf("\nDatabase is full! Cannot add more accounts\n");
 return;
 }
 
 printf("\n Creating New Account\n");
 
 currentIndex = *count;

 if(*count > 0) { 
 accounts[currentIndex].accountNumber = accounts[*count-1].accountNumber+1;
 } else {
 accounts[currentIndex].accountNumber=1001;
 }
 getchar();
 printf("Account Number: %d\n", accounts[currentIndex].accountNumber);
 printf("Enter The Account Holder Name: ");
 fgets(accounts[currentIndex].name, 50, stdin);
 accounts[currentIndex].name[strcspn(accounts[currentIndex].name, "\n")] = 0;
 
 printf("Enter Account Type (Savings/Current/Fixed): ");
 fgets(accounts[currentIndex].accountType, 20, stdin);
 accounts[currentIndex].accountType[strcspn(accounts[currentIndex].accountType, "\n")] = 0;

 
 printf("Enter Initial Balance: ");
 scanf("%f", &accounts[currentIndex].balance);
 getchar();

 
 printf("Enter Phone Number: ");
 fgets(accounts[currentIndex].phoneNumber, 15, stdin);
 accounts[currentIndex].phoneNumber[strcspn(accounts[currentIndex].phoneNumber, "\n")] = 0; 

 
 
 printf("Enter Address: ");
 fgets(accounts[currentIndex].address, 100, stdin);
 accounts[currentIndex].address[strcspn(accounts[currentIndex].address, "\n")] = 0;

 
 (*count)++;
 
 printf("\nAccount created\n");
 printf("Your Account Number is: %d\n", accounts[currentIndex].accountNumber);
}


void displayAllAccounts(struct BankAccount *accounts, int count) {
 int i;
 
 if(count == 0) {
 printf("\nNo accounts found in the system.\n");
 return;
 }
  
 printf(" ALL BANK ACCOUNTS\n");

 for(i = 0; i < count; i++) {
 printf("\nAccount %d:\n", i + 1);
 printf("  Account Number: %d\n", accounts[i].accountNumber);
 printf("  Name: %s\n", accounts[i].name);
 printf("  Account Type: %s\n", accounts[i].accountType);
 printf("  Balance: %.2f\n", accounts[i].balance);
 printf("  Phone: %s\n", accounts[i].phoneNumber);
 printf("  Address: %s\n", accounts[i].address);
 }
}


void searchAccount(struct BankAccount *accounts, int count) {
 int accNum, index;

 if(count == 0) {
 printf("\nNo accounts found in the system.\n");
 return;
 }
 
 printf("\nSEARCH ACCOUNT\n");
 printf("Enter Account Number: ");
 scanf("%d", &accNum);
 
 index = searchacc(accounts, count, accNum);
 
 if(index != -1) {
 printf("\n*** Account Found! ***\n");
 printf("Account Number: %d\n", accounts[index].accountNumber);
 printf("Name: %s\n", accounts[index].name);
 printf("Account Type: %s\n", accounts[index].accountType);
 printf("Balance: %.2f\n", accounts[index].balance);
 printf("Phone: %s\n", accounts[index].phoneNumber);
 printf("Address: %s\n", accounts[index].address);
 } else {
 printf("\nAccount not found!\n");
 }
}

void depositMoney(struct BankAccount *accounts, int count) {
 int accNum, index;
 float amount;

 if(count == 0) {
 printf("\nNo accounts found\n");
 return;
 }
 
 printf("\nDEPOSIT MONEY\n");
 printf("Enter Account Number: ");
 scanf("%d", &accNum);
 
 index = searchacc(accounts, count, accNum);
 
 if(index != -1) {
 printf("Enter amount to deposit: ");
 scanf("%f",&amount);
 
 if(amount > 0) {
 accounts[index].balance+=amount;
 printf("\nDeposit Successful\n");
 printf("New Balance: %.2f\n", accounts[index].balance);
 } else {
 printf("\nInvalid amount\n Amount must be positive\n");
 }
 } else {
 printf("\nAccount not found\n");
 }
}

void withdrawMoney(struct BankAccount *accounts, int count) {
 int accNum, index;
 float amount;
 if(count == 0) {
 printf("\nNo accounts found\n");
 return;
 }
 
 printf("\n--- WITHDRAW MONEY ---\n");
 printf("Enter Account Number: ");
 scanf("%d", &accNum);

 index = searchacc(accounts, count, accNum);
 
 if(index != -1) {
 printf("Current Balance: %.2f\n", accounts[index].balance);
 printf("Enter amount to withdraw: ");
 scanf("%f", &amount);
 if(amount > 0) {
 if(amount <= accounts[index].balance) {
  accounts[index].balance = accounts[index].balance - amount;
  printf("\nWithdrawal Done\n");
  printf("New Balance: %.2f\n", accounts[index].balance);
 } else {
  printf("\nInsufficient balance\nCan't withdraw.\n");
 }
 } else {
 printf("\nInvalid amount\nAmount must be positive\n");
 }
 } else {
 printf("\nAccount not found\n");
 }
}



void updateAccount(struct BankAccount *accounts, int count) {
 int accNum, index; 
 if(count == 0) {
 printf("\nNo accounts found in the system.\n");
 return;
 }
 printf("\nUPDATE ACCOUNT\n");
 printf("Enter Account Number: ");
 scanf("%d", &accNum);
 getchar();
 index = searchacc(accounts, count, accNum);
 if(index != -1) {
 printf("\nCurrent Information:\n");
 printf("Name: %s\n", accounts[index].name);
 printf("Phone: %s\n", accounts[index].phoneNumber);
 printf("Address: %s\n", accounts[index].address);
 
 printf("\nPlease Enter New Information\n");
 printf("Enter New Name ");
 fgets(accounts[index].name, 50, stdin);
 accounts[index].name[strcspn(accounts[index].name, "\n")] = 0;

 printf("Enter New Phone Number: ");
 fgets(accounts[index].phoneNumber, 15, stdin);
 accounts[index].phoneNumber[strcspn(accounts[index].phoneNumber, "\n")] = 0;

 printf("Enter New Address: ");
 fgets(accounts[index].address, 100, stdin);
 accounts[index].address[strcspn(accounts[index].address, "\n")] = 0;
 
 printf("\nAccount Data updated\n");
 } else {
 printf("\nAccount not found\n");
 }
}

void deleteAccount(struct BankAccount *accounts, int *count) {
 int accNum, index, i;
 char confirm;
 if(*count == 0) {
 printf("\nNo accounts found\n");
 return;
 }
 
 printf("\nDELETING ACCOUNT\n");
 printf("Enter Account Number: ");
 scanf("%d",&accNum);
 index = searchacc(accounts, *count, accNum); 
 if(index != -1) {
 printf("\nAccount Holder: %s\n", accounts[index].name);
 
 for(i = index; i < *count-1; i++) {
  accounts[i] = accounts[i+1];
 }
 (*count)--;
 
 printf("\nAccount deleted\n");
 }else {
 printf("\nAccount not found!\n");
 }
}

int main() {
 struct BankAccount accounts[100]; 
 int count = 0;
 int choice;
 
 
 loadfile(accounts, &count);
 

 printf("  BANK ACCOUNT MANAGEMENT SYSTEM\n");
   
 

 do {
 displayMenu();
 printf("\nEnter your choice: ");
 scanf("%d", &choice);
 getchar();
 
 switch(choice) {
 case 1:
  createAccount(accounts, &count); 
  break;
 case 2:
  displayAllAccounts(accounts, count);
  break;
 case 3:
  searchAccount(accounts, count);
  break;
 case 4:
  depositMoney(accounts, count);
  break;
 case 5:
  withdrawMoney(accounts, count);
  break;
 case 6:
  updateAccount(accounts, count);
  break;
 case 7:
  deleteAccount(accounts, &count);
  break;
 case 8:
  saveFile(accounts, count);
  printf("\nData saved successfully\n");
  break;
 case 9:
  saveFile(accounts, count);
  printf("\nThank you for using Bank Account Management System\n");
  printf("data has been saved\n");
  break;
 default:
  printf("\nInvalid choice! Please try again\n");
 }
 
 } while(choice != 9);
 
 return 0;
}