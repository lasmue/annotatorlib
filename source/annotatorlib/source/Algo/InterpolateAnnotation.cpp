// Copyright 2016 Annotator Team
#define Annotator_AnnotatorLib_Algo_InterpolateAnnotation_BODY

/************************************************************
 InterpolateAnnotation class body
 ************************************************************/

// include associated header file
#include "AnnotatorLib/Algo/InterpolateAnnotation.h"
#include "AnnotatorLib/Annotation.h"
#include "AnnotatorLib/Frame.h"
#include "AnnotatorLib/Session.h"

#include <assert.h>
#include <algorithm>

namespace AnnotatorLib {
namespace Algo {

shared_ptr<Annotation> InterpolateAnnotation::getInterpolation(
    shared_ptr<Frame> frame, shared_ptr<Annotation> prev,
    shared_ptr<Annotation> next) {
  if (!prev) return nullptr;

  shared_ptr<Annotation> annotation =
      Annotation::make_shared(prev, frame, true);

  if (!next) return annotation;

  unsigned long startFrame = prev->getFrame()->getFrameNumber();
  unsigned long endFrame = next->getFrame()->getFrameNumber();
  unsigned long curFrame = frame->getFrameNumber();

  assert(prev->getObject() == next->getObject());
  assert(startFrame < curFrame);
  assert(endFrame > curFrame);

  float multiplier = 1.0f * (curFrame - startFrame) / (endFrame - startFrame);

  float curX = prev->getX() + (next->getX() - prev->getX()) * multiplier;
  float curY = prev->getY() + (next->getY() - prev->getY()) * multiplier;

  annotation->setX(curX);
  annotation->setY(curY);

  float curWidth =
      prev->getWidth() + (next->getWidth() - prev->getWidth()) * multiplier;
  float curHeight =
      prev->getHeight() + (next->getHeight() - prev->getHeight()) * multiplier;

  annotation->setWidth(curWidth);
  annotation->setHeight(curHeight);

  return annotation;
}

shared_ptr<Annotation> InterpolateAnnotation::getInterpolation(
    const std::shared_ptr<Session> session, const shared_ptr<Frame> frame,
    const shared_ptr<Object> object, bool interpolationsOnly) {
  assert(frame);
  assert(object);
  // is it the first frame of the object?
  if (!interpolationsOnly && object->getAnnotations().size() == 1 &&
      *frame == *object->getLastAnnotation()->getFrame()) {
    return object->getLastAnnotation();
  }

  if (object->getAnnotations().size() > 1) {
    // is frame within the valid range of the object?
    if (*frame <= *object->getLastAnnotation()->getFrame() &&
        *frame >= *object->getFirstAnnotation()->getFrame()) {
      shared_ptr<Annotation> a = session->getAnnotation(frame, object);

      if (!a) {
        // find the nearest neighbours (keyframes)
        shared_ptr<Annotation> left = nullptr;
        shared_ptr<Annotation> right = nullptr;
        object->findClosestKeyFrames(frame, left, right);
        return getInterpolation(frame, left, right);
      } else if (!interpolationsOnly) {
        return a;
      }
    }

  } else if (object->getLastAnnotation() &&
             *frame > *object->getLastAnnotation()->getFrame() &&
             object->isActive()) {
    // copy the previous annotation to the requested frame
    return Annotation::make_shared(object->getLastAnnotation(), frame, true);
  }

  return shared_ptr<Annotation>(nullptr);
}

std::vector<shared_ptr<Annotation>> InterpolateAnnotation::getInterpolations(
    const std::shared_ptr<Session> session, const shared_ptr<Frame> frame,
    bool interpolationsOnly) {
  const ObjectMap &objects_map = session->getObjects();
  std::vector<shared_ptr<Annotation>> return_annotations;

  for (auto &o : objects_map) {
    shared_ptr<Annotation> a =
        getInterpolation(session, frame, o.second, interpolationsOnly);

    if (a != nullptr) {
      return_annotations.push_back(a);
    }
  }

  return return_annotations;
}

}  // of namespace Algo
}  // of namespace AnnotatorLib
