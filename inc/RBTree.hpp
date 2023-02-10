/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:55:11 by kennyduong        #+#    #+#             */
/*   Updated: 2023/02/10 07:09:07 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
# define RBTREE_HPP
# include <memory>
# include "utility.hpp"
# include "iterator.hpp"
# include "algorithm.hpp"
# include "type_traits.hpp"

namespace ft 
{
	enum Color {red, black};

	template<class T>
	struct RbNode {
		T				data;
		Color			color;
		RbNode*			parent;
		RbNode*			left;
		RbNode*			right;

		RbNode() : data(), color(black), parent(0), left(0), right(0) {}
		RbNode(const T& data) : data(data), color(black), parent(0), left(0), right(0) {}
		RbNode(const T& data, Color color, RbNode* parent, RbNode* left, RbNode* right) : data(data), color(color), parent(parent), left(left), right(right) {}
		RbNode(const RbNode& x) : data(x.data), color(x.color), parent(x.parent), left(x.left), right(x.right) {}
		~RbNode() {}

		static RbNode* minimum(RbNode* x) {
			while (x->left != 0)
				x = x->left;
			return x;
		}

		static const RbNode* minimum(const RbNode* x) {
			while (x->left != 0)
				x = x->left;
			return x;
		}

		static RbNode* maximum(RbNode* x) {
			while (x->right != 0) 
				x = x->right;
			return x;
		}

		static const RbNode* maximum(const RbNode* x) {
			while (x->right != 0) 
				x = x->right;
			return x;
		}
	};

	template<typename T>
	struct tree_iterator {
		typedef T												value_type;
		typedef value_type&										reference;
		typedef value_type*										pointer;
		typedef ptrdiff_t										difference_type;
		typedef std::bidirectional_iterator_tag					iterator_category;
		typedef RbNode<value_type>								Node;
	
		Node*													node;

		tree_iterator()						: node() {}
		explicit tree_iterator(Node* x)		: node(x) {}

		Node* prevNode(Node* x) {
			if (x->color == red	&& x->parent->parent == x)
				x = x->right;
			else if (x->left != 0) {
				Node* y = x->left;
				while (y->right != 0)
					y = y->right;
				x = y;
			} else {
				Node* y = x->parent;
				while (x == y->left) {
					x = y;
					y = y->parent;
				}
				x = y;
			}
			return x;
		}

		Node* nextNode(Node* x)	{
			if (x->right != 0) {
				x = x->right;
				while (x->left != 0)
					x = x->left;
			} else {
				Node* y = x->parent;
				while (x == y->right) {
					x = y;
					y = y->parent;
				}
				if (x->right != y)
					x = y;
			}
			return x;
		}

		reference           operator*() const { return this->node->data; }
		pointer     	    operator->() const { return &this->node->data; }
		tree_iterator&		operator++() {this->node = nextNode(this->node); return *this;}
		tree_iterator		operator++(int)	{tree_iterator tmp = *this; this->node = nextNode(this->node); return tmp;}
		tree_iterator&		operator--() {this->node = prevNode(this->node); return *this;}
		tree_iterator		operator--(int) {tree_iterator tmp = *this;	this->node = prevNode(this->node); return tmp;}
		bool        	    operator==(const tree_iterator& rhs) const 	{return this->node == rhs.node;}
		bool                operator!=(const tree_iterator& rhs) const 	{return this->node != rhs.node;}
	};

	template<typename T> 
	inline bool operator==(const tree_iterator<T>& lhs, const tree_iterator<T>& rhs) {return lhs.node == rhs.node;}
	
	template<typename T>
	inline bool operator!=(const tree_iterator<T>& lhs, const tree_iterator<T>& rhs) {return lhs.node != rhs.node;}


	template<typename Key, typename T, typename KeyOfValue, class Compare, class Alloc = std::allocator<T> >
	class RBTree {
		typedef typename Alloc::template rebind<RbNode<T> >::other		node_allocator;

		public:
			typedef Key													key_type;
			typedef T													value_type;
			typedef Compare												key_compare;
			typedef Alloc												allocator_type;
			
			typedef value_type*											pointer;
			typedef const value_type*									const_pointer;
			typedef value_type&											reference;
			typedef const value_type&									const_reference;
			
			typedef size_t												size_type;
			typedef ptrdiff_t											difference_type;
			typedef RbNode<value_type>									Node;
			
			typedef ft::tree_iterator<value_type>						iterator;
			typedef ft::tree_iterator<const value_type>					const_iterator;
			typedef ft::reverse_iterator<iterator>						reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;

		private:
			node_allocator												allocator;
			key_compare													compare;
			Node														header;
			size_type													count;
		
		public:
			RBTree() :	allocator(node_allocator()), compare(key_compare()), header(), count(0) {}

			RBTree(const key_compare& comp = key_compare(),	const node_allocator& a = node_allocator())	: allocator(a), compare(comp), header(), count(0) {
				this->header.color = red;
				this->header.parent = 0;
				this->header.left = &this->header;
				this->header.right = &this->header;
			}

			~RBTree() { erase(root()); }

			RBTree &operator=(const RBTree& rhs) {
				if (this != &rhs) {
					this->clear();
					this->compare = rhs.key_comp();
					if (rhs.root() != 0) {
						this->insertUnique(rhs.begin(), rhs.end());
						this->leftmost() = minimum(this->root());
						this->rightmost() = maximum(this->root());
						this->count = rhs.count;
					}
				}
				return *this;
			}
		
			allocator_type					getAllocator() const { return allocator_type(); }

			Node* createNode(const value_type& x) {
				Node* tmp =  allocator.allocate(1);
				try {
					getAllocator().construct(&tmp->data, x);
				} catch (...) {
					allocator.deallocate(tmp, 1);
					__throw_exception_again;
				}
				return tmp;
			}

			Node* cloneNode(const Node* x) {
				Node* tmp = createNode(x->data);
				tmp->color = x->color;
				tmp->left = 0;
				tmp->right = 0;
				return tmp;
			}

			void destroyNode(Node* p) {
				getAllocator().destroy(&p->data);
				allocator.deallocate(p, 1);
			}

			Node*&						leftmost() { return this->header.left; }
			const Node*					leftmost() const { return this->header.left; }
			Node*& 						rightmost() { return this->header.right; }
			const Node*					rightmost() const { return this->header.right; }
			Node*& 						root() { return this->header.parent; }
			const Node* 				root() const { return this->header.parent; }
			const_reference 			value(const Node* x) { return x->data; }
			const Key& 					key(const Node* x) { return KeyOfValue()(value(x)); }
			Node* 						left(Node* x) { return x->left; }
			const Node* 				left(const Node* x) const { return x->left; }
			Node*						right(Node* x) { return x->right; }
			const Node*					right(const Node* x) const { return x->right; }
			Node*						minimum(Node* x) { return x->minimum(x); }
			const Node*					minimum(const Node* x) const { return x->minimum(x); }
			Node*						maximum(Node* x) { return x->maximum(x); }
			const Node*					maximum(const Node* x) const { return x->maximum(x); }

			iterator					begin() { return iterator(this->header.left); }
			const_iterator				begin() const { return const_iterator(this->header.left); }
			iterator					end() { return iterator(&this->header); }
			const_iterator				end() const	{ return const_iterator(&this->header); }
			reverse_iterator			rbegin() { return reverse_iterator(end()); }
			const_reverse_iterator		rbegin() const { return const_reverse_iterator(end()); }
			reverse_iterator			rend() { return reverse_iterator(begin()); }
			const_reverse_iterator		rend() const { return const_reverse_iterator(begin()); }
			
			Node*						nodeBegin()	{ return this->header.left; }
			const Node*					nodeBegin() const { return this->header.left; }
			Node*						nodeEnd() { return &this->header; }
			const Node*					nodeEnd() const	{ return &this->header; }
			
			size_type					size() const { return this->count; }
			size_type					max_size() const { return this->allocator.max_size(); }
			
			void	clear() {erase(this->root());
				this->leftmost() = nodeEnd();
				this->header.parent = 0;
				this->rightmost() = nodeEnd();
				this->count = 0;
			}

			iterator	find(const Key& k) {
				Node* x = this->root();
				while (x != 0) {
					if (compare(key(x), k))
						x = right(x);
					else if (compare(k, key(x)))
						x = left(x);
					else if (!compare(key(x), k) && !compare(k, key(x)))
						return iterator(x);
				}
				return iterator(this->end());
			}

			const_iterator	find(const Key& k) const {
				const Node* x = this->root();
				while (x != 0) {
					if (compare(key(x), k))
						x = right(x);
					else if (compare(k, key(x)))
						x = left(x);
					else if (!compare(key(x), k) && !compare(k, key(x)))
						return const_iterator(x);
				}
				return this->end();
			}

			iterator		lower_bound(const Key& k) {
				Node* x = this->root();
				Node* y = this->nodeEnd();
				while (x != 0) {
					if (!compare(key(x), k))
						y = x, x = left(x);
					else 
						x = right(x);
				}
				return iterator(y);
			}

			const_iterator		lower_bound(const Key& k) const {
				const Node* x = this->root();
				const Node* y = this->nodeEnd();
				while (x != 0) {
					if (!compare(key(x), k))
						y = x, x = left(x);
					else
						x = right(x);
				}
				return const_iterator(y);
			}

			iterator		upper_bound(const Key& k) {
				Node* x = this->root();
				Node* y = this->nodeEnd();
				while (x != 0) {
					if (compare(k, key(x)))
						y = x, x = left(x);
					else
						x = right(x);
				}
				return iterator(y);
			}

			const_iterator		upper_bound(const Key& k) const {
				const Node* x = this->root();
				const Node* y = this->nodeEnd();
				while (x != 0) {
					if (compare(k, key(x)))
						y = x, x = left(x);
					else
						x = right(x);
				}
				return const_iterator(y);
			}

			iterator insert(Node* x, Node* p, const value_type& value) {
				bool insertLeft = (x != 0 || p == nodeEnd()	|| compare(KeyOfValue()(value),	key(p)));
				Node* z = createNode(value);
				insertAndRebalance(insertLeft, z, p, this->header);
				++this->count;
				return iterator(z);
			}

			size_type	erase(const Key& key) {
				iterator ret = this->find(key);
				if (ret != this->end()) {
					erase(ret);
					return 1;
				}
				return 0;
			}

			void	erase(iterator pos) {
				Node* y = eraseAndRebalance(pos.node, this->header);
				destroyNode(y);
				--this->count;
			}

			void	erase(iterator first, iterator last) {
				if (first == this->begin() && last == this->end())
					this->clear();
				else {
					while (first != last)
						erase(first++);
				}
			}

			void	erase(Node* x) {
				while (x != 0) {
					erase(right(x));
					Node* y = left(x);
					destroyNode(x);
					x = y;
				}
			}

			pair<iterator, bool>	insertUnique(const value_type& value) {
				Node* x =	this->root();
				Node* y =	this->nodeEnd();
				bool comp = true;

				while (x != 0) {
					y = x;
					comp = compare(KeyOfValue()(value), key(x));
					x = comp ? left(x) : right(x);
				}
				iterator j = iterator(y);
				if (comp) {
					if (j == iterator(begin()))
						return pair<iterator, bool>(insert(x, y, value), true);
					--j;
				}
				if (compare(key(j.node), KeyOfValue()(value)))
					return pair<iterator, bool>(insert(x, y, value), true);
				return pair<iterator, bool>(j, false);
			}

			iterator	insertUnique(iterator hint, const value_type& value) {
				if (hint.node == this->nodeEnd()) {
					if (this->count > 0	&& compare(key(this->rightmost()), KeyOfValue()(value)))
						return insert(0, rightmost(), value);
					else
						return insertUnique(value).first;
				} else if (compare(KeyOfValue()(value),	key(hint.node))) {
					iterator before = hint;
					if (hint.node == this->leftmost())
						return insert(this->leftmost(), this->leftmost(), value);
					else if (compare(key((--before).node),KeyOfValue()(value))) {
						if (right(before.node) == 0)
							return insert(0, before.node, value);
						else 
							return insert(hint.node, hint.node, value);
					} else
						return insertUnique(value).first;
				} else if (compare(key(hint.node),KeyOfValue()(value))) {
						iterator after = hint;
						if (hint.node == this->rightmost())
							return insert(0, this->rightmost(), value);
						else if (compare(KeyOfValue()(value),key((++after).node))) {
							if (right(hint.node) == 0)
								return insert (0, hint.node, value);
							else
								return insert(after.node, after.node, value);
						} else
							return insertUnique(value).first;
				} else
					return hint;
			}

			template<typename InputIt>
			void	insertUnique(InputIt first, InputIt last) {
				for (; first != last; ++first)
					insertUnique(end(), *first);
			}

			key_compare	key_comp() const{ return compare; }

			void	swap(RBTree& other) {
				std::swap(this->root(), other.root());
				std::swap(this->leftmost(), other.leftmost());
				std::swap(this->rightmost(), other.rightmost());
				if (this->root() != 0)
					this->root()->parent = this->nodeEnd();
				else {
					this->header.left = &this->header;
					this->header.right = &this->header;
				}
				if (other.root() != 0)
					other.root()->parent = other.nodeEnd();
				else {
					this->header.left = &this->header;
					this->header.right = &this->header;
				}
				std::swap(this->count, other.count);
				std::swap(this->compare, other.compare);
			}

		static void	leftRotate(Node*& root, Node* const node) {
			Node* const y = node->right;

			node->right = y->left;
			if (y->left != 0)
				y->left->parent = node;
			y->parent = node->parent;

			if (node == root)
				root = y;
			else if (node == node->parent->left)
				node->parent->left = y;
			else
				node->parent->right = y;
			y->left = node;
			node->parent = y;
		}

		static void	rightRotate(Node*& root, Node* const node) {
			Node* const y = node->left;

			node->left = y->right;
			if (y->right != 0)
				y->right->parent = node;
			y->parent = node->parent;

			if (node == root)
				root = y;
			else if (node == node->parent->right)
				node->parent->right = y;
			else 
				node->parent->left = y;
			y->right = node;
			node->parent = y;
		}

		void	rebalance(Node*& root, Node*& x)
		{
			while (x != root && x->parent->color == red) {
				Node* const grandParent = x->_grandParent;

				if (x->parent == grandParent->left) {
					Node* const uncle = grandParent->right;

					if (uncle && uncle->color == red) {
						x->parent->color = black;
						uncle->color = black;
						grandParent->color = red;
						x = grandParent;
					} else {
						if (x == x->parent->right) {
							x = x->parent;
							leftRotate(root, x);
						}
						x->parent->color = black;
						grandParent->color = red;
						rightRotate(root, grandParent);
					}
				} else {
					Node* const uncle = grandParent->left;
					if (uncle && uncle->color == red) {
						x->parent->color = black;
						uncle->color = black;
						grandParent->color = red;
						x = grandParent;
					} else {
						if (x == x->parent->left) {
							x = x->parent;
							rightRotate(root, x);
						}
						x->parent->color = black;
						grandParent->color = red;
						leftRotate(root, grandParent);
					}
				}
			}
			root->color = black;
		}

		/**
		 * @brief
		 * insert a node in the actual tree and rebalance it
		 * @param[in] insertLeft bool value
		 * @param[in] x the node to insert
		 * @param[in] p x's parent
		 * @param[in] header header of the tree
		 * @details
		 * if insertLeft is true, make x the left child of p
		 * else make x the right child of p
		 * if tree is empty, set x as the root (header.parent)
		 * if p is rightmost or leftmost, update the header
		 */
		void	insertAndRebalance(const bool insertLeft, Node* x, Node* p, Node& header)
		{
			Node*& root = header.parent;
			x->parent = p;
			x->left = 0;
			x->right = 0;
			x->color = red;

			if (insertLeft) {
				p->left = x;

				if (p == &header) {
					header.parent = x;
					header.right = x;
				} else if (p == header.left)
					header.left = x;
			} else {
				p->right = x;
				if (p == header.right)
					header.right = x;
			}
			rebalance(root, x);
		}

		/**
		 * @brief delete a node in the tree and rebalanced it
		 * @param z the node to delete
		 * @param header the header of the tree
		 * @return the node to be deleted
		 * @details
		 * first conditions block check z's child
		 * second conditions block whether link z's successor in place of z
		 * or rearrange z parent according to z's position in  the tree
		 * then finally we rebalance the tree
		 */
		Node*	eraseAndRebalance(Node* const z, Node& header) {
			Node*& root = header.parent;
			Node*& leftmost = header.left;
			Node*& rightmost = header.right;
			Node* y = z;
			Node* x = 0;
			Node* x_parent = 0;

			if (y->left == 0)
				x = y->right;
			else {
				if (y->right == 0)
					x = y->left;
				else {
					y = y->right;
					while (y->left != 0)
						y = y->left;
					x = y->right;
				}
			}

			if (y != z) {
				z->left->parent = y;
				y->left = z->left;
				if (y != z->right) {
					x_parent = y->parent;
					if (x)
						x->parent = y->parent;
					y->parent->left = x;
					y->right = z->right;
					z->right->parent = y;
				} else
					x_parent = y;
				if (root == z)
					root = y;
				else if (z->parent->left == z)
					z->parent->left = y;
				else
					z->parent->right = y;
				y->parent = z->parent;
				std::swap(y->color, z->color);
				y = z;
			} else {
				x_parent = y->parent;
				if (x)
					x->parent = y->parent;
				if (root == z)
					root = x;
				else {
					if (z->parent->left == z)
						z->parent->left = x;
					else
						z->parent->right = x;
				}
				if (leftmost == z) {
					if (z->right == 0)
						leftmost = z->parent;
					else
						leftmost = minimum(x);
				}
				if (rightmost == z) {
					if (z->left == 0)
						rightmost = z->parent;
					else
						rightmost = maximum(x);
				}
			}

			if (y->color != red) {
				while (x != root && (x == 0 || x->color == black)) {
					if (x == x_parent->left) {
						Node* w = x_parent->right;
						if (w->color == red) {
							w->color = black;
							x_parent->color = red;
							leftRotate(root, x_parent);
							w = x_parent->right;
						}
						if ((w->left == 0 ||
							w->left->color == black) &&
							(w->right == 0 ||
							w->right->color == black)) {
							w->color = red;
							x = x_parent;
							x_parent = x_parent->parent;
						} else {
							if (w->right == 0 ||
								w->right->color == black) {
								w->left->color = black;
								w->color = red;
								rightRotate(root, w);
								w = x_parent->right;
							}
							w->color = x_parent->color;
							x_parent->color = black;
							if (w->right)
								w->right->color = black;
							leftRotate(root, x_parent);
							break;
						}
					} else {
						Node* w = x_parent->left;
						if (w->color == red) {
							w->color = black;
							x_parent->color = red;
							rightRotate(root, x_parent);
							w = x_parent->left;
						}
						if ((w->right == 0 ||
							w->right->color == black) &&
							(w->left == 0 ||
							w->left->color == black)) {
							w->color = red;
							x = x_parent;
							x_parent = x_parent->parent;
						} else {
							if (w->left == 0 || w->left->color == black) {
								w->right->color = black;
								w->color = red;
								leftRotate(root, w);
								w = x_parent->left;
							}
							w->color = x_parent->color;
							x_parent->color = black;
							if (w->left)
								w->left->color = black;
							rightRotate(root, x_parent);
							break;
						}
					}
				}
				if (x)
					x->color = black;
			}
			return y;
		}
	};

} // namespace ft

#endif