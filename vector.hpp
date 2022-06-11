
#ifndef VECTOR_H
#define VECTOR_H

#include <initializer_list>

template <typename T>
class Vector
{
public:
    Vector();
    Vector(const Vector<T> &);
    Vector(Vector<T> &&);
    Vector(size_t);
    Vector(size_t, const T &val);
    Vector(std::initializer_list<T>);
    ~Vector();

public:
    Vector &operator=(const Vector<T> &);
    Vector &operator=(Vector<T> &&);
    T &at(size_t);
    bool empty();
    size_t size();
    size_t capasity();
    void shrink_to_fit();
    void clear();
    void insert(size_t, const T &);
    void erase(size_t);
    void push_back(const T &);
    void pop_back();
    T &operator[](size_t pos);
    T &front();
    T &back();
    void reserve(size_t);
    void resize(size_t);

    bool operator==(const Vector<T> &);
    bool operator!=(const Vector<T> &);
    bool operator>(const Vector<T> &);
    bool operator<(const Vector<T> &);
    bool operator>=(const Vector<T> &);
    bool operator<=(const Vector<T> &);

private:
    size_t m_cap;
    size_t m_size;
    T *m_buffer;
};

template <>
class Vector<bool>
{
public:
    Vector<bool>();
    Vector<bool>(const Vector<bool>&);
    Vector<bool>(Vector<bool>&&);
    Vector<bool>(size_t);
    Vector<bool>(size_t, bool);
    Vector<bool>(std::initializer_list<bool>);
    ~Vector<bool>();

public:
    class reference
    {
    public:
        reference(size_t*, size_t);
        reference(const reference&);
        reference(reference&&);
        ~reference();
        reference& operator=(const reference&);
        reference& operator=(reference&&);
        reference& operator=(bool);
        operator bool() const;
        void flip();

    private:
        size_t* _buffer;
        size_t _index;
        bool _value;
    };

public:
    Vector<bool>& operator=(const Vector<bool>&);
    Vector<bool>& operator=(Vector<bool>&&);
    reference at(size_t);
    bool empty() const;
    size_t size() const;
    size_t capasity() const;
    void clear();
    void insert(size_t, bool);
    void erase(size_t);
    void push_back(bool);
    void pop_back();
    reference operator[](size_t);
    reference front();
    reference back();
    void resize(size_t);
    void flip();
    void flip(size_t);

private:
    static const size_t bit_count = sizeof(size_t) * 8;

private:
    size_t _cap;
    size_t _size;
    size_t* _buffer;
};

#endif // VECTOR_H