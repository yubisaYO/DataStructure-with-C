#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct game{
	char title[50];
	char genre[50];
	int stock;
	int height;
	game *left, *right;
};

void enter(){
	printf("Press Enter to Continue . . .");
	getchar();
}

game *insertNewGame(char title[],char genre[], int stock){
	game *newgame = (game*)malloc(sizeof(game));
	strcpy(newgame->title,title);
	strcpy(newgame->genre,genre);
	newgame->stock = stock;
	newgame->height = 1;
	
	newgame->left = NULL;
	newgame->right = NULL;
	
	return newgame;
}

int search(game *root, char title[]){
	if(root == NULL){
		return 1;
	}
	else if(strcmp(title,root->title) < 0){
		return search(root->left,title);
	}
	else if(strcmp(title,root->title) > 0){
		return search(root->right,title);
	}else{
		return 0;
	}
}

game *searchStock(game *root, char title[]){
	if(root == NULL){
		return NULL;
	}
	else if(strcmp(title,root->title) < 0){
		return searchStock(root->left,title);
	}
	else if(strcmp(title,root->title) > 0){
		return searchStock(root->right,title);
	}else{
		return root;
	}
}

int getHeight(game *root){
	if(root == NULL){
		return 0;
	}
	return root->height;
}

int getBalance(game *root){
	if(root == NULL){
		return 0;
	}
	return getHeight(root->left) - getHeight(root->right);
}

int max(int a, int b){
	if(a < b){
		return b;
	}
	return a;
}

game *leftR(game *root){
	game *x = root->right;
	game *sub_x = x->left;
	
	x->left = root;
	root->right = sub_x;
	
	x->height = 1 + max(getHeight(x->left),getHeight(x->right));
	root->height = 1 + max(getHeight(root->left),getHeight(root->right));
	
	return x;
}

game *rightR(game *root){
	game *x = root->left;
	game *sub_x = x->right;
	
	x->right = root;
	root->left = sub_x;
	
	x->height = 1 + max(getHeight(x->left),getHeight(x->right));
	root->height = 1 + max(getHeight(root->left),getHeight(root->right));
	
	return x;
}

game *insertGame(game *root, char title[], char genre[], int stock){
	if(root == NULL){
		return insertNewGame(title,genre,stock);
	}
	else if(strcmp(title, root->title) < 0){
		root->left = insertGame(root->left, title, genre, stock);
	}
	else if(strcmp(title, root->title) > 0){
		root->right = insertGame(root->right, title, genre, stock);
	}
	
	root->height = 1 + max(getHeight(root->left),getHeight(root->right));
	int balance = getBalance(root);
	
	if(balance > 1 && getBalance(root->left) >=0){
		return rightR(root);
	}
	else if(balance < -1 && getBalance(root->right) <=0){
		return leftR(root);
	}
	else if(balance > 1 && getBalance(root->left) < 0){
		root->left = leftR(root->left);
		return rightR(root);
	}
	
	else if(balance < -1 && getBalance(root->right) > 0){
		root->right = rightR(root->right);
		return leftR(root);
	}
	
	return root;
	
}

void prefix(game *root){
	if(root != NULL){
		printf("%s - %s - %d\n",root->title, root->genre, root->stock);
		prefix(root->left);
		prefix(root->right);
	}
}

game *insert(game *root){
	char title[50];
	char genre[50];
	int stock;
	
	do{
		printf("Input Game Title[5-25 Characters][Unique] : ");
		scanf("%[^\n]",title);
		getchar();
	}while(strlen(title) < 0 || search(root,title) == 0);
	do{
		printf("Input Genre Game[Action | RPG | Adventure | Card Game] : ");
		scanf("%[^\n]",genre);
		getchar();
	}while(strcmp(genre,"Action") != 0 && strcmp(genre,"RPG") != 0 && strcmp(genre,"Adventure") != 0 && strcmp(genre,"Card Game") != 0);
	do{
		printf("Input Game Stock : ");
		scanf("%d",&stock);
		getchar();
	}while(stock < 1);
	
	return insertGame(root, title, genre, stock);
}

game *deletes(game *root, char title[]){
	if(root == NULL){
		return NULL;
	}
	else if(strcmp(title, root->title) < 0){
		root->left = deletes(root->left, title);
	}
	else if(strcmp(title, root->title) > 0){
		root->right = deletes(root->right, title);
	}else{
		if(root->left == NULL && root->right == NULL){
			free(root);
			root = NULL;
		}
		else if(root->left != NULL && root->right == NULL){
			game *temp = root->left;
			*root = *temp;
			free(temp);
			temp = NULL;
		}
		else if(root->left == NULL && root->right != NULL){
			game *temp = root->right;
			*root = *temp;
			free(temp);
			temp = NULL;
		}else{
			game *temp = root->left;
			while(temp->right != NULL){
				temp = temp->right;
			}
			strcpy(root->title,temp->title);
			strcpy(root->genre,temp->genre);
			root->stock = temp->stock;
			
			root->left = deletes(root->left,temp->title);
		}
	}
	if(root == NULL){
		return NULL;
	}
	
	root->height = 1 + max(getHeight(root->left),getHeight(root->right));
	int balance = getBalance(root);
	
	if(balance > 1 && getBalance(root->left) >=0){
		return rightR(root);
	}
	else if(balance < -1 && getBalance(root->right) <=0){
		return leftR(root);
	}
	else if(balance > 1 && getBalance(root->left) < 0){
		root->left = leftR(root->left);
		return rightR(root);
	}
	
	else if(balance < -1 && getBalance(root->right) > 0){
		root->right = rightR(root->right);
		return leftR(root);
	}
	
	return root;
}

game *updateStock(game *root, char title[], int stock){
	if(root == NULL){
		printf("Data Not Found !\n");
		return NULL;
	}
	else if(strcmp(title, root->title) < 0){
		root->left = updateStock(root->left, title, stock);
	}
	else if(strcmp(title, root->title) > 0){
		root->right = updateStock(root->right, title, stock);
	}else{
		root->stock = root->stock - stock;
	}
	
	return root;
}

game *updateGame(game *root){
	char title[50];
	char type[50];
	int stock;
	printf("Input game title: ");
	scanf("%[^\n]",title);
	getchar();

	if(search(root, title) == 1){
		printf("data not found!");
		return NULL;
	}
	do{
		printf("Input update type[add|remove][case insensitive]: ");
		scanf("%[^\n]",type);
		getchar();
	}while(strcmpi(type, "add") != 0 && strcmpi(type,"remove") != 0); 
	
	if(strcmpi(type,"remove") == 0){
		game *temp = searchStock(root,title);
		do{
			printf("Input stock to remove[1 - %d] : ",temp->stock);
			scanf("%d",&stock);
			getchar();
		}while(stock < 1 || stock > temp->stock);
		
		if(stock == temp->stock){
			return deletes(root, title);
		}else{
			return updateStock(root, title, stock);
		}
	}
	
}



void menu(){
	puts("--Bluejack GShop--");
	puts("===================");
	puts("1. Insert Game");
	puts("2. View Game");
	puts("3. Update Game");
	puts("4. Exit");
}

int main(){
	
	game *root = NULL;
	int choose = 0;
	do{
		do{
			menu();
			scanf("%d",&choose);
			getchar();
			system("cls");
		}while(choose < 1 || choose >4);
		switch(choose){
			case 1: 
				root = insert(root);
				break;
			case 2:
				prefix(root);
				break;
			case 3:
				root = updateGame(root);
				break;
			case 4:
				break;
		}
	}while(choose != 4);
	
	return 0;
}
