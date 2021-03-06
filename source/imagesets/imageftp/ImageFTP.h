// Copyright 2016-2017 Annotator Team
#ifndef ANNOTATOR_ANNOTATORLIB_IMAGEFTP_H
#define ANNOTATOR_ANNOTATORLIB_IMAGEFTP_H

/************************************************************
 ImageFolder class header
 ************************************************************/

#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/ImageSet/AbstractImageSet.h>
#include <AnnotatorLib/annotatorlib_api.h>

#include <string>
#include <vector>

#include <Poco/Net/FTPClientSession.h>
#include <boost/filesystem.hpp>

namespace AnnotatorLib {
namespace ImageSet {
/************************************************************/
/**
 *
 */
class ANNOTATORLIB_API ImageFTP : public AbstractImageSet {
 public:
  ImageFTP(std::string path);

  ~ImageFTP();

  /**
   *
   * @return type
   */
  virtual ImageSetType getType() override;

  /**
   * @brief getImage
   * @param position
   * @return
   */
  virtual Image getImage(unsigned long position) override;

  virtual std::string getImagePath(unsigned long position) override;

  virtual bool gotoPosition(unsigned long position) override;

  virtual long getPosition() override;

  /**
   *
   * @return next
   */
  virtual bool hasNext() override;

  /**
   *
   * @return image
   */
  virtual Image next() override;

  /**
   *
   * @return size
   */
  virtual unsigned int size() override;

  virtual unsigned int getFPS() override;

  virtual std::string getPath() override;

  virtual bool equals(std::shared_ptr<AbstractImageSet> other) override;

 protected:
  void loadFolder();
  Image downloadImage(std::string file);

  std::string path;

  long position = 0;
  std::vector<boost::filesystem::path> images;
  std::vector<boost::filesystem::path>::const_iterator imgIter;

  std::shared_ptr<Poco::Net::FTPClientSession> ftpSession;
  std::string username;
  std::string password;
  int port = 21;
  std::string host;
  std::string workingDir;
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace ImageSet
}  // of namespace AnnotatorLib

/************************************************************
 End of ImageFTP class header
 ************************************************************/

#endif
