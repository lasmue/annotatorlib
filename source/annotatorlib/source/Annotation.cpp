// --------------------------------------------------------
// Code generated by Papyrus C++
// --------------------------------------------------------

#define Annotator_AnnotatorLib_Annotation_BODY

/************************************************************
 Annotation class body
 ************************************************************/

// include associated header file
#include "AnnotatorLib/Annotation.h"
#include "AnnotatorLib/Frame.h"
#include "AnnotatorLib/Object.h"

#include <assert.h>
#include <algorithm>
// Derived includes directives

namespace AnnotatorLib {

// static attributes (if any)
static unsigned long lastId = 100000;
/**
 *
 * @return id
 */
Annotation::Annotation() : id(genId()) { }

Annotation::Annotation(const Annotation &obj) : Annotation() {
  this->attributes = obj.attributes;
  this->next = obj.next;
  this->previous = obj.previous;

  this->type = obj.type;
  this->frame = obj.frame;
  this->object = obj.object;

  this->x = obj.x;
  this->y = obj.y;
  this->width = obj.width;
  this->height = obj.height;
}

Annotation::Annotation(AnnotationType type) : Annotation() {
  this->type = type;
}

Annotation::Annotation(unsigned long id) : id(id) {
  if (lastId < id) lastId = id;
}

unsigned long Annotation::genId() {
  lastId += 5;
  return lastId;
}

unsigned long Annotation::getId() const { return id; }

std::vector<Attribute *> Annotation::getAttributes() const { return attributes; }

bool Annotation::addAttribute(Attribute *attribute) {
  if (attribute != nullptr &&
      std::find(attributes.begin(), attributes.end(), attribute) ==
          attributes.end()) {
    attributes.push_back(attribute);
    return true;
  }
  return false;
}

bool Annotation::removeAttribute(Attribute *attribute) {
  std::vector<Attribute *>::const_iterator position =
      std::find(attributes.begin(), attributes.end(), attribute);
  if (position != attributes.end()) {
    attributes.erase(position);
    return true;
  }
  return false;
}

Frame *Annotation::getFrame() const { return frame; }

void Annotation::setFrame(Frame *frame) {
  if (this->frame != frame) {
    this->frame = frame;
    // if(frame != nullptr)
    //    frame->addAnnotation(this);
  }
}

Object *Annotation::getObject() const { return object; }

void Annotation::setObject(Object *object) {
  if (this->object != object) {
    this->object = object;
    if (object != nullptr) object->addAnnotation(this);
  }
}

AnnotationType Annotation::getType() const { return this->type; }

void Annotation::setType(AnnotationType type) { this->type = type; }

void Annotation::setCenterPosition(float x, float y, float hradius,
                                   float vradius) {
  setX(x);
  setY(y);
  setHRadius(hradius);
  setVRadius(vradius);
}

int Annotation::getX() const { return x; }

void Annotation::setX(float x) { this->x = x; }

int Annotation::getY() const { return y; }

void Annotation::setY(float y) { this->y = y; }

float Annotation::getWidth() const { return width; }

void Annotation::setWidth(float width) {
  assert(width > 0);
  this->width = width;
}

float Annotation::getHeight() const { return height; }

void Annotation::setHeight(float height) {
  assert(height > 0);
  this->height = height;
}

float Annotation::getHRadius() const { return width / 2; }

void Annotation::setHRadius(float hradius) {
  assert(hradius > 0);
  if (hradius < 0) hradius *= -1;
  this->width = hradius * 2;
}

float Annotation::getVRadius() const { return height / 2; }

void Annotation::setVRadius(float vradius) {
  assert(vradius > 0);
  if (vradius < 0) vradius *= -1;
  this->height = vradius * 2;
}

void Annotation::setNext(Annotation *next) {
  if (this->next != next) {
    if (next == nullptr) {
      // this->next->setPrevious(nullptr);
      this->next = next;
    } else {
      this->next = next;
      // next->setPrevious(this);
    }
  }
}

Annotation *Annotation::getNext() const { return next; }

void Annotation::setPrevious(Annotation *previous) {
  if (this->previous != previous) {
    if (previous == nullptr) {
      // this->previous->setNext(nullptr);
      this->previous = previous;
    } else {
      this->previous = previous;
      // previous->setNext(this);
    }
  }
}

Annotation *Annotation::getPrevious() const { return previous; }

Annotation *Annotation::getFirst() {
  if (this->previous == nullptr) return this;
  return previous->getFirst();
}

Annotation *Annotation::getLast() {
  if (this->isLast()) return this;
  return next->getLast();
}

bool Annotation::isLast() const {
  return this->next == nullptr || this->next == this;
}

bool Annotation::isFirst() const { return this->previous == nullptr; }

void Annotation::setFinished(bool ended) {
  if (ended) {
    getLast()->next = getLast();
  } else {
    getLast()->next = nullptr;
  }
}

bool Annotation::isFinished() { return getLast()->next == getLast(); }

void Annotation::setInterpolated(bool interpolated) {
  this->interpolated = interpolated;
}

bool Annotation::isInterpolated() const { return interpolated; }

void Annotation::setPosition(float x, float y) {
  this->x = x;
  this->y = y;
}

void Annotation::setPosition(float x, float y, float width, float height) {
  setX(x);
  setY(y);
  setWidth(width);
  setHeight(height);
}

}  // of namespace AnnotatorLib

/************************************************************
 End of Annotation class body
 ************************************************************/
