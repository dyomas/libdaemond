#ifndef __io_wrapper_h__
#define __io_wrapper_h__

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

/**
Оболочка над потоками ввода-вывода.
Возвращает потоки через перегруженные операторы преобразования типа.
По умолчанию возвращает cin/cout.
Если через методы set_ указаны имена файлов, которые необходимо использовать для ввода/вывода, возвращает ссылки на открытые файлы.
Имена файлов '-', "/dev/std(in|out)" означают стандартные потоки ввода/вывода.
Исключения вызываются, если при открытии файла произошла ошибка или если обязательный файл не задан
*/
class IOWrapper
{
  const bool
      m_ifs_required
    , m_ofs_required
  ;
  ifstream m_ifs;
  ofstream m_ofs;

  public:
    operator istream &();
    operator ostream &();

    void validate() const;
    bool is_valid() const;

    void set_input(const string &/*_path*/);
    void set_output(const string &/*_path*/);

    IOWrapper(const bool /*ifs_required*/ = false, const bool /*ofs_required*/ = false);
};

#endif //__io_wrapper_h__

