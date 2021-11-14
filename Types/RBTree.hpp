#ifndef _RBTREE_HPP_INCLUDED_
#define _RBTREE_HPP_INCLUDED_

#include "../Types/Buffer.hpp"

class RBTree
{
private:
	RBTree(const RBTree &rhs) { *this = rhs; }
	RBTree &operator = (const RBTree &rhs) { return *this; }

public:
	RBTree() { m_size = 0; m_root = NULL; }
	virtual ~RBTree() { clear(); }
  void clear();

	void add(const uint val, const ddouble time);

	ddouble getTime(const uint i) const;
	bool getBuffer(Buffer<uint> &buf) const;

private:
	struct Stack
	{
		uint val;
		Stack *next;
		Stack(const uint aval = 0, Stack *const anext = NULL)
		{
			val = aval;
			next = anext;
		}
	};
	struct RBNode
  {
    RBNode *parent;
    RBNode *left;
    RBNode *right;
		ddouble time;
		Stack *stack;
		RBNode(const ddouble atime = 0.0, Stack *const astack = NULL)
    {
      parent = NULL;
      left = NULL;
      right = NULL;
			time = atime;
			stack = astack;
    }
  };

	uint m_size;
	RBNode *m_root;

	void updateBuffer(const RBNode *node, Buffer<uint> &buf, uint &i) const;

};

#endif //_RBTREE_HPP_INCLUDED_
