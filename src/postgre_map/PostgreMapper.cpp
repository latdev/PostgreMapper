//
// Created by Eugene Chugrejev on 03.03.20.
//

#include "PostgreMapper.h"

PostgreMapper::PostgreMapper(const std::string& connection_string) {
    this->conn = PQconnectdb(connection_string.c_str());
}

PostgreMapper::~PostgreMapper() {
    PQfinish(this->conn);
    this->conn = nullptr;
}

bool PostgreMapper::Query(const std::string &query, PMResultset &results) {
    this->query_error = "";
    results.clear();
    PGresult* res = PQexec(this->conn, query.c_str());
    int status = PQresultStatus(res);
    if (status == PGRES_TUPLES_OK) {
        int rows = PQntuples(res);
        for (int r=0; r<rows; r++) {
            PMRow row_data;
            for (int n = 0; n < PQnfields(res); n++) {
                row_data[ PQfname(res, n) ] = PQgetvalue(res, r, n);
            }
            results.push_back(row_data);
        }
    } else if (status == PGRES_COMMAND_OK) {
        //
    } else {
        this->query_error = PQresultErrorMessage(res);
        PQclear(res);
        return false;
    }
    PQclear(res);
    return true;
}

bool PostgreMapper::QueryRow(const std::string &query, PMRow &result) {
    this->query_error = "";
    return false;
}

bool PostgreMapper::IsActive() {
    return PQstatus(this->conn) == CONNECTION_OK && PQstatus(this->conn) != CONNECTION_BAD;
}

std::string PostgreMapper::GetErrorMessage() {
    return PQerrorMessage(this->conn);
}

std::string PostgreMapper::GetLastError() {
    return this->query_error;
}

std::string PostgreMapper::Escape(std::string esc) {
    int len = esc.length() * 2;
    char* out = (char*) calloc(sizeof(char), len);
    memset(out, 0, len);
    PQescapeString(out, esc.c_str(), esc.length());
    auto res = std::string(out);
    free(out);
    return res;
}
