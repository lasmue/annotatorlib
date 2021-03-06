// Copyright 2016 Annotator Team
#ifndef ANNOTATOR_ANNOTATORALGO_ANNOTATORALGOINTERFACE_H
#define ANNOTATOR_ANNOTATORALGO_ANNOTATORALGOINTERFACE_H

/************************************************************
 AnnotatorAlgoInterface class header
 ************************************************************/
#include <memory>
#include <opencv2/core/core.hpp>
#include <vector>

#include <AnnotatorLib/Commands/Command.h>
#include <AnnotatorLib/Image.h>
#include <AnnotatorLib/annotatorlib_api.h>

namespace AnnotatorLib {
class Annotation;
class Frame;
class Object;
class Project;
}

using std::shared_ptr;

namespace AnnotatorAlgo {

/************************************************************/
/**
 *
 */
class ANNOTATORLIB_API AnnotatorAlgoInterface {
 public:
  /**
   *
   * @param image
   */
  virtual bool setFrame(shared_ptr<AnnotatorLib::Frame> frame,
                        cv::Mat image) = 0;

  /**
   *
   * @param object
   */
  virtual void setObject(shared_ptr<AnnotatorLib::Object> object) = 0;

  virtual shared_ptr<AnnotatorLib::Object> getObject() const = 0;

  virtual bool requiresObject() const { return true; }

  /**
   * @brief setLastAnnotation
   * @param annotation
   */
  virtual void setLastAnnotation(
      shared_ptr<AnnotatorLib::Annotation> annotation) = 0;

  virtual std::vector<shared_ptr<AnnotatorLib::Commands::Command>>
  getCommands() = 0;

  virtual void setProject(std::shared_ptr<AnnotatorLib::Project> project) {
    this->project = project;
  }
  virtual std::shared_ptr<AnnotatorLib::Project> getProject() const {
    return project;
  }

  /**
 * @brief calculate
 * calculates an annotation for the given frame of an object using given image.
 * @param object
 * @param frame
 * @param image
 */
  virtual std::vector<shared_ptr<AnnotatorLib::Commands::Command>> calculate(
      shared_ptr<AnnotatorLib::Object> object,
      shared_ptr<AnnotatorLib::Frame> frame, bool execute_commands = true) = 0;

 protected:
  std::shared_ptr<AnnotatorLib::Project> project = nullptr;
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace AnnotatorAlgo

/************************************************************
 End of AnnotatorAlgoInterface class header
 ************************************************************/

#endif
