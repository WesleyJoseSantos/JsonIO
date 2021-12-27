/**
 * @file Json.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-12-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include "JsonItem.hpp"

#define addObject(x) addItem(#x, x);

class Json
{
private:
    JsonItem *items;
    uint8_t size;

    void assignType(char obj[]) {
        items[size].setType(ObjectType::t_string);
    }

    void assignType(int &obj) {
        items[size].setType(ObjectType::t_int);
    }

    void assignType(unsigned long &obj) {
        items[size].setType(ObjectType::t_ulong);
    }

    void assignType(float &obj) {
        items[size].setType(ObjectType::t_float);
    }

    void assignType(double &obj) {
        items[size].setType(ObjectType::t_double);
    }

    void assignType(bool &obj) {
        items[size].setType(ObjectType::t_bool);
    }

    String getKeyValue(String key, String jsonStr){
        jsonStr.replace(": ",":");
        key = "\"" + key + "\":";
        int idx1 = jsonStr.indexOf(key);
        String subs = jsonStr.substring(idx1 + key.length());
        int idx2 = subs.indexOf(",");
        String val = subs.substring(0, idx2);
        val.replace("\"","");
        val.replace("}","");
        return val;
    }

public:
    Json(int size) {
        items = new JsonItem[size];
    }

    ~Json() {
        delete [] items;
    }

    JsonItem getItem(uint8_t id){
        return items[id];
    }

    JsonItem getItem(String name){
        for (int i = 0; i < size; i++)
        {
            if(items[i].getName() == name)
                return items[i];
        }
    }

    String toString(){
        char jsonStr[512];
        int idx = sprintf(jsonStr,"{");
        for (int i = 0; i < size; i++)
        {
            idx += sprintf(&jsonStr[idx], "%s", items[i].toString().c_str());
            if(i < size - 1) idx += sprintf(&jsonStr[idx], ",");
        }
        idx += sprintf(&jsonStr[idx], "}");
        return String(jsonStr);
    }

    void fromString(String jsonStr){
        for (size_t i = 0; i < size; i++)
        {
            String name = items[i].getName();
            String val = getKeyValue(name, jsonStr);
            items[i].fromString(val);
        }
    }

    template <typename T>
    void addItem(String name, T &obj) {
        items[size] = JsonItem(name, &obj, sizeof(obj));
        assignType(obj);
        size++;
    }
};