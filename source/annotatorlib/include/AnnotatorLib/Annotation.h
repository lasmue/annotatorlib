// --------------------------------------------------------
// Code generated by Papyrus C++
// --------------------------------------------------------

#ifndef ANNOTATOR_ANNOTATORLIB_ANNOTATION_H
#define ANNOTATOR_ANNOTATORLIB_ANNOTATION_H

/************************************************************
 Annotation class header
 ************************************************************/
#include <vector>

#include <AnnotatorLib/AnnotatorLibDatastructs.h>
#include <AnnotatorLib/annotatorlib_api.h>

namespace AnnotatorLib {

class Attribute;
class Frame;
class Object;

/************************************************************/
/**
 * @brief The Annotation class
 * Represents a label for an object on a specific frame.
 */
class ANNOTATORLIB_API Annotation {
 public:

  const unsigned long id = 0;

  Annotation();
  Annotation(const Annotation &obj);
  Annotation(AnnotationType type);
  Annotation(unsigned long id);

  /**
   *
   * @return id
   */
  static unsigned long genId();

  unsigned long getId() const;

  std::vector<Attribute *> getAttributes() const;
  bool addAttribute(Attribute *attribute);
  bool removeAttribute(Attribute *attribute);

  Frame *getFrame() const;
  void setFrame(Frame *frame);

  Object *getObject() const;
  void setObject(Object *object);

  AnnotationType getType() const;
  void setType(AnnotationType type);

  /**
   * @brief setPosition
   * @param x
   * @param y
   */
  void setPosition(float x, float y);

  void setPosition(float x, float y, float width, float height);
  /**
   * @brief setPosition
   * @param x
   * @param y
   * @param hradius the radius horizontally
   * @param vradius the radius vertically
   */
  void setCenterPosition(float x, float y, float hradius, float vradius);

  int getX() const;
  void setX(float x);
  int getY() const;
  void setY(float y);

  float getWidth() const;
  void setWidth(float width);
  float getHeight() const;
  void setHeight(float height);

  float getHRadius() const;
  void setHRadius(float hradius);
  float getVRadius() const;
  void setVRadius(float vradius);

  void setNext(Annotation *next);
  Annotation *getNext() const;
  void setPrevious(Annotation *previous);
  Annotation *getPrevious() const;

  Annotation *getFirst();
  Annotation *getLast();
  bool isLast() const;
  bool isFirst() const;

  void setFinished(bool ended);
  bool isFinished();

  void setInterpolated(bool interpolated);
  bool isInterpolated() const;

 protected:

  /**
   *
   */
  std::vector<Attribute *> attributes;
  /**
   *
   */
  Object *object;

  /**
   * @brief frame where the annotation is.
   */
  Frame *frame;

  AnnotationType type = AnnotationType::RECTANGLE;

  Annotation *next = nullptr;
  Annotation *previous = nullptr;

  ///////////////////////////////

  // top, left corner, width, height
  float x = 0;
  float y = 0;

  float width = 0;
  float height = 0;

  bool interpolated = false;
};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

}  // of namespace AnnotatorLib

/************************************************************
 End of Annotation class header
 ************************************************************/

#endif
