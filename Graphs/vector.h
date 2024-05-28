#pragma once

#include <cassert>
#include <iostream>

template <typename T>
class Vector
{
private:
    T* m_data;
    size_t m_size, m_max_size;

    void merge_sort(T* array, size_t left, size_t right)
    {
        if (left < right)
        {
            size_t middle = left + (right - left) / 2;
            merge_sort(array, left, middle);
            merge_sort(array, middle + 1, right);
            merge(array, left, middle, right);
        }
    }

    void merge(T* array, size_t left, size_t middle, size_t right)
    {
        size_t n1 = middle - left + 1;
        size_t n2 = right - middle;

        T* leftArray = new T[n1];
        T* rightArray = new T[n2];

        for (size_t i = 0; i < n1; i++)
            leftArray[i] = array[left + i];
        for (size_t i = 0; i < n2; i++)
            rightArray[i] = array[middle + 1 + i];

        size_t i = 0, j = 0, k = left;
        while (i < n1 && j < n2)
        {
            if (leftArray[i] >= rightArray[j])
            {
                array[k] = leftArray[i];
                i++;
            }
            else
            {
                array[k] = rightArray[j];
                j++;
            }
            k++;
        }

        while (i < n1)
        {
            array[k] = leftArray[i];
            i++;
            k++;
        }

        while (j < n2)
        {
            array[k] = rightArray[j];
            j++;
            k++;
        }

        delete[] leftArray;
        delete[] rightArray;
    }

public:
    Vector(size_t init_size = 0)
    {
        m_max_size = init_size > 0 ? init_size : 1;
        m_data = new T[m_max_size];
        m_size = init_size;
    }

    Vector(size_t init_size, T default_value)
    {
        m_max_size = init_size > 0 ? init_size : 1;
        m_data = new T[m_max_size];
        m_size = init_size;
        for (size_t i = 0; i < m_size; i++)
            m_data[i] = default_value;
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

    bool contain(T value) const
    {
        for (size_t i = 0; i < m_size; i++)
            if (m_data[i] == value)
                return true;
        return false;
    }

    void clear()
    {
        delete[] m_data;
        m_max_size = 1;
        m_data = new T[m_max_size];
        m_size = 0;
    }

    bool empty() const
    {
        return m_size == 0;
    }

    void sort()
    {
        if (m_size > 1)
            merge_sort(m_data, 0, m_size - 1);
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