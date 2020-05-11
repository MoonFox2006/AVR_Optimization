#ifndef __VARIANT_H
#define __VARIANT_H

#include <avr/pgmspace.h>
#include <Arduino.h>

#define OPT_STEP 4 // 0 - 4

class Variant {
public:
#if OPT_STEP < 4
  enum vartype_t { VAR_NULL, VAR_BOOL, VAR_I8, VAR_U8, VAR_I16, VAR_U16, VAR_I32, VAR_U32, VAR_FLOAT, VAR_CHAR, VAR_STR };
#else
  enum vartype_t { VAR_NULL, VAR_BOOL, VAR_CHAR, VAR_I8, VAR_U8, VAR_I16, VAR_U16, VAR_I32, VAR_U32, VAR_FLOAT, VAR_STR };
#endif

  Variant() : _type(VAR_NULL) {}
  explicit Variant(bool value) {
#if OPT_STEP
    set(VAR_BOOL, &value, false, false);
#else
    _type = VAR_BOOL;
    _value.asbool = value;
#endif
  }
  explicit Variant(int8_t value) {
#if OPT_STEP
    set(VAR_I8, &value, false, false);
#else
    _type = VAR_I8;
    _value.asi8 = value;
#endif
  }
  explicit Variant(uint8_t value) {
#if OPT_STEP
    set(VAR_U8, &value, false, false);
#else
    _type = VAR_U8;
    _value.asu8 = value;
#endif
  }
  explicit Variant(int16_t value) {
#if OPT_STEP
    set(VAR_I16, &value, false, false);
#else
    _type = VAR_I16;
    _value.asi16 = value;
#endif
  }
  explicit Variant(uint16_t value) {
#if OPT_STEP
    set(VAR_U16, &value, false, false);
#else
    _type = VAR_U16;
    _value.asu16 = value;
#endif
  }
  explicit Variant(int32_t value) {
#if OPT_STEP
    set(VAR_I32, &value, false, false);
#else
    _type = VAR_I32;
    _value.asi32 = new int32_t(value);
#endif
  }
  explicit Variant(uint32_t value) {
#if OPT_STEP
    set(VAR_U32, &value, false, false);
#else
    _type = VAR_U32;
    _value.asu32 = new uint32_t(value);
#endif
  }
  explicit Variant(float value) {
#if OPT_STEP
    set(VAR_FLOAT, &value, false, false);
#else
    _type = VAR_FLOAT;
    _value.asfloat = new float(value);
#endif
  }
  explicit Variant(char value) {
#if OPT_STEP
    set(VAR_CHAR, &value, false, false);
#else
    _type = VAR_CHAR;
    _value.aschar = value;
#endif
  }
  explicit Variant(const char *value)  {
#if OPT_STEP
    set(VAR_STR, value, false, false);
#else
    _type = VAR_STR;
    _value.asstr = new char[strlen(value) + 1];
    strcpy(_value.asstr, value);
#endif
  }
  explicit Variant(const __FlashStringHelper *value) {
#if OPT_STEP
    set(VAR_STR, value, true, false);
#else
    _type = VAR_STR;
    _value.asstr = new char[strlen_P((PGM_P)value) + 1];
    strcpy_P(_value.asstr, (PGM_P)value);
#endif
  }
#if OPT_STEP > 3
  explicit Variant(const Variant &copy) {
    set(copy._type, (copy._type >= VAR_I32) && (copy._type <= VAR_STR) ? (void*)copy._value.asstr : (void*)&copy._value, false, false);
  }
#elif OPT_STEP > 1
  explicit Variant(const Variant &copy) {
    set(copy._type, ((copy._type >= VAR_I32) && (copy._type <= VAR_FLOAT)) || (copy._type == VAR_STR) ? (void*)copy._value.asstr : (void*)&copy._value, false, false);
  }
#else
  explicit Variant(const Variant &copy);
#endif
  ~Variant() {
    clear();
  }

  vartype_t type() const {
    return _type;
  }
  uint16_t size() const;
  void clear();
  bool get(void *value);
#if OPT_STEP
  Variant& operator=(bool value) {
    set(VAR_BOOL, &value, false, true);
    return *this;
  }
#else
  Variant& operator=(bool value);
#endif
#if OPT_STEP
  Variant& operator=(int8_t value) {
    set(VAR_I8, &value, false, true);
    return *this;
  }
#else
  Variant& operator=(int8_t value);
#endif
#if OPT_STEP
  Variant& operator=(uint8_t value) {
    set(VAR_U8, &value, false, true);
    return *this;
  }
#else
  Variant& operator=(uint8_t value);
#endif
#if OPT_STEP
  Variant& operator=(int16_t value) {
    set(VAR_I16, &value, false, true);
    return *this;
  }
#else
  Variant& operator=(int16_t value);
#endif
#if OPT_STEP
  Variant& operator=(uint16_t value) {
    set(VAR_U16, &value, false, true);
    return *this;
  }
#else
  Variant& operator=(uint16_t value);
#endif
#if OPT_STEP
  Variant& operator=(int32_t value) {
    set(VAR_I32, &value, false, true);
    return *this;
  }
#else
  Variant& operator=(int32_t value);
#endif
#if OPT_STEP
  Variant& operator=(uint32_t value) {
    set(VAR_U32, &value, false, true);
    return *this;
  }
#else
  Variant& operator=(uint32_t value);
#endif
#if OPT_STEP
  Variant& operator=(float value) {
    set(VAR_FLOAT, &value, false, true);
    return *this;
  }
#else
  Variant& operator=(float value);
#endif
#if OPT_STEP
  Variant& operator=(char value) {
    set(VAR_CHAR, &value, false, true);
    return *this;
  }
#else
  Variant& operator=(char value);
#endif
#if OPT_STEP
  Variant& operator=(const char *value) {
    set(VAR_STR, value, false, true);
    return *this;
  }
#else
  Variant& operator=(const char *value);
#endif
#if OPT_STEP
  Variant& operator=(const __FlashStringHelper *value) {
    set(VAR_STR, value, true, true);
    return *this;
  }
#else
  Variant& operator=(const __FlashStringHelper *value);
#endif
#if OPT_STEP > 3
  Variant& operator=(const Variant &value) {
    set(value._type, (value._type >= VAR_I32) && (value._type <= VAR_STR) ? (void*)value._value.asstr : (void*)&value._value, false, true);
    return *this;
  }
#elif OPT_STEP > 1
  Variant& operator=(const Variant &value) {
    set(value._type, ((value._type >= VAR_I32) && (value._type <= VAR_FLOAT)) || (value._type == VAR_STR) ? (void*)value._value.asstr : (void*)&value._value, false, true);
    return *this;
  }
#else
  Variant& operator=(const Variant &value);
#endif
  explicit operator bool() {
    if (_type == VAR_BOOL)
      return _value.asbool;
  }
  explicit operator int8_t() {
    if (_type == VAR_I8)
      return _value.asi8;
  }
  explicit operator uint8_t() {
    if (_type == VAR_U8)
      return _value.asu8;
  }
  explicit operator int16_t() {
    if (_type == VAR_I16)
      return _value.asi16;
  }
  explicit operator uint16_t() {
    if (_type == VAR_U16)
      return _value.asu16;
  }
  explicit operator int32_t() {
    if (_type == VAR_I32)
      return *_value.asi32;
  }
  explicit operator uint32_t() {
    if (_type == VAR_U32)
      return *_value.asu32;
  }
  explicit operator float() {
    if (_type == VAR_FLOAT)
      return *_value.asfloat;
  }
  explicit operator char() {
    if (_type == VAR_CHAR)
      return _value.aschar;
  }
  explicit operator char*() const {
    if (_type == VAR_STR)
      return _value.asstr;
  }

  char *toStr(char *str, uint16_t maxlen);
  size_t toStream(Stream &stream);

protected:
#if OPT_STEP
  void set(vartype_t type, const void *value, bool inflash, bool clearing);
#endif

  union {
    bool asbool;
    int8_t asi8;
    uint8_t asu8;
    int16_t asi16;
    uint16_t asu16;
    int32_t *asi32;
    uint32_t *asu32;
    float *asfloat;
    char aschar;
    char *asstr;
  } _value;
  vartype_t _type;
};

#endif
