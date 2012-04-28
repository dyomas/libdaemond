
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

typedef struct space_splitter
{
  static inline bool field_predicate (char arg)
  {
    return !isspace(arg);
  }

  static inline bool delimiter_predicate (char arg)
  {
    return isspace(arg) != 0;
  }
};

template<char D> struct char_splitter
{
  static inline bool field_predicate (char arg)
  {
    return arg != D;
  }

  static inline bool delimiter_predicate (char arg)
  {
    return arg == D;
  }
};

/**
Деление строки на фрагменты. Контейнер T должен иметь методы insert и end -- вставка фрагмента строки производится в конец контейнера. S должен иметь пару предикатов field_predicate и delimiter_predicate, обнаруживающих начало нового фрагмента строки и начало разделителя соответственно
*/
template <typename T, typename S> void split_string(T &, const string &);
template <typename T, typename S> void split_string_unique(T &, const string &);

/**
Деление строки на фрагменты по одному фрагменту за итерацию. Память для хранения результата, как в split_string не требуется
*/
bool parse_string(const char *&/*begin*/, const char *&/*end*/, const char */*src*/, const char /*delimiter*/);
bool parse_string(const char *&/*begin*/, const char *&/*end*/, const char */*src*/, const char */*src_end*/, const char /*delimiter*/);
/**
Деление строки на фрагменты с объединением последовательных разделителей.
Разделителями являются непечатаемые символы (пробел, табуляция и т. д.).
Экранирование разделителей не учитывается
*/
bool parse_string(const char *&/*begin*/, const char *&/*end*/, const char */*src*/);
bool parse_string(const char *&/*begin*/, const char *&/*end*/, const char */*src*/, const char */*src_end*/);

void hex_to_array(uint8_t *, size_t &, const char *);
void array_to_hex(char *, const uint8_t *, const size_t, const bool /*capitals*/ = false);

const string cut_spaces(const char *);

void replace_chars(string &, const char /*from*/, const char /*to*/);
bool is_number(const char *);
bool is_number(const string &);

//TODO Необходимо контроллировать переполнение при преобразовании к целому, а также гарантировать непреодолимость правой границы буфера (функции strtol[l] могут выйти за эту границу при отстутствии нулевого байта)
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

//TODO Приведение регистра требуется с учетом кодировки
void to_lower_case(string &);
void to_lower_case(string &, const char *);
void to_upper_case(string &);
void to_upper_case(string &, const char *);

const string shade_cstyle(const char *src, const size_t length);
const string shade_cstyle(const string &);

#endif //__strings_manip_h__
