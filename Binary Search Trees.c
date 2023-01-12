#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

/* COP 3502C Final Term Assignment 2 
This program is written by: Christian Samson */

struct node 
{
  struct node* left;
  struct node* right;
  char* name;
};

struct node* create(char* name)
{
  struct node* ptr;
 
  ptr = (struct node*)malloc(sizeof(struct node));
  ptr->left = NULL;
  ptr->right = NULL;
  ptr->name = (char*)malloc(sizeof(char)*100);
  strcpy(ptr->name,name);
  
  return ptr;
}

struct node* insert(char *name,struct node* root) 
{

  if(root == NULL)
  {
    struct node* x = create(name); 
    return x;
  }

  else 
  {
    int c;
     c = strcmp(name,root->name);
     if(c <= 0)
     {
      root->left = insert(name,root->left);
     }
     if(c > 0)
     {
      root->right = insert(name,root->right);
     }
  }
  return root;
}

void inorder(struct node* root,FILE* ptr)
{
  
  if(root == NULL)
  {
    return;
  }
  else
  {
    inorder(root->left,ptr);
    fprintf(ptr,"%s ",root->name);
    inorder(root->right,ptr);
  }
}

void preorder(struct node* root,FILE* ptr)
{
  if(root == NULL)
  {
    return;
  }
  else 
  {
    fprintf(ptr,"%s ",root->name);
    preorder(root->left,ptr);
    preorder(root->right,ptr);
  }
}

void postorder(struct node* root,FILE* ptr)
{
  if(root == NULL)
  {
    return;
  }
  else
  {
   postorder(root->left,ptr);
   postorder(root->right,ptr);
   fprintf(ptr,"%s ",root->name);
    
  }
}

int total_characters(struct node* root)
{
  if(root == NULL)
  {
    return 0;
  }
  else 
  {
    int l;
    l = total_characters(root->left);
    int r;
    r = total_characters(root->right);
    int length;
    length = strlen(root->name);

    return length + l + r;
  }
}

int height(struct node* root)
{
  if(root == NULL)
  {
    return -1;
  }
  else
  {
    int l;
    l = height(root->left);
    int r;
    r = height(root->right);

    if(l < r)
    {
      return 1 + r;
    }
    else
    {
      return l + 1;
    }
  }
}

int is_balanced(struct node* root)
{
  int l = height(root->left);
  int r = height(root->right);
  
  if( l-r == -1 || l-r == 0 || l-r == 1) 
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

struct node* search_name(struct node* root,char * name)
{
  if (root == NULL)
  {
    return NULL;
  }
  int c = strcmp(root->name,name);

  if(c < 0)
  {
   return  search_name(root->right,name);
  }
  if(c > 0)
  {
    return search_name(root->left,name);
  }
  else 
  {
    return root;
  }
}

int search(struct node* root, char* name)
{
  if(search_name(root,name) == NULL)
  {
    return 0;
  }
  else 
  {
    return 1;
  }
}

int size(struct node* root)
{
  if(root == NULL)
  {
    return 0;
  }
  else
  {
    return 1+ size(root->left) + size(root->right);
  }
}

int count_before(struct node* root,char* name)
{
  if (search_name(root,name) == 0)
  {
    return 0;
  }
  if(root == NULL)
  {
    return 0;
  }
  else
  {
   int c = strcmp(root->name,name);

   if(c < 0)
   {
     return  1+ count_before(root->right,name) +size(root->left);
   }
   if(c > 0)
   {
     return count_before(root->left,name);
   }
   else 
   {
     return size(root->left);
   }
  }
}

struct node* get_rightmost(struct node* root)
{
  while(root->right != NULL)
  {
    root = root->right;
  }
  return root;
}

struct node* delete(struct node* root, char* name)
{

  if(root == NULL)
  {
    return NULL;
  }
  int x;
   x = strcmp(root->name,name);
  if(x < 0)
  {
    root->right = delete(root->right,name);
  }
  else if(x > 0)
  {
    root->left = delete(root->left,name);
  }
  else
  {
    if(root->left == NULL && root->right == NULL)
    {
      free(root);
      return NULL;
    }
    if(root->left == NULL && root->right != NULL)
    {
      struct node* temp;
      temp = root->right;
      free(root);
      return temp;
    }
    if(root->left != NULL && root->right == NULL)
    {
      struct node* temp;
      temp = root->left;
      free(root);
      return temp;
    }
    else
    {
      struct node* temp;
      temp = get_rightmost(root->left);
      strcpy(root->name,temp->name);
      root->left = delete(root->left,temp->name);
      
      return root;
    }
  }
  return root;
}

int main(void) {
  int n,s,d;
  FILE *ptr;
  ptr = fopen("in.txt","r");
  fscanf(ptr,"%d %d %d",&n,&s,&d);

  struct node* root = NULL;
  int i = 0;
  for(i = 0; i<n; i++)
  {
    char names[100];
    fscanf(ptr,"%s",names);

    root = insert(names,root);
  }
  FILE* outptr;
  outptr = fopen("out.txt","w");
  fprintf(outptr,"Pre Order: ");
  preorder(root,outptr);
  fprintf(outptr,"\nIn Order: ");
  inorder(root,outptr);
  fprintf(outptr,"\nPost Order: ");
  postorder(root,outptr);
  fprintf(outptr,"\nTotal Characters: %d\n",total_characters(root));
  fprintf(outptr,"Height left = %d, Height right = %d. ",height(root->left),height(root->right));
 
   if(is_balanced(root) == 1)
   {
     fprintf(outptr,"The tree is balanced.\n");
   }
   else 
   {
     fprintf(outptr,"The tree is inbalanced.\n");
   }

  fprintf(outptr,"Search Phase:\n");
  char names[100];
  
  for(i = 0; i<s; i++)
  {
    fscanf(ptr,"%s",names);
    fprintf(outptr,"%s: ",names);
    if(search(root,names) == 1)
    {
      fprintf(outptr,"Found, Items before: %d\n",count_before(root,names));
    }
    else
    {
      fprintf(outptr,"Not Found,Items before: 0\n");
    }
  }
 

  fprintf(outptr,"Delete Phase:");
  for(i = 0; i < d; i++)
  {
    char names[100];
    fscanf(ptr,"%s",names);
    fprintf(outptr,"\n%s: Deleted",names);
    root = delete(root,names);
  }
  fprintf(outptr,"\nIn Order: ");
  inorder(root,outptr);
  fprintf(outptr,"\nTotal Characters: %d",total_characters(root));
   
    
  


  fclose(outptr);
  return 0;
}


