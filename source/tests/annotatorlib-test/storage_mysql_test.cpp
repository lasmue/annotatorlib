// Copyright 2016 Annotator Team
#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Session.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include "../../storages/mysql/MySQLStorage.h"

using namespace AnnotatorLib;
using std::shared_ptr;

class storage_mysql_test : public testing::Test {
 public:
};

TEST_F(storage_mysql_test, createTables) {
  MySQLStorage storage;
  storage.setPath(
      "host=localhost;user=annotator;password=annotator;db=annotatortestdb;"
      "auto-reconnect=true");
  ASSERT_TRUE(storage.open());
}

TEST_F(storage_mysql_test, objects) {
  MySQLStorage storage;
  storage.setPath(
      "host=localhost;user=annotator;password=annotator;db=annotatortestdb;"
      "auto-reconnect=true");
  ASSERT_TRUE(storage.open());
  auto c = std::make_shared<Class>("testclass");

  storage.addClass(c);
  storage.removeClass(c.get());

  shared_ptr<Object> o = std::make_shared<Object>();
  o->setClass(c);
  o->setName("testobject");
  storage.addObject(o);

  shared_ptr<Object> o2 = storage.getObject(o->getId());
  ASSERT_TRUE(o == o2);
  ASSERT_TRUE(o2->getName() == "testobject");

  MySQLStorage storage2;
  storage2.setPath(
      "host=localhost;user=annotator;password=annotator;db=annotatortestdb;"
      "auto-reconnect=true");
  ASSERT_TRUE(storage2.open());
  shared_ptr<Object> o3 = storage2.getObject(o->getId());
  ASSERT_TRUE(o3->getName() == "testobject");
}

TEST_F(storage_mysql_test, annotations) {
  MySQLStorage storage;
  storage.setPath(
      "host=localhost;user=annotator;password=annotator;db=annotatortestdb;"
      "auto-reconnect=true");
  ASSERT_TRUE(storage.open());
  auto c = std::make_shared<Class>("testclass");

  storage.addClass(c);
  storage.removeClass(c.get());

  shared_ptr<Object> o = std::make_shared<Object>();
  o->setClass(c);
  o->setName("testobject");
  storage.addObject(o);

  shared_ptr<Object> o2 = storage.getObject(o->getId());
  ASSERT_TRUE(o == o2);
  ASSERT_TRUE(o2->getName() == "testobject");

  shared_ptr<Frame> f = std::make_shared<Frame>(1);
  shared_ptr<Annotation> a =
      Annotation::make_shared(f, o, AnnotationType::RECTANGLE);
  a->setPosition(0, 0, 1, 1);
  ASSERT_TRUE(storage.addAnnotation(a, true));

  MySQLStorage storage2;
  storage2.setPath(
      "host=localhost;user=annotator;password=annotator;db=annotatortestdb;"
      "auto-reconnect=true");
  ASSERT_TRUE(storage2.open());
  shared_ptr<Object> o3 = storage2.getObject(o->getId());
  ASSERT_TRUE(o3->getName() == "testobject");

  shared_ptr<Annotation> a2 = storage2.getAnnotation(a->getId());
  ASSERT_TRUE(storage2.getAnnotations().size() > 0);
  ASSERT_TRUE(a2->getObject()->getName() == "testobject");
  ASSERT_TRUE(storage2.getFrames().size() == 1);
}

TEST_F(storage_mysql_test, attributes) {
  MySQLStorage storage;
  storage.setPath(
      "host=localhost;user=annotator;password=annotator;db=annotatortestdb;"
      "auto-reconnect=true");
  ASSERT_TRUE(storage.open());
  auto c = std::make_shared<Class>("testclass");

  storage.addClass(c);
  storage.removeClass(c.get());

  shared_ptr<Object> o = std::make_shared<Object>();
  o->setClass(c);
  o->setName("testobject");

  shared_ptr<Attribute> attr = std::make_shared<Attribute>(
      AnnotatorLib::Attribute::genId(), AnnotatorLib::AttributeType::BOOLEAN,
      "light");
  attr->getValue()->setValue(true);
  o->addAttribute(attr);

  storage.addObject(o);

  shared_ptr<Object> o2 = storage.getObject(o->getId());
  ASSERT_TRUE(o == o2);
  ASSERT_TRUE(o2->getName() == "testobject");

  shared_ptr<Frame> f = std::make_shared<Frame>(1);
  shared_ptr<Annotation> a =
      Annotation::make_shared(f, o, AnnotationType::RECTANGLE);
  a->setPosition(0, 0, 1, 1);

  a->addAttribute(attr);
  ASSERT_TRUE(storage.addAnnotation(a, true));

  MySQLStorage storage2;
  storage2.setPath(
      "host=localhost;user=annotator;password=annotator;db=annotatortestdb;"
      "auto-reconnect=true");
  ASSERT_TRUE(storage2.open());
  shared_ptr<Object> o3 = storage2.getObject(o->getId());
  ASSERT_TRUE(o3->getName() == "testobject");

  shared_ptr<Annotation> a2 = storage2.getAnnotation(a->getId());
  ASSERT_TRUE(storage2.getAnnotations().size() > 0);
  ASSERT_TRUE(a2->getObject()->getName() == "testobject");
  ASSERT_TRUE(storage2.getFrames().size() == 1);
  ASSERT_TRUE(a2->getAttribute("light")->getValue()->getBoolean());
}
