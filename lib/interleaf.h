#ifndef INTERLEAF_H
#define INTERLEAF_H

#include <fstream>

#include "core.h"
#include "info.h"
#include "object.h"

namespace si {

class Interleaf : public Core
{
public:
  enum Error
  {
    ERROR_SUCCESS,
    ERROR_IO,
    ERROR_INVALID_INPUT,
    ERROR_INVALID_BUFFER_SIZE
  };

  LIBWEAVER_EXPORT Interleaf();

  LIBWEAVER_EXPORT void Clear();

  LIBWEAVER_EXPORT Error Read(const char *f);
  LIBWEAVER_EXPORT Error Write(const char *f) const;

#ifdef _WIN32
  LIBWEAVER_EXPORT Error Read(const wchar_t *f);
  LIBWEAVER_EXPORT Error Write(const wchar_t *f) const;
#endif

  Error Read(std::istream &is);
  Error Write(std::ostream &os) const;

  Info *GetInformation() { return &m_Info; }

private:

  Error ReadChunk(Core *parent, std::istream &is, Info *info);

  Object *ReadObject(std::istream &is, Object *o, std::stringstream &desc);
  void WriteObject(std::ostream &os, const Object *o) const;

  void InterleaveObjects(std::ostream &os, const std::vector<Object*> &objects) const;
  void WriteSubChunk(std::ostream &os, uint16_t flags, uint32_t object, uint32_t time, const bytearray &data = bytearray()) const;
  void WritePadding(std::ostream &os, uint32_t size) const;

  Info m_Info;

  uint32_t m_Version;
  uint32_t m_BufferSize;
  uint32_t m_BufferCount;

  std::vector<uint32_t> m_ObjectList;
  std::map<uint32_t, Object*> m_ObjectIDTable;

};

}

#endif // INTERLEAF_H
