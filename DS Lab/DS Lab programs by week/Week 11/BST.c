// Program to create and print level order traversals, iterative preorder, search, delete of BST

#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

typedef struct tnode
{
	int data;
	struct tnode *lchild;
	struct tnode *rchild;
} TNode;

TNode * getNode()
{
	TNode *root = (TNode *) malloc (sizeof(TNode));
	root->lchild = root->rchild = NULL;
	return root;
}

TNode *insertBST (TNode *root, int ele)
{
	if (root == NULL)
	{
		root = getNode();
		root->data = ele;
		return root;
	}
	else if (ele < root->data)
	{
		root->lchild = insertBST(root->lchild, ele);
	}
	else if (root->data < ele)
	{
		root->rchild = insertBST(root->rchild, ele);
	}
	return root;
}

int search (TNode *root, int item)
{
	if (root == NULL)
	{
		return 0;
	}
	else if (root->data == item)
	{
		return 1;
	}
	else if (item < root->data)
	{
		search(root->lchild, item);
	}
	else if (root->data < item)
	{
		search(root->rchild, item);
	}
}

void levelOrder (TNode *root)
{
	TNode *q[SIZE];
	TNode *cur;
	int front = 0;
	int rear = -1;
	q[++rear] = root;
	while (front <= rear)
	{
		cur = q[front++];
		printf("%d\t", cur->data);
		if (cur->lchild != NULL)
		{
			q[++rear] = cur->lchild;
		}
		if (cur->rchild != NULL)
		{
			q[++rear] = cur->rchild;
		}
	}
	printf("\n");
}

void preorderIter(TNode *root)
{
	TNode *cur;
	TNode *s[20];
	int top = -1;
	
	if (root == NULL)
	{
		printf("Empty tree\n");
		return;
	}
	cur = root;
	for (;;)
	{
		while (cur != NULL)
		{
			printf("%d\t", cur->data);
			s[++top] = cur;
			cur = cur->lchild;
		}
		if (top != -1)
		{
			cur = s[top--];
			cur = cur->rchild;
		}
		else
			return;
	}
	printf("\n");
}

TNode *delete (TNode *root, int item) 
{
	if (root == NULL)
		return root;
	
	if (item < root->data)
		root->lchild = delete(root->lchild, item);
	else if (item > root->data)
		root->rchild = delete(root->rchild, item);
	
	else 
	{
		if (root->lchild == NULL) 
		{
			TNode *temp = root->rchild;
			free(root);
			return temp;
		}
		else if (root->rchild == NULL) 
		{
			TNode *temp = root->lchild;
			free(root);
			return temp;
		}
		
		TNode *temp = root;
		while (temp->lchild != NULL)
			temp = temp->lchild;
		root->data = temp->data;
		root->rchild = delete(root->rchild, temp->data);
	}
	return root;
}

int main()
{
	int n, ch, i, el, delEle, x;
  	TNode *root;
  	root = NULL;
  	while (1)
    {
      	printf("1 to insert, 2 to list level order traversals, 3 to iterative preorder traversals, 4 to delete, 5 to search, 6 to exit\n");
      	scanf(" %d", &ch);
      	switch(ch)
		{
			case 1:
	  			printf("Enter node\n");
	  			scanf(" %d", &el);
	  			root = insertBST(root, el);
	 			break;
			case 2:
				levelOrder(root);
				break;
			case 3:
				preorderIter(root);
				break;
			case 4:
				printf("Enter item to be deleted\n");
				scanf("%d", &delEle);
				TNode *element = getNode();
				element->data = search(root, delEle);
				if (element != NULL) 
				{
					delete(root, delEle);
				}
				else
					printf("%d is not present in the tree.", delEle);
				break;
			case 5:
				printf("Enter item to be searched\n");
				scanf("%d", &delEle);
				x = search(root, delEle);
				if (x == 1)
					printf("Item found\n");
				else
					printf("item does not exist in tree\n");
				break;
			case 6:
				exit(0);
		}
	}
	return 0;
}
