#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int sys_fork(void)
{
  return fork();
}

int sys_exit(void)
{
  exit();
  return 0; // not reached
}

int sys_wait(void)
{
  return wait();
}

int sys_kill(void)
{
  int pid;

  if (argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int sys_getpid(void)
{
  return myproc()->pid;
}

int sys_sbrk(void)
{
  int addr;
  int n;

  if (argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if (growproc(n) < 0)
    return -1;
  return addr;
}

int sys_sleep(void)
{
  int n;
  uint ticks0;

  if (argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while (ticks - ticks0 < n)
  {
    if (myproc()->killed)
    {
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int sys_uniq(void)
{
  cprintf("Uniq command is getting executed in kernel mode\n");

  char *option = "0";
  char *buffer = "0";
  int charcount = 0;

  argstr(0, &option);
  argint(1, &charcount);
  argstr(2, &buffer);

  // cprintf("%s\n", option);
  // cprintf("%d\n", charcount);
  // cprintf("%s\n", buffer);
  char current_line[512] = "";
  char prev_line[512] = "";
  int c = 0;
  int count = 1;
  for (int i = 0; i < charcount; i++)
  {
    if (buffer[i] == '\n')
    {
      current_line[c] = '\0';
      if (strncmp(current_line, prev_line, 512) != 0)
      {
        if (option[0] == 'i')
        {
          char prev_line_lowercase[512] = "";
          char curr_line_lowercase[512] = "";
          strncpy(curr_line_lowercase, current_line, 512);
          strncpy(prev_line_lowercase, prev_line, 512);
          for (int i = 0; i < strlen(curr_line_lowercase); ++i)
          {
            if (curr_line_lowercase[i] >= 'A' && curr_line_lowercase[i] <= 'Z')
            {
              curr_line_lowercase[i] = 'a' + (curr_line_lowercase[i] - 'A');
            }
          }

          for (int i = 0; i < strlen(prev_line_lowercase); ++i)
          {
            if (prev_line_lowercase[i] >= 'A' && prev_line_lowercase[i] <= 'Z')
            {
              prev_line_lowercase[i] = 'a' + (prev_line_lowercase[i] - 'A');
            }
          }

          if (strncmp(curr_line_lowercase, prev_line_lowercase, 512) != 0)
          {
            if (strlen(prev_line) > 1)
            {
              cprintf("%s\n", prev_line);
              count = 1;
            }
          }
          else
          {
            count++;
          }
        }
        else if (strlen(prev_line) > 1)
        {
          if (option[0] == 'c')
          {
            cprintf("%d %s\n", count, prev_line);
          }
          else if (option[0] == 'd')
          {
            if (count > 1)
            {
              cprintf("%s\n", prev_line);
            }
          }
          else
          {
            cprintf("%s\n", prev_line);
          }
          count = 1;
        }
      }
      else
      {
        count++;
      }

      strncpy(prev_line, current_line, 512);
      memset(current_line, 0, sizeof(current_line));
      c = 0;
    }
    else
    {
      current_line[c++] = buffer[i];
    }
  }
  if (option[0] == 'c')
  {
    cprintf("%d %s\n", count, prev_line);
  }
  else if (option[0] == 'd')
  {
    if (count > 1)
    {
      cprintf("%s\n", prev_line);
    }
  }
  else
  {
    cprintf("%s\n", prev_line);
  }

  return 0;
}

int sys_head(void)
{
  cprintf("Head command is getting executed in kernel mode\n");

  int printcount = 0;
  char *buffer = "0";
  int charcount = 0;

  argint(0, &printcount);
  argint(1, &charcount);
  argstr(2, &buffer);

  int line_count = 0;
  char current_line[512] = "";
  int a = 0;
  for (int i = 0; i < charcount; i++)
  {
    current_line[a++] = buffer[i];
    if (buffer[i] == '\n')
    {
      cprintf("%s", current_line);
      strncpy(current_line, "", 512);
      a = 0;
      if (++line_count >= printcount)
      {
        break;
      }
    }
  }

  return 0;
}
