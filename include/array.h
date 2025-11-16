#pragma once
#include <memory>
#include <stdexcept>
#include <iostream>

template <typename T>
class Array {
private:
    size_t m_size;
    size_t m_capacity;
    std::unique_ptr<T[]> m_data;

public:
    Array(size_t capacity = 0) : m_size(0), m_capacity(capacity), m_data(std::make_unique<T[]>(capacity))
    {}

    size_t size() const {
        return m_size;
    }

    size_t capacity() const {
        return m_capacity;
    }

    const T& operator[](size_t index) const {
        if(index >= m_size) throw std::out_of_range("Index out of range");
        return m_data[index];
    }

    void push_back(T&& value) {
        if(m_size == m_capacity) {
            size_t new_capacity = m_capacity == 0 ? 1 : m_capacity * 2;
            auto new_data = std::make_unique<T[]>(new_capacity);
            for(size_t i = 0; i < m_size; i++) {
                new_data[i] = std::move(m_data[i]);
            }
            m_data = std::move(new_data);
            m_capacity = new_capacity;
        }
        m_data[m_size++] = std::move(value);
    }

    void push_back(const T& value) {
        push_back(T(value));
    }

    void erase(size_t index) {
        if(index >= m_size) throw std::out_of_range("Index out of range");
        for(size_t i = index; i < m_size - 1; i++)
            m_data[i] = std::move(m_data[i+1]);
        m_size--;
    }
};