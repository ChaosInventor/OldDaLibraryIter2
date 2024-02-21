#ifndef ARITHMETIC__ARITHMETIC_ARITHMETIC_HPP
#define ARITHMETIC__ARITHMETIC_ARITHMETIC_HPP

//TODO: A better module name than arithmetic, it's kinda missleading considering
//this module will only be used for overflow detection.
namespace Library
{

    template<typename T>
    bool UnsignedNumberPlusUnsignedNumberWraps(
        const T& p_addend1, const T& p_addend2
    )
    {
        return (p_addend1 + p_addend2) < p_addend1;
    }
    template<typename T>
    bool UnsignedNumberMinusUnsignedNumberWraps(
        const T& p_minuend, const T& p_subtrahend
    )
    {
        return p_minuend < p_subtrahend;
    }
    template<typename T>
    bool UnsignedNumberTimesUnsignedNumberWrapsWithMaxValue(
        const T& p_factor1, const T& p_factor2, const T& p_max_number
    )
    {
        return p_factor1 > (p_max_number / p_factor2);
    }

    template<typename T>
    T Min(const T& p_first, const T& p_second)
    {
        if(p_first > p_second)
        {
            return p_second;
        }
        else
        {
            return p_first;
        }
    }
    template<typename T>
    T Max(const T& p_first, const T& p_second)
    {
        if(p_first < p_second)
        {
            return p_second;
        }
        else
        {
            return p_first;
        }
    }

    //TODO: Overflow detection for signed numbers.

    //TODO: Overflow detection for other operators.

}

#endif //ARITHMETIC__ARITHMETIC_ARITHMETIC_HPP