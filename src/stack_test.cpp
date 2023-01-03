/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_test.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chduong <chduong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:25:45 by chduong           #+#    #+#             */
/*   Updated: 2023/01/03 16:26:13 by chduong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stack>
#include <cassert>

int main() {
  std::stack<int> s;
  assert(s.empty()); // La pile est vide lorsqu'elle est créée
  s.push(1);
  assert(s.size() == 1); // La taille de la pile est de 1 après l'ajout d'un élément
  s.push(2);
  assert(s.top() == 2); // Le dernier élément ajouté est retourné par top
  s.pop();
  assert(s.top() == 1); // L'élément suivant est retourné par top après l'appel à pop
  s.pop();
  assert(s.empty()); // La pile est vide après avoir retiré tous les éléments
  return 0;
}
