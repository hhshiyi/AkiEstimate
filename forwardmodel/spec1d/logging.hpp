//
//    Spec1D : A spectral element code for surface wave dispersion of Love
//    and Rayleigh waves. See
//
//      R Hawkins, "A spectral element method for surface wave dispersion and adjoints",
//      Geophysical Journal International, 2018, 215:1, 267 - 302
//      https://doi.org/10.1093/gji/ggy277
//    
//    Copyright (C) 2014 - 2018 Rhys Hawkins
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//


#pragma once
#ifndef logging_hpp
#define logging_hpp

#include <stdarg.h>
#include <stdio.h>

#include <iostream>
#include <sstream>

#define FATAL(fmt, ...) logging::fatal::log(__FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define ERROR(fmt, ...) logging::error::log(__FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define WARNING(fmt, ...) logging::warning::log(__FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define INFO(fmt, ...) logging::info::log(__FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)
#define DEBUG(fmt, ...) logging::debug::log(__FILE__, __FUNCTION__, __LINE__, fmt, ##__VA_ARGS__)

#define STATUS(fmt, ...) logging::status::log(fmt, ##__VA_ARGS__)
#define MARK(fmt, ...) logging::status::mark(fmt, ##__VA_ARGS__)

namespace logging {
  
  class fatalexception : public std::exception {
  };
    
  class log {
  public:
    
    static bool set_output(const char *filename);

    static std::string mkformatstring(const char *fmt, ...);
    
  protected:
    
    static void vlog(const char *prefix,
		     const char *sourcefile,
		     const char *function,
		     int lineno,
		     const char *fmt,
		     va_list ap);

    static void vprintf(const char *fmt,
			va_list ap);

    static void mark(const char *fmt,
		     va_list ap);
		     
  private:
    log();

    static const char *timestamp();
    
    static std::string out;
    static std::stringstream tsbuffer;
  };

  class fatal : public log {
  public:
    
    static void log(const char *sourcefile,
		    const char *function,
		    int lineno,
		    const char *fmt,
		    ...)
    {
      va_list ap;

      va_start(ap, fmt);
      log::vlog("fatal", sourcefile, function, lineno, fmt, ap);
      va_end(ap);

      throw fatalexception();
    }
  };
  
  class error : public log {
  public:

    static void log(const char *sourcefile,
		    const char *function,
		    int lineno,
		    const char *fmt,
		    ...)
    {
      va_list ap;

      va_start(ap, fmt);
      log::vlog("error", sourcefile, function, lineno, fmt, ap);
      va_end(ap);
    }
  };

  class warning : public log {
  public:

    static void log(const char *sourcefile,
		    const char *function,
		    int lineno,
		    const char *fmt,
		    ...)
    {
      va_list ap;

      va_start(ap, fmt);
      log::vlog("warning", sourcefile, function, lineno, fmt, ap);
      va_end(ap);
    }
  };

  class info : public log {
  public:

    static void log(const char *sourcefile,
		    const char *function,
		    int lineno,
		    const char *fmt,
		    ...)
    {
      va_list ap;

      va_start(ap, fmt);
      log::vlog("info", sourcefile, function, lineno, fmt, ap);
      va_end(ap);
    }
  };

  class debug : public log {
  public:

    static void log(const char *sourcefile,
		    const char *function,
		    int lineno,
		    const char *fmt,
		    ...)
    {
      va_list ap;

      va_start(ap, fmt);
      log::vlog("debug", sourcefile, function, lineno, fmt, ap);
      va_end(ap);
    }
  };

  class status : public log {
  public:

    static void log(const char *fmt,
		    ...)
    {
      va_list ap;

      va_start(ap, fmt);
      log::vprintf(fmt, ap);
      va_end(ap);
    }

    static void mark(const char *fmt,
		    ...)
    {
      va_list ap;

      va_start(ap, fmt);
      log::mark(fmt, ap);
      va_end(ap);
    }
      
  };
  
  

};

#endif // logging
