#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/* Macro definitions are not variables and cannot be changed by your program code 
   like variables. You generally use this syntax when creating constants that represent 
   numbers, strings or expression */ 
#define MAX_DATA 512
#define MAX_ROWS 100

struct Address{
    int id;
    int set;
    char name[MAX_DATA];
    char email[MAX_DATA];
};

struct Database{
    // TYPE IDENTIFIER[], e.g. char row[]
    struct Address rows[MAX_ROWS]; 
};

struct Connection{
    FILE *file;
    struct Database *db;
};

void die(const char *message)
{
    if (errno){
        perror(message);
    } else{
        /* When  a system call fails, it usually returns -1 and sets the variable 
           errno to a value describing what went wrong.  (These values can be found 
           in <errno.h>.)  Many library functions do likewise.  The function perror
           () serves to translate this error  code  into  human- readable  form.   
           Note that errno is undefined after a successful sysme call or library 
           function call: this call may well change this variable, even though it 
           succeeds, for example because it internally used some other library function 
           that failed.  Thus, if a failing call is not immediately followed by a 
           call to perror(), the value of errno should be saved.  */ 
        
        printf("ERROR: %s\n", message);
    
    }
    
    exit(1);
}

void Address_print(struct Address *addr)
{
    printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
{
    /* #include <stdio.h>

       size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
       The function fread() reads nmemb items of data, each size bytes long, 
       from the stream pointed to by stream, storing them at the location given 
       by ptr.  */

    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);

    if (rc != 1){
        die("Failed to load database.");
    }
}

struct Connection *Database_open(const char *filename, char mode)
{
    struct Connection *conn = malloc(sizeof(struct Connection));
    if (!conn)
        die("Memory error");

    conn->db = malloc(sizeof(struct Database));
    if(!conn->db)
        die("Memory error");

    /* FILE *fopen(const char *path, const char *mode);

    The  argument  mode  points  to a string beginning with one of the following 
    sequences (possibly followed by additional characters, as described below):

    r      Open text file for reading.  The stream is positioned at the beginning of the file.

    r+     Open for reading and writing.  The stream is positioned at the beginning of the file.

    w      Truncate file to zero length or create text file for writing.  The stream 
    is positioned at the beginning of the file.

    w+     Open for reading and writing.  The file is created if it does not exist, otherwise 
    it is truncated.  The stream  is  positioned at the beginning of the file.  */

    if(mode == 'c'){
        conn->file = fopen(filename, "w");
    } else {
        conn->file = fopen(filename, "r+");

        if (conn->file){
            Database_load(conn);
        }
    }

    if (!conn->file)
        die("Failed to open the file.");

    return conn;
}

void Database_close(struct Connection *conn)
{
    if(conn){
        if(conn->file)
            fclose(conn->file);
        if(conn->db)
            free(conn->db);
            free(conn);
    }
}

void Database_write(struct Connection *conn)
{
    /* The rewind() function sets the file position indicator for the stream pointed 
       to by stream to the beginning of the file.  It is equiv‐ alent to: (void) 
       fseek(stream, 0L, SEEK_SET) except that the error indicator for the stream 
       is also cleared (see clearerr(3)).  */ 
    
    rewind(conn->file);

    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    if (rc != 1)
        die("Failed to write database.");

    /* For  output  streams,  fflush()  forces a write of all user-space buffered 
       data for the given output or update stream via the stream's underlying write 
       function.  For input streams associated with seekable files (e .g., disk files
       , but not pipes or terminals), fflush() discards any  buffered  data that 
       has been fetched from the underlying file, but has not been consumed by the 
       application.  */
    rc = fflush(conn->file);
    if(rc != -1)
        die("Cannot flush database.");
}

void Database_create(struct Connection *conn)
{
    int i = 0;

    for (i = 0; i < MAX_ROWS; i++){
        struct Address addr = {.id = i, .set = 0};
        conn->db->rows[i] = addr;
    }
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
    struct Address *addr = &conn->db->rows[id];
    if(addr->set)
        die("Already set, Delete it first");

    addr->set = 1;

    /*bug. The strncpy() function is similar, except that at most n bytes of src are 
      copied.  Warning: If there is no null byte among the first n bytes of src, 
      the string placed in dest will not be null-terminated.  If the length of src 
      is less than n, strncpy() writes additional null bytes to dest to ensure that 
      a total of n bytes are written.  */

    char *res = strncpy(addr->name, name, MAX_DATA);
    if(!res)
        die("Name copy failed.");

    res = strncpy (addr->email, email, MAX_DATA);
    if(!res)
        die("Email copy failed.");

}

void Database_get(struct Connection *conn, int id)
{
    // rows[id] is the value, like *(row + i)
    struct Address *addr = &conn->db->rows[id];

    if(addr->set){
        Address_print(addr);
    } else {
        die("ID is not set.");
    }
}

void Database_delete(struct Connection *conn, int id)
{
    struct Address addr = {.id = id, .set = 0};
    conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn)
{
    int i = 0;
    struct Database *db = conn->db;

    for (i = 0; i < MAX_ROWS; i++) {
        struct Address *cur = &db->rows[i];

        if(cur->set){
            Address_print(cur);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc > 3)
        die("USAGE: ex17 <dbfile> <action> [action params]");

    char *filename = argv[1];
    char action = argv[2][0];
    struct Connection *conn = Database_open(filename, action);
    int id = 0;

    /*  The atoi() function converts the initial portion of the string pointed to 
        by nptr to int.  The behavior is the same as strtol(nptr, NULL, 10); except 
        that atoi() does not detect errors.  */
    if(argc > 3) id = atoi(argv[3]);
    if (id > MAX_ROWS) die("There's not that many records.");

    switch (action){
        case 'c':
            Database_create(conn);
            Database_write(conn);
            break;

        case 'g':
            if (argc != 4)
                die("Need an id to get.");

            Database_get(conn,id);
            break;

        case 's':
            if (argc != 6)
                die("Need id, name, email to set.");
            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;
            
        case 'd':
            if (argc != 4)
                die("Need id to delete.");

            Database_delete(conn, id);
            Database_write(conn);
            break;

        case 'l':
            Database_list(conn);
            break;
        default:
            die("Invalid action: c=create, g=get, s=set, d=del, l=list");
    }

    Database_close(conn);

    return 0;
}
