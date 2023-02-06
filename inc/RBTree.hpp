/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:55:11 by kennyduong        #+#    #+#             */
/*   Updated: 2023/02/06 18:51:04 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP
# include<iostream>
# include <memory>
# include "utility.hpp"
# include "iterator.hpp"
# include "algorithm.hpp"
# include "type_traits.hpp"

namespace ft 
{
	enum Color {RED, BLACK};

	template<class T>
	struct Node {
		T				data;
		Color			color;
		Node*			parent;
		Node*			left;
		Node*			right;

		Node(const T data) : data(data), color(BLACK), parent(NULL), left(NULL), right(NULL) {}
		Node(const Node& node) : data(node.data), color(node.color), parent(node.parent), left(node.left), right(node.right) {}
		Node(const T data, Node* parent, Node* left, Node* right, Color color) : data(data), color(color), parent(parent), left(left), right(right) {}
		~Node() {}
		Node& operator=(const Node& node) {
			if(this != &node) {
				this->data = node.data;
				this->color = node.color;
				this->parent = node.parent;
				this->left = node.left;
				this->right = node.right;
			}
			return *this;
		}
	};

	// find the node with the minimum key
	template<class node_ptr>
	node_ptr minNode(node_ptr node) 
	{
		if (node == _nil)
			return _root;
		while (node->left != _nil)
			node = node->left;
		return node;
	}

	// find the node with the maximum key
	template<class node_ptr>
	node_ptr maxNode(node_ptr node) 
	{
		if (node == _nil)
			return _root;
		while (node->right != _nil)
			node = node->right;
		return node;
	}

	// find the nextNode of a given node
	template<class node_ptr>
	node_ptr nextNode(node_ptr x)	{
		// if the right subtree is not null the nextNode is the leftmost node in the sright subtree
		if (x->right != _nil)
			return minNode(x->right);
		// else it is the lowest ancestor of x whose left child is also an ancestor of x
		node_ptr y = x->parent;
		while (y != NULL && x == y->right)
		{
			x = y;
			y = y->parent;
		}
		return y;
	}

	// find the prevNode of a given node
	template<class node_ptr>
	node_ptr prevNode(node_ptr x)
	{
		// if the left subtree is not null the prevNode is the rightmost node in the left subtree
		if (x->left != _nil)
			return maxNode(x->left);
		node_ptr y = x->parent;
		while (y != NULL && x == y->left)
		{
			x = y;
			y = y->parent;
		}
		return y;
	}

	template<typename Key, typename T, typename Compare, class Alloc>
	class RBTree {
		typedef typename Alloc::template rebind<Node<T> >::other		node_allocator;

		public:
			typedef Key													key_type;
			typedef T													value_type;
			typedef value_type*											pointer;
			typedef const value_type*									const_pointer;
			typedef value_type&											reference;
			typedef const value_type&									const_reference;
			typedef size_t												size_type;
			typedef ptrdiff_t											difference_type;
			typedef Alloc												allocator_type;
			typedef Node<value_type>									node_type;
			typedef node_type*											node_ptr;
			typedef Compare												key_compare;
			
			typedef ft::bidirectional_iterator<value_type>				iterator;
			typedef ft::bidirectional_iterator<const value_type>		const_iterator;
			typedef ft::reverse_iterator<iterator>						reverse_iterator;
			typedef ft::reverse_iterator<const iterator>				const_reverse_iterator;

		private:
			node_ptr													_root;
			node_ptr													_nil;
			key_compare													_comp;
			node_allocator												_alloc;
			size_type													_size;
		
		public:
			RBtree(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()) : _comp(comp), _alloc(alloc), _size(0) {
				_nil = _alloc.allocate(1);
				_alloc.construct(_nil, node_type(value_type(), NULL, NULL, NULL, black));
				_root = _nil;
			}

			virtual ~RBtree() {	clear(_root); _alloc.destroy(_nil); _alloc.deallocate(_nil, 1);}

			node_ptr			getRoot() const { return (this->_root);}
			node_ptr			getNil() const	{ return (this->_nil);}
			size_type 			getSize() const { return (this->_size);}
			size_type 			max_size() const { return (_alloc.max_size());}

			node_ptr insertNode(const value_type &data)
			{
				node_ptr node = createNode(data, NULL, _nil, _nil, red)
				node_ptr y = NULL;
				node_ptr x = this->_root;

				while (x != _nil) // find node's natural placement
				{
					y = x;
					if (_comp(get_key_from_val()(node->data), get_key_from_val()(x->data)))
						x = x->left;
					else if (_comp(get_key_from_val()(x->data), get_key_from_val()(node->data)))
						x = x->right;
					else {
						destoryNode(node);
						return _nil;
					}
				}
				node->parent = y;
				if (y == NULL)
					this->_root = node;
				else if (_comp(get_key_from_val()(node->data), get_key_from_val()(y->data))) // place the new node at it's right placement
					y->left = node;
				else
					y->right = node;
				this->_size++;
				// if new node is a root node, simply return
				if (y == NULL)	{
					node->_color = black;
					return (this->_root);
				}
				// if the grandparent is null, simply return
				if (node->parent->parent == NULL)
					return (node);
				// Fix the tree colors
				fixInsert(node);
				return (node);
			}
			
			void 				clear(node_ptr const &node) { clear_helper(node); this->_root = _nil;}
			bool 				deleteNode(key_type key) {	return (deleteNodeHelper(key)); }
			node_ptr 			searchNode(key_type k) const { return searchNodeHelper(this->_root, k);}

			void swap(RBtree &x)
			{
				node_ptr		tmp_root = _root;
				node_ptr		tmp_nil = _nil;
				size_type		tmp_size = _size;
				
				this->_root = x._root;
				x._root = tmp_root;

				this->_nil = x._nil;
				x._nil = tmp_nil;

				this->_size = x._size;
				x._size = tmp_size;
			}

		protected:
			node_ptr createNode(const value_type& data, node_ptr parent, node_ptr left, node_ptr right, Color color) {
				node_ptr node = _alloc.allocate(1);
				_alloc.construct(node, node_type(data, parent, left, right, color));
				return node;
			}
	
			void destroyNode(node_ptr node) const {	_alloc.destroy(node); _alloc.deallocate(node, 1);}
			
			void left_rotate(node_ptr x)
			{
				node_ptr y = x->right; // y saves x's right branch

				x->right = y->left; // x's new right child is y's old left child
				if (y->left != _nil) // if y->left isn't NULL
					y->left->parent = x;
				y->parent = x->parent; // y is new x so it takes old x's parent
				if (x->parent == NULL)
					this->_root = y;
				else if (x == x->parent->left) // if x was it's parent's left child, y becomes it's new parent's left child
					x->parent->left = y;
				else
					x->parent->right = y; // mirror case
				y->left = x;
				x->parent = y;
			}

			void right_rotate(node_ptr x) // mirror case
			{
				node_ptr y = x->left;

				x->left = y->right;
				if (y->right != _nil)
					y->right->parent = x;
				y->parent = x->parent;
				if (x->parent == NULL)
					this->_root = y;
				else if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->right = x;
				x->parent = y;
			}

			void fixInsert(node_ptr z)
			{
				node_ptr u;
				while (z->parent->_color == red)
				{
					if (z->parent == z->parent->parent->right)  { // parent is gp's right child
						u = z->parent->parent->left; // uncle is left
						if (u->_color == red) // if uncle also red
						{
							u->_color = black;
							z->parent->_color = black;
							z->parent->parent->_color = red;
							z = z->parent->parent;
						}
						else {
							if (z == z->parent->left) // z is left child
							{
								z = z->parent;
								right_rotate(z); // new z is old parent
							}
							z->parent->_color = black;
							z->parent->parent->_color = red;
							left_rotate(z->parent->parent);
						}
					}
					else { // parent is gp's left child #mirror_case
						u = z->parent->parent->right; // uncle
						if (u->_color == red)	{
						// mirror case
							u->_color = black;
							z->parent->_color = black;
							z->parent->parent->_color = red;
							z = z->parent->parent;
						}
						else {
							if (z == z->parent->right)
							{
								// mirror case
								z = z->parent;
								left_rotate(z);
							}
							// mirror case
							z->parent->_color = black;
							z->parent->parent->_color = red;
							right_rotate(z->parent->parent);
						}
					}
					if (z == _root)
						break;
				}
				_root->_color = black; // root is black
			}

			void rbTransplant(node_ptr u, node_ptr v) // replaces u by v
			{
				if (u->parent == NULL)
					_root = v;
				else if (u == u->parent->left)
					u->parent->left = v;
				else
					u->parent->right = v;
				v->parent = u->parent;
			}

			// fix the rb tree modified by the delete operation
			void fixDelete(node_ptr x)
			{
				node_ptr w;

				while (x != this->_root && x->_color == black)
				{
					if (x == x->parent->left) // if x is the left child
					{
						w = x->parent->right; // w is x's right brother
						if (w->_color == red)
						{
							w->_color = black;
							x->parent->_color = red;
							left_rotate(x->parent); // new parent is w, old parent p became w's left child, p is still x's parent and x->parent->right bacame old w->left
							w = x->parent->right;
						}

						if (w->left->_color == black && w->right->_color == black)
						{
							w->_color = red;
							x = x->parent;
						}
						else // at least one child is red
						{
							if (w->right->_color == black) // left child is red
							{
								w->left->_color = black;
								w->_color = red;
								right_rotate(w);
								w = x->parent->right;
							}
							w->_color = x->parent->_color;
							x->parent->_color = black;
							w->right->_color = black;
							left_rotate(x->parent);
							x = _root;
						}
					}
					else // mirror case
					{
						w = x->parent->left;
						if (w->_color == red)
						{
							w->_color = black;
							x->parent->_color = red;
							right_rotate(x->parent);
							w = x->parent->left;
						}

						if (w->left->_color == black && w->right->_color == black)
						{
							w->_color = red;
							x = x->parent;
						}
						else
						{
							if (w->left->_color == black)
							{
								w->right->_color = black;
								w->_color = red;
								left_rotate(w);
								w = x->parent->left;
							}
							w->_color = x->parent->_color;
							x->parent->_color = black;
							w->left->_color = black;
							right_rotate(x->parent);
							x = _root;
						}
					}
				}
				x->_color = black; // root is black
			}

			void clear_helper(node_ptr const &node)
			{
				// Base case of recursion
				if (node == _nil)
					return;
				// Clear all nodes to the left and right of it
				clear_helper(node->left);
				clear_helper(node->right);
				// Clear the node itself
				destoryNode(node);
				_size--;
			}

			bool deleteNodeHelper(key_type key)
			{
				// find the node containing key
				node_ptr z, x, y;

				z = searchNode(key);
				if (z == _nil)
					return false;

				y = z; // y saves the suppressed node's placement
				color y_og_color = y->_color;
				if (z->left == _nil) // z only had 1 child whitch is the right one so so it get's replaced by it's child
				{
					x = z->right; // x saves the right child's branch
					rbTransplant(z, z->right);
				}
				else if (z->right == _nil) //mirror case
				{
					x = z->left;
					rbTransplant(z, z->left);
				}
				else // suppressed node had 2 children and is replaced by the minNode of it's right branch
				{
					y = minNode(z->right); // search for the minNode in the right child's branch
					y_og_color = y->_color;
					x = y->right; // x saves the minNode's right branch
					if (y->parent == z) // the minNode is z->right
						x->parent = y;
					else
					{
						rbTransplant(y, y->right); // replaces the minNode by it's right branch
						y->right = z->right; // set the new z's right side
						y->right->parent = y;
					}
					rbTransplant(z, y); // replace z by the correct value whitch is y and maintain the tree as a good search tree
					y->left = z->left; // set the new z's left side
					y->left->parent = y;
					y->_color = z->_color; // we keep the old z color
				}
				destroyNode(z);
				_size--;
				if (y_og_color == black) // fix the lost black color on x
					fixDelete(x);
				return true;
			}

			node_ptr searchNodeHelper(node_ptr node, key_type key) const
			{
				if (node == _nil)
					return _nil;
				if (key == get_key_from_val()(node->data))
					return node;
				if (node != _nil)
				{
					if (_comp(key, get_key_from_val()(node->data)))
						return searchNodeHelper(node->left, key);
					return searchNodeHelper(node->right, key);
				}
				return _nil;
			}
	};
	
}

#endif