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

#endif // VECTOR_H