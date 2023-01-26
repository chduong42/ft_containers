/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:55:11 by kennyduong        #+#    #+#             */
/*   Updated: 2023/01/26 19:42:10 by chduong          ###   ########.fr       */
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
		T				value;
		Color			color;
		Node*			parent;
		Node*			left;
		Node*			right;

		Node(const T value) : value(value), color(RED), parent(nullptr), left(nullptr), right(nullptr) {}
		Node(const Node& node) : value(node.value), color(node.color), parent(node.parent), left(node.left), right(node.right) {}
		~Node() {}
		Node& operator=(const Node& node) {
			if(this != &node) {
				this->value = node.value;
				this->color = node.color;
				this->parent = node.parent;
				this->left = node.left;
				this->right = node.right;
			}
			return *this;
		}
	};

	template<typename Key, typename T, typename Compare, class Alloc>
	class RBTree {
		typedef typename Alloc::template rebind<Node<T> >::other		node_allocator;

		public:
			typedef Key											key_type;
			typedef T											value_type;
			typedef value_type*									pointer;
			typedef const value_type*							const_pointer;
			typedef value_type&									reference;
			typedef const value_type&							const_reference;
			typedef size_t										size_type;
			typedef ptrdiff_t									difference_type;
			typedef Alloc										allocator_type;
			typedef Node<T>										node;
			typedef Node<T>*									nodePtr;

			typedef RBTree_iterator<value_type>					iterator;
			typedef RBTree_iterator<const value_type>			const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const iterator>		const_reverse_iterator;

		private:
			nodePtr							_root;
			nodePtr							_nil;
			size_type						_size;
			Compare							_comp;
			allocator_type					_alloc;
		
		// algorithm Well Balanced Binary Search Tree (RED-BLACK TREE)
		void leftRotate(nodePtr x) {
			nodePtr y = x->right;
			x->right = y->left;
			if (y->left != _nil)
				y->left->parent = x;
			y->parent = x->parent;
			if (x->parent == _nil)
				_root = y;
			else if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		}
		
		void rightRotate(nodePtr x) {
			nodePtr y = x->left;
			x->left = y->right;
			if (y->right != _nil)
				y->right->parent = x;
			y->parent = x->parent;
			if (x->parent == _nil)
				_root = y;
			else if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
			y->right = x;
			x->parent = y;
		}
		
		public:
		// Constructor
			explicit RBTree(const Compare& comp = Compare(), const allocator_type& alloc = allocator_type())
			: _root(nullptr), _nil(nullptr), _size(0), _comp(comp), _alloc(alloc) {
				_nil = new Node<T>(value_type());
				_nil->color = BLACK;
				_root = _nil;
			}

			RBTree(const RBTree& x) {*this = x;}

			~RBTree() {
				clear();
				delete _nil;
			}

			RBTree& operator=(const RBTree& x) {
				if (this != &x) {
					clear();
					insert(x.begin(), x.end());
				}
				return *this;
			}
			
			void clear() {
				while (_root != _nil)
					erase(_root->value.first);
			}
		
			void insert(nodePtr z)
			{
				while (z->parent->color == RED) {
					if (z->parent == z->parent->parent->left) {
						nodePtr y = z->parent->parent->right;
						if (y->color == RED) {
							z->parent->color = BLACK;
							y->color = BLACK;
							z->parent->parent->color = RED;
							z = z->parent->parent;
						} else {
							if (z == z->parent->right) {
								z = z->parent;
								leftRotate(z);
							}
							z->parent->color = BLACK;
							z->parent->parent->color = RED;
							rightRotate(z->parent->parent);
						}
					} else {
						nodePtr y = z->parent->parent->left;
						if (y->color == RED) {
							z->parent->color = BLACK;
							y->color = BLACK;
							z->parent->parent->color = RED;
							z = z->parent->parent;
						} else {
							if (z == z->parent->left) {
								z = z->parent;
								rightRotate(z);
							}
							z->parent->color = BLACK;
							z->parent->parent->color = RED;
							leftRotate(z->parent->parent);
						}
					}
				}
				_root->color = BLACK;
			}
		
		void delete(nodePtr x) {
			while (x != _root && x->color == BLACK) {
				if (x == x->parent->left) {
					nodePtr w = x->parent->right;
					if (w->color == RED) {
						w->color = BLACK;
						x->parent->color = RED;
						leftRotate(x->parent);
						w = x->parent->right;
					}
					if (w->left->color == BLACK && w->right->color == BLACK) {
						w->color = RED;
						x = x->parent;
					} else {
						if (w->right->color == BLACK) {
							w->left->color = BLACK;
							w->color = RED;
							rightRotate(w);
							w = x->parent->right;
						}
						w->color = x->parent->color;
						x->parent->color = BLACK;
						w->right->color = BLACK;
						leftRotate(x->parent);
						x = _root;
					}
				} else {
					nodePtr w = x->parent->left;
					if (w->color == RED) {
						w->color = BLACK;
						x->parent->color = RED;
						rightRotate(x->parent);
						w = x->parent->left;
					}
					if (w->right->color == BLACK && w->left->color == BLACK) {
						w->color = RED;
						x = x->parent;
					} else {
						if (w->left->color == BLACK) {
							w->right->color = BLACK;
							w->color = RED;
							leftRotate(w);
							w = x->parent->left;
						}
						w->color = x->parent->color;
						x->parent->color = BLACK;
						w->left->color = BLACK;
						rightRotate(x->parent);
						x = _root;
					}
				}
			}
			x->color = BLACK;
		}
		
			// function to find the next node in the tree
			nodePtr successor(nodePtr x) {
				if (x->right != _nil)
					return minimum(x->right);
				nodePtr y = x->parent;
				while (y != _nil && x == y->right) {
					x = y;
					y = y->parent;
				}
				return y;
			}

			// function to find the previous node in the tree
			nodePtr predecessor(nodePtr x) {
				if (x->left != _nil)
					return maximum(x->left);
				nodePtr y = x->parent;
				while (y != _nil && x == y->left) {
					x = y;
					y = y->parent;
				}
				return y;
			}
			
			// function to find the minimum node in the tree
			nodePtr minimum(nodePtr x) {
				while (x->left != _nil)
					x = x->left;
				return x;
			}

			// function to find the maximum node in the tree
			nodePtr maximum(nodePtr x) {
				while (x->right != _nil)
					x = x->right;
				return x;
			}


		
	};
	
}

#endif