#include <stdio.h>
#include <stdlib.h>
//http://en.wikipedia.org/wiki/Binary_tree

class t2node_t{
public://todo: add binary_tree as friend class
	char value;
	t2node_t* left;
	t2node_t* right;
	static unsigned int length;

	static unsigned int get_length()
	{
		return length;
	}
	static inline void inc_len()
	{
		length++;
	}
	static inline void dec_len()
	{
		length--;
	}
	t2node_t()
	{
		value = (char) ((rand()%95)+32);
		printf("%c:", value);//
	}
	~t2node_t()
	{

	}
};

class node_t{
public:
	t2node_t* value;
	//void* value;//void* makes EVERY kind of value happy!
	node_t* next;
};
class linklist{
	node_t* head;
	//node_t* tail;
	unsigned int length;

public:
	linklist()
	{
		length = 0;
	}
	unsigned int len()
	{
		return length;
	}
	node_t* iter(unsigned int sn)
	{
		node_t* ptr = head;
		for(; sn > 1 ; sn--)
			ptr=ptr->next;
		return ptr;

	}
	int add_after(unsigned int sn, t2node_t* const a_data)
	{
		if(sn > length)
			return -1;
		if(sn == 0)
		{
			node_t* to_add = new node_t;	
			to_add->value = a_data;
			to_add->next = head;
			head = to_add;
		}
		else
		{
			node_t* node_p = iter(sn);
			node_t* to_add = new node_t;	
			to_add->value = a_data;
			to_add->next = node_p->next;
			node_p->next = to_add;
		}
		length++;
		return 0;
	}
	int del_after(unsigned int sn)
	{
		if(sn > length-1)
			return -1;//out bound!

		if(sn == 0)
		{
//			printf("\n[%d]%c", sn, head->value);
			node_t* tmp_ptr = head->next;
			delete head;
			head = tmp_ptr;
		}
		else
		{
			node_t* node_p = iter(sn);
			//printf("\n[%d]%c", sn, node_p->next->value);
			node_t* tmp_ptr = node_p->next->next;
			delete node_p->next;
			node_p->next = tmp_ptr;
		}
		length--;
		return 0;
	}
	void traverse()
	{
		node_t* ptr = head;
		if(length == 0)
			printf("empty object!");;
		for(unsigned int i = 0; i < length; i++)
		{
			printf("[%d]%c", i, ptr->value);
			ptr=ptr->next;
		}
		printf("\n");
	}

};
class fifo : public linklist
{
public:
	void in_q(t2node_t* node)
	{
		add_after(len(),node);
	}
	t2node_t* out_q()
	{
		t2node_t* tmp;
		if(iter(0)!=NULL)
		{
			tmp = iter(0)->value;
			del_after(0);
		}
		else
		{
			tmp = NULL;
		}
		return tmp;
	}
};


class binary_tree{
	t2node_t* root;

public:
	binary_tree()
	{

	}
	unsigned int len()
	{
		return t2node_t::get_length();
	}
	t2node_t* iter(unsigned int sn, t2node_t* ptr)
	{
		//ASSERT(ptr= NULL);
		for(; sn > 1 ; sn--)
			ptr=ptr->left;
		return ptr;
	}
	void construct()
	{
		//add a root first
		root = new t2node_t;
		root->left = new t2node_t;
		//then randomly add leaves
		ctr_pre_order(root->left );
				
		root->right = new t2node_t;
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
			parent->right = NULL;
			ctr_pre_order(parent->left);
		}
		else if(decision == 2)
		{
			parent->left = NULL;
			parent->right = new t2node_t;
			ctr_pre_order(parent->right);
		}
		else
		{
			parent->left = new t2node_t;
			ctr_pre_order(parent->left);
			parent->right = new t2node_t;
			ctr_pre_order(parent->right);
		}
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
			if( (outptr = levelq.out_q()) != NULL)
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
