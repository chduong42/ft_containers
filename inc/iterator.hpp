/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennyduong <kennyduong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 15:17:18 by kennyduong        #+#    #+#             */
/*   Updated: 2022/08/24 15:39:26 by kennyduong       ###   ########.fr       */
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
	
	template<class T> class bidirectional_iterator : public iterator<bidirectional_iterator_tag, T> {
		protected:
			T*	_ptr;
		
		public:
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

	template<class T> class random_access_iterator : iterator<random_access_iterator_tag, T> {
		protected:
			T*	_ptr;

		public:
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
			random_access_iterator& operator++(int) { random_access_iterator tmp(*this); ++_ptr; return tmp; }
			random_access_iterator& operator--(int) { random_access_iterator tmp(*this); --_ptr; return tmp; }
			random_access_iterator& operator+=(difference_type n) {_ptr += n; return *this;}
			random_access_iterator& operator-=(difference_type n) {_ptr -= n; return *this;}
			random_access_iterator&	operator+(difference_type n) const {return random_access_iterator(_ptr + n);}
			random_access_iterator&	operator-(difference_type n) const {return random_access_iterator(_ptr - n);}

			difference_type			operator+(const random_access_iterator& src) const {return _ptr + src._ptr;}
			difference_type			operator-(const random_access_iterator& src) const {return _ptr - src._ptr;}
	};

	template<class I> class reverse_iterator : public iterator<typename iterator_traits<I>::iterator_category, typename iterator_traits<I>::value_type> {
		protected:
			I	_ptr;
		
		public:
			reverse_iterator() : _ptr(NULL) {}
			reverse_iterator(I ptr) : _ptr(ptr) {}
			reverse_iterator(const reverse_iterator& src) : _ptr(src._ptr) {}
			virtual ~reverse_iterator() {}
			
			reverse_iterator& operator=(const reverse_iterator& src) {
				if (this != &src)
					_ptr = src._ptr;
				return *this;
			}
			
			bool 				operator==(const reverse_iterator& src) const {return _ptr == src._ptr;}
			bool 				operator!=(const reverse_iterator& src) const { return _ptr != src._ptr;}
			bool 				operator<(const reverse_iterator& src) const {return _ptr < src._ptr;}
			bool 				operator>(const reverse_iterator& src) const {return _ptr > src._ptr;}
			bool 				operator<=(const reverse_iterator& src) const {return _ptr <= src._ptr;}
			bool 				operator>=(const reverse_iterator& src) const {return _ptr >= src._ptr;}
			
			reference			operator[](difference_type n) const {return _ptr[n];}
			reference			operator*() const {return *_ptr;}
			pointer				operator->() const {return _ptr;}

			reverse_iterator&	operator++() {--_ptr; return *this;}
			reverse_iterator&	operator--() {++_ptr; return *this;}
			reverse_iterator&	operator++(int) { reverse_iterator tmp(*this); --_ptr; return tmp; }
			reverse_iterator&	operator--(int) { reverse_iterator tmp(*this); ++_ptr; return tmp; }
			reverse_iterator&	operator+=(difference_type n) {_ptr -= n; return *this;}
			reverse_iterator&	operator-=(difference_type n) {_ptr += n; return *this;}
			reverse_iterator&	operator+(difference_type n) const {return reverse_iterator(_ptr - n);}
			reverse_iterator&	operator-(difference_type n) const {return reverse_iterator(_ptr + n);}

			difference_type		operator+(const reverse_iterator& src) const {return _ptr - src._ptr;}
			difference_type		operator-(const reverse_iterator& src) const {return _ptr + src._ptr;}
			
			I					base() const {return _ptr;}
	};
}

#endif