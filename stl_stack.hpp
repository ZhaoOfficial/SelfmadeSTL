#ifndef _STACK_H_
#define _STACK_H_

#include "stl_deque.hpp"

namespace selfmadeSTL {

    template <typename T, typename Sequence = deque<T>>
    class stack {
    public:
        typedef typename Sequence::value_type value_type;
        typedef typename Sequence::size_type size_type;
        typedef typename Sequence::reference reference;
        typedef typename Sequence::const_reference const_reference;
        typedef          Sequence  container_type;

    protected:
        Sequence container;

    public:
        stack() : container() {}
        explicit stack(const Sequence& other) : container(other) {}

        bool empty() const { return container.empty(); }
        size_type size() const { return container.size(); }
        reference top() { return container.back(); }
        const_reference top() const { return container.back(); }

        bool operator==(const stack& other) const { return container == other.container; }
        bool operator!=(const stack& other) const { return container != other.container; }
        bool operator<(const stack& other) const { return container < other.container; }
        
        void push(const value_type& value) { container.push_back(value); }
        void pop() { container.pop_back(); }
    };

}

#endif //! _STACK_H_