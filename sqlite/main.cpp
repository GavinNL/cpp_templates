#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>

int main(int argc, char* argv[])
{

    {
        // Open a database file in create/write mode
        SQLite::Database    db("test2.db3", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
        std::cout << "SQLite database file '" << db.getFilename().c_str() << "' opened successfully\n";

        db.exec("DROP TABLE IF EXISTS userTable");

        db.exec( "CREATE TABLE userTable ("
                                  "id INTEGER PRIMARY KEY"
                                  ",name TEXT"
                                  ",age INTEGER"
                                  ",weight FLOAT"
                            ")"

                 );

        {
            SQLite::Statement query(db, "INSERT INTO userTable VALUES (NULL, ?, ?, ?)");

            // Bind the blob value to the first parameter of the SQL query
            //query.bind(0, 1); // id
            query.bind(1, "Bob");
            query.bind(2, 36);
            query.bind(3, 180.f);
            // Execute the one-step query to insert the blob

            int nb = query.exec();
        }

        {
            SQLite::Statement query(db, "INSERT INTO userTable VALUES (NULL, ?, ?, ?)");

            // Bind the blob value to the first parameter of the SQL query
            //query.bind(0, 1); // id
            query.bind(1, "Alice");
            query.bind(2, 30);
            query.bind(3, 124.f);
            // Execute the one-step query to insert the blob

            int nb = query.exec();
        }

        // Check the results : expect two row of result
        SQLite::Statement   query(db, "SELECT * FROM userTable");
        std::cout << "SELECT * FROM userTable :\n";
        while (query.executeStep())
        {
            std::string name = query.getColumn(1);
            int32_t      age = query.getColumn(2);
            float     weight = query.getColumn(3).getDouble();

            std::cout << "Name: " << name << "  age: " << age << "  weight: " << weight << std::endl;
        }
    }
}
