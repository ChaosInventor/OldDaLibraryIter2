#ifndef CALLBACK__CALLBACK_CALLBACK_HPP
#define CALLBACK__CALLBACK_CALLBACK_HPP

#include "Debug/Debug.hpp"

#define ValidateCallback(p_callback)\
    Assert((p_callback).m_Function != nullptr, "Cannot call callback at "   \
    << &(p_callback) << " because its function is null(state is "           \
    << (p_callback).m_State)


namespace Library
{

    struct Callback;


    using CallbackFunction = void (*) (Callback& p_callback);


    extern Callback g_NullCallback;
    extern Callback g_ExitCallback;
    extern Callback g_AbortCallback;


    void NullCallback(Callback& p_callback);
    void ExitCallback(Callback& p_callback);
    void AbortCallback(Callback& p_callback);
    
    void ForkCallback_AssumingStateHasCallbacks(Callback& p_callback);
    void MoveCallback_AssumeStateHasCallbacks(Callback& p_callback);
    
    void SetToMin_AssumeStateIsLocationOfSize(Callback& p_callback);
    void SetToMax_AssumeStateIsLocationOfSize(Callback& p_callback);
    
    void SetToTrue_AssumeStateIsLocationOfBool(Callback& p_callback);
    void SetToFalse_AssumeStateIsLocationOfBool(Callback& p_callback);


    struct Callback
    {

        void* m_State;
        CallbackFunction m_Function;
    
        Callback():
        m_State(g_NullCallback.m_State),
        m_Function(g_NullCallback.m_Function)
        { }
        Callback(const Callback& p_other) = delete;
        Callback(Callback&& p_other):
        m_State(p_other.m_State),
        m_Function(p_other.m_Function)
        {
            p_other.m_State = nullptr;
            p_other.m_Function = nullptr;
        }

        Callback(CallbackFunction p_function):
        m_State(nullptr),
        m_Function(p_function)
        { }
        Callback(void* p_state, CallbackFunction p_function):
        m_State(p_state),
        m_Function(p_function)
        { }


        Callback& operator=(const Callback& p_other) = delete;
        Callback& operator=(Callback&& p_other)
        {
        
            m_State = p_other.m_State;
            m_Function = p_other.m_Function;
        
            p_other.m_State = nullptr;
            p_other.m_Function = nullptr;

            return *this;
        
        }


        operator CallbackFunction&()
        {
            return m_Function;
        }
        operator const CallbackFunction&() const
        {
            return m_Function;
        }

        void operator()()
        {
            
            ValidateCallback(*this)


            (*this).m_Function(*this);

        }

    };

}


#endif //CALLBACK__CALLBACK_CALLBACK_HPP