/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 18:56:26 by kennyduong        #+#    #+#             */
/*   Updated: 2023/01/04 17:32:39 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <memory>
# include "iterator.hpp"

namespace ft {
	template<class T, class Allocator = std::allocator<T> > class vector {
		private:
			T*												_data;
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
			explicit vector(const allocator_type& alloc = allocator_type()) : _size(0), _alloc(alloc) {} // empty container

			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) :
			_size(n), _alloc(alloc) {
				_data = _alloc.allocate(n);
				for (size_t i = 0; i < n; i++)
					_alloc.construct(&_data[i], val);
			} // n elements which are copy of val
			
			template<class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) : _size(0), _alloc(alloc) {
				difference_type n = last - first;
				_data = _alloc.allocate(n);
				for (; first != last; first++) {
					_alloc.construct(&_data[_size++], first);
				}	
			}

			vector(const vector& x) {*this = x;} // copy constrcutor
			
			//---------------------- Destructor -------------------------------
			~vector() {}

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

			// //---------------------- Element access -------------------------------
			vector						&operator[](size_type n){return _data[n];}
			vector const				&operator[](size_type n) const {return _data[n];}
			reference 					at(size_type n) {return _data[n];}
			const_reference				at(size_type n) const {return _data[n];}
			reference 					front() {return _data[0];}
			const_reference				front() const {return _data[0];}
			reference					back() {return _data[_size - 1];}
			const_reference				back() const {return _data[_size - 1];}
			value_type*					data() noexcept {return _data;}
			const value_type*			data() const noexcept {return _data;}

			// //---------------------- Iterators ----------------------//
			// iterator					begin();
			// const_iterator				begin() const;
			// iterator					end();
			// const_iterator 				end() const;
			// reverse_iterator			rbegin();
			// const_reverse_iterator		rbegin() const;
			// reverse_iterator			rend();
			// const_reverse_iterator		rend() const;
			// const_iterator				cbegin() const noexcept;
			// const_iterator 				cend() const noexcept;
			// const_reverse_iterator		crbegin() const noexcept;
			// const_reverse_iterator		crend() const noexcept;
			
			// //---------------------- Modifiers ----------------------//
			// template <class InputIterator>
			// void 					assign(InputIterator first, InputIterator last); // Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
			// void						assign(size_type n, const value_type& val);
			// void						push_back(const value_type& val);
			
			// template<class... Args>
			// void 					emplace_back(Args&&... args); // insert a new element at the end of the vector, right after its current last element
			// void						pop_back();
			
			// void						clear(); // remove all element from the vector
			// void						insert(itrator position, InputIterator first, InputIterator last); // the vector is extended by inserting new elements before the element at the specified position
			// iterator					insert(iterator position, const value_type& val);
			// void						insert(iterator position, size_type n, const value_type& val);
			// template<class... Args>
			// iterator					emplace(const_iterator position, Args&&... args); // The container is extended by inserting a new element at position
			// iterator					erase(iterator position);
			// iterator					erase(iterator first, iterator last); // Removes from the vector either a single element (pos) or a range of elements ([first, last])
			// template <class InputIterator>
			// void						swap(vector& x); // exchanges the content of the container by the content of x which is another vector object of the same type
			
			// //---------------------- Capacity ----------------------//
			// size_type					size() const; // return the number of element in vector
			// size_type					max_size() const; // return the maximum number of element that the vector can hold
			// void						resize (size_type n, value_type val = value_type()); // resizes the container so that it contains n elements
			// size_type					capacity() const; // return the size of the storage space currently allocated for the vector (expr in element)
			// bool 						empty() const; // returns whether the vector is empty
			// void 						reserve (size_type n); // request that the vector capacity be at least enough coutain n elements
			// void 						shrink_to_fit() const; // request the container to reduce its capacity to fit its size
			
			// //---------------------- Allocator ----------------------//
			// allocator_type				get_allocator() const; // returns a cp[y of the allocator object associated with the vector
	};
}

#endif