#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//A single vertex for a singe account
struct user{
	char userName[20];
	char name[20];
	char password[20];
	char securityQuestion[50];
	char securityAnswer[40];
};
//A nulluser vertex for the search_user function
struct user *nullUser = NULL;
//Linked list of users(a sub to to array of pointers)
struct accounts{
	struct user presentAcc;
	struct accounts * nextAcc;
};
//A graph structure representing edges
struct friendList{
	char userName[20];
	struct user * acc;
	struct friendList * nextFriend;
};
//Friendlistlinked containes all the nodes
struct friendListLinked{
	struct friendList * friend;
	struct friendListLinked * nextFriendList;
};

struct friendListLinked *startFriendList = NULL;



struct accounts * start = NULL, * end;


void displayFriends(struct user * dumUser);
void create_account();
struct user * search_username(char * str);
char * gets_f(char * str, int size);
void changePass(struct user * dumUser);
void addFriend(struct user *dumUser, struct user * friendAdd);
void enter_session(struct user * dumUser);
void displayAccounts();
void displayFriends(struct user * dumUser);
void deleteFriend(struct user *dumUser, struct user * friendAdd);
void deleteUser(struct user *dumUser);
void deleteAccount(struct user *dumuser);


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
		printf("4. To quit\n");
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


void create_account(){
	struct user temp;
	printf("Enter Name\n");
	gets_f(temp.name, 20);
	printf("Enter username\n");
	gets_f(temp.userName, 20);
	while(search_username(temp.userName) != nullUser){
		printf("This username already exists\n");
		gets_f(temp.userName, 20);
	}
	printf("Enter password\n");
	gets_f(temp.password, 20);
	printf("Enter security quesiton\n");
	gets_f(temp.securityQuestion, 50);
	printf("Enter answer to security question\n");
	gets_f(temp.securityAnswer, 40);
	struct accounts *tempAcc = (struct accounts *)(malloc(sizeof(struct accounts)));
	tempAcc->presentAcc = temp;
	tempAcc->nextAcc = NULL;
	if(start == NULL)
		start = end = tempAcc;
	else{
		end->nextAcc = tempAcc;
		end = tempAcc;
	}
	struct friendList *friends = (struct friendList *)(malloc(sizeof(struct friendList)));
	strcpy(friends->userName, temp.userName);
	friends->acc = &temp;
	friends->nextFriend = NULL;
	struct friendListLinked *friendlistlink = (struct friendListLinked *)(malloc(sizeof(struct friendListLinked)));
	friendlistlink->friend = friends;
	friendlistlink->nextFriendList = NULL; 
	if(startFriendList == NULL){
		startFriendList = friendlistlink;
	}
	else{
		struct friendListLinked * tempFriendList = startFriendList;
		while(tempFriendList->nextFriendList != NULL){
			tempFriendList = tempFriendList->nextFriendList;
		}
		tempFriendList->nextFriendList = friendlistlink;
	}
}


struct user * search_username(char * str){
	struct accounts *tempAcc = start;
	if(tempAcc == NULL){
		printf("No accounts\n");
		return nullUser;
	}
	while(tempAcc != NULL){
		if(strcmp(tempAcc->presentAcc.userName, str) == 0){
			return &(tempAcc->presentAcc);
		}
		tempAcc = tempAcc->nextAcc;
	}
	return nullUser;
	
}


void addFriend(struct user *dumUser, struct user * friendAdd){
	struct friendListLinked * friendlistlink = startFriendList;
	while(friendlistlink != NULL && strcmp(friendlistlink->friend->userName, dumUser->userName) != 0){
		friendlistlink = friendlistlink->nextFriendList;
	}
	if(friendlistlink == NULL){
		printf("Such account doesn't exists\n");
		return;
	}

	struct friendList * tempFriendList = (struct friendList *)(malloc(sizeof(struct friendList)));
	tempFriendList->nextFriend = NULL;
	tempFriendList->acc = friendAdd;
	
	struct friendList * temp = friendlistlink->friend;
	while(temp->nextFriend != NULL)
		temp = temp->nextFriend;
	temp->nextFriend = tempFriendList;
}

void changePass(struct user * dumUser){
	int tries = 0;
	char answer[40];
	printf("You need to first answer the entered security quesiton\n");
	printf("%s\n", dumUser->securityQuestion);
	printf("%s\n", dumUser->securityAnswer);
	gets_f(answer, 40);
	while(strcmp(dumUser->securityAnswer, answer) != 0 && tries < 3){
		tries++;
		printf("Please enter the correct answer\n");
		printf("You've got %d tries left\n", 3 - tries);
		gets_f(answer, 40);
	}
	if(tries >= 3){
		printf("Bye\n");
		return;
	}
	else{
		printf("Enter new password\n");
		gets_f(dumUser->password, 20);
	}
}


void enter_session(struct user * dumUser){
	char str[20];
	char choice;
	char yOrN;
	struct user * friendAdd;
	do{
		printf("Welcome, %s!\n", dumUser->name);
		printf("1. To add a friend\n");
		printf("2. To display friends\n");
		printf("3. To delete friend\n");
		printf("4. To delete account\n");
		printf("q. To quit\n");
		scanf("%c", &choice);
		getchar();
		switch(choice){
			case '1':
				printf("Enter friend's username to add\n");
				gets_f(str, 20);
				friendAdd = search_username(str);
				if(friendAdd == nullUser){
					printf("There isn't such account\n");
					break;
				}
				addFriend(dumUser, friendAdd);
				addFriend(friendAdd, dumUser);
				break;
			case '2':
				displayFriends(dumUser);
				break;
			case '3':
				printf("Enter friend's username to delete\n");
				gets_f(str, 20);
				friendAdd = search_username(str);
				if(friendAdd == nullUser){
					printf("There isn't such account\n");
					break;
				}
				deleteFriend(dumUser, friendAdd);
				deleteFriend(friendAdd, dumUser);
				break;
			case '4': 
				printf("Are you sure you want to do this! You will lose all your data and your existence will be wiped off!!\n");
				scanf("%s", &yOrN);
				if(yOrN == 'y' || yOrN == 'Y')
					deleteUser(dumUser);
				choice = 'q';
				break;

			case 'q':
				break;
			default:
				printf("Invalid choice\n");
		}
	}while(choice != 'q');


}

void displayAccounts(){
	struct accounts * tempAcc = start;
	if(tempAcc == NULL)
		printf("No acc\n");
	else
		while(tempAcc != NULL){
			printf("Name is -> %s\n",tempAcc->presentAcc.name);
			printf("Username is -> %s\n",tempAcc->presentAcc.userName);
			printf("Password is -> %s\n",tempAcc->presentAcc.password);
			tempAcc = tempAcc->nextAcc;

		}
}


void displayFriends(struct user * dumUser){
	struct friendListLinked * friendlistlink = startFriendList;
	while(friendlistlink != NULL && strcmp(friendlistlink->friend->userName, dumUser->userName) != 0){
		friendlistlink = friendlistlink->nextFriendList;
	}
	if(friendlistlink == NULL){
		printf("Such account doesn't exists\n");
		return;
	}
	printf("Over here\n");
	struct friendList * temp = friendlistlink->friend;
	temp = temp->nextFriend;
	if(temp == NULL){
		printf("You don't have any friends! :( \n");
		return;
	}
	while(temp != NULL){
		printf("%s\n", temp->acc->name);
		temp = temp->nextFriend;
	}
}

void deleteFriend(struct user *dumUser, struct user * friendAdd){
	char choice;
	struct friendListLinked * friendlistlink = startFriendList;
	while(friendlistlink != NULL && strcmp(friendlistlink->friend->userName, dumUser->userName) != 0){
		friendlistlink = friendlistlink->nextFriendList;
	}
	if(friendlistlink == NULL){
		printf("Such account doesn't exists\n");
		return;
	}
	struct friendList * friendlist = friendlistlink->friend;
	if(friendlist->nextFriend == NULL){
		printf("You don't have any friends! :( \n");
		return;
	}
	while(friendlist->nextFriend != NULL && friendlist->nextFriend->acc != friendAdd)
		friendlist = friendlist->nextFriend;
	if(friendlist->nextFriend == NULL){
		printf("You don't have a friend by this name\n");
		return;
	}
	printf("Are you sure you want to remove %s as your friend? (press Y | N)\n", friendlist->nextFriend->acc->userName);
	scanf("%c", &choice);
	getchar();
	if(choice == 'N' || choice == 'n')
		return;
	else{
		struct friendList * friends = friendlist->nextFriend;
		friendlist->nextFriend = friends->nextFriend;
		friends->nextFriend = NULL;
	}
}	

void deleteUser(struct user *dumUser){
	struct friendListLinked * friendlistlink = startFriendList;
	struct user * friends;
	struct friendList * friendsNext;
	while(friendlistlink != NULL && strcmp(friendlistlink->friend->userName, dumUser->userName) != 0){
		friendlistlink = friendlistlink->nextFriendList;
	}
	if(friendlistlink == NULL){
		printf("Such account doesn't exists\n");
		return;
	}

	/*Deleting all friends if they exist */
	if(friendlistlink->friend->nextFriend != NULL){
		struct friendList *friendlist = friendlistlink->friend;
		friendlist = friendlist->nextFriend;
		while(friendlist != NULL){
			friends = friendlist->acc;
			friendsNext = friendlist->nextFriend;
			deleteFriend(dumUser, friends);
			deleteFriend(friends,dumUser);
			friendlist = friendsNext;
		}
	}
	/*Deleting the account */
	deleteAccount(dumUser);
}

void deleteAccount(struct user *dumUser){
	struct accounts *temp = start;
	if(start == end)
		start = end = NULL;
	else if(start->presentAcc.userName == dumUser->userName){
		start = temp->nextAcc;
	}
	else{
		while(temp->nextAcc != NULL && temp->nextAcc->presentAcc.userName != dumUser->userName)
			temp = temp->nextAcc;
		struct accounts * temp2 = temp->nextAcc;
		temp->nextAcc = temp2->nextAcc;
		temp = temp2;
	}
	temp->nextAcc = NULL;
	free(temp);
}
