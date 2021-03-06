// Copyright 2016 Annotator Team
#ifndef REMOVEANNOTATION
#define REMOVEANNOTATION

#include <AnnotatorLib/Commands/Command.h>
#include <memory>

using std::shared_ptr;

namespace AnnotatorLib {

class Session;
class Frame;
class Annotation;

namespace Commands {

class ANNOTATORLIB_API RemoveAnnotation : public Command {
 public:
  RemoveAnnotation(std::shared_ptr<AnnotatorLib::Session> s,
                   shared_ptr<Annotation> a);
  ~RemoveAnnotation() {}

  virtual bool execute(Session *informSession = 0) override;

  virtual bool undo(Session *informSession = 0) override;

  shared_ptr<AnnotatorLib::Annotation> getAnnotation();

 protected:
  std::shared_ptr<AnnotatorLib::Session> session = nullptr;
  shared_ptr<Annotation> annotation;
};
}
}
#endif  // REMOVEANNOTATION
