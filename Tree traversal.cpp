#include<iostream>
using namespace std;
class Tree{
	public:
	int data;
	Tree *left;
	Tree *right;
	
	Tree(){
		data=0;
		right=left=NULL;
	}
	
	Tree *newNode(int data){
	Tree *n=new Tree;
	n->data=data;
	n->right=NULL;
	n->left=NULL;	
	}
	
	void preOrder(Tree *ptr){
		if (ptr!=NULL){
			cout<<ptr->data<<" ";
			preOrder(ptr->left);
			preOrder(ptr->right);
		}
	}
	
	void postOrder(Tree *ptr){
		if (ptr!=NULL){
			postOrder(ptr->left);
			postOrder(ptr->right);
			cout<<ptr->data<<" ";
		}
	}
	
		void inOrder(Tree *ptr){
		if (ptr!=NULL){
			inOrder(ptr->left);
			cout<<ptr->data<<" ";
			inOrder(ptr->right);
			
		}
	}
	
};

int main(){
	Tree t;
Tree *root=	t.newNode(1);
root->left= t.newNode(2);
root->right= t.newNode(3);
root->left->left= t.newNode(5);
root->left->right= t.newNode(6);
root->right->left= t.newNode(8);
root->right->right= t.newNode(7);

t.preOrder(root);
cout<<endl;
t.postOrder(root);
cout<<endl;
t.inOrder(root);



	
}
