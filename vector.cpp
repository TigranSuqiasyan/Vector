#include <iostream>
#include "vector.hpp"

int main()
{
    Vector<bool> vb;
    for(int i = 0; i < 10; ++i)
    {
        vb.push_back(false);
    }
    std::cout << vb.size() << std::endl;
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

// SPECIALIZATION FOR BOOL

// proxy class reference
Vector<bool>::reference::reference
        (size_t* buffer, size_t index)
    :_buffer{buffer}, _index{index}, _value{}
{
}

Vector<bool>::reference::reference
        (const reference& oth)
    : _buffer{oth._buffer}, _index{oth._index}, _value{}
{
}

Vector<bool>::reference::reference
        (reference&& oth)
    : _buffer{std::move(oth._buffer)},
    _index{oth._index},
    _value{oth._value}
{
}

Vector<bool>::reference::~reference() = default;

Vector<bool>::reference& Vector<bool>::reference::operator=
    (const Vector<bool>::reference& rhs)
{
    if(_value != rhs._value)
        this->flip();
    return *this;
}

Vector<bool>::reference& Vector<bool>::reference::operator=
    (Vector<bool>::reference&& rhs)
{
    if(_value != rhs._value)
        this->flip();
    return *this;
}

Vector<bool>::reference& Vector<bool>::reference::operator=
    (bool value)
{
    if(_value != value)
        this->flip();
    return *this;
}

Vector<bool>::reference::operator bool() const
{
    return _value;
}

void Vector<bool>::reference::flip()
{
    _buffer[_index / bit_count] ^= (1 << (_index % bit_count));
}

Vector<bool>::Vector()
    : _cap{bit_count}, _size{}, _buffer{new size_t}
{
}

Vector<bool>::Vector(size_t count)
    : _cap{(count / bit_count + 1) * bit_count}, 
    _size{count},
    _buffer{}
{
    _buffer = new size_t[_cap / bit_count];
    for(size_t i{}; i < _size; ++i)
    {
        this->operator[](i) = false;
    }
}

Vector<bool>::reference Vector<bool>::operator[]
    (size_t pos)
{
    Vector<bool>::reference result(_buffer, pos);
    return result;
}

Vector<bool>::Vector(size_t count, bool value)
    : _cap{(count / bit_count + 1) * bit_count},
    _size{count},
    _buffer{}
{
    _buffer = new size_t[_cap / bit_count];
    for(size_t i{}; i < _size; ++i)
    {
        this->operator[](i) = value;
    }
}

Vector<bool>::Vector(const Vector<bool>& oth)
    : _cap{oth._cap}, _size{oth._size}, _buffer{}
{
    _buffer = new size_t[_cap / bit_count ];
    for(size_t i{}; i < _cap / bit_count; ++i)
    {
        _buffer[i] = oth._buffer[i];
    }
}

Vector<bool>::Vector(Vector<bool>&& oth)
    : _cap{oth._cap}, _size{oth._size}, _buffer{oth._buffer}
{
}

Vector<bool>::Vector(std::initializer_list<bool> init)
    : _cap{(init.size() / bit_count + 1) * bit_count},
    _size{init.size()},
    _buffer{}
{
    _buffer = new size_t[_cap / bit_count];
    auto it = init.begin();
    size_t i{};
    for(; it != init.end(); ++i)
    {
        this->operator[](i) = *(it++);
    }
}

Vector<bool>::~Vector()
{
    delete[] _buffer;
}

Vector<bool>& Vector<bool>::operator=
    (const Vector<bool>& rhs)
{
    if(this == &rhs)
        return *this;
    _cap = rhs._cap;
    _size = rhs._size;
    size_t* temp = new size_t[_cap / bit_count];
    for(size_t i{}; i < _cap / bit_count; ++i)
    {
        temp[i] = rhs._buffer[i];
    }
    delete[] _buffer;
    _buffer = temp;
    temp = nullptr;
    return *this;
}

Vector<bool>& Vector<bool>::operator=
    (Vector<bool>&& rhs)
{
    _cap = rhs._cap;
    _size = rhs._size;
    _buffer = std::move(rhs._buffer);
    return *this;
}

Vector<bool>::reference Vector<bool>::at(size_t pos)
{
    if(pos > 0 && pos <= _size)
        return this->operator[](pos);
    throw std::out_of_range("");
}

bool Vector<bool>::empty() const
{
    return !_size;
}

size_t Vector<bool>::size() const
{
    return _size;
}

size_t Vector<bool>::capasity() const
{
    return _cap;
}

void Vector<bool>::clear()
{
    _cap = bit_count;
    _size = 0;
    delete[] _buffer;
    _buffer = new size_t[_cap / bit_count];
}

void Vector<bool>::insert(size_t pos, bool value)
{
    if(_cap == _size)
    {
        _cap += bit_count;
        size_t* temp = new size_t[_cap / bit_count];
        for(size_t i{}; i < _cap / bit_count; ++i)
        {
            temp[i] = _buffer[i];
        }
        delete[] _buffer;
        _buffer = temp;
        temp = nullptr;
    }
    for(size_t i = _size; i > pos; --i)
    {
        this->operator[](i) = this->operator[](i - 1);
    }
    this->operator[](pos) = value;
    ++_size;
}

void Vector<bool>::erase(size_t pos)
{
    if(this->empty() || pos >= _size)
        throw std:: out_of_range("");
    for(size_t i{pos}; i < _size - 1; ++i)
    {
        this->operator[](i) = this->operator[](i + 1);
    }
    --_size;
}

void Vector<bool>::push_back(bool value)
{
    if(_size == _cap)
    {
        _cap += bit_count;
        size_t* temp = new size_t[_cap / bit_count];
        for(size_t i{}; i < _cap / bit_count; ++i)
        {
            temp[i] = _buffer[i];
        }
        delete[] _buffer;
        _buffer = temp;
        temp = nullptr;
    }
    this->operator[](_size++) = value;
}

void Vector<bool>::pop_back()
{
    if(this->empty())
        throw std::out_of_range("");
    this->operator[](_size--) = false;
}

Vector<bool>::reference Vector<bool>::front()
{
    return this->operator[](0);
}

Vector<bool>::reference Vector<bool>::back()
{
    return this->operator[](_size - 1);
}

void Vector<bool>::resize(size_t count)
{
    _cap = (count / bit_count + 1) * bit_count;
    size_t* temp = new size_t[_cap / bit_count];
    for(size_t i{}; i < _cap / bit_count; ++i)
    {
        temp[i] = _buffer[i];
    }
    delete[] _buffer;
    _buffer = temp;
    temp = nullptr;
    if(count < _size)
        _size = count;
}

void Vector<bool>::flip()
{
    for(size_t i{}; i < _cap / bit_count; ++i)
    {
        _buffer[i] = ~_buffer[i];
    }
}

void Vector<bool>::flip(size_t pos)
{
    _buffer[pos / bit_count] ^= (1 << (pos % bit_count));
}