#define _XOPEN_SOURCE 600
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "print_err_if/print_err_if.h"
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <termios.h>
#include <unistd.h>

#include <sys/select.h>
#include <sys/ioctl.h>

#include <signal.h>

#define TTYNAME_MAX_LEN 256
#define BUF_SIZE 256

void slaveProcess(int fd, int argc, char** argv) {
  // Save terminal settings
  struct termios slave_settings_old; 
  // New terminal settings
  struct termios slave_settings;
  if (PRINT_ERRNO_IF(tcgetattr(fd, &slave_settings_old) != 0,
    "tcgetattr failed"))
    exit(EXIT_FAILURE);

  // Set RAW mode on slave side of PTY
  slave_settings = slave_settings_old;
  cfmakeraw(&slave_settings);
  if (PRINT_ERRNO_IF(tcsetattr(fd, TCSANOW, &slave_settings) != 0,
    "tcsetattr failed"))
    exit(EXIT_FAILURE);
  
  // Set slave side of PTY the standard input and output of the process
  if (PRINT_ERRNO_IF(close(STDIN_FILENO) != 0,
    "close failed"))
    exit(EXIT_FAILURE);
  if (PRINT_ERRNO_IF(close(STDOUT_FILENO) != 0,
    "close failed"))
    exit(EXIT_FAILURE);
  if (PRINT_ERRNO_IF(close(STDERR_FILENO) != 0,
    "close failed"))
    exit(EXIT_FAILURE);
  if (PRINT_ERRNO_IF(dup(fd) == -1, // PTY become STDIN
    "dup failed"))
    exit(EXIT_FAILURE);
  if (PRINT_ERRNO_IF(dup(fd) == -1, // PTY become STDOUT
    "dup failed"))
    exit(EXIT_FAILURE);
  if (PRINT_ERRNO_IF(dup(fd) == -1, // PTY become STDERR
    "dup failed"))
    exit(EXIT_FAILURE);
  
  // Close original fd which is become useless.
  if (PRINT_ERRNO_IF(close(fd) != 0,
    "close failed"))
    exit(EXIT_FAILURE);

  // Run process in a new session
  if (PRINT_ERRNO_IF(setsid() == (pid_t) -1,
    "Failed to create new session"))
    exit(EXIT_FAILURE);
  // Process is a session leader.
  // Set controlling terminal to the slave side of the PTY
  if (PRINT_ERRNO_IF(ioctl(STDIN_FILENO, TIOCSCTTY, STDOUT_FILENO) == -1,
    "Failed to switch on slave side of PTY"))
    exit(EXIT_FAILURE);
  
  // Execute the program
  
  char** child_argv = malloc((argc + 1) * sizeof(char*));
  for (int i = 0; i < argc; ++i) {
    if (PRINT_ERRNO_IF((child_argv[i] = strdup(argv[i])) == NULL,
      "strdup failed")) {
      free(child_argv);
      exit(EXIT_FAILURE);
    }
  }
  child_argv[argc] = NULL;
  if (PRINT_ERRNO_IF(execvp(child_argv[0], child_argv) == -1,
    "Failed execvp")) {
    free(child_argv);
    exit(EXIT_FAILURE);
  }
  // To be sure ;-)
  exit(EXIT_FAILURE);
}

/*
 * Read BUF_SIZE data max from fdin
 * and write it on fdout
 * @return nb bytes read/write on success -1 on error
 */
int forwardData(int fdin, int fdout) {
  char buf[BUF_SIZE];
  int rc;
  // Read data on fdin
  if (PRINT_ERRNO_IF((rc = read(fdin, buf, sizeof(buf))) < 0,
    "Read on fdin failed")) 
    return -1;
  if (rc > 0) {
    // Write data on fdout
    if (PRINT_ERRNO_IF(write(fdout, buf, rc) < 0,
      "Write on fdout failed"))
      return -1;
  }
  return rc;
}

void masterProcess(int fd) {
  fd_set set;
  while(1) {
    // Build set of file descriptors
    // With stdin and fd (master side of pty)
    FD_ZERO(&set);
    FD_SET(STDIN_FILENO, &set);
    FD_SET(fd, &set);
    
    if (PRINT_ERRNO_IF(select(fd+2, &set, NULL, NULL, NULL) == -1,
      "Error on select")) 
      exit(EXIT_FAILURE);
    
    if (FD_ISSET(STDIN_FILENO, &set)) { // data on stdin
      if (PRINT_ERR_IF(forwardData(STDIN_FILENO, fd) < 0,
        "Fail forward data from stdin to master side of PTY"))
        exit(EXIT_FAILURE);
    }
    if (FD_ISSET(fd, &set)) { // data on master side of pty
      if (PRINT_ERR_IF(forwardData(fd, STDOUT_FILENO) < 0,
        "Fail forward data from master side of PTY to stdout"))
        exit(EXIT_FAILURE);
    }
  }
}

void sigCHLDhandler(int signum) {
  // On termine le processus pere quand le fils meurt.
  exit(EXIT_SUCCESS);
}

int main(int argc, char** argv) {
  // Handle SIGCHLD signal to exit father process on child death
  struct sigaction sig;
  sig.sa_handler = &sigCHLDhandler;
  if (PRINT_ERRNO_IF(sigaction(SIGCHLD, &sig, NULL) != 0,
    "sigaction failed")) 
    exit(EXIT_FAILURE);
  
  int fd_master, fd_slave;
  if (argc <= 1) {
    fprintf(stderr, "Usage %s program [args]\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  // Open pseudo terminal
  if (PRINT_ERRNO_IF((fd_master = posix_openpt(O_RDWR)) < 0,
    "Error open pseudo terminal"))
    exit(EXIT_FAILURE);
  // Change mode and owner of the slave pt of master pt
  if (PRINT_ERRNO_IF(grantpt(fd_master) != 0, "grantpt"))
    exit(EXIT_FAILURE);
  // unlock slave pt of df_master
  if (PRINT_ERRNO_IF(unlockpt(fd_master) != 0,
    "Unlock slave pseudo terminal"))
    exit(EXIT_FAILURE);
  // Get name of tty
  //*
  char ttyname[TTYNAME_MAX_LEN];
  if (PRINT_ERRNO_IF(ptsname_r(fd_master, ttyname, TTYNAME_MAX_LEN),
    "Get name of pseudo terminal")) 
    exit(EXIT_FAILURE);
  // Open slave side of master pt
  if (PRINT_ERRNO_IF((fd_slave = open(ttyname, O_RDWR)) == -1,
    "Open slave pseudo terminal"))
    exit(EXIT_FAILURE);
  /*/
  if (PRINT_ERRNO_IF((fd_slave = open(ptsname(fd_master), O_RDWR)) == -1,
    "Open slave pseudo terminal"))
    exit(EXIT_FAILURE);

  //*/

  switch(fork()) {
    case -1: // Error
      PRINT_ERRNO_IF(1 == 1, "fork failed");
      exit(EXIT_FAILURE);
    case 0:  // Child
      if (PRINT_ERRNO_IF(close(fd_master) != 0,
        "Close master pts"))
        exit(EXIT_FAILURE);
      slaveProcess(fd_slave, argc - 1, argv + 1);
      break;
    default: // parent
      if (PRINT_ERRNO_IF(close(fd_slave) != 0,
        "Close slave pts"))
        exit(EXIT_FAILURE);
      masterProcess(fd_master);
      break;
  }

  return EXIT_FAILURE;
}

