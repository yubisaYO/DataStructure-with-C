#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int a = 0;

struct store{
	char id[50];
	char name[50];
	char owner[50];
	char location[50];
	char type[50];
	int height;
	
	store *left, *right;
};

char *generateId(){
	char temp[50];
	sprintf(temp,"%c%c%03d",'S','T',a++);
	
	return temp;
}

store *insertStore(char id[], char name[],char owner[],char location[], char type[]){
	store *newStore=  (store*)malloc(sizeof(store));
	strcpy(newStore->id,id); 
	strcpy(newStore->name,name); 
	strcpy(newStore->owner,owner); 
	strcpy(newStore->location,id); 
	strcpy(newStore->type,type);
	newStore->height = 1;
	
	newStore->left = NULL;
	newStore->right = NULL;
	
	return newStore; 
}

store *search(store *root, char id[]){
	if(root == NULL){
		return NULL;
	}
	else if(strcmp(id,root->id) < 0){
		return search(root->left,id);
	}
	else if(strcmp(id, root->id) > 0){
		return search(root->right,id);
	}else{
		return root;
	}
}
int max(int a, int b){
	if(a < b){
		return b;
	}
	return a;
}

int getHeight(store *root){
	if(root == NULL){
		return 0;
	}
	return root->height;
}

int getBalance(store *root){
	if(root == NULL){
		return 0;
	}
	
	return getHeight(root->left) - getHeight(root->right);
}

store *leftRotate(store *root){
	store *x = root->right;
	store *sub_x = x->left;
	
	x->left = root;
	root->right = sub_x;
	
	x->height = 1 + max(getHeight(x->left),getHeight(x->right));
	root->height = 1 + max(getHeight(root->left),getHeight(root->right));
	
	return x;
}

store *rightRotate(store *root){
	store *x = root->left;
	store *sub_x = x->right;
	
	x->right = root;
	root->left = sub_x;
	
	x->height = 1 + max(getHeight(x->left),getHeight(x->right));
	root->height = 1 + max(getHeight(root->left),getHeight(root->right));
	
	return x;
}
store *insert(store *root, char id[], char name[], char owner[], char location[], char type[]){
	if(root == NULL){
		return insertStore(id,name,owner,location,type);
	}
	else if(strcmp(id, root->id) < 0){
		root->left = insert(root->left,id,name,owner,location,type);
	}
	else if(strcmp(id, root->id) > 0){
		root->right = insert(root->right,id,name,owner,location,type);
	}
	
	root->height = 1 + max(getHeight(root->left),getHeight(root->right));
	int balance = getBalance(root);
	
	if(balance > 1 && getBalance(root->left) >= 0){
		return rightRotate(root);
	}
	else if(balance < -1 && getBalance(root->right) <=0){
		return leftRotate(root);
	}
	else if(balance > 1 && getBalance(root->left) < 0){
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	else if(balance < -1 && getBalance(root->right) > 0){
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	
	return root;
}

store *insertNewStore(store *root){
	char id[50];
	char name[50];
	char owner[50];
	char location[50];
	char type[50];
	int validate = 0;
	int val1 = 0;
	strcpy(id,generateId());
//	printf("%s",id);
	val1 = 0;
	do{
		if(val1 > 0){
			printf("String name must at least 5 characters\n");
		}
		val1++;
		printf("Input Store Name : ");
		scanf("%[^\n]",name);
		getchar();
	}while(strlen(name) < 5);
	val1 = 0;
	do{
		if(val1 > 0){
			printf("Owner name must start with either 'Mr. 'or 'Mrs. '!\n");
		}
		
		validate = 0;
		printf("Input store owner name[Mr. |Mrs. ]: ");
		scanf("%[^\n]",owner);
		getchar();
		if(owner[0] == 'M' && owner[1] == 'r' && owner[2] == '.' && owner[3] ==' ' &&owner[4] !=' '&&owner[4] != NULL){
			validate = 1;
		}
		else if(owner[0] == 'M' && owner[1] == 'r' && owner[2] == 's' && owner[3] =='.' &&owner[4] ==' ' && owner[5] != ' ' && owner[5] != NULL){
			validate = 1;
		}
		val1++;
	}while(validate == 0);
	
	val1 = 0;
	do{
		if(val1 > 0){
			printf("Store location must end with 'Street'\n");
		}
		val1++;
		int val = 0;
		validate = 0;
		printf("Input store location[end with 'Street'] : ");
		scanf("%[^\n]",location);
		getchar();
		while(val < strlen(location)){
			if(location[0] ==' ' || location[strlen(location)-1] ==' '){
				validate = 2;
				break;
			}
			if(location[val] ==' '){
				validate = 1;
			}
			val++;
		}
	}while(strncmp(strrev(location),"teertS",6) != 0 || validate != 1);
	strrev(location);
	val1 = 0;
	
	do{
		if(val1 > 0){
			printf("store type mus be [Daily Needs || Clothing || F&B || Electronics]\n");
		}
		val1++;
		printf("Input store type : ");
		scanf("%[^\n]",type);
		getchar();
		
	}while(strcmpi(type,"Daily Needs") != 0 && strcmpi(type,"Clothing") !=0 && strcmpi(type,"F&B") != 0 && strcmpi(type,"Electronics") != 0 && strcmpi(type,"Kitchenware") !=0);
	
	return insert(root,id,name,owner,location, type);
}

store *deleteStore(store *root, char id[]){
	if(root == NULL){
		printf("ID not Found!\n");
		return NULL;
	}
	else if(strcmp(id,root->id) < 0){
		root->left = deleteStore(root->left,id);
	}
	else if(strcmp(id,root->id) > 0){
		root->right = deleteStore(root->right,id);
	}else{
		//ketemu
		if(root->left == NULL && root->right == NULL){
			free(root);
			root = NULL;
		}
		else if(root->left != NULL && root->right == NULL){
			store *temp = root->left;
			*root = *temp;
			free(temp);
			temp = NULL;
		}
		else if(root->left == NULL && root->right != NULL){
			store *temp = root->right;
			*root = *temp;
			free(temp);
			temp = NULL;
		}else{
			store *temp = root->left;
			while(temp->right != NULL){
				temp = temp->right;
			}
			strcpy(root->id,temp->id);
			strcpy(root->name,temp->name);
			strcpy(root->owner,temp->owner);
			strcpy(root->location,temp->location);
			strcpy(root->type,temp->type);
			
			root->left = deleteStore(root->left,temp->id);
		}
	}
	if(root == NULL){
		return NULL;
	}
	
	root->height = 1 + max(getHeight(root->left),getHeight(root->right));
	int balance = getBalance(root);
	
	if(balance > 1 && getBalance(root->left) >= 0){
		return rightRotate(root);
	}
	else if(balance < -1 && getBalance(root->right) <=0){
		return leftRotate(root);
	}
	else if(balance > 1 && getBalance(root->left) < 0){
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	else if(balance < -1 && getBalance(root->right) > 0){
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	
	return root;
	
	
}

void infix(store *root){
	if(root != NULL){
		infix(root->left);
		printf("%s - %s - %s - %s - %s\n",root->id,root->name, root->owner,root->location,root->type);
		infix(root->right);
	}
}

store *deletes(store *root){
	char id[50];
	infix(root);
	printf("Input Store ID : ");
	scanf("%[^\n]",id);
	getchar();
	if(search(root,id) == NULL){
		printf("ID NOT FOUND !");
		return root;
	}else{
		deleteStore(root,id);
	}
}

void prefix(store *root){
	if(root != NULL){
		printf("%s - %s - %s - %s - %s\n",root->id,root->name, root->owner,root->location,root->type);
		prefix(root->left);
		prefix(root->right);
	}
}



void postfix(store *root){
	if(root != NULL){
		postfix(root->left);
		postfix(root->right);
		printf("%s - %s - %s - %s - %s\n",root->id,root->name, root->owner,root->location,root->type);
	}
}

void print(store *root){
	int method;
	puts("-View Menus-");
	puts("1. Pre-Order");
	puts("2. In Order");
	puts("3. Post Order");
	printf(">> ");
	do{
		scanf("%d",&method);
		getchar();
	}while(method < 1 || method >3);
	
	if(method == 1){
		prefix(root);
	}
	else if(method ==2){
		infix(root);
	}
	else if(method ==3){
		
		postfix(root);
	}
}

store *deleteAll(store *root){
	if(search(root,root->id) == NULL){
		printf("No store yet...\n");
		return root;
	}
	char confirm[50];
	do{
		printf("All stores data will be deleted\n");
		printf("Would you like to proceed? [Yes | No] : ");
		scanf("%[^\n]",confirm);
		getchar();
	}while(strcmp(confirm,"Yes") != 0 && strcmp(confirm,"No") !=0);
	
	if(strcmp(confirm,"Yes") == 0){
		while(root != NULL){
			root = deleteStore(root,root->id);
		}
	}

	return root;
}




void menu(){
	puts("< Amasun >");
	puts("1. View all stores");
	puts("2. Insert new store");
	puts("3. Delete a store");
	puts("4. Delete all stores");
	puts("5. Exit");
}

void exit(){
	printf("-- SELAMAT TINGGAL --\n");
}
int main(){
	
	int choose = 0;
	store *root = NULL;
	do{
		do{
			menu();
			scanf("%d",&choose);
			getchar();
			system("cls");
		}while(choose < 0 || choose > 5);
		switch(choose){
			case 1:
				print(root);
				break;
			case 2:
				root = insertNewStore(root);
				break;
			case 3:
				root= deletes(root);
				break;
			case 4:
				root = deleteAll(root);
				break;
			case 5:
				exit();
				break;
		}
	}while(choose != 5);
	
	
	return 0;
}
