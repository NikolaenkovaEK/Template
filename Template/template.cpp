#include <algorithm>
 
template<class T>
class List
{
public:
    typedef T value_type;
    typedef std::size_t size_type;
 
private:
    struct Knot
    {
        value_type val_;
        Knot * next_;
        Knot(const value_type &val)
        :val_(val), next_(0)
        {}
    };
    Knot * head_;
    size_type nelems_;
 
public:
    //Default constructor
    List() throw()
    :head_(0), nelems_(0)
    {}
    bool empty() const throw()
    { return size() == 0; }
    size_type size() const throw()
    { return nelems_; }
 
private:
    Knot * last() throw() //could be done better
    {
        if(empty()) return 0;
        Knot *p = head_;
        while (p->next_)
            p = p->next_;
        return p;
    }
 
public:
    void push_back(const value_type & val)
    {
        Knot *p = last();
        if(!p)
            head_ = new Knot(val);
        else
            p->next_ = new Knot(val);
        ++nelems_;
    }
    void clear() throw()
    {
        while(head_)
        {
            Knot *p = head_->next_;
            delete head_;
            head_ = p;
        }
        nelems_ = 0;
    }
    //Destructor:
    ~List() throw()
    { clear(); }
    //Iterators:
    class iterator
    {
        Knot * cur_;
    public:
        iterator(Knot *p) throw()
        :cur_(p)
        {}
        bool operator==(const iterator & iter)const throw()
        { return cur_ == iter.cur_; }
        bool operator!=(const iterator & iter)const throw()
        { return !(*this == iter); }
        iterator & operator++()
        {
            cur_ = cur_->next_;
            return *this;
        }
        iterator operator++(int)
        {
            iterator temp(*this);
            operator++();
            return temp;
        }
        value_type & operator*()throw()
        { return cur_->val_; }
        value_type operator*() const
        { return cur_->val_; }
        value_type operator->()
        { return cur_->val_; }
        const value_type operator->() const
        { return cur_->val_; }
    };
    iterator begin() throw()
    { return iterator(head_); }
    iterator begin() const throw()
    { return iterator(head_); }
    iterator end() throw()
    { return iterator(0); }
    iterator end() const throw()
    { return iterator(0); }
    //Copy constructor:
    List(const List & lst)
    :head_(0), nelems_(0)
    {
        for(iterator i = lst.begin(); i != lst.end(); ++i)
            push_back(*i);
    }
    void swap(List & lst) throw()
    {
        std::swap(head_, lst.head_);
        std::swap(nelems_, lst.nelems_);
    }
    List & operator=(const List & lst)
    {
        List(lst).swap(*this);
        return *this;
    }
    //Conversion constructor
    template<class U>
    List(const List<U> &lst)
    :head_(0), nelems_(0)
    {
        for(typename List<U>::iterator iter = lst.begin(); iter != lst.end(); ++iter)
            push_back(*iter);
    }
    template<class U>
    List & operator=(const List<U> &lst)
    {
        List(lst).swap(*this);
        return *this;
    }
    //Sequence constructor:
    template<class Iter>
    List(Iter first, Iter last)
    :head_(0), nelems_(0)
    {
        for(;first!=last; ++first)
            push_back(*first);
    }
};
 
#include <iostream>
using std::cout;
using std::endl;
 
int main()
{
    const char MAX_LIMIT = 127;
    List<short> listA;
    //...
    List<char> listB = listA; //without the conversion constructor this would not go very far!
    for(char i = 0; i < MAX_LIMIT; ++i)
        listB.push_back(i);
    for(List<char>::iterator iter = listB.begin(); iter != listB.end(); ++iter)
        cout << *iter << endl;
	system("pause");
}