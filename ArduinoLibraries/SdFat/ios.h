/* Arduino SdFat Library
 * Copyright (C) 2012 by William Greiman
 *
 * This file is part of the Arduino SdFat Library
 *
 * This Library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the Arduino SdFat Library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
#ifndef ios_h
#define ios_h
#include <SdFat\\SdBaseFile.h>
/**
 * \file 
 * \brief \ref ios_base and \ref ios classes
 */
//==============================================================================
/**
 * \class ios_base
 * \brief Base class for all streams
 */
class ios_base {
 public:
  /** typedef for iostate bitmask */
  typedef unsigned char iostate;
  // State flags.
  /** iostate for no flags */
  static const iostate goodbit = 0x00;
  /** iostate bad bit for a nonrecoverable error. */
  static const iostate badbit = 0X01;
  /** iostate bit for end of file reached */
  static const iostate eofbit = 0x02;
  /** iostate fail bit for nonfatal error */
  static const iostate failbit = 0X04;
  /**
   * unsigned size that can represent maximum file size.
   *  (violates spec - should be signed)
   */
  typedef uint32_t streamsize;
  /** type for absolute seek position */
  typedef uint32_t pos_type;
  /** type for relative seek offset */
  typedef int32_t off_type;

  /** enumerated type for the direction of relative seeks */
  enum seekdir {
    /** seek relative to the beginning of the stream */
    beg,
    /** seek relative to the current stream position */
    cur,
    /** seek relative to the end of the stream */
    end
  };
  /** type for format flags */
  typedef unsigned int fmtflags;
  /** left adjust fields */
  static const fmtflags left       = 0x0001;
  /** right adjust fields */
  static const fmtflags right      = 0x0002;
  /** fill between sign/base prefix and number */
  static const fmtflags internal   = 0x0004;
  /** base 10 flag*/
  static const fmtflags dec        = 0x0008;
  /** base 16 flag */
  static const fmtflags hex        = 0x0010;
  /** base 8 flag */
  static const fmtflags oct        = 0x0020;
  // static const fmtflags fixed      = 0x0040;
  // static const fmtflags scientific = 0x0080;
  /** use strings true/false for bool */
  static const fmtflags boolalpha  = 0x0100;
  /** use prefix 0X for hex and 0 for oct */
  static const fmtflags showbase   = 0x0200;
  /** always show '.' for floating numbers */
  static const fmtflags showpoint  = 0x0400;
  /** show + sign for nonnegative numbers */
  static const fmtflags showpos    = 0x0800;
  /** skip initial white space */
  static const fmtflags skipws     = 0x1000;
  // static const fmtflags unitbuf    = 0x2000;
  /** use uppercase letters in number representations */
  static const fmtflags uppercase  = 0x4000;
  /** mask for adjustfield */
  static const fmtflags adjustfield = left | right | internal;
  /** mask for basefield */
  static const fmtflags basefield   = dec | hex | oct;
  // static const fmtflags floatfield  = scientific | fixed;
  //----------------------------------------------------------------------------
  /** typedef for iostream open mode */
  typedef uint8_t openmode;

  // Openmode flags.
  /** seek to end before each write */
  static const openmode app    = 0X4;
  /** open and seek to end immediately after opening */
  static const openmode ate    = 0X8;
  /** perform input and output in binary mode (as opposed to text mode) */
  static const openmode binary = 0X10;
  /** open for input */
  static const openmode in     = 0X20;
  /** open for output */
  static const openmode out    = 0X40;
  /** truncate an existing stream when opening */
  static const openmode trunc  = 0X80;
  //----------------------------------------------------------------------------
  ios_base() : fill_(' '), fmtflags_(dec | right | skipws)
    , precision_(2), width_(0) {}
  /** \return fill character */
  char fill() {return fill_;}
  /** Set fill character
   * \param[in] c new fill character
   * \return old fill character
   */
  char fill(char c) {
    char r = fill_;
    fill_ = c;
    return r;
  }
  /** \return format flags */
  fmtflags flags() const {return fmtflags_;}
  /** set format flags
   * \param[in] fl new flag
   * \return old flags
   */
  fmtflags flags(fmtflags fl) {
    fmtflags tmp = fmtflags_;
    fmtflags_ = fl;
    return tmp;
  }
  /** \return precision */
  int precision() const {return precision_;}
  /** set precision
   * \param[in] n new precision
   * \return old precision
   */
  int precision(unsigned int n) {
    int r = precision_;
    precision_ = n;
    return r;
  }
  /** set format flags
   * \param[in] fl new flags to be or'ed in
   * \return old flags
   */
  fmtflags setf(fmtflags fl) {
    fmtflags r = fmtflags_;
    fmtflags_ |= fl;
    return r;
  }
  /** modify format flags
   * \param[in] mask flags to be removed
   * \param[in] fl flags to be set after mask bits have been cleared
   * \return old flags
   */
  fmtflags setf(fmtflags fl, fmtflags mask) {
    fmtflags r = fmtflags_;
    fmtflags_ &= ~mask;
    fmtflags_ |= fl;
    return r;
  }
  /** clear format flags
   * \param[in] fl flags to be cleared
   * \return old flags
   */
  void unsetf(fmtflags fl) {
    fmtflags_ &= ~fl;
  }
  /** \return width */
  unsigned width() {return width_;}
  /** set width
   * \param[in] n new width
   * \return old width
   */
  unsigned width(unsigned n) {
    unsigned r = width_;
    width_ = n;
    return r;
  }

 protected:
  /** \return current number base */
  uint8_t flagsToBase() {
    uint8_t f = flags() & basefield;
    return f == oct ? 8 : f != hex ? 10 : 16;
  }

 private:
  char fill_;
  fmtflags fmtflags_;
  unsigned char precision_;
  unsigned int width_;
};
//------------------------------------------------------------------------------
/** function for boolalpha manipulator
 * \param[in] str The stream
 * \return The stream
 */
inline ios_base& boolalpha(ios_base& str) {
  str.setf(ios_base::boolalpha);
  return str;
}
/** function for dec manipulator
 * \param[in] str The stream
 * \return The stream
 */
inline ios_base& dec(ios_base& str) {
  str.setf(ios_base::dec, ios_base::basefield);
  return str;
}
/** function for hex manipulator
 * \param[in] str The stream
 * \return The stream
 */
inline ios_base& hex(ios_base& str) {
  str.setf(ios_base::hex, ios_base::basefield);
  return str;
}
/** function for internal manipulator
 * \param[in] str The stream
 * \return The stream
 */
inline ios_base& internal(ios_base& str) {
  str.setf(ios_base::internal, ios_base::adjustfield);
  return str;
}
/** function for left manipulator
 * \param[in] str The stream
 * \return The stream
 */
inline ios_base& left(ios_base& str) {
  str.setf(ios_base::left, ios_base::adjustfield);
  return str;
}
/** function for noboolalpha manipulator
 * \param[in] str The stream
 * \return The stream
 */
inline ios_base& noboolalpha(ios_base& str) {
  str.unsetf(ios_base::boolalpha);
  return str;
}
/** function for noshowbase manipulator
 * \param[in] str The stream
 * \return The stream
 */
inline ios_base& noshowbase(ios_base& str) {
  str.unsetf(ios_base::showbase);
  return str;
}
/** function for noshowpoint manipulator
 * \param[in] str The stream
 * \return The stream
 */
inline ios_base& noshowpoint(ios_base& str) {
  str.unsetf(ios_base::showpoint);
  return str;
}
/** function for noshowpos manipulator
 * \param[in] str The stream
 * \return The stream
 */
inline ios_base& noshowpos(ios_base& str) {
  str.unsetf(ios_base::showpos);
  return str;
}
/** function for noskipws manipulator
 * \param[in] str The stream
 * \return The stream
 */
inline ios_base& noskipws(ios_base& str) {
  str.unsetf(ios_base::skipws);
  return str;
}
/** function for nouppercase manipulator
 * \param[in] str The stream
 * \return The stream
 */
inline ios_base& nouppercase(ios_base& str) {
  str.unsetf(ios_base::uppercase);
  return str;
}
/** function for oct manipulator
 * \param[in] str The stream
 * \return The stream
 */
inline ios_base& oct(ios_base& str) {
  str.setf(ios_base::oct, ios_base::basefield);
  return str;
}
/** function for right manipulator
 * \param[in] str The stream
 * \return The stream
 */
inline ios_base& right(ios_base& str) {
  str.setf(ios_base::right, ios_base::adjustfield);
  return str;
}
/** function for showbase manipulator
 * \param[in] str The stream
 * \return The stream
 */
inline ios_base& showbase(ios_base& str) {
  str.setf(ios_base::showbase);
  return str;
}
/** function for showpos manipulator
 * \param[in] str The stream
 * \return The stream
 */
inline ios_base& showpos(ios_base& str) {
  str.setf(ios_base::showpos);
  return str;
}
/** function for showpoint manipulator
 * \param[in] str The stream
 * \return The stream
 */
inline ios_base& showpoint(ios_base& str) {
  str.setf(ios_base::showpoint);
  return str;
}
/** function for skipws manipulator
 * \param[in] str The stream
 * \return The stream
 */
inline ios_base& skipws(ios_base& str) {
  str.setf(ios_base::skipws);
  return str;
}
/** function for uppercase manipulator
 * \param[in] str The stream
 * \return The stream
 */
inline ios_base& uppercase(ios_base& str) {
  str.setf(ios_base::uppercase);
  return str;
}
//==============================================================================
/**
 * \class ios
 * \brief Error and state information for all streams
 */
class ios : public ios_base {
 public:
  /** Create ios with no error flags set */
  ios() : iostate_(0) {}

  /** \return null pointer if fail() is true. */
  operator const void*() const {
    return !fail() ? reinterpret_cast<const void*>(this) : 0;
  }
  /** \return true if fail() else false.  */
  bool operator!() const {return fail();}
  /** \return The iostate flags for this file. */
  iostate rdstate() const {return iostate_;}
  /** \return True if no iostate flags are set else false. */
  bool good() const {return iostate_ == goodbit;}
  /** \return true if end of file has been reached else false.
   *
   * Warning: An empty file returns false before the first read.
   *
   * Moral: eof() is only useful in combination with fail(), to find out
   * whether EOF was the cause for failure
   */
  bool eof() const {return iostate_ & eofbit;}
  /** \return true if any iostate bit other than eof are set else false. */
  bool fail() const {return iostate_ & (failbit | badbit);}
  /** \return true if bad bit is set else false. */
  bool bad() const {return iostate_ & badbit;}
  /** Clear iostate bits.
   *
   * \param[in] state The flags you want to set after clearing all flags.
   **/
  void clear(iostate state = goodbit) {iostate_ = state;}
  /** Set iostate bits.
   *
   * \param[in] state Bitts to set.
   **/
  void setstate(iostate state) {iostate_ |= state;}

 private:
  iostate iostate_;
};
#endif  // ios_h
