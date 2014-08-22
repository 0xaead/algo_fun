class node_t{
public:
	//t2node_t* value;
	void* value;//void* makes EVERY kind of value happy!
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
	int add_after(unsigned int sn, void* const a_data)
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
			printf("[%d]%d", i, ptr->value);
			ptr=ptr->next;
		}
		printf("\n");
	}

};
class fifo : public linklist
{
public:
	void in_q(void* node)
	{
		add_after(len(),node);
	}
	void* out_q()
	{
		void* tmp;
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
