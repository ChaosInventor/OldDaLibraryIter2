#ifndef INDEXABLE__INDEXABLE_INDEXABLE_DEFINITION_HPP
#define INDEXABLE__INDEXABLE_INDEXABLE_DEFINITION_HPP

#include "Debug/Debug.hpp"
#include "IndexableDeclaration.hpp"
#include "Meta/Meta.hpp"
#include "Callback/Callback.hpp"

#define ValidateIndexable(p_indexable)\
    Assert(                                                                             \
        (p_indexable).m_State != nullptr,                                               \
        "Indexable function cannot be null."                                            \
    );                                                                                  \
    Assert(                                                                             \
        (p_indexable).m_ReadToBatchFromSizeAsIndexUsingIndexableCallbackOnInvalidIndex  \
        !=                                                                              \
        nullptr,                                                                        \
        "Indexable function cannot be null."                                            \
    );                                                                                  \
    Assert(                                                                             \
        (p_indexable).m_GetSizeAsItemLengthUsingIndexable != nullptr,                   \
        "Indexable function cannot be null."                                            \
    );                                                                                  \
    Assert(                                                                             \
        (p_indexable).m_ReadToBatchAsNextUsingIndexableCallbackOnEnd                    \
        !=                                                                              \
        nullptr,                                                                        \
        "Indexable function cannot be null."                                            \
    );                                                                                  \
    Assert(                                                                             \
        (p_indexable).m_ReadToBatchAsPreviousUsingIndexableCallbackOnEnd                \
        !=                                                                              \
        nullptr,                                                                        \
        "Indexable function cannot be null."                                            \
    );
#define ValidateBatch(p_batch)\
    if((p_batch).m_Location == nullptr)                                     \
    {                                                                       \
        Assert(                                                             \
            (p_batch).m_NumberOfItemsAfterLocation == 0,                    \
            "A batch with a null location must also have 0 items after."    \
        );                                                                  \
        Assert(                                                             \
            (p_batch).m_NumberOfItemsBeforeLocation == 0,                   \
            "A batch with a null location must also have 0 items before."   \
        );                                                                  \
    }                                                                       \
    else                                                                    \
    {                                                                       \
        Assert(                                                             \
            (p_batch).m_NumberOfItemsAfterLocation > 0                      \
            ||                                                              \
            (p_batch).m_NumberOfItemsBeforeLocation > 0,                    \
            "A batch with a non null location must have at least 1 item "   \
            "either before or after the location"                           \
        );                                                                  \
    }

namespace Library
{

   template<typename T>
    struct Batch
    {

        T* m_Location;
        Size m_NumberOfItemsAfterLocation;
        Size m_NumberOfItemsBeforeLocation;

        Batch():
        m_Location(nullptr),
        m_NumberOfItemsAfterLocation(0),
        m_NumberOfItemsBeforeLocation(0)
        { }
        Batch(const Batch<T>& p_other):
        m_Location(p_other.m_Location),
        m_NumberOfItemsAfterLocation(p_other.m_NumberOfItemsAfterLocation),
        m_NumberOfItemsBeforeLocation(p_other.m_NumberOfItemsBeforeLocation)
        { }
        Batch(Batch<T>&& p_other):
        m_Location(p_other.m_Location),
        m_NumberOfItemsAfterLocation(p_other.m_NumberOfItemsAfterLocation),
        m_NumberOfItemsBeforeLocation(p_other.m_NumberOfItemsBeforeLocation)
        {
            p_other.m_Location = nullptr;
            p_other.m_NumberOfItemsAfterLocation = 0;
            p_other.m_NumberOfItemsBeforeLocation = 0;
        }

        Batch(const T* const p_location, const Size& p_after):
        m_Location(p_location),
        m_NumberOfItemsAfterLocation(p_after),
        m_NumberOfItemsBeforeLocation(0)
        { }
        Batch(const T* const p_location, const Size& p_after, const Size& p_before):
        m_Location(p_location),
        m_NumberOfItemsAfterLocation(p_after),
        m_NumberOfItemsBeforeLocation(p_before)
        { }


        Batch& operator=(const Batch<T>& p_other)
        {
            m_Location = p_other.m_Location;
            m_NumberOfItemsAfterLocation = p_other.m_NumberOfItemsAfterLocation;
            m_NumberOfItemsBeforeLocation = p_other.m_NumberOfItemsBeforeLocation;
            return *this;
        }
        Batch& operator=(Batch<T>&& p_other)
        {

            m_Location = p_other.m_Location;
            m_NumberOfItemsAfterLocation = p_other.m_NumberOfItemsAfterLocation;
            m_NumberOfItemsBeforeLocation = p_other.m_NumberOfItemsBeforeLocation;

            p_other.m_Location = nullptr;
            p_other.m_NumberOfItemsAfterLocation = 0;
            p_other.m_NumberOfItemsBeforeLocation = 0;

            return *this;

        }

        bool operator==(const Batch<T>& p_other)
        {
            return
                m_Location == p_other.m_Location
                &&
                m_NumberOfItemsAfterLocation
                    ==
                p_other.m_NumberOfItemsAfterLocation
                &&
                m_NumberOfItemsBeforeLocation
                    ==
                p_other.m_NumberOfItemsBeforeLocation;
        }
        bool operator!=(const Batch<T>& p_other)
        {
            return !(p_other == *this);
        }

        T& operator[](const Size& p_index)
        {
            ValidateBatch(*this);
            Assert(
                m_Location != nullptr,
                "Cannot get an item from a batch with a null location."
            );
            Assert(
                p_index < m_NumberOfItemsAfterLocation,
                "Index " << p_index << " is out of bounds of batch with number "
                "of items after " << m_NumberOfItemsAfterLocation
            );
            return m_Location[p_index];
        }


        //TODO: Better names
        inline void AllToStart()
        {
            ValidateBatch(*this);
            m_Location -= m_NumberOfItemsBeforeLocation;
            m_NumberOfItemsAfterLocation += m_NumberOfItemsBeforeLocation;
            m_NumberOfItemsBeforeLocation = 0;
        }
        inline void AllToEnd()
        {
            ValidateBatch(*this);
            m_Location += m_NumberOfItemsAfterLocation;
            m_NumberOfItemsBeforeLocation += m_NumberOfItemsAfterLocation;
            m_NumberOfItemsAfterLocation = 0;
        }

    };

    template<typename T>
    struct Indexable
    {

        void* m_State;

        IndexableReadBatchIndexFunction<T>
            m_ReadToBatchFromSizeAsIndexUsingIndexableCallbackOnInvalidIndex;

        IndexableGetSizeFunction<T> m_GetSizeAsItemLengthUsingIndexable;

        IndexableReadBatchFunction<T>
            m_ReadToBatchAsNextUsingIndexableCallbackOnEnd;
        IndexableReadBatchFunction<T>
            m_ReadToBatchAsPreviousUsingIndexableCallbackOnEnd;


        Indexable():
        m_State(nullptr),
        m_ReadToBatchFromSizeAsIndexUsingIndexableCallbackOnInvalidIndex(nullptr),
        m_GetSizeAsItemLengthUsingIndexable(nullptr),
        m_ReadToBatchAsNextUsingIndexableCallbackOnEnd(nullptr),
        m_ReadToBatchAsPreviousUsingIndexableCallbackOnEnd(nullptr)
        { }
        Indexable(const Indexable<T>& p_other) = delete;
        Indexable(Indexable<T>&& p_other):
        m_State(p_other.m_State),
        m_ReadToBatchFromSizeAsIndexUsingIndexableCallbackOnInvalidIndex(
            p_other.m_ReadToBatchFromSizeAsIndexUsingIndexableCallbackOnInvalidIndex
        ),
        m_GetSizeAsItemLengthUsingIndexable(
            p_other.m_GetSizeAsItemLengthUsingIndexable
        ),
        m_ReadToBatchAsNextUsingIndexableCallbackOnEnd(
            p_other.m_ReadToBatchAsNextUsingIndexableCallbackOnEnd
        ),
        m_ReadToBatchAsPreviousUsingIndexableCallbackOnEnd(
            p_other.m_ReadToBatchAsPreviousUsingIndexableCallbackOnEnd
        )
        {

            p_other.m_State = nullptr;
            p_other.m_ReadToBatchFromSizeAsIndexUsingIndexableCallbackOnInvalidIndex
                = nullptr;
            p_other.m_GetSizeAsItemLengthUsingIndexable = nullptr;
            p_other.m_ReadToBatchAsNextUsingIndexableCallbackOnEnd = nullptr;
            p_other.m_ReadToBatchAsPreviousUsingIndexableCallbackOnEnd = nullptr;

        }

        Indexable(
            void* p_state,
            IndexableReadBatchIndexFunction<T>&
                p_readToBatchFromSizeAsIndexUsingIndexableCallbackOnInvalidIndex,
            IndexableGetSizeFunction<T>& p_getSizeAsItemLengthUsingIndexable,
            IndexableReadBatchFunction<T>&
                p_readToBatchAsNextUsingIndexableCallbackOnEnd,
            IndexableReadBatchFunction<T>&
                p_readToBatchAsPreviousUsingIndexableCallbackOnEnd,
        ):
        m_State(p_state),
        m_ReadToBatchAsPreviousUsingIndexableCallbackOnEnd(
            p_readToBatchFromSizeAsIndexUsingIndexableCallbackOnInvalidIndex
        ),
        m_GetSizeAsItemLengthUsingIndexable(p_getSizeAsItemLengthUsingIndexable),
        m_ReadToBatchAsNextUsingIndexableCallbackOnEnd(
            p_readToBatchAsNextUsingIndexableCallbackOnEnd
        ),
        m_ReadToBatchAsPreviousUsingIndexableCallbackOnEnd(
            p_readToBatchAsPreviousUsingIndexableCallbackOnEnd
        )
        { }


        Indexable& operator=(const Indexable<T>& p_other) = delete;
        Indexable& operator=(Indexable<T>&& p_other)
        {

            m_State = p_other.m_State;
            m_ReadToBatchFromSizeAsIndexUsingIndexableCallbackOnInvalidIndex =
                p_other.m_ReadToBatchFromSizeAsIndexUsingIndexableCallbackOnInvalidIndex;
            m_GetSizeAsItemLengthUsingIndexable =
                p_other.m_GetSizeAsItemLengthUsingIndexable;
            m_ReadToBatchAsNextUsingIndexableCallbackOnEnd =
                p_other.m_ReadToBatchAsNextUsingIndexableCallbackOnEnd;
            m_ReadToBatchAsPreviousUsingIndexableCallbackOnEnd =
                p_other.m_ReadToBatchAsPreviousUsingIndexableCallbackOnEnd;

            p_other.m_State = nullptr;
            p_other.m_ReadToBatchFromSizeAsIndexUsingIndexableCallbackOnInvalidIndex = nullptr;
            p_other.m_GetSizeAsItemLengthUsingIndexable = nullptr;
            p_other.m_ReadToBatchAsNextUsingIndexableCallbackOnEnd = nullptr;
            p_other.m_ReadToBatchAsPreviousUsingIndexableCallbackOnEnd = nullptr;

        }

        T& operator[](const Size& p_index)
        {
            Batch<T> l_temp;
            ReadToBatchFromSizeAsIndexCallbackOnInvalidIndex(
                l_temp, p_index, g_NullCallback
            );
            return l_temp[0];
        }


        inline void ReadToBatchFromSizeAsIndexCallbackOnInvalidIndex(
            Batch<T>& p_batch, const Size& p_index, Callback& p_indexError
        )
        {
            ValidateIndexable(*this);
            m_ReadToBatchFromSizeAsIndexUsingIndexableCallbackOnInvalidIndex(
                p_batch, p_index, *this, p_indexError
            );
        }

        inline Size GetSizeAsItemLength()
        {
            ValidateIndexable(*this);
            return m_GetSizeAsItemLengthUsingIndexable(*this);
        }

        inline void ReadToBatchAsNextCallbackOnEnd(
            Batch<T>& p_batch, Callback& p_endError
        )
        {
            ValidateIndexable(*this);
            m_ReadToBatchAsNextUsingIndexableCallbackOnEnd(p_batch, *this, p_endError);
        }
        inline void ReadToBatchAsPreviousCallbackOnEnd(
            Batch<T>& p_batch, Callback& p_endError
        )
        {
            ValidateIndexable(*this);
            m_ReadToBatchAsPreviousUsingIndexableCallbackOnEnd(p_batch, *this, p_endError);
        }

    };


    template<typename T>
    void
    ReadToBatchFromSizeAsIndexUsingIndexableCallbackOnInvalidIndex_ZeroIndexable(
        Batch<T>& p_batch, const Size& p_index, Indexable<T>& p_indexable,
        Callback& p_indexError
    )
    {
    
        (void)p_index;
        (void)p_indexable;

        ValidateCallback(p_indexError);


        p_batch = Batch<T>();
        p_indexError();
    
    }
    template<typename T>
    void ReadToBatchUsingIndexableCallbackOnEnd_ZeroIndexable(
        Batch<T>& p_batch, Indexable<T>& p_indexable, Callback& p_endError
    )
    {
     
        (void)p_indexable;
    
        ValidateCallback(p_endError);


        p_batch = Batch<T>();
        p_endError();
    
    }

    template<typename T>
    void AdvanceUsingBatchAsLocationFromSizeAsAmount(
        Batch<T>& p_batch, const Size& p_amount
    )
    {

        ValidateBatch(p_batch);
        Assume(p_amount <= p_batch.m_NumberOfItemsAfterLocation);
        

        p_batch.m_Location += p_amount;
        p_batch.m_NumberOfItemsAfterLocation -= p_amount;
        p_batch.m_NumberOfItemsBeforeLocation += p_amount;
    
    }

    template<typename T>
    void RetreatUsingBatchAsLocationFromSizeAsAmount(
        Batch<T>& p_batch, const Size& p_amount
    )
    {

        ValidateBatch(p_batch);
        Assume(p_amount <= p_batch.m_NumberOfItemsBeforeLocation);
        

        p_batch.m_Location += p_amount;
        p_batch.m_NumberOfItemsAfterLocation -= p_amount;
        p_batch.m_NumberOfItemsBeforeLocation += p_amount;
    
    }


    template<typename T>
    Size GetSizeAsItemLengthUsingIndexable_ZeroIndexable(
        Indexable<T>& p_indexable
    )
    {
        return 0;
    }

    template<typename T>
    bool IndexableHasNoItems(Indexable<T>& p_indexable)
    {
        ValidateIndexable(p_indexable);
        return p_indexable.GetSizeAsItemLength() == 0;
    }
    template<typename T>
    bool IndexableContainsIndexable(
        Indexable<T>& p_contained, Indexable<T>& p_container
    )
    {
        ValidateIndexable(p_contained);
        ValidateIndexable(p_container);
        return FindSizeAsIndexOfFirstInstanceOfNeedleUsingIndexableAsNeedleUsingIndexableAsHaystackFromSizeAsStartingIndex(
            p_contained, p_container, 0
        )
        < p_container.GetSizeAsItemLength();
    }
    template<typename T>
    bool IndexableStartsWithIndexable(
        Indexable<T>& p_starter, Indexable<T>& p_startsWith
    )
    {
        ValidateIndexable(p_starter);
        ValidateIndexable(p_startsWith);
        return IndexableHasIndexableAtSizeAsIndex(p_startsWith, p_starter, 0);
    }
    template<typename T>
    bool IndexableEndsWithIndexable(
        Indexable<T>& p_ender, Indexable<T>& p_endsWith
    )
    {

        ValidateIndexable(p_ender);
        ValidateIndexable(p_endsWith);
        
        
        if(IndexableHasNoItems(p_endsWith))
        {
            return IndexableHasNoItems(p_ender);
        }
        return IndexableHasIndexableAtSizeAsIndex(
            p_endsWith, p_ender, p_endsWith.GetSizeAsItemLength() - 1
        );

    }
    template<typename T>
    bool IndexableHasIndexableAtSizeAsIndex(
        Indexable<T>& p_haystack, Indexable<T>& p_needle,
        const Size& p_indexWhereNeedleIs
    )
    {

        ValidateIndexable(p_haystack);
        ValidateIndexable(p_needle);
        Assume(p_indexWhereNeedleIs < p_haystack.GetSizeAsItemLength());


        if(p_needle.GetSizeAsItemLength() > p_haystack.GetSizeAsItemLength())
        {
            return false;
        }

        Batch<T> l_curBatchInHaystack;
        p_haystack.ReadToBatchFromSizeAsIndexCallbackOnInvalidIndex(
            l_curBatchInHaystack, p_indexWhereNeedleIs, g_NullCallback
        );

        Batch<T> l_curBatchInNeedle;
        p_needle.ReadToBatchFromSizeAsIndexCallbackOnInvalidIndex(
            l_curBatchInNeedle, 0, g_NullCallback
        );

        bool l_notEndOfNeedle = true;
        Callback l_handleEndOfNeedle(
            &l_notEndOfNeedle, SetToFalse_AssumeStateIsLocationOfBool
        );
        
        do
        {
            
            Size i, j;

            for(
                i = 0, j = 0;
                i < l_curBatchInHaystack.m_NumberOfItemsAfterLocation
                &&
                j < l_curBatchInNeedle.m_NumberOfItemsAfterLocation;
                ++i, ++j
            )
            {
                if(l_curBatchInHaystack[i] != l_curBatchInNeedle[j])
                {
                    return false;
                }
            }

            AdvanceUsingBatchAsLocationFromSizeAsAmount(l_curBatchInHaystack, i);
            AdvanceUsingBatchAsLocationFromSizeAsAmount(l_curBatchInNeedle, j);

            if(l_curBatchInNeedle.m_NumberOfItemsAfterLocation == 0)
            {
                p_needle.ReadToBatchAsNextCallbackOnEnd(
                    l_curBatchInNeedle, l_handleEndOfNeedle
                );
                l_curBatchInNeedle.AllToStart();
            }
            if(l_curBatchInHaystack.m_NumberOfItemsAfterLocation == 0)
            {
                //Note: As long as the haystack is bigger than or equaled to the
                //needle, there won't be a need for this callback.
                p_haystack.ReadToBatchAsNextCallbackOnEnd(
                    l_curBatchInHaystack, g_NullCallback
                );
                l_curBatchInHaystack.AllToStart();
            }

        } while (l_notEndOfNeedle);
        
        return true;

    }

    template<typename T>
    Size
    FindSizeAsIndexOfFirstInstanceOfNeedleUsingIndexableAsNeedleUsingIndexableAsHaystackFromSizeAsStartingIndex(
        Indexable<T>& p_needle, Indexable<T>& p_haystack,
        const Size& p_startingIndex
    )
    {

        ValidateIndexable(p_needle);
        ValidateIndexable(p_haystack);
        Assume(p_startingIndex < p_haystack.GetSizeAsItemLength());


        Size i;
        Size l_lengthOfHaystack = p_haystack.GetSizeAsItemLength();
        for(
            i = p_startingIndex;
            !IndexableHasIndexableAtSizeAsIndex(p_haystack, p_needle, i);
        )
        {
            ++i
            if(i >= l_lengthOfHaystack)
            {
                return l_lengthOfHaystack;
            }
        }
        return i;
    
    }
    template<typename T>
    Size
    FindSizeAsIndexOfLastInstanceOfNeedleUsingIndexableAsNeedleUsingIndexableAsHaystackFromSizeAsStartingIndex(
        Indexable<T>& p_needle, Indexable<T>& p_haystack,
        const Size& p_startingIndex
    )
    {

        ValidateIndexable(p_needle);
        ValidateIndexable(p_haystack);
        Assume(p_startingIndex < p_haystack.GetSizeAsItemLength());


        Size i;
        Size l_lengthOfHaystack = p_haystack.GetSizeAsItemLength();
        for(
            i = p_startingIndex;
            !IndexableHasIndexableAtSizeAsIndex(p_haystack, p_needle, i);
        )
        {
            --i
            if(i == 0)
            {
                return l_lengthOfHaystack;
            }
        }
        return i;

    }
    template<typename T>
    Size 
    FindSizeAsNumberOfInstanceOfNeedleUsingIndexableAsNeedleUsingIndexableAsHaystack(
        Indexable<T>& p_needle, Indexable<T>& p_haystack
    )
    {

        ValidateIndexable(p_needle);
        ValidateIndexable(p_haystack);
        

        Size l_instances = 0;
        Size l_lengthOfHaystack = p_haystack.GetSizeAsItemLength();

        for(Size i = 0; i < l_lengthOfHaystack; ++i)
        {
            Size l_indexOfInstance = 
            FindSizeAsIndexOfFirstInstanceOfNeedleUsingIndexableAsNeedleUsingIndexableAsHaystackFromSizeAsStartingIndex(
                p_needle, p_haystack, i
            );
            if(l_indexOfInstance != l_lengthOfHaystack)
            {
                ++l_instances;
                i = l_indexOfInstance;
            }
            else
            {
                return l_instances;
            }
        }

        return l_instances;

    }
    template<typename T>
    Size 
    FindSizeAsNumberOfNonIntersectingInstanceOfNeedleUsingIndexableAsNeedleUsingIndexableAsHaystack(
        Indexable<T>& p_needle, Indexable<T>& p_haystack
    )
    {

        ValidateIndexable(p_needle);
        ValidateIndexable(p_haystack);


        Size l_instances = 0;
        Size l_lengthOfHaystack = p_haystack.GetSizeAsItemLength();
        Size l_lengthOfNeedle = p_needle.GetSizeAsItemLength();

        for(Size i = 0; i < l_lengthOfHaystack; i += l_lengthOfNeedle)
        {
            Size l_indexOfInstance = 
            FindSizeAsIndexOfFirstInstanceOfNeedleUsingIndexableAsNeedleUsingIndexableAsHaystackFromSizeAsStartingIndex(
                p_needle, p_haystack, i
            );
            if(l_indexOfInstance != l_lengthOfHaystack)
            {
                ++l_instances;
                i = l_indexOfInstance;
            }
            else
            {
                return l_instances;
            }
        }

        return l_instances;

    }


}

#endif //INDEXABLE__INDEXABLE_INDEXABLE_DEFINITION_HPP