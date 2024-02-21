#ifndef CIRCULAR_ARRAY__CIRCULAR_ARRAY_CIRCULAR_ARRAY_DEFINITION_HPP
#define CIRCULAR_ARRAY__CIRCULAR_ARRAY_CIRCULAR_ARRAY_DEFINITION_HPP

#include "Meta/Meta.hpp"
#include "CircularArrayDeclaration.hpp"
#include "Array/ArrayDefinition.hpp"

#define ValidateCircularArray(p_cArray)\
    ValidateArray((p_cArray).m_UnderlyingArray);                                \
    if(ArrayIsNull((p_cArray).m_UnderlyingArray))                               \
    {                                                                           \
        Assert(                                                                 \
            (p_cArray).m_Back == 0,                                             \
            "The back index must be 0 with a null underlying array."            \
        );                                                                      \
        Assert(                                                                 \
            (p_cArray).m_Front == 0,                                            \
            "The front index must be 0 with a null underlying array."           \
        );                                                                      \
    }                                                                           \
    else                                                                        \
    {                                                                           \
        Assert(                                                                 \
            (p_cArray).m_Back < (p_cArray).m_UnderlyingArray.m_Size,            \
            "The back index cannot be " << (p_cArray).m_Back                    \
            << " in a circular array of size "                                  \
            << (p_cArray).m_UnderlyingArray.m_Size << " because it too big, the"\
            " back index must be less than the underlying array's size"         \
        );                                                                      \
        Assert(                                                                 \
            (p_cArray).m_Front <= (p_cArray).m_UnderlyingArray.m_Size,          \
            "The front index cannot be " << (p_cArray).m_Front                  \
            << " in a circular array of size "                                  \
            << (p_cArray).m_UnderlyingArray.m_Size << " because it too big,"    \
            " the front index must be less than or equalled to the underlying " \
            "array's size"                                                      \
        );                                                                      \
    }

#define ValidateIndexInCircularArray(p_index, p_cArray)\
    Assert(                                                                 \
        FindSizeAsFullSpaceFromCircularArray((p_cArray)) < (p_index),       \
        "Index " << (p_index) << " is out of bounds in the given circular " \
        "array."                                                            \
    );


namespace Library
{

    template<typename T>
    struct CircularArray
    {

        Array<T> m_UnderlyingArray;
        Size m_Front;
        Size m_Back;


        CircularArray():
        m_UnderlyingArray(),
        m_Front(0),
        m_Back(0)
        { }
        CircularArray(const CircularArray<T>& p_other):
        m_UnderlyingArray(p_other.m_UnderlyingArray),
        m_Front(p_other.m_Front),
        m_Back(p_other.m_Back)
        { }
        CircularArray(CircularArray<T>&& p_other):
        m_UnderlyingArray(p_other.m_UnderlyingArray),
        m_Front(p_other.m_Front),
        m_Back(p_other.m_Back)
        {
            p_other.m_UnderlyingArray = Array<T>();
            p_other.m_Front = 0;
            p_other.m_Back = 0;
        }

        CircularArray(
            Array<T>& p_underlyingArray, const Size& p_front, const Size& p_back
        ):
        m_UnderlyingArray(p_underlyingArray),
        m_Front(p_front),
        m_Back(p_back)
        { }
        CircularArray(Array<T>& p_underlyingArray):
        m_UnderlyingArray(p_underlyingArray),
        m_Front(0),
        m_Back(0)
        { }



        CircularArray& operator=(const CircularArray<T>& p_other)
        {

            m_UnderlyingArray = p_other.m_UnderlyingArray;
            m_Front = p_other.m_Front;
            m_Back = p_other.m_Back;

            return *this;

        }
        CircularArray& operator=(CircularArray<T>&& p_other)
        {
            
            m_UnderlyingArray = p_other.m_UnderlyingArray;
            m_Front = p_other.m_Front;
            m_Back = p_other.m_Back;

            p_other.m_UnderlyingArray = Array<T>();
            p_other.m_Front = 0;
            p_other.m_Back = 0;

            return *this;

        }

        T& operator[](const Size& p_index)
        {
            return GetItemFromSizeAsIndexFromCircularArray(p_index, *this);
        }

        bool operator==(const CircularArray<T>& p_other)
        {
            return 
                m_UnderlyingArray == p_other.m_UnderlyingArray
                &&
                m_Front == p_other.m_Front
                &&
                m_Back == p_other.m_Back;
        }
        bool operator!=(const CircularArray<T>& p_other)
        {
            return !(*this == p_other);
        }

    };


    //TODO: Some of the create functions use the removed index range array
    //functions. They need to be replaced with the upcoming ArrayIndexRange glue
    //module.

    template<typename T>
    void CreateToCircularArrayAsNull(CircularArray<T>& p_nullCArray)
    {
        p_nullCArray.m_UnderlyingArray.m_Location = nullptr;
        p_nullCArray.m_UnderlyingArray.m_Size = 0;
        p_nullCArray.m_Front = 0;
        p_nullCArray.m_Back = 0;
    }
    template<typename T>
    void CreateToCircularArrayAsEmptyFromArray(
        CircularArray<T>& p_emptyCArray,
        Array<T>& p_withArray
    )
    {

        ValidateArray(p_withArray);
        
        
        p_emptyCArray.m_UnderlyingArray = p_withArray;
        p_emptyCArray.m_Front = 0;
        p_emptyCArray.m_Back = 0;
    
    }
    template<typename T>
    void CreateToCircularArrayAsFullFromArray(
        CircularArray<T>& p_emptyCArray,
        Array<T>& p_withArray
    )
    {

        ValidateArray(p_withArray);


        p_emptyCArray.m_UnderlyingArray = p_withArray;
        p_emptyCArray.m_Front = p_withArray.m_Size;
        p_emptyCArray.m_Back = 0;

    }


    template<typename T>
    T& GetItemFromSizeAsIndexFromCircularArray(
        const Size& p_index, const CircularArray<T>& p_cArray
    )
    {
        ValidateCircularArray(p_cArray);
        ValidateIndexInCircularArray(p_index, p_cArray);
        return p_cArray.m_UnderlyingArray[
            (p_cArray.m_Back + p_index) % p_cArray.m_UnderlyingArray.m_Size
        ];
    }

    template<typename T>
    Size FindSizeAsFullSpaceFromCircularArray(const CircularArray<T>& p_cArray)
    {

        Size l_returnValue = 0;

        //TODO: More elegant implementation.
        if(p_cArray.m_Front == p_cArray.m_UnderlyingArray.m_Size)
        {
            l_returnValue = p_cArray.m_UnderlyingArray.m_Size;
        }
        else if(p_cArray.m_Back < p_cArray.m_Front)
        {
            l_returnValue = p_cArray.m_Front - p_cArray.m_Back;
        }
        else if(p_cArray.m_Back == p_cArray.m_Front)
        {
            l_returnValue = 0;
        }
        else
        {
            l_returnValue += p_cArray.m_UnderlyingArray.m_Size - p_cArray.m_Back;
            l_returnValue += p_cArray.m_Front;
        }

        return l_returnValue;

    }
    template<typename T>
    Size FindSizeAsFreeSpaceFromCircularArray(const CircularArray<T>& p_cArray)
    {
        return
            p_cArray.m_UnderlyingArray.m_Size
            -
            FindSizeAsFullSpaceFromCircularArray(p_cArray);
    }


    template<typename T>
    bool CircularArrayIsNull(const CircularArray<T>& p_nullCArray)
    {
        return ArrayIsNull(p_nullCArray.m_UnderlyingArray);
    }
    template<typename T>
    bool CircularArrayIsNullOrEmpty(const CircularArray<T>& p_emptyOrNullCArray)
    {
        return p_emptyOrNullCArray.m_Back == p_emptyOrNullCArray.m_Front;
    }
    template<typename T>
    bool CircularArrayIsNullOrFull(const CircularArray<T>& p_fullOrNullCArray)
    {
        return p_fullOrNullCArray.m_Front == p_fullOrNullCArray.m_UnderlyingArray.m_Size;
    }
    template<typename T>
    bool CircularArrayIsEmpty(const CircularArray<T>& p_emptyCArray)
    {
        return
            CircularArrayIsNullOrEmpty(p_emptyCArray)
            &&
            !CircularArrayIsNull(p_emptyCArray);
    }
    template<typename T>
    bool CircularArrayIsFull(const CircularArray<T>& p_fullCArray)
    {
        return
            CircularArrayIsNullOrFull(p_fullCArray)
            &&
            !CircularArrayIsNull(p_fullCArray);
    }
    template<typename T>
    bool CircularArrayIsAvailable(const CircularArray<T>& p_availableCArray)
    {
        return p_availableCArray.m_Back != p_availableCArray.m_Front;
    }


    //TODO: Rethink advancing and retreating.

    template<typename T>
    void AdvanceUsingCircularArrayAsFrontFromSizeAsAmount(
        CircularArray<T>& p_cArray, const Size& p_advanceBy
    )
    {
        ValidateCircularArray(p_cArray);
        Assume(p_advanceBy <= FindSizeAsFreeSpaceFromCircularArray(p_cArray));
        p_cArray.m_Front =
            (p_cArray.m_Front + p_advanceBy) % p_cArray.m_UnderlyingArray.m_Size;
        if(p_cArray.m_Front == p_cArray.m_Back)
        {
            p_cArray.m_Front = p_cArray.m_UnderlyingArray.m_Size;
        }
    }
    template<typename T>
    void AdvanceUsingCircularArrayAsBackFromSizeAsAmount(
        CircularArray<T>& p_cArray, const Size& p_advanceBy
    )
    {
        ValidateCircularArray(p_cArray);
        Assume(p_advanceBy <= FindSizeAsFullSpaceFromCircularArray(p_cArray));
        p_cArray.m_Back =
            (p_cArray.m_Back + p_advanceBy) % p_cArray.m_UnderlyingArray.m_Size;
        if(p_cArray.m_Front == p_cArray.m_UnderlyingArray.m_Size)
        {
            p_cArray.m_Front = (p_cArray.m_Back - p_advanceBy) % p_cArray.m_UnderlyingArray.m_Size;
        }
    }
    template<typename T>
    void
    AdvanceToSizeAsAdvancedUsingCircularArrayAsFrontFromSizeAsAmountCallbackOnPartial(
        Size& p_advanced, CircularArray<T>& p_cArray, const Size& p_advanceBy,
        Callback& p_partial
    )
    {

        ValidateCircularArray(p_cArray);
        ValidateCallback(p_partial);


        //Advancing the front index of a circular array means that free space
        //will be converted to full space.
        Size l_freeSpace = FindSizeAsFreeSpaceFromCircularArray(p_cArray);
        if(p_advanceBy > l_freeSpace)
        {
            //p_cArray becomes full now.
            p_cArray.m_Front = p_cArray.m_UnderlyingArray.m_Size;

            p_advanced = l_freeSpace;
            p_partial();
            
            return;
        }

        AdvanceUsingCircularArrayAsFrontFromSizeAsAmount(p_cArray, p_advanceBy);

        p_advanced = p_advanceBy;

    }
    template<typename T>
    void
    AdvanceToSizeAsAdvancedUsingCircularArrayAsBackFromSizeAsAmountCallbackOnPartial(
        Size& p_advanced, CircularArray<T>& p_cArray, const Size& p_advanceBy,
        Callback& p_partial
    )
    {

        ValidateCircularArray(p_cArray);
        ValidateCallback(p_partial);


        //Advancing the back index of a circular array means that full space
        //will be converted to free space.
        Size l_fullSpace = FindSizeAsFullSpaceFromCircularArray(p_cArray);
        if(p_advanceBy > l_fullSpace)
        {
            //p_cArray becomes empty now.
            p_cArray.m_Back = p_cArray.m_Front;
            
            p_advanced = l_fullSpace;
            p_partial();
            
            return;
        }

        AdvanceUsingCircularArrayAsBackFromSizeAsAmount(p_cArray, p_advanceBy);

        p_advanced = p_advanceBy;

    }

    template<typename T>
    void RetreatUsingCircularArrayAsFrontFromSizeAsAmount(
        CircularArray<T>& p_cArray, const Size& p_retreatBy
    )
    {
        ValidateCircularArray(p_cArray);
        Assume(p_retreatBy <= FindSizeAsFullSpaceFromCircularArray(p_cArray));
        if(p_retreatBy == 0)
        {
            return;
        }
        if(p_cArray.m_Front == p_cArray.m_UnderlyingArray.m_Size)
        {
            p_cArray.m_Front = p_cArray.m_Back;
        }
        p_cArray.m_Front =
            (p_cArray.m_Front - p_retreatBy) % p_cArray.m_UnderlyingArray.m_Size;
    }
    template<typename T>
    void RetreatUsingCircularArrayAsBackFromSizeAsAmount(
        CircularArray<T>& p_cArray, const Size& p_retreatBy
    )
    {
        ValidateCircularArray(p_cArray);
        Assume(p_retreatBy <= FindSizeAsFreeSpaceFromCircularArray(p_cArray));
        p_cArray.m_Back =
            (p_cArray.m_Back - p_retreatBy) % p_cArray.m_UnderlyingArray.m_Size;
        if(p_cArray.m_Back == p_cArray.m_Front)
        {
            p_cArray.m_Front = p_cArray.m_UnderlyingArray.m_Size;
        }
    }
    template<typename T>
    void
    RetreatToSizeAsRetreatedUsingCircularArrayAsFrontFromSizeAsAmountCallbackOnPartial(
        Size& p_retreated, CircularArray<T>& p_cArray, const Size& p_retreatBy,
        Callback& p_partial
    )
    {

        ValidateCircularArray(p_cArray);
        ValidateCallback(p_partial);


        //Retreating the front index of a circular arrays means that full space
        //will be converted to free space.
        Size l_fullSpace = FindSizeAsFullSpaceFromCircularArray(p_cArray);
        if(p_retreatBy > l_fullSpace)
        {
            //p_cArray becomes empty now.
            p_cArray.m_Front = p_cArray.m_Back;
            
            p_retreated = l_fullSpace;
            p_partial();
            
            return;
        }

        RetreatUsingCircularArrayAsFrontFromSizeAsAmount(p_cArray, p_retreatBy);

        p_retreated = p_retreatBy;

    }
    template<typename T>
    void
    RetreatToSizeAsRetreatedUsingCircularArrayAsBackFromSizeAsAmountCallbackOnPartial(
        Size& p_retreated, CircularArray<T>& p_cArray, const Size& p_retreatBy,
        Callback& p_partial
    )
    {

        ValidateCircularArray(p_cArray);
        ValidateCallback(p_partial);


        //Retreating the back index of a circular array means that free space
        //will be converted to full space.
        Size l_freeSpace = FindSizeAsFreeSpaceFromCircularArray(p_cArray);
        if(p_retreatBy > l_freeSpace)
        {
            //p_cArray becomes full now.
            p_cArray.m_Front = p_cArray.m_UnderlyingArray.m_Size;

            p_retreated = l_freeSpace;
            p_partial();

            return;
        }

        RetreatUsingCircularArrayAsBackFromSizeAsAmount(p_cArray, p_retreatBy);

        p_retreated = p_retreatBy;

    }


    template<typename T>
    void ReadFromArrayFromCircularArrayAsFront(
        const Array<T>& p_array, const CircularArray<T>& p_cArray
    )
    {

        ValidateArray(p_array);
        ValidateCircularArray(p_cArray);
        Assume(p_array.m_Size <= FindSizeAsFullSpaceFromCircularArray(p_cArray));


        //i is the index in p_cArray;
        //j is the index in p_array
        for(
            Size i = GetSizeAsLastIndexFromCircularArray(p_cArray),
            j = GetSizeAsLastIndexFromArray(p_array);
            j-- > 0;
            --i
        )
        {
            p_array[j] = p_cArray[i];
        }

    }
    template<typename T>
    void ReadFromArrayFromCircularArrayAsBack(
        const Array<T>& p_array, const CircularArray<T>& p_cArray
    )
    {

        ValidateArray(p_array);
        ValidateCircularArray(p_cArray);
        Assume(p_array.m_Size <= FindSizeAsFullSpaceFromCircularArray(p_cArray));


        //Same index is used in both.
        for(Size i = 0; i < p_array.m_Size; ++i)
        {
            p_array[i] = p_cArray[i];
        }

    }
    template<typename T>
    void ReadToSizeAsRedFromArrayFromCircularArrayAsFrontCallbackOnPartial(
        Size& p_red, const Array<T>& p_arrayToRead,
        const CircularArray<T>& p_readFromCArray, Callback& p_partial
    )
    {

        ValidateArray(p_arrayToRead);
        ValidateCircularArray(p_readFromCArray);


        Size l_numOfItemsInCArray =
            FindSizeAsFullSpaceFromCircularArray(p_readFromCArray);

        if(l_numOfItemsInCArray > p_arrayToRead.m_Size)
        {
            p_red = p_arrayToRead.m_Size;
            ReadFromArrayFromCircularArrayAsFront(p_arrayToRead, p_readFromCArray);
        }
        else
        {
            p_red = l_numOfItemsInCArray;
            
            Array<T> l_smallerArrayToReadFrom(
                p_arrayToRead.m_Location, l_numOfItemsInCArray
            );
            ReadFromArrayFromCircularArrayAsFront(
                l_smallerArrayToReadFrom, p_readFromCArray
            );
            
            p_partial();
        }

    }
    template<typename T>
    void ReadToSizeAsRedFromArrayFromCircularArrayAsBackCallbackOnPartial(
        Size& p_red, const Array<T>& p_arrayToRead,
        const CircularArray<T>& p_readFromCArray, Callback& p_partial
    )
    {

        ValidateArray(p_arrayToRead);
        ValidateCircularArray(p_readFromCArray);


        Size l_numOfItemsInCArray =
            FindSizeAsFullSpaceFromCircularArray(p_readFromCArray);

        if(l_numOfItemsInCArray > p_arrayToRead.m_Size)
        {
            p_red = p_arrayToRead.m_Size;
            ReadFromArrayFromCircularArrayAsBack(p_arrayToRead, p_readFromCArray);
        }
        else
        {
            p_red = l_numOfItemsInCArray;
            
            Array<T> l_smallerArrayToRead(
                p_arrayToRead.m_Location, l_numOfItemsInCArray
            );
            ReadFromArrayFromCircularArrayAsBack(
                l_smallerArrayToRead, p_readFromCArray
            );       

            p_partial();
        }

    }

    template<typename T>
    void WriteFromArrayFromCircularArrayAsFront(
        const Array<T>& p_array, const CircularArray<T>& p_cArray
    )
    {

        ValidateArray(p_array);
        ValidateCircularArray(p_cArray);
        Assume(p_array.m_Size <= FindSizeAsFullSpaceFromCircularArray(p_cArray));


        //i is the index in p_cArray;
        //j is the index in p_array
        for(
            Size i = GetSizeAsLastIndexFromCircularArray(p_cArray),
            j = GetSizeAsLastIndexFromArray(p_array);
            j-- > 0;
            --i
        )
        {
            p_cArray[i] = p_array[j];
        }

    }
    template<typename T>
    void WriteFromArrayFromCircularArrayAsBack(
        const Array<T>& p_array, const CircularArray<T>& p_cArray
    )
    {

        ValidateArray(p_array);
        ValidateCircularArray(p_cArray);
        Assume(p_array.m_Size <= FindSizeAsFullSpaceFromCircularArray(p_cArray));


        //Same index is used in both.
        for(Size i = 0; i < p_array.m_Size; ++i)
        {
            p_cArray[i] = p_array[i];
        }

    }
    template<typename T>
    void WriteToSizeAsWrittenFromArrayFromCircularArrayAsFrontCallbackOnPartial(
        Size& p_written, const Array<T>& p_arrayToWrite,
        const CircularArray<T>& p_writeToCArray, Callback& p_partial
    )
    {

        ValidateArray(p_arrayToWrite);
        ValidateCircularArray(p_writeToCArray);


        Size l_numOfItemsInCArray =
            FindSizeAsFullSpaceFromCircularArray(p_writeToCArray);
        
        if(l_numOfItemsInCArray > p_arrayToWrite.m_Size)
        {
            p_written = p_arrayToWrite.m_Size;
            WriteFromArrayFromCircularArrayAsFront(p_arrayToWrite, p_writeToCArray);
        }
        else
        {
            p_written = l_numOfItemsInCArray;

            Array<T> l_smallerArrayToWrite(
                p_arrayToWrite.m_Location, l_numOfItemsInCArray
            );
            WriteFromArrayFromCircularArrayAsFront(
                l_smallerArrayToWrite, p_writeToCArray
            );
            
            p_partial();
        }

    }
    template<typename T>
    void WriteToSizeAsWrittenFromArrayFromCircularArrayAsBackCallbackOnPartial(
        Size& p_written, const Array<T>& p_arrayToWrite,
        const CircularArray<T>& p_writeToCArray, Callback& p_partial
    )
    {

        ValidateArray(p_arrayToWrite);
        ValidateCircularArray(p_writeToCArray);


        Size l_numOfItemsInCArray =
            FindSizeAsFullSpaceFromCircularArray(p_writeToCArray);

        if(l_numOfItemsInCArray > p_arrayToWrite.m_Size)
        {
            p_written = p_arrayToWrite.m_Size;
            WriteFromArrayFromCircularArrayAsBack(p_arrayToWrite, p_writeToCArray);
        }
        else
        {
            p_written = l_numOfItemsInCArray;
            Array<T> l_smallerArrayToWrite(
                p_arrayToWrite.m_Location, l_numOfItemsInCArray
            );
            ReadFromArrayFromCircularArrayAsBack(
                l_smallerArrayToWrite, p_writeToCArray
            );
            p_partial();
        }

    }

    template<typename T>
    void
    CallbackExtractToSizeAsExtractedFromArrayFromCircularArrayAsFrontCallbackOnPartial(
        Callback& p_self
    )
    {

        Assert(p_self.m_State != nullptr, "Data for this callback should never be null");


        void** l_dataPack = (void**)p_self.m_State;

        Size& l_extracted = *(Size*)l_dataPack[0];
        CircularArray<T>& l_extractFromCArray = *(CircularArray<T>*)l_dataPack[1];
        Callback& l_partial = *(Callback*)l_dataPack[2];
        Size& l_toRetreat = *(Size*)l_dataPack[3];

        RetreatUsingCircularArrayAsFrontFromSizeAsAmount(
            l_extractFromCArray, l_extracted
        );
        l_toRetreat = 0;
        l_partial();

    }
    template<typename T>
    void ExtractToSizeAsExtractedFromArrayUsingCircularArrayAsFrontCallbackOnPartial(
        Size& p_extracted, const Array<T>& p_arrayToExtract,
        CircularArray<T>& p_extractFromCArray, Callback& p_partial
    )
    {
        
        //Gets set to 0 if the read function calls l_handlePartial. If however
        //it is not called then the array's size is fine to use.
        Size l_toRetreat = p_arrayToExtract.m_Size;

        void* l_dataForPartialHandle[4];
        l_dataForPartialHandle[0] = &p_extracted;
        l_dataForPartialHandle[1] = &p_extractFromCArray;
        l_dataForPartialHandle[2] = &p_partial;
        l_dataForPartialHandle[3] = &l_toRetreat;

        Callback l_handlePartial(
            l_dataForPartialHandle,
            CallbackExtractToSizeAsExtractedFromArrayFromCircularArrayAsFrontCallbackOnPartial<T>
        );
    
        ReadToSizeAsRedFromArrayFromCircularArrayAsFrontCallbackOnPartial(
            p_extracted, p_arrayToExtract, p_extractFromCArray, l_handlePartial
        );
    
        RetreatUsingCircularArrayAsFrontFromSizeAsAmount(
            p_extractFromCArray, l_toRetreat
        );
    
    }
    template<typename T>
    void
    CallbackExtractToSizeAsExtractedFromArrayFromCircularArrayAsBackCallbackOnPartial(
        Callback& p_self
    )
    {

        Assert(p_self.m_State != nullptr, "Data for this callback should never be null");


        void** l_dataPack = (void**)p_self.m_State;

        Size& l_extracted = *(Size*)l_dataPack[0];
        CircularArray<T>& l_extractFromCArray = *(CircularArray<T>*)l_dataPack[1];
        Callback& l_partial = *(Callback*)l_dataPack[2];
        Size& l_toAdvance = *(Size*)l_dataPack[3];

        AdvanceUsingCircularArrayAsBackFromSizeAsAmount(
            l_extractFromCArray, l_extracted
        );
        l_toAdvance = 0;
        l_partial();

    }
    template<typename T>
    void ExtractToSizeAsExtractedFromArrayUsingCircularArrayAsBackCallbackOnPartial(
        Size& p_extracted, const Array<T>& p_arrayToExtract,
        CircularArray<T>& p_extractFromCArray, Callback& p_partial
    )
    {

        //Gets set to 0 if the read function calls l_handlePartial. If however
        //it is not called then the array's size is fine to use.
        Size l_toAdvance = p_arrayToExtract.m_Size;
        
        void* l_dataForPartialHandle[4];
        l_dataForPartialHandle[0] = &p_extracted;
        l_dataForPartialHandle[1] = &p_extractFromCArray;
        l_dataForPartialHandle[2] = &p_partial;
        l_dataForPartialHandle[3] = &l_toAdvance;

        Callback l_handlePartial(
            l_dataForPartialHandle,
            CallbackExtractToSizeAsExtractedFromArrayFromCircularArrayAsBackCallbackOnPartial<T>
        );

        ReadToSizeAsRedFromArrayFromCircularArrayAsBackCallbackOnPartial(
            p_extracted, p_arrayToExtract, p_extractFromCArray, l_handlePartial
        );
    
        AdvanceUsingCircularArrayAsBackFromSizeAsAmount(
            p_extractFromCArray, l_toAdvance
        );
    
    }

    template<typename T>
    void CallbackInsertToSizeAsInsertedFromArrayUsingCircularArrayAsFrontCallbackOnPartial(
        Callback& p_self
    )
    {

        Assert(p_self.m_State != nullptr, "Data for this callback can never be null");


        void** l_dataPack = (void**)p_self.m_State;

        Size& l_inserted = *(Size*)l_dataPack[0];
        CircularArray<T>& l_insertToCArray = *(CircularArray<T>*)l_dataPack[1];
        Callback& l_partial = *(Callback*)l_dataPack[2];
        Array<T>& l_toWrite = *(Array<T>*)l_dataPack[3];

        l_toWrite.m_Size = l_inserted;
        WriteFromArrayFromCircularArrayAsFront(l_toWrite, l_insertToCArray);
        l_toWrite = Array<T>();
        l_partial();

    }
    template<typename T>
    void InsertToSizeAsInsertedFromArrayUsingCircularArrayAsFrontCallbackOnPartial(
        Size& p_inserted, const Array<T>& p_arrayToInsert,
        CircularArray<T>& p_insertToCArray, Callback& p_partial
    )
    {

        //If the advance function calls l_handlePartial this becomes a null
        //array.
        Array<T> l_toWrite = p_arrayToInsert;

        void* l_dataForPartialHandle[4];
        l_dataForPartialHandle[0] = &p_inserted;
        l_dataForPartialHandle[1] = &p_insertToCArray;
        l_dataForPartialHandle[2] = &p_partial;
        l_dataForPartialHandle[3] = &l_toWrite;

        Callback l_handlePartial(
            l_dataForPartialHandle,
            CallbackInsertToSizeAsInsertedFromArrayUsingCircularArrayAsFrontCallbackOnPartial<T>
        );

        AdvanceToSizeAsAdvancedUsingCircularArrayAsFrontFromSizeAsAmountCallbackOnPartial(
            p_inserted, p_insertToCArray, p_arrayToInsert.m_Size,
            l_handlePartial
        );

        WriteFromArrayFromCircularArrayAsFront(l_toWrite, p_insertToCArray);

    }
    template<typename T>
    void CallbackInsertToSizeAsInsertedFromArrayUsingCircularArrayAsBackCallbackOnPartial(
        Callback& p_self
    )
    {

        Assert(p_self.m_State != nullptr, "Data for this callback can never be null");


        void** l_dataPack = (void**)p_self.m_State;

        Size& l_inserted = *(Size*)l_dataPack[0];
        CircularArray<T>& l_insertToCArray = *(CircularArray<T>*)l_dataPack[1];
        Callback& l_partial = *(Callback*)l_dataPack[2];
        Array<T>& l_toWrite = *(Array<T>*)l_dataPack[3];

        l_toWrite.m_Size = l_inserted;
        WriteFromArrayFromCircularArrayAsBack(l_toWrite, l_insertToCArray);
        l_toWrite = Array<T>();
        l_partial();

    }
    template<typename T>
    void InsertToSizeAsInsertedFromArrayUsingCircularArrayAsBackCallbackOnPartial(
        Size& p_inserted, const Array<T>& p_arrayToInsert,
        CircularArray<T>& p_insertToCArray, Callback& p_partial
    )
    {

        //If the advance function calls l_handlePartial this becomes a null
        //array.
        Array<T> l_toWrite = p_arrayToInsert;

        void* l_dataForPartialHandle[4];
        l_dataForPartialHandle[0] = &p_inserted;
        l_dataForPartialHandle[1] = &p_insertToCArray;
        l_dataForPartialHandle[2] = &p_partial;
        l_dataForPartialHandle[3] = &l_toWrite;

        Callback l_handlePartial(
            l_dataForPartialHandle,
            CallbackInsertToSizeAsInsertedFromArrayUsingCircularArrayAsBackCallbackOnPartial<T>
        );

        RetreatToSizeAsAdvancedUsingCircularArrayAsBackFromSizeAsAmountCallbackOnPartial(
            p_inserted, p_insertToCArray, p_arrayToInsert.m_Size,
            l_handlePartial
        );

        WriteFromArrayFromCircularArrayAsBack(l_toWrite, p_insertToCArray);

    }

}

#endif //CIRCULAR_ARRAY__CIRCULAR_ARRAY_CIRCULAR_ARRAY_DEFINITION_HPP