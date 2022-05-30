//
// Created by tedhi on 5/27/2022.
//
double accumulative_avg(double *accumulator, int len, double nextNum)
{
    *accumulator += nextNum;
    len++;
    //return the average
    return *accumulator / len;
}