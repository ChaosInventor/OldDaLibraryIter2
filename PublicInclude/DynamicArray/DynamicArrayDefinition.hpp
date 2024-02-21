#ifndef DYNAMIC_ARRAY__DYNAMIC_ARRAY_DYNAMIC_ARRAY_DEFINITION_HPP
#define DYNAMIC_ARRAY__DYNAMIC_ARRAY_DYNAMIC_ARRAY_DEFINITION_HPP

#include "Debug/Debug.hpp"
#include "Meta/Meta.hpp"
#include "DynamicArrayDeclaration.hpp"

namespace Library
{

    template<typename T>
    struct DynamicArray
    {

        T* m_Location;
        Size m_Used;
        Size m_Capacity;
    
        DynamicArray():
        m_Location(nullptr),
        m_Used(0),
        m_Capacity(0)
        { }
        DynamicArray(const DynamicArray<T>& p_other):
        m_Location(p_other.m_Location),
        m_Used(p_other.m_Used),
        m_Capacity(p_other.m_Capacity)
        { }
        DynamicArray(DynamicArray<T>&& p_other):
        m_Location(p_other.m_Location),
        m_Used(p_other.m_Used),
        m_Capacity(p_other.m_Capacity)
        {
            p_other.m_Location = nullptr;
            p_other.m_Used = 0;
            p_other.m_Capacity = 0;
        }

        DynamicArray(T* p_location, const Size& p_usedAndCapacity):
        m_Location(p_location),
        m_Used(p_usedAndCapacity),
        m_Capacity(p_usedAndCapacity)
        { }
        DynamicArray(T* p_location, const Size& p_used, const Size& p_capacity):
        m_Location(p_location),
        m_Used(p_used),
        m_Capacity(p_capacity)
        { }


        DynamicArray<T>& operator=(const DynamicArray<T>& p_other)
        {
            m_Location = p_other.m_Location;
            m_Used = p_other.m_Used;
            m_Capacity = p_other.m_Capacity;
        }
        DynamicArray<T>& operator=(DynamicArray<T>&& p_other)
        {

            m_Location = p_other.m_Location;
            m_Used = p_other.m_Used;
            m_Capacity = p_other.m_Capacity;
        
            p_other.m_Location = nullptr;
            p_other.m_Used = 0;
            p_other.m_Capacity = 0;
        
        }

        bool operator==(const DynamicArray<T>& p_other)
        {
            return 
                m_Location == p_other.m_Location
                &&
                m_Used == p_other.m_Used
                &&
                m_Capacity == p_other.m_Capacity;
        }
        bool operator!=(const DynamicArray<T>& p_other)
        {
            return !(*this == p_other);
        }

    };

    template<typename T>
    bool DynamicArrayIsNull(const DynamicArray<T>& p_dArray)
    {
        return p_dArray.m_Location == nullptr;
    }
    template<typename T>
    bool DynamicArrayIsEmpty(const DynamicArray<T>& p_dArray)
    {
        return p_dArray.m_Used == 0 && p_dArray.m_Capacity > 0;
    }


}

#endif //DYNAMIC_ARRAY__DYNAMIC_ARRAY_DYNAMIC_ARRAY_DEFINITION_HPP