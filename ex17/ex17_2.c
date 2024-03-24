#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>

#define MAX_DATA 512
#define MAX_ROWS 100





struct Connection {
    struct Address {
        int id;
        int set;
        char name[MAX_DATA];
        char email[MAX_DATA];
    };
    struct Database {
        struct Address rows[MAX_ROWS];
        int maxData;
        int maxRows;
    };
    FILE *file;
    struct Database *db;
};

void die (const char *message) {
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }
    exit(1);
}

void Address_print(struct Address *addr) {
    printf("ID: %d Name: %s Email: %s\n", addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn) {
    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
    if (rc != 1)
        die("Failed to load database.");
}

struct Connection *Database_open(const char *filename, char mode) {
    struct Connection *conn = malloc(sizeof(struct Connection));
    if (!conn) {
        die("Memory error");
    }
    conn->db = malloc(sizeof(struct Database));
    if (!conn->db)
        die("Memory error");
    
    if (mode == 'c') {
        conn->file = fopen(filename, "w");
    } else {
        conn->file = fopen(filename, "r+");

        if (conn->file) {
            Database_load(conn);
        }
    }

    if (!conn->file) 
        die("Failed to open the file");

    return conn;
}

void Database_close(struct Connection *conn) {
    if (conn) {
        if (conn->file)
            fclose(conn->file);
        if (conn->db)
            free(conn->db);
        free(conn);
    }
}

void Database_write(struct Connection *conn) {
    rewind(conn->file);

    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    if (rc != 1)
        die("Failed to write database.");
    
    rc = fflush(conn->file);
    if (rc == -1)
        die("Cannot flash database.");
    
}

void Database_init(struct Connection *conn, int maxData, int maxRows) {
    conn->db->maxData = maxData;
    conn->db->maxRows = maxRows;
}

void Database_create(struct Connection *conn) {
    int i = 0;
    for (i = 0; i < conn->db->maxRows; i++) {
        // make a prototype to initialize it
        struct Address addr = {.id = i, .set = 0};
        // then just assign it
        conn->db->rows[i] = addr;
    }
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email){
    if (id < 0 || id >= conn->db->maxRows) 
        die("Invalid ID");
    struct Address *addr = &conn->db->rows[id];
    if (addr->set) 
        die("Already set, delete it first");
    addr->set = 1;
    // WARNING: bug, read the "How to Break it" and fix this
    char *res = strncpy(addr->name, name, conn->db->maxData);
    addr->name[conn->db->maxData - 1] = '\0';
    // demonstrate the strncpy bug
    if (!res)
        die("Name copy failed");
    
    res = strncpy(addr->email, email, conn->db->maxData);
    addr->email[conn->db->maxData - 1] = '\0'; 
    if (!res)
        die("Email copy failed");
}

void Database_get(struct Connection *conn, int id) {
    struct Address *addr = &conn->db->rows[id];
    if (addr->set) {
        Address_print(addr);
    } else {
        die("ID is not set");
    }
}

void Database_delete(struct Connection *conn, int id) {
    struct Address addr = {.id = id, .set = 0};
    conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn) {
    int i = 0;
    struct Database *db = conn->db;
    for (i = 0; i < db->maxRows; i++) {
        struct Address *cur = &db->rows[i];

        if (cur->set) {
            Address_print(cur);
        }
    }
}

void Database_find(struct Connection *conn, char *find) {
    int i = 0;
    struct Database *db = conn->db;
    for (i = 0; i < db->maxRows; i++) {
        struct Address *cur = &db->rows[i];
        if (strcmp(cur->name, find) == 0) {
            Address_print(cur);
        } else if (strcmp(cur->email, find) == 0) {
            Address_print(cur);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3)
        die("USAGE: ex17 <dbfile> <action> [action params]");

    char *filename = argv[1];
    char action = argv[2][0];
    struct Connection *conn = Database_open(filename, action);
    int id = 0;

    if ((argc > 3) && action != 'f' && (action == 's' || action == 'g' || action == 'd')) {
        id = atoi(argv[3]);
        if (id < 0 || id >= conn->db->maxRows) {
            die("There's not that many records.");
        }
    }

    switch (action) {
        case 'c':
            Database_init(conn, atoi(argv[3]), atoi(argv[4]));
            Database_create(conn);
            Database_write(conn);
            break;

        case 'g':
            if (argc != 4) 
                die("Need an id to get");
            Database_get(conn, id);
            break;
        
        case 's':
            if (argc != 6) 
                die("Need id, name, email to set");
            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;
        
        case 'd':
            if (argc != 4) 
                die("Need id to delete");

            Database_delete(conn, id);
            Database_write(conn);
            break;

        case 'l':
            Database_list(conn);
            break;

        case 'f':
            if (argc != 4)
                die("Need character to find");
            Database_find(conn, argv[3]);
            break;

        default:
            die("Invalid action: c=create, g=get, s=set, d=del, l=list");
    }

    Database_close(conn);

    return 0;
}
