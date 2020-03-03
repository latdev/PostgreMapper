//
// Created by Eugene Chugrejev on 03.03.20.
//

#ifndef _POSTGREMAP_H_
#define _POSTGREMAP_H_

#include <string>
#include <vector>
#include <map>
#include <libpq-fe.h>
#include <cstring>

typedef std::pair<std::string,std::string> PMColumn;
typedef std::map<std::string,std::string> PMRow;
typedef std::vector<PMRow> PMResultset;
typedef std::vector<std::vector<std::string>> PMResultsetNum;

class PostgreMapper {
private:
    PGconn* conn;
    std::string query_error;
public:
    explicit PostgreMapper(const std::string& connection_string);
    ~PostgreMapper();
    bool IsActive();
    bool Query(const std::string& query, PMResultset& results);
    bool QueryRow(const std::string& query, PMRow& result);
    std::string GetErrorMessage();
    std::string GetLastError();
    std::string Escape(std::string esc);
};

#endif
