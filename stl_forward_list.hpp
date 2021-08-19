#ifndef _FORWARD_LIST_H_
#define _FORWARD_LIST_H_

#include "stl_iterator.hpp"

namespace selfmadeSTL {

	struct forward_list_node_base {
		forward_list_node_base* next;
	};

	template <typename T>
	struct forward_list_node : public forward_list_node_base {
		T data;
	};

	inline forward_list_node_base* make_link(forward_list_node_base* prev, forward_list_node_base* curr) {
		curr->next = prev->next;
		prev->next = curr;
		return curr;
	}

	inline forward_list_node_base* previous(const forward_list_node_base* head, const forward_list_node_base* curr) {
		while (head && head->next != curr) {
			head = head->next;
		}
		return head;
	}

	inline size_t forward_list_size(const forward_list_node_base* head) {
		size_t result = 0;
		while (head != nullptr) {
			result++;
			head = head->next;
		}
		return result;
	}

	struct forward_list_iterator_base {
		typedef size_t               size_type;
		typedef ptrdiff_t            difference_type;
		typedef forward_iterator_tag iterator_category;

		forward_list_node_base* inner;

		forward_list_iterator_base(forward_list_node_base* inner) : inner(inner) {}
		
		void increment() { inner = inner->next; }
		bool operator==(const forward_list_iterator_base& other) const {
			return inner == other.inner;
		}
		bool operator!=(const forward_list_iterator_base& other) const {
			return inner != other.inner;
		}
	};

	template<typename T, typename Ref, typename Ptr>
	struct forward_list_iterator : public forward_list_iterator_base {
		typedef forward_list_iterator<T, T&, T*>             iterator;
		typedef forward_list_iterator<T, const T&, const T*> const_iterator;
		typedef forward_list_iterator<T, Ref, Ptr>           self;

		typedef T                    value_type;
		typedef Ptr                  pointer;
		typedef Ref                  reference;
		typedef forward_list_node<T> node;

		forward_list_iterator(node* inner) : forward_list_iterator_base(inner) {}
		forward_list_iterator() : forward_list_iterator_base(nullptr) {}
		forward_list_iterator(const iterator& other) : forward_list_iterator_base(other.inner) {}

		reference operator*() const { return ((node*)inner)->data; }
		pointer operator->() const { return &(operator*()); }

		self& operator++() {
			increment();
			return *this;
		}
		self operator++(int) {
			self temp = *this;
			increment();
			return temp;
		}
	};

	class forward_list {

	};

}

#endif // !_FORWARD_LIST_H_