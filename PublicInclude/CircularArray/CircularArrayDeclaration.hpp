#ifndef CIRCULAR_ARRAY__CIRCULAR_ARRAY_CIRCULAR_ARRAY_DECLARATION_HPP
#define CIRCULAR_ARRAY__CIRCULAR_ARRAY_CIRCULAR_ARRAY_DECLARATION_HPP

#include "Meta/Meta.hpp"
#include "Array/ArrayDeclaration.hpp"
#include "Callback/Callback.hpp"

namespace Library
{

    template<typename T>
    struct CircularArray;


    template<typename T>
    void CreateToCircularArrayAsNull(CircularArray<T>& p_nullCArray);
    template<typename T>
    void CreateToCircularArrayAsEmptyFromArray(
        CircularArray<T>& p_emptyCArray,
        Array<T>& p_withArray
    );
    template<typename T>
    void CreateToCircularArrayAsFullFromArray(
        CircularArray<T>& p_emptyCArray,
        Array<T>& p_withArray
    );


    template<typename T>
    T& GetItemFromSizeAsIndexFromCircularArray(
        const Size& p_index, const CircularArray<T>& p_cArray
    );
    template<typename T>
    Size GetSizeAsLastIndexFromCircularArray(const CircularArray<T>& p_cArray);

    template<typename T>
    Size FindSizeAsFullSpaceFromCircularArray(const CircularArray<T>& p_cArray);
    template<typename T>
    Size FindSizeAsFreeSpaceFromCircularArray(const CircularArray<T>& p_cArray);


    template<typename T>
    bool CircularArrayIsNull(const CircularArray<T>& p_nullCArray);
    template<typename T>
    bool CircularArrayIsEmpty(const CircularArray<T>& p_emptyCArray);
    template<typename T>
    bool CircularArrayIsFull(const CircularArray<T>& p_fullCArray);
    template<typename T>
    bool CircularArrayIsAvailable(const CircularArray<T>& p_availableCArray);
    template<typename T>
    bool CircularArrayIsNullOrFull(const CircularArray<T>& p_availableCArray);
    template<typename T>
    bool CircularArrayIsNullOrEmpty(const CircularArray<T>& p_availableCArray);
    
    template<typename T>
    bool CircularArrayHasSameContentsAsCircularArrray(
        const CircularArray<T>& p_cArray1, const CircularArray<T>& p_cArray2
    );


    template<typename T>
    void AdvanceUsingCircularArrayAsFrontFromSizeAsAmount(
        CircularArray<T>& p_cArray, const Size& p_advanceBy
    );
    template<typename T>
    void AdvanceUsingCircularArrayAsBackFromSizeAsAmount(
        CircularArray<T>& p_cArray, const Size& p_advanceBy
    );
    template<typename T>
    void
    AdvanceToSizeAsAdvancedUsingCircularArrayAsFrontFromSizeAsAmountCallbackOnPartial(
        Size& p_advanced, CircularArray<T>& p_cArray, const Size& p_advanceBy,
        Callback& p_partial
    );
    template<typename T>
    void
    AdvanceToSizeAsAdvancedUsingCircularArrayAsBackFromSizeAsAmountCallbackOnPartial(
        Size& p_retreated, CircularArray<T>& p_cArray, const Size& p_advanceBy,
        Callback& p_partial
    );

    template<typename T>
    void RetreatUsingCircularArrayAsFrontFromSizeAsAmount(
        CircularArray<T>& p_cArray, const Size& p_retreatBy
    );
    template<typename T>
    void RetreatUsingCircularArrayAsBackFromSizeAsAmount(
        CircularArray<T>& p_cArray, const Size& p_retreatBy
    );
    template<typename T>
    void
    RetreatToSizeAsRetreatedUsingCircularArrayAsFrontFromSizeAsAmountCallbackOnPartial(
        Size& p_retreated, CircularArray<T>& p_cArray, const Size& p_retreatBy,
        Callback& p_partial
    );
    template<typename T>
    void
    RetreatToSizeAsRetreatedUsingCircularArrayAsBackFromSizeAsAmountCallbackOnPartial(
        Size& p_retreated, CircularArray<T>& p_cArray, const Size& p_retreatBy,
        Callback& p_partial
    );

    template<typename T>
    void ReadFromArrayFromCircularArrayAsFront(
        const Array<T>& p_array, const CircularArray<T>& p_cArray
    );
    template<typename T>
    void ReadFromArrayFromCircularArrayAsBack(
        const Array<T>& p_array, const CircularArray<T>& p_cArray
    );
    template<typename T>
    void ReadToSizeAsRedFromArrayFromCircularArrayAsFrontCallbackOnPartial(
        Size& p_red, const Array<T>& p_arrayToRead,
        const CircularArray<T>& p_readFromCArray, Callback& p_partial
    );
    template<typename T>
    void ReadToSizeAsRedFromArrayFromCircularArrayAsBackCallbackOnPartial(
        Size& p_red, const Array<T>& p_arrayToRead,
        const CircularArray<T>& p_readFromCArray, Callback& p_partial
    );

    template<typename T>
    void WriteFromArrayFromCircularArrayAsFront(
        const Array<T>& p_array, const CircularArray<T>& p_cArray
    );
    template<typename T>
    void WriteFromArrayFromCircularArrayAsBack(
        const Array<T>& p_array, const CircularArray<T>& p_cArray
    );
    template<typename T>
    void WriteToSizeAsWrittenFromArrayFromCircularArrayAsFrontCallbackOnPartial(
        Size& p_written, const Array<T>& p_arrayToWrite,
        const CircularArray<T>& p_writeToCArray, Callback& p_partial
    );
    template<typename T>
    void WriteToSizeAsWrittenFromArrayFromCircularArrayAsBackCallbackOnPartial(
        Size& p_written, const Array<T>& p_arrayToRead,
        const CircularArray<T>& p_writeToCArray, Callback& p_partial
    );

    template<typename T>
    void ExtractToSizeAsExtractedFromArrayUsingCircularArrayAsFrontCallbackOnPartial(
        Size& p_extracted, const Array<T>& p_arrayToExtract,
        CircularArray<T>& p_extractFromCArray, Callback& p_partial
    );
    template<typename T>
    void ExtractToSizeAsExtractedFromArrayUsingCircularArrayAsBackCallbackOnPartial(
        Size& p_extracted, const Array<T>& p_arrayToExtract,
        CircularArray<T>& p_extractFromCArray, Callback& p_partial
    );

    template<typename T>
    void InsertToSizeAsInsertedFromArrayUsingCircularArrayAsFrontCallbackOnPartial(
        Size& p_inserted, const Array<T>& p_arrayToInsert,
        CircularArray<T>& p_insertToCArray, Callback& p_partial
    );
    template<typename T>
    void InsertToSizeAsInsertedFromArrayUsingCircularArrayAsBackCallbackOnPartial(
        Size& p_inserted, const Array<T>& p_arrayToInsert,
        CircularArray<T>& p_insertToCArray, Callback& p_partial
    );

}

#endif //CIRCULAR_ARRAY__CIRCULAR_ARRAY_CIRCULAR_ARRAY_DECLARATION_HPP