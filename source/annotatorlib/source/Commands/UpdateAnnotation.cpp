// Copyright 2016 Annotator Team
#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Commands/UpdateAnnotation.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Session.h>

AnnotatorLib::Commands::UpdateAnnotation::UpdateAnnotation(
    shared_ptr<Annotation> annotation, float x, float y, float width,
    float height, float confidence) {
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
  this->confidence = confidence;
  this->annotation = annotation;
}

bool AnnotatorLib::Commands::UpdateAnnotation::execute(
    AnnotatorLib::Session *informSession) {
  old_x = annotation->getX();
  old_y = annotation->getY();
  old_width = annotation->getWidth();
  old_height = annotation->getHeight();
  old_confidence = annotation->getConfidenceScore();
  annotation->setPosition(x, y, width, height);
  annotation->setConfidenceScore(confidence);
  if (informSession) {
    informSession->updateAnnotation(annotation);
  }
  return true;
}

bool AnnotatorLib::Commands::UpdateAnnotation::undo(
    AnnotatorLib::Session *informSession) {
  annotation->setPosition(old_x, old_y, old_width, old_height);
  annotation->setConfidenceScore(old_confidence);
  if (informSession) {
    informSession->updateAnnotation(annotation);
  }
  return true;
}

shared_ptr<AnnotatorLib::Annotation>
AnnotatorLib::Commands::UpdateAnnotation::getAnnotation() {
  return annotation;
}
