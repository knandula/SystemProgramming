#define TRUE 1
#define FALSE !TRUE

static pid_t processid;
static pid_t parentPID;
static int shellbash;
static struct termios bashmodes;

static char* currentDirectory;
extern char** environ;

struct sigaction act_child;
struct sigaction act_int;

int no_reprint_prmpt;

pid_t pid;

void signalHandler_child(int p);
void signalHandler_int(int p);

int changeDirectory(char * args[]);
