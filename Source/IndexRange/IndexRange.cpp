#include "IndexRange/IndexRange.hpp"
#include "Debug/Debug.hpp"
#include "Arithmetic/Arithmetic.hpp"

namespace Library
{

    void CreateToIndexRangeFromSizeAsLowerFromSizeAsLength(
        IndexRange& p_range, const Size& p_lowerIndex,
        const Size& p_lengthOfRange
    )
    {

        Assert(
            p_lengthOfRange > 0, "Cannot create an index range with 0 length."
        );
        Check(
            p_lowerIndex + (p_lengthOfRange - 1) >= p_lowerIndex,
            "This function assumes that the caller will handle the case for "
            "overflow."
        );


        p_range.m_LowerIndex = p_lowerIndex;
        p_range.m_HigherIndex = p_lowerIndex + (p_lengthOfRange - 1);
        
    }
    void CreateToIndexRangeFromSizeAsHigherFromSizeAsLength(
        IndexRange& p_range, const Size& p_higherIndex,
        const Size& p_lengthOfRange
    )
    {

        Assert(
            p_lengthOfRange > 0, "Cannot create an index range with 0 length."
        );
        Check(
            p_higherIndex - (p_lengthOfRange - 1) <= p_higherIndex,
            "This function assumes that the caller will handle the case for "
            "overflow."
        );


        p_range.m_HigherIndex = p_higherIndex;
        p_range.m_LowerIndex = p_higherIndex - (p_lengthOfRange - 1);
        
    }
    void CreateToIndexRangeAsUnionFromIndexRangeFromIndexRange(
        IndexRange& p_range, const IndexRange& p_range1,
        const IndexRange& p_range2
    )
    {

        ValidateIndexRange(p_range1);
        ValidateIndexRange(p_range2);


        p_range.m_LowerIndex = Min(
            p_range1.m_LowerIndex, p_range2.m_LowerIndex
        );
        p_range.m_HigherIndex = Max(
            p_range1.m_HigherIndex, p_range2.m_HigherIndex
        );
    
    }
    void CreateToIndexRangeAsIntersectionFromIndexRangeFromIndexRange(
        IndexRange& p_range, const IndexRange& p_range1,
        const IndexRange& p_range2
    )
    {

        ValidateIndexRange(p_range1);
        ValidateIndexRange(p_range2);


        p_range.m_LowerIndex = 0;
        p_range.m_HigherIndex = 0;

        Size l_smallestLow = Min(p_range1.m_LowerIndex, p_range2.m_LowerIndex);        
        Size l_smallestHigh = Min(p_range1.m_HigherIndex, p_range2.m_HigherIndex);
        
        Size l_biggestLow = Max(p_range1.m_LowerIndex, p_range2.m_LowerIndex);        

        //In both these cases there isn't an intersection.
        if(l_smallestLow > l_smallestHigh)
        {
            return;
        }
        if(l_biggestLow > l_smallestHigh)
        {
            return;
        }
        
        p_range.m_LowerIndex = l_biggestLow;
        p_range.m_HigherIndex = l_smallestHigh;


    }


    Size FindSizeAsLengthFromIndexRange(const IndexRange& p_range)
    {

        ValidateIndexRange(p_range);


        if(p_range.m_LowerIndex == 0)
        {
            return p_range.m_HigherIndex + 1;
        }
        return p_range.m_HigherIndex - (p_range.m_LowerIndex - 1);

    }

}
