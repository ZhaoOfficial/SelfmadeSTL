#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "stl_deque.hpp"
#include "stl_function.hpp"
#include "stl_heap.hpp"
#include "stl_vector.hpp"

namespace selfmadeSTL {

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

    template <typename T, typename Sequence = vector<T>, typename Compare = less<typename Sequence::value_type>>
    class priority_queue {
    public:
        typedef typename Sequence::value_type value_type;
        typedef typename Sequence::size_type size_type;
        typedef typename Sequence::reference reference;
        typedef typename Sequence::const_reference const_reference;
        typedef          Sequence  container_type;

    protected:
        Sequence container;
        Compare comp;

    public:
        priority_queue() : container() {}
        explicit priority_queue(const Compare& c) : container(), comp(c) {}
        priority_queue(const Compare& c, const Sequence& s) : container(s), comp(c) {
            make_heap(container.begin(), container.end(), comp);
        }
        template <typename InputIterator>
        priority_queue(const InputIterator first, const InputIterator last) : container(first, last) {
            make_heap(container.begin(), container.end(), comp);
        }
        template <typename InputIterator>
        priority_queue(const InputIterator first, const InputIterator last, const Compare& c) : container(first, last), comp(c) {
            make_heap(container.begin(), container.end(), comp);
        }
        template <typename InputIterator>
        priority_queue(const InputIterator first, const InputIterator last, const Compare& c, const Sequence& s) : container(s), comp(c) {
            container.insert(container.end(), first, last);
            make_heap(container.begin(), container.end(), comp);
        }

        bool empty() const { return container.empty(); }
        size_type size() const { return container.size(); }
        const_reference top() const { return container.front(); }

        void push(const value_type& value) {
            try {
                container.push_back(value);
                push_heap(container.begin(), container.end(), comp);
            }
            catch (const std::exception&) {
                container.clear();
            }
        }
        void pop() {
            try {
                pop_heap(container.begin(), container.end(), comp);
                container.pop_back();
            }
            catch (const std::exception&) {
                container.clear();
            }
        }
    };
}

#endif //! _QUEUE_H_