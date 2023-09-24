#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int heap[100]={0};
int element = 0;


void enter(){
	printf("Press enter to continue...");
	getchar();
}

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void up_heap(int value){
	if(value == 1){
		return;
	}
	int parent = value/2;
	if(heap[value] > heap[parent]){
		swap(&heap[value],&heap[parent]);
		up_heap(parent);
	}

}

int left(int index){
	return index*2;
}

int right(int index){
	return (index*2)+1;
}

void down_heap(int index){
	int to_index = index;
	if(left(index) <= element && heap[left(index)] > heap[to_index]){
		to_index = left(index);
	}
	
	if(right(index) <= element && heap[right(index)] > heap[to_index]){
		to_index = right(index);
	}
	
	if(to_index == index){
		return;
	}
	swap(&heap[index],&heap[to_index]);
	down_heap(to_index);
}

void insert(int value){
	element++;
	heap[element] = value;
	
	up_heap(element);
}

void insertData(){
	int data;
	do{
		printf("Input Your Data [1-100] : ");
		scanf("%d",&data);
		getchar();
	}while(data < 1 || data>100);
	insert(data);
	puts("Insert Success");
	enter();
	
}

void deleteData(){
	if(element == 0){
		puts("there is no data!");
		return;
	}
	if(element == 1){
		heap[element] = NULL;
		element--;
		return;
	}
	heap[1] = heap[element];
	heap[element] = NULL;
	element--;
	
	down_heap(1);
	return;
}

void print(){
	for(int i = 1;i<= 10;i++){
		printf("%d ",heap[i]);
	}
	puts("");
}

void exit(){
	puts("--- SELAMAT TINGGAL ---");
}

void menu(){
	puts("MAX HEAP TREE");
	puts("==============");
	puts("1. Insert");
	puts("2. View");
	puts("3. Pop");
	puts("4. Exit");
	printf("Choose : ");
}

int main(){
	
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
				insertData();
				break;
			case 2:
				print();
				break;
			case 3:
				deleteData();
				break;
			case 4:
				exit();
				break;
		}
	}while(choose !=4);
	
	
	
	return 0;
}
