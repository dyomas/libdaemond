#include "io_wrapper.h"

IOWrapper::operator istream &()
{
  const ios_base::iostate _ist = m_ifs.rdstate();

  if ((_ist & _S_badbit) || (_ist & _S_failbit))
  {
    throw runtime_error("Input stream has invalid state");
  }
  else if (m_ifs_required & !m_ifs.is_open())
  {
    throw runtime_error("Required input file not open");
  }

  return m_ifs.is_open() ? m_ifs : cin;
}

IOWrapper::operator ostream &()
{
  const ios_base::iostate _ost = m_ofs.rdstate();

  if ((_ost & _S_badbit) || (_ost & _S_failbit))
  {
    throw runtime_error("Output stream has invalid state");
  }
  else if (m_ofs_required & !m_ofs.is_open())
  {
    throw runtime_error("Required output file not open");
  }

  return m_ofs.is_open() ? m_ofs : cout;
}

void IOWrapper::validate() const
{
  const ios_base::iostate
      _ist = m_ifs.rdstate()
    , _ost = m_ofs.rdstate()
  ;
  bool error_occured = false;
  ostringstream ostr;

  if ((_ist & _S_badbit) || (_ist & _S_failbit))
  {
    ostr << "Input stream has invalid state";
    error_occured = true;
  }
  else if (m_ifs_required & !m_ifs.is_open())
  {
    ostr << "Required input file not open";
    error_occured = true;
  }

  if ((_ost & _S_badbit) || (_ost & _S_failbit))
  {
    if (error_occured)
    {
      ostr << "; ";
    }
    ostr << "Output stream has invalid state";
    error_occured = true;
  }
  else if (m_ofs_required & !m_ofs.is_open())
  {
    if (error_occured)
    {
      ostr << "; ";
    }
    ostr << "Required output file not open";
    error_occured = true;
  }

  if (error_occured)
  {
    throw runtime_error(ostr.str());
  }
}

bool IOWrapper::is_valid() const
{
  const ios_base::iostate
      _ist = m_ifs.rdstate()
    , _ost = m_ofs.rdstate()
  ;

  return !(
       _ist & _S_badbit
    || _ist & _S_failbit
    || m_ifs_required & !m_ifs.is_open()
    || _ost & _S_badbit
    || _ost & _S_failbit
    || m_ofs_required & !m_ofs.is_open()
  );
}

void IOWrapper::set_input(const string &_path)
{
  if (_path != "-" && _path != "/dev/stdin")
  {
    m_ifs.open(_path.c_str());
  }
}

void IOWrapper::set_output(const string &_path)
{
  if (_path != "-" && _path != "/dev/stdout")
  {
    m_ofs.open(_path.c_str());
  }
}

IOWrapper::IOWrapper(const bool ifs_required, const bool ofs_required)
  : m_ifs_required(ifs_required)
  , m_ofs_required(ofs_required)
{
}
