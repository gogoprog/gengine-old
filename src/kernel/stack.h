#pragma once

#include <stack>

namespace gengine
{

template<typename T>
class Stack
{
public:
    void push(const T & t)
    {
        data.push(t);
    }

    void pop()
    {
        data.pop();
    }

    T & getTop() { return data.top(); }
    const T & getTop() const { return data.top(); }

protected:
    std::stack<T> data;
};

}
