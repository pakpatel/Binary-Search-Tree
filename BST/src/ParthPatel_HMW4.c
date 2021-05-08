/*
 ============================================================================
 Name        : ParthPatel_HMW4.c
 Author      : Parth Patel
 Version     :
 Copyright   : Your copyright notice
 Description : A BST that does various functions
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct node //each node in tree
{
	char word[10];
	char desc[100];
	struct node *right_child;
	struct node *left_child;
}; typedef struct node node;

struct tree //tree that points to the root
{
	int count;
	node *root;

}; typedef struct tree tree;

node* search(node *root, char find[10]) //searches the tree for a word
{
	if (root == NULL) { //word is never found or list is empty
		printf("word not found\n\n");

		return root;
	}
	else if (strcasecmp(root->word, find) == 0) { //if word is found then prints the word
		printf(" %s was found with description: %s \n\n", root->word, root->desc);
		return root;
	}
	else if (strcasecmp(find, root->word) > 0) // //if word is greater then the current root search with the right of the current root
		return search(root->right_child, find);
	else //if word is smaller then current word call search again with the new root
		return search(root->left_child, find);
}

tree* create_tree() { //initializes the tree
	tree* newtree;
	newtree = (tree*)malloc(sizeof(tree));
	if (newtree)
	{
		newtree->root = NULL;
		newtree->count = 0;
	}

	return newtree;
}


node* add_node(char newword[10], char newdesc[100]) //actually adds the node into the tree
{
	node *p;
	p = malloc(sizeof(node));
	newword = strlwr(newword);
	newdesc = strlwr(newdesc);
	strcpy(p->word, newword);
	strcpy(p->desc, newdesc);
	p->left_child = NULL;
	p->right_child = NULL;
	printf(" %s was added with description: %s \n\n", p->word, p->desc);
	return p;
}

node* insert_node(node *root, char newword[10], char newdesc[100]) //searches the tree for a place to put the new node
{

	if (root == NULL) {//if tree is empty then it becomes root
		root = add_node(newword, newdesc);
		return root;
	}
	else if (strcasecmp(newword, root->word) > 0) { //if word is greater then check the right of the current root
		root->right_child = insert_node(root->right_child, newword, newdesc);
		return root;
	}
	else //if word is smaller then check the left of the current root
		root->left_child = insert_node(root->left_child, newword, newdesc);
	return root;
}

node* find_successor(struct node *root) //finds successor after being passed the right branch of delete_node
{
	if (root == NULL)
		return NULL;
	else if (root->left_child != NULL)
		return find_successor(root->left_child);
	return root;
}


node* delete_node(node *root, char newword[10])//searches for the node to delete_node and then delete_nodes it depending on how many children it has
{

	if (root == NULL) { //tree is empty or not in the tree since it reached null
		printf("Word not found in the tree! \n\n");
		return NULL;
	}
	if (strcasecmp(newword, root->word) > 0) //if word is greater then checks right
		root->right_child = delete_node(root->right_child, newword);
	else if (strcasecmp(newword, root->word) < 0) //if word is smaller then checks left
		root->left_child = delete_node(root->left_child, newword);
	else
	{

		if (root->left_child == NULL && root->right_child == NULL) //if the node is found and has no children
		{
			printf(" %s was delete_noded with description: %s \n\n", root->word, root->desc);
			free(root);
			return NULL;
		}


		else if (root->left_child == NULL || root->right_child == NULL) //word is found and there is only one child
		{
			node *temp;
			if (root->left_child == NULL) //if there is a right child
				temp = root->right_child;
			else
				temp = root->left_child; //if there is a left child
			printf(" %s was delete_noded with description: %s \n\n", root->word, root->desc); //prints the node before deleting
			free(root);
			return temp;
		}


		else //if node is found and there are two children
		{
			node *temp = find_successor(root->right_child); //finds the successor with the from the right branch
			strcpy(root->word, temp->word); //replaces the node with the successor
			root->right_child = delete_node(root->right_child, temp->word);
		}
	}
	return root;
}

void display_tree(node *root)
{

	if (root != NULL) //makes sure that there is a tree
	{
		display_tree(root->left_child); //starts left
		printf("%-10s        %-10s \n\n", root->word, root->desc); //after printing the left child prints parent of it
		display_tree(root->right_child);// prints the right child
	}

}

int main()
{
	tree *newtree;
	newtree = create_tree();
	FILE *fp;
	 char menu_option,newword[10],newdesc[100],filename[20];
	 do{//prints menu as long as the q option is not pressed
		printf("Main Menu\n");
		printf("What would you like to do?\n");
		printf("a. Build BST from a file\n");
		printf("b. Insert a new word and description\n");
		printf("c. Delete a word\n");
		printf("d. Search for a word\n");
		printf("e. Display the tree in alphabetical order\n");
		printf("q. Press q at this menu to quit.\n\n");
		fflush(stdout);
		scanf(" %c",&menu_option);
		fflush(stdin);


		switch(menu_option){
		case 'a': //build from file

			printf("Enter the name of the file \n"); //asks the user for a file
			fflush(stdout);
			scanf("%s",filename);
			if((fp= fopen(filename,"r"))==NULL){ //makes sure file can be opened
			printf("Error opening file\n");

		}
			while(fscanf(fp,"%s\t%[^\n]", newword, newdesc)!=EOF) //if file is opened then reads line by line following the format until EOF
			{
			newtree->root=insert_node(newtree->root,newword,newdesc); //inserts each word as it is read
			}
			fclose(fp); //closes file after reading
			break;
		case 'b': //insert new word
			printf("Enter a word \n"); //asks for a word and description and then adds to tree
			fflush(stdout);
			scanf("%10s",newword);
			fflush(stdin);
			printf("Enter a description\n");
			fflush(stdout);
			scanf("%[^\n]",newdesc); //reads until end of line so that spaces and sentences can be used for description
			fflush(stdin);
			newtree->root=insert_node(newtree->root,newword,newdesc); //inserts the word making sure that it creates a root if it is empty
			printf("\n");
			break;
		case 'c': //delete_node a word
			printf("Enter a word \n"); //gets a word from the user then deletes
			fflush(stdout);
			scanf("%10s",newword);
			fflush(stdin);
			delete_node(newtree->root,newword);
			break;
		case 'd': //searches for a word
			printf("Enter a word \n"); //searches for a word and then displays it
			fflush(stdout);
			scanf("%10s",newword);
			fflush(stdin);
			search(newtree->root,newword);
			break;
		case 'e': //display the current tree
			printf("\nThe current Tree contains:\n");
			printf("Word:             Description: \n\n");
			display_tree(newtree->root);
			break;
		case 'q': //breaks out if q is pressed
			break;
		default: //if other key is pressed then the error message is printed
			printf("invalid input\n");
				break;
		}
	}while(menu_option!='q');

	return 0;
}
