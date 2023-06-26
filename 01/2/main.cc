#include <iostream>
#include "sql_query_builder.hh"

int main()
{
    SqlSelectQueryBuilder query_builder;
    query_builder.AddFrom("students");

    std::map<std::string, std::string> add_where;
    std::vector<std::string> add_cols{"surname", "age"};

    add_where["name"] = "Mary";
    add_where["id"] = "600";
    query_builder.AddWhere(add_where);
    query_builder.AddColumns(add_cols).AddColumn("HZ");

    std::cout << query_builder.BuildQuery() << std::endl;
    return 0;
}