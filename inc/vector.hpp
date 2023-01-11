/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kennyduong <kennyduong@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:56:26 by kennyduong        #+#    #+#             */
/*   Updated: 2023/01/11 02:12:16 by kennyduong       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <memory>
# include "iterator.hpp"
# include <iterator>

namespace ft {
	template<class T, class Allocator = std::allocator<T> > class vector {
		private:
			T*												_data;
			size_t											_capacity;
			size_t											_size;
			Allocator										_alloc;
		
		public:
			// ====================== Member Types ========================= //
			typedef T													value_type;
			typedef Allocator											allocator_type;
			typedef ptrdiff_t											difference_type;	
			typedef size_t												size_type;
			typedef T&													reference;
			typedef const T&											const_reference;
				
			typedef typename Allocator::pointer							pointer;
			typedef typename Allocator::const_pointer					const_pointer;
			typedef typename ft::random_access_iterator<T>				iterator;
			typedef typename ft::random_access_iterator<const T>		const_iterator;
			typedef typename ft::reverse_iterator<iterator>				reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>		const_reverse_iterator;	
			
			// ====================== Member Functions ========================= //
			// ---------------------- Constructors ----------------------------- //
			explicit vector(const allocator_type& alloc = allocator_type()) : _capacity(0), _size(0), _alloc(alloc) {} // empty container

			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _capacity(n), _size(n), _alloc(alloc) {
				_data = _alloc.allocate(n);
				for (size_t i = 0; i < n; i++)
					_alloc.construct(&_data[i], val);
			} // n elements which are copy of val
			
			template<class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) : _capacity(0), _size(0), _alloc(alloc) {
				assign(first, last);
			} // range of elements

			vector(const vector& x) {*this = x;} // copy constrcutor
			
			//---------------------- Destructor -------------------------------
			~vector() {
				for (size_t i = 0; i < _size; i++)
					_alloc.destroy(&_data[i]);
				_alloc.deallocate(_data, _size);
			}

			//---------------------- Overload Operator -------------------------------
			vector		&operator=(const vector &src) {
				if (this != &src) {
					_alloc.deallocate(_data, _size);
					_size = src._size;
					_data = _alloc.allocate(_size);
					for (size_t i = 0; i < _size; i++)
						_alloc.construct(&_data[i], src._data[i]);
				}
				return *this;
			}

			//---------------------- Element access -------------------------------
			vector						&operator[](size_type n){return _data[n];}
			vector const				&operator[](size_type n) const {return _data[n];}
			reference 					at(size_type n) {return _data[n];}
			const_reference				at(size_type n) const {return _data[n];}
			reference 					front() {return _data[0];}
			const_reference				front() const {return _data[0];}
			reference					back() {return _data[_size - 1];}
			const_reference				back() const {return _data[_size - 1];}
			value_type*					data() {return _data;}

			//---------------------- Iterators ----------------------//
			iterator					begin() {return iterator(_data);}
			const_iterator				begin() const {return const_iterator(_data);}
			iterator					end() {return iterator(_data + _size);}
			const_iterator 				end() const {return const_iterator(_data + _size);}
			reverse_iterator			rbegin() {return reverse_iterator(end());}
			const_reverse_iterator		rbegin() const {return const_reverse_iterator(end());}
			reverse_iterator			rend() {return reverse_iterator(begin());}
			const_reverse_iterator		rend() const {return const_reverse_iterator(begin());}
			
			//---------------------- Modifiers ----------------------//
			template <class InputIterator>
			void assign(InputIterator first, InputIterator last) {
				_alloc.deallocate(_data, _size);
				_size = last - first;
				_data = _alloc.allocate(_size);
				for (size_t i = 0; first != last; first++) {
					_alloc.construct(&_data[i++], first);
				}
			}
			
			void assign(size_type n, const value_type& val) {
				_alloc.deallocate(_data, _size);
				_size = n;
				_data = _alloc.allocate(_size);
				for (size_t i = 0; i < n; i++)
					_alloc.construct(&_data[i], val);
			}
			
			void						pop_back() {_alloc.destroy(&_data[--_size]);}
			void 						push_back(const value_type& val) {_alloc.construct(&_data[_size++], val);}
			void						clear() {_alloc.deallocate(_data, _size); _size = 0;}
			
			iterator insert( const_iterator pos, const T& value ) {
				iterator it = begin();
				for (; it != pos; it++);
				insert(it, value);
				return it;
			}
			
			template<class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last) {
				size_t n = last - first;
				pointer tmp = _alloc.allocate(_size + n);
				for (size_t i = 0; i < position; i++)
					_alloc.construct(&tmp[i], _data[i]);
				for (size_t i = 0; first != last; first++)
					_alloc.construct(&tmp[i++], first);
				for (size_t i = position; i < _size; i++)
					_alloc.construct(&tmp[i + n], _data[i]);
				_alloc.deallocate(_data, _size);
				_data = tmp;
				_size += n;
			}
			
			iterator insert( const_iterator pos, size_type count, const T& value ) {
				iterator it = begin();
				for (; it != pos; it++);
				insert(it, count, value);
				return it;
			}
			
			iterator erase(iterator position) {
				_alloc.destroy(&_data[position]);
				return position;
			}

			iterator erase(iterator first, iterator last) {
				for (; first != last; first++)
					_alloc.destroy(&_data[first]);
				return first;
			}
			
			void swap( vector& other ) {
				pointer tmp = _data;
				_data = other._data;
				other._data = tmp;
			}
			
			//---------------------- Capacity ----------------------//
			size_type					size() const {return _size;}
			size_type					max_size() const {return _alloc.max_size();}
			size_type					capacity() const {return _size;}
			bool 						empty() const {return _size == 0;}
			
			void resize (size_type n, value_type val = value_type()) {
				if (n > _size) {
					_data = _alloc.allocate(n);
					for (size_t i = _size; i < n; i++)
						_alloc.construct(&_data[i], val);
				}
				else if (n < _size) {
					for (size_t i = n; i < _size; i++)
						_alloc.destroy(&_data[i]);
				}
				_size = n;
			}
			
			void reserve (size_type n) {
				if (n > _size) {
					_data = _alloc.allocate(n);
					for (size_t i = _size; i < n; i++)
						_alloc.construct(&_data[i], value_type());
				}
				_size = n;
			}
			
			//---------------------- Allocator ----------------------//
			allocator_type				get_allocator() const {return _alloc;}
	};
}

#endif