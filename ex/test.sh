#!/bin/sh

# Writing a fully self-contained test is too complicated task (at least I think so),
# therefore satisfy with a small manual test or use executable file with
# a variety of options directly to ensure efficiency of library

set -e

readonly EXECUTABLE_DEFAULT="sample"
readonly MODE_DEFAULT="N"
readonly PID_FILE="./sample.pid"

EXECUTABLE=$EXECUTABLE_DEFAULT
MODE=$MODE_DEFAULT
EXIT=0
USAGE=0
VERBOSE=0

usage () {
  echo "Manual test launcher for daemon sample"
  echo "Usage: `basename $0` [options]"
  echo "Options are:"
  echo "  -E - path to sample executable, default \"$EXECUTABLE_DEFAULT\""
  echo "       usually it places in CMAKE_BINARY_DIR (see cmake(1))"
  echo "  -m - mode, one of the following, default \"$MODE_DEFAULT\""
  echo "    $MODE_DEFAULT - run daemon in detach mode with single child"
  echo "    A - 2 children call abort(3) every 3 seconds, no detach"
  echo "    X - 2 children throws unhandled exception every 3 seconds, no detach"
  echo "    E - 2 children call exit(3) directly every 3 seconds, no detach"
  echo "    S - 2 children provokes signal \"SIGSEGV\" every 3 seconds, no detach"
  echo "    C - check state using PID file ($PID_FILE)"
  echo "    L - two processes try lock same PID file ($PID_FILE)"
  echo "    W - two processes try rewrite same PID file ($PID_FILE)"
  echo "    R - two processes try relock same PID file ($PID_FILE)"
  echo "  -v - show diagnostic messages"
  echo "  -vv - show diagnostic messages and set -x"
  echo "  -h - show help message and exit"
}

while getopts E:m:vh Option; do
  case $Option in
    E) EXECUTABLE=$OPTARG
    ;;
    m) MODE=$OPTARG
    ;;
    v)
      VERBOSE=$((VERBOSE + 1))
    ;;
    h) USAGE=1
    ;;
    *)
      USAGE=1
      EXIT=1
    ;;
  esac
done

if [ $USAGE -ne 0 ];
then
  usage
  exit $EXIT
fi

#Arguments checking
if [ -z "$EXECUTABLE" ] || ! [ -f "$EXECUTABLE" ] || ! [ -e "$EXECUTABLE" ];
then
  echo "*** Executable file \"$EXECUTABLE\" invalid" >&2
  EXIT=1
fi

if [ -z "$MODE" ];
then
  echo "*** Mode not set" >&2
  EXIT=1
elif [ "$MODE" != "$MODE_DEFAULT" ] && [ "$MODE" != "A" ] && [ "$MODE" != "X" ] && [ "$MODE" != "E" ] && [ "$MODE" != "S" ] && [ "$MODE" != "C" ] && [ "$MODE" != "L" ] && [ "$MODE" != "W" ] && [ "$MODE" != "R" ];
then
  echo "*** Mode \"$MODE\" invalid" >&2
  EXIT=1
fi

if [ $EXIT -ne 0 ];
then
  exit $EXIT
fi

if [ $VERBOSE -gt 1 ];
then
  set -x
fi

if [ $VERBOSE -ne 0 ];
then
  echo "EXECUTABLE = \"$EXECUTABLE\""
  echo "MODE = \"$MODE\""
fi


#The actual commands
if [ "$MODE" = "$MODE_DEFAULT" ];
then
  $EXECUTABLE -C1 -L3 -P $PID_FILE -- start

elif [ "$MODE" = "A" ];
then
  $EXECUTABLE -C2 -L3 -N -P $PID_FILE -xabort -- start

elif [ "$MODE" = "X" ];
then
  $EXECUTABLE -C2 -L3 -N -P $PID_FILE -xexcept -- start

elif [ "$MODE" = "E" ];
then
  $EXECUTABLE -C2 -L3 -N -P $PID_FILE -xexit -- start

elif [ "$MODE" = "S" ];
then
  $EXECUTABLE -C2 -L3 -N -P $PID_FILE -xsf -- start

elif [ "$MODE" = "C" ];
then
  $EXECUTABLE -N -P $PID_FILE -- check

elif [ "$MODE" = "L" ];
then
  $EXECUTABLE -P $PID_FILE -mL &
  $EXECUTABLE -P $PID_FILE -mL &

elif [ "$MODE" = "W" ];
then
  $EXECUTABLE -P $PID_FILE -mL &
  $EXECUTABLE -P $PID_FILE -mW &

elif [ "$MODE" = "R" ];
then
  $EXECUTABLE -P $PID_FILE -mL &
  $EXECUTABLE -P $PID_FILE -mR &

fi


if [ "$MODE" = "$MODE_DEFAULT" ] || [ "$MODE" = "L" ] || [ "$MODE" = "W" ] || [ "$MODE" = "R" ];
then
  COMM=`basename $EXECUTABLE`
  PIDS=`ps -ax -o 'pid,comm' | awk 'BEGIN{cnt = 0}{if ($2 == "'$COMM'"){cnt += 1; pids = pids " " $1}} END {if (cnt == 2){print pids} else {exit 1}}'` && {
    echo "Watch PIDs $PIDS"
  } || {
    echo "*** Error. Processes count differs from 2" >&2
  }
fi
