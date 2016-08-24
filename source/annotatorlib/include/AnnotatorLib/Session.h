// --------------------------------------------------------
// Code generated by Papyrus C++
// --------------------------------------------------------

#ifndef ANNOTATOR_ANNOTATORLIB_SESSION_H
#define ANNOTATOR_ANNOTATORLIB_SESSION_H

/************************************************************
 Session class header
 ************************************************************/
#include <vector>

#include <AnnotatorLib/annotatorlib_api.h>
#include <AnnotatorLib/AnnotatorLibDatastructs.h>

#include <AnnotatorLib/AnnotatorAlgoInterface.h>
#include <AnnotatorLib/Annotation.h>
#include <AnnotatorLib/Attribute.h>
#include <AnnotatorLib/Class.h>
#include <AnnotatorLib/Frame.h>
#include <AnnotatorLib/Object.h>
#include <AnnotatorLib/Commands/Command.h>

namespace AnnotatorLib {

/************************************************************/
/**
 * @brief The Session class
 * Contains pointers to all data within a session.
 */
class ANNOTATORLIB_API Session {


public:
    Session();
    virtual ~Session();

    // Attributes
    virtual std::vector<Attribute *> getAttributes();
    virtual bool addAttribute(Attribute* attribute);
    virtual bool removeAttribute(Attribute* attribute);
    virtual Attribute *getAttribute(unsigned long id);

    // Annotations
    virtual std::vector<Annotation *> getAnnotations();
    virtual bool addAnnotation(Annotation* annotation);
    virtual bool removeAnnotation(const Annotation* annotation);
    virtual Annotation *getAnnotation(unsigned long id);

    // Classes
    virtual std::vector<Class *> getClasses();
    virtual bool addClass(Class *c);
    virtual bool removeClass(Class * c);
    virtual Class *getClass(unsigned long id);
    virtual Class *getClass(std::string name);

    // Frames
    virtual std::vector<Frame *> getFrames();
    virtual bool addFrame(Frame* frame);
    virtual bool removeFrame(Frame* frame);
    /**
     * @brief getFrame
     * @param number
     * @return The Frame by given Frame Number
     */
    virtual Frame *getFrame(unsigned long number);

    virtual std::vector<Object *> getObjects();
    virtual bool addObject(Object* object);
    virtual bool removeObject(Object* object);
    /**
     * @brief getFirstObjectByName
     * @param name
     * @return Object with given name
     */
    virtual Object * getFirstObjectByName(std::string name);
    virtual Object *getObject(unsigned long id);

    virtual bool execute(AnnotatorLib::Commands::Command *command);
    virtual bool redo();
    virtual bool undo();


protected:

	/**
	 * 
	 */
    std::vector<Frame*> frames;
	/**
	 * 
	 */
    std::vector<Object*> objects;
	/**
	 * 
	 */
    std::vector<Attribute*> attributes;
	/**
	 * 
	 */
    std::vector<Annotation*> annotations;
	/**
	 * 
	 */
    std::vector<Class*> classes;

    unsigned int commandIndex = 0;
    std::vector<AnnotatorLib::Commands::Command*> commands;

    AnnotatorAlgo::AnnotatorAlgoInterface *annotatorAlgo;

};
/************************************************************/
/* External declarations (package visibility)               */
/************************************************************/

/* Inline functions                                         */

} // of namespace AnnotatorLib

/************************************************************
 End of Session class header
 ************************************************************/

#endif
