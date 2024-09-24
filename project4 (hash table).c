#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node *next;
} Node_t;

typedef struct LinkedList {
	Node_t *head;
	Node_t *tail;
} LinkedList_t;

typedef struct HashTable {
	LinkedList_t *arrayOfLL;
	int tableSize;
	int numOfItems;
} HashTable_t;

Node_t* CreateNode(int value) {
	Node_t *newNode = (Node_t*)malloc(sizeof(Node_t));
	newNode->data = value;
	newNode->next = NULL;
	
	return newNode;
}

LinkedList_t* CreateArrayOfLists(int size) {
	LinkedList_t *newArr = (LinkedList_t*)malloc(sizeof(LinkedList_t) * size);
	for(int i = 0; i < size; i++) {
		newArr[i].head = NULL;
		newArr[i].tail = NULL;
	}
	
	return newArr;
}

HashTable_t* CreateTable(int size) {
	HashTable_t *newTable = (HashTable_t*)malloc(sizeof(HashTable_t));
	newTable->arrayOfLL = CreateArrayOfLists(size);
	newTable->tableSize = size;
	newTable->numOfItems = 0;
	
	return newTable;
}

int CalculateTableIndex(HashTable_t* table, int value) {
	int index = value % table->tableSize;
	
	return index;
}

void InsertTable(HashTable_t* table, int value) {
	//check if value exists
	Node_t *currNode = table->arrayOfLL[CalculateTableIndex(table, value)].head;
	while(currNode != NULL) {
		if(currNode->data == value) {
			return;
		}
		currNode = currNode->next;
	}
	Node_t *newNode = CreateNode(value);
	if(table->arrayOfLL[CalculateTableIndex(table, value)].head == NULL) {
		table->arrayOfLL[CalculateTableIndex(table, value)].head = newNode;
		table->arrayOfLL[CalculateTableIndex(table, value)].tail = newNode;
	}
	else {
		table->arrayOfLL[CalculateTableIndex(table, value)].tail->next = newNode;
		table->arrayOfLL[CalculateTableIndex(table, value)].tail = newNode;
	}
	
	return;
}

void RemoveTable(HashTable_t* table, int value) {
	Node_t *currNode = table->arrayOfLL[CalculateTableIndex(table, value)].head;
	while(currNode != NULL) {
		if(currNode->data == value) {
			if(currNode == table->arrayOfLL[CalculateTableIndex(table, value)].head) {
				table->arrayOfLL[CalculateTableIndex(table, value)].head = table->arrayOfLL[CalculateTableIndex(table, value)].head->next;
				//free memory
				free(currNode);
			}
			else if(currNode == table->arrayOfLL[CalculateTableIndex(table, value)].tail) {
				Node_t *newNode = table->arrayOfLL[CalculateTableIndex(table, value)].head;
				while(newNode->next != currNode) {
					newNode = newNode->next;
				}
				table->arrayOfLL[CalculateTableIndex(table, value)].tail = newNode;
				table->arrayOfLL[CalculateTableIndex(table, value)].tail->next = NULL;
				free(currNode);
			}
			else {
				Node_t *newNode = table->arrayOfLL[CalculateTableIndex(table, value)].head;
				while(newNode->next != currNode) {
					newNode = newNode->next;
				}
				newNode->next = currNode->next;
				free(currNode);
			}
			break;
		}
		currNode = currNode->next;
	}
	
	return;
}

void PrintTable(HashTable_t* table) {
	for(int i = 0; i < table->tableSize; i++) {
		printf("%d: ", i);
		Node_t *currNode = table->arrayOfLL[i].head;
		while(currNode != NULL) {
			printf("%d,", currNode->data);
			currNode = currNode->next;
		}
		printf("\n");
	}
	printf("\n");
	
	return;
}

int main() {
	int size;
	int option;
	int value;
	
	printf("Specify the size of the hash table: ");
	scanf("%d", &size);
	
	HashTable_t* table = CreateTable(size);
	
	while(option != 3) {
		printf("\nSelect the operation to perform:\n");
		printf("\n1. Insert a value\n");
		printf("2. Remove a value\n");
		printf("3. Exit\n");
		printf("\nSelect an option: ");
		scanf("%d", &option);
		
		switch(option) {
			case 1:
				printf("\nEnter a value: ");
				scanf("%d", &value);
				
				InsertTable(table, value);
				printf("\n");
				PrintTable(table);
				break;
			case 2:
				printf("\nEnter a value: ");
				scanf("%d", &value);
				
				RemoveTable(table, value);
				printf("\n");
				PrintTable(table);
				break;
			case 3:
				printf("\nGood-bye.\n");
				
				break;
			default:
				printf("\nNot a valid option.\n");
		}
	}
	
	return 0;
}