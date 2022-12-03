//
// Created by Łukasz Narolski on 03/12/2022.
//

#include "Star2.h"
#include <iostream>

namespace Day1 {
    Star2::Star2(std::vector<std::string>* file) {
        long long max[3] = {0, 0, 0};
        long long tempSum = 0;

        for (std::string fileLine : *file)
        {
            if (fileLine == "")
            {
                for (int i = 0; i < 3; ++i)
                {
                    if (tempSum > max[i])
                    {
                        long long temp = max[i];
                        max[i] = tempSum;
                        tempSum = temp;
                    }
                }

                tempSum = 0;
            }
            else
            {
                tempSum += std::stoull(fileLine);
            }
        }

        for (int i = 0; i < 3; ++i)
        {
            if (tempSum > max[i])
            {
                long long temp = max[i];
                max[i] = tempSum;
                tempSum = temp;
            }
        }

        tempSum = 0;
        for (int i = 0; i < 3; ++i)
        {
            tempSum += max[i];
        }

        std::cout << "Day1-Star2 Max: " << tempSum << std::endl;

        delete file;
    }
} // Day1