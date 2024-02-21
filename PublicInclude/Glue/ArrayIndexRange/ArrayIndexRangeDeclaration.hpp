#ifndef ARRAY_INDEX_RANGE__GLUE_ARRAY_INDEX_RANGE_ARRAY_INDEX_RANGE_DECLARATION_HPP
#define ARRAY_INDEX_RANGE__GLUE_ARRAY_INDEX_RANGE_ARRAY_INDEX_RANGE_DECLARATION_HPP

#include "Array/ArrayDeclaration.hpp"
#include "IndexRange/IndexRange.hpp"

namespace Library::Glue
{

    template<typename T>
    void CreateToArrayAsSubArrayFromArrayFromIndexRange(
        Array<T>& p_subArray, const Array<T>& p_ofArray,
        const IndexRange& p_rangeOfSubArray
    );

}


#endif //ARRAY_INDEX_RANGE__GLUE_ARRAY_INDEX_RANGE_ARRAY_INDEX_RANGE_DECLARATION_HPP