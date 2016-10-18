#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Commands/CompressObject.h>
#include <AnnotatorLib/Commands/NewAnnotation.h>
#include <AnnotatorLib/Commands/RemoveAnnotation.h>
#include <AnnotatorLib/Commands/RemoveAnnotationRange.h>
#include <AnnotatorLib/Commands/RemoveObject.h>
#include <AnnotatorLib/Commands/UpdateObject.h>
#include <AnnotatorLib/Project.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

using std::shared_ptr;
using namespace AnnotatorLib;

class commands_test : public testing::Test {
 public:
};

TEST_F(commands_test, newAnnotation) {
  std::shared_ptr<Session> session = std::make_shared<Session>();
  ASSERT_EQ(session->getAnnotations().size(), (unsigned long)0);

  shared_ptr<Frame> frame = std::make_shared<Frame>(1);
  shared_ptr<Class> c = std::make_shared<Class>("car");

  Commands::NewAnnotation *nA =
      new Commands::NewAnnotation(1001, c, session, frame, 10, 10, 5, 5);

  session->execute(shared_ptr<Commands::Command>(nA));
  ASSERT_EQ(session->getAnnotations().size(), 1ul);
  shared_ptr<Object> o = session->getObject(1001);
  ASSERT_EQ(o->getAnnotations().size(), 1ul);

  session->undo();
  ASSERT_EQ(session->getAnnotations().size(), 0ul);

  // call redo 2 times
  session->redo();
  ASSERT_EQ(session->getAnnotations().size(), 1ul);
  session->redo();
  ASSERT_EQ(session->getAnnotations().size(), 1ul);

  // call undo 2 times
  session->undo();
  ASSERT_EQ(session->getAnnotations().size(), 0ul);
  session->undo();
  ASSERT_EQ(session->getAnnotations().size(), 0ul);

  for (unsigned long i = 0ul; i < 5; ++i) {
    session->execute(std::make_shared<Commands::NewAnnotation>(
        1001 + i, c, session, frame, 10, 10, 5, 5));
    ASSERT_EQ(session->getAnnotations().size(), i + 1);
    ASSERT_EQ(session->getObjects().size(), i + 1);
  }
  for (long i = 4ul; i >= 0; --i) {
    session->undo();
    ASSERT_EQ(session->getAnnotations().size(), (unsigned long)i);
    ASSERT_EQ(session->getObjects().size(), (unsigned long)i);
  }
}

TEST_F(commands_test, updateObject) {
  std::shared_ptr<Session> session = std::make_shared<Session>();
  auto frame = std::make_shared<Frame>(1);
  auto c = std::make_shared<Class>("car");

  Commands::NewAnnotation *nA =
      new Commands::NewAnnotation(1001, c, session, frame, 10, 10, 5, 5);

  session->execute(shared_ptr<Commands::Command>(nA));

  auto c_new = std::make_shared<Class>("person");

  Commands::UpdateObject *uO =
      new Commands::UpdateObject(session->getObject(1001), c_new);

  session->execute(shared_ptr<Commands::Command>(uO));
  ASSERT_EQ(session->getAnnotations().size(), 1ul);
  ASSERT_EQ(session->getObjects().size(), 1ul);
  ASSERT_EQ(session->getObject(1001)->getClass()->getName(), "person");

  session->undo();
  ASSERT_EQ(session->getObject(1001)->getClass()->getName(), "car");
  ASSERT_EQ(session->getAnnotations().size(), 1ul);
  ASSERT_EQ(session->getObjects().size(), 1ul);

  session->redo();
  ASSERT_EQ(session->getObject(1001)->getClass()->getName(), "person");
  ASSERT_EQ(session->getAnnotations().size(), 1ul);
  ASSERT_EQ(session->getObjects().size(), 1ul);
}

TEST_F(commands_test, removeObject) {
  std::shared_ptr<Session> session = std::make_shared<Session>();

  auto frame = std::make_shared<Frame>(1);
  auto c = std::make_shared<Class>("car");

  Commands::NewAnnotation *nA =
      new Commands::NewAnnotation(1001, c, session, frame, 10, 10, 5, 5);

  session->execute(shared_ptr<Commands::Command>(nA));

  ASSERT_EQ(session->getAnnotations().size(), 1ul);
  ASSERT_EQ(session->getObjects().size(), 1ul);

  session->execute(shared_ptr<Commands::Command>(
      new Commands::RemoveObject(session, session->getObject(1001))));
  ASSERT_EQ(session->getAnnotations().size(), 0ul);
  ASSERT_EQ(session->getObjects().size(), 0ul);

  session->undo();
  ASSERT_EQ(session->getAnnotations().size(), 1ul);
  ASSERT_EQ(session->getObjects().size(), 1ul);

  session->redo();
  ASSERT_EQ(session->getAnnotations().size(), 0ul);
  ASSERT_EQ(session->getObjects().size(), 0ul);
}

TEST_F(commands_test, removeAnnotation) {
  std::shared_ptr<Session> session = std::make_shared<Session>();
  ASSERT_EQ(session->getAnnotations().size(), 0ul);

  shared_ptr<Class> c = std::make_shared<Class>("car");
  shared_ptr<Object> o = std::make_shared<Object>(c);

  // create frame 2,4,6,8,10
  for (unsigned long i = 2; i < 11; i += 2) {
    session->execute(
        shared_ptr<Commands::NewAnnotation>(new Commands::NewAnnotation(
            session, o, std::make_shared<Frame>(i), 10, 10, 5, 5)));
  }

  ASSERT_EQ(session->getAnnotations().size(), 5ul);

  std::shared_ptr<Annotation> a2 =
      o->getAnnotation(session->getFrame((unsigned long)2));
  session->execute(shared_ptr<Commands::RemoveAnnotation>(
      new Commands::RemoveAnnotation(session, a2)));

  ASSERT_EQ(session->getAnnotations().size(), 4ul);
  session->undo();
  ASSERT_EQ(session->getAnnotations().size(), 5ul);
  session->redo();
  ASSERT_EQ(session->getAnnotations().size(), 4ul);
  session->undo();
  ASSERT_EQ(session->getAnnotations().size(), 5ul);

  // REMOVE RANGE
  session->execute(shared_ptr<Commands::RemoveAnnotationRange>(
      new Commands::RemoveAnnotationRange(session, o, 1ul, 3ul)));

  ASSERT_EQ(session->getAnnotations().size(), 4ul);
  session->undo();
  ASSERT_EQ(session->getAnnotations().size(), 5ul);

  session->execute(shared_ptr<Commands::RemoveAnnotationRange>(
      new Commands::RemoveAnnotationRange(session, o, 1ul, 11ul)));

  ASSERT_EQ(session->getAnnotations().size(), 0ul);
  session->undo();
  ASSERT_EQ(session->getAnnotations().size(), 5ul);

  session->execute(shared_ptr<Commands::RemoveAnnotationRange>(
      new Commands::RemoveAnnotationRange(session, o, 2ul, 4ul)));

  ASSERT_EQ(session->getAnnotations().size(), 3ul);
  session->undo();
  ASSERT_EQ(session->getAnnotations().size(), 5ul);
}

TEST_F(commands_test, compressObject) {
  std::shared_ptr<Session> session = std::make_shared<Session>();
  shared_ptr<Object> obj = std::make_shared<Object>();

  for (unsigned long i = 0; i < 5; ++i) {
    shared_ptr<Frame> frame_i = std::make_shared<Frame>(i);
    session->addAnnotation(Annotation::make_shared(frame_i, obj));
    session->getAnnotation(frame_i, obj)->setPosition(i * 10, 40, 20, 20);
    ASSERT_EQ(session->getAnnotations().size(), i + 1);
    ASSERT_EQ(session->getFrames().size(), i + 1);
  }
  ASSERT_EQ(session->getFrames().size(), 5ul);
  ASSERT_EQ(obj->getAnnotations().size(), 5ul);

  Commands::CompressObject *cmd = new Commands::CompressObject(session, obj);
  session->execute(shared_ptr<Commands::Command>(cmd));

  ASSERT_EQ(obj->getAnnotations().size(), 2ul);

  session->undo();

  ASSERT_EQ(obj->getAnnotations().size(), 5ul);

  session->redo();

  ASSERT_EQ(obj->getAnnotations().size(), 2ul);
}
