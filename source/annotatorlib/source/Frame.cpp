// --------------------------------------------------------
// Code generated by Papyrus C++
// --------------------------------------------------------

#define Annotator_AnnotatorLib_Frame_BODY

/************************************************************
 Frame class body
 ************************************************************/

// include associated header file
#include <algorithm>
#include "AnnotatorLib/Frame.h"

// Derived includes directives

namespace AnnotatorLib {

Frame::Frame(unsigned long frame_number) : frame_number(frame_number) { }

Frame::~Frame()
{
    annotations.clear();
}

std::vector<Annotation *> Frame::getAnnotations() const
{
    return annotations;
}

bool Frame::hasAnnotations() const
{
    return !annotations.empty();
}

bool Frame::addAnnotation(Annotation *annotation)
{
    if (annotation != nullptr && std::find(annotations.begin(), annotations.end(), annotation) == annotations.end()) {
        annotations.push_back(annotation);
        annotation->setFrame(this);
        return true;
    }
    return false;
}

bool Frame::removeAnnotation(Annotation *annotation)
{
    std::vector<Annotation *>::const_iterator position = std::find(annotations.begin(), annotations.end(), annotation);
    if (position != annotations.end()){
        annotations.erase(position);
        return true;
    }
    return false;
}

std::vector<Attribute *> Frame::getAttributes() const
{
    std::vector<Attribute *> attributes;

    for (std::vector<Annotation *>::const_iterator it = annotations.begin() ; it != annotations.end(); ++it)
    {
        Annotation * annotation = *it;
        for(Attribute *attribute: annotation->getAttributes()){
            if(attribute != nullptr)
                attributes.push_back(attribute);
        }
    }

    // remove duplicates
    std::sort( attributes.begin(), attributes.end() );
    attributes.erase( std::unique( attributes.begin(), attributes.end() ), attributes.end() );

    return attributes;
}

unsigned long Frame::getFrameNumber() const
{
    return frame_number;
}

bool Frame::equals(Frame *other) const
{
    if(this == other)
        return true;
    if(this->frame_number != other->frame_number)
        return false;
    if(this->annotations.size() != other->annotations.size())
        return false;
    return true;
}

// static attributes (if any)

}// of namespace AnnotatorLib

/************************************************************
 End of Frame class body
 ************************************************************/
