#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stdexcept>

template <typename T>
class ArrayList {

public:
    ArrayList() {
        _size = 0;
        _reserved = 0;
        _elems = nullptr;
    }

    // Copy constructor
    ArrayList(const ArrayList<T>& c){
        _size = c._size;
        _reserved = c._reserved;

        if (_size > 0) {
            _elems = new T[_reserved];
        }

        for (int i = 0; i < _size; ++i)
        {
            _elems[i] = c._elems[i];
        }
    }

    // Move constructor
    ArrayList(ArrayList<T>&& c) {
        _elems = c._elems;
        _size = c._size;
        _reserved = c._reserved;

        c._elems = nullptr;
        c._size = 0;
        c._reserved = 0;

    }

    // Constructor with initialization of "initialized" elements
    ArrayList(int initialized) {
        _size = 0;
        _reserved = initialized;
        _elems = new T[_reserved];
    }

    virtual ~ArrayList() {
        if (_reserved > 0) {
            delete[] _elems;
        }
    }

    // Copy assignment operator
    ArrayList<T >& operator=(const ArrayList<T>& a) {
        if (_reserved > 0) {
            delete[] _elems;
        }
        _size = a._size;
        _reserved = a._reserved;

        if (_size > 0) {
            _elems = new T[_reserved];
        }

        for (int i = 0; i < _size; ++i)
        {
            _elems[i] = a._elems[i];
        }

        return *this;
    }

    // Move assignment operator
    ArrayList <T>& operator=(ArrayList <T>&& a) {
        if (_reserved > 0) {
            delete[] _elems;
        }

        _elems = a._elems;
        _size = a._size;
        _reserved = a._reserved;

        a._elems = nullptr;
        a._size = 0;
        a._reserved = 0;

        return *this;
    }

    // Add element to dynamic array
    void add(const T& element) {
        if (_size == _reserved)
            extendStorage();

        _elems[_size] = element;
        ++_size;
    }

    /*
     * Inserts the element at placement "idx " in array and moves the remaining
     * items by one place , restoring the old element at "idx ".
     * check whether it is needed to extend the storage .
     * move all elements from _size to idx (reverse) one element to the right in the array
     * set _elems [idx] equal to the element to be inserted
     */
    void add(int idx, const T& element) {
        if (_size == _reserved)
            extendStorage();

        for (int i = _size + 1; i > idx; --i)
        {
            _elems[i] = _elems[i - 1];
        }

        _elems[idx] = element;

        _size += 1;
    }

    // Get a const reference to the element at idx
    const T& operator[](int idx) const { return _elems[idx]; }

    // Get a reference to the element at idx
    T& operator[](int idx) { return _elems[idx]; }

    /*
     * Removes the element at placement "idx " by moving all the remaining elements
     * by one place to the left in the array
     */
    void remove(int idx) {
        for (int i = idx; i < _size; i++)
        {
            _elems[i] = _elems[i + 1];
        }

        _size -= 1;
    }

    // Returns the number of elements stored
    int size() const { return _size; }

    // Returns the number of items currently reserved inmemory
    int reserved() const { return _reserved; }

    // Returns true if number of elements in array is zero
    bool isEmpty() const { return (_size == 0) ? true : false; }

    // Trims the storage array to the exact number of elements stored.
    void trimToSize() {
        _reserved = _size;
        T* temp = new T[_reserved];

        for (int i = 0; i < _size; i++)
        {
            temp[i] = _elems[i];
        }

        delete[] _elems;
        _elems = new T[_reserved];

        for (int i = 0; i < _size; i++)
        {
            _elems[i] = temp[i];
        }

        delete[] temp;
    }

    /*
     * Sorts the array using insertion sort (or another algorithm)
     * You are not allowed to use standard algorithms from algorithm header.
     */
    void sort() {
        T relative;
        int i, j;
            for (i = 1; i < _size; i++)
            {
                relative = _elems[i];
                j = i - 1;

                // Move the elements of pos [0 to i-1],
                // that are greater than the "relative" one position
                // ahead of their current pos
                while (j >= 0 && _elems[j] > relative)
                {
                    _elems[j + 1] = _elems[j];
                    j = j - 1;
                }
                _elems[j + 1] = relative;
            }
    }

    // Returns a new ArrayList with elements from "fromIdx" index to "toIdx"
    ArrayList<T> subArrayList(int fromIdx, int toIdx) const {
        if (fromIdx > toIdx) {
            throw std::runtime_error("fromIdx is larger than toIdx");
        } else if (fromIdx == toIdx) {
            throw std::runtime_error("The two indexes are the same");
        } else if (fromIdx < 0 || toIdx < 0) {
            throw std::runtime_error("An index is less than 0");
        } else if (fromIdx > _size || toIdx > _size) {
            throw std::runtime_error("An index is greater than the size of the ArrayList");
        }

        ArrayList<T> array((toIdx - fromIdx) + 1);

        for (int i = fromIdx, j = 0; i <= toIdx; ++i, ++j)
        {
            array._elems[j] = _elems[i];
        }

        array._size = array._reserved;
        
        return array;
    }

    // Returns a new C style array (copy created with new) with all elements
    T* toArray() {

        T* cArray = new T[_size];

        for (int i = 0; i < _size; i++)
        {
            cArray[i] = _elems[i];
        }

        return cArray;
    }


private:
    /*
     * extendStorage():
     * create new array with size 2* _reserved
     * copy old data to the new array
     * delete old array
     * update pointer _elems to point to the new array
     * (Since this method is private, the method will only be used internally,
     * but the functionality is needed).
     */
    void extendStorage() {
        _reserved = (_reserved == 0) ? 1 : _reserved * 2;
        T* temp = new T[_reserved];

        for (int i = 0; i < _size; i++)
        {
            temp[i] = _elems[i];
        }

        delete[] _elems;
        _elems = new T[_reserved];

        for (int i = 0; i < _size; i++)
        {
            _elems[i] = temp[i];
        }

        delete[] temp;
    }

    // Member variables
    int _reserved; // The current capacity of " _elems " array
    int _size; // The number of elements stored

    T* _elems; // Array for storing the elements
};

# endif // ARRAYLIST_H
