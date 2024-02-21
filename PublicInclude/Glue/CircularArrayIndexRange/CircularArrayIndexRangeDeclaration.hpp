#ifndef CIRCULAR_ARRAY_INDEX_RANGE__GLUE_CIRCULAR_ARRAY_INDEX_RANGE_CIRCULAR_ARRAY_INDEX_RANGE_DECLARATION_HPP
#define CIRCULAR_ARRAY_INDEX_RANGE__GLUE_CIRCULAR_ARRAY_INDEX_RANGE_CIRCULAR_ARRAY_INDEX_RANGE_DECLARATION_HPP

#include "CircularArray/CircularArrayDeclaration.hpp"
#include "IndexRange/IndexRange.hpp"

namespace Library::Glue
{

    template<typename T>
    void CreateToIndexRangeAsFreeSpaceAfterFrontFromCircularArray(
        IndexRange& p_rangeFromFreeSpace, const CircularArray<T>& p_cArray
    );
    template<typename T>
    void CreateToIndexRangeAsFreeSpaceBeforeBackFromCircularArray(
        IndexRange& p_rangeFromFreeSpace, const CircularArray<T>& p_cArray
    );
    template<typename T>
    void CreateToIndexRangeAsFullSpaceBeforeFrontFromCircularArray(
        IndexRange& p_rangeFromFullSpace, const CircularArray<T>& p_cArray
    );
    template<typename T>
    void CreateToIndexRangeAsFullSpaceAfterBackFromCircularArray(
        IndexRange& p_rangeFromFullSpace, const CircularArray<T>& p_cArray
    );
    

}

#endif //CIRCULAR_ARRAY_INDEX_RANGE__GLUE_CIRCULAR_ARRAY_INDEX_RANGE_CIRCULAR_ARRAY_INDEX_RANGE_DECLARATION_HPP