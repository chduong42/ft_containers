/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennyduong <kennyduong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:56:26 by kennyduong        #+#    #+#             */
/*   Updated: 2023/01/20 18:28:57 by kennyduong       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <memory>
# include "utility.hpp"
# include "iterator.hpp"
# include "algorithm.hpp"
# include "type_traits.hpp"

namespace ft {
	
	template<class T, class Allocator = std::allocator<T> > class vector {
		public:
			// ====================== Member Types ========================= //
			typedef T															value_type;
			typedef Allocator													allocator_type;
			typedef ptrdiff_t													difference_type;
			typedef size_t														size_type;
			typedef	typename allocator_type::reference							reference;
			typedef typename allocator_type::const_reference					const_reference;
			typedef typename allocator_type::pointer							pointer;
			typedef typename allocator_type::const_pointer						const_pointer;
			typedef typename ft::random_access_iterator<value_type>				iterator;
			typedef typename ft::random_access_iterator<const value_type>		const_iterator;
			typedef typename ft::reverse_iterator<iterator>						reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>				const_reverse_iterator;	
	
		private:
			allocator_type 		_alloc;
			pointer 			_data;
			size_type			_capacity;
			size_type			_size;

		public:
        // Constructs an empty container, with no elements.
		explicit vector(const allocator_type& alloc = allocator_type()) : _alloc(alloc), _data(NULL), _capacity(0), _size(0) {}

		// Constructs a container with n elements. Each element is a copy of val.
		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _data(NULL), _capacity(n), _size(n) {
			_data = _alloc.allocate(n);
			for (size_type i = 0; i < n; i++)
			_alloc.construct(_data + i, val);
		}

		// Constructs a container with as many elements as the range [first,last), with each element constructed from its corresponding element in that range, in the same order.
		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) : _alloc(alloc), _size(0) {
			difference_type n = ft::distance(first, last);
			_data = _alloc.allocate(n);
			_capacity = n;
			for (; first != last; first++)
			push_back(*first);
		}

		// Copy constructor
		vector(const vector& x) : _alloc(allocator_type()), _data(NULL), _capacity(0), _size(0) {*this = x;}

		~vector() {
			clear();
			if (_capacity > 0)
				_alloc.deallocate(_data, _capacity);
		}

		// Assign content
		vector& operator=(const vector& x) {
			if (this != &x) {
				clear();
				assign(x.begin(), x.end());
			}
			return (*this);
		}

		// Iterators
		iterator 					begin() {return (iterator(_data));}
		const_iterator 				begin() const {return (const_iterator(_data));}
		iterator 					end() {return (iterator(_data + _size));}
		const_iterator 				end() const {return (const_iterator(_data + _size));}
		reverse_iterator 			rbegin() {return (reverse_iterator(end()));}
		const_reverse_iterator 		rbegin() const {return (const_reverse_iterator(end()));}
		reverse_iterator 			rend() {return (reverse_iterator(begin()));}
		const_reverse_iterator 		rend() const {return (const_reverse_iterator(begin()));}

		// Capacity
		size_type 					size() const {return (_size);}
		size_type 					max_size() const {return (_alloc.max_size());}
		size_type 					capacity() const {return (_capacity);}
		bool 						empty() const {return (size() == 0 ? true : false);}

		void 	resize(size_type n, value_type val = value_type()) {
			if (n > _capacity) reserve(n);
			if (n >= _size) {
				for (size_type i = _size; i < n; i++)
				_alloc.construct(_data + i, val);
			} else {
				for (size_type i = n; i < _size; i++)
				_alloc.destroy(_data + i);
				_capacity = n;
			}
			_size = n;
		}
		
		void 	reserve(size_type n) {
			if (n > max_size()) {
				throw (std::length_error("ft::vector::reserve"));
			} else if (n > _capacity) {
				pointer new_data = _alloc.allocate(n);
				for (size_type i = 0; i < _size; i++)
				_alloc.construct(new_data + i, *(_data + i));
				_alloc.deallocate(_data, _capacity);
				_data = new_data;
				_capacity = n;
			}
		}

		// Element access
		reference 			operator[](size_type n) {return (_data[n]);}
		const_reference 	operator[](size_type n) const {return (_data[n]);}
		reference 			front() {return (*begin());}
		const_reference 	front() const {return (*begin());}
		reference 			back() {return (*(end() - 1));}
		const_reference 	back() const {return (*(end() - 1));}
		reference 			at(size_type n) {
			if (n >= size())
				throw (std::out_of_range("ft::vector::at"));
			else
				return (_data[n]);
		}
		const_reference 	at(size_type n) const {
			if (n >= size())
				throw (std::out_of_range("ft::vector::at"));
			else
				return (_data[n]);
		}

		// Modifiers
		// Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
		template <class InputIterator>
		void	assign (InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value>::type* = 0) {
			this->clear();
			while (first != last) {
				push_back(*first);
				++first;
			}
		}
		
		void	assign(size_type n, const value_type& val) {
			this->clear();
			while (n) {
				push_back(val);
				--n;
			}
		}

		// Adds a new element at the end of the vector, after its current last element. The content of val is copied (or moved) to the new element.
		void push_back(const value_type& val) {
			if (_size == _capacity)
				empty() ? reserve(1) : reserve(_size * 2);
			_alloc.construct(_data + _size, val);
			_size++;
		}

		// Removes the last element in the vector, effectively reducing the container size by one.
		void pop_back() {
			if (_size > 0) {
				_alloc.destroy(_data + (_size - 1));
				_size--;
			}
		}

		// The vector is extended by inserting new elements before the element at the specified position, effectively increasing the container size by the number of elements inserted.
		iterator insert (iterator position, const value_type& val) {
			size_type n = ft::distance(begin(), position);
			insert(position, 1, val);
			return (iterator(&this->_data[n]));
		}
		void insert (iterator position, size_type n, const value_type& val) {
			vector tmp(position, end());
			this->_size -= ft::distance(position, end());
			while (n) {
				push_back(val);
				--n;
			}
			iterator it = tmp.begin();
			while (it != tmp.end()) {
				push_back(*it);
				++it;
			}
		}
		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0) {
			vector tmp(position, end());
			this->_size -= ft::distance(position, end());
			while (first != last) {
				push_back(*first);
				++first;
			}
			iterator it = tmp.begin();
			while (it != tmp.end()) {
				push_back(*it);
				++it;
			}
		}

		// Removes from the vector either a single element (position) or a range of elements ([first,last]).
		iterator erase(iterator position) {
			if (empty())
				return (end());
			iterator it = begin();
			while (it != position)
				it++;
			_alloc.destroy(&(*it));
			while (it + 1 != end()) {
				_alloc.construct(&(*it), *(it + 1));
				it++;
			}
			pop_back();
			return (position);
		}
		iterator erase(iterator first, iterator last) {
			if (empty())
				return (end());
			iterator it = begin();
			iterator rtn = first;
			difference_type dist = last - first;
			while (it != first)
				it++;
			for (; first != last; first++)
				_alloc.destroy(&(*first));
			while (it + dist != end()) {
				_alloc.construct(&(*it), *(it + dist));
				it++;
			}
			while (dist-- > 0)
				pop_back();
			return (rtn);
		}

		void swap(vector& x) {
			std::swap(_size, x._size);
			std::swap(_capacity, x._capacity);
			std::swap(_data, x._data);
		}

		void clear() {
			if (_size > 0) {
				for (iterator it = begin(); it != end(); it++)
				_alloc.destroy(&(*it));
				_size = 0;
			}
		}

		// Allocator
		allocator_type get_allocator() const {return (Alloc(_alloc));}
	};

	// Non-member function overloads
	template <class T, class Alloc>	bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));}
	template <class T, class Alloc>	bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {return (!(lhs == rhs));}
	template <class T, class Alloc> bool operator< (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));}
	template <class T, class Alloc>	bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {return (!(lhs > rhs));}
	template <class T, class Alloc>	bool operator> (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {return (rhs < lhs);}
	template <class T, class Alloc>	bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {return (!(lhs < rhs));}
	template <class T, class Alloc>	void swap(vector<T, Alloc>& x, vector<T, Alloc>& y) {x.swap(y);}
}

#endif