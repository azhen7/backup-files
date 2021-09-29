#ifndef _STD_COPY_PAIR
#define _STD_COPY_PAIR

namespace std_copy {
    template <class T1, class T2>
    struct pair {
        T1  first;
        T2  second;

        pair(T1 f = T1(), T2 s = T2())
            : first(f), 
            second(s) 
        {
        }

        pair (const pair& p)
            : first(p.first),
            second(p.second)
        {
        }
        pair (pair&& p)
            : first(p.first),
            second(p.second)
        {
        }

        void swap(pair& p) {
            T1 temp = first;
            first = p.first;
            p.first = temp;

            T2 temp2 = second;
            second = p.second;
            p.second = temp2;
        }
        const pair& operator=(const pair& toAssign) {
            first = toAssign.first;
            second = toAssign.second;
            return *this;
        }
    };
    template <class T1, class T2>
    pair<T1, T2> make_pair(T1 f, T2 s) {
        pair<T1, T2> p(f, s);
        return p;
    }
    template <class T1, class T2>
    void swap(pair<T1, T2> lhs, pair<T1, T2> rhs) {
        T1 temp = lhs.first;
        lhs.first = rhs.first;
        rhs.first = temp;
    }

    /**
     * Check if two pair objects are equal.
    */
    template <class T1, class T2>
    bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
        return (lhs.first == rhs.first) && (lhs.second == rhs.second);
    }
    /**
     * Check if two pair objects are unequal.
    */
    template <class T1, class T2>
    bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
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
    bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
        return !(rhs < lhs);
    }
    /**
     * Check if one pair object is greater than the other pair object.
    */
    template <class T1, class T2>
    bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
        return rhs < lhs;
    }
    /**
     * Check if one pair object is greater than or equal to the other pair 
     * object.
    */
    template <class T1, class T2>
    bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
        return !(lhs < rhs);
    }
}

#endif /* _STD_COPY_PAIR */