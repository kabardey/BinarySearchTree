#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**This program insert the entries into a BST based on the following rule
   depths (0, 4, 8, 12,) is done with respect to name
   depths (1, 5, 9, 13,) is done with respect to surname
   depths (2, 6, 10, 14,) is done with respect to id
   depths (3, 7, 11, 15,) is done with respect to number of working-days of the student’s summer internship.
   and show traversal according to choices of user
**/


struct tree{
	int id,day,height;
	int entries;
	char name[30],surname[30];
	struct tree *left;
	struct tree *right;
};

typedef struct tree tree;

void addBST(tree **,int,char*,char*,int,int,int);
void search(tree *,int,int,int,int,char *,char *,int,int);
void printInorder(tree *);
void printPostorder(tree *);
void printPreorder(tree *);

int main(){
	
	FILE *fp;
	int id;
	int day;
	char name[30];
	char surname[30];
	
	//if the file can not be opened quit the code
	if((fp = fopen("input.txt","r")) == NULL){
		printf("Dosya acilamadi\n");
		return 0;
	}
	
	tree *root = NULL;
	int height = 0;
	int entries = 1;
	int personNumber = 0;
	
	//read the file and put the datas in BST
	while(!feof(fp)){
		personNumber++;
		fscanf(fp,"%d %s %s %d",&id,name,surname,&day);
		addBST(&root,id,name,surname,day,height,entries);
	}
	
	//choices for in,pre,post order traversal
	do{
		char option[10];
		printf("If you want inorder/postorder/preorder please enter one of these in/pre/post:\n");
		scanf("%s",&option);
		
		if(strcasecmp(option,"in") == 0){
			printInorder(root);
			break;
		}else if(strcasecmp(option,"pre")== 0){
			printPreorder(root);
			break;
		}else if(strcasecmp(option,"post") == 0){
			printPostorder(root);
			break;
		}else{
			printf("\nPlease enter correct word!\n\n");
		}	
	}while(1);
	
	
	printf("\nThe number of person is %d\n",personNumber);
	printf("\n");
	
	int select1,select2,select3,select4;
	
	//take the data that which is greater or smaller than tree's data from user for searching the tree 
	printf("For searching please enter name:\n");
	scanf("%s",&name);
	printf("For smaller or greater names please enter 0 or 1:\n");
	scanf("%d",&select1);
	
	printf("For searching please enter surname:\n");
	scanf("%s",&surname);
	printf("For smaller or greater surnames please enter 0 or 1:\n");
	scanf("%d",&select2);
	
	printf("For searching please enter id:\n");
	scanf("%d",&id);
	printf("For smaller or greater ids please enter 0 or 1:\n");
	scanf("%d",&select3);
	
	printf("For searching please enter day:\n");
	scanf("%d",&day);
	printf("For smaller or greater days please enter 0 or 1:\n");
	scanf("%d",&select4);
	
	search(root,select1,select2,select3,select4,name,surname,id,day);
	
	fclose(fp);
	
	return 0;
}

void addBST(tree **treeRoot,int id,char *name,char *surname,int day,int height,int entries){
	
	//liste boþsa
	if(*treeRoot == NULL){

		*treeRoot = malloc(sizeof(tree));
		
		if(treeRoot == NULL){
			printf("out of memory!!!");
			return;
		}
		
		//put the datas in the BST
		(*treeRoot)->id = id;
		strcpy((*treeRoot)->name,name);
		strcpy((*treeRoot)->surname,surname);
		(*treeRoot)->day = day;
		(*treeRoot)->height = height;
		(*treeRoot)->entries = entries;
		
		(*treeRoot)->left = NULL;
		(*treeRoot)->right = NULL;		
	}else{
		
		//put the name according to 0,4,8... depths
		if(height%4 == 0){
			height++;
			
			int resultName = strcmp((*treeRoot)->name,name);
			
			if(resultName < 0){
				entries = (entries*2) + 1;
				addBST(&(*treeRoot)->right,id,name,surname,day,height,entries);
				return;
			}else{
				entries = entries*2;
				addBST((&(*treeRoot)->left),id,name,surname,day,height,entries);
				return;
			}
		}

		//put the surname according to 1,5,9... depths
		if(height%4 == 1){
			height++;
			
			int resultSurname = strcmp((*treeRoot)->surname,surname);
			
			if(resultSurname < 0){
				entries = (entries*2) + 1;
				addBST(&(*treeRoot)->right,id,name,surname,day,height,entries);
				return;
			}else{
				entries = entries*2;
				addBST(&(*treeRoot)->left,id,name,surname,day,height,entries);
				return;
			}
		}
	
		//put the id according to 2,6,10... depths
		if(height%4 == 2){
			height++;
			
			if((*treeRoot)->id < id){
				entries = (entries*2) + 1;
				addBST(&(*treeRoot)->right,id,name,surname,day,height,entries);
				return;
			}else{
				entries = entries*2;
				addBST(&(*treeRoot)->left,id,name,surname,day,height,entries);
				return;
			}
		}

		//put the day according to 3,7,11... depths
		if(height%4 == 3){
			height++;
			
			if((*treeRoot)->day < day){
				entries = (entries*2) + 1;
				addBST(&(*treeRoot)->right,id,name,surname,day,height,entries);
				return;
			}else{
				entries = entries*2;
				addBST(&(*treeRoot)->left,id,name,surname,day,height,entries);
				return;
			}
		}
	}
}

void search(tree *root,int select1,int select2,int select3,int select4,char *n,char *s,int id,int day){
	char name[30];
	char surname[30];
	
	strcpy(name,n);
	strcpy(surname,s);
	int resultName = strcasecmp(root->name,name);
	int resultSurname = strcasecmp(root->surname,surname);
	
	if (root == NULL){
          return;
	}else{
		if(select1 == 0 && select2 == 0 && select3 == 0 && select4 == 0){
			
			if(resultName < 0 && resultSurname < 0 && (root->id) < id && (root->day) < day )
				printf("%d %d %d %s %s %d\n",root->height,root->entries,root->id,root->name,root->surname,root->day);
		}
		if(select1 == 1 && select2 == 0 && select3 == 0 && select4 == 0){
			
			if(resultName > 0 && resultSurname < 0 && (root->id) < id && (root->day) < day )
				printf("%d %d %d %s %s %d\n",root->height,root->entries,root->id,root->name,root->surname,root->day);
		}
		if(select1 == 0 && select2 == 1 && select3 == 0 && select4 == 0){
		
			if(resultName < 0 && resultSurname > 0 && (root->id) < id && (root->day) < day )
				printf("%d %d %d %s %s %d\n",root->height,root->entries,root->id,root->name,root->surname,root->day);
		}
		if(select1 == 0 && select2 == 0 && select3 == 1 && select4 == 0){
			
			if(resultName < 0 && resultSurname < 0 && (root->id) > id && (root->day) < day )
				printf("%d %d %d %s %s %d\n",root->height,root->entries,root->id,root->name,root->surname,root->day);
		}
		if(select1 == 0 && select2 == 0 && select3 == 0 && select4 == 1){
			
			if(resultName < 0 && resultSurname < 0 && (root->id) < id && (root->day) > day )
				printf("%d %d %d %s %s %d\n",root->height,root->entries,root->id,root->name,root->surname,root->day);
		}
		if(select1 == 1 && select2 == 1 && select3 == 0 && select4 == 0){
			
			if(resultName > 0 && resultSurname > 0 && (root->id) < id && (root->day) < day )
				printf("%d %d %d %s %s %d\n",root->height,root->entries,root->id,root->name,root->surname,root->day);
		}
		if(select1 == 1 && select2 == 0 && select3 == 1 && select4 == 0){
		
			if(resultName > 0 && resultSurname < 0 && (root->id) > id && (root->day) < day )
				printf("%d %d %d %s %s %d\n",root->height,root->entries,root->id,root->name,root->surname,root->day);
		}
		if(select1 == 1 && select2 == 0 && select3 == 0 && select4 == 1){
			
			if(resultName > 0 && resultSurname < 0 && (root->id) < id && (root->day) > day )
				printf("%d %d %d %s %s %d\n",root->height,root->entries,root->id,root->name,root->surname,root->day);
		}
		if(select1 == 0 && select2 == 1 && select3 == 1 && select4 == 0){
			
			if(resultName < 0 && resultSurname > 0 && (root->id) > id && (root->day) < day )
				printf("%d %d %d %s %s %d\n",root->height,root->entries,root->id,root->name,root->surname,root->day);
		}
		if(select1 == 0 && select2 == 1 && select3 == 0 && select4 == 1){
			
			if(resultName < 0 && resultSurname > 0 && (root->id) < id && (root->day) > day )
				printf("%d %d %d %s %s %d\n",root->height,root->entries,root->id,root->name,root->surname,root->day);
		}
		if(select1 == 0 && select2 == 0 && select3 == 1 && select4 == 1){
			
			if(resultName < 0 && resultSurname < 0 && (root->id) > id && (root->day) > day )
				printf("%d %d %d %s %s %d\n",root->height,root->entries,root->id,root->name,root->surname,root->day);
		}
		if(select1 == 1 && select2 == 1 && select3 == 1 && select4 == 0){
			
			if(resultName > 0 && resultSurname > 0 && (root->id) > id && (root->day) < day )
				printf("%d %d %d %s %s %d\n",root->height,root->entries,root->id,root->name,root->surname,root->day);
		}
		if(select1 == 1 && select2 == 1 && select3 == 0 && select4 == 1){
			
			if(resultName > 0 && resultSurname > 0 && (root->id) < id && (root->day) > day )
				printf("%d %d %d %s %s %d\n",root->height,root->entries,root->id,root->name,root->surname,root->day);
		}
		if(select1 == 1 && select2 == 0 && select3 == 1 && select4 == 1){
			
			if(resultName > 0 && resultSurname < 0 && (root->id) > id && (root->day) > day )
				printf("%d %d %d %s %s %d\n",root->height,root->entries,root->id,root->name,root->surname,root->day);
		}
		if(select1 == 0 && select2 == 1 && select3 == 1 && select4 == 1){
			
			if(resultName < 0 && resultSurname > 0 && (root->id) > id && (root->day) > day )
				printf("%d %d %d %s %s %d\n",root->height,root->entries,root->id,root->name,root->surname,root->day);
		}
		if(select1 == 1 && select2 == 1 && select3 == 1 && select4 == 1){
			
			if(resultName > 0 && resultSurname > 0 && (root->id) > id && (root->day) > day )
				printf("%d %d %d %s %s %d\n",root->height,root->entries,root->id,root->name,root->surname,root->day);
		}
	}
	if(root->left != NULL)
		search(root->left,select1,select2,select3,select4,name,surname,id,day);
	
	if(root->right != NULL)
		search(root->right,select1,select2,select3,select4,name,surname,id,day);
	
}

//Given a binary tree, print its nodes in inorder
void printInorder(tree *node){
	if (node == NULL){
		return;
	}
	printInorder(node->left);
	printf("%d %d %d %s %s %d\n", node->height,node->entries,node->id,node->name,node->surname,node->day);
	printInorder(node->right);
}

//Given a binary tree, print its nodes in postorder
void printPostorder(tree *node){
	if (node == NULL){
		return;
	}
	printPostorder(node->left);
	printPostorder(node->right);
	printf("%d %d %d %s %s %d\n", node->height,node->entries,node->id,node->name,node->surname,node->day);
}


//Given a binary tree, print its nodes in preorder
void printPreorder(tree *node){
    if (node == NULL){
          return;
	}
     printf("%d %d %d %s %s %d\n", node->height,node->entries,node->id,node->name,node->surname,node->day);  
     printPreorder(node->left);  
     printPreorder(node->right);
 }

