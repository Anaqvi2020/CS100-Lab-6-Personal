#ifndef __SELECT_HPP__
#define __SELECT_HPP__

#include <string>
#include "spreadsheet.hpp"

class Select
{
public:
    virtual ~Select() = default;

    
    virtual bool select(const Spreadsheet* sheet, int row) const = 0;
};


class Select_Column: public Select
{
protected:
    int column;
public:
    Select_Column(const Spreadsheet* sheet, const std::string& name)
    {
        column = sheet->get_column_by_name(name);
    }

    virtual bool select(const Spreadsheet* sheet, int row) const
    {
        return select(sheet->cell_data(row, column));
    }

    
    virtual bool select(const std::string& s) const = 0;
};

class Select_And: public Select
{
    public:
    Select* first;
    Select* second;
    Select_And(Select* select1, Select* select2)
    {
        first = select1;
        second = select2;
    }
    ~Select_And()
    {
    delete first;
    delete second;
    }
    virtual bool select(const Spreadsheet* sheet, int row)
    {
        if ((first->select(sheet, row)==true) && (second->select(sheet, row)==true))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

class Select_Contains: public Select_Column
{
    public:
    std::string data;

    Select_Contains(const Spreadsheet* sheet, const std::string columnName, const std::string item):Select_Column(sheet, columnName)
    {
        data = item;
    }
    ~Select_Contains()
    {}
    virtual bool select(const std::string& s) const
    {
        if ( s.find(data) != std::string::npos)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

};

class Select_Not: public Select
{
    public:
    Select* argument;
    Select_Not(Select* input)
    {
        argument = input;
    }
    ~Select_Not()
     {
      delete argument;
     }

    virtual bool select(const Spreadsheet* sheet, int row)
    {
        if (argument->select(sheet, row) == false)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

class Select_Or: public Select
{
    public:
    Select* first;
    Select* second;
    Select_Or(Select* select1, Select* select2)
    {
        first = select1;
        second = select2;
    }
    ~Select_Or()
     {
      delete first;
      delete second;
     }

    virtual bool select(const Spreadsheet* sheet, int row)
    {
        if ((first->select(sheet, row)==true) || (second->select(sheet, row)==true))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};
#endif 
