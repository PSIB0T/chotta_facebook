#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_FRIEND_SIZE 5
struct node{
	char name[20];
	char userName[10];
	char passWord[10];
	struct node *next;
	int friend_count;
};

int main_account_count = 0;

struct node *create_account(struct node * friend){
	printf("Over here at create account function\n");
	char named[20], username[10], password[10];
	friend = (struct node *)malloc(sizeof(struct node ));
	printf("Enter name\n");
	scanf("%s", named);
	getchar();
	printf("Enter username\n");
	scanf("%s", username);
	getchar();
	printf("Enter password\n");
	scanf("%s", password);
	getchar();
	strcpy(friend->name, named);
	strcpy(friend->userName, username);
	strcpy(friend->passWord, password);
	friend->friend_count = 0;
	friend->next = (struct node *)malloc(sizeof(MAX_FRIEND_SIZE * sizeof(struct node *)));
	int i;
	struct node *temp = friend->next;
	for(i = 0; i < MAX_FRIEND_SIZE; i++){
		temp = NULL;
		temp++;

	}
	printf("Account created with name %s and friend count is %d \n",friend->name, friend->friend_count);
	main_account_count++;
	return friend;
}

void add_friend(struct node **friend1, struct node **friend2){
	struct node *temp1 = *friend1;
	struct node *temp2 = *friend2;
	temp1->next[temp1->friend_count] =  *temp2;
	temp2->next[temp2->friend_count] =  *temp1;
	printf("Wht!\n");
	temp1->friend_count++;
	temp2->friend_count++;
	
}

void resize(struct node **arr, int size){
	*arr = (struct node *)(realloc(arr, size*sizeof(int)));
}

void disp_friends(struct node *friend){
	struct node *temp = friend->next;
	int i;
	for(i = 0; i < friend->friend_count; i++){
		printf("%s\n",friend->next[i].name);
	}
}

void delete_account(){

}

int search_username(struct node *accounts[], char a[]){
	printf("Over here in search_suer\n");
	int i;
	for(i = 0; i < main_account_count; i++){
		if(strcmp(accounts[i]->userName, a) == 0)
			return i;
	}
	return -1;
}

void list_friends(struct node **account, int index){
	int i = 0;
	while(i < account[index]->friend_count){
		printf("%s\n", account[index]->next[i].name);
		i++;
	}
}

void enter_session(struct node ** account, int index){
	char choice, friendUser[10], friendIndex = -1;
	do{
		printf("Hello %s\n", account[index]->name);
		printf("Enter 1 to list friends\n");
		printf("Enter 2 to add a friend\n");
		printf("Enter 3 to list friend count\n");
		printf("Press q to quit\n");
		scanf("%c", &choice);
		getchar();
		switch(choice){
			case '1':
				list_friends(account, index);
				break;
			case '2':
				while(friendIndex == -1){
					printf("Enter friend's username\n");
					scanf("%s",friendUser);
					getchar();
					friendIndex = search_username(account, friendUser);
				}
				add_friend(&account[index], &account[friendIndex]);
				break;
			case '3':
				printf("Your friend count is %d\n",account[index]->friend_count);
			case 'q':
				break;
		}
	}while(choice != 'q');
}


int main(void){
	struct node *accounts[8];
	char def_username[10];
	int index;
	/*accounts[main_account_count] = create_account(accounts[main_account_count]);
	accounts[main_account_count] = create_account(accounts[main_account_count]);
	accounts[main_account_count] = create_account(accounts[main_account_count]);
	printf("friend1 count = %d\n", accounts[0]->friend_count);
	printf("friend2 count = %d\n", accounts[1]->friend_count);
	printf("friend3 count = %d\n", accounts[2]->friend_count);
	add_friend(&accounts[0], &accounts[1]);
	add_friend(&accounts[0], &accounts[2]);
	disp_friends(accounts[0]);*/
	//printf("%s is a friend of %s\n",friend1->name, friend1->next[0].name);
	//printf("%s is a friend of %s\n",friend2->name, friend2->next[0].name);
	//printf("%s is a friend of %s\n",friend3->name, friend3->next[0].name);
	printf("main account count is %d\n",main_account_count);
	int choice;
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
				accounts[main_account_count] = create_account(accounts[main_account_count]);
				break;
			case 2:
				printf("Please enter username\n");
				scanf("%s", def_username);
				getchar();
				while((index = search_username(accounts, def_username)) == -1){
					printf("Please enter correct username\n");
					scanf("%s", def_username);
					getchar();
				}
				printf("Welcome %s!\n", accounts[index]->name);
				enter_session(accounts, index);

			case 3: 
				break;
			
			case 4:
				break;
			default:
				printf("Invalid choice\n");
		}
	}while(choice != 4);

}