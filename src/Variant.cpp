#include "Variant.h"

static const char BOOLS[][6] PROGMEM = { "false", "true" };

#if OPT_STEP == 0
Variant::Variant(const Variant &copy) {
  _type = copy._type;
  switch (_type) {
    case VAR_BOOL:
      _value.asbool = copy._value.asbool;
      break;
    case VAR_I8:
      _value.asi8 = copy._value.asi8;
      break;
    case VAR_U8:
      _value.asu8 = copy._value.asu8;
      break;
    case VAR_I16:
      _value.asi16 = copy._value.asi16;
      break;
    case VAR_U16:
      _value.asu16 = copy._value.asu16;
      break;
    case VAR_I32:
      _value.asi32 = new int32_t(*copy._value.asi32);
      break;
    case VAR_U32:
      _value.asu32 = new uint32_t(*copy._value.asu32);
      break;
    case VAR_FLOAT:
      _value.asfloat = new float(*copy._value.asfloat);
      break;
    case VAR_CHAR:
      _value.aschar = copy._value.aschar;
      break;
    case VAR_STR:
      _value.asstr = new char[strlen(copy._value.asstr) + 1];
      strcpy(_value.asstr, copy._value.asstr);
      break;
    default:
      break;
  }
}
#elif OPT_STEP == 1
Variant::Variant(const Variant &copy) {
  switch (_type) {
    case VAR_I32:
      set(copy._type, copy._value.asi32, false, false);
      break;
    case VAR_U32:
      set(copy._type, copy._value.asu32, false, false);
      break;
    case VAR_FLOAT:
      set(copy._type, copy._value.asfloat, false, false);
      break;
    case VAR_STR:
      set(copy._type, copy._value.asstr, false, false);
      break;
    default:
      set(copy._type, &copy._value, false, false);
      break;
  }
}
#endif

uint16_t Variant::size() const {
  switch (_type) {
    case VAR_BOOL:
      return sizeof(bool);
    case VAR_I8:
      return sizeof(int8_t);
    case VAR_U8:
      return sizeof(uint8_t);
    case VAR_I16:
      return sizeof(int16_t);
    case VAR_U16:
      return sizeof(uint16_t);
    case VAR_I32:
      return sizeof(int32_t);
    case VAR_U32:
      return sizeof(uint32_t);
    case VAR_FLOAT:
      return sizeof(float);
    case VAR_CHAR:
      return sizeof(char);
    case VAR_STR:
      return strlen(_value.asstr);
    default:
      return 0;
  }
}

void Variant::clear() {
#if OPT_STEP < 3
  switch (_type) {
    case VAR_I32:
      delete _value.asi32;
      break;
    case VAR_U32:
      delete _value.asu32;
      break;
    case VAR_FLOAT:
      delete _value.asfloat;
      break;
    case VAR_STR:
      delete _value.asstr;
      break;
    default:
      break;
  }
  _type = VAR_NULL;
#elif OPT_STEP > 3
  if ((_type >= VAR_I32) && (_type <= VAR_STR))
    free(_value.asstr);
  _type = VAR_NULL;
#else
  if (((_type >= VAR_I32) && (_type <= VAR_FLOAT)) || (_type == VAR_STR))
    free(_value.asstr);
  _type = VAR_NULL;
#endif
}

bool Variant::get(void *value) {
  if (! value)
    return false;
  switch (_type) {
    case VAR_BOOL:
      *(bool*)value = _value.asbool;
      break;
    case VAR_I8:
      *(int8_t*)value = _value.asi8;
      break;
    case VAR_U8:
      *(uint8_t*)value = _value.asu8;
      break;
    case VAR_I16:
      *(int16_t*)value = _value.asi16;
      break;
    case VAR_U16:
      *(uint16_t*)value = _value.asu16;
      break;
    case VAR_I32:
      *(int32_t*)value = *_value.asi32;
      break;
    case VAR_U32:
      *(uint32_t*)value = *_value.asu32;
      break;
    case VAR_FLOAT:
      *(float*)value = *_value.asfloat;
      break;
    case VAR_CHAR:
      *(char*)value = _value.aschar;
      break;
    case VAR_STR:
      strcpy((char*)value, _value.asstr);
      break;
    default:
      return false;
  }
  return true;
}

#if OPT_STEP == 0
Variant& Variant::operator=(bool value) {
  clear();
  _type = VAR_BOOL;
  _value.asbool = value;
  return *this;
}

Variant& Variant::operator=(int8_t value) {
  clear();
  _type = VAR_I8;
  _value.asi8 = value;
  return *this;
}

Variant& Variant::operator=(uint8_t value) {
  clear();
  _type = VAR_U8;
  _value.asu8 = value;
  return *this;
}

Variant& Variant::operator=(int16_t value) {
  clear();
  _type = VAR_I16;
  _value.asi16 = value;
  return *this;
}

Variant& Variant::operator=(uint16_t value) {
  clear();
  _type = VAR_U16;
  _value.asu16 = value;
  return *this;
}

Variant& Variant::operator=(int32_t value) {
  clear();
  _type = VAR_I32;
  _value.asi32 = new int32_t(value);
  return *this;
}

Variant& Variant::operator=(uint32_t value) {
  clear();
  _type = VAR_U32;
  _value.asu32 = new uint32_t(value);
  return *this;
}

Variant& Variant::operator=(float value) {
  clear();
  _type = VAR_FLOAT;
  _value.asfloat = new float(value);
  return *this;
}

Variant& Variant::operator=(char value) {
  clear();
  _type = VAR_CHAR;
  _value.aschar = value;
  return *this;
}

Variant& Variant::operator=(const char *value) {
  clear();
  _type = VAR_STR;
  _value.asstr = new char[strlen(value) + 1];
  strcpy(_value.asstr, value);
  return *this;
}

Variant& Variant::operator=(const __FlashStringHelper *value) {
  clear();
  _type = VAR_STR;
  _value.asstr = new char[strlen_P((PGM_P)value) + 1];
  strcpy_P(_value.asstr, (PGM_P)value);
  return *this;
}
#endif

#if OPT_STEP < 2
Variant& Variant::operator=(const Variant &value) {
  clear();
  _type = value._type;
  switch (_type) {
    case VAR_BOOL:
      _value.asbool = value._value.asbool;
      break;
    case VAR_I8:
      _value.asi8 = value._value.asi8;
      break;
    case VAR_U8:
      _value.asu8 = value._value.asu8;
      break;
    case VAR_I16:
      _value.asi16 = value._value.asi16;
      break;
    case VAR_U16:
      _value.asu16 = value._value.asu16;
      break;
    case VAR_I32:
      _value.asi32 = new int32_t(*value._value.asi32);
      break;
    case VAR_U32:
      _value.asu32 = new uint32_t(*value._value.asu32);
      break;
    case VAR_FLOAT:
      _value.asfloat = new float(*value._value.asfloat);
      break;
    case VAR_CHAR:
      _value.aschar = value._value.aschar;
      break;
    case VAR_STR:
      _value.asstr = new char[strlen(value._value.asstr) + 1];
      strcpy(_value.asstr, value._value.asstr);
      break;
    default:
      break;
  }
  return *this;
}
#endif

char *Variant::toStr(char *str, uint16_t maxlen) {
  switch (_type) {
    case VAR_BOOL:
      strncpy_P(str, BOOLS[_value.asbool], maxlen - 1);
      break;
    case VAR_I8:
      snprintf_P(str, maxlen - 1, PSTR("%d"), _value.asi8);
      break;
    case VAR_U8:
      snprintf_P(str, maxlen - 1, PSTR("%u"), _value.asi16);
      break;
    case VAR_I16:
      snprintf_P(str, maxlen - 1, PSTR("%d"), _value.asi16);
      break;
    case VAR_U16:
      snprintf_P(str, maxlen - 1, PSTR("%u"), _value.asi16);
      break;
    case VAR_I32:
      snprintf_P(str, maxlen - 1, PSTR("%ld"), *_value.asi32);
      break;
    case VAR_U32:
      snprintf_P(str, maxlen - 1, PSTR("%lu"), *_value.asu32);
      break;
    case VAR_FLOAT:
      snprintf_P(str, maxlen - 1, PSTR("%f"), *_value.asfloat);
      break;
    case VAR_CHAR:
      str[0] = _value.aschar;
      str[1] = '\0';
      break;
    case VAR_STR:
      strncpy(str, _value.asstr, maxlen - 1);
      break;
    default:
      *str = '\0';
  }
  str[maxlen - 1] = '\0';
  return str;
}

size_t Variant::toStream(Stream &stream) {
#if OPT_STEP < 3
  switch (_type) {
    case VAR_BOOL:
      return stream.print((const __FlashStringHelper*)BOOLS[_value.asbool]);
    case VAR_I8:
      return stream.print(_value.asi8);
    case VAR_U8:
      return stream.print(_value.asu8);
    case VAR_I16:
      return stream.print(_value.asi16);
    case VAR_U16:
      return stream.print(_value.asi16);
    case VAR_I32:
      return stream.print(*_value.asi32);
    case VAR_U32:
      return stream.print(*_value.asu32);
    case VAR_FLOAT:
      return stream.print(*_value.asfloat);
    case VAR_CHAR:
      return stream.write(_value.aschar);
    case VAR_STR:
      return stream.print(_value.asstr);
    default:
      return 0;
  }
#else
  if (_type == VAR_NULL)
    return 0;
  if (_type == VAR_STR) {
    return stream.print(_value.asstr);
  } else {
    char str[16];

    return stream.print(toStr(str, sizeof(str)));
  }
#endif
}

#if OPT_STEP
void Variant::set(vartype_t type, const void *value, bool inflash, bool clearing) {
  if (clearing)
    clear();
  _type = type;
  switch (_type) {
    case VAR_BOOL:
      _value.asbool = *(bool*)value;
      break;
    case VAR_I8:
      _value.asi8 = *(int8_t*)value;
      break;
    case VAR_U8:
      _value.asu8 = *(uint8_t*)value;
      break;
    case VAR_I16:
      _value.asi16 = *(int16_t*)value;
      break;
    case VAR_U16:
      _value.asu16 = *(uint16_t*)value;
      break;
    case VAR_I32:
      _value.asi32 = new int32_t(*(int32_t*)value);
      break;
    case VAR_U32:
      _value.asu32 = new uint32_t(*(uint32_t*)value);
      break;
    case VAR_FLOAT:
      _value.asfloat = new float(*(float*)value);
      break;
    case VAR_CHAR:
      _value.aschar = *(char*)value;
      break;
    case VAR_STR:
      if (inflash) {
        _value.asstr = new char[strlen_P((PGM_P)value) + 1];
        strcpy_P(_value.asstr, (PGM_P)value);
      } else {
        _value.asstr = new char[strlen((char*)value) + 1];
        strcpy(_value.asstr, (char*)value);
      }
      break;
    default:
      break;
  }
}
#endif
