#pragma once
#include <iostream>
using namespace std; 


class clsCalculater
{
    float _LastNumber = 0;
    string _LastOperation = " ";
    float _PreviousResult = 0;
    float _Result = 0;

    bool IsZero(float Number)
    {
        return  (Number == 0);
    }

public:

    void Add(float Number)
    {
        _LastNumber = Number;
        _LastOperation = "Adding";
        _PreviousResult = _Result;
        _Result += Number;
    }

    void Subtract(float Number)
    {
        _LastNumber = Number;
        _LastOperation = "Subtract";
        _PreviousResult = _Result;
        _Result -= Number;
    }

    void Multiply(float Number)
    {
        _LastNumber = Number;
        _LastOperation = "Multiply";
        _PreviousResult = _Result;
        _Result *= Number;
    }

    void Divide(float Number)
    {
        if (IsZero(Number))
        {
            Number = 1;
        }

        _LastNumber = Number;
        _LastOperation = "Divide";
        _PreviousResult = _Result;
        _Result /= Number;
    }

    float GetFinlResult()
    {
        return _Result;
    }

    void Clear()
    {
        _LastNumber = 0;
        _LastOperation = "Clear";
        _PreviousResult = 0;
        _Result = 0;
    }

    void CancellOperation()
    {
        _LastNumber = 0;
        _LastOperation = "Cancelling Operation";
        _PreviousResult = _Result;
    }

    void PrintResult()
    {
        cout << "Result ";
        cout << "After " << _LastOperation << " " <<
            _LastNumber << " is " << _Result << "\n";
    }
};

