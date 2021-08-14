#ifndef _FUNCTION_H_
#define _FUNCTION_H_

namespace selfmadeSTL{

    // base functor

	template <typename Arg, typename Return>
	struct unary_function {
		typedef Arg argument_type;
		typedef Return return_type;
	};

    template <typename Arg1, typename Arg2, typename Return>
    struct binary_function {
        typedef Arg1 first_argument_type;
        typedef Arg2 second_argument_type;
        typedef Return return_type;
    };

    // comparison functor

    template <typename T>
    struct equal_to : public binary_function<T, T, bool> {
        bool operator()(const T& a, const T& b) const {
            return a == b;
        }
    };

    template <typename T>
    struct not_equal_to : public binary_function<T, T, bool> {
        bool operator()(const T& a, const T& b) const {
            return a != b;
        }
    };

	template <typename T>
	struct less : public binary_function<T, T, bool> {
        bool operator()(const T& a, const T& b) const {
            return a < b;
        }
	};

    template <typename T>
    struct less_equal : public binary_function<T, T, bool> {
        bool operator()(const T& a, const T& b) const {
            return a <= b;
        }
    };
    
    template <typename T>
    struct greater : public binary_function<T, T, bool> {
        bool operator()(const T& a, const T& b) const {
            return a > b;
        }
    };

    template <typename T>
    struct greater_equal : public binary_function<T, T, bool> {
        bool operator()(const T& a, const T& b) const {
            return a >= b;
        }
    };

    // arithmetic functor

    template <typename T>
    struct negate : public unary_function<T, T> {
        T operator()(const T& a) const {
            return -a;
        }
    };

    template <typename T>
    struct plus : public binary_function<T, T, T> {
        T operator()(const T& a, const T& b) const {
            return a + b;
        }
    };

    template <typename T>
    struct minus : public binary_function<T, T, T> {
        T operator()(const T& a, const T& b) const {
            return a - b;
        }
    };

    template <typename T>
    struct multiply : public binary_function<T, T, T> {
        T operator()(const T& a, const T& b) const {
            return a * b;
        }
    };

    template <typename T>
    struct divide : public binary_function<T, T, T> {
        T operator()(const T& a, const T& b) const {
            return a / b;
        }
    };

    template <typename T>
    struct modulu : public binary_function<T, T, T> {
        T operator()(const T& a, const T& b) const {
            return a % b;
        }
    };

    // identity

    template <typename T>
    inline T identity_element(plus<T>) {
        return T(0);
    };

    template <typename T>
    inline T identity_element(multiply<T>) {
        return T(1);
    };

    // logical functor

    template <typename T>
    struct logical_and : public binary_function<T, T, bool> {
        bool operator()(const T& a, const T& b) const {
            return a && b;
        }
    };

    template <typename T>
    struct logical_or : public binary_function<T, T, bool> {
        bool operator()(const T& a, const T& b) const {
            return a || b;
        }
    };

    template <typename T>
    struct logical_not : public unary_function<T, bool> {
        bool operator()(const T& a) const {
            return !a;
        }
    };

    // not c++ standard, but usefull

    template <typename T>
    struct identity : public unary_function<T, T> {
        const T& operator()(const T& a) const {
            return a;
        }
    };

    // select first element in a pair
    template <typename Pair>
    struct select1st : public unary_function<Pair, typename Pair::first_type> {
        const typename Pair::first_type& operator()(const Pair& a) const {
            return a.first;
        }
    };

    // select second element in a pair
    template <typename Pair>
    struct select2rd : public unary_function<Pair, typename Pair::second_type> {
        const typename Pair::second_type& operator()(const Pair& a) const {
            return a.second;
        }
    };

    // return first element
    template <typename Arg1, typename Arg2>
    struct project1st : public binary_function<Arg1, Arg2, Arg1> {
        Arg1& operator()(Arg1& a, Arg2&) {
            return a;
        }
    };

    // return second element
    template <typename Arg1, typename Arg2>
    struct project2rd : public binary_function<Arg1, Arg2, Arg2> {
        Arg2& operator()(Arg1&, Arg2& b) {
            return b;
        }
    };


}

#endif // !_FUNCTION_H_