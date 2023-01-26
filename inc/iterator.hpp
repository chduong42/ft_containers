/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:17:18 by kennyduong        #+#    #+#             */
/*   Updated: 2023/01/26 19:03:10 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include <cstddef>
# include "RBTree.hpp"

namespace ft 
{
	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };
	
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
		typedef random_access_iterator_tag					iterator_category;
		typedef T											value_type;
		typedef ptrdiff_t									difference_type;
		typedef T*											pointer;
		typedef T&											reference;
	};
	
	template<class T> struct iterator_traits<const T*> {
		typedef random_access_iterator_tag					iterator_category;
		typedef T											value_type;
		typedef ptrdiff_t									difference_type;
		typedef const T*									pointer;
		typedef const T&									reference;
	};

	// ---------- Reverse iterator
	template<class Iter>
	class reverse_iterator {
		public:
			typedef Iter												iterator_type;
			typedef typename iterator_traits<Iter>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iter>::value_type			value_type;
			typedef typename iterator_traits<Iter>::difference_type		difference_type;
			typedef typename iterator_traits<Iter>::pointer				pointer;
			typedef typename iterator_traits<Iter>::reference			reference;
		
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
	
	template<class Iter1, class Iter2> inline bool operator==(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)	{return lhs.base() == rhs.base();}
	template<class Iter1, class Iter2> inline bool operator!=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)	{return lhs.base() != rhs.base();}
	template<class Iter1, class Iter2> inline bool operator<(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)	{return lhs.base() >  rhs.base();}
	template<class Iter1, class Iter2> inline bool operator<=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)	{return lhs.base() >= rhs.base();}
	template<class Iter1, class Iter2> inline bool operator>(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)	{return lhs.base() <  rhs.base();}
	template<class Iter1, class Iter2> inline bool operator>=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)	{return lhs.base() <= rhs.base();}
	
	template<class Iterator> inline reverse_iterator<Iterator> 
	operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) {return rev_it + n;}
	
	template< class Iterator1, class Iterator2 > inline typename reverse_iterator<Iterator1>::difference_type
    operator-( const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs ) {return rhs.base() - lhs.base();}
	// ---------- End of Reverse iterator


	// ---------- Random access iterator
	template<class T>
	class random_access_iterator : public iterator<random_access_iterator_tag, T> {
		public:
			using typename iterator<random_access_iterator_tag, T>::value_type;
			using typename iterator<random_access_iterator_tag, T>::difference_type;
			using typename iterator<random_access_iterator_tag, T>::pointer;
			using typename iterator<random_access_iterator_tag, T>::reference;
			using typename iterator<random_access_iterator_tag, T>::iterator_category;

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

	template<class Iter1, class Iter2> inline bool operator==(const random_access_iterator<Iter1>& lhs, const random_access_iterator<Iter2>& rhs)	{return lhs.base() == rhs.base();}
	template<class Iter1, class Iter2> inline bool operator!=(const random_access_iterator<Iter1>& lhs, const random_access_iterator<Iter2>& rhs)	{return lhs.base() != rhs.base();}
	template<class Iter1, class Iter2> inline bool operator<(const random_access_iterator<Iter1>& lhs, const random_access_iterator<Iter2>& rhs)	{return lhs.base() <  rhs.base();}
	template<class Iter1, class Iter2> inline bool operator<=(const random_access_iterator<Iter1>& lhs, const random_access_iterator<Iter2>& rhs)	{return lhs.base() <= rhs.base();}
	template<class Iter1, class Iter2> inline bool operator>(const random_access_iterator<Iter1>& lhs, const random_access_iterator<Iter2>& rhs)	{return lhs.base() >  rhs.base();}
	template<class Iter1, class Iter2> inline bool operator>=(const random_access_iterator<Iter1>& lhs, const random_access_iterator<Iter2>& rhs)	{return lhs.base() >= rhs.base();}
	
	template<class Iterator> inline random_access_iterator<Iterator> 
	operator+ (typename random_access_iterator<Iterator>::difference_type n, const random_access_iterator<Iterator>& rev_it) {return rev_it + n;}
	
	template<class Iter1, class Iter2> inline typename random_access_iterator<Iter1>::difference_type
	operator- (const random_access_iterator<Iter1>& lhs,const random_access_iterator<Iter2>& rhs) {return lhs.base() - rhs.base();}
	// ---------- End of Random access iterator


	// ---------- RB Tree iterator
	template<typename T>
	class RBTree_iterator {
		public:
			typedef T										value_type;
			typedef T*										pointer;
			typedef T&										reference;
			typedef bidirectional_iterator_tag				iterator_category;
			typedef ptrdiff_t								difference_type;
			
		protected:
			Node<T>*										_node;
		
		public:
			RBTree_iterator() 							: _node(NULL) {}
			explicit RBTree_iterator(Node<T>* node) 	: _node(node) {}
			RBTree_iterator(const RBTree_iterator& src) : _node(src._node) {}
			virtual ~RBTree_iterator() {}
			
			RBTree_iterator& operator=(const RBTree_iterator& src) {
				if (this != &src) {
					_node = src._node;
					_root = src._root;
					_nil = src._nil;
				}
				return *this;
			}

			operator RBTree_iterator<const value_type>() const {return RBTree_iterator<const value_type>(_node);}

			pointer						base() const {return _node;}
			pointer						operator->() const {return _node;}
			reference					operator*() const {return _node->value;}
			reference 					operator[](difference_type n) const {return _node[n];}

			RBTree_iterator& 			operator++() {_node = _node->next(); return *this;}
			RBTree_iterator& 			operator--() {_node = _node->prev(); return *this;}
			RBTree_iterator				operator++(int) {RBTree_iterator tmp(*this); _node = _node->next(); return tmp; }
			RBTree_iterator				operator--(int) {RBTree_iterator tmp(*this); _node = _node->prev(); return tmp; }
			
			friend bool					operator==(const RBTree_iterator& rhs) const {return _node == rhs._node;}
			friend bool					operator!=(const RBTree_iterator& rhs) const {return _node != rhs._node;}	
	};

	template<typename T> inline bool operator==(const RBTree_iterator<T>& lhs, const RBTree_iterator<T>& rhs) {return lhs.base() == rhs.base();}
	template<typename T> inline bool operator!=(const RBTree_iterator<T>& lhs, const RBTree_iterator<T>& rhs) {return lhs.base() != rhs.base();}
	// ---------- End of RB tree iterator


	// utility functions
	template<typename Iterator>
	std::ptrdiff_t distance(Iterator first, Iterator last) {
		std::ptrdiff_t dist = 0;
		while (first != last) {
			++dist;
			++first;
		}
		return (dist);
	}

}

#endif