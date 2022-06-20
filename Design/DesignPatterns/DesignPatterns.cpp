// DesignPatterns.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include"AbsFactory.h"


int main()
{
    CWidgetFactory* pFactory = new CMacFactory();
    CClient c(pFactory);    
    c.createWindow();
    c.Draw();

    pFactory = new CWindowsFactory();
    CClient c1(pFactory);
    c1.createWindow();
    c1.Draw();

    return 1;
}
