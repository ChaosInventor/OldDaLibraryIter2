#ifndef CIRCULAR_ARRAY_INDEX_RANGE__GLUE_CIRCULAR_ARRAY_INDEX_RANGE_CIRCULAR_ARRAY_INDEX_RANGE_DEFINITION_HPP
#define CIRCULAR_ARRAY_INDEX_RANGE__GLUE_CIRCULAR_ARRAY_INDEX_RANGE_CIRCULAR_ARRAY_INDEX_RANGE_DEFINITION_HPP

#include "CircularArray/CircularArrayDefinition.hpp"
#include "IndexRange/IndexRange.hpp"

namespace Library::Glue
{

    template<typename T>
    void CreateToIndexRangeAsFreeSpaceAfterFrontFromCircularArray(
        IndexRange& p_rangeFromFreeSpace, const CircularArray<T>& p_cArray
    )
    {

        ValidateCircularArray(p_cArray);


        if(CircularArrayIsNullOrFull(p_cArray))
        {
            p_rangeFromFreeSpace = IndexRange();            
            return;
        }

        p_rangeFromFreeSpace.m_LowerIndex = p_cArray.m_Front;

        if(p_cArray.m_Front < p_cArray.m_Back)
        {
            p_rangeFromFreeSpace.m_HigherIndex = p_cArray.m_Back - 1;
        }
        else
        {
            p_rangeFromFreeSpace.m_HigherIndex =
                p_cArray.m_UnderlyingArray.m_Size - 1;
        }

    }
    template<typename T>
    void CreateToIndexRangeAsFreeSpaceBeforeBackFromCircularArray(
        IndexRange& p_rangeFromFreeSpace, const CircularArray<T>& p_cArray
    )
    {

        ValidateCircularArray(p_cArray);


        if(CircularArrayIsNullOrFull(p_cArray))
        {
            p_rangeFromFreeSpace = IndexRange();            
            return;
        }

        if(p_cArray.m_Back != 0)
        {
            p_rangeFromFreeSpace.m_HigherIndex = p_cArray.m_Back;
            
            if(p_cArray.m_Front < p_cArray.m_Back)
            {
                p_rangeFromFreeSpace.m_LowerIndex = p_cArray.m_Front;
            }
            else
            {
                p_rangeFromFreeSpace.m_LowerIndex = 0;
            }
        }
        else
        {
            p_rangeFromFreeSpace.m_HigherIndex =
                p_cArray.m_UnderlyingArray.m_Size - 1;
            p_rangeFromFreeSpace.m_LowerIndex = p_cArray.m_Front;
        }

    }
    template<typename T>
    void CreateToIndexRangeAsFullSpaceBeforeFrontFromCircularArray(
        IndexRange& p_rangeFromFullSpace, const CircularArray<T>& p_cArray
    )
    {
        
        ValidateCircularArray(p_cArray);


        if(CircularArrayIsNullOrEmpty(p_cArray))
        {
            p_rangeFromFullSpace = IndexRange();            
            return;
        }

        if(p_cArray.m_Front != 0)
        {
            p_rangeFromFullSpace.m_HigherIndex = p_cArray.m_Front - 1;
            if(p_cArray.m_Front < p_cArray.m_Back)
            {
                p_rangeFromFullSpace.m_LowerIndex = 0;
            }
            else
            {
                p_rangeFromFullSpace.m_LowerIndex = p_cArray.m_Back;
            }
        }
        else
        {
            p_rangeFromFullSpace.m_HigherIndex =
                p_cArray.m_UnderlyingArray.m_Size - 1;
            p_rangeFromFullSpace.m_LowerIndex = p_cArray.m_Back;
        }

    }
    template<typename T>
    void CreateToIndexRangeAsFullSpaceAfterBackFromCircularArray(
        IndexRange& p_rangeFromFullSpace, const CircularArray<T>& p_cArray
    )
    {
        
        ValidateCircularArray(p_cArray);


        if(CircularArrayIsNullOrEmpty(p_cArray))
        {
            p_rangeFromFullSpace = IndexRange();            
            return;
        }

        p_rangeFromFullSpace.m_LowerIndex = p_cArray.m_Back;
        if(p_cArray.m_Front < p_cArray.m_Back)
        {
            p_rangeFromFullSpace.m_HigherIndex =
                p_cArray.m_UnderlyingArray.m_Size - 1;
        }
        else
        {
            p_rangeFromFullSpace.m_HigherIndex = p_cArray.m_Front - 1;
        }

    }


}

#endif //CIRCULAR_ARRAY_INDEX_RANGE__GLUE_CIRCULAR_ARRAY_INDEX_RANGE_CIRCULAR_ARRAY_INDEX_RANGE_DEFINITION_HPP