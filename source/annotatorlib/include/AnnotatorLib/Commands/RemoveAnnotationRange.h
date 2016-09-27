#ifndef REMOVEANNOTATIONRANGE
#define REMOVEANNOTATIONRANGE

#include <AnnotatorLib/Commands/Command.h>
#include <AnnotatorLib/Commands/RemoveAnnotation.h>
#include <memory>

using std::shared_ptr;

namespace AnnotatorLib {

class Session;
class Frame;
class Object;

namespace Commands {
/**
 * @brief The RemoveAnnotationRange class
 * Iterates over a range of frames and executes command RemoveAnnotation on them.
 */
class ANNOTATORLIB_API RemoveAnnotationRange : public Command {
 public:

    /**
   * @brief RemoveAnnotationRange
   * @param s the session to work with
   * @param o object to remove annotations from
   * @param f1 the first frame in range
   * @param f2 the last frame in range
   */
  RemoveAnnotationRange(std::shared_ptr<AnnotatorLib::Session> s, shared_ptr<Object> o, shared_ptr<Frame> f1, shared_ptr<Frame> f2);
  ~RemoveAnnotationRange() {}

  bool execute();

  bool undo();

  shared_ptr<AnnotatorLib::Object> getObject();
  shared_ptr<AnnotatorLib::Frame> getFrame1();
  shared_ptr<AnnotatorLib::Frame> getFrame2();

 protected:
  std::vector<shared_ptr<Annotation>> removedAnnotations;
  std::shared_ptr<AnnotatorLib::Frame> frame1, frame2;
  std::shared_ptr<AnnotatorLib::Object> object;
  std::shared_ptr<AnnotatorLib::Session> session = nullptr;
};
}
}
#endif  // REMOVEANNOTATIONRANGE
