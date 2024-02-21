#ifndef INDEX_RANGE__INDEX_RANGE_INDEX_RANGE_HPP
#define INDEX_RANGE__INDEX_RANGE_INDEX_RANGE_HPP

#include "Meta/Meta.hpp"

#define ValidateIndexRange(p_range)\
    Assert(                                                                     \
        (p_range).m_LowerIndex <= (p_range).m_HigherIndex,                      \
        "Index range cannot have a it's lower index be greater than it's higher"\
        " index."                                                               \
    );                                                                          \
    Assert(                                                                     \
        (p_range).m_HigherIndex < SIZE_MAXIMUM, "Index range cannot have it's "     \
        "higher index be SIZE_MAXIMUM."                                             \
    );


namespace Library
{

    struct IndexRange
    {

        Size m_LowerIndex;
        Size m_HigherIndex;


        IndexRange():
        m_LowerIndex(0),
        m_HigherIndex(0)
        { }
        IndexRange(const IndexRange& p_other):
        m_LowerIndex(p_other.m_LowerIndex),
        m_HigherIndex(p_other.m_HigherIndex)
        { }
        IndexRange(IndexRange&& p_other):
        m_LowerIndex(p_other.m_LowerIndex),
        m_HigherIndex(p_other.m_HigherIndex)
        {
            p_other.m_LowerIndex = 0;
            p_other.m_HigherIndex = 0;
        }

        IndexRange(const Size& p_lower, const Size& p_higher):
        m_LowerIndex(p_lower),
        m_HigherIndex(p_higher)
        { }


        IndexRange& operator=(const IndexRange& p_other)
        {
            m_LowerIndex = p_other.m_LowerIndex;
            m_HigherIndex = p_other.m_HigherIndex;
            return *this;
        }
        IndexRange& operator=(IndexRange&& p_other)
        {

            m_LowerIndex = p_other.m_LowerIndex;
            m_HigherIndex = p_other.m_HigherIndex;

            p_other.m_LowerIndex = 0;
            p_other.m_HigherIndex = 0;

            return *this;

        }

        bool operator==(const IndexRange& p_other)
        {
            return
                m_LowerIndex == p_other.m_LowerIndex
                &&
                m_HigherIndex == p_other.m_HigherIndex;
        }
        bool operator!=(const IndexRange& p_other)
        {
            return !(*this == p_other);
        }

    };


    void CreateToIndexRangeFromSizeAsLowerFromSizeAsLength(
        IndexRange& p_range, const Size& p_lowerIndex,
        const Size& p_lengthOfRange
    );
    void CreateToIndexRangeFromSizeAsHigherFromSizeAsLength(
        IndexRange& p_range, const Size& p_higherIndex,
        const Size& p_lengthOfRange
    );
    void CreateToIndexRangeAsUnionFromIndexRangeFromIndexRange(
        IndexRange& p_range, const IndexRange& p_range1,
        const IndexRange& p_range2
    );
    void CreateToIndexRangeAsIntersectionFromIndexRangeFromIndexRange(
        IndexRange& p_range, const IndexRange& p_range1,
        const IndexRange& p_range2
    );


    Size FindSizeAsLengthFromIndexRange(const IndexRange& p_range);

}

#endif //INDEX_RANGE__INDEX_RANGE_INDEX_RANGE_HPP