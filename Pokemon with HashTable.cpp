#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>
#define SIZE 100

int count = 1;
struct pokemon{
	char id[50];
	char name[50];
	char element[50];
	char skill[50];
	int level;
	int damage;
	
	pokemon *next,*prev;
}*head[SIZE],*tail[SIZE];

char *generateId(char id[]){
	char temp[50];
	sprintf(temp,"%s%03d",id,count);
	count++;
	
	return temp;
}

int hashkey(char id[]){
	int key = 0;
	for(int i = 0;i<strlen(id);i++){
		key = key + id[i];
	}
	
	return key%SIZE;
}


pokemon *createNewPokemon(char id[],char name[],char element[],char skill[],int level,int damage){
	pokemon *newPokemon = (pokemon*)malloc(sizeof(pokemon));
	strcpy(newPokemon->id,id);
	strcpy(newPokemon->name,name);
	strcpy(newPokemon->element,element);
	strcpy(newPokemon->skill,skill);
	newPokemon->level = level;
	newPokemon->damage = damage;
	newPokemon->next = NULL;
	newPokemon->prev = NULL;
	
	return newPokemon;
}

void createPokemon(char id[],char name[],char element[],char skill[],int level,int damage,int key){
	pokemon *news = createNewPokemon(id,name,element,skill,level,damage);
	if(head[key] == NULL){
		head[key] = tail[key] = news;
		return;
	}
	else{
		//push tail
		tail[key]->next = news;
		news->prev = tail[key];
		tail[key] = news;
		return;
	}
}

void insertPokemon(){
	char id[50];char name[50];char element[50];char skill[50];int level;int damage;
	char validate[50];
	do{
		printf("Insert Pokemon Name[5-20] : ");
		scanf("%[^\n]",name);
		getchar();
	}while(strlen(name)<5 || strlen(name)>20);
	
	do{
		printf("Insert Pokemon Element[Fire | Water | Grass] : ");
		scanf("%[^\n]",element);
		getchar();
	}while(strcmp(element,"Fire")!=0 && strcmp(element,"Water")!=0 && strcmp(element,"Grass") != 0);
	
	do{
		printf("Insert Pokemon skill[Tackle | Dragon breath | Overgrow] : ");
		scanf("%[^\n]",skill);
		getchar();
	}while(strcmpi(skill,"Tackle")!=0 && strcmp(skill,"Dragon breath")!=0 && strcmp(skill,"Overgrow") != 0);
	
	do{
		printf("Input level[1-99] : ");
		scanf("%d",&level);
		getchar();
	}while(level < 1 || level >99);
	
	do{
		printf("Input pokemon damage[100 - 10000] : ");
		scanf("%d",&damage);
		getchar();
	}while(damage < 100 || damage > 10000);
	do{
		printf("Are you suree want to add a pokemon[yes | no]: ");
		scanf("%[^\n]",validate);
		getchar();
	}while(strcmp(validate,"yes") != 0 && strcmp(validate,"no") != 0);
	
	if(strcmp(validate,"no") == 0){
		return;
	}
	char idPok[50]="PK";
	strcpy(id,generateId(idPok));
	int key = hashkey(id);
	createPokemon(id,name,element,skill,level,damage,key);
	return;
}

void menu(){
	puts("Pokemon Book");
	puts("1. Add Pokemon");
	puts("2. View Pokemon");
	puts("3. Delete Pokemon");
	puts("4. Exit");
	printf("Choose : ");
}



void views(){
	
	for(int i = 0;i<SIZE;i++){
		printf("%d",i+1);
		if(head[i] != NULL){
			pokemon *curr = head[i];
			while(curr != NULL){
				printf("%s%s%s%s%d%d -> ",curr->id,curr->name,curr->element,curr->skill,curr->level,curr->damage);
				curr = curr->next;
	
			}//chaining ke bawah
		}
		
	}
		
}


void deletePokemon(){
	char deleteId[50];
	char s[50];
	
	printf("Delete Pokemon ID ( case insensitive ) : ");
	scanf("%[^\n]",deleteId);
	getchar();
	for(int i = 0;i<2;i++){
		deleteId[i] = toupper(deleteId[i]);
	}
	
	
	int key = hashkey(deleteId);
	if(head[key] == NULL){
		printf("data not found\n");
		return;
	}
	else{
		if(head[key] == tail[key] && strcmp(head[key]->id,deleteId)==0){
			printf("Deleted Pokemon\n");
			printf("ID : %s\n",head[key]->id);
			printf("Name: %s\n",head[key]->name);
			printf("Element: %s\n",head[key]->element);
			printf("Skill: %s\n",head[key]->skill);
			printf("Level: %d\n",head[key]->level);
			printf("Damage%d\n",head[key]->damage);
			free(head[key]);
			head[key] = NULL;
			tail[key] = NULL;
			return;
		}
		else if(strcmp(head[key]->id,deleteId) == 0){
			printf("Deleted Pokemon\n");
			printf("ID : %s\n",head[key]->id);
			printf("Name: %s\n",head[key]->name);
			printf("Element: %s\n",head[key]->element);
			printf("Skill: %s\n",head[key]->skill);
			printf("Level: %d\n",head[key]->level);
			printf("Damage%d\n",head[key]->damage);
			pokemon *remove = head[key];
			head[key] = remove->next;
			head[key]->prev = NULL;
			remove->next = NULL;
			free(remove);
			remove = NULL;
			return;
		}
		else if(strcmp(tail[key]->id,deleteId) == 0){
			printf("Deleted Pokemon\n");
			printf("ID : %s\n",tail[key]->id);
			printf("Name: %s\n",tail[key]->name);
			printf("Element: %s\n",tail[key]->element);
			printf("Skill: %s\n",tail[key]->skill);
			printf("Level: %d\n",tail[key]->level);
			printf("Damage%d\n",tail[key]->damage);
			pokemon *remove = tail[key];
			tail[key] = remove->prev;
			tail[key]->next = NULL;
			remove->prev = NULL;
			free(remove);
			remove = NULL;
			return;
		}
		pokemon *curr = head[key];
		while(curr->next != NULL && strcmp(curr->next->id,deleteId) != 0){
			curr = curr->next;
		}
		if(curr->next == NULL){
			printf("data not found");
			return;
		}
		pokemon *remove = curr->next;
		printf("Deleted Pokemon\n");
		printf("ID : %s\n",remove->id);
		printf("Name: %s\n",remove->name);
		printf("Element: %s\n",remove->element);
		printf("Skill: %s\n",remove->skill);
		printf("Level: %d\n",remove->level);
		printf("Damage%d\n",remove->damage);
		curr->next = remove->next;
		remove->next->prev = curr;
		remove->next = NULL;
		remove->prev = NULL;
		free(remove);
		remove = NULL;
	}
	
	
}

void exit(){
	puts("Selamat Tinggal");
}
int main(){
	
	char name[5]="aku";
	
	printf("%c",toupper(name[0]));
	
	int x = 0;
	
	do{
		
		do{
			
			menu();
			scanf("%d",&x);
			getchar();
			system("cls");
		}while(x<1 || x>5);
		switch(x){
			case 1:
				insertPokemon();
				break;
			case 2:
				views();
				break;
			case 3:
				deletePokemon();
				break;
			case 4:
				exit();
				break;
		}
	}while(x != 4);
	
	return 0;
}
