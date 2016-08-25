
#include <gmock/gmock.h>
#include <string>
#include <AnnotatorLib/Algo/InterpolateAnnotation.h>
#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Frame.h>
#include <AnnotatorLib/Project.h>

class annotation_test : public testing::Test {
 public:
};

TEST_F(annotation_test, genId) {
  AnnotatorLib::Annotation annotation1(AnnotatorLib::Annotation::genId());
  AnnotatorLib::Annotation annotation2(AnnotatorLib::Annotation::genId());
  std::cout << "Annotation 1 id:" << annotation1.getId() << std::endl;
  std::cout << "Annotation 2 id:" << annotation2.getId() << std::endl;

  ASSERT_LT(annotation1.getId(), annotation2.getId());
}

TEST_F(annotation_test, previousAndNext) {
  AnnotatorLib::Annotation annotation1(AnnotatorLib::Annotation::genId());
  AnnotatorLib::Annotation annotation2(AnnotatorLib::Annotation::genId());

  annotation1.setNext(&annotation2);
  annotation2.setPrevious(&annotation1);

  ASSERT_EQ(annotation1.getNext(), &annotation2);
  ASSERT_EQ(annotation2.getPrevious(), &annotation1);

  ASSERT_EQ(annotation1.getPrevious(), nullptr);
  ASSERT_EQ(annotation2.getNext(), nullptr);
}

TEST_F(annotation_test, interpolation) {
  AnnotatorLib::Annotation annotation5(AnnotatorLib::Annotation::genId());
  annotation5.setPosition(100, 200, 20, 40);
  AnnotatorLib::Annotation annotation15(AnnotatorLib::Annotation::genId());
  annotation15.setPosition(200, 140, 40, 30);

  AnnotatorLib::Frame frame5(5);
  frame5.addAnnotation(&annotation5);
  AnnotatorLib::Frame frame10(10);
  AnnotatorLib::Frame frame15(15);
  frame15.addAnnotation(&annotation15);

  AnnotatorLib::Annotation* annotation10 =
      AnnotatorLib::Algo::InterpolateAnnotation::getInterpolation(
          &frame10, &annotation5, &annotation15);

  ASSERT_EQ(annotation10->getFrame(), &frame10);
  ASSERT_EQ(annotation10->getX(), 150);
  ASSERT_EQ(annotation10->getY(), 170);
  ASSERT_EQ(annotation10->getHRadius(), 30);
  ASSERT_EQ(annotation10->getVRadius(), 35);

  delete annotation10;
}