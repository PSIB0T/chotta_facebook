struct user{
	char userName[20];
	char name[20];
	char password[20];
	char securityQuestion[50];
	char securityAnswer[40];
	struct Post * userPost;

};

struct accounts{
	struct user presentAcc;
	struct accounts * nextAcc;
};

struct friendList{
	char userName[20];
	struct user * acc;
	struct friendList * nextFriend;
};

struct friendListLinked{
	struct friendList * friend;
	struct friendListLinked * nextFriendList;
};

struct Post{
	char post[80];
	struct Post * nextPost;
	char postTime[30];
};



void displayFriends(struct user * dumUser);
void create_account();
struct user * search_username(char * str);
void changePass(struct user * dumUser);
void addFriend(struct user *dumUser, struct user * friendAdd);
void enter_session(struct user * dumUser);
void displayAccounts();
void displayFriends(struct user * dumUser);
void deleteFriend(struct user *dumUser, struct user * friendAdd);
void deleteUser(struct user *dumUser);
void deleteAccount(struct user *dumUser);
void addPost(struct user *dumUser);
void displayPost(struct user *dumUser);
struct user * findFriend(struct user *dumUser, char * str);

struct user *nullUser;
//Linked list of users(a sub to to array of pointers)


struct friendListLinked *startFriendList;

struct accounts * start, * end;

struct Post * startPost;
