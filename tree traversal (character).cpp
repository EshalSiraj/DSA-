#include<iostream>
using namespace std;
class Tree{
	public:
	char data;
	Tree *left;
	Tree *right;
	
	Tree(){
		data=' ';
		right=left=NULL;
	}
	
	Tree *newNode(char data){
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
Tree *root=	t.newNode('A');
root->left= t.newNode('B');
root->right= t.newNode('C');
root->left->left= t.newNode('D');
root->left->right= t.newNode('E');
root->right->left= t.newNode('F');
root->right->right= t.newNode('G');

t.preOrder(root);
cout<<endl;
t.postOrder(root);
cout<<endl;
t.inOrder(root);



	
}
