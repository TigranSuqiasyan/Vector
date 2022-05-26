#include <iostream>
#include "vector.hpp"

int main()
{
    Vector<int> v1{1,2,3};
    Vector<int> v2{1,2,5};
    v1.clear();
    std::cout << v1.size() << v1.capasity();
}

template <typename T>
Vector<T>::Vector() : m_cap{1}, m_size{}, m_buffer{}
{
}

template <typename T>
Vector<T>::Vector(const Vector<T> &oth)
    : m_cap{oth.m_cap}, m_size{oth.m_size}, m_buffer{}
{
    m_buffer = new T[m_cap];
    for (int i{}; i < m_size; ++i)
    {
        m_buffer[i] = oth.m_buffer[i];
    }
}

template <typename T>
Vector<T>::Vector(Vector<T> &&tmp)
    : m_cap{tmp.m_cap}, m_size{tmp.m_size}, m_buffer{tmp.m_buffer}
{
    tmp.m_buffer = nullptr;
}

template <typename T>
Vector<T>::Vector(size_t count)
    : m_cap{count}, m_size{m_cap}, m_buffer{new T[m_size]}
{
}

template <typename T>
Vector<T>::Vector(size_t count, const T &val)
    : m_cap{count}, m_size{m_cap}, m_buffer{new T[m_size]}
{
    for (int i{}; i < m_size; ++i)
    {
        m_buffer[i] = val;
    }
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> init)
    : m_cap{init.size()}, m_size{init.size()}, m_buffer{new T[m_size]}
{
    int i{};
    for(auto it = init.begin(); it != init.end(); ++it)
    {
        m_buffer[i++] = *it;
    }
}

template <typename T>
Vector<T>::~Vector()
{
    if(m_buffer)
    {
        delete[] m_buffer;
    }
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    m_cap = rhs.m_cap;
    m_size = rhs.m_size;
    if (m_buffer)
    {
        delete[] m_buffer;
    }
    m_buffer = new T[m_cap];
    for (int i{}; i < m_size; ++i)
    {
        m_buffer[i] = rhs.m_buffer[i];
    }
    return *this;
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector<T> &&tmp)
{
    m_cap = tmp.m_cap;
    m_size = tmp.m_size;
    std::swap(m_buffer, tmp.m_buffer);
}

template <typename T>
T &Vector<T>::at(size_t pos)
{
    if (pos < 0 || pos >= pos)
    {
        throw std::out_of_range("");
    }
    return m_buffer[pos];
}

template <typename T>
bool Vector<T>::empty()
{
    return !m_size;
}

template <typename T>
size_t Vector<T>::size()
{
    return m_size;
}

template <typename T>
size_t Vector<T>::capasity()
{
    return m_cap;
}

template <typename T>
void Vector<T>::shrink_to_fit()
{
    if (m_cap == m_size)
    {
        return;
    }
    m_cap = m_size;
    T *temp = new T[m_cap];
    for (int i{}; i < m_size; i++)
    {
        temp[i] = m_buffer[i];
    }
    delete[] m_buffer;
    m_buffer = temp;
    temp = nullptr;
}

template <typename T>
void Vector<T>::clear()
{
    m_size = 0;
    m_cap = 1;
    T* temp = m_buffer;
    m_buffer = new T[m_cap];
    if(temp)
        delete[] temp;
}

template <typename T>
void Vector<T>::insert(size_t pos, const T& val)
{
    if (pos < 0 || pos >= m_size)
    {
        throw std::out_of_range("");
    }
    if(m_size == m_cap)
    {
        m_cap *= 2;
        T* tmp = m_buffer;
        m_buffer = new T[m_cap];
        for(int i{}; i < m_size; ++i)
        {
            m_buffer[i] = tmp[i];
        }
        delete[] tmp;
    }
    int count{};
    for(int i = m_size++; i > pos; --i)
    {
        m_buffer[i] = m_buffer[i - 1];
        m_buffer[pos] = val;
    }
}

template <typename T>
void Vector<T>::push_back(const T& val)
{
    if(m_cap == m_size)
    {
        m_cap *= 2;
        T* tmp = m_buffer;
        m_buffer = new T[m_cap];
        for(int i{}; i < m_size; ++i)
        {
            m_buffer[i] = tmp[i];
        }
        delete[] tmp;
    }
    m_buffer[m_size++] = val;
}

template <typename T>
void Vector<T>::pop_back()
{
    if(!m_size)
    {
        throw std::out_of_range("");
    }
    --m_size;
}

template <typename T>
T& Vector<T>::operator[](size_t pos)
{
    if (pos < 0 || pos >= m_size)
    {
        throw std::out_of_range("");
    }
    return m_buffer[pos];
}

template <typename T>
T& Vector<T>::front()
{
    return m_buffer[0];
}

template <typename T>
T& Vector<T>::back()
{
    return m_buffer[m_size - 1];
}

template <typename T>
void Vector<T>::erase(size_t pos)
{
    if(pos < 0 || pos >= m_size)
    {
        throw std::out_of_range("");
    }
    for(int i = pos; i < m_size - 1; ++i)
    {
        m_buffer[i] = m_buffer[i + 1];
    }
    --m_size;
}

template <typename T>
void Vector<T>::reserve(size_t count)
{
    if(count > m_size && m_buffer)
    {
        m_cap = count;
        T* temp = m_buffer;
        m_buffer = new T[m_cap];
        for(int i{}; i < m_size; ++i)
        {
            m_buffer[i] = temp[i];
        }
        delete[] temp;
    }
}

template <typename T>
void Vector<T>::resize(size_t count)
{
    if(count == m_size && m_buffer)
    {
        this->shrink_to_fit();
    }
    if(count < m_size && m_buffer)
    {
        m_size = count;
        this->shrink_to_fit();
    }
    if(count > m_size && m_buffer)
    {
        m_cap = count;
        T* temp = m_buffer;
        m_buffer = new T[m_cap];
        for(int i{}; i < m_size; ++i)
        {
            m_buffer[i] = temp[i];
        }
        delete[] temp;
    }
}

template <typename T>
bool Vector<T>::operator==(const Vector<T>& rhs)
{
    if(m_size != rhs.m_size)
        return false;
    for(int i{}; i < m_size; ++i)
    {
        if(m_buffer[i] != rhs.m_buffer[i])
            return false;
    }
    return true;
}

template <typename T>
bool Vector<T>::operator!=(const Vector<T>& rhs)
{
    return !this->operator==(rhs);
}

template <typename T>
bool Vector<T>::operator>(const Vector<T>& rhs)
{
    size_t min_size = m_size < rhs.m_size ? m_size : rhs.m_size;
    for(int i{}; i < min_size; ++i)
    {
        if(m_buffer[i] != rhs.m_buffer[i])
            return m_buffer[i] > rhs.m_buffer[i];
    }
    if(m_size == rhs.m_size)
        return false;
    else
        return m_size > rhs.m_size;
}

template <typename T>
bool Vector<T>::operator<(const Vector<T>& rhs)
{
    size_t min_size = m_size < rhs.m_size ? m_size : rhs.m_size;
    for(int i{}; i < min_size; ++i)
    {
        if(m_buffer[i] != rhs.m_buffer[i])
            return m_buffer[i] < rhs.m_buffer[i];
    }
    if(m_size == rhs.m_size)
        return false;
    else
        return m_size < rhs.m_size;
}

template <typename T>
bool Vector<T>::operator>=(const Vector<T>& rhs)
{
    return !this->operator<(rhs);
}

template <typename T>
bool Vector<T>::operator<=(const Vector<T>& rhs)
{
    return !this->operator>(rhs);
}
