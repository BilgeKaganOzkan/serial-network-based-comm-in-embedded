/** \addtogroup FailCode
 * @{
 * @author Bilge Kağan ÖZKAN
 * @file FailCode.h
 * @defgroup FailCode
 * @brief This module includes FailCode class, FAILCODE_SET_AND_EXIT and FAILCODE_CHECK_AND_EXIT functions.
 * @verbatim
 * The main idea of FailCode class is to provide template structure to all the other classes to keep their
 * own failcodes which were defined as enum type. Therefore, FailCode class was created as the template type.
 * If you want to use FailCode class, first you must define your own 'failCode' as an enum type and then
 * objectify it using your own 'failCode' enum.
 * 
 * The main ideas of FAILCODE_SET_AND_EXIT and FAILCODE_CHECK_AND_EXIT functions are to assign 'failCode'
 * to your objectified FailCode class and then throw the objectified FailCode class to raise an exception
 * @endverbatim
 */

#pragma once

/**
 * @class FailCode
 * @brief FailCode class provides template structure to all the other classes to keep their own failcodes.
 * Therefore, FailCode class was created as the template type.
 */
template <typename T>
class FailCode
{
private:
    T failCode; ///< This variable keeps 'failCode' variable whose type is T type.
public:
    /**
     * @brief This constructor initializes the FailCode object without any argument.
     * @param N/A
     * @return N/A
     */
    FailCode()
    {
    }

    /**
     * @brief This constructor deinitializes the FailCode object without any argument.
     * @param N/A
     * @return N/A
     */
    ~FailCode()
    {
    }

    /**
     * @brief This function overloads the "=" operator.
     * Therefore, A failCode variable, which is T type, can be assigned 
     * to the failCode variable that is in the FailCode object.
     * @param[in] failCode: This is the fail code, which is T type.
     * @return FailCode<T>&: FailCode object reference.
     */
    FailCode<T>& operator =(const T& failCode)
    {
        (this->failCode) = failCode;

        return *this;
    }

    /**
     * @brief This function overloads the "!=" operator.
     * Therefore, A failCode variable, which is T type, can be 
     * compared to the failCode variable that is in the FailCode object.
     * @param[in] failCode: This is the fail code, which is T type.
     * @return TRUE: if the failCode variable, which is T type, is equal to the failCode variable which is in the FailCode object.
     *         FALSE: if the failCode variable, which is T type, is not equal to the failCode variable which is in the FailCode object.
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
     * @brief This function returns the failCode, which is in the FailCode object, variable that is T type.
     * @param N/A
     * @return T&: The failCode, which is in the FailCode object, variable reference that is T type.
     */
    T& getValue()
    {
        return failCode;
    }
};

/**
 * @brief This function assigns the appointedFailCode variable which is T type
 * to the FailCode object and throw the FailCode object.
 * @param[in] failCode: This is the FailCode object reference which is T type.
 * @param[in] appointedFailCode: This is Failcode right value reference which is T type. 
 * @return N/A
 */
template <typename T>
inline void FAILCODE_SET_AND_EXIT(FailCode<T>& failCode, T&& appointedFailCode)
{
    failCode = appointedFailCode;
    throw failCode;
};

/**
 * @brief This function compares the controlFailCode variable which is T type and the FailCode object.
 * If controlFailCode variable is not equal to FailCode object, this function throws the FailCode object.
 * @param[in] failCode: This is FailCode object reference whose type is T.
 * @param[in] controlFailCode: This is Failcode right value reference whose type is T. 
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

/**@}*/
