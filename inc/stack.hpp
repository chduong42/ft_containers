/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 22:09:12 by chduong           #+#    #+#             */
/*   Updated: 2023/01/03 19:42:11 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP
# include <vector>
# include <stack>

namespace ft 
{
	template <class T, class Container = std::vector<T> > class stack {
		private:
			// ====================== Member Variables ========================= //
			Container               _ctnr;
		
		public:
			// ====================== Member Types ========================= //
			typedef T				value_type;
			typedef Container		container_type;
			
			// ---------------------- Constructors / Destructor ----------------------- //
			explicit stack(const container_type& ctnr = container_type()) : _ctnr(ctnr) {} // empty container
			~stack() {}
			// ---------------------- Member Functions ----------------------------- //
			bool					empty() const { return _ctnr.empty(); }
			
			size_t					size() const { return _ctnr.size(); }
			
			value_type&             top() { return _ctnr.back(); }
			const value_type&       top() const { return _ctnr.back(); }
			
			void                    push(const value_type& val) { _ctnr.push_back(val); }
			void                    pop() { _ctnr.pop_back(); }
			
			// ---------------------- Non-member Functions ----------------------------- //
			friend bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs._ctnr == rhs._ctnr;}
			friend bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs._ctnr != rhs._ctnr;}
			friend bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs._ctnr < rhs._ctnr;}
			friend bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs._ctnr <= rhs._ctnr;}
			friend bool operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs._ctnr > rhs._ctnr;}
			friend bool operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {return lhs._ctnr >= rhs._ctnr;}
	};
}

#endif