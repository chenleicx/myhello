//
//  CTest.cpp
//  mytest
//
//  Created by chenlei on 2017/9/3.
//  Copyright © 2017年 longzhihui. All rights reserved.
//

#include "CTest.hpp"
#include <iostream>

CTest::CTest() : m_data(0)
{
    std::cout << "CTest::CTest()\n";
}

CTest::~CTest()
{
    std::cout << "CTest::~CTest()\n";
}

CTest::CTest(const CTest & t)
{
    std::cout << "CTest::CTest(const CTest & t)";
}

CTest & CTest::operator = (const CTest & t)
{
    this->m_data = t.m_data;
    return *this;
}
