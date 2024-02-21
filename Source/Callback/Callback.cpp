#include "Callback/Callback.hpp"
#include "Meta/Meta.hpp"
#include "Process/Process.hpp"

namespace Library
{

    void NullCallback(Callback& p_callback)
    {
        (void)p_callback;
        return;
    }
    void ExitCallback(Callback& p_callback)
    {
        (void)p_callback;
        ExitWithInteger(0);
    }
    void AbortCallback(Callback& p_callback)
    {
        (void)p_callback;
        Abort();
    }

    void ForkCallback_AssumingStateHasCallbacks(Callback& p_callback)
    {

        Assert(
            p_callback.m_State != nullptr, "Fork callback state cannot be null."
        );


        void** l_dataPack = (void**)p_callback.m_State;
        Callback& l_callback1 = *(Callback*)l_dataPack[0];
        Callback& l_callback2 = *(Callback*)l_dataPack[1];

        l_callback1();
        l_callback2();

    }
    void MoveCallback_AssumeStateHasCallbacks(Callback& p_callback)
    {

        void** l_dataPack = (void**)p_callback.m_State;

        Callback& l_callback1 = *(Callback*)l_dataPack[0];
        Callback& l_callback2 = *(Callback*)l_dataPack[1];

        l_callback1 = (Callback&&)l_callback2;

    }

    void SetToMin_AssumeStateIsLocationOfSize(Callback& p_callback)
    {
        *(Size*)p_callback.m_State = SIZE_MINIMUM;
    }
    void SetToMax_AssumeStateIsLocationOfSize(Callback& p_callback)
    {
        *(Size*)p_callback.m_State = SIZE_MAXIMUM;
    }

    void SetToTrue_AssumeStateIsLocationOfBool(Callback& p_callback)
    {
        *(bool*)p_callback.m_State = true;
    }
    void SetToFalse_AssumeStateIsLocationOfBool(Callback& p_callback)
    {
        *(bool*)p_callback.m_State = false;
    }

    Callback g_NullCallback(nullptr, NullCallback);
    Callback g_ExitCallback(nullptr, ExitCallback);
    Callback g_AbortCallback(nullptr, AbortCallback);

}
