#ifndef ARRAY__ARRAY_ARRAY_DECLARATION_HPP
#define ARRAY__ARRAY_ARRAY_DECLARATION_HPP

#include "Meta/Meta.hpp"

/**
 * @brief Quick example
 * 
 */
namespace Library
{

    /**
     * @brief A structure used for storing continuos homogeneous data of fixed
     * sized.
     * 
     * @tparam T 
     */
    template<typename T>
    struct Array;
    template<typename T>
    using ReadOnlyArray = Array<const T>;


    template<typename T>
    void CreateToArrayAsNull(Array<T>& p_array);
    template<typename T>
    void CreateToArrayFromTPointerFromSize(
        Array<T>& p_array, const T*& p_fromLocation, const Size& p_fromSize
    );
    template<typename T>
    void CreateUsingArrayAsSubArrayWithoutBackByFromSizeAsCount(
        Array<T>& p_subArray, const Size& p_numberOfItems
    );
    template<typename T>
    void CreateUsingArrayAsSubArrayWithoutFrontByFromSizeAsCount(
        Array<T>& p_subArray, const Size& p_numberOfItems
    );


    template<typename T>
    T& GetItemFromIndexFromArray(const Size& p_index, const Array<T>& p_array);
    template<typename T>
    Size GetSizeAsLastIndexFromArray(const Array<T>& p_array);

    template<typename T>
    bool ArrayIsNull(const Array<T>& p_nullArray);
    template<typename T>
    bool ArrayHasSameContentsAsArray(
        const Array<T>& p_array1, const Array<T>& p_array2
    );



}

#endif //ARRAY__ARRAY_ARRAY_DECLARATION_HPP