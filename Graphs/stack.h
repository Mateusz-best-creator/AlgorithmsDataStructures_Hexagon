#ifndef __STACK_H__
#define __STACK_H__

#include <cassert>
#include <iostream>

template <typename T>
class Stack
{
private:
    T* m_Data = nullptr;
    size_t m_Size = 0;
    size_t m_Capacity = 0;

public:
    // Constructors and destructors
    Stack()
    {
        ReAlloc(2);
    }

    // Push and Pop functions
    void push(const T& value)
    {
        if (m_Size >= m_Capacity)
        {
            if (m_Capacity == 0)
                ReAlloc(5);
            else
                ReAlloc(m_Capacity * 3);
        }
        m_Data[m_Size++] = value;
    }

    T top() const
    {
        return m_Data[m_Size - 1];
    }

    void pop()
    {
        m_Size--;
    }

    // Overloaded operators
    T& operator[](size_t index)
    {
        assert((index < m_Size) && "Index out of range");
        return m_Data[index];
    }

    const T& operator[](size_t index) const
    {
        assert((index < m_Size) && "Index out of range");
        return m_Data[index];
    }

    bool empty() const
    {
        return m_Size == 0;
    }

    // Getters and setters
    size_t size() const { return m_Size; }
    size_t capacity() const { return m_Capacity; }
    T& back() { return m_Data[m_Size - 1]; }
    const T& back() const { return m_Data[m_Size - 1]; }

    // friend functions
    friend std::ostream& operator<<(std::ostream& os, const Stack& other)
    {
        for (size_t i = 0; i < other.m_Size; i++)
        {
            os << other.m_Data[i];
        }
        return os;
    }

private:
    void ReAlloc(size_t newCapacity)
    {
        // Allocate new block of memory
        T* newBlock = new T[newCapacity];

        if (newCapacity < m_Size)
            m_Size = newCapacity;

        // Copy elements
        for (size_t i = 0; i < m_Size; i++)
            newBlock[i] = m_Data[i];
        
        // delete
        delete[] m_Data;
        m_Data = newBlock;
        m_Capacity = newCapacity;
    }
};

#endif