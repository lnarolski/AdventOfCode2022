//
// Created by Łukasz Narolski on 03/12/2022.
//

#include "Star1.h"
#include <iostream>

namespace Day1 {
    Star1::Star1(std::vector<std::string>* file) {
        long long max = 0;
        long long tempSum = 0;

        for (std::string fileLine : *file)
        {
            if (fileLine == "")
            {
                if (tempSum > max)
                {
                    max = tempSum;
                }

                tempSum = 0;
            }
            else
            {
                tempSum += std::stoull(fileLine);
            }
        }

        if (tempSum > max)
        {
            max = tempSum;
        }

        std::cout << "Day1-Star1 Max: " << max << std::endl;

        delete file;
    }
} // Day1