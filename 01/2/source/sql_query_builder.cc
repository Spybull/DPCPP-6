#include "sql_query_builder.hh"

SqlSelectQueryBuilder::SqlSelectQueryBuilder() {}

SqlSelectQueryBuilder &SqlSelectQueryBuilder::AddColumn(const std::string &col_name) noexcept {

    std::string col = trim(col_name);
    query.columns.push_back(col);
    return *this;
}

SqlSelectQueryBuilder &SqlSelectQueryBuilder::AddFrom(const std::string &table_name) {
    std::string table = trim(table_name);
    query.from_table = table;
    return *this;
}

SqlSelectQueryBuilder &SqlSelectQueryBuilder::AddWhere(const std::string &col,
                                                       const std::string &value,
                                                       const std::string &operation) noexcept
{

    std::string c, v, o;
    c = trim(col);
    v = trim(value);
    o = trim(operation);

    if ( query.condition.empty() )
        query.condition.push_back(c + "=" + v);
    else
        query.condition.push_back(o + " " + c + "=" + v);
    return *this;
}

SqlSelectQueryBuilder &SqlSelectQueryBuilder::AddWhere(const std::map<std::string,std::string>& kv) noexcept
{
    for (const auto &pair : kv)
        SqlSelectQueryBuilder::AddWhere(pair.first, pair.second);
    return *this;
}

SqlSelectQueryBuilder &SqlSelectQueryBuilder::AddColumns(const std::vector<std::string>& columns) noexcept
{
    for (const auto &col : columns)
        AddColumn(col);
    return *this;
}

std::string SqlSelectQueryBuilder::BuildQuery()
{
    std::ostringstream result_query;
    result_query << "SELECT ";

    if (query.columns.empty())
    {
       result_query << "*";
    }
    else
    {
        for (size_t i = 0; i < query.columns.size(); ++i)
        {
            result_query << query.columns[i];
            if (i != query.columns.size() - 1)
                result_query << ", ";
        }
    }

    if (!query.from_table.size())
        throw std::runtime_error("FROM operator must be set");

    result_query << " FROM " << query.from_table << " ";

    if (!query.condition.empty())
    {
        result_query << "WHERE ";
        for (size_t i = 0; i < query.condition.size(); ++i)
        {
            result_query << query.condition[i];
            if (i != query.condition.size() - 1)
                result_query << " ";
        }
    }

    result_query << ";";
    return result_query.str();
}

std::string SqlSelectQueryBuilder::trim(const std::string &str)
{
    if (!str.length())
        return {};

    const char wp[] = {" \t\n"};

    const size_t lspaced(str.find_first_not_of(wp));
    if (std::string::npos == lspaced)
        return {};

    const size_t rspaced(str.find_last_not_of(wp));
    return str.substr(lspaced, (rspaced - lspaced + 1));
}