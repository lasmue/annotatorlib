#ifndef REMOVEANNOTATION
#define REMOVEANNOTATION

#include <AnnotatorLib/Commands/Command.h>

namespace AnnotatorLib {

class Session;
class Annotation;

namespace Commands {

class ANNOTATORLIB_API RemoveAnnotation: public Command
{
public:
    RemoveAnnotation(Session *, Annotation *);
    ~RemoveAnnotation() { delete annotation; }

    bool execute();

    bool undo();

    Annotation *getAnnotation();

protected:
    Annotation *annotation = nullptr;
    Session *session = nullptr;
};

}
}
#endif // REMOVEANNOTATION
