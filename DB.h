//
// Created by Hrayr on 5/30/2020.
//

#ifndef DATABASE_DB_H
#define DATABASE_DB_H

class String;

class FileManager;

class DB {
private:
    static DB *instance;
    char **table_data;
    char **table_structure;
    String **tables;
    long long table_count;

    /** LOAD DATA SECTION */

    /**
     * add or take(not implemented for now) a size by integer sign
     * @param size
     * @return
     */
    bool resize(long long size);

    /**
     * checks if table exists in cache
     * @param table_name
     * @return
     */
    bool check_table_loaded(String *table_name);

    /**
     * getting index of cached table
     * @param table_name
     * @return
     */
    long long get_table_index(String *table_name);

    /**
     * Load table data from a file
     * if not force load cached ~ if force reload data
     * @param table_name
     * @param force
     * @return
     */
    bool load_table(String *table_name, bool force = false);

    /**
     * Returns table data raw by given name
     * @param table_name
     * @return
     */
    char *get_table_data(String *table_name);

    /**
     * Returns table structure raw by given name
     * @param table_name
     * @return
     */
    char *get_table_structure(String *table_name);

    /** END LOAD DATA SECTION */

    /**
     * Saves table raw data into table data file
     * @param table_name
     * @return
     */
    bool save_table_data(String *table_name);

    /**
     * Saves table structure raw into table structure file
     * @param table_name
     * @return
     */
    bool save_table_structure(String *table_name);

    bool save_tables();


    DB();

public:
    /**
     * Returns singleton class instance
     * @return
     */
    DB *getInstance();

    ~DB() {
        // On program exit or anyway when DB class deconstruct will be called
        // save data into files
        this->save_tables();
        // then delete variables
        delete[] table_data;
        delete[] table_structure;
        delete[] tables;
    }

    /**
     * Returns table data and structure in raw format
     * get_table()[0] - Table structure
     * get_table()[1] - Table data
     * @return
     */
    char **getTable(String *table_name);

    /**
     * Saves Table raw into files
     * @param table_name
     * @return
     */
    bool saveTable(String *table_name);

};


#endif //DATABASE_DB_H
