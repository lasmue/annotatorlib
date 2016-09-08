#ifndef COMPRESSSESSION_CMD_H
#define COMPRESSSESSION_CMD_H

#include <AnnotatorLib/Commands/Command.h>
#include <vector>
#include <memory>

using std::shared_ptr;
using std::vector;

namespace AnnotatorLib {

class Session;
class Annotation;

namespace Commands {

class ANNOTATORLIB_API CompressSession : public Command {
 public:
  CompressSession() = delete;

  CompressSession(Session* session);

  ~CompressSession() {
    removed_annotations.clear();
  }

  bool execute();

  bool undo();

 protected:
  Session* session;

 private:
  vector<shared_ptr<Annotation>> removed_annotations;
};
}
}
#endif  // UPDATEANNOTATION_H