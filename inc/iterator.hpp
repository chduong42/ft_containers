/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:17:18 by kennyduong        #+#    #+#             */
/*   Updated: 2023/02/16 17:08:41 by chduong          ###   ########.fr       */
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
			explicit reverse_iterator(Iter x) 									: _base(x) {}
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

	// ---------- Tree iterator
	template<typename Pair, class Node>
	class tree_iterator : public ft::iterator<std::bidirectional_iterator_tag, Pair> 
	{
		public:
			typedef typename ft::iterator<std::bidirectional_iterator_tag, Pair>::value_type				value_type;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, Pair>::difference_type			difference_type;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, Pair>::pointer					pointer;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, Pair>::reference					reference;
			typedef typename ft::iterator<std::bidirectional_iterator_tag, Pair>::iterator_category			iterator_category;
	
			Node*													node;
			Node*													root;
			Node*													nil;	

			tree_iterator()											: node(NULL), root(NULL), nil(NULL) {}
			tree_iterator(Node* _node, Node* _root, Node* _nil)		: node(_node), root(_root), nil(_nil) {}
			tree_iterator(const tree_iterator& src)					: node(src.node), root(src.root), nil(src.nil) {}
			~tree_iterator() {}
			
			tree_iterator& operator=(const tree_iterator& src) {
				if (this != &src)	{
					node = src.node;
					root = src.root;
					nil = src.nil;
				}
				return *this;
			}

			operator tree_iterator<const value_type, Node>() const { return tree_iterator<const value_type, Node>(node, root, nil);}
			
			bool 				operator==(tree_iterator const &lhs) const {return (this->node == lhs.node);}
			bool 				operator!=(tree_iterator const &lhs) const {return (this->node != lhs.node);}
		
			reference           operator*() const { return this->node->data; }
			pointer     	    operator->() const { return &this->node->data; }
			
			tree_iterator&		operator++() {
				if (node != nil)
					node = next_node(node, nil);
				return *this;
			}
			
			tree_iterator&		operator--() {
				if (node == nil)
					node = max_node(root, nil);
				node = prev_node(node, nil);
				return *this;
			}
			
			tree_iterator 		operator++(int) {tree_iterator tmp = *this; ++*this; return tmp;}
			tree_iterator 		operator--(int) {tree_iterator tmp = *this; --*this; return tmp;}
	};

	template<typename P1, typename P2>
	inline bool operator==(const tree_iterator<P1, RBNode<P1> >& lhs, const tree_iterator<P2, RBNode<P2> >& rhs) {return lhs.node == rhs.node;}
	
	template<typename P1, typename P2>
	inline bool operator!=(const tree_iterator<P1, RBNode<P1> >& lhs, const tree_iterator<P2, RBNode<P2> >& rhs) {return !(lhs == rhs);}
	// ---------- End of tree iterator
}

#endif