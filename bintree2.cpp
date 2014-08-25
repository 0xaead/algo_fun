#include <stdio.h>
#include <stdlib.h>
#include "..\tree\fifo.h"

//ref http://en.wikipedia.org/wiki/Binary_tree 
//http://www.cs.cmu.edu/~adamchik/15-121/lectures/Trees/trees.html
//http://www.cs.princeton.edu/~rs/AlgsDS07/08BinarySearchTrees.pdf

class t2node_t{
public://todo: add binary_tree as friend class
	char value;
	t2node_t* left;
	t2node_t* right;
	t2node_t* parent;
	static unsigned int size;

	static unsigned int get_size()
	{
		return size;
	}
	static inline void inc_size()
	{
		size++;
	}
	static inline void dec_size()
	{
		size--;
	}
	t2node_t()
	{
		value = (char) ((rand()%95)+32);
		//practically, a value should be gotten outside. 
		//it implies that a t2node_t(type* const value) is better a t2node_t()!
		printf("%c:", value);//
	}
	~t2node_t()
	{

	}
};

class binary_tree{
	t2node_t* root;

public:
	binary_tree()
	{

	}
	unsigned int size()
	{
		return t2node_t::get_size();
	}
	void construct()
	{
		//add a root first
		root = new t2node_t;
		root->parent = NULL;
		root->left = new t2node_t;
		root->left->parent = root;
		//then randomly add leaves
		ctr_pre_order(root->left );
				
		root->right = new t2node_t;
		root->right->parent = root;
		//then randomly add leaves
		ctr_pre_order(root->right);
	}
	void ctr_pre_order(t2node_t* parent)
	{
		unsigned int decision = (unsigned int) (rand()%4);
		//printf("/%d/", decision);
		if(decision== 0)
		{		
			parent->left = NULL;
			parent->right = NULL;
			return;
		}
		else if(decision == 1)
		{
			parent->left = new t2node_t;
			parent->left->parent = root;
			parent->right = NULL;
			ctr_pre_order(parent->left);
		}
		else if(decision == 2)
		{
			parent->left = NULL;
			parent->right = new t2node_t;
			parent->right->parent = root;
			ctr_pre_order(parent->right);
		}
		else
		{
			parent->left = new t2node_t;
			parent->left->parent = root;
			ctr_pre_order(parent->left);
			parent->right = new t2node_t;
			parent->right->parent = root;
			ctr_pre_order(parent->right);
		}
	}
	void construct_search_tree()
	{
		//it is better to get values from a (sorted) linked list, not a randomized generated value.		
		root = new t2node_t;//add a root first
		t2node_t* succ = new t2node_t;
		
		//then randomly add leaves
		ctr_search_tree(succ);				
	}
	void ctr_search_tree(t2node_t* succ)
	{
		//todo, 
	}

	int insert_after(unsigned int sn, t2node_t* const to_add)
	{

		return 0;
	}
	int del_after(unsigned int sn)
	{

		return 0;
	}
	void traverse()
	{
		iter_inorder(root);
		printf("\n\n");
		iter_preorder(root);
		printf("\n\n");
		iter_postorder(root);
		printf("\n\n");
		level_order(root);
	}
private:
	void iter_preorder(t2node_t* parent)
	{
		printf("%c:",parent->value);
		if(parent->left != NULL)
		{		
			iter_preorder(parent->left);
		}
		
		if(parent->right != NULL)
		{
			iter_preorder(parent->right);
		}
		
		return;
		
	}
	void iter_inorder(t2node_t* parent)
	{
		
		if(parent->left != NULL)
		{		
			iter_inorder(parent->left);
		}
		
		printf("%c:",parent->value);
		
		if(parent->right != NULL)
		{
			iter_inorder(parent->right);
		}

		return;
	}
	void iter_postorder(t2node_t* parent)
	{
		
		if(parent->left != NULL)
		{		
			iter_inorder(parent->left);
		}		
		
		if(parent->right != NULL)
		{
			iter_inorder(parent->right);
		}

		printf("%c:",parent->value);
		return;
	}
	void level_order(t2node_t* parent)
	{
		fifo levelq;
		t2node_t* outptr;
		unsigned int current_ctr=0, next_ctr=0;
		levelq.in_q(parent);
		current_ctr++;
		while(levelq.len() > 0 )
		{
			if( (outptr = (t2node_t*)levelq.out_q()) != NULL)
			{
				printf("%c:",outptr->value);

				if(outptr->left != NULL)
				{
					/* fifo_node = new node_t ;
					fifo_node->value = parent->left;
					fifo_node->next = NULL;
					levelq.in_q(fifo_node); -- not good to operate node by a queue, value oriented is NICE!!*/
					levelq.in_q(outptr->left);
					next_ctr++;
				}
				else
					levelq.in_q(NULL);

				if(outptr->right != NULL)
				{
					levelq.in_q(outptr->right);
					next_ctr++;
				}
				else
					levelq.in_q(NULL);

				current_ctr--;
				if(current_ctr==0)
				{
					printf("\n");
					current_ctr = next_ctr;
					next_ctr = 0;
				}
			}
			else
				printf("%\176");
		}

	}

};

void main()
{
	binary_tree b_tree;
	b_tree.construct();
	printf("\n\n");
	b_tree.traverse();
	
	printf("[d%]%c");

}
