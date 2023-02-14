/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:55:11 by kennyduong        #+#    #+#             */
/*   Updated: 2023/02/14 06:03:05 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP
# include <memory>
# include "utility.hpp"
# include "iterator.hpp"
# include "algorithm.hpp"
# include "type_traits.hpp"
# include "RBNode.hpp"

namespace ft 
{
	template<typename Key, typename Value, class Compare, class Alloc = std::allocator<Value> >
	class RBTree {
		public:
			typedef Key													key_type;
			typedef Value												value_type;
			typedef Compare												key_compare;
			typedef Alloc												allocator_type;
			typedef size_t												size_type;
			typedef ptrdiff_t											difference_type;
			typedef RbNode<value_type>									Node;
			typedef Node*												node_ptr;
			typedef typename Alloc::template rebind<Node>::other		node_allocator;
			
			typedef value_type*											pointer;
			typedef const value_type*									const_pointer;
			typedef value_type&											reference;
			typedef const value_type&									const_reference;

		private:
			node_ptr													_root;
			node_ptr													_nil;
			size_type													_size;
			key_compare													_comp;
			node_allocator												_alloc;

		public:
			RBTree(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type()): _size(0), _comp(comp), _alloc(alloc) {
				_nil = _alloc.allocate(1);
				_alloc.construct(_nil, Node(value_type()));
				_nil->color = BLACK;
				_nil->left = _nil;
				_nil->right = _nil;
				_nil->parent = NULL;
				_root = _nil;
			}

			RBTree& operator=(const RBTree &x) {
				if (this != &x) {
					_root = x._root;
					_nil = x._nil;
					_size = x._size;
					_comp = x._comp;
					_alloc = x._alloc;
				}
				return *this;
			}

			~RBTree() {	clear_h(_root);	_alloc.destroy(_nil); _alloc.deallocate(_nil, 1);}

			node_ptr 					getRoot() const { return (this->_root); }
			node_ptr 					getNil() const { return (this->_nil); }
			size_type 					getSize() const { return (this->_size); }
			size_type 					max_size() const { return (_alloc.max_size()); }
			
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
				node_ptr node;
				node = _alloc.allocate(1);
				_alloc.construct(node, Node(data, RED, NULL, _nil, _nil));

				node_ptr y = NULL;
				node_ptr x = this->_root;

				while (x != _nil) // find node's natural placement
				{
					y = x;
					if (_comp(node->data, x->data))
						x = x->left;
					else if (_comp(x->data,node->data))
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
				else if (_comp(node->data, y->data)) // place the new node at it's right placement
					y->left = node;
				else
					y->right = node;
				this->_size++;
				// if new node is a root node, simply return
				if (y == NULL)
				{
					node->color = BLACK;
					return (this->_root);
				}
				// if the grandparent is null, simply return
				if (node->parent->parent == NULL)
					return (node);
				// Fix the tree colors
				fixInsert(node);
				return (node);
			}

			bool deleteNode(key_type key) {return (deleteNodeHelper(key));}

			// search the tree for the key k and return the corresponding node
			node_ptr searchTree(key_type k) const {return searchTreeHelper(this->_root, k);}

			// find the successor of a given node
			node_ptr successor(node_ptr x)
			{
				// if the right subtree is not null the successor is the leftmost node in the sright subtree
				if (x->right != _nil)
					return minimum(x->right);
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
					return maximum(x->left);
				node_ptr y = x->parent;
				while (y != NULL && x == y->left)
				{
					x = y;
					y = y->parent;
				}
				return y;
			}

			void clear_h(node_ptr const &node) {clear_helper(node); this->_root = _nil;}

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

			void swap(node_ptr const &x, node_ptr const &y)
			{
				node_ptr temp = x;
				x = y;
				y = temp;
			}

		protected:
			void fixInsert(node_ptr z)
			{
				node_ptr u;
				while (z->parent->color == RED)
				{
					if (z->parent == z->parent->parent->right) // parent is gp's right child
					{
						u = z->parent->parent->left; // uncle is left
						if (u->color == RED) // if uncle also RED
						{
							u->color = BLACK;
							z->parent->color = BLACK;
							z->parent->parent->color = RED;
							z = z->parent->parent;
						}
						else
						{
							if (z == z->parent->left) // z is left child
							{
								z = z->parent;
								right_rotate(z); // new z is old parent
							}
							z->parent->color = BLACK;
							z->parent->parent->color = RED;
							left_rotate(z->parent->parent);
						}
					}
					else // parent is gp's left child #mirror_case
					{
						u = z->parent->parent->right; // uncle
						if (u->color == RED)
						{
						// mirror case
							u->color = BLACK;
							z->parent->color = BLACK;
							z->parent->parent->color = RED;
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
							z->parent->color = BLACK;
							z->parent->parent->color = RED;
							right_rotate(z->parent->parent);
						}
					}
					if (z == _root)
						break;
				}
				_root->color = BLACK; // root is BLACK
			}

			void transplant(node_ptr u, node_ptr v) // replaces u by v
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

				while (x != this->_root && x->color == BLACK)
				{
					if (x == x->parent->left) // if x is the left child
					{
						w = x->parent->right; // w is x's right brother
						if (w->color == RED)
						{
							w->color = BLACK;
							x->parent->color = RED;
							left_rotate(x->parent); // new parent is w, old parent p became w's left child, p is still x's parent and x->parent->right bacame old w->left
							w = x->parent->right;
						}

						if (w->left->color == BLACK && w->right->color == BLACK)
						{
							w->color = RED;
							x = x->parent;
						}
						else // at least one child is RED
						{
							if (w->right->color == BLACK) // left child is RED
							{
								w->left->color = BLACK;
								w->color = RED;
								right_rotate(w);
								w = x->parent->right;
							}
							w->color = x->parent->color;
							x->parent->color = BLACK;
							w->right->color = BLACK;
							left_rotate(x->parent);
							x = _root;
						}
					}
					else // mirror case
					{
						w = x->parent->left;
						if (w->color == RED)
						{
							w->color = BLACK;
							x->parent->color = RED;
							right_rotate(x->parent);
							w = x->parent->left;
						}
						if (w->left->color == BLACK && w->right->color == BLACK)
						{
							w->color = RED;
							x = x->parent;
						}
						else
						{
							if (w->left->color == BLACK)
							{
								w->right->color = BLACK;
								w->color = RED;
								left_rotate(w);
								w = x->parent->left;
							}
							w->color = x->parent->color;
							x->parent->color = BLACK;
							w->left->color = BLACK;
							right_rotate(x->parent);
							x = _root;
						}
					}
				}
				x->color = BLACK; // root is BLACK
			}

			bool deleteNodeHelper(key_type key)
			{
				// find the node containing key
				node_ptr z, x, y;

				z = searchTree(key);
				if (z == _nil)
					return false;

				y = z; // y saves the suppressed node's placement
				Color y_color = y->color;
				if (z->left == _nil) // z only had 1 child whitch is the right one so so it get's replaced by it's child
				{
					x = z->right; // x saves the right child's branch
					transplant(z, z->right);
				}
				else if (z->right == _nil) //mirror case
				{
					x = z->left;
					transplant(z, z->left);
				}
				else // suppressed node had 2 children and is replaced by the minimum of it's right branch
				{
					y = minimum(z->right); // search for the minimum in the right child's branch
					y_color = y->color;
					x = y->right; // x saves the minimum's right branch
					if (y->parent == z) // the minimum is z->right
						x->parent = y;
					else
					{
						transplant(y, y->right); // replaces the minimum by it's right branch
						y->right = z->right; // set the new z's right side
						y->right->parent = y;
					}
					transplant(z, y); // replace z by the correct value whitch is y and maintain the tree as a good search tree
					y->left = z->left; // set the new z's left side
					y->left->parent = y;
					y->color = z->color; // we keep the old z Color
				}
				_alloc.destroy(z);
				_alloc.deallocate(z, 1);
				_size--;
				if (y_color == BLACK) // fix the lost BLACK Color on x
					fixDelete(x);
				return true;
			}

			node_ptr searchTreeHelper(node_ptr node, key_type key) const
			{
				if (node == _nil)
					return _nil;
				if (key == node->data.first)
					return node;
				if (node != _nil)
				{
					if (key < node->data.first)
						return searchTreeHelper(node->left, key);
					return searchTreeHelper(node->right, key);
				}
				return _nil;
			}
	};

} // namespace ft

#endif