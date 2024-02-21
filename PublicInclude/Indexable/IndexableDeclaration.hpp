#ifndef INDEXABLE__INDEXABLE_INDEXABLE_DECLARATION_HPP
#define INDEXABLE__INDEXABLE_INDEXABLE_DECLARATION_HPP

#include "Meta/Meta.hpp"
#include "Callback/Callback.hpp"

namespace Library
{

    template<typename T>
    struct Batch;

    template<typename T>
    struct Indexable;


    template<typename T>
    using IndexableReadBatchIndexFunction = void (*) (
        Batch<T>& p_batch, const Size& p_index, Indexable<T>& p_indexable,
        Callback& p_indexError
    );
    template<typename T>
    using IndexableGetSizeFunction = Size (*) (Indexable<T>& p_indexable);
    template<typename T>
    using IndexableReadBatchFunction = void (*) (
        Batch<T>& p_batch, Indexable<T>& p_indexable, Callback& p_endError
    );


    template<typename T>
    void
    ReadToBatchFromSizeAsIndexUsingIndexableCallbackOnInvalidIndex_ZeroIndexable(
        Batch<T>& p_batch, const Size& p_index, Indexable<T>& p_indexable,
        Callback& p_indexError
    );
    template<typename T>
    void ReadToBatchUsingIndexableCallbackOnEnd_ZeroIndexable(
        Batch<T>& p_batch, Indexable<T>& p_indexable, Callback& p_endError
    );

    template<typename T>
    void AdvanceUsingBatchAsLocationFromSizeAsAmount(
        Batch<T>& p_batch, const Size& p_amount
    );

    template<typename T>
    void RetreatUsingBatchAsLocationFromSizeAsAmount(
        Batch<T>& p_batch, const Size& p_amount
    );


    template<typename T>
    Size GetSizeAsItemLengthUsingIndexable_ZeroIndexable(
        Indexable<T>& p_indexable
    );

    template<typename T>
    bool IndexableHasNoItems(Indexable<T>& p_indexable);
    template<typename T>
    bool IndexableContainsIndexable(
        Indexable<T>& p_needle, Indexable<T>& p_haystack
    );
    template<typename T>
    bool IndexableStartsWithIndexable(
        Indexable<T>& p_starter, Indexable<T>& p_startsWith
    );
    template<typename T>
    bool IndexableEndsWithIndexable(
        Indexable<T>& p_ender, Indexable<T>& p_endsWith
    );
    template<typename T>
    bool IndexableHasIndexableAtSizeAsIndex(
        Indexable<T>& p_haystack, Indexable<T>& p_needle,
        const Size& p_indexWhereNeedleIs
    );

    template<typename T>
    Size
    FindSizeAsIndexOfFirstInstanceOfNeedleUsingIndexableAsNeedleUsingIndexableAsHaystackFromSizeAsStartingIndex(
        Indexable<T>& p_needle, Indexable<T>& p_haystack,
        const Size& p_startingIndex
    );
    template<typename T>
    Size
    FindSizeAsIndexOfLastInstanceOfNeedleUsingIndexableAsNeedleUsingIndexableAsHaystackFromSizeAsStartingIndex(
        Indexable<T>& p_needle, Indexable<T>& p_haystack,
        const Size& p_startingIndex
    );
    template<typename T>
    Size 
    FindSizeAsNumberOfInstanceOfNeedleUsingIndexableAsNeedleUsingIndexableAsHaystack(
        Indexable<T>& p_needle, Indexable<T>& p_haystack
    );
    template<typename T>
    Size 
    FindSizeAsNumberOfNonIntersectingInstanceOfNeedleUsingIndexableAsNeedleUsingIndexableAsHaystack(
        Indexable<T>& p_needle, Indexable<T>& p_haystack
    );

}

#endif //INDEXABLE__INDEXABLE_INDEXABLE_DECLARATION_HPP