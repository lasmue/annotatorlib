// Copyright 2016 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_IMAGEFTP_H
#define ANNOTATOR_ANNOTATORLIB_IMAGEFTP_H

/************************************************************
 ImageFolder class header
 ************************************************************/

#include <boost/filesystem.hpp>
#include <vector>

#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/annotatorlib_api.h>

#include <AnnotatorLib/ImageSet.h>

namespace AnnotatorLib {

/************************************************************/
/**
 *
 */
class ANNOTATORLIB_API ImageFTP : public ImageSet {
 public:
  ImageFTP(std::string path);

  /**
   *
   * @return type
   */
  virtual ImageSetType getType();

  /**
   * @brief getImage
   * @param position
   * @return
   */
  virtual Image getImage(unsigned long position) override;

  virtual bool gotoPosition(unsigned long position) override;

  virtual long getPosition() override;

  /**
   *
   * @return next
   */
  virtual bool hasNext();

  /**
   *
   * @return image
   */
  virtual Image next();

  /**
   *
   * @return size
   */
  virtual unsigned int size();

  virtual unsigned int getFPS() override;

  virtual std::string getPath();

  virtual bool equals(ImageSet *other);

 protected:
  void loadFolder();

  std::string path;

  long position = 0;
  std::vector<boost::filesystem::path> images;
  std::vector<boost::filesystem::path>::const_iterator imgIter;
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace AnnotatorLib

/************************************************************
 End of ImageFTP class header
 ************************************************************/

#endif
