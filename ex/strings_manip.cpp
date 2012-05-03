#include "strings_manip.h"
#include <errno.h>
#include <vis.h>

int8_t c_string_to_int8(const char *src)
{
  const char *errstr;
  int8_t res = strtonum(src, -128, 127, &errstr);
  int errno_copy = errno;

  if (errstr)
  {
    ostringstream ostr;
    ostr << "Conversion failed from string \"" << src << "\" to int8_t (";
    if (errno_copy)
    {
      ostr << errno_copy << ", ";
    }
    ostr << errstr << ")";
    throw runtime_error(ostr.str());
  }
  return res;
}

uint8_t c_string_to_uint8(const char *src)
{
  const char *errstr;
  uint8_t res = strtonum(src, 0, 255LL, &errstr);
  int errno_copy = errno;

  if (errstr)
  {
    ostringstream ostr;
    ostr << "Conversion failed from string \"" << src << "\" to uint8_t (";
    if (errno_copy)
    {
      ostr << errno_copy << ", ";
    }
    ostr << errstr << ")";
    throw runtime_error(ostr.str());
  }
  return res;
}

int16_t c_string_to_int16(const char *src)
{
  const char *errstr;
  int16_t res = strtonum(src, -32768LL, 32767LL, &errstr);
  int errno_copy = errno;

  if (errstr)
  {
    ostringstream ostr;
    ostr << "Conversion failed from string \"" << src << "\" to int16_t (";
    if (errno_copy)
    {
      ostr << errno_copy << ", ";
    }
    ostr << errstr << ")";
    throw runtime_error(ostr.str());
  }
  return res;
}

uint16_t c_string_to_uint16(const char *src)
{
  const char *errstr;
  uint16_t res = strtonum(src, 0, 0xffffLL, &errstr);
  int errno_copy = errno;

  if (errstr)
  {
    ostringstream ostr;
    ostr << "Conversion failed from string \"" << src << "\" to uint16_t (";
    if (errno_copy)
    {
      ostr << errno_copy << ", ";
    }
    ostr << errstr << ")";
    throw runtime_error(ostr.str());
  }
  return res;
}

int32_t c_string_to_int(const char *src)
{
  char *endptr;
  int32_t res = strtol(src, &endptr, 10);
  int errno_copy = errno;

  if (*endptr)
  {
    ostringstream ostr;
    ostr << "Conversion failed from string \"" << src << "\" to int";
    if (errno_copy)
    {
      ostr << " (" << errno_copy << ", " << strerror(errno_copy) << ")";
    }
    throw runtime_error(ostr.str());
  }
  return res;
}

int32_t string_to_int(const char *begin, const char *end)
{
  char *endptr;
  int32_t res = strtol(begin, &endptr, 10);
  int errno_copy = errno;

  if (endptr != end)
  {
    ostringstream ostr;
    ostr << "Conversion failed from string \"" << string(begin, end) << "\" to int";
    if (errno_copy)
    {
      ostr << " (" << errno_copy << ", " << strerror(errno_copy) << ")";
    }
    throw runtime_error(ostr.str());
  }
  return res;
}

int32_t string_to_int(const string &src)
{
  char *endptr;
  int32_t res = strtol(src.c_str(), &endptr, 10);
  int errno_copy = errno;

  if (*endptr)
  {
    ostringstream ostr;
    ostr << "Conversion failed from string \"" << src << "\" to int";
    if (errno_copy)
    {
      ostr << " (" << errno_copy << ", " << strerror(errno_copy) << ")";
    }
    throw runtime_error(ostr.str());
  }
  return res;
}

uint32_t c_string_to_uint(const char *src)
{
  const char *errstr;
  uint32_t res = strtonum(src, 0, 0xffffffffLL, &errstr);
  int errno_copy = errno;

  if (errstr)
  {
    ostringstream ostr;
    ostr << "Conversion failed from string \"" << src << "\" to uint32_t (";
    if (errno_copy)
    {
      ostr << errno_copy << ", ";
    }
    ostr << errstr << ")";
    throw runtime_error(ostr.str());
  }
  return res;
}

int64_t c_string_to_int64(const char *src)
{
  char *endptr;
  int64_t res = strtoll(src, &endptr, 10);
  int errno_copy = errno;

  if (*endptr)
  {
    ostringstream ostr;
    ostr << "Conversion failed from string \"" << src << "\" to int64_t";
    if (errno_copy)
    {
      ostr << " (" << errno_copy << ", " << strerror(errno_copy) << ")";
    }
    throw runtime_error(ostr.str());
  }
  return res;
}

int64_t string_to_int64(const char *begin, const char *end)
{
  char *endptr;
  int64_t res = strtoll(begin, &endptr, 10);
  int errno_copy = errno;

  if (endptr != end)
  {
    ostringstream ostr;
    ostr << "Conversion failed from string \"" << string(begin, end) << "\" to int64_t";
    if (errno_copy)
    {
      ostr << " (" << errno_copy << ", " << strerror(errno_copy) << ")";
    }
    throw runtime_error(ostr.str());
  }
  return res;
}

int64_t string_to_int64(const string &src)
{
  char *endptr;
  int64_t res = strtoll(src.c_str(), &endptr, 10);
  int errno_copy = errno;

  if (*endptr)
  {
    ostringstream ostr;
    ostr << "Conversion failed from string \"" << src << "\" to int64_t";
    if (errno_copy)
    {
      ostr << " (" << errno_copy << ", " << strerror(errno_copy) << ")";
    }
    throw runtime_error(ostr.str());
  }
  return res;
}

uint64_t c_string_to_uint64(const char *src)
{
  const char *errstr;
  uint64_t res = strtonum(src, 0, 0x7fffffffffffffffLL, &errstr);
  int errno_copy = errno;

  if (errstr)
  {
    ostringstream ostr;
    ostr << "Conversion failed from string \"" << src << "\" to uint64_t (";
    if (errno_copy)
    {
      ostr << errno_copy << ", ";
    }
    ostr << errstr << ")";
    throw runtime_error(ostr.str());
  }
  return res;
}

float c_string_to_float(const char *src)
{
  char *endptr;
  float res = strtof(src, &endptr);
  int errno_copy = errno;

  if (*endptr)
  {
    ostringstream ostr;
    ostr << "Conversion failed from string \"" << src << "\" to float";
    if (errno_copy)
    {
      ostr << " (" << errno_copy << ", " << strerror(errno_copy) << ")";
    }
    throw runtime_error(ostr.str());
  }
  return res;
}

double c_string_to_double(const char *src)
{
  char *endptr;
  double res = strtod(src, &endptr);
  int errno_copy = errno;

  if (*endptr)
  {
    ostringstream ostr;
    ostr << "Conversion failed from string \"" << src << "\" to double";
    if (errno_copy)
    {
      ostr << " (" << errno_copy << ", " << strerror(errno_copy) << ")";
    }
    throw runtime_error(ostr.str());
  }
  return res;
}

void string_to_number(int8_t *pres, const string &src)
{
  const char *errstr;
  *pres = strtonum(src.c_str(), -128, 127, &errstr);
  int errno_copy = errno;

  if (errstr)
  {
    ostringstream ostr;
    ostr << "Conversion failed from string \"" << src << "\" to int8_t (";
    if (errno_copy)
    {
      ostr << errno_copy << ", ";
    }
    ostr << errstr << ")";
    throw runtime_error(ostr.str());
  }
}

void string_to_number(uint8_t *pres, const string &src)
{
  const char *errstr;
  *pres = strtonum(src.c_str(), 0, 255LL, &errstr);
  int errno_copy = errno;

  if (errstr)
  {
    ostringstream ostr;
    ostr << "Conversion failed from string \"" << src << "\" to uint8_t (";
    if (errno_copy)
    {
      ostr << errno_copy << ", ";
    }
    ostr << errstr << ")";
    throw runtime_error(ostr.str());
  }
}

void string_to_number(int16_t *pres, const string &src)
{
  const char *errstr;
  *pres = strtonum(src.c_str(), -32768LL, 32767LL, &errstr);
  int errno_copy = errno;

  if (errstr)
  {
    ostringstream ostr;
    ostr << "Conversion failed from string \"" << src << "\" to int16_t (";
    if (errno_copy)
    {
      ostr << errno_copy << ", ";
    }
    ostr << errstr << ")";
    throw runtime_error(ostr.str());
  }
}

void string_to_number(uint16_t *pres, const string &src)
{
  const char *errstr;
  *pres = strtonum(src.c_str(), 0, 0xffffLL, &errstr);
  int errno_copy = errno;

  if (errstr)
  {
    ostringstream ostr;
    ostr << "Conversion failed from string \"" << src << "\" to uint16_t (";
    if (errno_copy)
    {
      ostr << errno_copy << ", ";
    }
    ostr << errstr << ")";
    throw runtime_error(ostr.str());
  }
}

void string_to_number(int32_t *pres, const string &src)
{
  char *endptr;
  *pres = strtol(src.c_str(), &endptr, 10);
  int errno_copy = errno;

  if (*endptr)
  {
    ostringstream ostr;
    ostr << "Conversion failed from string \"" << src << "\" to int";
    if (errno_copy)
    {
      ostr << " (" << errno_copy << ", " << strerror(errno_copy) << ")";
    }
    throw runtime_error(ostr.str());
  }
}

void string_to_number(uint32_t *pres, const string &src)
{
  const char *errstr;
  *pres = strtonum(src.c_str(), 0, 0xffffffffLL, &errstr);
  int errno_copy = errno;

  if (errstr)
  {
    ostringstream ostr;
    ostr << "Conversion failed from string \"" << src << "\" to uint32_t (";
    if (errno_copy)
    {
      ostr << errno_copy << ", ";
    }
    ostr << errstr << ")";
    throw runtime_error(ostr.str());
  }
}

void string_to_number(int64_t *pres, const string &src)
{
  char *endptr;
  *pres = strtoll(src.c_str(), &endptr, 10);
  int errno_copy = errno;

  if (*endptr)
  {
    ostringstream ostr;
    ostr << "Conversion failed from string \"" << src << "\" to int64_t";
    if (errno_copy)
    {
      ostr << " (" << errno_copy << ", " << strerror(errno_copy) << ")";
    }
    throw runtime_error(ostr.str());
  }
}

void string_to_number(uint64_t *pres, const string &src)
{
  const char *errstr;
  *pres = strtonum(src.c_str(), 0, 0x7fffffffffffffffLL, &errstr);
  int errno_copy = errno;

  if (errstr)
  {
    ostringstream ostr;
    ostr << "Conversion failed from string \"" << src << "\" to uint64_t (";
    if (errno_copy)
    {
      ostr << errno_copy << ", ";
    }
    ostr << errstr << ")";
    throw runtime_error(ostr.str());
  }
}

void string_to_number(float *pres, const string &src)
{
  char *endptr;
  *pres = strtof(src.c_str(), &endptr);
  int errno_copy = errno;

  if (*endptr)
  {
    ostringstream ostr;
    ostr << "Conversion failed from string \"" << src << "\" to float";
    if (errno_copy)
    {
      ostr << " (" << errno_copy << ", " << strerror(errno_copy) << ")";
    }
    throw runtime_error(ostr.str());
  }
}

void string_to_number(double *pres, const string &src)
{
  char *endptr;
  *pres = strtod(src.c_str(), &endptr);
  int errno_copy = errno;

  if (*endptr)
  {
    ostringstream ostr;
    ostr << "Conversion failed from string \"" << src << "\" to double";
    if (errno_copy)
    {
      ostr << " (" << errno_copy << ", " << strerror(errno_copy) << ")";
    }
    throw runtime_error(ostr.str());
  }
}

void string_to_number(int32_t *pres, const char *begin, const char *end)
{
  char *endptr;
  *pres = strtol(begin, &endptr, 10);
  int errno_copy = errno;

  if (endptr != end || errno_copy == ERANGE)
  {
    ostringstream ostr;
    ostr << "Conversion failed from string \"" << string(begin, end) << "\" to int32_t";
    if (errno_copy)
    {
      ostr << " (" << errno_copy << ", " << strerror(errno_copy) << ")";
    }
    throw runtime_error(ostr.str());
  }
}

void string_to_number(int64_t *pres, const char *begin, const char *end)
{
  char *endptr;
  int errno_copy;

  *pres = strtoll(begin, &endptr, 10);
  errno_copy = errno;

  if (endptr != end || errno_copy == ERANGE)
  {
    ostringstream ostr;
    ostr << "Conversion failed from string \"" << string(begin, end) << "\" to int64_t";
    if (errno_copy)
    {
      ostr << " (" << errno_copy << ", " << strerror(errno_copy) << ")";
    }
    throw runtime_error(ostr.str());
  }
}

void string_to_number(float *pres, const char *begin, const char *end)
{
  char *endptr;
  int errno_copy;

  *pres = strtod(begin, &endptr);
  errno_copy = errno;

  if (endptr != end || errno_copy == ERANGE)
  {
    ostringstream ostr;
    ostr << "Conversion failed from string \"" << string(begin, end) << "\" to float";
    if (errno_copy)
    {
      ostr << " (" << errno_copy << ", " << strerror(errno_copy) << ")";
    }
    throw runtime_error(ostr.str());
  }
}

void string_to_number(double *pres, const char *begin, const char *end)
{
  ostringstream ostr;
  char *endptr;
  int errno_copy;

  *pres = strtod(begin, &endptr);
  errno_copy = errno;

  if (endptr != end || errno_copy == ERANGE)
  {
    ostr << "Conversion failed from string \"" << string(begin, end) << "\" to double";
    if (errno_copy)
    {
      ostr << " (" << errno_copy << ", " << strerror(errno_copy) << ")";
    }
    throw runtime_error(ostr.str());
  }
}

void to_lower_case(string &data)
{
  for (string::iterator iter = data.begin(); iter != data.end(); iter ++)
  {
    *iter = tolower(*iter);
  }
}

void to_lower_case(string &res, const char *src)
{
  while (*src)
  {
    res.push_back(tolower(*src ++));
  }
}

void to_upper_case(string &data)
{
  for (string::iterator iter = data.begin(); iter != data.end(); iter ++)
  {
    *iter = toupper(*iter);
  }
}

void to_upper_case(string &res, const char *src)
{
  while (*src)
  {
    res.push_back(toupper(*src ++));
  }
}

const string shade_cstyle(const char *src, const size_t length)
{
  string ret_val;
  ret_val.resize(length * 4);
  const int length_escaped = strvisx (&ret_val[0], src, length, VIS_CSTYLE | VIS_WHITE);
  ret_val.resize(length_escaped > 0 ? length_escaped : 0);
  return ret_val;
}

const string shade_cstyle(const string &src)
{
  string ret_val;
  ret_val.resize(src.length() * 4);
  const int length_escaped = strvisx (&ret_val[0], src.c_str(), src.length(), VIS_CSTYLE | VIS_WHITE);
  ret_val.resize(length_escaped > 0 ? length_escaped : 0);
  return ret_val;
}
