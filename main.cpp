#include <iostream>
#include <string>
#include "src/postgre_map/PostgreMapper.h"

using namespace std;

int main() {
    cout << "Postgres Connection Library Test Case" << endl;

    PostgreMapper db("host=127.0.0.1 port=5432 user=USER password=PASSWORD dbname=DATABASE");
    if (db.IsActive()) {
        PMResultset res;
        int n = 0;
        if (db.Query("SELECT * FROM test_table LIMIT 1", res)) {
            for (PMRow row: res) {
                for (PMColumn col: row) {
                    cout << col.first << " => " << col.second << endl;
                }
                cout << "=============( " << ++n << " )===" << endl;
            }
        } else {
            cerr << db.GetLastError() << endl;
        }
    } else {
        cerr << db.GetErrorMessage() << endl;
    }
    return 0;
}
