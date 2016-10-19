#include <stdio.h>
#include <string.h>
#include "users.h"

//A single vertex for a singe account

//A nulluser vertex for the search_user function

struct user *nullUser = NULL;
//Linked list of users(a sub to to array of pointers)


struct friendListLinked *startFriendList = NULL;



struct accounts * start = NULL, * end;

struct Post * startPost = NULL;

char * gets_f(char * str, int size);



int main(void){
	int choice;
	char def_username[20];
	char def_password[20];
	struct user * dumUser;
	char choice2;
	do{
		printf("Welcome to facebook!\n");
		printf("1. To create account\n");
		printf("2. To login\n");
		printf("3. To list accounts\n");
		printf("5. To quit\n");
		scanf("%d", &choice);
		getchar();
		switch(choice){
			case 1:
				create_account();
				break;
			case 2:	
							
				printf("Please enter username\n");
				scanf("%s", def_username);
				getchar();
				//If search_user returns nullUser(which is NULL) then the username entered is incorrect
				while(( dumUser = search_username(def_username)) == nullUser){
					printf("Please enter correct username\n");
					scanf("%s", def_username);
					getchar();
				}
				printf("Hello %s!\n", dumUser->name);
				printf("Please enter password or press q to change password\n");
				scanf("%s", def_password);
				getchar();
				//False if password entered is incorrect
				while(strcmp(dumUser->password, def_password) != 0 && strcmp(def_password, "q") != 0){
					printf("Please enter correct password or q to quit\n");
					scanf("%s", def_password);
					getchar();
				}
				if(strcmp(def_password, "q") == 0){
					printf("Do you want to change the password? (y | n)\n");
					scanf("%c", &choice2);
					getchar();
					if(choice2 == 'y' || choice2 == 'Y')
						changePass(dumUser);
					break;
				}
				printf("Welcome %s!\n", dumUser->name);
				enter_session(dumUser);
				break;

			case 3: 
				displayAccounts();
				break;			
			case 5:
				break;
			default:
				printf("Invalid choice\n");
		}
	}while(choice != 5);
	

}

char * gets_f(char * str, int size){
	char * ret_val;
	star: 
	ret_val = fgets(str, size, stdin);
	int i = 0;
	//fgets stores even the newline character, so we must get rid of the newline character first
	if(ret_val[0] == '\n'){
		printf("Please enter something\n");
		goto star;
	}
	
	else{
		while(ret_val[i] != '\n'){
			i++;
		}
		ret_val[i] = '\0';
		return ret_val;
	}
}


