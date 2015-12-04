//* simplified circular-based list class template *


#ifndef _SLISTT
#define _SLISTT
#include <cstddef>


//* forward class declarations *


template <typename ElementType> class link;
template <typename ElementType> class listIterator;
template <typename ElementType> class const_listIterator;
template <typename ElementType> class reverse_listIterator;
template <typename ElementType> class const_reverse_listIterator;
template <typename ElementType> class list;

//* link - a basic element of a list *


template <typename ElementType>
class link {
private:
    ElementType value;
    link<ElementType> * prevLink;
    link<ElementType> * nextLink;
    link() { }
    link(const ElementType & v) : value(v), nextLink(0), prevLink(0) { }
    // allow list and iterator to see the data values and use the constructor
    friend class list<ElementType>;
    friend class listIterator<ElementType>;
    friend class const_listIterator<ElementType>;
    friend class reverse_listIterator<ElementType>;
    friend class const_reverse_listIterator<ElementType>;
};


//* iterator - the tool to go through all list elements *


template <typename ElementType>
class listIterator {
    typedef listIterator<ElementType> iterator;
public:
    // constructors
    listIterator()
        : currentLink(0) { }
    listIterator(link<ElementType> * cl)
        : currentLink(cl) { }

    // iterator protocol
    ElementType & operator * () const // Note this const relates only to the pointer currentLink
    {
        return currentLink->value;
    }
    bool        operator != (const iterator & rhs) const
    {
        return currentLink != rhs.currentLink;
    }
    bool        operator == (const iterator & rhs) const
    {
        return currentLink == rhs.currentLink;
    }
    const iterator&   operator ++ ()
    {
        currentLink = currentLink->nextLink; return *this;
    }
    iterator    operator ++ (int);
    const iterator&   operator -- ()
    {
        currentLink = currentLink->prevLink; return *this;
    }
    iterator    operator -- (int);

protected:
    link<ElementType> *  currentLink;
    friend class list<ElementType>;
    friend class const_listIterator<ElementType>;
};

// postfix form of increment of the iterator
template <typename ElementType>
listIterator<ElementType> listIterator<ElementType>::operator ++ (int)
{
    // clone, then increment, return clone
    listIterator clone(currentLink);
    currentLink = currentLink->nextLink;
    return clone;
}

// postfix form of decrement of the iterator
template <typename ElementType>
listIterator<ElementType> listIterator<ElementType>::operator -- (int)
{
    // clone, then increment, return clone
    listIterator clone(currentLink);
    currentLink = currentLink->prevLink;
        return clone;
}


//* const_iterator - the tool to go through all list elements *


template <typename ElementType>
class const_listIterator {
    typedef listIterator<ElementType> iterator;
    typedef const_listIterator<ElementType> const_iterator;
public:
    // constructors
    const_listIterator()
        : currentLink(0) { }
    const_listIterator(const link<ElementType> * cl)
        : currentLink(cl) { }
    const_listIterator(const iterator& it)
        : currentLink(it.currentLink) { }

    // iterator protocol
    const ElementType & operator * () const
    {
        return currentLink->value;
    }
    bool    operator != (const const_iterator & rhs) const
    {
        return currentLink != rhs.currentLink;
    }
    bool    operator == (const const_iterator & rhs) const
    {
        return currentLink == rhs.currentLink;
    }
    const const_iterator &operator ++ ()
    {
        currentLink = currentLink->nextLink; return *this;
    }
    const_iterator  operator ++ (int);
    const const_iterator &operator -- ()
    {
        currentLink = currentLink->prevLink; return *this;
    }
    const_iterator  operator -- (int);

protected:
    const link<ElementType>  * currentLink;
    friend class list<ElementType>;
};

// postfix form of increment of the iterator
template <typename ElementType>
const_listIterator<ElementType> const_listIterator<ElementType>::operator ++ (int)
{
    // clone, then increment, return clone
    const_listIterator clone(currentLink);
    currentLink = currentLink->nextLink;
    return clone;
}

// postfix form of decrement of the iterator
template <typename ElementType>
const_listIterator<ElementType> const_listIterator<ElementType>::operator -- (int)
{
    // clone, then increment, return clone
   const_listIterator clone(currentLink);
    currentLink = currentLink->prevLink;
        return clone;
}


//* reverse_iterator - the tool to go through all list elements *


template <typename ElementType>
class reverse_listIterator {
    typedef reverse_listIterator<ElementType> reverse_iterator;
public:
    // constructors
    reverse_listIterator()
        : currentLink(0) { }
    reverse_listIterator(link<ElementType> * cl)
        : currentLink(cl) { }

    // reverse_iterator protocol
    ElementType & operator * () const // Note this const relates only to the pointer currentLink
    {
        return currentLink->value;
    }
    bool        operator != (const reverse_iterator & rhs) const
    {
        return currentLink != rhs.currentLink;
    }
    bool        operator == (const reverse_iterator & rhs) const
    {
        return currentLink == rhs.currentLink;
    }
    const reverse_iterator&   operator ++ ()
    {
        currentLink = currentLink->prevLink; return *this;
    }
    reverse_iterator    operator ++ (int);
    const reverse_iterator&   operator -- ()
    {
        currentLink = currentLink->nextLink; return *this;
    }
    reverse_iterator    operator -- (int);

protected:
    link<ElementType> *  currentLink;
    friend class list<ElementType>;
    friend class const_reverse_listIterator<ElementType>;
};

// postfix form of increment of the reverse_iterator
template <typename ElementType>
reverse_listIterator<ElementType> reverse_listIterator<ElementType>::operator ++ (int)
{
    // clone, then increment, return clone
    reverse_listIterator clone(currentLink);
    currentLink = currentLink->prevLink;
    return clone;
}

// postfix form of decrement of the reverse_iterator
template <typename ElementType>
reverse_listIterator<ElementType> reverse_listIterator<ElementType>::operator -- (int)
{
    // clone, then increment, return clone
    reverse_listIterator clone(currentLink);
    currentLink = currentLink->nextLink;
    return clone;
}


//* const_reverse_iterator - the tool to go through all list elements *


template <typename ElementType>
class const_reverse_listIterator {
    typedef reverse_listIterator<ElementType> reverse_iterator;
    typedef const_reverse_listIterator<ElementType> const_reverse_iterator;
public:
    // constructors
    const_reverse_listIterator()
        : currentLink(0) { }
    const_reverse_listIterator(const link<ElementType> * cl)
        : currentLink(cl) { }
    const_reverse_listIterator(const reverse_iterator& it)
        : currentLink(it.currentLink) { }

    // reverse_iterator protocol
    const ElementType & operator * () const
    {
        return currentLink->value;
    }
    bool    operator != (const const_reverse_iterator & rhs) const
    {
        return currentLink != rhs.currentLink;
    }
    bool    operator == (const const_reverse_iterator & rhs) const
    {
        return currentLink == rhs.currentLink;
    }
    const const_reverse_iterator &operator ++ ()
    {
        currentLink = currentLink->prevLink; return *this;
    }
    const_reverse_iterator  operator ++ (int);
    const const_reverse_iterator &operator -- ()
    {
        currentLink = currentLink->nextLink; return *this;
    }
    const_reverse_iterator  operator -- (int);

protected:
    const link<ElementType>  * currentLink;
    friend class list<ElementType>;
};

// postfix form of increment of the reverse_iterator
template <typename ElementType>
const_reverse_listIterator<ElementType> const_reverse_listIterator<ElementType>::operator ++ (int)
{
    // clone, then increment, return clone
    const_reverse_listIterator clone(currentLink);
    currentLink = currentLink->prevLink;
    return clone;
}

// postfix form of decrement of the reverse_iterator
template <typename ElementType>
const_reverse_listIterator<ElementType> const_reverse_listIterator<ElementType>::operator -- (int)
{
    // clone, then increment, return clone
    reverse_listIterator clone(currentLink);
    currentLink = currentLink->nextLink;
    return clone;
}


//* list - the main data structure *


template <typename ElementType>
class list {
public:
    // type definitions
    typedef ElementType                             value_type;
    typedef listIterator<ElementType>               iterator;
    typedef const_listIterator<ElementType>         const_iterator;
    typedef reverse_listIterator<ElementType>       reverse_iterator;
    typedef const_reverse_listIterator<ElementType> const_reverse_iterator;

    // constructors and destructor
    list();
    list(const list<ElementType> & x);
    ~list() { clear(); delete endLink; }

    // operations
    bool empty() const { return (endLink == endLink->nextLink); }
    size_t size() const { return(m_size); }
    ElementType &   back() { return endLink->prevLink->value; }
    const ElementType &   back() const { return endLink->prevLink->value; }
    ElementType &   front() { return endLink->nextLink->value; }
    const ElementType &   front() const { return endLink->nextLink->value; }
    void            push_front(const ElementType & newValue);
    void            push_back(const ElementType & newValue);
    void            pop_front();
    void            pop_back();
    iterator        begin() { return iterator(endLink->nextLink); }
    const_iterator  begin() const { return const_iterator(endLink->nextLink); }
    const_iterator  cbegin() const { return const_iterator(endLink->nextLink); }
    iterator        end() { return iterator(endLink); }
    const_iterator  end() const { return const_iterator(endLink); }
    const_iterator  cend() const { return const_iterator(endLink); }
    iterator        insert(iterator before, const ElementType & value);
    void            insert(iterator before, const_iterator beg2, const_iterator end2);
    void            erase(iterator start, iterator stop);
    void            erase(iterator iter);
    void            clear();

    reverse_iterator        rbegin() { return reverse_iterator(endLink->prevLink); }
    const_reverse_iterator  rbegin() const { return const_reverse_iterator(endLink->prevLink); }
    const_reverse_iterator  crbegin() const { return const_reverse_iterator(endLink->prevLink); }
    reverse_iterator        rend() { return reverse_iterator(endLink); }
    const_reverse_iterator  rend() const { return const_reverse_iterator(endLink); }
    const_reverse_iterator  crend() const { return const_reverse_iterator(endLink); }

protected:
    link<ElementType> * endLink;
    friend class listIterator<ElementType>;
    friend class const_listIterator<ElementType>;
    friend class reverse_listIterator<ElementType>;
    friend class const_reverse_listIterator<ElementType>;

private:
    size_t m_size = 0;

    void sort();       // disabled - set as private and let unimplemented
    void reverse();    // disabled - set as private and let unimplemented
    void unique();     // disabled - set as private and let unimplemented

    list<ElementType>& operator= (const list<ElementType> &rhs);
};


template <typename ElementType>
list<ElementType>::list()
{
    endLink = new link<ElementType>();
    endLink->nextLink = endLink;
    endLink->prevLink = endLink;
}

template <typename ElementType>
list<ElementType>::list(const list<ElementType> & x)
{

    endLink = new link<ElementType>();
    endLink->nextLink = endLink;
    endLink->prevLink = endLink;
    insert(begin(), x.begin(), x.end());
    m_size = x.m_size;
}

// add a new value to the front of a list
template <typename ElementType>
void list<ElementType>::push_front(const ElementType & newValue)
{
    link<ElementType> * newLink = new link<ElementType>(newValue);
    newLink->nextLink = endLink->nextLink;
    newLink->prevLink = endLink;

    endLink->nextLink->prevLink = newLink;
    endLink->nextLink = newLink;

    m_size++;
}

// remove first element from linked list
template <typename ElementType>
void list<ElementType>::pop_front()
{
    link<ElementType> * save = endLink->prevLink;
    endLink->prevLink = save->prevLink;
    endLink->prevLink->nextLink = endLink;
    delete save;
    m_size--;
}

// add a new value to the end of a list
template <typename ElementType>
void list<ElementType>::push_back(const ElementType & newValue)
{
    link<ElementType> * newLink = new link<ElementType>(newValue);
    newLink->prevLink = endLink->prevLink;
    newLink->nextLink = endLink;

    endLink->prevLink->nextLink = newLink;
    endLink->prevLink = newLink;
    m_size++;
}

// remove last element from linked list
template <typename ElementType>
void list<ElementType>::pop_back()
{
    link<ElementType> * save = endLink->nextLink;
    endLink->nextLink = save->nextLink;
    endLink->nextLink->prevLink = endLink;
    delete save;
    m_size--;
}


template <typename ElementType>
listIterator<ElementType> list<ElementType>::insert(listIterator<ElementType> before, const ElementType & value)
// insert a new element into the middle of a linked list
{
    link<ElementType> * newLink = new link<ElementType>(value);
    link<ElementType> * current = before.currentLink;
    newLink->nextLink = current;
    newLink->prevLink = current->prevLink;
    current->prevLink = newLink;
    (newLink->prevLink)->nextLink = newLink;
    m_size++;
    return(iterator(newLink));
}

template <typename ElementType>
void list<ElementType>::insert(iterator before, const_iterator beg2, const_iterator end2)
// insert a copy of a partial list of elements into the middle of a linked list
{
    for (const_iterator it = beg2; it != end2; ++it)
    {
        insert(before, *it);
        m_size++;
    }

}

template <typename ElementType>
void list<ElementType>::erase(listIterator<ElementType> start, listIterator<ElementType> stop)
// remove values from the range of elements
{
    link<ElementType> * prev = start.currentLink->prevLink;
    link<ElementType> * last = stop.currentLink;
    prev->nextLink = last;
    last->prevLink = prev;

    // now delete the values
    while (start != stop) {
        link<ElementType> * todelete = start.currentLink;
        ++start;
        delete todelete;
        m_size--;
    }
}

template <typename ElementType>
void list<ElementType>::erase(listIterator<ElementType> iter)
{
    listIterator<ElementType> next;
    next = iter;
    ++next;
    erase(iter, next);
}

template <typename ElementType>
void list<ElementType>::clear()
{
    while (!empty()) pop_front();
}

#endif
