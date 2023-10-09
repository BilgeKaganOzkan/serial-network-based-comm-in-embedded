#pragma once

template <typename T>
class FailCode
{
private:
    T failCode;
public:
    FailCode()
    {
    }

    FailCode(const T failCodee)
    {
        failCode = failCodee;
    }

    ~FailCode()
    {
    }

    FailCode<T>& operator =(const T& failCodee)
    {
        (this->failCode) = failCodee;

        return *this;
    }

    bool operator !=(const T& failCodee)
    {
        if (this->failCode != failCodee)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    T& getValue()
    {
        return failCode;
    }
};


template <typename T>
inline void FAILCODE_SET_AND_EXIT(FailCode<T>& failCode, T&& assignFailCode)
{
    failCode = assignFailCode;
    throw failCode;
};


template <typename T>
inline void FAILCODE_CHECK_AND_EXIT(FailCode<T>& failCode, T&& controlFailCode)
{
    if (failCode != controlFailCode)
    {
       throw failCode;
    }
};
