#ifndef DYNAMIC_ARRAY__DYNAMIC_ARRAY_DYNAMIC_ARRAY_DECLARATION_HPP
#define DYNAMIC_ARRAY__DYNAMIC_ARRAY_DYNAMIC_ARRAY_DECLARATION_HPP

namespace Library
{
 
    template<typename T>
    struct DynamicArray;


    template<typename T>
    bool DynamicArrayIsNull(const DynamicArray<T>& p_dArray);
    template<typename T>
    bool DynamicArrayIsEmpty(const DynamicArray<T>& p_dArray);

}

#endif //DYNAMIC_ARRAY__DYNAMIC_ARRAY_DYNAMIC_ARRAY_DECLARATION_HPP