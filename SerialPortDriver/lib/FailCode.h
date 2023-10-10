#pragma once

/**
 * @class FailCode
 * @brief FailCode class provide template structure to all the another class to keep keep their own failcodes.
 */
template <typename T>
class FailCode
{
private:
    T failCode;
public:
    /**
     * @brief This function initialize failCode variable.
     * @param[in] failCode: This is fail code, which has template T type.
     * @return N/A
     */
    FailCode(const T failCode)
    {
        failCode = failCode;
    }

    /**
     * @brief This function over load the "=" operator.
     * Therefore, A failCode variable, which has template T type can be assigned to the failCode variable which is in the FailCode object.
     * @param[in] failCode: This is fail code, which has template T type.
     * @return FailCode<T>&: FailCode class object referance.
     */
    FailCode<T>& operator =(const T& failCode)
    {
        (this->failCode) = failCode;

        return *this;
    }

    /**
     * @brief This function over load the "!=" operator.
     * Therefore, A failCode variable, which has template T type can be compared to the failCode variable which is in the FailCode object.
     * @param[in] failCode: This is fail code, which has template T type.
     * @return TRUE: if the failCode variable, which has template T type is equal to the failCode variable which is in the FailCode object.
     *         FALSE: if the failCode variable, which has template T type is not equal to the failCode variable which is in the FailCode object.
     */
    bool operator !=(const T& failCode)
    {
        if (this->failCode != failCode)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /**
     * @brief This function return the The failCode, which is in the FailCode object, variable that is template T type.
     * @param N/A
     * @return T&: The failCode, which is in the FailCode object, variable referance that is template T type.
     */
    T& getValue()
    {
        return failCode;
    }
};

/**
 * @brief This function assign the appointedFailCode to the FailCode object and throw the FailCode object.
 * @param[in] failCode: This is the FailCode object referance which has template T.
 * param[in] appointedFailCode: This is Failcode right value referance which has template T. 
 * @return N/A
 */
template <typename T>
inline void FAILCODE_SET_AND_EXIT(FailCode<T>& failCode, T&& appointedFailCode)
{
    failCode = appointedFailCode;
    throw failCode;
};

/**
 * @brief This function compare the controlFailCode and the FailCode object.
 * If controlFailCode is not equal to FailCode object, this function throw the FailCode object
 * @param[in] failCode: This is FailCode object referance whose type is template T.
 * param[in] controlFailCode: This is Failcode right value referance whose type is template T. 
 * @return N/A
 */
template <typename T>
inline void FAILCODE_CHECK_AND_EXIT(FailCode<T>& failCode, T&& controlFailCode)
{
    if (failCode != controlFailCode)
    {
       throw failCode;
    }
};
