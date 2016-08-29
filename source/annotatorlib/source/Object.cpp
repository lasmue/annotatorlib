// --------------------------------------------------------
// Code generated by Papyrus C++
// --------------------------------------------------------

#define Annotator_AnnotatorLib_Object_BODY

/************************************************************
 Object class body
 ************************************************************/

// include associated header file
#include <algorithm>
#include <assert.h>
#include "AnnotatorLib/Object.h"
#include "AnnotatorLib/Class.h"
#include "AnnotatorLib/Annotation.h"

// Derived includes directives

namespace AnnotatorLib {

// static attributes (if any)

static long lastId = 10000;
static long lastNamePostfix = 1;

Object::Object( ) : id(genId()) { genName(); }

Object::Object(unsigned long id) : id(id) { genName(); }

Object::Object(Class* c) : id(genId()), objectClass(c) { genName(); }

Object::Object(unsigned long id, Class* c) : id(id), objectClass(c) { genName(); }

unsigned long Object::genId() {
    lastId += 3;
    return lastId;
}

unsigned long Object::getId() const
{
    return id;
}

std::string Object::getName()
{
    return name;
}

void Object::setName(std::string name)
{
    this->name = name;
}

std::string Object::genName()
{
    std::string prefix = "unnamed_obj_";
    const Class* c = getClass();
    if (c)
        prefix = c->getName() + "_";
    return prefix + std::to_string(lastNamePostfix++);
}

Class *Object::getClass() const
{
    return objectClass;
}

void Object::setClass(Class *c)
{
    this->objectClass = c;
}

std::vector<Attribute *> Object::getAttributes() const
{
    return attributes;
}

bool Object::addAttribute(Attribute *attribute)
{
    if (attribute != nullptr && std::find(attributes.begin(), attributes.end(), attribute) == attributes.end()) {
        attributes.push_back(attribute);
        return true;
    }
    return false;
}

bool Object::removeAttribute(Attribute *attribute)
{
    std::vector<Attribute *>::const_iterator position = std::find(attributes.begin(), attributes.end(), attribute);
    if (position != attributes.end()){
        attributes.erase(position);
        return true;
    }
    return false;
}

Annotation *Object::getFirstAnnotation() const
{
    if(annotations.size() == 0)
        return nullptr;
    //anntations are sorted by frame-number, thus we directly return the first
    return annotations[0];
}

Annotation *Object::getLastAnnotation() const {
  if(annotations.size() == 0)
      return nullptr;
  //anntations are sorted by frame-number, thus we directly return the last
  return annotations[annotations.size() - 1];
}

std::vector<Annotation *> Object::getAnnotations() const
{
    return annotations;
}

bool Object::addAnnotation(Annotation *annotation)
{
    if (annotation != nullptr && annotation->getObject() == this && std::find(annotations.begin(), annotations.end(), annotation) == annotations.end()) {
        addAnnotationToSortedList(annotation);
        //annotations.push_back(annotation);
        //addFrame(annotation->getFrame());
        return true;
    }
    return false;
}

static struct _CompareAnnotationPointer
{
   bool operator() ( Annotation * left, Annotation * right) {
      return *left < *right;
   }
} _CompareAnnotationPointer;

static struct _CompareAnnotationPointerToFrame
{
   bool operator() ( const Annotation * left, const Frame right) {
      return *left->getFrame() < right;
   }
} _CompareAnnotationPointerToFrame;

bool Object::removeAnnotation(Annotation *annotation)
{
    //binary search for anntation
    if(annotation) {
      std::vector<Annotation *>::iterator  it = std::lower_bound(annotations.begin(), annotations.end(), annotation, _CompareAnnotationPointer);
      if (**it == *annotation) {
          Frame* frame = annotation->getFrame();
          if (frame) {
              frame->removeAnnotation(annotation);
              //this->removeFrame(frame);
          }
          if (annotation->getPrevious())
            annotation->getPrevious()->setNext(annotation->getNext());
            annotation->setPrevious(nullptr);
          if (annotation->getNext())
            annotation->getNext()->setPrevious(annotation->getPrevious());
            annotation->setNext(nullptr);
          annotations.erase(it);
          return true;
      }
    }
    return false;
}

std::vector<Frame *> Object::getFrames() const
{
    std::vector<Frame *> frames;
    for (Annotation* a : annotations) {
      frames.push_back(a->getFrame());
    }
    return frames;
}

//bool Object::addFrame(Frame *frame)
//{
//    if (frame != nullptr && std::find(frames.begin(), frames.end(), frame) == frames.end()) {
//        frames.push_back(frame);
//        return true;
//    }
//    return false;
//}

//bool Object::removeFrame(Frame *frame)
//{
//    std::vector<Frame *>::const_iterator position = std::find(frames.begin(), frames.end(), frame);
//    if (position != frames.end()){
//        frames.erase(position);
//        //TODO: remove all annotations of this frame
//        return true;
//    }
//    return false;
//}

Annotation* Object::getAnnotation(const Frame *frame) const {
  std::vector<Annotation *>::const_iterator  it = std::lower_bound(annotations.begin(), annotations.end(), *frame, _CompareAnnotationPointerToFrame);
  if (it != annotations.cend() && (*it)->getFrame() == frame)
    return *it;
  return nullptr;
}

bool Object::appearsInFrame(const Frame *frame) const
{
    return getAnnotation(frame) != nullptr;

//    if(annotations.size() > 0)
//    {
//        Annotation *annotation = annotations[0];
//        Annotation *first = annotation->getFirst();
//        assert(first);
//        Annotation *last = annotation->getLast();
//        assert(last);
//        if(first->getFrame()->getFrameNumber() <= frame->getFrameNumber()
//                && last->getFrame()->getFrameNumber() >= frame->getFrameNumber())
//            return true;
//        if(first->getFrame()->getFrameNumber() <= frame->getFrameNumber()
//                && !last->isFinished())
//            return true;
//    }
//    return false;
}

void Object::findClosestKeyFrames(const Frame *target_frame, Annotation*& left, Annotation*& right) const {
  std::vector<Annotation *>::const_iterator  it = std::lower_bound(annotations.cbegin(), annotations.cend(), *target_frame, _CompareAnnotationPointerToFrame);

  std::vector<Annotation *>::const_iterator  it_fwd = it;
  while ( it_fwd != annotations.cend() && (*it_fwd)->isInterpolated()) {
    it_fwd++;
  }
  right = *(it_fwd);

  while ( it != annotations.cbegin()) {
    it--;
    if ( !(*it)->isInterpolated())
      break;
  }
  left = *(it);

  assert(right != left);
  assert(right->isInterpolated() == false);
  assert(left->isInterpolated() == false);
}

void Object::addAnnotationToSortedList(Annotation* a) {

  if (annotations.empty()) {
    annotations.push_back(a);
    return;
  }

  // find the position for the lower_bound  element
  std::vector<Annotation*>::iterator pos = std::lower_bound( annotations.begin(), annotations.end(), a, _CompareAnnotationPointer);

  assert(pos == annotations.end() || **pos > *a);

  // insert it before pos
  std::vector<Annotation*>::iterator new_pos = annotations.insert(pos, a);

  if ( new_pos != annotations.begin()) {
    Annotation* prev = *std::prev(new_pos);
    prev->setNext(a);
    a->setPrevious(prev);
  }

  if ( std::next(new_pos) != annotations.end()) {
    Annotation* next = *std::next(new_pos);
    next->setPrevious(a);
    a->setNext(next);
  }



}

} // of namespace AnnotatorLib

/************************************************************
 End of Object class body
 ************************************************************/
