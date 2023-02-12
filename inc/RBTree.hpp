/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennyduong <kennyduong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:55:11 by kennyduong        #+#    #+#             */
/*   Updated: 2023/02/12 20:08:07 by kennyduong       ###   ########.fr       */
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
	template<typename Value, class Compare, class Alloc = std::allocator<Value> >
	class RBTree {
		typedef typename Alloc::template rebind<RbNode<Value> >::other		node_allocator;

		public:
			typedef Value													value_type;
			typedef Compare													key_compare;
			typedef Alloc													allocator_type;
			
			typedef value_type*												pointer;
			typedef const value_type*										const_pointer;
			typedef value_type&												reference;
			typedef const value_type&										const_reference;
			
			typedef size_t													size_type;
			typedef ptrdiff_t												difference_type;
			typedef RbNode<value_type>										Node;
			
			typedef ft::tree_iterator<value_type>							iterator;
			typedef ft::tree_iterator<const value_type>						const_iterator;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;

		private:
			Node*						_root;
			Node*						_end;
			size_type					_size;
			key_compare					_comp;
			node_allocator				_alloc;

		public:
			// ====================== Member Functions ========================= //
			explicit RBTree(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _root(NULL), _end(NULL), _size(0), _comp(comp), _alloc(alloc) {
				_end = _alloc.allocate(1);
				_alloc.construct(_end, Node());
				_end->color = BLACK;
			};
			
			RBTree(const RBTree& x) : _root(NULL), _end(NULL), _size(0), _comp(x._comp), _alloc(x._alloc) {
				_end = _alloc.allocate(1);
				_alloc.construct(_end, Node());
				_end->color = BLACK;
				*this = x;
			};
			
			~RBTree() {
				clear();
				_alloc.destroy(_end);
				_alloc.deallocate(_end, 1);
			};
			
			RBTree& operator=(const RBTree& x) {
				if (this != &x) {
					clear();
					_comp = x._comp;
					_alloc = x._alloc;
					_size = x._size;
					_root = copy(x._root, _end);
				}
				return *this;
			};
			
			iterator 						begin() { return iterator(_root); };
			const_iterator 					begin() const { return const_iterator(_root); };
			iterator 						end() { return iterator(_end); };
			const_iterator 					end() const { return const_iterator(_end); };
			reverse_iterator 				rbegin() { return reverse_iterator(end()); };
			const_reverse_iterator 			rbegin() const { return const_reverse_iterator(end()); };
			reverse_iterator 				rend() { return reverse_iterator(begin()); };
			const_reverse_iterator 			rend() const { return const_reverse_iterator(begin()); };
			
			bool 							empty() const { return _size == 0; };
			size_type 						size() const { return _size; };
			size_type 						max_size() const { return _alloc.max_size(); };
			
			ft::pair<iterator, bool> insert(const value_type& val) {
				Node* node = _root;
				Node* parent = NULL;
				while (node != NULL) {
					parent = node;
					if (_comp(val, node->data))
						node = node->left;
					else if (_comp(node->data, val))
						node = node->right;
					else
						return ft::make_pair(iterator(node), false);
				}
				node = _alloc.allocate(1);
				_alloc.construct(node, Node(val, parent, _end, _end));
				if (parent == NULL)
					_root = node;
				else if (_comp(val, parent->data))
					parent->left = node;
				else
					parent->right = node;
				++_size;
				insertFix(node);
				return ft::make_pair(iterator(node), true);
			};
			
			iterator insert(iterator position, const value_type& val) { (void)position; return insert(val).first;};

			template <class InputIterator>
			void insert(InputIterator first, InputIterator last) {
				while (first != last) {
					insert(*first); 
					++first;
				}
			}	
			
			void swap(RBTree& x) {
				std::swap(_root, x._root);
				std::swap(_end, x._end);
				std::swap(_size, x._size);
				std::swap(_comp, x._comp);
				std::swap(_alloc, x._alloc);
			};

			void 				clear() {erase(begin(), end());};
			key_compare 		key_comp() const { return _comp; };
			value_compare 		value_comp() const { return _comp; };
			
			iterator find(const key_type& k) {
				Node* node = _root;
				while (node != NULL) {
					if (_comp(k, node->data))
						node = node->left;
					else if (_comp(node->data, k))
						node = node->right;
					else
						return iterator(node);
				}
				return end();
			};
			
			const_iterator find(const key_type& k) const {
				Node* node = _root;
				while (node != NULL) {
					if (_comp(k, node->data))
						node = node->left;
					else if (_comp(node->data, k))
						node = node->right;
					else
						return const_iterator(node);
				}
				return end();
			};

			size_type count(const key_type& k) const {
				if (find(k) == end())
					return 0;
				return 1;
			};
			
			iterator lower_bound(const key_type& k) {
				iterator it = begin();
				while (it != end()) {
					if (!_comp(it->first, k))
						return it;
					++it;
				}
				return it;
			};
			
			const_iterator lower_bound(const key_type& k) const {
				const_iterator it = begin();
				while (it != end()) {
					if (!_comp(it->first, k))
						return it;
					++it;
				}
				return it;
			};
			
			iterator upper_bound(const key_type& k) {
				iterator it = begin();
				while (it != end()) {
					if (_comp(k, it->first))
						return it;
					++it;
				}
				return it;
			};

			const_iterator upper_bound(const key_type& k) const {
				const_iterator it = begin();
				while (it != end()) {
					if (_comp(k, it->first))
						return it;
					++it;
				}
				return it;
			};
			
			ft::pair<iterator, iterator> 				equal_range(const key_type& k) {return ft::make_pair(lower_bound(k), upper_bound(k));}
			ft::pair<const_iterator, const_iterator> 	equal_range(const key_type& k) const {return ft::make_pair(lower_bound(k), upper_bound(k));}

		private:
			void leftRotate(Node* node) {
				Node* tmp = node->right;
				node->right = tmp->left;
				if (tmp->left != NULL)
					tmp->left->parent = node;
				tmp->parent = node->parent;
				if (node->parent == NULL)
					_root = tmp;
				else if (node == node->parent->left)
					node->parent->left = tmp;
				else
					node->parent->right = tmp;
				tmp->left = node;
				node->parent = tmp;
			};
			
			void rightRotate(Node* node) {
				Node* tmp = node->left;
				node->left = tmp->right;
				if (tmp->right != NULL)
					tmp->right->parent = node;
				tmp->parent = node->parent;
				if (node->parent == NULL)
					_root = tmp;
				else if (node == node->parent->right)
					node->parent->right = tmp;
				else
					node->parent->left = tmp;
				tmp->right = node;
				node->parent = tmp;
			};

			void insertFix(Node* node) {
				Node* parent = NULL;
				Node* grandparent = NULL;
				while ((node != _root) && (node->color != BLACK) && (node->parent->color == RED)) {
					parent = node->parent;
					grandparent = node->parent->parent;
					if (parent == grandparent->left) {
						Node* uncle = grandparent->right;
						if (uncle != NULL && uncle->color == RED) {
							grandparent->color = RED;
							parent->color = BLACK;
							uncle->color = BLACK;
							node = grandparent;
						}
						else {
							if (node == parent->right) {
								leftRotate(parent);
								node = parent;
								parent = node->parent;
							}
							rightRotate(grandparent);
							std::swap(parent->color, grandparent->color);
							node = parent;
						}
					}
					else {
						Node* uncle = grandparent->left;
						if ((uncle != NULL) && (uncle->color == RED)) {
							grandparent->color = RED;
							parent->color = BLACK;
							uncle->color = BLACK;
							node = grandparent;
						}
						else {
							if (node == parent->left) {
								rightRotate(parent);
								node = parent;
								parent = node->parent;
							}
							leftRotate(grandparent);
							std::swap(parent->color, grandparent->color);
							node = parent;
						}
					}
				}
				_root->color = BLACK;
			};
			
			void deleteFix(Node* node) {
				
			}
				
	};

} // namespace ft

#endif