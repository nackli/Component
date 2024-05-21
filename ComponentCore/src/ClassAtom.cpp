/*
Written by Nack li <nackli@163.com>
Copyright (c) 2024. All Rights Reserved.
*/

#include "ClassAtom.h"
#include <typeinfo>
#include "StringUtils.h"
#include "Properties.h"
#ifndef WIN32
#include <cxxabi.h>
#endif
ClassAtom::ClassAtom() :ObjectClass(), Properties()
{

}

ClassAtom::~ClassAtom()
{
}