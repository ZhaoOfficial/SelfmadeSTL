#ifndef _FUNCTION_H_
#define _FUNCTION_H_

namespace SelfMadeSTL{

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

    template <typename T>
    struct negate : public unary_function<T, T> {
        T operator()(const T& a) const {
            return -a;
        }
    };

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
}

#endif // !_FUNCTION_H_