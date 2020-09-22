#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node{
	int key;
	int height;
	struct node *left;
	struct node *right;
};

struct node *newNode(int x){
	struct node *curr = (struct node *)malloc(sizeof(struct node));
	curr->key=x;
	curr->height= 1;
	curr->left= NULL;
	curr->right = NULL;
	return curr;
}

int max(int left, int right)
{
	if(right > left) return right;
	else return left;
}

int getHeight(struct node *root){
	if (root == NULL) return 0;
	else return root->height;
}

int getBF(struct node *root){
	if (root == NULL) return 0;
	return getHeight(root->left) -getHeight(root->right);
}




struct node *rightRotate(struct node *root){
	struct node *newRoot = root->left;
	struct node *B = newRoot->right;
	
	newRoot->right = root;
	root->left = B;
	
	root->height = max(getHeight(root->left),getHeight(root->right))+1;
	newRoot->height = max(getHeight(newRoot->left),getHeight(newRoot->right))+1;
	
	return newRoot;
	
}

struct node *leftRotate(struct node *root){
 	struct node *newRoot = root->right;
	struct node *B = newRoot->left;
	
	newRoot->left = root;
	root->right = B;
	
	root->height = max(getHeight(root->left),getHeight(root->right))+1;
	newRoot->height = max(getHeight(newRoot->left),getHeight(newRoot->right))+1;
	
	return newRoot;
	
 }

struct node *insert(struct node *root, int key){
	if(root==NULL) return newNode(key);
	
	if (key < root->key){
		root->left = insert(root->left,key);
	}else if (key >root->key){
		root->right = insert(root->right,key);
	}else{
		return root;
	}
	
	root->height = 1 + max(getHeight(root->left),getHeight(root->right));
	int bFactor = getBF(root);
	
	if(bFactor >1 && key<root->left->key){
		return rightRotate(root);
	}
	if(bFactor <-1 && key > root->right->key){
		return leftRotate(root);	
	}
	if(bFactor >1 && key>root->left->key){
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	if(bFactor <-1 && key <root->right->key){
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	return root;	
}  

struct node *search(struct node *root, int key){
	if(root ==NULL){
		return root;
	}
	if(key >root->key){
		return search (root->right,key);
	}else if(key< root->key){
		return search(root->left,key);
	}else{
		return root;
	}
	 
}

void printbylevel(struct node *root,int height){
	if(root == NULL) return;
	if(height == 1){
		printf("%d ", root->key);
	}else{
		printbylevel(root->left,height-1);
		printbylevel(root->right,height-1);
	}
}

void print(struct node *root){
	int h = getHeight(root);
	for(int a=1; a<=h; a++){
		printbylevel(root,a);
		printf("\n");
	}
}

int main(){
	struct node *root= NULL;
	struct node *temp;
	root = insert(root,12);
	root = insert(root,8);
	root = insert(root,18);
	root = insert(root,17);
	root = insert(root,11);
	root = insert(root,5);
	root = insert(root,4);
	root = insert(root,19);
	
	print(root);
	temp= search(root,9);
	if(temp){
		printf("Searched node=%d\n",temp->key);
	}else{
		printf("Data not found in tree");
	}
	return 0;
}
