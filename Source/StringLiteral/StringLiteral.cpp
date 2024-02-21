#include "StringLiteral/StringLiteral.hpp"
#include "Debug/Debug.hpp"

namespace Library
{

    StringLiteral::StringLiteral(const char* p_cString)
    {

        m_Location = p_cString;
        if(p_cString == nullptr)
        {
            m_Length = 0;
        }
        else
        {
            m_Length = FindSizeAsLengthOfFromCharPointerAsCString(p_cString);
        }

    }

    bool StringLiteral::operator==(const StringLiteral& p_other) const
    {

        ValidateStringLiteral(*this);
        ValidateStringLiteral(p_other);


        if(m_Location == nullptr || p_other.m_Location == nullptr)
        {
            return m_Location == nullptr && p_other.m_Location == nullptr;
        }

        if(m_Length != p_other.m_Length)
        {
            return false;
        }

        for(Size i = 0; i < m_Length; ++i)
        {
            if(m_Location[i] != p_other[i])
            {
                return false;
            }
        }

        return true;

    }
    bool StringLiteral::operator==(const char* p_cString) const
    {

        ValidateStringLiteral(*this);


        if(p_cString == nullptr || m_Location == nullptr)
        {
            return p_cString == nullptr && m_Location == nullptr;
        }

        Size i;
        for(i = 0; i < m_Length && p_cString[i] != '\0'; ++i)
        {
            if(m_Location[i] != p_cString[i])
            {
                return false;
            }
        }

        return i == m_Length && p_cString[i] == '\0';

    }
    bool operator==(const char* p_cString, const StringLiteral& p_literal)
    {
        ValidateStringLiteral(p_literal);
        return p_literal == p_cString;
    }

    bool StringLiteral::operator!=(const StringLiteral& p_other) const
    {
        ValidateStringLiteral(*this);
        ValidateStringLiteral(p_other);
        return !(*this == p_other);
    }

    bool StringLiteral::operator!=(const char* p_cString) const
    {
        ValidateStringLiteral(*this);
        return !(*this == p_cString);
    }
    bool operator!=(const char* p_cString, const StringLiteral& p_literal)
    {
        ValidateStringLiteral(p_literal);
        return p_literal != p_cString;
    }

    const char& StringLiteral::operator[](const Size& p_index) const
    {
        
        ValidateStringLiteral(*this);
        Assert(
            m_Location != nullptr,
            "Cannot index a string literal with a null location"
        );
        Assert(p_index < m_Length, "Error index is out of bound");


        return m_Location[p_index];
    
    }


    Size FindSizeAsLengthOfFromCharPointerAsCString(const char* p_cString)
    {

        Assert(p_cString != nullptr, "Cannot find the length of a null pointer");
        
        
        Size l_result;
        for(l_result = 0; p_cString[l_result] != '\0'; ++l_result);
        return l_result;
    
    }

}