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

class CTest
{
public:
    CTest();
    virtual ~CTest();
    CTest(const CTest & t);
    CTest & operator = (const CTest & t);
private:
    int m_data;
};

#endif /* CTest_hpp */
