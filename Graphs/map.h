#pragma once

template <typename T, typename I>
class Map
{
public:
    Map() : size_(0), capacity_(10) 
    {
        keys_ = new T[capacity_];
        values_ = new I[capacity_];
    }

    ~Map() {
        delete[] keys_;
        delete[] values_;
    }

    void insert(const T& key, const I& value) 
    {
        // Check if the key already exists and update the value
        for (size_t i = 0; i < size_; ++i) {
            if (keys_[i] == key) {
                values_[i] = value;
                return;
            }
        }

        if (size_ == capacity_) 
        {
            resize();
        }

        // Insert the new key-value pair
        keys_[size_] = key;
        values_[size_] = value;
        ++size_;
    }

    // Method to get the value associated with a key
    bool get(const T& key, I& value) const 
    {
        for (size_t i = 0; i < size_; ++i) 
        {
            if (keys_[i] == key) 
            {
                value = values_[i];
                return true;
            }
        }
        return false;
    }

    // Method to check if a key exists
    bool exists(const T& key) const 
    {
        for (size_t i = 0; i < size_; ++i) 
        {
            if (keys_[i] == key) {
                return true;
            }
        }
        return false;
    }

private:
    void resize() 
    {
        capacity_ *= 2;
        T* new_keys = new T[capacity_];
        I* new_values = new I[capacity_];

        for (size_t i = 0; i < size_; ++i) {
            new_keys[i] = keys_[i];
            new_values[i] = values_[i];
        }

        delete[] keys_;
        delete[] values_;

        keys_ = new_keys;
        values_ = new_values;
    }

    T* keys_;
    I* values_;
    size_t size_;
    size_t capacity_;
};
