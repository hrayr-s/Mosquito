#include <iostream>
#include "types/String.h"
#include "types/structures.h"
#include "FileManager.h"
#include "command/Parser.h"
#include "command/Create.h"
#include "command/Drop.h"
#include "command/Select.h"
#include "command/Update.h"
#include "command/Delete.h"
#include "command/Insert.h"

using namespace std;

int main() {
    String query(';');
    cout << "Welcome to Database" << endl;
    cout << "Type commands" << endl;
    Create create;
    Select select;
    Update update;
    Delete del;
    Insert insert;
    Drop drop;
    while (true) {
        cout << " $>:";
        cin >> query;
        try {
            switch (Parser::getCMD((char *) query)) {
                case COMMAND_SELECT:
                    select.run(query);
                    break;
                case COMMAND_UPDATE:
                    update.run(query);
                    break;
                case COMMAND_DELETE:
                    del.run(query);
                    break;
                case COMMAND_INSERT:
                    insert.run(query);
                    break;
                case COMMAND_DROP:
                    drop.run(query);
                    break;
                case COMMAND_CREATE:
                    create.run(query);
                    break;
                case COMMAND_EXIT:
                    return 0;
                default:
                    cout << endl << "Command not found!" << endl;
                    break;
            }
        } catch (char *s) {
            // catch any text error and print it
            cout << s << endl;
        }
    }
}
