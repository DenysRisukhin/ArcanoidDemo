//
//  SharedRef.h
//  ArcanoidDemo
//
//  Created by Denys Risukhin on 12/16/19.
//

#ifndef SharedRef_h
#define SharedRef_h

#include <stdio.h>
#include <iostream>

template<typename T, typename U = T>
T exchange(T& obj, U&& newValue)
{
    T curValue = std::move(obj);
    obj = std::forward<U>(newValue);
    return curValue;
}

#pragma mark - Shared Ref

template<typename T>
class SharedRef {
public:
    SharedRef() {}
    
    SharedRef(T* obj) {
        updateObject(obj);
    }
    
    SharedRef(const SharedRef& rhs)
        : SharedRef(rhs.m_obj)
    {
        // do nothing
    }
    
    SharedRef(SharedRef&& rhs) noexcept
        : m_obj(exchange(rhs.m_obj, nullptr))
    {
        // do nothing
    }
    
    SharedRef& operator=(const SharedRef& rhs)
    {
        updateObject(rhs.m_obj);
        return *this;
    }
    
    SharedRef& operator=(SharedRef&& rhs) noexcept
    {
        std::swap(m_obj, rhs.m_obj);
        return *this;
    }
    
    ~SharedRef()
    {
        updateObject(nullptr);
    }
    
    void reset()
    {
        updateObject(nullptr);
    }
    
    void updateObject(T* obj)
    {
        if (m_obj != obj)
        {
            if (m_obj)
            {
                m_obj->release();
            }
            
            m_obj = obj;
            
            if (m_obj)
            {
                m_obj->retain();
                
            }
        }
    }
    
    operator bool() const
    {
        return m_obj != nullptr;
    }
    
    T* operator->() const
    {
        return m_obj;
    }
    
    bool operator==(T* rhs) const
    {
        return m_obj == rhs;
    }
    
    bool operator!=(T* rhs) const
    {
        return m_obj != rhs;
    }
    
    T* get() const
    {
        return m_obj;
    }
    
private:
    T* m_obj = nullptr;
};

#endif /* SharedRef_h */
