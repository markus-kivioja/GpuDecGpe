#include "RBTree.hpp"

void RBTree::clear()
{
	RBNode *curr = m_root;
	while(curr)
	{
		if(curr->left)
		{
			RBNode *next = curr->left;
			curr->left = NULL;
			curr = next;
		}
		else if(curr->right)
		{
			RBNode *next = curr->right;
			curr->right = NULL;
			curr = next;
		}
		else
		{
			RBNode *parent = curr->parent;
			Stack *stack = curr->stack;
			while(stack)
			{
				Stack *next = stack->next;
				delete stack;
				stack = next;
			}
			delete curr;
			curr = parent;
		}
	}
	m_root = NULL;
	m_size = 0;
}


void RBTree::add(const uint val, const ddouble time)
{
	m_size++;
	if(m_root == NULL)
	{
		m_root = new RBNode(time, new Stack(val));
		return;
	}

	const ddouble EPSILON = 1e-13;
	RBNode *curr = m_root;
	while(true)
	{
		if(time < curr->time - EPSILON)
		{
			if(curr->left) curr = curr->left;
			else
			{
				curr->left = new RBNode(time, new Stack(val));
				curr->left->parent = curr;
				break;
			}
		}
		else if(time > curr->time + EPSILON)
		{
			if(curr->right) curr = curr->right;
			else
			{
				curr->right = new RBNode(time, new Stack(val));
				curr->right->parent = curr;
				break;
			}
		}
		else
		{
			curr->stack = new Stack(val, curr->stack);
			break;
		}
	}
}

ddouble RBTree::getTime(const uint i) const
{
	if(i >= m_size) return 0.0;

	RBNode *curr = m_root;
	while(curr->left) curr = curr->left;

	uint j = 0;
	ddouble time = curr->time;
	while(true)
	{
		if(curr->left && time < curr->left->time) curr = curr->left;
		else if(time < curr->time)
		{
			time = curr->time;
			Stack *stack = curr->stack;
			while(stack)
			{
				if(i == j) return time;
				stack = stack->next;
				j++;
			}
		}
		else if(curr->right && time < curr->right->time) curr = curr->right;
		else if(curr->parent) curr = curr->parent;
		else return time;
	}
}

bool RBTree::getBuffer(Buffer<uint> &buf) const
{
	uint i = 0;
	buf.resize(m_size);
	if(m_root) updateBuffer(m_root, buf, i);
	return (i == m_size);
}

void RBTree::updateBuffer(const RBNode *node, Buffer<uint> &buf, uint &i) const
{
	if(node->left) updateBuffer(node->left, buf, i);
	Stack *stack = node->stack;
	while(stack)
	{
		buf[i++] = stack->val;
		stack = stack->next;
	}
	if(node->right) updateBuffer(node->right, buf, i);
}


