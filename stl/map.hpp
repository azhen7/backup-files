#ifndef _STD_COPY_MAP
#define _STD_COPY_MAP

#include <stdexcept>
#include <functional>

#include "algorithm.hpp"
#include "iterator.hpp"
#include "pair.hpp"
#include "allocator.hpp"

namespace std_copy
{
    /**
     * My implementation of std::map, defined in the <map> header file. 
     * This implementation contains some new functions, aside from the 
     * ones in the original implementation.
    */
    template <class Key, class T, class Compare = std::less<Key>, class Alloc = std_copy::allocator<pair<Key, T>>>
    class map
    {
        private:
            typedef map<Key, T, Compare, Alloc>                 map_type;
            typedef iterator<map_type>                          iterator_type;
            
        public:
            typedef Key                                         key_type;
            typedef T                                           mapped_type;
            typedef pair<Key, T>                                value_type;
            typedef Compare                                     key_compare;
            typedef value_type*                                 pointer;
            typedef const value_type*                           const_pointer;
            typedef value_type&                                 reference;
            typedef const value_type&                           const_reference;
            typedef Alloc                                       allocator_type;
            typedef unsigned long long                          size_type;
            typedef long long                                   difference_type;
            typedef iterator_type                               iterator;
            typedef const iterator_type                         const_iterator;
        
        private:
            typedef pair<iterator, bool>                        iterator_and_bool;

            pointer internalBuffer_;
            size_type numberOfElements_;
            size_type capacity_;
            allocator_type allocator;
            key_compare compare_keys;

            class value_compare
                : std::binary_function<value_type, value_type, bool>
            {
                private:
                    key_compare comp;
                    value_compare(key_compare c) : comp(c) {}

                public:
                    bool operator()(const value_type& a, const value_type& b)
                    {
                        return comp(a.first, b.first);
                    }
            };

            void copyAndFindInsertPos(pointer copyFrom, const key_type& key, int& pos)
            {
                for (int i = 0; i < numberOfElements_; i++)
                {
                    if (!compare_keys(copyFrom[i].first, key))
                    {
                        for (int j = numberOfElements_ - 1; j >= i; j--)
                            internalBuffer_[j + 1] = std_copy::move(copyFrom[i]);

                        pos = i;
                        break;
                    }
                    internalBuffer_[i] = std_copy::move(copyFrom[i]);
                }
            }

            iterator_and_bool _emplace(const_reference elemToConstruct)
            {
                if (this->contains(elemToConstruct.first))
                    return iterator_and_bool(this->find(elemToConstruct.first), false);

                int whereToInsert = 0;
                if (numberOfElements_ + 1 > capacity_)
                {
                    capacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;

                    pointer temp = internalBuffer_;
                    internalBuffer_ = allocator.allocate(capacity_);
                    copyAndFindInsertPos(temp, elemToConstruct.first, whereToInsert);
                    allocator.deallocate(temp, (int) capacity_ / 2);
                }
                std_copy::allocator_traits<allocator_type>::construct(allocator, internalBuffer_ + numberOfElements_, std_copy::move(elemToConstruct));
                numberOfElements_++;
                return iterator_and_bool(iterator(internalBuffer_ + numberOfElements_), true);
            }

        public:
            /**
             * Default constructor
            */
            map() 
                : capacity_(0),
                numberOfElements_(0)
            {
            }
            /**
             * This function constructs a map from a given map object.
             * @param copy The map used to construct the current map object.
            */
            map(const map_type& copy)
                : capacity_(copy.capacity_),
                numberOfElements_(copy.numberOfElements_)
            {
                internalBuffer_ = allocator.allocate(capacity_);
                for (size_type i = 0; i < numberOfElements_; i++)
                    internalBuffer_[i] = copy.internalBuffer_[i];
            }
            map(const map_type& copy, const allocator_type& alloc)
                : capacity_(copy.capacity_),
                numberOfElements_(copy.numberOfElements_)
            {
                internalBuffer_ = alloc.allocate(capacity_);
                for (size_type i = 0; i < numberOfElements_; i++)
                    internalBuffer_[i] = copy.internalBuffer_[i];
            }
            /**
             * This function constructs a map from a given rvalue reference 
             * map object.
             * @param copy The map used to construct the current map object.
            */
            map(map_type&& copy)
                : capacity_(copy.capacity_),
                internalBuffer_(copy.internalBuffer_),
                numberOfElements_(copy.numberOfElements_)
            {
            }

            virtual ~map()
            {
                for (int i = 0; i < numberOfElements_; i++)
                    internalBuffer_[i].~value_type();
            }

            /**
             * This function returns the number of elements 
             * in the map.
            */
            size_type size() const noexcept
            {
                return numberOfElements_;
            }
            /**
             * This function checks whether the map is empty (i.e. has no elements).
            */
            bool empty() const noexcept
            {
                return numberOfElements_ == 0;
            }
            /**
             * This function clears the map.
            */
            void clear()
            {
                allocator.deallocate(internalBuffer_, capacity_);
                numberOfElements_ = 0;
                capacity_ = 0;
            }
            /**
             * This function returns an iterator to the first element in the container
            */
            iterator begin()
            {
                return iterator(internalBuffer_);
            }
            /**
             * This function returns an iterator to the theoretical element after the last 
             * element in the container;
            */
            iterator end()
            {
                return iterator(internalBuffer_ + numberOfElements_);
            }
            /**
             * This function returns a const iterator to the first element in the container
            */
            const_iterator cbegin()
            {
                return (const_iterator) iterator(internalBuffer_);
            }
            /**
             * This function returns a const iterator to the theoretical element after the last 
             * element in the container;
            */
            const_iterator cend()
            {
                return (const_iterator) iterator(internalBuffer_ + numberOfElements_);
            }
            /**
             * This function erases the element pointed to by the provided iterator.
             * @param pos The iterator which points to the element to erase.
            */
            iterator erase(iterator pos)
            {
                if (numberOfElements_ == 0)
                    throw std::length_error("No elements to erase");
                
                size_type index = 0;
                for (iterator it = this->begin(); it != this->end(); it++)
                {
                    if (it != pos)
                        internalBuffer_[index++] = *it;
                }
                numberOfElements_--;
                (internalBuffer_ + numberOfElements_)->~value_type();
                return pos;
            }
            /**
             * This function erases the range [first, last).
             * @param first The start of the sequence to erase.
             * @param last The end of the sequence to erase.
            */
            iterator erase(const_iterator first, const_iterator last)
            {
                if (numberOfElements_ == 0)
                    throw std::length_error("No elements to erase");

                size_type index = 0;
                for (iterator it = this->begin(); it != this->end(); it++)
                {
                    if (it < first || it >= last)
                        internalBuffer_[index++] = *it;
                }
                for (int i = 0; i < last - first; i++)
                    (internalBuffer_ + numberOfElements_ - 1 - i)->~value_type();

                numberOfElements_ = index;
                return last;
            }
            /**
             * Operator overload of operator[]. If the provided argument exists in the 
             * map, a reference to its mapped value is returned. Otherwise, the function
             * adds an element to the map with the key having the value of the argument.
             * @param key The key of the element to get, or in case an element with the same key 
             * doesn't exist, creates it.
            */
            mapped_type& operator[](const key_type& key)
            {
                if (this->contains(key))
                    return find(key)->second;
                    
                int whereToInsert = numberOfElements_;
                if (numberOfElements_ + 1 > capacity_)
                {
                    capacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;

                    pointer temp = internalBuffer_;
                    internalBuffer_ = allocator.allocate(capacity_);
                    copyAndFindInsertPos(temp, key, whereToInsert);
                    allocator.deallocate(temp, capacity_ / 2);
                }
                numberOfElements_++;
                internalBuffer_[whereToInsert] = pair<key_type, mapped_type>(key, mapped_type());
                return internalBuffer_[whereToInsert].second;
            }
            /**
             * This function has the same functionality as operator[], except 
             * instead of creating a new element if the provided key doesn't 
             * exist, an out_of_range exception is thrown.
             * @param key The key of the element to return.
            */
            mapped_type& at(const key_type& key)
            {
                if (this->contains(key))
                    return find(key)->second;

                throw std::out_of_range("map::at");
            }
            /**
             * This function inserts an element into the container. It does not 
             * insert an element when an element with the specified key already exists.
             * @param pairToInsert The element to insert into the map.
            */
            iterator_and_bool insert(const_reference pairToInsert)
            {
                if (this->contains(pairToInsert.first))
                    return iterator_and_bool(this->find(pairToInsert.first), false);
                
                int whereToInsert = numberOfElements_;
                if (numberOfElements_ + 1 > capacity_)
                {
                    capacity_ = (capacity_ == 0) ? 1 : capacity_ * 2;

                    pointer temp = internalBuffer_;
                    internalBuffer_ = allocator.allocate(capacity_);
                    copyAndFindInsertPos(temp, pairToInsert.first, whereToInsert);
                    allocator.deallocate(temp, (int) capacity_ / 2);
                }
                numberOfElements_++;
                internalBuffer_[whereToInsert] = pairToInsert;
                return iterator_and_bool(iterator(internalBuffer_ + whereToInsert), true);
            }
            /**
             * This function does the same thing as insert(), except if the element with the specified 
             * key already exists, that element gets assigned to the new mapped value instead.
             * @param pairToInsert The element to insert into the map.
            */
            iterator_and_bool insert_or_assign(const_reference pairToInsert)
            {
                iterator_and_bool p = this->insert(pairToInsert);
                if (!p.second)
                    (*this)[p.first->first] = pairToInsert.second;
                return p;
            }
            /**
             * This function constructs an element in place if an element with the key does not exist in 
             * the container.
             * @param elemToConstruct The element to construct in place.
            */
            iterator_and_bool emplace(const_reference elemToConstruct)
            {
                return _emplace(elemToConstruct);
            }
            /**
             * Constructs an element in place if an element with the specified key does not exist in the 
             * container.
             * @param args The arguments forwarded to the constructor.
            */
            template <class ...Args>
            iterator_and_bool emplace(Args&&... args)
            {
                return _emplace(value_type(std_copy::forward<Args>(args)...));
            }
            /**
             * Behaves like emplace() except args is forwarded to the constructed element's second parameter.
             * @param key The key of the object that will get inserted.
             * @param args The arguments forwarded to the constructed element's second parameter.
            */
            template <class ...Args>
            iterator_and_bool try_emplace(const key_type& key, Args&&... args)
            {
                return _emplace(value_type(std_copy::move(key), mapped_type(std_copy::forward<Args>(args)...)));
            }
            /**
             * This function copies one map to another.
             * @param s The map to copy to this.
            */
            void operator=(const map_type& s)
            {
                allocator.deallocate(internalBuffer_, capacity_);
                numberOfElements_ = s.numberOfElements_;
                capacity_ = s.capacity_;
                std_copy::copy(s.internalBuffer_, s.internalBuffer_ + numberOfElements_, internalBuffer_);
            }
            /**
             * This function returns an object of the provided allocator type.
            */
            allocator_type get_allocator() const noexcept
            {
                return allocator;
            }
            /**
             * This function returns an iterator to the element with the 
             * same key as key.
             * @param key The key of the element to search for.
            */
            iterator find(const key_type& key)
            {
                if (!numberOfElements_)
                    return this->end();

                pointer start = internalBuffer_;
                pointer finish = internalBuffer_ + numberOfElements_;
                size_type tempNumberOfElements = numberOfElements_;
                while (finish >= start)
                {
                    size_type addToGetMiddle = (tempNumberOfElements % 2 != 0) ? (tempNumberOfElements / 2) : (tempNumberOfElements / 2 - 1);
                    pointer middle = start + addToGetMiddle;
                    if (middle->first == key)
                        return iterator(middle);
                    else if (middle->first > key)
                    {
                        finish = middle - 1;
                        tempNumberOfElements = addToGetMiddle + 1;
                    }
                    else
                    {
                        start = middle + 1;
                        tempNumberOfElements = addToGetMiddle + 1;
                    }
                }
                return this->end();
            }
            /**
             * This function checks whether the container contains an 
             * element with a specified key.
             * The equality operator has to be provided by the user.
             * @param key The key to find.
            */
            bool contains(const key_type& key)
            {
                return this->find(key) != this->end();
            }
            /**
             * This function swaps the contents of *this with s.
             * @param s The map to swap with.
            */
            void swap(const map_type& s)
            {
                pointer temp = s.internalBuffer_;
                s.internalBuffer_ = internalBuffer_;
                internalBuffer_ = temp;

                size_type tempCapacity = s.capacity_;
                s.capacity_ = capacity_;
                capacity_ = tempCapacity;

                size_type tempNumberOfElems = s.numberOfElements_;
                s.numberOfElements_ = numberOfElements_;
                numberOfElements_ = tempNumberOfElems;
            }
            /**
             * This function returns an iterator to the first element with 
             * a key that does not compare less than key.
             * @param key The key used to compare against the keys of the 
             * other elements.
            */
            iterator lower_bound(const key_type& key)
            {
                if (!numberOfElements_)
                    return this->end();

                pointer start = internalBuffer_;
                pointer finish = internalBuffer_ + numberOfElements_;
                size_type tempNumberOfElements = numberOfElements_;
                while (finish >= start)
                {
                    size_type addToGetMiddle = (tempNumberOfElements % 2 != 0) ? (tempNumberOfElements / 2) : (tempNumberOfElements / 2 - 1);
                    pointer middle = start + addToGetMiddle;
                    if (middle->first >= key)
                        return iterator(middle);
                    else
                    {
                        start = middle + 1;
                        tempNumberOfElements = addToGetMiddle + 1;
                    }
                }
                return this->end();
            }
            /**
             * This function returns an iterator to the first element with 
             * a key that is greater than key.
             * @param key The key used to compare against the keys of the 
             * other elements.
            */
            iterator upper_bound(const key_type& key)
            {
                if (!numberOfElements_)
                    return this->end();

                pointer start = internalBuffer_;
                pointer finish = internalBuffer_ + numberOfElements_;
                size_type tempNumberOfElements = numberOfElements_;
                while (finish >= start)
                {
                    size_type addToGetMiddle = (tempNumberOfElements % 2 != 0) ? (tempNumberOfElements / 2) : (tempNumberOfElements / 2 - 1);
                    pointer middle = start + addToGetMiddle;
                    if (middle->first > key)
                        return iterator(middle);
                    else
                    {
                        start = middle + 1;
                        tempNumberOfElements = addToGetMiddle + 1;
                    }
                }
                return this->end();
            }
            /**
             * Returns the object used to compare the keys.
            */
            key_compare key_comp() const noexcept
            {
                return compare_keys;
            }
            /**
             * Returns the object used to compare the mapped values.
            */
            value_compare value_comp() const noexcept
            {
                return value_compare(compare_keys);
            }
    };
    /**
     * This function swaps the contents of two maps.
     * @param lhs The first map.
     * @param rhs The second map.
    */
    template <class T1, class T2, class Alloc>
    void swap(const map<T1, T2, Alloc>& lhs, const map<T1, T2, Alloc>& rhs)
    {
        lhs.swap(rhs);
    }
    /**
     * This function erases all elements from a map that meet a certain criteria.
     * @param c The map to erase elements from.
     * @param pred The function used to erase elements.
    */
    template <class T1, class T2, class Compare, class Alloc, class Function>
    typename std_copy::map<T1, T2, Compare, Alloc>::size_type 
        erase_if(std_copy::map<T1, T2, Compare, Alloc>& c, Function func)
    {
        unsigned long long oldSize = c.size();
        for (typename std_copy::map<T1, T2, Compare, Alloc>::iterator it = c.begin(); it != c.end(); )
        {
            if (func(*it))
                c.erase(it);
            else
                it++;
        }
        return oldSize - c.size();
    }
}

#endif /* _STD_COPY_MAP */
