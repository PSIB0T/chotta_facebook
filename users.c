#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "users.h"

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
	temp.userPost = NULL;
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
		printf("5. To add a post.\n");
		printf("6. To checkout your posts.\n");
		printf("7. To go to friend's timeline.\n");
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
			case '5':
				addPost(dumUser);
				break;
			case '6':
				displayPost(dumUser);
				break;
			case '7':
				start:
				displayFriends(dumUser);
				printf("\n\nSelect a username\n");
				gets_f(str, 20);
				friendAdd = findFriend(dumUser, str);
				if(friendAdd == nullUser){
					printf("This particular username is not your friend\n");
					goto start;
				}
				printf("\t\t%s\t\t\n",friendAdd->name );
				displayPost(friendAdd);

				
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
	int i = 0;
	while(temp != NULL){
		i++;
		printf("%d.) %s Username:- %s\n", i, temp->acc->name, temp->acc->userName);
		temp = temp->nextFriend;
	}
}

struct user * findFriend(struct user *dumUser, char * str){
	struct friendListLinked * friendlistlink = startFriendList;
	while(friendlistlink != NULL && strcmp(friendlistlink->friend->userName, dumUser->userName) != 0){
		friendlistlink = friendlistlink->nextFriendList;
	}
	if(friendlistlink == NULL){
		printf("Such account doesn't exists\n");
		return nullUser;
	}
	struct friendList * friendlist = friendlistlink->friend;
	if(friendlist->nextFriend == NULL){
		printf("You don't have any friends! :( \n");
		return nullUser;
	}
	friendlist = friendlist->nextFriend;
	while(friendlist != NULL && strcmp(friendlist->acc->userName,str) != 0)
		friendlist = friendlist->nextFriend;
	if(friendlist == NULL){
		printf("You don't have a friend by this name\n");
		return nullUser;
	}
	return friendlist->acc;
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

void addPost(struct user *dumUser){
	char post[80];
	time_t t;
	time(&t);
	printf("Enter something...\n");
	gets_f(post, 80);
	struct Post *tempPost = (struct Post *)malloc(sizeof(struct Post));
	strcpy(tempPost->post, post);
	strcpy(tempPost->postTime, ctime(&t));
	if(dumUser->userPost == NULL)
		tempPost->nextPost = NULL;
	else
		tempPost->nextPost = dumUser->userPost;
	dumUser->userPost = tempPost;
	

}

void displayPost(struct user *dumUser){
	
	if(dumUser->userPost == NULL){
		printf("No posts to be displayed!\n");
		return;
	}
	struct Post * ptr = dumUser->userPost;
	while(ptr != NULL){
		
		printf("\n\n%s\n\n", ptr->post);
		printf("%s\n\n", ptr->postTime);
		ptr = ptr->nextPost;
	}
	
}