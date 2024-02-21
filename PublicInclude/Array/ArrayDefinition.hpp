#ifndef ARRAY__ARRAY_ARRAY_DEFINITION_HPP
#define ARRAY__ARRAY_ARRAY_DEFINITION_HPP

#include "Debug/Debug.hpp"
#include "Meta/Meta.hpp"
#include "ArrayDeclaration.hpp"

#define ValidateArray(p_array)\
    if((p_array).m_Location == nullptr)                                     \
    {                                                                       \
        Assert((p_array).m_Size == 0,                                       \
        "Fixed array cannot have a size of " << (p_array).m_Size            \
        << " while it has a null buffer, it must have a size of 0")         \
    }
#define ValidateIndexInArray(p_index, p_array)\
    Assert(                                                             \
        (p_index) < (p_array).m_Size,                                   \
        "Index " << (p_index) << " is an invalid index in an array of " \
        "size " << (p_array).m_Size                                     \
    );

namespace Library
{

    template<typename T>
    struct Array
    {

        T* m_Location;
        Size m_Size;
    
        Array():
        m_Location(nullptr),
        m_Size(0)
        { }
        Array(const Array& p_other):
        m_Location(p_other.m_Location),
        m_Size(p_other.m_Size)
        { }
        Array(Array&& p_other):
        m_Location(p_other.m_Location),
        m_Size(p_other.m_Size)
        {
            p_other.m_Location = nullptr;
            p_other.m_Size = 0;
        }

        Array(T* const& p_buffer, const Size& p_size):
        m_Location(p_buffer),
        m_Size(p_size)
        { }

        Array(T& p_item):
        m_Location(&p_item),
        m_Size(1)
        { }

        Array& operator=(const Array& p_other)
        {

            m_Location = p_other.m_Location;
            m_Size = p_other.m_Size;

            return *this;
        
        }
        Array& operator=(Array&& p_other)
        {

            m_Location = p_other.m_Location;
            m_Size = p_other.m_Size;

            p_other.m_Location = nullptr;
            p_other.m_Size = 0;

            return *this;
        
        }


        T& operator[](const Size& p_index) const
        {
            ValidateArray(*this)
            ValidateIndexInArray(p_index, *this);
            return m_Location[p_index];
        }


        bool operator==(const Array& p_other) const
        {
            return (m_Location == p_other.m_Location) && (m_Size == p_other.m_Size);
        }
        bool operator!=(const Array& p_other) const
        {
            return !(*this == p_other);
        }

    };

    template<typename T>
    struct Array<const T>
    {

        const T* m_Location;
        Size m_Size;
    
        Array():
        m_Location(nullptr),
        m_Size(0)
        { }
        Array(const Array& p_other):
        m_Location(p_other.m_Location),
        m_Size(p_other.m_Size)
        { }
        Array(Array&& p_other):
        m_Location(p_other.m_Location),
        m_Size(p_other.m_Size)
        {
            p_other.m_Location = nullptr;
            p_other.m_Size = 0;
        }

        Array(const T* const& p_buffer, const Size& p_size):
        m_Location(p_buffer),
        m_Size(p_size)
        { }
        Array(const Array<T>& p_otherNotReadOnly):
        m_Location((const T*)p_otherNotReadOnly.m_Location),
        m_Size(p_otherNotReadOnly.m_Size)
        { }

        Array(const T& p_item):
        m_Location(&p_item),
        m_Size(1)
        { }

        Array& operator=(const Array& p_other)
        {

            m_Location = p_other.m_Location;
            m_Size = p_other.m_Size;

            return *this;
        
        }
        Array& operator=(Array&& p_other)
        {

            m_Location = p_other.m_Location;
            m_Size = p_other.m_Size;

            p_other.m_Location = nullptr;
            p_other.m_Size = 0;

            return *this;
        
        }


        const T& operator[](const Size& p_index) const
        {
            ValidateArray(*this)
            ValidateIndexInArray(p_index, *this);
            return m_Location[p_index];
        }


        bool operator==(const Array& p_other) const
        {
            return (m_Location == p_other.m_Location) && (m_Size == p_other.m_Size);
        }
        bool operator!=(const Array& p_other) const
        {
            return !(*this == p_other);
        }

    };


    template<typename T>
    void CreateToArrayAsNull(const Array<T>& p_array)
    {
        p_array.m_Location = nullptr;
        p_array.m_Size = 0;
    }
    template<typename T>
    void CreateToArrayFromTPointerFromSize(
        const Array<T>& p_array, T* p_fromLocation, const Size& p_fromSize
    )
    {
        p_array.m_Location = p_fromLocation;
        p_array.m_Size = p_fromSize;
    }
    template<typename T>
    void CreateUsingArrayAsSubArrayWithoutBackByFromSizeAsCount(
        Array<T>& p_subArray, const Size& p_numberOfItems
    )
    {
        ValidateArray(p_subArray);
        Assert(
            p_numberOfItems <= p_subArray.m_Size,
            "Cannot resize array down forward by " << p_numberOfItems
            << " when it's size is only " << p_subArray.m_Size
        );


        p_subArray.m_Location += p_numberOfItems;
        p_subArray.m_Size -= p_numberOfItems;
    }
    template<typename T>
    void CreateUsingArrayAsSubArrayWithoutFrontByFromSizeAsCount(
        Array<T>& p_subArray, const Size& p_numberOfItems
    )
    {
        ValidateArray(p_subArray);
        Assert(
            p_numberOfItems <= p_subArray.m_Size,
            "Cannot resize array down backward by " << p_numberOfItems
            << " when it's size is only " << p_subArray.m_Size
        );


        p_subArray.m_Size -= p_numberOfItems;
    }

    template<typename T>
    T& GetItemFromIndexFromArray(const Size& p_index, const Array<T>& p_array)
    {
        return p_array[p_index];
    }
    template<typename T>
    Size GetSizeAsLastIndexFromArray(const Array<T>& p_array)
    {
        ValidateArray(p_array);
        Assert(
            !ArrayIsNull(p_array),
            "Cannot get the last index of a null array."
        );
        return p_array.m_Size - 1;
    }

    template<typename T>
    bool ArrayIsNull(const Array<T>& p_array)
    {
        return p_array.m_Location == nullptr || p_array.m_Size == 0;
    }
    template<typename T>
    bool ArrayHasSameContentsAsArray(
        const Array<T>& p_array1, const Array<T>& p_array2
    )
    {

        ValidateArray(p_array1);
        ValidateArray(p_array2);


        if(p_array1.m_Size != p_array2.m_Size)
        {
            return false;
        }

        if(p_array1.m_Location == nullptr || p_array2.m_Location == nullptr)
        {
            return p_array1.m_Location == nullptr && p_array2.m_Location == nullptr;
        }

        for(Size i = 0; i < p_array1.m_Size; ++i)
        {
            if(p_array1[i] != p_array2[i])
            {
                return false;
            }
        }

        return true;

    }

}

#endif //ARRAY__ARRAY_ARRAY_DEFINITION_HPP