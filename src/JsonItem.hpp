/**
 * @file JsonItem.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-12-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <WString.h>
#include <stdio.h>

enum ObjectType
{
    t_string,
    t_int,
    t_ulong,
    t_long,
    t_float,
    t_double,
    t_bool,
};

class JsonItem
{
private:
    String _name;
    ObjectType _type;
    void *_ptr;
    uint8_t _size;

    String getPrintf()
    {
        switch (_type)
        {
        case ObjectType::t_string:
            {
                String val = "\"";
                int i = 0;
                char c = ((char*)_ptr)[i];
                while(c != '\0')
                {
                    val += c;
                    i++;
                    c = ((char*)_ptr)[i];
                }
                val += "\"";
                return val;
            }
        case ObjectType::t_int:
            {
                int *val = (int*)_ptr;
                return String(*val);
            }
        case ObjectType::t_ulong:
            {
                unsigned long *val = (unsigned long*)_ptr;
                return String(*val);
            }
        case ObjectType::t_long:
            {
                long *val = (long*)_ptr;
                return String(*val);
            }
        case ObjectType::t_float:
            {
                float *val = (float*)_ptr;
                return String(*val);
            }
        case ObjectType::t_double:
            {
                double *val = (double*)_ptr;
                return String(*val);
            }    
        case ObjectType::t_bool:
            {
                bool *val = (bool*)_ptr;
                return *val ? "true" : "false";
            }
        default:
            return "null";
            break;
        }
    }

public:
    JsonItem(){}

    JsonItem(String name, void *ptr, uint8_t size) {
        _name = name;
        _ptr = ptr;
        _size = size;
    }

    ~JsonItem() {}

    String toString()
    {
        char jsonElement[64];
        String id = getPrintf();
        sprintf(jsonElement, "\"%s\":%s", _name.c_str(), getPrintf().c_str());
        return String(jsonElement);
    }

    void fromString(String value){
        switch (_type)
        {
        case ObjectType::t_string:
            {
                char *val = (char*)_ptr;
                value.toCharArray(val, _size);
            }
            break;
        case ObjectType::t_int:
            {
                int *val = (int*)_ptr;
                *val = value.toInt();
            }
            break;
        case ObjectType::t_ulong:
            {
                unsigned long *val = (unsigned long*)_ptr;
                *val = value.toInt();
            }
            break;
        case ObjectType::t_long:
            {
                long *val = (long*)_ptr;
                *val = value.toInt();
            }
            break;
        case ObjectType::t_float:
            {
                float *val = (float*)_ptr;
                *val = value.toFloat();
            }
            break;
        case ObjectType::t_double:
            {
                double *val = (double*)_ptr;
                *val = value.toDouble();
            }    
            break;
        case ObjectType::t_bool:
            {
                bool *val = (bool*)_ptr;
                *val = value == "true";
            }
            break;
        default:
            break;
        }
    }

    String getName()
    {
        return _name;
    }

    ObjectType getType()
    {
        return _type;
    }

    void setType(ObjectType type)
    {
        this->_type = type;
    }
};