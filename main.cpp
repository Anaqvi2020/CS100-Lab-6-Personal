#include "spreadsheet.hpp"
#include "select.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
    Spreadsheet sheet;
    sheet.set_column_names({"First","Last","Age","Major"});
    sheet.add_row({"Amanda","Andrews","22","business"});
    sheet.add_row({"Brian","Becker","21","computer science"});
    sheet.add_row({"Carol","Conners","21","computer science"});
    sheet.add_row({"Joe","Jackson","21","mathematics"});
    sheet.add_row({"Sarah","Summers","21","computer science"});
    sheet.add_row({"Diane","Dole","20","computer engineering"});
    sheet.add_row({"David","Dole","22","electrical engineering"});
    sheet.add_row({"Dominick","Dole","22","communications"});
    sheet.add_row({"George","Genius","9","astrophysics"});

    sheet.print_selection(std::cout);
    std::cout << std::endl;

    
     sheet.set_selection(new Select_Contains(&sheet,"Last","Dole"));
    sheet.print_selection(std::cout);
    std::cout << std::endl;
    return 0;
}
