#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "stl_deque.hpp"

namespace SelfMadeSTL {

    template <typename T, typename Sequence = deque<T>>
    class queue {
    public:
        typedef typename Sequence::value_type value_type;
        typedef typename Sequence::size_type size_type;
        typedef typename Sequence::reference reference;
        typedef typename Sequence::const_reference const_reference;
        typedef          Sequence  container_type;

    protected:
        Sequence container;

    public:
        queue() : container() {}
        explicit queue(const Sequence& other) : container(other) {}

        bool empty() const { return container.empty(); }
        size_type size() const { return container.size(); }
        reference front() { return container.front(); }
        const_reference front() const { return container.front(); }
        reference back() { return container.back(); }
        const_reference back() const { return container.back(); }

        bool operator==(const queue& other) const { return container == other.container; }
        bool operator!=(const queue& other) const { return container != other.container; }
        bool operator<(const queue& other) const { return container < other.container; }
        
        void push(const value_type& value) { container.push_back(value); }
        void pop() { container.pop_front(); }
    };


    class priority_queue;
}

#endif //! _QUEUE_H_