#include<iostream>
using namespace std;

class node{
public:
	node();
	node(int value);
	~node();
	friend void gothrough(node *p);

private:
	node *left, *right; // the left child and the right child pointer
	int number; // record the node's number
	int is_threadl, is_threadr; //the flag to record whether the pointer is a thread or not

	friend class op_tree_totum;//you could access all valuables in class op_tree_totum
};

//ctor
node::node(){
	left = right = NULL;
	is_threadl = 1;
	is_threadr = 1;
}

//ctor
node::node(int value){
	number = value;
	left = right = NULL;
	is_threadl = 1;
	is_threadr = 1;
}

//dtor
node::~node(){

}

class op_tree_totum{

public:
	op_tree_totum();
	~op_tree_totum();
	void insertion(int s);
	void deletion(int s);
	void inorder_run();
	void reverseorder_run();
	int size();
	node* pre(node* p);
	node* succ(node* q);

private:
	node *root, *head, *tail;
	int num;//caculate how many nodes in the totum
};

//ctor
op_tree_totum::op_tree_totum(){
	head = new node();
	tail = new node();
	head->right = tail; //initialize the head node to connect to the tail node
	tail->left = head;
	root = NULL;
	num = 0;
}

//dtor
op_tree_totum::~op_tree_totum(){
	node *p = root;
	if(p!=NULL)	gothrough(p);
	num = 0;
	if (head != NULL)delete head;
	if (tail != NULL)delete tail;
}

void gothrough(node *p){
	if (p->is_threadl==0 && p->left!= NULL) gothrough(p->left);
	if (p->is_threadr==0 && p->right!= NULL) gothrough(p->right);
	delete p;
}

void op_tree_totum::insertion(int s){
	//TODO: fill in the code to do the insertion of the node with number s
	node* current_node = new node();
	node* compare;
	
		
	if(root==NULL){
		root=new node(s);
		head->right = root;
		tail->left = root;
		root->left = root;
		root->right = root;
		root->is_threadl=1;
		root->is_threadr=1;
	}
	else {
		
	current_node->number=s;
	compare = root;
	
	while(compare->number != current_node->number){
	if(s < (compare->number)){
		if(!(compare->is_threadl)){
			compare = compare -> left;
		}
		else {
									
			current_node->left = compare->left;

			current_node->right = compare;
			current_node->is_threadl = compare->is_threadl;
			compare->left = current_node;
			current_node->is_threadr=1;
			compare->is_threadl=0;
			
			if((current_node->number < root->number)&&(current_node->left == root))	//設定head最左下角
				head->right = current_node;
			break;
			 }	
	}
	
	else if(s > (compare->number)){
		if(!(compare->is_threadr))
			compare = compare->right;
		else{
			current_node->right = compare->right;

			current_node->left = compare;
			current_node->is_threadr = compare->is_threadr;
			compare->right = current_node;
			current_node->is_threadl=1;
			compare->is_threadr=0;
			if((current_node->number > root->number) && (current_node->right == root))
			tail->left = current_node;
			
			break;
			}
		}
	}
}

}

void op_tree_totum::deletion(int s){
	//TODO: fill in the code to do the deletion of the node with number s
	node* previous,*next;
	
	if(root==NULL){
		return;
	}
	node* parent = root;    				
	node* to_delete = root;
	
	
	
	while(to_delete->number != s){
		
		parent = to_delete;
		
		if(s < to_delete->number){
			if(!(to_delete->is_threadl))     	//小就往左搜
				to_delete = to_delete->left;
			
			else break;
		}
		else if(s > to_delete->number){			//大就往右搜啊不然咧
			if(!(to_delete->is_threadr))
				to_delete = to_delete->right;
			else break;			
		}
	}	
	
	if(to_delete->number != s)   return;
	
	//刪除樹葉YO ~~
	
	if(to_delete->is_threadl && to_delete->is_threadr){
		if(to_delete == root){				//只有一值，刪樹根
			head->right = tail;
			tail->left = head;
		}
		else if(to_delete->number < parent->number){    //刪樹葉之左邊
			parent->left = to_delete->left;
			parent->is_threadl = 1;
			
			if(head->right == to_delete)
				head->right = parent;
			}
		else {
			parent->right = to_delete->right;       //就是要刪樹葉右邊啊不然要幹嘛
			parent->is_threadr = 1;
			
			if(tail->left == to_delete)
				tail->left = parent;
		}	
		delete to_delete;
	}
	
	//刪除左右都有子樹的Node YO~~
	
	else if ((!to_delete->is_threadl) && (!to_delete->is_threadr) ) {  
		
		
		                    int tempnumber;				
		                    node *tempnode = to_delete->right;		
				   
		                    while(tempnode->is_threadl == 0){		
		                        tempnode = tempnode->left;		
		                    }						
		                    tempnumber = tempnode->number;
		                    deletion(tempnumber);
		                    to_delete->number = tempnumber;
		            }
			
		
		
	
	//刪除只有一邊有子樹的node

	else {
		if(to_delete == root){
			node* tmp;
			if(!to_delete->is_threadl){
				tmp=to_delete->left;
				root = tmp;
				if(tail->left == to_delete)
				tail->left = pre(to_delete);

				delete to_delete;
			}
			else{
				tmp=to_delete->right;
				root = tmp;
				
				if(head->right == to_delete)
				head->right = succ(to_delete);
								
				delete to_delete;
			}
		}
		
		else{
			
			if(to_delete->number < parent->number){
				if(!to_delete->is_threadl){
					parent->left = to_delete->left;
					node* sagae= pre(to_delete);
					sagae->right = parent;
					}
				else{
					parent->left = to_delete->right;
					node* tomoya = succ(to_delete);
					tomoya->left = to_delete->left;
					if(head->right == to_delete)
					head->right = succ(to_delete);
				}
			}
			else{
				if(!to_delete->is_threadr){
				parent->right = to_delete->right;
				node* sagaejan = succ(to_delete);
				sagaejan -> left = parent;			
				}
				else{
					parent->right = to_delete->left;
					node* tomokun = pre(to_delete);
					tomokun->right = to_delete->right;
									
					if(tail->left == to_delete)
					tail->left = pre(to_delete);
				}
			}
			delete to_delete;
		}
		
		
	}
	
}
	

void op_tree_totum::inorder_run(){
	//TODO: travel the tree from the head node to the tail node and output the values
	//You should NOT use stack or recurtion 
	//head 先往右  若往右路徑是實線  則往左走到底
	node* for_print;
	for_print = head->right;
	cout<<for_print->number<<" ";
	while(1){
		
	if(for_print != tail->left ){
		if(!(for_print->is_threadr)){
			for_print=for_print->right;
			while(!(for_print->is_threadl)){
				for_print = for_print->left;
			}
			cout<<for_print->number<<" ";
		}
		else {
			for_print=for_print->right;
			cout<<for_print->number<<" ";
		}
	}
	else break;	
	}

}

void op_tree_totum::reverseorder_run(){
	//TODO: travel the tree from the tail node to the head node and output the values
	//You should NOT use stack or recurtion 
	node* print;
	print = tail->left;
	cout<<print->number<<" ";
	
	while(1){
		if(print != head->right){
			if(!(print->is_threadl)){
				print=print->left;
			while(!(print->is_threadr)){
				print = print->right;
			}
			cout<<print->number<<" ";
		}
		else{
			print = print->left;
			cout<<print->number<<" ";
		}
	}
	else break;
	}
}

int op_tree_totum::size(){
	return num;
}
node* op_tree_totum::pre(node* p){
	node* pred;
	
	pred = p->left;
		while(!pred->is_threadr)
			pred = pred->right;
	return pred;
}

node* op_tree_totum::succ(node* q){
	node* succ;
	
	succ = q->right;
		while(!succ->is_threadl)
			succ = succ->left;
	return succ;
}
