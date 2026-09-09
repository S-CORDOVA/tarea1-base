#include "types.h"
#include "stat.h"
#include "user.h"
#include "param.h"
#include "procinfo.h"

static char*
state_name(int state)
{
  switch(state){
  case PSTATE_UNUSED:
    return "UNUSED";
  case PSTATE_EMBRYO:
    return "EMBRYO";
  case PSTATE_SLEEPING:
    return "SLEEPING";
  case PSTATE_RUNNABLE:
    return "RUNNABLE";
  case PSTATE_RUNNING:
    return "RUNNING";
  case PSTATE_ZOMBIE:
    return "ZOMBIE";
  default:
    return "UNKNOWN";
  }
}

int
main(int argc, char *argv[])
{
  struct procinfo procs[NPROC];
  int n;
  int i;

  n = getprocs(procs, NPROC);

  if(n < 0){
    printf(2, "ps: getprocs failed\n");
    exit();
  }

  printf(1, "PID\tPPID\tSTATE\t\tCPU\tWAIT\tNAME\n");

  for(i = 0; i < n; i++){
    printf(1, "%d\t%d\t%s\t%d\t%d\t%s\n",
           procs[i].pid,
           procs[i].ppid,
           state_name(procs[i].state),
           procs[i].rtime,
           procs[i].wtime,
           procs[i].name);
  }

  exit();
}