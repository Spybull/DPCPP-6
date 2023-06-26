#pragma once
#include <sstream>
#include <string>
#include <string_view>
#include <algorithm>
#include <exception>
#include <stdexcept>
#include <vector>
#include <map>

struct SQLselect
{
    std::vector<std::string> columns;
    std::string from_table;
    std::vector<std::string> condition;
};

class SqlSelectQueryBuilder {
    public:
        explicit SqlSelectQueryBuilder();
        SqlSelectQueryBuilder &AddColumn(const std::string &col_name) noexcept;
        SqlSelectQueryBuilder &AddFrom(const std::string &table_name);
        SqlSelectQueryBuilder &AddWhere(const std::string &col,
                                        const std::string &value,
                                        const std::string &operation="AND") noexcept;

        SqlSelectQueryBuilder &AddWhere(const std::map<std::string, std::string>& kv) noexcept;
        SqlSelectQueryBuilder &AddColumns(const std::vector<std::string>& columns) noexcept;

         
        std::string BuildQuery();
    private:
        SQLselect query;
        std::string trim(const std::string &str);
};