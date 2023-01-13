/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennyduong <kennyduong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:17:18 by kennyduong        #+#    #+#             */
/*   Updated: 2023/01/12 18:19:58 by kennyduong       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include <cstddef>

namespace ft 
{
	struct bidirectional_iterator_tag {};
	struct random_access_iterator_tag {};
	
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

	template<class Iter> class reverse_iterator {
		protected:
			Iter	_current;
			
		public:
			typedef Iter												iterator_type;
			typedef typename iterator_traits<Iter>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iter>::value_type			value_type;
			typedef typename iterator_traits<Iter>::difference_type		difference_type;
			typedef typename iterator_traits<Iter>::pointer				pointer;
			typedef typename iterator_traits<Iter>::reference			reference;
		
			// --------- Constructors
			reverse_iterator() : _current() {}
			explicit reverse_iterator(Iter x) : _current(x) {}
			template<class U> reverse_iterator(const reverse_iterator<U>& src) : _current(src.base()) {}
			virtual ~reverse_iterator() {} // Destructor
			
			// ---------- Operators
			template<class U>
			reverse_iterator& 	operator=(const reverse_iterator<U>& other) {_current = other.base(); return *this;}
			
			iterator_type 		base() const {return _current;}
			reference 			operator*() const {Iter tmp = _current; return *--tmp;}
			pointer 			operator->() const {return &(operator*());}
			reference			operator[]( difference_type n ) const {return _current[-n-1];}
			reverse_iterator& 	operator++() {--_current;	return *this;}
			reverse_iterator 	operator++(int) {reverse_iterator tmp = *this; --_current; return tmp;}
			reverse_iterator& 	operator--() {++_current; return *this;}
			reverse_iterator	operator--(int) {reverse_iterator tmp = *this; ++_current; return tmp;}
			reverse_iterator 	operator+(difference_type n) const {return reverse_iterator(_current - n);}
			reverse_iterator& 	operator+=(difference_type n) {_current -= n; return *this;}
			reverse_iterator 	operator-(difference_type n) const {return reverse_iterator(_current + n);}
			reverse_iterator& 	operator-=(difference_type n) {_current += n; return *this;}
	};
	
	template< class Iter >
	reverse_iterator<Iter> operator+( typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it )
	{return reverse_iterator<Iter>(it.base() - n);}
	
	template< class Iterator1, class Iterator2 >
	typename reverse_iterator<Iterator1>::difference_type operator-( const reverse_iterator<Iterator1>& lhs,const reverse_iterator<Iterator2>& rhs )
	{return rhs.base() - lhs.base();}
	
	template<class Iter1, class Iter2> bool operator==(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {return lhs.base() == rhs.base();}
	template<class Iter1, class Iter2> bool operator!=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {return lhs.base() != rhs.base();}
	template<class Iter1, class Iter2> bool operator<(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {return lhs.base() > rhs.base();}
	template<class Iter1, class Iter2> bool operator<=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {return lhs.base() >= rhs.base();}
	template<class Iter1, class Iter2> bool operator>(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {return lhs.base() < rhs.base();}
	template<class Iter1, class Iter2> bool operator>=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs) {return lhs.base() <= rhs.base();}
	
	template<class T> class bidirectional_iterator : public iterator<bidirectional_iterator_tag, T> {
		protected:
			T*	_ptr;
		
		public:
			typedef T											value_type;
			typedef T*											pointer;
			typedef T&											reference;
			typedef bidirectional_iterator_tag					iterator_category;
			typedef ptrdiff_t									difference_type;
		
			bidirectional_iterator() : _ptr(NULL) {}
			bidirectional_iterator(T* ptr) : _ptr(ptr) {}
			bidirectional_iterator(const bidirectional_iterator& src) : _ptr(src._ptr) {}
			virtual ~bidirectional_iterator() {}
			
			bidirectional_iterator& operator=(const bidirectional_iterator& src) {
				if (this != &src)
					_ptr = src._ptr;
				return *this;
			}
			
			bool 					operator==(const bidirectional_iterator& src) const {return _ptr == src._ptr;}
			bool 					operator!=(const bidirectional_iterator& src) const { return _ptr != src._ptr;}
			
			reference				operator*() const {return *_ptr;}
			pointer					operator->() const {return _ptr;}
			
			bidirectional_iterator& operator++() {++_ptr; return *this;}
			bidirectional_iterator& operator--() {--_ptr; return *this;}
			bidirectional_iterator& operator++(int) { bidirectional_iterator tmp(*this); ++_ptr; return tmp; }
			bidirectional_iterator& operator--(int) { bidirectional_iterator tmp(*this); --_ptr; return tmp; }
	};

	template<class T> class random_access_iterator : public iterator<random_access_iterator_tag, T> {
		protected:
			T*	_ptr;

		public:
			typedef T											value_type;
			typedef T*											pointer;
			typedef T&											reference;
			typedef random_access_iterator_tag					iterator_category;
			typedef ptrdiff_t									difference_type;
		
			random_access_iterator() : _ptr(NULL) {}
			random_access_iterator(T* ptr) : _ptr(ptr) {}
			random_access_iterator(const random_access_iterator& src) : _ptr(src._ptr) {}
			virtual ~random_access_iterator() {}
			
			random_access_iterator& operator=(const random_access_iterator& src) {
				if (this != &src)
					_ptr = src._ptr;
				return *this;
			}

			bool 					operator==(const random_access_iterator& src) const {return _ptr == src._ptr;}
			bool 					operator!=(const random_access_iterator& src) const { return _ptr != src._ptr;}
			bool 					operator<(const random_access_iterator& src) const {return _ptr < src._ptr;}
			bool 					operator>(const random_access_iterator& src) const {return _ptr > src._ptr;}
			bool 					operator<=(const random_access_iterator& src) const {return _ptr <= src._ptr;}
			bool 					operator>=(const random_access_iterator& src) const {return _ptr >= src._ptr;}

			reference 				operator[](difference_type n) const {return _ptr[n];}
			reference				operator*() const {return *_ptr;}
			pointer					operator->() const {return _ptr;}

			random_access_iterator& operator++() {++_ptr; return *this;}
			random_access_iterator& operator--() {--_ptr; return *this;}
			random_access_iterator operator++(int) { random_access_iterator tmp(*this); ++_ptr; return tmp; }
			random_access_iterator operator--(int) { random_access_iterator tmp(*this); --_ptr; return tmp; }
			random_access_iterator& operator+=(difference_type n) {_ptr += n; return *this;}
			random_access_iterator& operator-=(difference_type n) {_ptr -= n; return *this;}
			random_access_iterator	operator+(difference_type n) const {return random_access_iterator(_ptr + n);}
			random_access_iterator	operator-(difference_type n) const {return random_access_iterator(_ptr - n);}

			difference_type			operator+(const random_access_iterator& src) const {return _ptr + src._ptr;}
			difference_type			operator-(const random_access_iterator& src) const {return _ptr - src._ptr;}
	};

	template <typename T1, typename T2>
	bool operator==(const random_access_iterator<T1>& lhs, const random_access_iterator<T2>& rhs) {return (lhs.base() == rhs.base());}
	
	template <typename T1, typename T2>
	bool operator!=(const random_access_iterator<T1>& lhs, const random_access_iterator<T2>& rhs) {return (lhs.base() != rhs.base());}
	
	template <typename T1, typename T2>
	bool operator< (const random_access_iterator<T1>& lhs, const random_access_iterator<T2>& rhs) {return (lhs.base() < rhs.base());}
	
	template <typename T1, typename T2>
	bool operator> (const random_access_iterator<T1>& lhs, const random_access_iterator<T2>& rhs) {return (lhs.base() > rhs.base());}
	
	template <typename T1, typename T2>
	bool operator<=(const random_access_iterator<T1>& lhs, const random_access_iterator<T2>& rhs) {return (lhs.base() <= rhs.base());}
	
	template <typename T1, typename T2>
	bool operator>=(const random_access_iterator<T1>& lhs, const random_access_iterator<T2>& rhs) {return (lhs.base() >= rhs.base());}

	template <typename T>
	random_access_iterator<T> operator+(typename random_access_iterator<T>::difference_type n, const random_access_iterator<T>& rev_it) {
		return (rev_it + n);
	}

	template <typename T1, typename T2>
	typename random_access_iterator<T1>::difference_type operator-(const random_access_iterator<T1>& lhs, const random_access_iterator<T2>& rhs) {
		return (lhs.base() - rhs.base());
	}

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