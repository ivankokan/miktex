/***** Autogenerated from runstring.in; changes will be overwritten *****/

#line 1 "runtimebase.in"
/*****
 * runtimebase.in
 * Andy Hammerlindl  2009/07/28
 *
 * Common declarations needed for all code-generating .in files.
 *
 *****/


#line 1 "runstring.in"
/*****
 * runstring.in
 *
 * Runtime functions for string operations.
 *
 *****/

#line 1 "runtimebase.in"
#include "stack.h"
#include "types.h"
#include "builtin.h"
#include "entry.h"
#include "errormsg.h"
#include "array.h"
#include "triple.h"
#include "callable.h"
#include "opsymbols.h"

using vm::stack;
using vm::error;
using vm::array;
using vm::read;
using vm::callable;
using types::formal;
using types::function;
using camp::triple;

#define PRIMITIVE(name,Name,asyName) using types::prim##Name;
#include <primitives.h>
#undef PRIMITIVE

typedef double real;

void unused(void *);

namespace run {
array *copyArray(array *a);
array *copyArray2(array *a);
array *copyArray3(array *a);

double *copyTripleArray2Components(array *a, size_t &N,
                                   GCPlacement placement=NoGC);
triple *copyTripleArray2C(array *a, size_t &N,
                          GCPlacement placement=NoGC);
}

function *realRealFunction();

#define CURRENTPEN processData().currentpen

#line 10 "runstring.in"
#include <cfloat>
#include <cstring>
#include <algorithm>

#include "array.h"

using namespace camp;
using namespace vm;
using namespace settings;

typedef array stringarray;
typedef array stringarray2;

using types::stringArray;
using types::stringArray2;

namespace types {
extern const char *names[];
}

namespace run {
extern string emptystring;
}

static const string defaulttimeformat=string("%a %b %d %T %Z %Y");
#ifdef HAVE_STRFTIME
static const size_t nTime=256;
static char Time[nTime];
#endif  

void checkformat(const char *ptr, bool intformat) 
{
  while(*ptr != '\0') {
    if(*ptr != '%') /* While we have regular characters, print them.  */
      ptr++;
    else { /* We've got a format specifier. */
      ptr++;
      
      while(*ptr && strchr ("-+ #0'I", *ptr)) /* Move past flags.  */
        ptr++;

      if(*ptr == '*')
        ptr++;
      else while(isdigit(*ptr)) /* Handle explicit numeric value.  */
             ptr++;
          
      if(*ptr == '.') {
        ptr++; /* Go past the period.  */
        if(*ptr == '*') {
          ptr++;
        } else
          while(isdigit(*ptr)) /* Handle explicit numeric value.  */
            ptr++;
      }
      while(*ptr && strchr ("hlL", *ptr))
        ptr++;
          
      if(*ptr == '%') {++ptr; continue;}
      else if(*ptr != '\0') {
        if(intformat) {
          switch(*ptr) {
            case 'd':
            case 'i':
            case 'o':
            case 'u':
            case 'x':
            case 'X':
            case 'c':
              break;
            default:
              ostringstream buf;
              buf << "Invalid format '" << *ptr << "' for type " 
                  << types::names[types::ty_Int];
              error(buf);
              break;
          }
        } else {
          switch(*ptr) {
            case 'f':
            case 'F':
            case 'e':
            case 'E':
            case 'g':
            case 'G':
              break;
            default:
              ostringstream buf;
              buf << "Invalid format '" << *ptr << "' for type "
                  << types::names[types::ty_real];
              error(buf);
              break;
          }
        }
      }
      break; // Only one argument is allowed.
    } /* End of else statement */
  }
}
  
// Autogenerated routines:



#ifndef NOSYM
#include "runstring.symbols.h"

#endif
namespace run {
// String operations
#line 113 "runstring.in"
void emptyString(stack *Stack)
{
#line 114 "runstring.in"
  {Stack->push<string>(emptystring); return;}
}

#line 119 "runstring.in"
// Int length(string *s);
void gen_runstring1(stack *Stack)
{
  string * s=vm::pop<string *>(Stack);
#line 120 "runstring.in"
  {Stack->push<Int>((Int) s->length()); return;}
}

#line 124 "runstring.in"
// Int find(string *s, string t, Int pos=0);
void gen_runstring2(stack *Stack)
{
  Int pos=vm::pop<Int>(Stack,0);
  string t=vm::pop<string>(Stack);
  string * s=vm::pop<string *>(Stack);
#line 125 "runstring.in"
  size_t n=s->find(t,pos);
  {Stack->push<Int>(n == string::npos ? (Int) -1 : (Int) n); return;}
}

#line 130 "runstring.in"
// Int rfind(string *s, string t, Int pos=-1);
void gen_runstring3(stack *Stack)
{
  Int pos=vm::pop<Int>(Stack,-1);
  string t=vm::pop<string>(Stack);
  string * s=vm::pop<string *>(Stack);
#line 131 "runstring.in"
  size_t n=s->rfind(t,pos);
  {Stack->push<Int>(n == string::npos ? (Int) -1 : (Int) n); return;}
}

#line 136 "runstring.in"
// string reverse(string s);
void gen_runstring4(stack *Stack)
{
  string s=vm::pop<string>(Stack);
#line 137 "runstring.in"
  reverse(s.begin(),s.end());
  {Stack->push<string>(s); return;}
}

#line 142 "runstring.in"
// string insert(string s, Int pos, string t);
void gen_runstring5(stack *Stack)
{
  string t=vm::pop<string>(Stack);
  Int pos=vm::pop<Int>(Stack);
  string s=vm::pop<string>(Stack);
#line 143 "runstring.in"
  if ((size_t) pos < s.length())
    {Stack->push<string>(s.insert(pos,t)); return;}
  {Stack->push<string>(s); return;}
}

#line 149 "runstring.in"
// string substr(string* s, Int pos, Int n=-1);
void gen_runstring6(stack *Stack)
{
  Int n=vm::pop<Int>(Stack,-1);
  Int pos=vm::pop<Int>(Stack);
  string* s=vm::pop<string*>(Stack);
#line 150 "runstring.in"
  if ((size_t) pos < s->length())
    {Stack->push<string>(s->substr(pos,n)); return;}
  {Stack->push<string>(emptystring); return;}
}

#line 156 "runstring.in"
// string erase(string s, Int pos, Int n);
void gen_runstring7(stack *Stack)
{
  Int n=vm::pop<Int>(Stack);
  Int pos=vm::pop<Int>(Stack);
  string s=vm::pop<string>(Stack);
#line 157 "runstring.in"
  if ((size_t) pos < s.length())
    {Stack->push<string>(s.erase(pos,n)); return;}
  {Stack->push<string>(s); return;} 
}

#line 163 "runstring.in"
// string downcase(string s);
void gen_runstring8(stack *Stack)
{
  string s=vm::pop<string>(Stack);
#line 164 "runstring.in"
  std::transform(s.begin(),s.end(),s.begin(),tolower);
  {Stack->push<string>(s); return;}
}

#line 169 "runstring.in"
// string upcase(string s);
void gen_runstring9(stack *Stack)
{
  string s=vm::pop<string>(Stack);
#line 170 "runstring.in"
  std::transform(s.begin(),s.end(),s.begin(),toupper);
  {Stack->push<string>(s); return;}
}

// returns a string constructed by translating all occurrences of the string
// from in an array of string pairs {from,to} to the string to in string s.
#line 177 "runstring.in"
// string replace(string *S, stringarray2 *translate);
void gen_runstring10(stack *Stack)
{
  stringarray2 * translate=vm::pop<stringarray2 *>(Stack);
  string * S=vm::pop<string *>(Stack);
#line 178 "runstring.in"
  size_t size=checkArray(translate);
  for(size_t i=0; i < size; i++) {
    array *a=read<array*>(translate,i);
    checkArray(a);
  }
  const char *p=S->c_str();
  ostringstream buf;
  while(*p) {
    for(size_t i=0; i < size;) {
      array *a=read<array*>(translate,i);
      size_t size2=checkArray(a);
      if(size2 != 2) 
        error("translation table entry must be an array of length 2");
      string* from=read<string*>(a,0);
      size_t len=from->length();
      if(strncmp(p,from->c_str(),len) != 0) {i++; continue;}
      buf << read<string>(a,1);
      p += len;
      if(*p == 0) {Stack->push<string>(buf.str()); return;}
      i=0;
    }
    buf << *(p++);
  }
  {Stack->push<string>(buf.str()); return;}
}

#line 205 "runstring.in"
// string format(string *format, Int x, string locale=emptystring);
void gen_runstring11(stack *Stack)
{
  string locale=vm::pop<string>(Stack,emptystring);
  Int x=vm::pop<Int>(Stack);
  string * format=vm::pop<string *>(Stack);
#line 206 "runstring.in"
  ostringstream out;
  const char *p0=format->c_str();
  checkformat(p0,true);
  
  const char *p=p0;
  const char *start=NULL;
  while(*p != 0) {
    char curr=*p;
    if(curr == '%') {
      p++;
      if(*p != '%') {start=p-1; break;}
    }
    out << *(p++);
  }
  
  if(!start) {Stack->push<string>(out.str()); return;}
  
  // Allow at most 1 argument  
  while(*p != 0) {
    if(*p == '*' || *p == '$') {Stack->push<string>(out.str()); return;}
    if(isupper(*p) || islower(*p)) {p++; break;}
    p++;
  }
  
  string f=format->substr(start-p0,p-start);

  const char *oldlocale=NULL;

  if(!locale.empty()) {
    oldlocale=setlocale(LC_ALL,NULL);
    if(oldlocale) oldlocale=StrdupNoGC(oldlocale);
    setlocale(LC_ALL,locale.c_str());
  }

  Int size=snprintf(NULL,0,f.c_str(),x)+1;
  if(size < 1) size=255; // Workaround for non-C99 compliant systems.
  char *buf=new char[size];
  snprintf(buf,size,f.c_str(),x);

  out << string(buf);
  out << p;

  delete[] buf;
  
  if(oldlocale) {
    setlocale(LC_ALL,oldlocale);
    delete[] oldlocale;
  }

  {Stack->push<string>(out.str()); return;}
}

#line 259 "runstring.in"
// string format(string *format, bool forcemath=false, string separator, real x,              string locale=emptystring);
void gen_runstring12(stack *Stack)
{
  string locale=vm::pop<string>(Stack,emptystring);
  real x=vm::pop<real>(Stack);
  string separator=vm::pop<string>(Stack);
  bool forcemath=vm::pop<bool>(Stack,false);
  string * format=vm::pop<string *>(Stack);
#line 261 "runstring.in"
  if(*format == "%") {Stack->push<string>(""); return;} // Temporary workaround for github Issue #29.
  
  bool tex=getSetting<string>("tex") != "none";
  bool texify=forcemath;
  ostringstream out;
  
  const char *p0=format->c_str();
  checkformat(p0,false);

  const char *phantom="\\phantom{+}";
  
  const char *p=p0;
  const char *start=NULL;
  char prev=0;
  while(*p != 0) {
    char curr=*p;
    if(tex && curr == '$' && prev != '\\') texify=true;
    prev=curr;
    if(curr == '%') {
      p++;
      if(*p != '%') {start=p-1; break;}
    }
    out << *(p++);
  }
  
  if(!start) {Stack->push<string>(out.str()); return;}
  
  // Allow at most 1 argument  
  while(*p != 0) {
    if(*p == '*' || *p == '$') {Stack->push<string>(out.str()); return;}
    if(isupper(*p) || islower(*p)) {p++; break;}
    p++;
  }
  
  const char *tail=p;
  string f=format->substr(start-p0,tail-start);

  const char *oldlocale=NULL;
  if(!locale.empty()) {
    oldlocale=setlocale(LC_ALL,NULL);
    if(oldlocale) oldlocale=StrdupNoGC(oldlocale);
    setlocale(LC_ALL,locale.c_str());
  }

  Int size=snprintf(NULL,0,f.c_str(),x)+1;
  if(size < 1) size=255; // Workaround for non-C99 compliant systems.
  char *buf=new char[size];
  snprintf(buf,size,f.c_str(),x);

  bool trailingzero=f.find("#") < string::npos;
  bool plus=f.find("+") < string::npos;
  bool space=f.find(" ") < string::npos;
  
  char *q=buf; // beginning of formatted number

  if(*q == ' ' && texify) {
    out << phantom;
    q++;
  }
  
  const char decimal=*(localeconv()->decimal_point);

  // Remove any spurious sign
  if(*q == '-' || *q == '+') {
    p=q+1;
    bool zero=true;
    while(*p != 0) {
      if(!isdigit(*p) && *p != decimal) break;
      if(isdigit(*p) && *p != '0') {zero=false; break;}
      p++;
    }
    if(zero) {
      q++;
      if((plus || space) && texify) out << phantom;
    }
  }
  
  const char *r=p=q;
  bool dp=false;
  while(*r != 0 && (isspace(*r) || isdigit(*r) || *r == decimal \
    || *r == '+' || *r == '-')) {
    if(*r == decimal) dp=true;
    r++;
  }
  if(dp) { // Remove trailing zeros and/or decimal point
    r--;
    unsigned n=0;
    while(r > q && *r == '0') {r--; n++;}
    if(*r == decimal) {r--; n++;}
    while(q <= r) out << *(q++);
    if(!trailingzero) q += n;
  }
  
  bool zero=(r == p && *r == '0') && !trailingzero;
  
  // Translate "E+/E-/e+/e-" exponential notation to TeX
  while(*q != 0) {
    if(texify && (*q == 'E' || *q == 'e') && 
       (*(q+1) == '+' || *(q+1) == '-')) {
      if(!zero) out << separator << "10^{";
      bool plus=(*(q+1) == '+');
      q++;
      if(plus) q++;
      if(*q == '-') out << *(q++);
      while(*q == '0' && (zero || isdigit(*(q+1)))) q++;
      while(isdigit(*q)) out << *(q++);
      if(!zero)
        out << "}";
      break;
    }
    out << *(q++);
  }
  
  while(*tail != 0) 
    out << *(tail++);
  
  delete[] buf;

  if(oldlocale) {
    setlocale(LC_ALL,oldlocale);
    delete[] oldlocale;
  }
  
  {Stack->push<string>(out.str()); return;}
}

#line 388 "runstring.in"
// Int hex(string s);
void gen_runstring13(stack *Stack)
{
  string s=vm::pop<string>(Stack);
#line 389 "runstring.in"
  istringstream is(s);
  is.setf(std::ios::hex,std::ios::basefield);
  Int value;
  if(is && is >> value && ((is >> std::ws).eof())) {Stack->push<Int>(value); return;}
  ostringstream buf;
  buf << "invalid hexadecimal cast from string \"" << s << "\"";
  error(buf);
}

#line 399 "runstring.in"
// Int ascii(string s);
void gen_runstring14(stack *Stack)
{
  string s=vm::pop<string>(Stack);
#line 400 "runstring.in"
  {Stack->push<Int>(s.empty() ? -1 : (unsigned char) s[0]); return;}
}

#line 404 "runstring.in"
// string string(Int x);
void gen_runstring15(stack *Stack)
{
  Int x=vm::pop<Int>(Stack);
#line 405 "runstring.in"
  ostringstream buf;
  buf << x;
  {Stack->push<string>(buf.str()); return;}
}

#line 411 "runstring.in"
// string string(real x, Int digits=DBL_DIG);
void gen_runstring16(stack *Stack)
{
  Int digits=vm::pop<Int>(Stack,DBL_DIG);
  real x=vm::pop<real>(Stack);
#line 412 "runstring.in"
  ostringstream buf;
  buf.precision(digits);
  buf << x;
  {Stack->push<string>(buf.str()); return;}
}

#line 419 "runstring.in"
// string time(string format=defaulttimeformat);
void gen_runstring17(stack *Stack)
{
  string format=vm::pop<string>(Stack,defaulttimeformat);
#line 420 "runstring.in"
#ifdef HAVE_STRFTIME
  const time_t bintime=time(NULL);
  if(!strftime(Time,nTime,format.c_str(),localtime(&bintime))) {Stack->push<string>(""); return;}
  {Stack->push<string>(Time); return;}
#else
  {Stack->push<string>(format); return;}
#endif  
}

#line 430 "runstring.in"
// string time(Int seconds, string format=defaulttimeformat);
void gen_runstring18(stack *Stack)
{
  string format=vm::pop<string>(Stack,defaulttimeformat);
  Int seconds=vm::pop<Int>(Stack);
#line 431 "runstring.in"
#ifdef HAVE_STRFTIME
  const time_t bintime=seconds;
  if(!strftime(Time,nTime,format.c_str(),localtime(&bintime))) {Stack->push<string>(""); return;}
  {Stack->push<string>(Time); return;}
#else
// Avoid unused variable warning messages
  unused(&seconds);
  {Stack->push<string>(format); return;}
#endif
}

#line 443 "runstring.in"
// Int seconds(string t=emptystring, string format=emptystring);
void gen_runstring19(stack *Stack)
{
  string format=vm::pop<string>(Stack,emptystring);
  string t=vm::pop<string>(Stack,emptystring);
#line 444 "runstring.in"
#if defined(HAVE_STRPTIME)
  const time_t bintime=time(NULL);
  tm tm=*localtime(&bintime);
  if(t != "" && !strptime(t.c_str(),format.c_str(),&tm)) {Stack->push<Int>(-1); return;}
  {Stack->push<Int>((Int) mktime(&tm)); return;}
#else
  {Stack->push<Int>(-1); return;}
#endif  
}

} // namespace run

namespace trans {

void gen_runstring_venv(venv &ve)
{
#line 112 "runstring.in"
  REGISTER_BLTIN(run::emptyString,"emptyString");
#line 119 "runstring.in"
  addFunc(ve, run::gen_runstring1, primInt(), SYM(length), formal(primString(), SYM(s), false, false));
#line 124 "runstring.in"
  addFunc(ve, run::gen_runstring2, primInt(), SYM(find), formal(primString(), SYM(s), false, false), formal(primString() , SYM(t), false, false), formal(primInt(), SYM(pos), true, false));
#line 130 "runstring.in"
  addFunc(ve, run::gen_runstring3, primInt(), SYM(rfind), formal(primString(), SYM(s), false, false), formal(primString() , SYM(t), false, false), formal(primInt(), SYM(pos), true, false));
#line 136 "runstring.in"
  addFunc(ve, run::gen_runstring4, primString() , SYM(reverse), formal(primString() , SYM(s), false, false));
#line 142 "runstring.in"
  addFunc(ve, run::gen_runstring5, primString() , SYM(insert), formal(primString() , SYM(s), false, false), formal(primInt(), SYM(pos), false, false), formal(primString() , SYM(t), false, false));
#line 149 "runstring.in"
  addFunc(ve, run::gen_runstring6, primString() , SYM(substr), formal(primString(), SYM(s), false, false), formal(primInt(), SYM(pos), false, false), formal(primInt(), SYM(n), true, false));
#line 156 "runstring.in"
  addFunc(ve, run::gen_runstring7, primString() , SYM(erase), formal(primString() , SYM(s), false, false), formal(primInt(), SYM(pos), false, false), formal(primInt(), SYM(n), false, false));
#line 163 "runstring.in"
  addFunc(ve, run::gen_runstring8, primString() , SYM(downcase), formal(primString() , SYM(s), false, false));
#line 169 "runstring.in"
  addFunc(ve, run::gen_runstring9, primString() , SYM(upcase), formal(primString() , SYM(s), false, false));
#line 175 "runstring.in"
  addFunc(ve, run::gen_runstring10, primString() , SYM(replace), formal(primString(), SYM(s), false, false), formal(stringArray2(), SYM(translate), false, false));
#line 205 "runstring.in"
  addFunc(ve, run::gen_runstring11, primString() , SYM(format), formal(primString(), SYM(format), false, false), formal(primInt(), SYM(x), false, false), formal(primString() , SYM(locale), true, false));
#line 259 "runstring.in"
  addFunc(ve, run::gen_runstring12, primString() , SYM(format), formal(primString(), SYM(format), false, false), formal(primBoolean(), SYM(forcemath), true, false), formal(primString() , SYM(separator), false, false), formal(primReal(), SYM(x), false, false), formal(primString() , SYM(locale), true, false));
#line 388 "runstring.in"
  addFunc(ve, run::gen_runstring13, primInt(), SYM(hex), formal(primString() , SYM(s), false, false));
#line 399 "runstring.in"
  addFunc(ve, run::gen_runstring14, primInt(), SYM(ascii), formal(primString() , SYM(s), false, false));
#line 404 "runstring.in"
  addFunc(ve, run::gen_runstring15, primString() , SYM(string), formal(primInt(), SYM(x), false, false));
#line 411 "runstring.in"
  addFunc(ve, run::gen_runstring16, primString() , SYM(string), formal(primReal(), SYM(x), false, false), formal(primInt(), SYM(digits), true, false));
#line 419 "runstring.in"
  addFunc(ve, run::gen_runstring17, primString() , SYM(time), formal(primString() , SYM(format), true, false));
#line 430 "runstring.in"
  addFunc(ve, run::gen_runstring18, primString() , SYM(time), formal(primInt(), SYM(seconds), false, false), formal(primString() , SYM(format), true, false));
#line 443 "runstring.in"
  addFunc(ve, run::gen_runstring19, primInt(), SYM(seconds), formal(primString() , SYM(t), true, false), formal(primString() , SYM(format), true, false));
}

} // namespace trans
