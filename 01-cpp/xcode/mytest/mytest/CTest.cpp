//
//  CTest.cpp
//  mytest
//
//  Created by chenlei on 2017/9/3.
//  Copyright © 2017年 longzhihui. All rights reserved.
//

#include "CTest.hpp"
#include <iostream>

CTest::CTest() : m_name(""), m_data(0)
{
    std::cout << "CTest::CTest(), name=" << this->m_name << "\n";
}

CTest::CTest(const std::string& name) : m_name(name), m_data(0)
{
    std::cout << "CTest::CTest(), name=" << this->m_name << "\n";
}

CTest::~CTest()
{
    std::cout << "CTest::~CTest(), name=" << this->m_name << "\n";
}

CTest::CTest(const CTest & t)
{
    std::cout << "CTest::CTest(const CTest & t), name=" << this->m_name << "\n";
}

CTest & CTest::operator = (const CTest & t)
{
    this->m_data = t.m_data;
    this->m_name = t.m_name;
    
    std::cout << "CTest & CTest::operator = (const CTest & t), name="
        << this->m_name << "\n";
    
    return *this;
}
