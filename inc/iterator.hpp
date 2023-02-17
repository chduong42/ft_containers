/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:17:18 by kennyduong        #+#    #+#             */
/*   Updated: 2023/02/17 20:38:22 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include <cstddef>
# include <iterator>
# include "RBNode.hpp"

namespace ft 
{
	template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator {
		typedef Category									iterator_category;
		typedef T											value_type;
		typedef Distance									difference_type;
		typedef Pointer										pointer;
		typedef Reference									reference;
	};
	
	template<class Iterator> struct iterator_traits {
		typedef typename Iterator::iterator_category		iterator_category;
		typedef typename Iterator::value_type				value_type;
		typedef typename Iterator::difference_type			difference_type;
		typedef typename Iterator::pointer					pointer;
		typedef typename Iterator::reference				reference;
	};

	template<class T> struct iterator_traits<T*> {
		typedef std::random_access_iterator_tag				iterator_category;
		typedef T											value_type;
		typedef ptrdiff_t									difference_type;
		typedef T*											pointer;
		typedef T&											reference;
	};
	
	template<class T> struct iterator_traits<const T*> {
		typedef std::random_access_iterator_tag				iterator_category;
		typedef T											value_type;
		typedef ptrdiff_t									difference_type;
		typedef const T*									pointer;
		typedef const T&									reference;
	};

	// ---------- Reverse iterator
	template<class Iter>
	class reverse_iterator {
		public:
			typedef Iter													iterator_type;
			typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iter>::value_type			value_type;
			typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iter>::pointer				pointer;
			typedef typename ft::iterator_traits<Iter>::reference			reference;
		
		protected:
			iterator_type												_base;
			
		public:
			// --------- Constructors
			reverse_iterator() 													: _base() {}
			explicit reverse_iterator(Iter node) 									: _base(node) {}
			template<class U> reverse_iterator(const reverse_iterator<U>& src)	: _base(src.base()) {}
			virtual ~reverse_iterator() {} // Destructor
			
			// ---------- Operators
			template<class U>
			reverse_iterator& 	operator=(const reverse_iterator<U>& other) {_base = other.base(); return *this;}

			iterator_type 		base() const {return _base;}
			reference			operator[]( difference_type n ) const {return _base[-n-1];}
			reference 			operator*() const {Iter tmp = _base; return *--tmp;}
			pointer 			operator->() const {return &(operator*());}
			
			reverse_iterator& 	operator++() {--_base;	return *this;}
			reverse_iterator& 	operator--() {++_base; return *this;}
			reverse_iterator 	operator++(int) {reverse_iterator tmp = *this; --_base; return tmp;}
			reverse_iterator	operator--(int) {reverse_iterator tmp = *this; ++_base; return tmp;}
			reverse_iterator& 	operator+=(difference_type n) {_base -= n; return *this;}
			reverse_iterator& 	operator-=(difference_type n) {_base += n; return *this;}
			reverse_iterator 	operator+(difference_type n) const {return reverse_iterator(_base - n);}
			reverse_iterator 	operator-(difference_type n) const {return reverse_iterator(_base + n);}
	};
	
	template<class Iter1, class Iter2> inline bool operator==(const ft::reverse_iterator<Iter1>& lhs, const ft::reverse_iterator<Iter2>& rhs)	{return lhs.base() == rhs.base();}
	template<class Iter1, class Iter2> inline bool operator!=(const ft::reverse_iterator<Iter1>& lhs, const ft::reverse_iterator<Iter2>& rhs)	{return lhs.base() != rhs.base();}
	template<class Iter1, class Iter2> inline bool operator<(const ft::reverse_iterator<Iter1>& lhs, const ft::reverse_iterator<Iter2>& rhs)	{return lhs.base() >  rhs.base();}
	template<class Iter1, class Iter2> inline bool operator<=(const ft::reverse_iterator<Iter1>& lhs, const ft::reverse_iterator<Iter2>& rhs)	{return lhs.base() >= rhs.base();}
	template<class Iter1, class Iter2> inline bool operator>(const ft::reverse_iterator<Iter1>& lhs, const ft::reverse_iterator<Iter2>& rhs)	{return lhs.base() <  rhs.base();}
	template<class Iter1, class Iter2> inline bool operator>=(const ft::reverse_iterator<Iter1>& lhs, const ft::reverse_iterator<Iter2>& rhs)	{return lhs.base() <= rhs.base();}
	
	template<class Iterator> inline reverse_iterator<Iterator> 
	operator+ (typename ft::reverse_iterator<Iterator>::difference_type n, const ft::reverse_iterator<Iterator>& rev_it) {return rev_it + n;}
	
	template< class Iterator1, class Iterator2 > inline typename ft::reverse_iterator<Iterator1>::difference_type
    operator-( const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs ) {return rhs.base() - lhs.base();}
	// ---------- End of Reverse iterator


	// ---------- Random access iterator
	template<class T>
	class random_access_iterator : public ft::iterator<std::random_access_iterator_tag, T> {
		public:
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::value_type				value_type;
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::difference_type			difference_type;
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::pointer					pointer;
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::reference				reference;
			typedef typename ft::iterator<std::random_access_iterator_tag, T>::iterator_category		iterator_category;

		protected:
			pointer														_ptr;

		public:
			random_access_iterator() 									: _ptr(NULL) {}
			random_access_iterator(T* ptr) 								: _ptr(ptr) {}
			random_access_iterator(const random_access_iterator& src) 	: _ptr(src._ptr) {}
			virtual ~random_access_iterator() {}
			
			random_access_iterator& operator=(const random_access_iterator& src) {
				if (this != &src)
					_ptr = src._ptr;
				return *this;
			}

			operator random_access_iterator<const value_type>() const {return random_access_iterator<const value_type>(_ptr);}

			pointer						base() const {return _ptr;}
			pointer						operator->() const {return _ptr;}
			reference					operator*() const {return *_ptr;}
			reference 					operator[](difference_type n) const {return _ptr[n];}

			random_access_iterator& 	operator++() {++_ptr; return *this;}
			random_access_iterator& 	operator--() {--_ptr; return *this;}
			random_access_iterator		operator++(int) { random_access_iterator tmp(*this); ++_ptr; return tmp; }
			random_access_iterator		operator--(int) { random_access_iterator tmp(*this); --_ptr; return tmp; }
			random_access_iterator& 	operator+=(difference_type n) {_ptr += n; return *this;}
			random_access_iterator& 	operator-=(difference_type n) {_ptr -= n; return *this;}
			random_access_iterator		operator+(difference_type n) const {return _ptr + n;}
			random_access_iterator		operator-(difference_type n) const {return _ptr - n;}
	};

	template<class Iter1, class Iter2> inline bool operator==(const ft::random_access_iterator<Iter1>& lhs, const ft::random_access_iterator<Iter2>& rhs)	{return lhs.base() == rhs.base();}
	template<class Iter1, class Iter2> inline bool operator!=(const ft::random_access_iterator<Iter1>& lhs, const ft::random_access_iterator<Iter2>& rhs)	{return lhs.base() != rhs.base();}
	template<class Iter1, class Iter2> inline bool operator<(const ft::random_access_iterator<Iter1>& lhs, const ft::random_access_iterator<Iter2>& rhs)	{return lhs.base() <  rhs.base();}
	template<class Iter1, class Iter2> inline bool operator<=(const ft::random_access_iterator<Iter1>& lhs, const ft::random_access_iterator<Iter2>& rhs)	{return lhs.base() <= rhs.base();}
	template<class Iter1, class Iter2> inline bool operator>(const ft::random_access_iterator<Iter1>& lhs, const ft::random_access_iterator<Iter2>& rhs)	{return lhs.base() >  rhs.base();}
	template<class Iter1, class Iter2> inline bool operator>=(const ft::random_access_iterator<Iter1>& lhs, const ft::random_access_iterator<Iter2>& rhs)	{return lhs.base() >= rhs.base();}
	
	template<class Iterator> inline ft::random_access_iterator<Iterator> 
	operator+ (typename ft::random_access_iterator<Iterator>::difference_type n, const ft::random_access_iterator<Iterator>& rev_it) {return rev_it + n;}
	
	template<class Iter1, class Iter2> inline typename random_access_iterator<Iter1>::difference_type
	operator- (const ft::random_access_iterator<Iter1>& lhs, const ft::random_access_iterator<Iter2>& rhs) {return lhs.base() - rhs.base();}
	// ---------- End of Random access iterator
	
	// utility functions
	template<typename Iterator>
	typename iterator_traits<Iterator>::difference_type distance(Iterator first, Iterator last) {
		typename iterator_traits<Iterator>::difference_type dist = 0;
		while (first != last) {
			++dist;
			++first;
		}
		return (dist);
	}

	template< class T, class N >
	class tree_iterator	: public std::iterator<std::bidirectional_iterator_tag, T> {
		public:
			typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::value_type			value_type;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::difference_type		difference_type;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::pointer				pointer;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::reference			reference;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::iterator_category	iterator_category;
			typedef const value_type* 																const_pointer;
			typedef const value_type& 																const_reference;
			typedef N 																				node_type;
			typedef node_type*																		node_ptr;

		protected:
			node_ptr 																				_ptr;
			node_ptr 																				_root;
			node_ptr 																				_nil;
		
		public:
			tree_iterator() 											: _ptr(NULL), _root(NULL), _nil(NULL) {}
			tree_iterator(node_ptr ptr, node_ptr root, node_ptr nil) 	: _ptr(ptr), _root(root), _nil(nil) {}
			tree_iterator(tree_iterator const &lhs) 					: _ptr(lhs._ptr), _root(lhs._root), _nil(lhs._nil) {}
			virtual ~tree_iterator() {}
			
			tree_iterator 		&operator=(tree_iterator const &lhs)	{
				if (this == &lhs)
					return (*this);
				this->_ptr = lhs._ptr;
				this->_root = lhs._root;
				this->_nil = lhs._nil;
				return (*this);
			}

			reference 			operator*() {return (_ptr->data);}
			const_reference 	operator*() const {return (_ptr->data);}
			pointer 			operator->() {return (&(operator*()));}
			const_pointer 		operator->() const {return (&(operator*()));}

			tree_iterator &operator++()	{
				if (_ptr != _nil)
					_ptr = successor(_ptr, _nil);
				return (*this);
			}

			tree_iterator &operator--()	{
				if (_ptr == _nil)
					_ptr = maxNode(_root, _nil);
				else
					_ptr = predecessor(_ptr, _nil);
				return (*this);
			}

			tree_iterator 		operator++(int)	{tree_iterator tmp(*this); operator++(); return (tmp);}
			tree_iterator 		operator--(int)	{tree_iterator tmp(*this); operator--(); return (tmp);}

			bool 				operator==(tree_iterator<value_type, node_type> const &lhs) const 	{return (this->_ptr == lhs._ptr);}
			bool 				operator!=(tree_iterator<value_type, node_type> const &lhs) const	{return (this->_ptr != lhs._ptr);}
			
			// Overload called when trying to copy construct a const_iterator
			// based on an iterator
			operator tree_iterator<value_type const, node_type const>() const {return tree_iterator<value_type const, node_type const>(_ptr, _root, _nil);}
		
		protected:
			// find the successor of a given node
			node_ptr successor(node_ptr node, node_ptr nil)	{
				// if the right subtree is not null the successor is the leftmost node in the sright subtree
				if (node->right != nil)
					return minNode(node->right, nil);
				// else it is the lowest ancestor of node whose left child is also an ancestor of node
				node_ptr parent = node->parent;
				while (parent != NULL && node == parent->right)	{
					node = parent;
					parent = parent->parent;
				}
				if (parent == NULL)
					return nil;
				return parent;
			}

			// find the predecessor of a given node
			node_ptr predecessor(node_ptr node, node_ptr nil)	{
				// if the left subtree is not null the predecessor is the rightmost node in the left subtree
				if (node->left != nil)
					return maxNode(node->left, nil);
				node_ptr parent = node->parent;
				while (parent != NULL && node == parent->left)	{
					node = parent;
					parent = parent->parent;
				}
				return parent;
			}
	};

} // namespace ft

#endif