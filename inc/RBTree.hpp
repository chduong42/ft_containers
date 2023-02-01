/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:55:11 by kennyduong        #+#    #+#             */
/*   Updated: 2023/02/01 21:31:04 by chduong          ###   ########.fr       */
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
			typedef Node<value_type>									node;
			typedef Node<value_type>*									nodePtr;

			typedef ft::bidirectional_iterator<value_type, node>		iterator;
			typedef ft::bidirectional_iterator<const value_type, node>	const_iterator;
			typedef ft::reverse_iterator<iterator>						reverse_iterator;
			typedef ft::reverse_iterator<const iterator>				const_reverse_iterator;

		private:
			nodePtr														_root;
			nodePtr														_nil;
			size_type													_size;
			Compare														_comp;
			allocator_type												_alloc;
		
		public:
			explicit RBTree(const Compare& comp = Compare(), const allocator_type& alloc = allocator_type()) : _root(NULL), _nil(NULL), _size(0), _comp(comp), _alloc(alloc) {
				_nil = node_allocator().allocate(1);
				node_allocator().construct(_nil, node(value_type()));
				_nil->color = BLACK;
				_root = _nil;
			}
			
			template<typename InputIterator>
			RBTree(InputIterator first, InputIterator last, const Compare& comp = Compare(), const allocator_type& alloc = allocator_type()) : _root(NULL), _nil(NULL), _size(0), _comp(comp), _alloc(alloc) {
				_nil = node_allocator().allocate(1);
				node_allocator().construct(_nil, node(value_type()));
				_nil->color = BLACK;
				_root = _nil;
				insert(first, last);
			}

			RBTree(const RBTree& x) : _root(NULL), _nil(NULL), _size(0), _comp(x._comp), _alloc(x._alloc) {
				_nil = node_allocator().allocate(1);
				node_allocator().construct(_nil, node(value_type()));
				_nil->color = BLACK;
				_root = _nil;
				insert(x.begin(), x.end());
			}
			
			~RBTree() {
				clear();
				node_allocator().destroy(_nil);
				node_allocator().deallocate(_nil, 1);
			}
			
			RBTree& operator=(const RBTree& x) {
				if (this != &x) {
					clear();
					insert(x.begin(), x.end());
				}
				return *this;
			}

			// Accessors
			allocator_type 				get_allocator() const {return _alloc;}
			nodePtr 					getRoot() const {return _root;}
			nodePtr 					getNil() const {return _nil;}
			Compare 					getComp() const {return _comp;}			

			// iterators
			iterator 					begin() {return iterator(minNode(_root), _nil);}
			const_iterator 				begin() const {return const_iterator(minNode(_root), _nil);}
			iterator 					end() {return iterator(_nil, _nil);}
			const_iterator 				end() const {return const_iterator(_nil, _nil);}
			reverse_iterator 			rbegin() {return reverse_iterator(end());}
			const_reverse_iterator 		rbegin() const {return const_reverse_iterator(end());}
			reverse_iterator 			rend() {return reverse_iterator(begin());}
			const_reverse_iterator 		rend() const {return const_reverse_iterator(begin());}
			
			// capacity
			bool 						empty() const {return _size == 0;}
			size_type 					size() const {return _size;}
			size_type 					max_size() const {return _alloc.max_size();}

			// modifiers
			ft::pair<iterator, bool> insert(const value_type& val) {
				nodePtr newNode = node_allocator().allocate(1);
				node_allocator().construct(newNode, node(val));
				newNode->left = _nil;
				newNode->right = _nil;
				newNode->parent = _nil;
				newNode->color = RED;
				nodePtr parent = _nil;
				nodePtr current = _root;
				while (current != _nil) {
					parent = current;
					if (_comp(newNode->data, current->data))
						current = current->left;
					else if (_comp(current->data, newNode->data))
						current = current->right;
					else {
						node_allocator().destroy(newNode);
						node_allocator().deallocate(newNode, 1);
						return ft::make_pair(iterator(current, _nil), false);
					}
				}
				newNode->parent = parent;
				if (parent == _nil)
					_root = newNode;
				else if (_comp(newNode->data, parent->data))
					parent->left = newNode;
				else
					parent->right = newNode;
				++_size;
				insertFixup(newNode);
				return ft::make_pair(iterator(newNode, _nil), true);
			}
			
			iterator insert(iterator position, const value_type& val) {
				(void)position;
				return insert(val).first;
			}

			template<typename InputIterator>
			void insert(InputIterator first, InputIterator last) {
				while (first != last) {
					insert(*first);
					++first;
				}
			}

		private:
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

			void transplant(nodePtr u, nodePtr v) {
				if (u->parent == _nil)
					_root = v;
				else if (u == u->parent->left)
					u->parent->left = v;
				else
					u->parent->right = v;
				v->parent = u->parent;
			}

			void deleteFixup(nodePtr x) {
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
						}
						else {
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
					}
					else {
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
						}
						else {
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

			nodePtr minimum(nodePtr x) {
				while (x->left != _nil)
					x = x->left;
				return x;
			}
			
			
	};
	
}

#endif