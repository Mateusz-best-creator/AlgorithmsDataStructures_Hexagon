#pragma once

#include <cassert>

template <typename T>
class Vector
{
private:
    T* m_data;
    size_t m_size, m_max_size;

public:
    explicit Vector(size_t init_size = 0)
    {
        m_max_size = init_size > 0 ? init_size : 1;
        m_data = new T[m_max_size];
        m_size = init_size;
    }

    Vector(const Vector& other)
    {
        m_max_size = other.get_m_max_size();
        m_size = other.size();
        m_data = new T[m_max_size];
        for (size_t i = 0; i < m_size; i++)
            m_data[i] = other.m_data[i];
    }

    Vector(const Vector&& other) noexcept
        : m_data(other.m_data), m_size(other.m_size), m_max_size(other.m_max_size)
    {
        other.m_size = 0;
        other.m_max_size = 0;
        other.m_data = nullptr;
    }

    Vector& operator=(const Vector& other)
    {
        if (this == &other)
            return*this;

        delete[] m_data;
        m_size = other.m_size;
        m_max_size = other.m_max_size;
        m_data = new T[m_max_size];
        for (size_t i = 0; i < m_size; i++)
            m_data[i] = other.m_data[i];

        return*this;
    }

    ~Vector()
    {
        std::cout << "Deleting Vector\n";
        if (m_data != nullptr)
            delete[] m_data;
    }

    void push_back(T value)
    {
        if (m_size >= m_max_size)
        {
            m_max_size *= 2;
            T* m_data_new = new T[m_max_size];
            for (size_t i = 0; i < m_size; i++)
                m_data_new[i] = m_data[i];
            delete[] m_data;
            m_data = m_data_new;
        }
        m_data[m_size++] = value;
    }

    T& at(int index)
    {
        assert(index >= 0 && index < m_size);
        return m_data[index];
    }
    
    T& operator[](int index)
    {
        assert(index >= 0 && index < m_size);
        return m_data[index];
    }

    const T& operator[](int index) const
    {
        assert(index >= 0 && index < m_size);
        return m_data[index];
    }

    const size_t& get_m_max_size() const
    {
        return m_max_size;
    }

    const size_t& size() const
    {
        return m_size;
    }
};