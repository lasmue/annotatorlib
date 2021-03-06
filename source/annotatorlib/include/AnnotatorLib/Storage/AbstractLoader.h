// Copyright 2016 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_LOADER_ABSTRACTLOADER_H
#define ANNOTATOR_ANNOTATORLIB_LOADER_ABSTRACTLOADER_H

/************************************************************
 AbstractLoader class header
 ************************************************************/

#include <AnnotatorLib/annotatorlib_api.h>

#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/AnnotatorLibDatastructs.h>

namespace AnnotatorLib {

class Session;

namespace Storage {

/************************************************************/
/**
 *
 */
class ANNOTATORLIB_API AbstractLoader {
 public:
  /**
   *
   * @param path
   */
  virtual void setPath(std::string /*in*/ path) = 0;

  /**
   *
   * @return type
   */
  virtual AnnotatorLib::StorageType getType() = 0;

  virtual void loadSession(AnnotatorLib::Session* session) = 0;

  virtual ~AbstractLoader() {}
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace Loader
}  // of namespace AnnotatorLib

/************************************************************
 End of AbstractLoader class header
 ************************************************************/

#endif
