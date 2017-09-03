//
//  CTest.hpp
//  mytest
//
//  Created by chenlei on 2017/9/3.
//  Copyright © 2017年 longzhihui. All rights reserved.
//

#ifndef CTest_hpp
#define CTest_hpp

#include <stdio.h>
#include <string>

class CTest
{
public:
    CTest();
    CTest(const std::string& name);
    virtual ~CTest();
    CTest(const CTest & t);
    CTest & operator = (const CTest & t);
    
private:
    int m_data;
    std::string m_name;
};

#endif /* CTest_hpp */
