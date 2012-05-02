#include <iostream>
#include <sstream>
#include <stdexcept>
#include <errno.h>

extern "C"
{
#include "libdaemond.h"
};
#include "io_wrapper.h"
#include "strings_manip.h"

using namespace std;

const string mode_default = "1";
const string pidfile_default = "./libdaemond.pid";
const int children_count_default = 1;


void usage(const char *me)
{
  cout
    << "This is testsuite for \"libdaemond\" library" << endl
    << "Usage: " << me << " [Options] [-- CLI]" << endl
    << "Options are:" << endl
    << "  -C - child processes count, default " << children_count_default << endl
    << "  -I - use internal CLI" << endl
    << "  -N - no detach" << endl
    << "  -P - PID file, not used if empty, default \"" << pidfile_default << "\"" << endl
    << "  -T - reset tracers with b/w standard stream (controlled by \"-o\" option)" << endl
    << "  -i - input, default stdin, persistent file recommended in detach mode" << endl
    << "  -m - mode (test name), default " << mode_default << ":" << endl
    << "    1 - test_standard([-CINPio])" << endl
    << "    L - test_daemond_pid_lock()" << endl
    << "    W - test_daemond_pid_write()" << endl
    << "    R - test_daemond_pid_relock()" << endl
    << "  -o - output, default stdout" << endl
    << "  -h - print this help and exit" << endl
    << "CLI - command line interface for \"libdaemond\" functions, currently:" << endl
    << "  \"start\", \"stop\", \"restart\" or \"check\"," << endl
    << "  use only with \"-I\" option in mode \"" << mode_default << "\"" << endl
  ;
}

string _G_pidfile = pidfile_default;
IOWrapper _G_io;
int _G_children_count = children_count_default;
bool _G_detach = true;
bool _G_cli = false;

void bw_console_tracer(const char * fmt, va_list va_args)
{
  ostream &os = _G_io;
  const char *fmt_prev = fmt;
  const char *fmt_begin;
  string fmt_clean;

  while ((fmt_begin = strchr(fmt_prev, '<')))
  {
    const char *fmt_end;
    if ((fmt_end = strchr(fmt_begin, '>')))
    {
      fmt_clean.append(fmt_prev, fmt_begin);
      fmt_prev = ++ fmt_end;
    }
    else
    {
      fmt_clean.append(fmt_prev, fmt_begin + 1);
      fmt_prev = fmt_begin + 1;
    }
  }
  fmt_clean.append(fmt_prev);

  const size_t buff_size = 1024;
  char buff[buff_size];
  const int res = vsnprintf(buff, buff_size, fmt_clean.c_str(), va_args);
  if (res > 0 && res <= static_cast<int>(buff_size))
  {
    os << buff;
    os.flush();
  }
  else if (res)
  {
    cerr
      << "*** \"vsnprintf\" failed" << endl
    ;
  }
  return;
}

ostream &operator << (ostream &os, const daemond_pid &d)
{
  os << '{';
  bool delimiter = false;
  if (d.pidfile)
  {
    os << '\"' << d.pidfile << '\"';
    delimiter = true;
  }
  if (d.locked)
  {
    if (delimiter)
    {
      os << ", ";
    }
    os << "locked";
    delimiter = true;
  }
  if (d.owner)
  {
    if (delimiter)
    {
      os << ", ";
    }
    os << "owner = " << d.owner;
    delimiter = true;
  }
  if (d.oldpid)
  {
    if (delimiter)
    {
      os << ", ";
    }
    os << "oldpid = " << d.oldpid;
    delimiter = true;
  }
  if (d.fd)
  {
    if (delimiter)
    {
      os << ", ";
    }
    os << "fd = " << d.fd;
    delimiter = true;
  }
  if (d.handle)
  {
    if (delimiter)
    {
      os << ", ";
    }
    os << "FILE*";
    delimiter = true;
  }
  if (d.verbose)
  {
    if (delimiter)
    {
      os << ", ";
    }
    os << "verbose";
    delimiter = true;
  }
  os << '}';
  return os;
}

void suspend()
{
  if (kill(getpid(), SIGSTOP))
  {
    const int errno_copy = errno;
    ostringstream ostr;
    ostr << "\"kill\" failed, " << errno_copy << ", " << strerror(errno_copy);
    throw runtime_error(ostr.str());
  }
}

void test_standard(int argc, char **argv)
{
  ostream &os = _G_io;
  daemond d;
  daemond_init(&d);

  d.name = "sample";
  d.detach = _G_detach;
  d.children_count = _G_children_count;
  d.pid.verbose = 1;
  d.use_pid = !_G_pidfile.empty();
  d.pid.pidfile = _G_pidfile.empty() ? NULL : _G_pidfile.c_str();

  if (_G_cli)
  {
    daemond_cli_run(&d.cli, argc, argv);
  }
  else if (d.use_pid && !daemond_pid_lock(&d.pid))
  {
    throw runtime_error("PID file locking failed");
  }

  os
    << getpid() << " daemond_daemonize..." << endl
  ;
  daemond_daemonize(&d);
  os
    << getpid() << " daemond_master..." << endl
  ;
  daemond_master(&d);

  while (true)
  {
    os
      << getpid() << " child iteration" << endl
    ;
    sleep(3);
  }

  os
    << getpid() << " child finished" << endl
  ;
}

void test_daemond_pid_lock()
{
  daemond_pid d;
  bzero(&d, sizeof(daemond_pid));

  d.pidfile = _G_pidfile.c_str();
  const int res = daemond_pid_lock(&d);

  cout
    << "daemond_pid = " << d << endl
  ;

  if (!res)
  {
    throw runtime_error("PID file locking failed");
  }
  suspend();
}

void test_daemond_pid_write()
{
  daemond_pid d;
  bzero(&d, sizeof(daemond_pid));

  d.pidfile = _G_pidfile.c_str();
  const int res = daemond_pid_lock(&d);
  cout
    << "before write: daemond_pid = " << d << endl
  ;
  if (!res)
  {
    throw runtime_error("PID file locking failed");
  }
  daemond_pid_write(&d);
  cout
    << "after write: daemond_pid = " << d << endl
  ;
  suspend();
}

void test_daemond_pid_relock()
{
  daemond_pid d;
  bzero(&d, sizeof(daemond_pid));

  d.pidfile = _G_pidfile.c_str();
  const int res = daemond_pid_lock(&d);
  cout
    << "before relock: daemond_pid = " << d << endl
  ;
  if (!res)
  {
    throw runtime_error("PID file locking failed");
  }
  daemond_pid_relock(&d);
  cout
    << "after relock: daemond_pid = " << d << endl
  ;
  suspend();
}

int main(int argc, char *argv[])
{
  int ret_val = EXIT_FAILURE;
  string mode = mode_default;
  char ch;

  try
  {
    while ((ch = getopt(argc, argv, "C:INP:Ti:m:o:h")) != -1)
    {
      switch (ch)
      {
        case 'C':
          _G_children_count = c_string_to_uint(optarg);
          break;
        case 'I':
          _G_cli = true;
          break;
        case 'N':
          _G_detach = false;
          break;
        case 'P':
          _G_pidfile = optarg;
          break;
        case 'T':
          set_tracer(bw_console_tracer);
          set_tracer_debug(bw_console_tracer);
          break;
        case 'i':
          _G_io.set_input(optarg);
          break;
        case 'm':
          mode = optarg;
          break;
        case 'o':
          _G_io.set_output(optarg);
          break;
        case 'h':
        case '?':
        default:
          usage(argv[0]);
          return ret_val;
      }
    }

    if (mode == "1")
    {
      test_standard(argc - optind, &argv[optind]);
    }
    else if (mode == "L")
    {
      test_daemond_pid_lock();
    }
    else if (mode == "W")
    {
      test_daemond_pid_write();
    }
    else if (mode == "R")
    {
      test_daemond_pid_relock();
    }
    else
    {
      ostringstream ostr;
      ostr << "Mode \"" << mode << "\" invalid";
      throw runtime_error(ostr.str());
    }
    ret_val = EXIT_SUCCESS;
  }
  catch (const runtime_error &rerr)
  {
    cerr
      << "*** std::runtime_error! " << rerr.what() << endl
    ;
  }
  catch (const logic_error &lerr)
  {
    cerr
      << "*** std::logic_error! " << lerr.what() << endl
    ;
  }
  catch (const exception &ex)
  {
    cerr
      << "*** std::exception! " << ex.what() << endl
    ;
  }
  catch (...)
  {
    cerr
      << "*** Fatal! Uncaught exception" << endl
    ;
  }
  return ret_val;
}
