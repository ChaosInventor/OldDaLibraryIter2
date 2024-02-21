#ifndef STRING_LITERAL__STRING_LITERAL_STRING_LITERAL_HPP
#define STRING_LITERAL__STRING_LITERAL_STRING_LITERAL_HPP

#include "Meta/Meta.hpp"
#include "Debug/Debug.hpp"

#define ValidateStringLiteral(p_literal)\
    if((p_literal).m_Location == nullptr)                                       \
    {                                                                           \
        Assert(                                                                 \
            (p_literal).m_Length == 0,                                          \
            "String literal with a null location must have a size of 0."        \
        );                                                                      \
    }                                                                           \
    else                                                                        \
    {                                                                           \
        Assert(                                                                 \
            (p_literal).m_Length > 0,                                           \
            "String literal with a non null location must have a size that is " \
            "greater than 0"                                                    \
        );                                                                      \
    }

namespace Library
{

    struct StringLiteral
    {
      
        const char* m_Location;
        Size m_Length;
    
        StringLiteral() = default;
        StringLiteral(const StringLiteral&) = default;
        StringLiteral(StringLiteral&&) = default;

        StringLiteral(const char* p_cString);


        StringLiteral& operator=(const StringLiteral&) = default;
        StringLiteral& operator=(StringLiteral&&) = default;
    
        bool operator==(const StringLiteral& p_other) const;
        bool operator==(const char* p_cString) const;

        bool operator!=(const StringLiteral& p_other) const;
        bool operator!=(const char* p_cString) const;


        const char& operator[](const Size& p_index) const;

    };

    
    Size FindSizeAsLengthOfFromCharPointerAsCString(const char* p_cString);

    bool operator==(const char* p_cString, const StringLiteral& p_literal);
    bool operator!=(const char* p_cString, const StringLiteral& p_literal);


}

#endif //STRING_LITERAL__STRING_LITERAL_STRING_LITERAL_HPP