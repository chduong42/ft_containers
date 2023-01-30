/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:55:11 by kennyduong        #+#    #+#             */
/*   Updated: 2023/01/30 19:20:11 by chduong          ###   ########.fr       */
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

		Node(const T value) : value(value), color(RED), parent(NULL), left(NULL), right(NULL) {}
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

	template<typename NodePtr>
	NodePtr minNode(NodePtr node) {
		while (node->left)
			node = node->left;
		return node;
	}

	template<typename NodePtr>
	NodePtr maxNode(NodePtr node) {
		while (node->right)
			node = node->right;
		return node;
	}
	
	template<typename NodePtr>
	NodePtr nextNode(NodePtr node) {
		if (node->right)
			return minNode(node->right);
		NodePtr parent = node->parent;
		while (parent && node == parent->right) {
			node = parent;
			parent = parent->parent;
		}
		return parent;
	}

	template<typename NodePtr>
	NodePtr prevNode(NodePtr node) {
		if (node->left)
			return maxNode(node->left);
		NodePtr parent = node->parent;
		while (parent && node == parent->left) {
			node = parent;
			parent = parent->parent;
		}
		return parent;
	}
		
	// ---------- RB Tree iterator
	template<typename T>
	class tree_iterator {
		public:
			typedef T									value_type;
			typedef T*									pointer;
			typedef T&									reference;
			typedef std::bidirectional_iterator_tag		iterator_category;
			typedef ptrdiff_t							difference_type;
			typedef Node<T>*							nodePtr;
			
		protected:
			nodePtr										_node;
		
		public:
			tree_iterator() 						: _node(NULL) {}
			explicit tree_iterator(Node<T>* node) 	: _node(node) {}
			tree_iterator(const tree_iterator& src) : _node(src._node) {}
			virtual ~tree_iterator() {}
			
			tree_iterator& operator=(const tree_iterator& src) {
				if (this != &src)
					_node = src._node;
				return *this;
			}

			operator tree_iterator<const value_type>() const {return tree_iterator<const value_type>(_node);}

			pointer						base() const {return &_node->value;}
			pointer						operator->() {return &_node->value;}
			reference					operator*() const {return _node->value;}

			tree_iterator& 				operator++() {_node = nextNode(_node); return *this;}
			tree_iterator& 				operator--() {_node = prevNode(_node); return *this;}
			tree_iterator				operator++(int) {tree_iterator tmp(*this); ++(*this); return tmp; }
			tree_iterator				operator--(int) {tree_iterator tmp(*this); --(*this); return tmp; }
			
			bool						operator==(const tree_iterator& rhs) const {return _node == rhs._node;}
			bool						operator!=(const tree_iterator& rhs) const {return _node != rhs._node;}
	};

	template<typename iter1, typename iter2>
	inline bool operator==(const tree_iterator<iter1>& lhs, const tree_iterator<iter2>& rhs) {return lhs.base() == rhs.base();}
	
	template<typename iter1, typename iter2>
	inline bool operator!=(const tree_iterator<iter1>& lhs, const tree_iterator<iter2>& rhs) {return lhs.base() != rhs.base();}
	// ---------- End of RB tree iterator


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
			typedef Node<T>												node;
			typedef Node<T>*											nodePtr;

			typedef tree_iterator<value_type>							iterator;
			typedef tree_iterator<const value_type>						const_iterator;
			typedef ft::reverse_iterator<iterator>						reverse_iterator;
			typedef ft::reverse_iterator<const iterator>				const_reverse_iterator;

		private:
			nodePtr														_root;
			nodePtr														_nil;
			size_type													_size;
			Compare														_comp;
			allocator_type												_alloc;
		
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

		void insertFixup(nodePtr z) {
			while (z->parent->color == RED) {
				if (z->parent == z->parent->parent->left) {
					nodePtr y = z->parent->parent->right;
					if (y->color == RED) {
						z->parent->color = BLACK;
						y->color = BLACK;
						z->parent->parent->color = RED;
						z = z->parent->parent;
					}
					else {
						if (z == z->parent->right) {
							z = z->parent;
							leftRotate(z);
						}
						z->parent->color = BLACK;
						z->parent->parent->color = RED;
						rightRotate(z->parent->parent);
					}
				}
				else {
					nodePtr y = z->parent->parent->left;
					if (y->color == RED) {
						z->parent->color = BLACK;
						y->color = BLACK;
						z->parent->parent->color = RED;
						z = z->parent->parent;
					}
					else {
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
		
		public:
			// Constructor
			explicit RBTree(const Compare& comp = Compare(), const allocator_type& alloc = allocator_type())
			: _root(NULL), _nil(NULL), _size(0), _comp(comp), _alloc(alloc) {
				_nil = new Node<T>(value_type());
				_nil->color = BLACK;
				_root = _nil;
			}

			RBTree(const RBTree& x) {*this = x;}

			// get allocator
			allocator_type			get_allocator() const {return _alloc;}
			
			// Create a new node
			nodePtr createNode(const value_type& val) {
				nodePtr tmp = node_allocator().allocate(1);
				node_allocator().construct(tmp, Node<T>(val));
				tmp->left = _nil;
				tmp->right = _nil;
				tmp->parent = _nil;
				tmp->color = RED;
				return tmp;
			}

			// Delete a node
			void deleteNode(nodePtr z) {
				node_allocator().destroy(z);
				node_allocator().deallocate(z, 1);
			}
			
			// Insert a new node
			pair<iterator, bool> insert(const value_type& val) {
				nodePtr z = createNode(val);
				nodePtr y = _nil;
				nodePtr x = _root;
				while (x != _nil) {
					y = x;
					if (_comp(z->value.first, x->value.first))
						x = x->left;
					else if (_comp(x->value.first, z->value.first))
						x = x->right;
					else {
						node_allocator().destroy(z);
						node_allocator().deallocate(z, 1);
						return make_pair(iterator(x), false);
					}
				}
				z->parent = y;
				if (y == _nil)
					_root = z;
				else if (_comp(z->value.first, y->value.first))
					y->left = z;
				else
					y->right = z;
				insertFixup(z);
				_size++;
				return make_pair(iterator(z), true);
			}
			
			// Iterator
			iterator begin() {
				nodePtr tmp = _root;
				while (tmp->left != _nil)
					tmp = tmp->left;
				return iterator(tmp);
			}

			iterator 			end() {return iterator(_nil);}
			reverse_iterator 	rbegin() {return reverse_iterator(end());}
			reverse_iterator 	rend() {return reverse_iterator(begin());}
			
			// Capacity
			bool 				empty() const {return _size == 0;}
			size_type 			size() const {return _size;}
			size_type 			max_size() const {return node_allocator().max_size();}
		
	};
	
}

#endif