/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rbt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:51:15 by alilin            #+#    #+#             */
/*   Updated: 2023/02/16 18:11:30 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP
# include <iostream>
# include <memory>
# include "utility.hpp"
# include "iterator.hpp"
# include "algorithm.hpp"
# include "type_traits.hpp"

namespace ft
{
	enum color {red, black};

	template <class T>
	struct Node
	{
		typedef	T value_type;

		value_type data;

		struct Node* parent;
		struct Node* left;
		struct Node* right;

		color _color;

		Node(value_type data, Node* parent, Node* left, Node* right, color clr): data(data), parent(parent), left(left), right(right), _color(clr) {}
	};

	template <class Key, class T, class get_key_from_val, class Compare = std::less<Key>, class Alloc = std::allocator<Node<T> > >
	class RBtree
	{
	public:

		typedef T value_type;
		typedef Key key_type;
		typedef Compare key_compare;
		typedef Alloc allocator_type;

		typedef Node<value_type> node_type;
		typedef Node<value_type>* node_ptr;

		typedef std::size_t size_type;


		RBtree(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()): _comp(comp), _alloc(alloc), _size(0)
		{
			_nil = _alloc.allocate(1);
			_alloc.construct(_nil, node_type(value_type(), NULL, NULL, NULL, black));
			_root = _nil;
		}

		virtual ~RBtree()
		{
			clear_h(_root);
			_alloc.destroy(_nil);
			_alloc.deallocate(_nil, 1);
		}

		node_ptr getRoot() const
		{
			return (this->_root);
		}

		node_ptr getNil() const
		{
			return (this->_nil);
		}

		size_type getSize() const
		{
			return (this->_size);
		}

		size_type max_size() const
		{
			return (_alloc.max_size());
		}

		// find the node with the minimum key
		node_ptr minimum() const
		{
			node_ptr node = _root;
			if (node == _nil)
				return _root;
			while (node->left != _nil)
				node = node->left;
			return node;
		}

		// find the node with the maximum key
		node_ptr maximum() const
		{
			node_ptr node = _root;
			if (node == _nil)
				return _root;
			while (node->right != _nil)
				node = node->right;
			return node;
		}

		// find the node with the minimum key
		node_ptr minimum(node_ptr node) const
		{
			if (node == _nil)
				return _root;
			while (node->left != _nil)
				node = node->left;
			return node;
		}

		// find the node with the maximum key
		node_ptr maximum(node_ptr node) const
		{
			if (node == _nil)
				return _root;
			while (node->right != _nil)
				node = node->right;
			return node;
		}

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

		node_ptr insertNode(const value_type &data)
		{
		// init node with those values
		// node->data = data;
		// node->parent = null;
		// node->left = nil;
		// node->right = nil;
		// node->color = red;
		// new node must be red

			node_ptr node;
			node = _alloc.allocate(1);
			_alloc.construct(node, node_type(data, NULL, _nil, _nil, red));

			node_ptr y = NULL;
			node_ptr x = this->_root;

			while (x != _nil) // find node's natural placement
			{
				y = x;
				if (_comp(get_key_from_val()(node->data), get_key_from_val()(x->data)))
					x = x->left;
				else if (_comp(get_key_from_val()(x->data), get_key_from_val()(node->data)))
					x = x->right;
				else
				{
					_alloc.destroy(node);
					_alloc.deallocate(node, 1);
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
			if (y == NULL)
			{
				node->_color = black;
				return (this->_root);
			}
			// if the grandparent is null, simply return
			if (node->parent->parent == NULL)
			{
				return (node);
			}
			// Fix the tree colors
			fixInsert(node);
			return (node);
		}

		bool deleteNode(key_type key)
		{
			return (deleteNodeHelper(key));
		}

		// search the tree for the key k and return the corresponding node
		node_ptr searchTree(key_type k) const
		{
			return searchTreeHelper(this->_root, k);
		}

		// find the successor of a given node
		node_ptr successor(node_ptr x)
		{
			// if the right subtree is not null the successor is the leftmost node in the sright subtree
			if (x->right != _nil)
			{
				return minimum(x->right);
			}
			// else it is the lowest ancestor of x whose left child is also an ancestor of x
			node_ptr y = x->parent;
			while (y != NULL && x == y->right)
			{
				x = y;
				y = y->parent;
			}
			return y;
		}

		// find the predecessor of a given node
		node_ptr predecessor(node_ptr x)
		{
			// if the left subtree is not null the predecessor is the rightmost node in the left subtree
			if (x->left != _nil)
			{
				return maximum(x->left);
			}
			node_ptr y = x->parent;
			while (y != NULL && x == y->left)
			{
				x = y;
				y = y->parent;
			}
			return y;
		}

		void clear_h(node_ptr const &node)
		{
			clear_helper(node);
			this->_root = _nil;
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
			_alloc.destroy(node);
			_alloc.deallocate(node, 1);
			_size--;
		}

		void swap(RBtree &x)
		{
			node_ptr		tmp_root = _root;
			this->_root = x._root;
			x._root = tmp_root;

			node_ptr		tmp_nil = _nil;
			this->_nil = x._nil;
			x._nil = tmp_nil;

			size_type		tmp_size = _size;
			this->_size = x._size;
			x._size = tmp_size;
		}

	protected:

		node_ptr _root;
		node_ptr _nil;
		key_compare _comp;
		allocator_type _alloc;
		size_type _size;

		void fixInsert(node_ptr z)
		{
			node_ptr u;
			while (z->parent->_color == red)
			{
				if (z->parent == z->parent->parent->right) // parent is gp's right child
				{
					u = z->parent->parent->left; // uncle is left
					if (u->_color == red) // if uncle also red
					{
						u->_color = black;
						z->parent->_color = black;
						z->parent->parent->_color = red;
						z = z->parent->parent;
					}
					else
					{
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
				else // parent is gp's left child #mirror_case
				{
					u = z->parent->parent->right; // uncle
					if (u->_color == red)
					{
					// mirror case
						u->_color = black;
						z->parent->_color = black;
						z->parent->parent->_color = red;
						z = z->parent->parent;
					}
					else
					{
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
				{
					break;
				}
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

		bool deleteNodeHelper(key_type key)
		{
			// find the node containing key
			node_ptr z, x, y;

			z = searchTree(key);
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
			else // suppressed node had 2 children and is replaced by the minimum of it's right branch
			{
				y = minimum(z->right); // search for the minimum in the right child's branch
				y_og_color = y->_color;
				x = y->right; // x saves the minimum's right branch
				if (y->parent == z) // the minimum is z->right
					x->parent = y;
				else
				{
					rbTransplant(y, y->right); // replaces the minimum by it's right branch
					y->right = z->right; // set the new z's right side
					y->right->parent = y;
				}
				rbTransplant(z, y); // replace z by the correct value whitch is y and maintain the tree as a good search tree
				y->left = z->left; // set the new z's left side
				y->left->parent = y;
				y->_color = z->_color; // we keep the old z color
			}
			_alloc.destroy(z);
			_alloc.deallocate(z, 1);
			_size--;
			if (y_og_color == black) // fix the lost black color on x
				fixDelete(x);
			return true;
		}

		node_ptr searchTreeHelper(node_ptr node, key_type key) const
		{
			if (node == _nil)
				return _nil;
			if (key == get_key_from_val()(node->data))
				return node;
			if (node != _nil)
			{
				if (_comp(key, get_key_from_val()(node->data)))
					return searchTreeHelper(node->left, key);
				return searchTreeHelper(node->right, key);
			}
			return _nil;
		}
	};
}

#endif
