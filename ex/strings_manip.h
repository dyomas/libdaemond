
#ifndef __strings_manip_h__
#define __strings_manip_h__

//Наиболее популярные манипуляции со строками, не вошедшие в STL

#include <iostream>
#include <sstream>
#include <vector>
#include <deque>
#include <set>
#include <stdexcept>
#include <iomanip>

using namespace std;

int8_t c_string_to_int8(const char *);
uint8_t c_string_to_uint8(const char *);

int16_t c_string_to_int16(const char *);
uint16_t c_string_to_uint16(const char *);

int32_t c_string_to_int(const char *);
int32_t string_to_int(const char */*begin*/, const char */*end*/);
int32_t string_to_int(const string &);
uint32_t c_string_to_uint(const char *);

int64_t c_string_to_int64(const char *);
int64_t string_to_int64(const char */*begin*/, const char */*end*/);
int64_t string_to_int64(const string &);
uint64_t c_string_to_uint64(const char *);

float c_string_to_float(const char *);
double c_string_to_double(const char *);

//Одноименные перегруженные функции для шаблонных классов
void string_to_number(int8_t */*pres*/, const string &);
void string_to_number(uint8_t */*pres*/, const string &);
void string_to_number(int16_t */*pres*/, const string &);
void string_to_number(uint16_t */*pres*/, const string &);
void string_to_number(int32_t */*pres*/, const string &);
void string_to_number(uint32_t */*pres*/, const string &);
void string_to_number(int64_t */*pres*/, const string &);
void string_to_number(uint64_t */*pres*/, const string &);
void string_to_number(float */*pres*/, const string &);
void string_to_number(double */*pres*/, const string &);
void string_to_number(int32_t */*pres*/, const char */*begin*/, const char */*end*/);
void string_to_number(int64_t */*pres*/, const char */*begin*/, const char */*end*/);
void string_to_number(float */*pres*/, const char */*begin*/, const char */*end*/);
void string_to_number(double */*pres*/, const char */*begin*/, const char */*end*/);

void to_lower_case(string &);
void to_lower_case(string &, const char *);
void to_upper_case(string &);
void to_upper_case(string &, const char *);

const string shade_cstyle(const char *src, const size_t length);
const string shade_cstyle(const string &);

#endif //__strings_manip_h__
