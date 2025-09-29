#pragma once
#include <vector>
#include <iostream> 
template <typename T>
class Biogesic			//Same as Ring Buffer class
{
    std::vector<T> _data;
    int _cur_index;

public:
    struct iterator;			//struct

    Biogesic(int size) : _cur_index(0)
    {
        _data.reserve(size);
        for (auto i = 0; i < size; i++)
        {
            _data.push_back(T());
        }
    }

    void add(T value)
    {
        if (_cur_index < _data.size())
        {
            _data[_cur_index] = value;
            _cur_index++;
        }
        else
        {
            _cur_index = 0;
            _data[_cur_index] = value;
        }
    }

    T get(int index)
    {
        if (index < _data.size())
        {
            return _data[index];
        }
        return T();
    }

    int size()
    {
        return static_cast<int>(_data.size());
    }
};

template <typename T>
class Biogesic<T>::iterator
{
public:
    void print() const; 
};

template <typename T>
void Biogesic<T>::iterator::print() const
{
}
