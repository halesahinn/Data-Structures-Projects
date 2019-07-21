#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
///////////////////////////////////////**********   BST ********///////////////////////////////////////////////////////////////////////////////////////
struct _node
{
    char key[10] ;
    struct _node *left, *right;
    int height;
};
 typedef struct _node _nodenode;
 typedef _nodenode *_nodeptr;
 
int findHeight(struct _node*  aNode) {
    if (aNode == NULL) {
        return -1;
    }
    int lefth = findHeight(aNode->left);
    int righth = findHeight(aNode->right);

    if (lefth > righth) {
        return lefth + 1;
    } else {
        return righth + 1;
    }
}
////////////////////////////////////////////insert
 int counterBST = 0;
 void insertBST (_nodeptr *node,char key [30])
 {
 	 
  if (*node == NULL)
   {
     *node = malloc(sizeof(_nodenode));
     counterBST++;
     if (*node != NULL)
       {
         strcpy((*node)->key,key);
         (*node)->left = NULL;
         (*node)->right = NULL;
       }
     else
       printf("Can not be added \n");
   }
   else
     {
      if (strcmp((*node)->key,key) == 1)
        insertBST(&((*node)->left),key);
      else if(strcmp((*node)->key,key) == -1)
         insertBST(&((*node)->right),key);
      else
        assert(strcmp((*node)->key,key) == 0);
       // printf("duplicate\n");
     }
 }
 
 ///////////////////////////////////////////////////////print

 void printBST (_nodeptr node)
 {
  if (node != NULL)
   {
    printBST(node->left);
    printf("%s \n",node->key);
    printBST(node->right);
   }
 }

/////////////////////////////////////////////////delete

/* Given a non-empty binary search tree, return the node with minimum
   key value found in that tree. Note that the entire tree does not
   need to be searched. */
struct _node* minValueNodeBST(struct _node* node)
{
    struct _node* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}

/* Given a binary search tree and a key, this function deletes the key
   and returns the new root */
struct _node* deleteNodeBST(struct _node* root, char* key)
{
    // base case
    if (root == NULL) return root;
 
    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (strcmp(key,root->key)==-1)
        root->left = deleteNodeBST(root->left, key);
 
    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (strcmp(key,root->key)==1)
        root->right = deleteNodeBST(root->right, key);
 
    // if key is same as root's key, then This is the node
    // to be deleted
    else
    {
        // node with only one child or no child
        if (root->left == NULL)
        {
            struct _node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct _node *temp = root->left;
            free(root);
            return temp;
        }
 
        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        struct _node* temp = minValueNodeBST(root->right);
 
        // Copy the inorder successor's content to this node
        strcpy(root->key,temp->key);
 
        // Delete the inorder successor
        root->right = deleteNodeBST(root->right, temp->key);
    }
    return root;
}


//////////////////////////**********************  BST codes ends here ****************///////////////////////////////////////////////




/////////////////////////*********************** AVL codes *************************///////////////////////////////////////////////

 // C program to insert a node in AVL tree
// An AVL tree node
struct Node
{
    char* key;
    struct Node *left;
    struct Node *right;
    int height;
};
 
// A utility function to get maximum of two strings
int max(int a, int b);
 
// A utility function to get height of the tree
int height(struct Node *N)
{
    if (N == NULL){

        return 0;
   	} 
	   return N->height;
}
 
// A utility function to get maximum of two integers
int max(int a, int b)
{
	if(a<b)
	return b;
	else if(b<a)
    return a;
}
 
/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
int counterAVL; 
struct Node* newNode(char* newKey)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    counterAVL++;
    //strcpy(node->key,newKey);
    node->key = strdup(newKey);
	node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  // new node is initially added at leaf
    return(node);
}
 
// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
 
    // Return new root
    return x;
}
 
// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
 
    // Return new root
    return y;
}
 
// Get Balance factor of node N
int getBalance(struct Node *N)
{
    if (N == NULL){
     return 0;	
    }
    return height(N->left) - height(N->right);
}
 
// Recursive function to insert key in subtree rooted
// with node and returns new root of subtree.
struct Node* insert(struct Node* node, char* key)
{

    /* 1.  Perform the normal BST insertion */
    if (node == NULL)
   {
   return (newNode(key));
   }else
     {
      if (strcmp((node)->key,key) == 1)
        node->left = insert(((node)->left),key);
      else if(strcmp((node)->key,key) == -1)
         node->right = insert(((node)->right),key);
      else
        assert(strcmp((node)->key,key) == 0);
       // printf("duplicate\n");
     }
 
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),height(node->right));
 
    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(node);
    
    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && (strcmp(key,node->left->key)==-1)){

        return rightRotate(node);
 	}
    // Right Right Case
    if (balance < -1 && (strcmp(key,node->right->key)==1)){

         
		 return leftRotate(node);
 	}
    // Left Right Case
    if (balance > 1 && (strcmp(key,node->left->key)==1))
    {
        node->left =  leftRotate(node->left);

        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && (strcmp(key,node->right->key)==-1))
    {  	       
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
}
 
// A utility function to print preorder traversalof the tree.
// The function also prints height of every node
void preOrder(struct Node *root)
{
    if(root != NULL)
    {
	    preOrder(root->left);
        printf("%s\n", root->key);
        preOrder(root->right);
    }
}

/* Given a non-empty binary search tree, return the
   node with minimum key value found in that tree.
   Note that the entire tree does not need to be
   searched. */
struct Node * minValueNodeAVL(struct Node* node)
{
    struct Node* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}
 
// Recursive function to delete a node with given key
// from subtree with given root. It returns root of
// the modified subtree.
struct Node* deleteNodeAVL(struct Node* root, char* key)
{
    // STEP 1: PERFORM STANDARD BST DELETE
 
    if (root == NULL)
        return root;
 
    // If the key to be deleted is smaller than the
    // root's key, then it lies in left subtree
    if ( strcmp(key,root->key)==-1)
        root->left = deleteNodeAVL(root->left,key);
 
    // If the key to be deleted is greater than the
    // root's key, then it lies in right subtree
    else if( strcmp(key,root->key)==1)
        root->right = deleteNodeAVL(root->right, key);
 
    // if key is same as root's key, then This is
    // the node to be deleted
    else
    {
        // node with only one child or no child
        if( (root->left == NULL) || (root->right == NULL) )
        {
        struct Node *temp = root->left ? root->left : root->right;
 
            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
             *root = *temp; // Copy the contents of
                            // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            struct Node* temp = minValueNodeAVL(root->right);
 
            // Copy the inorder successor's data to this node
            strcpy(root->key,temp->key);
 
            // Delete the inorder successor
            root->right = deleteNodeAVL(root->right, temp->key);
        }
    }
 
    // If the tree had only one node then return
    if (root == NULL)
      return root;
 
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left),
                           height(root->right));
 
    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to
    // check whether this node became unbalanced)
    int balance = getBalance(root);
 
    // If this node becomes unbalanced, then there are 4 cases
 
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
 
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
 
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
 
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 
    return root;
}


///////////////////////////////////******************* AVL codes end here **********************//////////////////////////////////////////////////////




 FILE *file1, *file2;


int main()
{   
    clock_t start,end,start1,end1,start2,end2,start3,end3,start4,end4,start5,end5,start6,end6;
    double time1,time2,time3,time4,time5,time6,time7;
	char sentence[1000];
	char *word ;
    _nodeptr  rootBST1 = NULL;
    _nodeptr  rootBST2 = NULL;
    struct Node* rootAVL1 = NULL;
    struct Node* rootAVL2 = NULL;
    char ch;
    int count = 1;
    int counter = 0;

  ////////////////////////////  FOR THE INPUT 1 ////////////////////////
  
		if((file1 = fopen("input1.txt","r")) == NULL){
		printf("Input File Could Not Be Opened!\n");
	}
     else
     {
        fscanf(file1,"%s",sentence);
	    word = strtok(sentence," ,.-");
        start1 = clock();
	    insertBST(&rootBST1,word);
		while (!feof(file1)) {
		fscanf(file1,"%s ",sentence);
	    word = strtok(sentence," ,.-");
	    insertBST(&rootBST1,word);
		}
		end1 = clock();
       fclose(file1);
	  
}
	 time1 = ((double) (end1 - start1)) / CLOCKS_PER_SEC;
	 printf("Time spent in the cpu while reading and creating BST from the first input is %.15f\n",time1);

	 	if((file1 = fopen("input1.txt","r")) == NULL){
		printf("Input File Could Not Be Opened!\n");
	}
     else
     {
       fscanf(file1,"%s",sentence);
	     word = strtok(sentence," ,.-");
	     start2 = clock();
	    rootAVL1 = insert(rootAVL1,word);
		while (!feof(file1)) {
		 fscanf(file1,"%s ",sentence);
	     word = strtok(sentence," ,.-");
	    rootAVL1 = insert(rootAVL1,word);
	    }
	    end2 = clock();
       fclose(file1);
	 }
	 time2 = ((double) (end2 - start2)) / CLOCKS_PER_SEC;
	 printf("Time spent in the cpu while reading and creating AVL from the first input is %.15f\n",time2);
//////////////////////////// FOR THE INPUT 2 ///////////////////////////

    	if((file2 = fopen("input2.txt","r")) == NULL){
		printf("Input File Could Not Be Opened!\n");
	}
     else
     {
       fscanf(file2,"%s",sentence);
	     word = strtok(sentence," ,.-");
	     start3 = clock();
	    insertBST(&rootBST2,word);
		while (!feof(file2)) {
		 fscanf(file2,"%s ",sentence);
	     word = strtok(sentence," ,.-");
	    insertBST(&rootBST2,word);
     }
     end3 = clock();

       fclose(file2);
	 }
     time3 = ((double) (end3 - start3)) / CLOCKS_PER_SEC;
	 printf("Time spent in the cpu while reading and creating BST from the second input is %.15f\n",time3);
   
   
    if((file2 = fopen("input2.txt","r")) == NULL){
		printf("Input File Could Not Be Opened!\n");
	}
     else
     {
       fscanf(file2,"%s",sentence);
	     word = strtok(sentence," ,.-");
	     start4 = clock();
	    rootAVL2 = insert(rootAVL2,word);
		while (!feof(file2)) {
		 fscanf(file2,"%s ",sentence);
	     word = strtok(sentence," ,.-");
	    rootAVL2 = insert(rootAVL2,word);
     }
     end4 = clock();

       fclose(file2);
	 }
    time4 = ((double) (end4 - start4)) / CLOCKS_PER_SEC;
	 printf("Time spent in the cpu while reading and creating AVL from the second input is %.15f\n",time4);
    ////////////////////////////delete first sentence from first input BST and AVL
    start5 = clock();
	if((file1 = fopen("input1.txt","r")) == NULL){
		printf("Input File Could Not Be Opened!\n");
	}
    else
    {
    	while(!feof(file1)){
    	ch=fgetc(file1);
        if(ch==46){
        	break;
        }else if (ch==32){
        	count++;
		}		
     }
     fclose(file1);
	}
    if((file1 = fopen("input1.txt","r")) == NULL){
		printf("Input File Could Not Be Opened!\n");
	}
    else
    {
    while(counter < count){
    fscanf(file1,"%s ",sentence);
	word = strtok(sentence," ,-.");
	deleteNodeBST(rootBST1,word);
	deleteNodeAVL(rootAVL1,word);
	counter++;
	}
   }
   end5 = clock();
   time5 = ((double) (end5 - start5)) / CLOCKS_PER_SEC;
   printf("Time spent in the cpu while reading first input and finding,deleting first sentence is %.15f\n",time5);

 //////////////////////////////////////////delete first sentence from second input BST and AVL
 counter=0;
 count=1;
 start6 = clock();
 if((file2 = fopen("input2.txt","r")) == NULL){
		printf("Input File Could Not Be Opened!\n");
	}
    else
    {
    	while(!feof(file2)){
    	ch=fgetc(file2);
        if(ch==46){
        	break;
        }else if (ch==32){
        	count++;
		}		
     }
     fclose(file2);
	}
    if((file2 = fopen("input2.txt","r")) == NULL){
		printf("Input File Could Not Be Opened!\n");
	}
    else
    {
    while(counter < count){

    fscanf(file2,"%s ",sentence);
	word = strtok(sentence," ,-.");
	deleteNodeBST(rootBST2,word);
	deleteNodeAVL(rootAVL2,word);
	counter++;
	}
   }  
   end6 = clock();
   time6 = ((double) (end6 - start6)) / CLOCKS_PER_SEC;
   printf("Time spent in the cpu while reading second input and finding,deleting first sentence is %.15f\n",time6);
   printf("The memory usage of the first input BST is %d\n",(int)(pow(2,findHeight(rootBST1)) )* sizeof(char[10]));
   printf("The memory usage of the first input AVL is %d\n",(int)pow(2,rootAVL1->height) * sizeof(char*));
   printf("The memory usage of the second input BST is %d\n",(int)pow(2,findHeight(rootBST2))* sizeof(char[10])); 
   printf("The memory usage of the second input AVL is %d\n",(int)pow(2,rootAVL2->height) * sizeof(char*));
// print inoder traversal of the BST
//  printBST(rootBST1);
//	printBST(rootBST2);
//	preOrder(rootAVL1);
//	preOrder(rootAVL2);

    return 0;
}




