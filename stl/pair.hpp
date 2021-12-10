#ifndef _STD_COPY_PAIR
#define _STD_COPY_PAIR

namespace std_copy
{
    /**
     * An implementation of std::pair.
     * @param T1 The type of the first member.
     * @param T2 The type of the second member.
    */
    template <class T1, class T2>
    class pair
    {
        private:
            typedef pair<T1, T2>    pair_type;

        public:
            typedef T1  first_type;
            typedef T2  second_type;

            first_type  first;
            second_type  second;

            pair() {}
            /**
             * This function constructs a pair from two arguments.
             * @param f The argument that first gets set to.
             * @param s The argument that second gets set to.
            */
            pair(const first_type& f, const second_type& s)
                : first(std_copy::move(f)),
                second(std_copy::move(s))
            {
            }
            /**
             * This function constructs a pair from the given pair.
             * @param p The pair used to construct the current pair object.
            */
            pair(const pair_type& p)
                : first(p.first),
                second(p.second)
            {
            }
            /**
             * This function constructs a pair from the given rvalue 
             * reference pair.
             * @param p The pair used to construct the current pair object.
            */
            pair(pair_type&& p)
                : first(p.first),
                second(p.second)
            {
            }

            void swap(const pair_type& p)
            {
                first_type temp = first;
                first = p.first;
                p.first = temp;

                second_type temp2 = second;
                second = p.second;
                p.second = temp2;
            }
            const pair_type& operator=(const pair_type& toAssign)
            {
                first = std_copy::move(toAssign.first);
                second = std_copy::move(toAssign.second);
                return *this;
            }
    };
    /**
     * Returns a pair object constructed from f and s.
     * @param f The argument that gets assigned to first.
     * @param s The argument that gets assigned to second,
    */
    template <class T1, class T2>
    pair<T1, T2> make_pair(T1 f, T2 s)
    {
        return pair<T1, T2>(f, s);
    }
    /**
     * @brief Swaps the member variables of two pair objects.
    */
    template <class T1, class T2>
    void swap(pair<T1, T2> lhs, pair<T1, T2> rhs)
    {
        T1 tempFirst = lhs.first;
        lhs.first = rhs.first;
        rhs.first = tempFirst;

        T2 tempSecond = lhs.second;
        lhs.second = rhs.second;
        rhs.second = tempSecond;
    }

    /**
     * Check if two pair objects are equal.
    */
    template <class T1, class T2>
    bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return (lhs.first == rhs.first) && (lhs.second == rhs.second);
    }
    /**
     * Check if two pair objects are unequal.
    */
    template <class T1, class T2>
    bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return !(lhs == rhs);
    }
    /**
     * Check if one pair object is less than the other one.
    */
    template <class T1, class T2>
    bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) 
    {
        if (lhs.first != rhs.first)
            return (lhs.first < rhs.first);
        else
            return (lhs.second < rhs.second);
    }
    /**
     * Check if one pair object is less than or equal to the other pair 
     * object.
    */
    template <class T1, class T2>
    bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return !(rhs < lhs);
    }
    /**
     * Check if one pair object is greater than the other pair object.
    */
    template <class T1, class T2>
    bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return rhs < lhs;
    }
    /**
     * Check if one pair object is greater than or equal to the other pair 
     * object.
    */
    template <class T1, class T2>
    bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
    {
        return !(lhs < rhs);
    }
}

#endif /* _STD_COPY_PAIR */