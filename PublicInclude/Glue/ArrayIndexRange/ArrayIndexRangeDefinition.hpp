#ifndef ARRAY_INDEX_RANGE__GLUE_ARRAY_INDEX_RANGE_ARRAY_INDEX_RANGE_DEFINITION_HPP
#define ARRAY_INDEX_RANGE__GLUE_ARRAY_INDEX_RANGE_ARRAY_INDEX_RANGE_DEFINITION_HPP

#include "ArrayIndexRangeDeclaration.hpp"
#include "Array/ArrayDefinition.hpp"

namespace Library::Glue
{

    template<typename T>
    void CreateToArrayAsSubArrayFromArrayFromIndexRange(
        Array<T>& p_subArray, const Array<T>& p_ofArray,
        const IndexRange& p_rangeOfSubArray
    )
    {

        ValidateArray(p_ofArray);
        ValidateIndexRange(p_rangeOfSubArray);

        Assume(
            FindSizeAsLengthFromIndexRange(p_rangeOfSubArray)
            <=
            p_ofArray.m_Size - p_rangeOfSubArray.m_LowerIndex
        );


        p_subArray.m_Location = p_ofArray.m_Location + p_rangeOfSubArray.m_LowerIndex;
        p_subArray.m_Size = FindSizeAsLengthFromIndexRange(p_rangeOfSubArray);

    }

}


#endif //ARRAY_INDEX_RANGE__GLUE_ARRAY_INDEX_RANGE_ARRAY_INDEX_RANGE_DEFINITION_HPP