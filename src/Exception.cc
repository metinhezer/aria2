/* <!-- copyright */
/*
 * aria2 - The high speed download utility
 *
 * Copyright (C) 2006 Tatsuhiro Tsujikawa
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so.  If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source
 * files in the program, then also delete it here.
 */
/* copyright --> */
#include "Exception.h"

#include <sstream>

namespace aria2 {

Exception::Exception(const char* file, int line, const std::string& msg):
  _file(file), _line(line), _msg(msg) {}

Exception::Exception(const char* file, int line, const std::string& msg,
		     const Exception& cause):
  _file(file), _line(line), _msg(msg), _cause(cause.copy()) {}

Exception::Exception(const char* file, int line, const Exception& e):
  _file(file), _line(line), _msg(e._msg), _cause(e._cause)
{}

Exception::~Exception() throw() {}

const char* Exception::what() const throw()
{
  return _msg.c_str();
}

std::string Exception::stackTrace() const throw()
{
  std::stringstream s;
  s << "Exception: " << "[" << _file << ":" << _line << "] " << what() << "\n";
  SharedHandle<Exception> e = _cause;
  while(!e.isNull()) {
    s << "  -> " << "[" << e->_file << ":" << e->_line << "] "
      << e->what() << "\n";
    e = e->_cause;
  }
  return s.str();
}

} // namespace aria2
