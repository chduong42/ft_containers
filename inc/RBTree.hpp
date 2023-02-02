/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:55:11 by kennyduong        #+#    #+#             */
/*   Updated: 2023/02/02 17:57:30 by chduong          ###   ########.fr       */
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
			typedef Compare												key_compare;
			
			typedef ft::bidirectional_iterator<value_type, node>		iterator;
			typedef ft::bidirectional_iterator<const value_type, node>	const_iterator;
			typedef ft::reverse_iterator<iterator>						reverse_iterator;
			typedef ft::reverse_iterator<const iterator>				const_reverse_iterator;

		private:
			nodePtr														_root;
			nodePtr														_nil;
			size_type													_size;
			key_compare													_comp;
			node_allocator												_alloc;
		
		public:
			// Constructors
			explicit RBTree(const Compare& comp = Compare(), const allocator_type& alloc = allocator_type()) : _root(NULL), _nil(NULL), _size(0), _comp(comp), _alloc(alloc) {
				_nil = _alloc.allocate(1);
				_alloc.construct(_nil, node(value_type()));
				_nil->color = BLACK;
				_root = _nil;
			}
			
			template<typename InputIterator>
			RBTree(InputIterator first, InputIterator last, const Compare& comp = Compare(), const allocator_type& alloc = allocator_type()) : _root(NULL), _nil(NULL), _size(0), _comp(comp), _alloc(alloc) {
				_nil = _alloc.allocate(1);
				_alloc.construct(_nil, node(value_type()));
				_nil->color = BLACK;
				_root = _nil;
				insert(first, last);
			}

			RBTree(const RBTree& x) : _root(NULL), _nil(NULL), _size(0), _comp(x._comp), _alloc(x._alloc) {
				_nil = _alloc.allocate(1);
				_alloc.construct(_nil, node(value_type()));
				_nil->color = BLACK;
				_root = _nil;
				insert(x.begin(), x.end());
			}

			// Destructor
			~RBTree() {
				clear();
				_alloc.destroy(_nil);
				_alloc.deallocate(_nil, 1);
			}

			// Operators
			RBTree& operator=(const RBTree& x) {
				if (this != &x) {
					clear();
					insert(x.begin(), x.end());
				}
				return *this;
			}

			// Accessors
			node_allocator 				get_allocator() const {return _alloc;}
			nodePtr 					getRoot() const {return _root;}
			nodePtr 					getNil() const {return _nil;}
			key_compare 				key_comp() const {return _comp;}	

			// iterators
			iterator 					begin() {return iterator(minNode(_root), _nil);}
			const_iterator 				begin() const {return const_iterator(minNode(_root), _nil);}
			iterator 					end() {return iterator(_nil, _nil);}
			const_iterator 				end() const {return const_iterator(_nil, _nil);}
			reverse_iterator 			rbegin() {return reverse_iterator(end());}
			const_reverse_iterator 		rbegin() const {return const_reverse_iterator(end());}
			reverse_iterator 			rend() {return reverse_iterator(begin());}
			const_reverse_iterator 		rend() const {return const_reverse_iterator(begin());}

			// Capacity
			bool 						empty() const {return _size == 0;}
			size_type 					size() const {return _size;}
			size_type 					max_size() const {return _alloc.max_size();}
			
			// Modifiers
			ft::pair<iterator, bool> insert(const value_type& val) {
				nodePtr newNode = _alloc.allocate(1);
				_alloc.construct(newNode, node(val));
				newNode->left = _nil;
				newNode->right = _nil;
				newNode->parent = _nil;
				newNode->color = RED;
				_size++;
				if (_root == _nil) {
					_root = newNode;
					_root->color = BLACK;
					_root->parent = _nil;
					return ft::make_pair(iterator(_root, _nil), true);
				}
				nodePtr parent = _root;
				while (parent != _nil) {
					if (_comp(newNode->data, parent->data)) {
						if (parent->left == _nil) {
							parent->left = newNode;
							newNode->parent = parent;
							break;
						}
						parent = parent->left;
					}
					else if (_comp(parent->data, newNode->data)) {
						if (parent->right == _nil) {
							parent->right = newNode;
							newNode->parent = parent;
							break;
						}
						parent = parent->right;
					}
					else {
						_alloc.destroy(newNode);
						_alloc.deallocate(newNode, 1);
						_size--;
						return ft::make_pair(iterator(parent, _nil), false);
					}
				}
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
					first++;
				}
			}

			void erase(iterator position) {
				nodePtr node = position.getNode();
				if (node == _nil)
					return;
				_size--;
				if (node->left != _nil && node->right != _nil) {
					nodePtr successor = minNode(node->right);
					node->data = successor->data;
					node = successor;
				}
				nodePtr child = node->left != _nil ? node->left : node->right;
				if (node->color == BLACK) {
					node->color = child->color;
					deleteFixup(node);
				}
				if (node->parent == _nil)
					_root = child;
				else if (node == node->parent->left)
					node->parent->left = child;
				else
					node->parent->right = child;
				child->parent = node->parent;
				_alloc.destroy(node);
				_alloc.deallocate(node, 1);
			}

			size_type erase(const key_type& k) {
				iterator it = find(k);
				if (it == end())
					return 0;
				erase(it);
				return 1;
			}

			void erase(iterator first, iterator last) {
				while (first != last) {
					iterator tmp = first;
					first++;
					erase(tmp);
				}
			}

			void swap(RBTree& x) {
				nodePtr tmp = _root;
				_root = x._root;
				x._root = tmp;
				tmp = _nil;
				_nil = x._nil;
				x._nil = tmp;
				size_type tmpSize = _size;
				_size = x._size;
				x._size = tmpSize;
			}

			void clear() {
				erase(begin(), end());
			}

			// Operations
			iterator find(const key_type& k) {
				nodePtr node = _root;
				while (node != _nil) {
					if (_comp(k, node->data))
						node = node->left;
					else if (_comp(node->data, k))
						node = node->right;
					else
						return iterator(node, _nil);
				}
				return end();
			}

			const_iterator find(const key_type& k) const {
				nodePtr node = _root;
				while (node != _nil) {
					if (_comp(k, node->data))
						node = node->left;
					else if (_comp(node->data, k))
						node = node->right;
					else
						return const_iterator(node, _nil);
				}
				return end();
			}

			size_type count(const key_type& k) const {
				if (find(k) == end())
					return 0;
				return 1;
			}

			iterator lower_bound(const key_type& k) {
				iterator it = begin();
				while (it != end()) {
					if (!_comp(it->first, k))
						return it;
					it++;
				}
				return it;
			}

			const_iterator lower_bound(const key_type& k) const {
				const_iterator it = begin();
				while (it != end()) {
					if (!_comp(it->first, k))
						return it;
					it++;
				}
				return it;
			}

			iterator upper_bound(const key_type& k) {
				iterator it = begin();
				while (it != end()) {
					if (_comp(k, it->first))
						return it;
					it++;
				}
				return it;
			}

			const_iterator upper_bound(const key_type& k) const {
				const_iterator it = begin();
				while (it != end()) {
					if (_comp(k, it->first))
						return it;
					it++;
				}
				return it;
			}

			ft::pair<iterator, iterator> equal_range(const key_type& k) {
				return ft::make_pair(lower_bound(k), upper_bound(k));
			}

			ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const {
				return ft::make_pair(lower_bound(k), upper_bound(k));
			}

			// Observers
			key_compare key_comp() const {
				return _comp;
			}

			value_compare value_comp() const {
				return value_compare(_comp);
			}
			
			// Allocator
			allocator_type get_allocator() const {
				return _alloc;
			}
			
			// Debug
			void print(nodePtr x, int level) {
				if (x != _nil) {
					print(x->right, level + 1);
					for (int i = 0; i < level; i++)
						std::cout << "   ";
					std::cout << x->key << std::endl;
					print(x->left, level + 1);
				}
			}

			void print() {
				print(_root, 0);
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
							x = root;
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
	};
	
}

#endif